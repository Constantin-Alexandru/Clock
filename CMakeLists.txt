cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_COMPILER_WORKS TRUE)

project(Clock)

set(CMAKE_CXX_STANDARD 20)

add_executable(Clock main.cpp sfml_analogue.cpp sfml_analogue.h)

include_directories(${CMAKE_CURRENT_LIST_DIR}/sdks/SFML/include)

set(SFML_ROOT sdks/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Clock ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()