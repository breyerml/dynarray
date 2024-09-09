# cpp_util::dynarray

[![Test with GCC, Clang and MSVC](https://github.com/breyerml/dynarray/actions/workflows/compiler_test.yml/badge.svg)](https://github.com/breyerml/dynarray/actions/workflows/compiler_test.yml) &ensp;
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/4f9e7aed05774d538c7fa6f99f81c26f)](https://app.codacy.com/gh/breyerml/dynarray/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade) &ensp;
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Implementation of a runtime fixed-size array (loosely based on [N3662](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3662)).

In contrast to `std::array`, the size of a `cpp_util::dynarray` doesn't have to be a compile-time constant. 
Additionally, since a `cpp_util::dynarray` doesn't have to grow at runtime, there is no need to save a capacity resulting in less memory used (e.g. 2 byte vs. 3 byte).

The API is inspired by the `std::array` and `std::vector` API without the member functions modifying its size. Three additional functions
are implemented:

- `cpp_util::dynarray::fill(const value_type& value = value_type{})`
- `cpp_util::dynarray::iota(const value_type& value = value_type{})`
- `cpp_util::dynarray::generate(const value_type& value = value_type{})`

## Prerequisites

Any compiler supporting `C++11` should be sufficient (for more information see [Compiler Support](#compiler-support)). 
Additionally, at least [CMake](https://cmake.org/) `3.30` is required.

The tests are implemented using [Catch2](https://github.com/catchorg/Catch2/tree/v2.x), which gets shipped as single header file with this repository.

## Building and Running the Examples

Building with GCC, Clang, or MSVC can be done using CMake presets.

```bash
git clone git@github.com:breyerml/dynarray.git
cd dynarray
cmake --preset [preset] .
cmake --build --preset [preset]
./build/dynarray
```

Where `[preset]` is one of `gcc`, `clang`, or `msvc`.

## Building and Running the Tests

To additionally build the tests and run them use:

```bash
cmake --preset [preset] -DCPP_UTIL_ENABLE_TESTS .
cmake --build --preset [preset]
ctest --preset [preset]
```

Tests for all supported `C++` standards starting with `C++11` for the currently used compiler are generated.

## Compiler Support

The `cpp_util::dynarray` has been tested with the following compilers, all installed using the respective package
manager and GitHub actions (other compilers or compiler versions may also be supported):

| Compiler | Versions                               |
|----------|----------------------------------------|
| GCC      | 9.5.0, 10.5.0, 11.4.0, 12.3.0          |
| Clang    | 11.1.0, 12.0.1, 13.0.1, 14.0.0, 15.0.7 |
| MSVC     | 19.29.30154.0                          |

All tests were run using the following compiler flags:

- GCC: `-Wall -Wextra -Wpedantic -Werror`
  
- Clang: `-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unknown-warning-option -Wno-zero-as-null-pointer-constant -Wno-c++1z-extensions -Wno-self-assign-overloaded -Wno-self-move -Wno-reserved-identifier -Werror`
  - `-Wno-c++98-compat -Wno-c++98-compat-pedantic`: since `C++98` is not supported
  - `-Wno-unknown-warning-option`: due to `clang-11.1.0` and `clang-12.0.1` not recognizing the `Wno-reserved-identifier` option
  - `-Wno-zero-as-null-pointer-constant`: due to a warning generated by `clang-11.1.0` when compiling the Catch2 header
  - `-Wno-c++1z-extensions`: due to a warning in `clang` when using `[[nodiscard]]` prior to `C++17` (although the corresponding feature test macro is defined)
  - `-Wno-self-assign-overloaded -Wno-self-move`: due to a warning generated by the tests which use self-assignment to increase test coverage
  - `-Wno-reserved-identifier`: due to a warning generated by `clang-13.0.1` when compiling the Catch2 header

- MSVC:  `/W4 /EHsc /WX`

## Compiler Standard Version

- `C++11`:
  - the minimum required standard version enabling all functions

- `C++14`:
  - the functions `exchange(T&, U&&)` and `make_reverse_iterator(Iter)` are now implemented using the `std::` versions
  - `operator==(const dynarray&, const dynarray&)` is now implemented using `std::equal(InputIt1, InputIt1, InputIt2, InputIt2)`

- `C++17`:
  - almost all functions are now marked as `[[nodiscard]]`
  - added a deduction guide for the iterator range constructor `dynarray(ForwardIt, ForwardIt)`

- `C++20`:
  - all functions are now marked as `constexpr`
  - the relational operators are now implemented in terms of the three-way comparison operator `operator<=>(const dynarray&, const dynarray&)`

The actual features are enabled using the specific features test macros and not the `__cplusplus` macro.