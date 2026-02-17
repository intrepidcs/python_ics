import os
import dunamai
import pathlib
import re

GEN_DIR = pathlib.Path("./gen")
GEN_ICS_DIR = GEN_DIR / "ics"


def _get_version_from_metadata() -> str:
    """
    Try to read version from existing package metadata (PKG-INFO).
    Used as fallback when building from sdist in isolated environment.
    """
    # Check for PKG-INFO in the egg-info directory
    egg_info_dirs = list(pathlib.Path(".").glob("*.egg-info"))
    if egg_info_dirs:
        pkg_info = egg_info_dirs[0] / "PKG-INFO"
        if pkg_info.exists():
            try:
                content = pkg_info.read_text()
                match = re.search(r"^Version:\s+(.+)$", content, re.MULTILINE)
                if match:
                    return match.group(1)
            except Exception:
                pass
    return None

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
    try:
        return dunamai.Version.from_git().serialize(metadata=False)
    except RuntimeError:
        # Fallback when git is not available (e.g., in isolated build environments)
        # Try to read version from existing package metadata
        metadata_version = _get_version_from_metadata()
        if metadata_version:
            return metadata_version
        # Final fallback
        return "0.0.0.dev0"
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
    try:
        full_version = dunamai.Version.from_git().serialize(format="v{base}-{commit}-{timestamp}")
    except RuntimeError:
        # Fallback when git is not available
        full_version = f"v{pkg_version}"
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