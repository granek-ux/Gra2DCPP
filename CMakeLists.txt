cmake_minimum_required(VERSION 3.28)
project(Gra2DProjekt)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)


add_executable(Gra2DProjekt main.cpp
        FileHandling.cpp
        FileHandling.h
        Entity.cpp
        Entity.h
        Interrupters.cpp
        Interrupters.h
)
target_link_libraries(Gra2DProjekt sfml-graphics fmt)
