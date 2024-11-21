cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

CMAKE_C_STANDARD(99)  # Si tu utilises C99

add_executable(untitled1
        main.c
        loc.c
        moves.c
        map.c
        queue.c
        stack.c
        tree.c)