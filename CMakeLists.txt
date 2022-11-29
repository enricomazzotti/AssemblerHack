cmake_minimum_required(VERSION 3.23)
project(Assemblatore C)

set(CMAKE_C_STANDARD 99)

add_executable(Assemblatore main.c parser.c parser.h symbletable.c symbletable.h core.c core.h)
