import os
import dunamai
import pathlib
import tomlkit

GEN_DIR = pathlib.Path("./gen")
GEN_VERSION_PY = GEN_DIR / "__version.py"

def get_module_name() -> str:
    """
    Get the project name specified from the pyproject.toml file.
    
    Returns:
        str: The project name.
    """
    with open("pyproject.toml", "rb") as f:
        data = tomlkit.load(f)
        return data["project"]["name"]

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

if __name__ == "__main__":
    create_version_py()
    print("Version info generated!")