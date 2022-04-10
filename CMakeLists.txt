cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

#JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp ConverterJSON.cpp ConverterJSON.h InvertedIndex.cpp InvertedIndex.h SearchServer.cpp SearchServer.h)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

#GoogleTest
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL
#        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#set(gtest_disable_pthreads on)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#enable_testing()
#target_link_libraries(search_engine PRIVATE gtest_main)
#include(GoogleTest)
#gtest_discover_tests(search_engine)

#BOOST
#set (Boost_USE_STATIC_LIBS OFF)
#set(Boost_INCLUDE_DIR "F:\\public\\alx\\skilbox_project\\boost_1_71_0")
#set(Boost_LIBRARY_DIR "F:\\public\\alx\\skilbox_project\\boost_1_71_0\\stage\\lib")
#find_package(Boost COMPONENTS REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})
#target_link_libraries(search_engine ${Boost_LIBRARIES})