add_executable(C-Templates-Test
        main.c
        list_test.h
        list_test.c
        vector_test.c
        vector_test.h
        )

target_include_directories(C-Templates-Test PRIVATE "../includes")