import os
import dunamai
import pathlib

GEN_DIR = pathlib.Path("./gen")
GEN_ICS_DIR = GEN_DIR / "ics"

def get_pkg_version() -> str:
    """
    Get the package version.

    Returns:
        str: The package version.
    """
    # version = dunamai.Version.from_git()
    # # Set the dev version if the environment variable is set.
    # if os.getenv("PYTHON_ICS_DEV_BUILD") is not None:
    #     pkg_version = version.serialize(format="v{base}.dev{distance}", style=dunamai.Style.Pep440)
    # else:
    #     pkg_version = version.serialize(format="{base}", style=dunamai.Style.Pep440)
    return dunamai.Version.from_git().serialize(metadata=False)
    # return pkg_version

def create_version_py(path: pathlib.Path = pathlib.Path("gen/ics/__version.py")) -> None:
    """
    Create a version.py file with the package version and full version.

    Args:
        path (pathlib.Path, optional): The path to the version.py file. Defaults to pathlib.Path("gen/ics/__version.py").

    Returns:
        None
    """
    pkg_version = get_pkg_version()
    full_version = dunamai.Version.from_git().serialize(format="v{base}-{commit}-{timestamp}")
    print(f"Creating '{path}' with version {pkg_version} and full version {full_version}...")
    path.parent.mkdir(parents=True, exist_ok=True)
    # Write the version file to disk
    with open(path, "w+") as f:
        f.write(f"""__version__ = "{pkg_version}"\n""")
        f.write(f"""__full_version__ = "{full_version}"\n""")

def create_ics_init():
    fdata = \
"""# Warning: This file is auto generated. Don't modify if you value your sanity!
try:
    import ics.__version
    __version__ = ics.__version.__version__
    __full_version__ = ics.__version.__full_version__
except Exception as ex:
    print(ex)


from ics.structures import *
from ics.structures.neo_device import NeoDevice, neo_device
from ics.hiddenimports import hidden_imports
try:
    from ics.py_neo_device_ex import PyNeoDeviceEx
except ModuleNotFoundError as ex:
    print(f"Warning: {ex}")

try:
    # Release environment
    #print("Release")
    from ics.ics import *
except Exception as ex:
    # Build environment
    #print("Debug", ex)
    from ics import *
"""
    init_path = GEN_ICS_DIR / "__init__.py"
    print(f"Creating '{init_path}'...")
    init_path.parent.mkdir(parents=True, exist_ok=True)
    with open(init_path, "w+") as f:
        f.write(fdata)


if __name__ == "__main__":
    create_ics_init()
    create_version_py()
    print("Version info generated!")