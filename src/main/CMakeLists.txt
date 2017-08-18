
include_directories(${MAIN_SOURCE_DIR}/main/include)

include_directories(${MAIN_SOURCE_DIR}/game/include)
link_directories(${MAIN_SOURCE_DIR}/game/source)
set (EXTRA_LIBS ${EXTRA_LIBS} game)

add_executable(Life source/main.cpp)

target_link_libraries(Life ${EXTRA_LIBS})
