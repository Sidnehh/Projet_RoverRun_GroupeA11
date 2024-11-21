cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled1 main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        tree.h
        tree.c
        queue.h
        queue.c
        stack.c
        stack.h
        "test gpt.c"
        node.c
        node.h)
