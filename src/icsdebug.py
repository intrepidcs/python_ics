import os

input(os.getpid())

import ics
import struct

ics.override_library_name(r"C:\dev\vspy3\Binaries\win64\icsneo40.dll")

CHIP_IDs = {
    82: "FIRE3_ZCHIP_ID",
    109: "NEOVI_FIRE3_LINUX_ID",
    121: "NEOVI_CONNECT_ZCHIP_ID",
    126: "NEOVI_FIRE3_LINUX_ID",
}

def dot_version(version: int) -> str:
    version = '.'.join(str(x) for x in struct.unpack("4B", version.to_bytes(4, byteorder='big')))
    return version.lstrip('0.')

def linux_state(component_info: int) -> str:
    match component_info:
        case 1:
            return "SD Card/MMC Partition 2"
        case 2:
            return "SD Card/MMC Partition 3"
        case 3:
            return "RAM"
        case _:
            return f"Unknown {component_info}"

d = ics.open_device()
print(str(d))
versions = d.get_component_versions()
for version in versions:
    print(f"\t{version.valid}")
    print(f"\t{version.expansionSlot}")
    print(f"\t{version.componentInfo}: {linux_state(version.componentInfo)}")
    print(f"\t{version.reserved}")
    print(f"\t{version.identifier}: {CHIP_IDs[version.identifier]}")
    print(f"\t{version.dotVersion}: {dot_version(version.dotVersion)}")
    print(f"\t{version.commitHash}")
    print()
