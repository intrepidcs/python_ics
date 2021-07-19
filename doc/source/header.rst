============================================================
python_ics
============================================================

Intrepid Control Systems, Inc. open source Python module for interfacing to Intrepid hardware. Basic knowledge of using and installing Python modules is assumed. Please see https://docs.python.org/3/installing/index.html for documentation on how to install Python modules.

This module is essentially just a wrapper around icsneo40.dll. For more documentation please visit neoVI DLL Documentation under https://intrepidcs.com/support/support-resources/

============================================================
Whats New?
============================================================

-Updated icsnVC40.h to v905.10
-Fixed a bunch of issues with setting structures. Script was essentially completely re-written with unit tests now.

============================================================
v903+ Compatibility Changes
============================================================

ISO 15765-2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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


Setting support for the following devices:

- red:  s_red_settings 
- fire:  s_fire_settings 
- firevnet:  s_fire_vnet_settings 
- cyan:  s_cyan_settings (FIRE2) 
- vcan3:  svcan3_settings 
- vcan4:  svcan4_settings 
- ecu:  secu_settings 
- ievb:  sievb_settings 
- pendant:  s_pendant_settings 
- radgalaxy:  srad_galaxy_settings 
- radstar2:  srad_star2_settings 
- neoobd2_sim:  sobd2_sim_settings 
- cmprobe:  s_cm_probe_settings 
- obd2pro:  sobd2_pro_settings 
- vcan412:  svcan412_settings 
- vcan4_12:  svcan412_settings 
- neoecu_avb:  secu_avb_settings 
- radsupermoon:  srad_super_moon_settings 
- radmoon2:  srad_moon2_settings 
- pluto:  srad_pluto_settings 
- plutoswitch:  s_pluto_switch_settings_s 
- radgigalog:  srad_gigalog_settings 
- canhub:  scan_hub_settings 
- neoecu12:  s_neo_ecu12_settings 
- vcanrf:  svcanrf_settings 
- eevb:  seevb_settings 
- flexvnetz:  s_flex_vnetz_settings 
- vividcan:  s_vivid_can_settings 
- vcan4_ind:  svcan4_ind_settings 
- radgigastar:  srad_gigastar_settings 
- jupiter:  srad_jupiter_settings 
- fire3:  s_fire3_settings 
- radmoon_duo:  s_rad_moon_duo_settings

PyInstaller
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Due to the added complexity underneath when building PyInstaller ``hidden_imports.py`` should be used now in your spec script:

.. code-block:: python

    # -*- mode: python ; coding: utf-8 -*-
    
    import ics
    
    block_cipher = None
    
    
    a = Analysis(['test.py'],
                 pathex=['.'],
                 binaries=[],
                 datas=[],
                 hiddenimports=ics.hidden_imports,
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



Other Fixes and Changes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Expanded documentation.
- Adding support for Python 3.8 and Python 3.9.
- Updated iso15765 example to utilize new flags.
- Updated documentation to mention libicsneolegacy.so
- Fixed an issue when get_messages() timeout was 0 no messages were returned.
- Updated documentation and added use_server option for opening devices.
- Added read_jupiter_firmware and write_jupiter_firmware methods.
- Fixed a memory leak in find_devices()
- Add methods for Gigalog/Gigastar disk formatting
- Fixed a documentation issue per issue #90
- Fixed month being offset by 1 in ics.get_rtc().
- Fixed transmit_messages() to handle extended network ids.
- Fixed code related to meth_get_backup_power_ready() internally.

============================================================
Versioning Information
============================================================

Minor differences can occur between different icsnVC40.h versions. These differences are usually just structures and constant differences. Below is a list of how the python_ics version correlates to the icsnVC40.h version:

v903
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Starting with 903, python_ics module will now match official upstream version releases.

``pip install 'python_ics>=5.0,<904.0' --force-reinstall``

    **Note:** Refer to platform specific installation if not on Windows

Older Versions:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
- v802
    ``pip install 'python_ics>=2.0,<3.0' --force-reinstall``

        **Note:** Refer to platform specific installation if not on Windows

- v803
    ``pip install 'python_ics>=3.0,<4.0' --force-reinstall``

        **Note:** Refer to platform specific installation if not on Windows

- v900
    ``pip install 'python_ics>=4.0,<5.0' --force-reinstall``

        **Note:** Refer to platform specific installation if not on Windows


============================================================
Installation on Windows
============================================================

PyPi provides binary packages for Windows. You can simply install the python_ics module by running the following command:

``pip install python_ics``

    **Note:** pip.exe is usually located under the Scripts directory under the Python
    installation directory.

    
Building from source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Building from source on windows is not usually need so it won't really be covered here in detail. As a starting point you'll need to match the compiler version used to build the official Python binaries (MSVC). If the build environment is setup correctly, you should be able to run ``python setup.py build`` like usual. 

Intrepid icsneo40 Library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
python_ics module looks for ``icsneo40.dll`` in the normal windows DLL search paths. The module will throw an exception if its not found.



============================================================
Installation on Linux
============================================================
python_ics does not provide binaries for linux distributions so we will have to compile from source. This can be easily achieved by utilzing Python's PIP. First we need to make sure we have some base packages installed.

libicsneo is a newer library and has wider support for Intrepid Products under linux (https://github.com/intrepidcs/libicsneo).
libicsneo has a legacy library (``libicsneolegacy.so``) that can be loaded by utilizing ``ics.override_library_name("libicsneolegacy.so")``.


Fedora Dependencies (FC28)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``sudo dnf install redhat-rpm-config gcc g++ python3-devel``

Debian/Ubuntu Dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``sudo apt install build-essential python-dev``

Others (Required dependencies)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
- GCC
- G++
- Python Development packages (We Need to link to Python.h)


Installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After dependencies are installed we can run the following pip command:

``pip install python_ics``

    **Note:** A lot of distributions have Python 2 and 3 installed side by side. As of this writing without a version suffix the commands still default to version 2 of the Python binaries. In order to utilize the Python 3 binaries you must append a 3 after the binary names (python3 and pip3 instead of just python and pip).

Intrepid libicsneoapi.so Library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Please see https://github.com/intrepidcs/icsneoapi for more details.


============================================================
Getting Started
============================================================

Please see https://github.com/intrepidcs/python_ics/tree/master/examples for simple examples on how to use this module. Most function documentation has a simple example on how its intended to be used. Every function was designed to be as close as possible to it's C counterpart unless it was deemed to make the function more pythonic in nature. 

For those experienced with the C API ``ics.open_device`` (``icsneoOpenNeoDevice()``) behavior has been changed the most (no parameters makes it auto utilize ``ics.find_devices`` (``icsneoFindNeoDevices()``) and open the first device). Also since python is a object oriented language the module utilizes this and auto cleans up device handles when going out of scope so there is usually no need to call ``ics.close_device()``.

