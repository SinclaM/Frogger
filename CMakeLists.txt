cmake_minimum_required(VERSION 3.3)

set(GAME_EXE Frogger)

project(${GAME_EXE} CXX)
include(.cs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        src/model.cxx
        src/frog.cxx
        src/game_config.cxx
        src/coaster.cxx
        src/clock.cxx
        src/home.cxx)

add_program(${GAME_EXE}
        ${MODEL_SRC}
        src/view.cxx
        src/controller.cxx
        src/main.cxx)
target_link_libraries(${GAME_EXE} ge211)

add_test_program(model_test
        ${MODEL_SRC}
        test/model_test.cxx)
target_link_libraries(model_test ge211)

# vim: ft=cmake
