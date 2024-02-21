import os
import dunamai
import pathlib


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
    # Write the version file to disk
    with open(path, "w+") as f:
        f.write(f"""__version__ = "{pkg_version}"\n""")
        f.write(f"""__full_version__ = "{full_version}"\n""")


if __name__ == "__main__":
    create_version_py()
