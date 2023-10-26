cmake_minimum_required(VERSION 3.26)
project(fpsevo C)

set(CMAKE_C_STANDARD 99)

file(COPY resources/. DESTINATION "${CMAKE_BINARY_DIR}")
add_compile_definitions(USE_SDL2)
add_executable(fpsevo main.c
        game.h game.c
        utils/mymath.h utils/mymath.c
        dda/player.h dda/player.c
        dda/map.h dda/map.c
        scenes.h
        scenes.c
        ui/label.c
        ui/label.h
        ui/fonts.h
        ui/ui.h
        ui/color.h
)
target_link_libraries(fpsevo SDL2 SDL2_gfx SDL2_ttf m)