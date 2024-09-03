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
PC -> USB -> NIC -> ETH -> Fire3 -> CAN/LIN/ETH network v v
          -> Fire2 -> CAN/LIN/ETH network             v | ^
          -> VCAN42 -> (2x)CAN network                ^ ^
          -> NIC -> ETH -> Moon2 -> Moon2 network v
                        -> Moon2 -> Moon2 network ^

Hardware / software testing:
- Run all python ics functions on all hardware
- Verify all USB, ETH, CAN, LIN networks