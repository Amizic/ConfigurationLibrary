# Configuration Library
Configuration library made in C++, for reading configuration file key-value pairs, and storing them in memory.

## Building the Library
### Static Build
`cmake -B build_static -G "MinGW Makefiles"`
`cmake --build build_static`

### Dynamic Build
-`cmake -B build_shared -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON`
-`cmake --build build_shared`

## Building Tests
### Static Library Test
-`g++ -std=c++17 tests/test_config.cpp -Iinclude -Lbuild_static -lconfig -o tests/test_config.exe`

### Dynamic Library Test
-`g++ -std=c++17 tests/test_config.cpp -Iinclude -DCONFIGLIB_DYNAMIC -Lbuild_shared -lconfig -o tests/test_config_dynamic.exe`
