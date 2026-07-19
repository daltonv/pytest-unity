"""Global fixtures for testing the plugin"""

import shutil
from pathlib import Path

import pytest
from pytest import Pytester

TEST_DIR = Path(__file__).parent

# Make the internal pytester plugin available for testing the plugin
pytest_plugins = ["pytester"]


@pytest.fixture
def copy_c_proj(pytester: Pytester):
    """Copy the C project to the test directory."""
    c_proj_path = TEST_DIR / "c_proj"
    test_files = (
        list(c_proj_path.glob("include/*"))
        + list(c_proj_path.glob("src/*"))
        + list(c_proj_path.glob("tests/*"))
        + list(c_proj_path.glob("CMakeLists.txt"))
    )

    for file in test_files:
        dest = pytester.path / file.relative_to(c_proj_path)
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(file, dest)


@pytest.fixture
def build_c_proj(pytester, copy_c_proj):
    """Build the C project using CMake."""
    unity_path = TEST_DIR.parent / "vendor" / "unity"
    cmd = [
        "cmake",
        "-S",
        ".",
        "-B",
        "build",
        "-G",
        "Ninja",
        f"-DUNITY_ROOT={unity_path}",
    ]
    pytester.run(*cmd)

    cmd = ["cmake", "--build", "build"]
    pytester.run(*cmd)
