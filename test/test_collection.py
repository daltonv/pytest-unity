import shutil


def test_standard_collection(build_c_proj, pytester):
    """Test that the Unity test files are collected correctly."""
    # Run pytest on the built Unity test executables
    result = pytester.runpytest("build/", "--collect-only")

    # Check that both test files were collected and executed
    result.stdout.fnmatch_lines(["*collected 4 items*"])


def test_name_collection(build_c_proj, pytester):
    """Test that only executables with the 'test_' prefix are collected."""
    # Run pytest on the built Unity test executables
    test_clamp = pytester.path / "build" / "test_clamp"

    shutil.copy(test_clamp, pytester.path / "build" / "clamp_test")

    result = pytester.runpytest("build/", "--collect-only")

    # Check that both test files were collected and executed
    result.stdout.fnmatch_lines(["*collected 4 items*"])
