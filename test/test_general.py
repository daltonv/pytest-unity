def test_passing_test_case(build_c_proj, pytester):
    """Test that a passing Unity test case is collected and executed."""
    # Run pytest on the built Unity test executable
    result = pytester.runpytest("build/test_clamp")

    # Check that the test passed
    result.assert_outcomes(passed=1)


def test_failing_test_case(build_c_proj, pytester):
    """Test that a failing Unity test case is collected and executed."""
    # Run pytest on the built Unity test executable
    result = pytester.runpytest("build/test_math_utils")

    # Check that the test failed
    result.assert_outcomes(failed=1)
