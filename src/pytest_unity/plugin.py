import pathlib

import pytest


def pytest_collect_file(parent, file_path: pathlib.Path):
    """Collect Unity test files."""
    valid_suffixes = ("", ".exe")
    if file_path.suffix in valid_suffixes and file_path.name.startswith("test_"):
        return UnityFile.from_parent(parent, path=file_path)


class UnityFile(pytest.File):
    """A Unity test file."""

    def collect(self):
        """Collect Unity test cases from the file."""
        # Run the Unity test executable and capture its output
        yield UnityTestCase.from_parent(self, name=self.path.stem)


class UnityTestCase(pytest.Item):
    """A single Unity test case."""

    def runtest(self):
        """Run the Unity test case."""
        import subprocess

        # Execute the Unity test executable and capture its output
        result = subprocess.run([self.path], capture_output=True, text=True)
        if result.returncode != 0:
            raise UnityTestException(result.stdout, result.stderr)

    def repr_failure(self, excinfo):
        """Called when self.runtest() raises an exception."""
        if isinstance(excinfo.value, UnityTestException):
            exc = excinfo.value
            return exc.stdout + exc.stderr
        return super().repr_failure(excinfo)

    def reportinfo(self):
        """Return information for reporting."""
        return self.path, 0, f"Unity test case: {self.name}"


class UnityTestException(Exception):
    """Custom exception for Unity test failures."""

    def __init__(self, stdout: str, stderr: str):
        self.stdout = stdout
        self.stderr = stderr
