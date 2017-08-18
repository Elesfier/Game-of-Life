
include_directories (${MAIN_SOURCE_DIR}/game/include)

add_library (game source/game.cpp)

target_include_directories (game PUBLIC ${MAIN_SOURCE_DIR}/matrix/include)
target_link_libraries (game matrix)
