import python_ics
import random
import time
import os
import ldfparser


def parse_ldf():
    path = os.path.join(os.path.dirname(__file__), "lin22.ldf")
    return ldfparser.parse_ldf(path)


def open_device(index=0):
    device = None
    # python_ics.open_device() won't open a device if we have handles open already
    # so we need to find them and specify which ones to connect to.
    devices = python_ics.find_devices()
    print(
        "Opening Device {} (Open Client handles: {})...".format(
            devices[index], devices[index].NumberOfClients
        )
    )
    python_ics.open_device(devices[index])
    device = devices[index]
    print("Opened Device %s." % device)
    return device


def receive_lin(device):
    msgs, error_count = python_ics.get_messages(device)
    print("Received {} messages with {} errors.".format(len(msgs), error_count))
    netids = {python_ics.NETID_LIN: "LIN 1"}  # , python_ics.NETID_LIN2: "LIN 2" }
    for i, m in enumerate(msgs):
        netid = netids.get(m.NetworkID)
        if netid is not None:
            # print('\nMessage #{}: '.format(i+1), end='')
            print("{}".format(netid), end="")
            if m.StatusBitField & python_ics.SPY_STATUS_INIT_MESSAGE:
                print(" | Init")
            data_list = []
            for x in m.Header[1:]:
                data_list.append(x)
            for y in m.Data:
                data_list.append(y)
            try:
                frame_name = ldf.get_frame(m.Header[0] & 0x3F).name
                if frame_name is not None:
                    print("{} | ".format(frame_name), end="")
            except:
                pass
            print("ID: {} | ".format(hex(m.Header[0])), end="")
            if len(data_list):
                checksum = data_list.pop()
                print("Data: {} | ".format([hex(x) for x in data_list]), end="")
                print("Checksum: {}".format(hex(checksum)))
            print()
    return True


def send_frame(self, baudrate: int, frame_id: int, data: bytearray, netid: int, is_commander: bool):
    # set baudrate with device settings?
    msg = python_ics.SpyMessageJ1850()
    if is_commander:
        msg.StatusBitField = python_ics.SPY_STATUS_INIT_MESSAGE
    msg.Protocol = python_ics.SPY_PROTOCOL_LIN
    msg.NetworkID = netid
    header_bytes = [frame_id]
    frame_bytes = []
    if len(data):
        hdr_len = min(len(data), 2)
        data_len = min((len(data) - hdr_len), 6)
        checksum = 0
        if hdr_len > 0:
            header_bytes += list(data[0:hdr_len])
        if data_len > 0:
            frame_bytes += list(data[hdr_len:])
        for byte in header_bytes + frame_bytes:
            checksum += byte
            if checksum > 255:
                checksum -= 255
        if len(header_bytes) == 2:
            header_bytes.append(~checksum & 0xFF)
        else:
            frame_bytes.append(~checksum & 0xFF)
    msg.Header = tuple(header_bytes)
    msg.Data = tuple(frame_bytes)
    msg.NumberBytesHeader = len(msg.Header)
    msg.NumberBytesData = len(msg.Data)
    try:
        python_ics.transmit_messages(self.device, msg)
    except python_ics.RuntimeError as ex:
        print(ex)
        return False
    return True


class LINCommander:
    def __init__(self, device):
        self.device = device
        self.frames = {}

    def send_commander_frame(self, baudrate: int, frame_id: int, data: bytearray):
        send_frame(self, baudrate, frame_id, data, python_ics.NETID_LIN, True)


class LINResponder:
    def __init__(self, device):
        self.device = device
        self.frames = {}

    def send_responder_frame(self, baudrate: int, frame_id: int, data: bytearray):
        send_frame(self, baudrate, frame_id, data, python_ics.NETID_LIN2, False)


if __name__ == "__main__":
    import time

    ldf = parse_ldf()
    # Lets figure out how many are connected to the PC and display it
    connected_count = len(python_ics.find_devices())
    print("Found {} connected device(s)...".format(connected_count))
    device = open_device(0)
    responder_nodes = ldf.get_slaves()
    commander_nodes = ldf.get_master()
    lin_cmdr = LINCommander(device)
    lin_resp = LINResponder(device)
    for resp in responder_nodes:
        for each in resp.publishes_frames:
            lin_resp.frames.update({each.name: each})

    for cmdr in commander_nodes.publishes_frames:
        lin_cmdr.frames.update({cmdr.name: cmdr})

    collision_schedule = ldf.get_schedule_table("Collision_resolver")
    for entry in collision_schedule.schedule:
        if entry.frame is not None:
            if entry.frame.name in lin_cmdr.frames:
                cmdr_data = entry.frame.encode({})
                lin_cmdr.send_commander_frame(ldf.baudrate, entry.frame.frame_id, cmdr_data)
            elif entry.frame.name in lin_resp.frames:
                resp_data = entry.frame.encode({})
                lin_resp.send_responder_frame(ldf.baudrate, entry.frame.frame_id, resp_data)
                time.sleep(150 / 1000)
                lin_cmdr.send_commander_frame(ldf.baudrate, entry.frame.frame_id, bytearray())
            time.sleep(150 / 1000)

    # request_frame = ldf.get_unconditional_frame('CEM_Frm1')
    # request_data = request_frame.encode({"InternalLightsRequest": 'on'}, ldf.converters)
    # lin_cmdr.send_commander_frame(ldf.baudrate, request_frame.frame_id, request_data)

    # responseFrame = ldf.get_unconditional_frame('RSM_Frm1')
    # responseData = responseFrame.encode({"RightIntLightsSwitch": 'off'}, ldf.converters)
    # lin_resp.send_responder_frame(ldf.baudrate, responseFrame.frame_id, responseData)
    receive_lin(device)
    time.sleep(1)
    print("Finished.")
