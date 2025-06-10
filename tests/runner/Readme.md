Runner tests
===

This directory is specifically for testing against hardware attached to the runner.

Each runner consists of the following ICS hardware:
- neoVI FIRE3
- neoVI FIRE2
- ValueCAN4-2
- RAD-Moon2
- RAD-Moon2

Runner platforms:
- Windows 10
- MacOS (something? M1)
- Linux (Debian)
- Linux ARM (Raspberry PI)

Hardware setup:
PC -> USB -> NIC -> ETH -> Fire3 -> CAN1/2 network v v
                                 -> LIN network    | | V
                                 -> ETH network    | | | V
          -> Fire2 -> CAN1/2 network             v | ^ | |
                   -> LIN network                | |   ^ |
                   -> ETH network                | |     ^
          -> VCAN42 -> CAN1/2 network            ^ ^
          -> NIC -> ETH -> Moon2 -> 100/1000BASE-T1 network v
          -> NIC -> ETH -> Moon2 -> 100/1000BASE-T1 network ^

Software setup:
- Both Moon2 USB NIC adapter properties must be set:
    - "ASIX USB to Gigabit Ethernet Family Adapter" -> "Ethernet" (windows 10)
    - "ASIX USB to Gigabit Ethernet Family Adapter #2" -> "Ethernet 2" (windows 10)
        - IPV6 disabled
        - IPV4 IP address: 192.168.69.10, 192.168.69.11
        - IPV4 subnet mask: 255.255.255.0

Hardware / software testing:
- Run all python ics functions on all hardware
- Verify all networks, transmit, recieve, message functions
- Verify all example scripts are fully working