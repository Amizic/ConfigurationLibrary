cmake_minimum_required(VERSION 3.14)
project(ConfigurationLibrary VERSION 1.0 LANGUAGES CXX)

# Option to build shared library (default static)
option(BUILD_SHARED_LIBS "Build as shared library (DLL)" OFF)

# Library target
add_library(config
    src/ConfigurationHandler.cpp
)

# Public include directory for anyone linking against 'config'
target_include_directories(config PUBLIC include)

# When building shared, define the DLL export macros
if(BUILD_SHARED_LIBS)
    target_compile_definitions(config PRIVATE CONFIGLIB_DYNAMIC CONFIGLIB_BUILD)
    target_compile_definitions(config INTERFACE CONFIGLIB_DYNAMIC)
endif()

# Optional: set C++ standard
target_compile_features(config PUBLIC cxx_std_11)