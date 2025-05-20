set(SRC_FILES
        main.cpp
        shell.cpp
        ../include/utility.h
        utility.cpp
        run_shell.cpp
        ../include/run_shell.h
)

add_executable(minishell ${SRC_FILES})

target_include_directories(minishell PRIVATE ${PROJECT_SOURCE_DIR}/include)
