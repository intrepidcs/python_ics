##############################################################################
Examples
##############################################################################

Examples can be found at https://github.com/intrepidcs/python_ics/tree/master/examples

For extra information on data structures and underlying functionality, please visit neoVI DLL Documentation under https://intrepidcs.com/support/support-resources/

Opening a device
==============================================================================

The ``open_device_example.py`` example shows how to successfully open and close an Intrepid device.

Transmitting and Receiving a CAN message
==============================================================================

The following examples show how to interact with CAN messages on an Intrepid device.

- ``transmit_can_example.py``: Basic example showing how to transmit and receive standard CAN frame
- ``transmit_can_xtd_example.py``: Builds off of the CAN example and adds extended Arbitration ID attributes
- ``canfd_transmit_example.py``: Bare minimum example on how to transmit over CANFD. 


ISO 15765-2 Example
==============================================================================

The ``iso15765_example.py`` example shows how to setup basic ISO 15765-2 receive filters and transmitting an ISO 15765-2 message.

After opening an Intrepid device ``ics.iso15765_enable_networks`` should be called to enable ISO 15765-2. 

Receive filtering can be established by passing a custom ``ics.CmISO157652RxMessage()`` to ``ics.iso15765_receive_message()``. 

Similarly transmitting an ISO 15765-2 frame can be accomplished by passing a custom ``ics.CmISO157652TxMessage()`` to ``ics.iso15765_transmit_message()``.


Missing an example?
==============================================================================

Need an example on something that isn't covered here? Please submit an issue on github or feel free to send over a Pull Request of your own.