import os
import dunamai
import pathlib

GEN_DIR = pathlib.Path("./gen")
GEN_VERSION_PY = GEN_DIR / "__version.py"

def get_pkg_version() -> str:
    """
    Get the package version.

    Returns:
        str: The package version.
    """
    version = dunamai.Version.from_git()
    # Set the dev version if the environment variable is set.
    if os.getenv("PYTHON_ICS_DEV_BUILD") is not None:
        pkg_version = version.serialize(format="v{base}.dev{distance}", style=dunamai.Style.Pep440)
    else:
        pkg_version = version.serialize(format="{base}", style=dunamai.Style.Pep440)
    return pkg_version

def create_version_py(path: pathlib.Path = GEN_VERSION_PY) -> None:
    """
    Create a version.py file with the package version and full version.

    Args:
        path (pathlib.Path, optional): The path to the version.py file. Defaults to GEN_VERSION_PY.

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
    # Bring the auto generated structures into scope
    from .structures import *
    from .structures.neo_device import NeoDevice, neo_device
except ImportError as ex:
    # If we are still building this won't work correctly.
    import sys
    print("Warning: .structures is not installed. .structures will not be available.", file=sys.stderr, flush=True)

# Bring the c module "ics" into the parent scope
try:
    from .ics import *
except ImportError as ex:
    # If we are still building this won't work correctly.
    import sys
    print("Warning: ics module is not installed. ics will not be available.", file=sys.stderr, flush=True)

# Bring the auto generated python files info into the parent scope
from . import __version
__version__ = __version.__version__
__full_version__ = __version.__full_version__
from .hiddenimports import hidden_imports

# Bring python files into the parent scope
from .py_neo_device_ex import PyNeoDeviceEx

"""
    init_path = GEN_DIR / "__init__.py"
    print(f"Creating '{init_path}'...")
    init_path.parent.mkdir(parents=True, exist_ok=True)
    with open(init_path, "w+") as f:
        f.write(fdata)


if __name__ == "__main__":
    create_ics_init()
    create_version_py()
    print("Version info generated!")