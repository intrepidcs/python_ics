"""Build orchestration checks without downloads, compilers, or hardware."""

import importlib.util
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest import mock


class TestLinuxBuild(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        # Model an unpacked source archive: the build script has no parent .git.
        script = self.root / "build_libicsneo.py"
        shutil.copyfile(Path(__file__).resolve().parents[1] / script.name, script)
        previous = Path.cwd()
        os.chdir(self.root)
        self.addCleanup(os.chdir, previous)
        spec = importlib.util.spec_from_file_location("archive_build", script)
        self.module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.module)
        self.build = Path(self.module.LIBICSNEO_BUILD)
        self.source = Path(self.module.LIBICSNEO_SOURCE)
        self.source.mkdir(parents=True)
        subprocess.run(["git", "init", "--quiet", str(self.source)], check=True)
        self.real_check_output = subprocess.check_output

    def run_build(self, stale=None):
        commands = []

        def command(args, **kwargs):
            if args[0] != "cmake":
                return self.real_check_output(args, **kwargs)
            self.assertTrue(self.build.is_dir())
            if stale is not None:
                self.assertFalse(stale.exists())
            commands.append(args)
            return b""

        with mock.patch.object(self.module.subprocess, "check_output", side_effect=command):
            self.module._build_libicsneo_linux()
        self.assertEqual(len(commands), 2)
        self.assertEqual(Path(commands[0][commands[0].index("-S") + 1]), self.source)
        self.assertEqual(commands[0][commands[0].index("-B") + 1], self.module.LIBICSNEO_BUILD)
        self.assertEqual(commands[1][1:3], ["--build", self.module.LIBICSNEO_BUILD])
        self.assertFalse((self.root / "libicsneo" / "build").exists())

    def test_fresh_archive_build(self):
        self.run_build()

    def test_rebuild_cleans_only_build_directory(self):
        self.build.mkdir()
        stale = self.build / "CMakeCache.txt"
        stale.write_text("stale build environment")
        preserved = [
            self.source / "untracked-source.txt",
            Path(self.module.LIBICSNEO_INSTALL) / "installed.txt",
            Path(self.module.ICSPB_BOOTSTRAP_DIR) / "protobuf.txt",
            self.root / "libicsneo" / "other-version" / "keep.txt",
        ]
        for path in preserved:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("keep")
        self.run_build(stale)
        for path in preserved:
            self.assertEqual(path.read_text(), "keep")
        self.assertTrue((self.source / ".git").is_dir())

    def test_cleanup_failure_stops_before_cmake(self):
        self.build.mkdir()
        with mock.patch.object(self.module.shutil, "rmtree", side_effect=PermissionError("busy")):
            with mock.patch.object(self.module.subprocess, "check_output") as command:
                with self.assertRaises(PermissionError):
                    self.module._build_libicsneo_linux()
                command.assert_not_called()
