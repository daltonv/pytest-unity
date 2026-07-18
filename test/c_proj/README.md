# pytest-unity example fixture

This test project contains:

- A small static C library named `example`
- Two library modules:
  - `math_utils`
  - `ring_buffer`
- Three Unity test source files

## Test files

- `tests/test_math_utils.c`
- `tests/test_clamp.c`
- `tests/test_ring_buffer.c`

## Build

```sh
cmake -S . -B build
cmake --build build
```

This produces the static library and all test exes.

## Unity integration

Pass the root of a cloned ThrowTheSwitch/Unity repository:

```sh
cmake -S . -B build
```
