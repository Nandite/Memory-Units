Memory-Units
===============

[![][license-image]][license] 
![platform-image](https://img.shields.io/badge/platorms-linux64%20%7C%20osx%20%7C%20windows-lightgrey?style=flat-square) 
![language](https://img.shields.io/badge/language-c++-blue.svg?style=flat-square)
![c++](https://img.shields.io/badge/std-c++11-blue.svg?style=flat-square)

[license-image]: https://img.shields.io/badge/license-MIT-green.svg?style=flat-square
[license]: https://github.com/Nandite/PclWalkerViewer/blob/master/LICENSE

This project provides a type named memory_size to represent the size of objects in memory. 
It has been inspired by the [std::chrono](https://en.cppreference.com/w/cpp/chrono) library, 
more specifically by [std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration).



Template Parameters:
* Rep: Represents the type to store the size value (e.g., int, long, double).
* Factor: A std::ratio type representing the size unit (e.g., bytes, kilobytes, megabytes). 
It's a compile-time rational fraction defining the ratio of the size's unit to a byte.

Usage:

The mu::memory_size object can represent memory sizes with different granularities, 
like bytes, kilobytes, megabytes, etc., through its template parameters. Common predefined 
types are available, which are specializations of the mu::memory_size template:

```c++
mu::bytes b(1024); // 1024 bytes
mu::kilobytes kb(5); // 5 kilobytes
mu::megabytes mb(75); // 75 megabytes
mu::gigabytes gb(89); // 89 gigabytes
mu::terabytes tb(4); // 4 terabytes
mu::petabytes pb(977); // 977 petabytes
mu::exabytes eb(7); // 7 exabytes
```
It supports various arithmetic operations like addition, subtraction, multiplication, and division:
```c++
auto total_bytes = b + kb + mb + gb + tb + pb + eb; // Adding all memory sizes together
auto remaining_gb = gb - mb - kb - b; // Subtracting smaller units from gigabytes
auto double_gb = gb * 2; // Doubling the gigabytes
auto five_times_mb = mb * 5; // Multiplying megabytes by 5
auto ratio_gb_to_mb = gb / mb; // How many times megabytes fit into gigabytes
auto half_tb = tb / 2; // Halving the terabytes
```

You can compare durations using relational operators:

```c++
mu::gigabytes compute_filesystem_size(...);
mu::megabytes compute_available_cache_size(...);
mu::megabytes compute_used_memory_in_cache(...);
mu::bytes free_memory(mu::bytes how_much_to_free, ....);
// --------------------------------------
auto size {computeFileSystemSize()};
if(size > mu::gigabytes(20))
    // ...
   
auto available_size{compute_available_cache_size()};
if(available_size > mu::megabytes(20))
    // There is at least 20MB of non used memory in the cache
  
auto used{compute_used_memory_in_cache(...)};  
auto freed{free_memory(used, ...)};
if(freed == used)
    // All memory has been reclaimed
```

Type conversion between different units (e.g., megabytes to bytes) is also supported and automatically handled by the type's 
implicit conversion mechanism.
```c++
std::vector<...> find_all_files_with_size_gt(mu::bytes threshold);
void delete_file_if_size_gt(... file, mu::bytes threshold);
// ...
// --------------------------------------

std::gigabytes max_size{10}; // 10GB
std::kilobytes delete_threshold{512};

auto files {find_all_files_with_size_gt(max_size)};
for(const auto & f : files)
    delete_file_if_size_gt(f, delete_threshold); 
```

A method for casting from one memory unit type to another is provided within the
namespace. This functionality enables explicit conversion between different units,
such as converting from bytes to kilobytes or gigabytes to megabytes, ensuring easy
unit conversion:

```c++
mu::bytes large_number_of_bytes(5000000); // 5,000,000 bytes
//...

// Casting bytes to megabytes
auto size_in_mb{mu::memory_size_cast<mu::megabytes>(large_number_of_bytes)};
std::cout << "5,000,000 bytes is " << size_in_mb.count() << " megabytes." << std::endl;
```
## Base 2 vs Base 10

The megabytes, gigabytes (etc.) are representation of size in the decimal system or Base 10:
```c++
using kb = std::ratio<1000 * b::num>;
using mb = std::ratio<1000 * kb::num>;
using gb = std::ratio<1000 * mb::num>;
using tb = std::ratio<1000 * gb::num>;
using pb = std::ratio<1000 * tb::num>;
using eb = std::ratio<1000 * pb::num>;

using kilobytes = memory_size<..., details::kb>;
using megabytes = memory_size<..., details::mb>;
using gigabytes = memory_size<..., details::gb>;
using terabytes = memory_size<..., details::tb>;
using petabytes = memory_size<..., details::pb>;
using exabytes = memory_size<..., details::eb>;
```
In Base 10 (or decimal system), which is one of the main standards for measuring memory-related quantities, every unit is related 
by a factor of 1000

However, an alternative system is the binary system, or Base 2. In this system, units are related by a factor 
of 1024. This reflects the binary nature of computing, where data is processed in powers of 2. The namespace 
provides types for both these measurement systems:

```c++
using kib = std::ratio<1024 * b::num>;
using mib = std::ratio<1024 * kib::num>;
using gib = std::ratio<1024 * mib::num>;
using tib = std::ratio<1024 * gib::num>;
using pib = std::ratio<1024 * tib::num>;
using eib = std::ratio<1024 * pib::num>;

using kibibytes = memory_size<..., details::kib>;
using mebibytes = memory_size<..., details::mib>;
using gibibytes = memory_size<..., details::gib>;
using tebibytes = memory_size<..., details::tib>;
using pebibytes = memory_size<..., details::pib>;
using exbibytes = memory_size<..., details::eib>;
```
The floating-point backed memory_size types are as usable as the Base 10 types in the provided usage examples.

## Floating types

Floating-point representation types for the memory_size are also supported in the implementation. These are
particularly useful in scenarios where precise memory amounts are needed, without the rounding that occurs 
with integer types. Floating-point backed memory_size types ensure accuracy across conversions between different 
units, maintaining the exactness of memory quantities even in fractional values:

```c++
using f_kilobytes = memory_size< /* floating type rep*/, details::kb>;
using f_megabytes = memory_size</* floating type rep*/, details::mb>;
using f_gigabytes = memory_size</* floating typerep*/, details::gb>;
using f_terrabytes = memory_size</* floating type rep*/, details::tb>;
using f_petabytes = memory_size</* floating type rep*/, details::pb>;
using f_exabytes = memory_size</* floating type rep*/, details::eb>;

using f_kibibytes = memory_size</* floating type rep*/, details::kib>;
using f_mebibytes = memory_size</* floating type rep*/, details::mib>;
using f_gibibytes = memory_size</* floating type rep*/, details::gib>;
using f_tebibytes = memory_size</* floating type rep*/, details::tib>;
using f_pebibytes = memory_size</* floating type rep*/, details::pib>;
using f_exbibytes = memory_size</* floating type rep*/, details::eib>;
```

## Literals operators

Literal operators are available for all types from both Base 10 and Base 2 systems, enabling the creation
of memory size constants at compile-time. These operators are part of the mu::literals namespace. Users can
employ these operators to specify memory sizes in their preferred unit:

```c++
// ...
using namespace mu::literals;
// ...

auto size_kb = 256_kB; // 256 kilobytes
auto size_mb = 128_MB; // 128 megabytes
auto size_gb = 2_GB;   // 2 gigabytes
auto size_tb = 1_TB;   // 1 terabyte
auto size_pb = 3_PB;   // 3 petabytes
auto size_eb = 5_EB;   // 5 exabytes

auto size_kib = 256_kiB; // 256 kibibytes
auto size_mib = 128_MiB; // 128 mebibytes
auto size_gib = 2_GiB;   // 2 gibibytes
auto size_tib = 1_TiB;   // 1 tebibyte
auto size_pib = 3_PiB;   // 3 petbibytes
auto size_eib = 5_EiB;   // 5 exbibytes

if (size_gb < 5_GB) 
    // ...

if (2_TiB >= size_kib)
    // ...

//...
```

## Dependencies

The implementation is self-contained and needs only standard language support through a compiler supporting at 
least **[C++11](https://en.cppreference.com/w/cpp/compiler_support)**.

To run the test suite, [Google Test (GTest)](https://github.com/google/googletest) is required.

## Installation

Just copy the [header file](include/memory_units.hpp) or its content into your project.

## Feedback

Don't hesitate if you have any suggestions for improving this project, or if you find any error. I will be glad to
hear from you. Contributions are welcomed :)

## License

Distributed under the MIT Software License (X11 license).
See the accompanying [LICENSE](LICENSE) file.