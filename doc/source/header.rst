##############################################################################
README
##############################################################################
.. mdinclude:: ../../README.md


##############################################################################
PyInstaller
##############################################################################

Due to the added complexity underneath when building, PyInstaller ``hidden_imports.py`` should be used now in your spec script:

.. code-block:: python

    # -*- mode: python ; coding: utf-8 -*-
    
    import python_ics
    
    block_cipher = None
    
    
    a = Analysis(['test.py'],
                 pathex=['.'],
                 binaries=[],
                 datas=[],
                 hiddenimports=ics.hiddenimports.hidden_imports,
                 hookspath=[],
                 runtime_hooks=[],
                 excludes=[],
                 win_no_prefer_redirects=False,
                 win_private_assemblies=False,
                 cipher=block_cipher,
                 noarchive=False)
    pyz = PYZ(a.pure, a.zipped_data,
                 cipher=block_cipher)
    exe = EXE(pyz,
              a.scripts,
              [],
              exclude_binaries=True,
              name='test',
              debug=False,
              bootloader_ignore_signals=False,
              strip=False,
              upx=True,
              console=True )
    coll = COLLECT(exe,
                   a.binaries,
                   a.zipfiles,
                   a.datas,
                   strip=False,
                   upx=True,
                   upx_exclude=[],
                   name='test')

##############################################################################
Breaking Changes v915
##############################################################################

The icsneo40 library has migrated to the NeoDeviceEx structure and python_ics has finally been updated to reflect these changes. A new class `ics.PyNeoDeviceEx` now inherits `ics.structures.neo_device_ex.neo_device_ex` and allows a more pythonic way of coding.

Previous:

.. code-block:: python

    import python_ics
    # Open the first device
    device = ics.open_device()
    # Load default settings
    ics.load_default_settings(device)
    # Close the device
    ics.close_device(device)
    # When device goes out of scope, its automatically cleaned up here by garbage collection if not closed

New:

.. code-block:: python

    import python_ics
    # Open the first device
    device = ics.open_device()
    # Load default settings
    device.load_default_settings()
    # Close the device
    device.close()
    # When device goes out of scope, its automatically cleaned up here by garbage collection if not closed


`ics.PyNeoDeviceEx` includes accessors to provide backwards compatibility with the old NeoDevice class so all existing code should still be functional.

##############################################################################
Breaking Changes v903
##############################################################################

ISO 15765-2
==============================================================================

old naming conventions have been updated to reflex closer to the actual codebase.

.. code-block:: python

    # Old:
    tx_msg = ics.CmISO157652TxMessage()
    rx_msg = ics.CmISO157652RxMessage()

    # New:
    tx_msg = ics.st_cm_iso157652_tx_message.st_cm_iso157652_tx_message()
    rx_msg = ics.st_cm_iso157652_rx_message.st_cm_iso157652_rx_message()

``ics.st_cm_iso157652_tx_message.st_cm_iso157652_tx_message()`` data structure is now a ctypes.c_ubytes array instead of a python list.

.. code-block:: python

    # Old:
    msg.data = [x for x in range(number_of_bytes)]

    # New:
    my_data = [x for x in range(number_of_bytes)]
    msg.data = (ctypes.c_ubyte*len(msg.data))(*my_data)

    >>> msg.data
    <ics.structures.st_cm_iso157652_tx_message.c_ubyte_Array_4096 object at 0x0000023E534BE940>

Settings
==============================================================================

v903 and up have converted over to a new auto generation of ``icsnVC40.h``. This enables faster support for newer Intrepid devices and less error prone. With this switch we have moved to using ``ics.s_device_settings``.

.. code-block:: python

    # Old behavior:
    device = ics.open_device()
    settings = ics.get_device_settings(device)
    # settings is a Vcan3Settings type
    settings.can1.Baudrate = 1
    ics.set_device_settings(device, settings)

    # New behavior
    device = ics.open_device()
    settings = ics.get_device_settings(device)
    # settings is a s_device_settings type
    settings.vcan3.can1.Baudrate = 1
    ics.set_device_settings(device, settings)

##############################################################################
Getting Started
##############################################################################

Please see https://github.com/intrepidcs/python_ics/tree/master/examples for simple examples on how to use this module. Most function documentation has a simple example on how its intended to be used. Every function was designed to be as close as possible to it's C counterpart unless it was deemed to make the function more pythonic in nature. 

For those experienced with the C API ``ics.open_device`` (``icsneoOpenNeoDevice()``) behavior has been changed the most (no parameters makes it auto utilize ``ics.find_devices`` (``icsneoFindNeoDevices()``) and open the first device). Also since python is a object oriented language the module utilizes this and auto cleans up device handles when going out of scope so there is usually no need to call ``ics.close_device()``.
