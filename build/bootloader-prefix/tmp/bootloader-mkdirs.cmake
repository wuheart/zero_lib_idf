# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Wu/Desktop/esp-mdf/esp-idf/components/bootloader/subproject"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix/tmp"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix/src"
  "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Wu/Desktop/esp32_lib/zero_lib_idf/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
