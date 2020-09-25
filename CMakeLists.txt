cmake_minimum_required(VERSION 3.0)
project(d1extender)

set(CMAKE_CXX_STANDARD 14)

add_executable(pos2mesh pos2mesh.cpp)
add_executable(fun2gfun fun2gfun.cpp)

install(
        TARGETS pos2mesh fun2gfun
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin
)