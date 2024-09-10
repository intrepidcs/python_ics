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
- MAC
- Linux
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

Hardware / software testing:
- Run all python ics functions on all hardware
- Verify all networks, transmit, recieve, message functions