cmake_minimum_required(VERSION 3.22)
project(tp_aeds2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(estruturas/invIndex)
include_directories(estruturas/patricia)

add_executable(tp_aeds2
        estruturas/invIndex/invIndex.c
        estruturas/invIndex/invIndex.h
        estruturas/patricia/patricia.c
        estruturas/patricia/patricia.h
        hash.c
        hash.h
        main.c
        separacaoString.c)
