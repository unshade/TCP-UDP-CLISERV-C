cmake_minimum_required(VERSION 3.27)
project(cliserv C)

set(CMAKE_C_STANDARD 11)

add_executable(cliserv main.c
        clientTCP.c)
