cmake_minimum_required(VERSION 3.18.1)

project("qqvoicechange")

set(libs_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)

add_library(fmod
        SHARED
        IMPORTED)

set_target_properties(fmod
        PROPERTIES
        IMPORTED_LOCATION ${libs_DIR}/${ANDROID_ABI}/libfmod.so
        )

add_library(fmodL
        SHARED
        IMPORTED)

set_target_properties(fmodL
        PROPERTIES
        IMPORTED_LOCATION ${libs_DIR}/${ANDROID_ABI}/libfmodL.so
        )


add_library(
        qqvoicechange
        SHARED
        native-lib.cpp)

#头文件
target_include_directories(qqvoicechange PRIVATE ./inc/)

target_link_libraries(
        qqvoicechange
        fmod
        fmodL
        log)