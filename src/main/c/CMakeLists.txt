cmake_minimum_required(VERSION 3.4.1)

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../jniLibs)

add_library(lib_cardano_funcs STATIC IMPORTED)

set_target_properties(lib_cardano_funcs PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/${ANDROID_ABI}/libcardano_funcs.a)

# build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(load-libs SHARED
            load-libs.c)

target_include_directories(load-libs PRIVATE
                           ${distribution_DIR}/include)

target_link_libraries(load-libs
                      android
                      lib_cardano_funcs
                      log)
