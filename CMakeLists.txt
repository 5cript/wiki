# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(wiki-client)

# Add files
file(GLOB sources "rest/*.cpp")

# Link a libraries statically
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Add include directory
include_directories(AFTER "../")

option(X64 "64bit build?" ON)

# Add linker directory
if (${X64} EQUAL OFF)
	link_directories("../SimpleJSON/build32")
else()
	link_directories("../SimpleJSON/build")
endif()

# Find Boost
set (Boost_USE_MULTITHREADED 	ON)
find_package(Boost 1.50.0 REQUIRED COMPONENTS system)

if (!Boost_FOUND)
	message(FATAL_ERROR "Boost was not found!")
endif()

#######################################################################
# Add library (shared)
add_library(wiki-client-shared SHARED ${sources})

if (NOT ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"))
	set_target_properties(wiki-client-shared PROPERTIES OUTPUT wiki-client)
endif()

# Compiler Options wiki-client-shared
target_compile_options(wiki-client-shared PRIVATE -fexceptions -std=c++14 -O2 -Wall -pedantic-errors -pedantic)
target_compile_definitions(wiki-client-shared PRIVATE BUILD_DLL)

# Linker Options
target_link_libraries(
	wiki-client-shared 
	PRIVATE 
	ws2_32 
	ssl 
	crypto 
	boost_system-mt
	SimpleJSON
)
#######################################################################

#######################################################################
# Add library
add_library(wiki-client STATIC ${sources})

# Compiler Options wiki-client-shared
target_compile_options(wiki-client PRIVATE -fexceptions -std=c++14 -O2 -Wall -pedantic-errors -pedantic)

# Linker Options
target_link_libraries(
	wiki-client 
	PRIVATE 
	ws2_32 
	ssl 
	crypto 
	boost_system-mt
	SimpleJSON
)
#######################################################################
