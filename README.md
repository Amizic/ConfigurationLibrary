# ConfigurationLibrary
Configuration library made for reading config.cfg file values, and storing them in memory.

#Static build
`cmake -B build_static -G "MinGW Makefiles"`
`cmake --build build_static`

#Dynamic build
-`cmake -B build_shared -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON`
-`cmake --build build_shared`

#test static library
-`g++ -std=c++11 tests/test_config.cpp -Iinclude -Lbuild_static -lconfig -o tests/test_config.exe`

#test dynamic library
-`g++ -std=c++11 tests/test_config.cpp -Iinclude -DCONFIGLIB_DYNAMIC -Lbuild_shared -lconfig -o tests/test_config_dynamic.exe`
