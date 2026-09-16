"""Build-time import validation must not load ics into the build process."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

import generate_icsneo40_structs as generator


@pytest.fixture
def generated_package(tmp_path, monkeypatch):
    package = tmp_path / "generated package" / "ics"
    structures = package / "structures"
    structures.mkdir(parents=True)
    (package / "__init__.py").write_text("", encoding="utf-8")
    (structures / "__init__.py").write_text("", encoding="utf-8")
    monkeypatch.setattr(generator, "GEN_ICS_DIR", package)
    return structures


def test_validation_imports_in_child_and_leaves_parent_unchanged(generated_package):
    marker = generated_package / "import-pid.txt"
    (generated_package / "sample.py").write_text(
        "import os\nfrom pathlib import Path\n"
        f"Path({str(marker)!r}).write_text(str(os.getpid()))\n",
        encoding="utf-8",
    )
    original_path = sys.path[:]
    original_modules = {k: v for k, v in sys.modules.items() if k == "ics" or k.startswith("ics.")}

    generator.validate_generated_modules(["sample.py"])

    assert int(marker.read_text()) != os.getpid()
    assert sys.path == original_path
    assert {k: v for k, v in sys.modules.items() if k == "ics" or k.startswith("ics.")} == original_modules


@pytest.mark.parametrize("source", ["raise RuntimeError('invalid structure')\n", "invalid syntax !\n", None])
def test_validation_propagates_import_errors(generated_package, source):
    if source is not None:
        (generated_package / "broken.py").write_text(source, encoding="utf-8")

    with pytest.raises(subprocess.CalledProcessError):
        generator.validate_generated_modules(["broken.py"])


def test_validation_reads_regenerated_modules(generated_package):
    module = generated_package / "sample.py"
    module.write_text("value = 1\n", encoding="utf-8")
    generator.validate_generated_modules(["sample.py"])
    module.write_text("raise RuntimeError('regenerated invalid structure')\n", encoding="utf-8")

    with pytest.raises(subprocess.CalledProcessError):
        generator.validate_generated_modules(["sample.py"])


def test_build_version_is_read_without_importing_package(generated_package):
    from setuptools.config.expand import read_attr
    from setuptools.config.pyprojecttoml import load_file

    package = generated_package.parent
    (package / "__init__.py").write_text("raise RuntimeError('package must not be imported')\n")
    (package / "__version.py").write_text('__version__ = "1.2.3"\n')
    config = load_file(Path(__file__).resolve().parents[1] / "pyproject.toml")
    version_attr = config["tool"]["setuptools"]["dynamic"]["version"]["attr"]

    assert read_attr(version_attr, package_dir={"ics": str(package)}) == "1.2.3"
