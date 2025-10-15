cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- PDCurses ---
set(PDCURSES_DIR "C:/Users/Thomas/Desktop/PDCurses") # Use forward slashes
include_directories(${PDCURSES_DIR})

# Gather PDCurses source files
file(GLOB PDCURSES_SOURCES
    "${PDCURSES_DIR}/pdcurses/*.c"
    "${PDCURSES_DIR}/wincon/*.c"
)
# --- End PDCurses ---

# Add source directory for our game
include_directories(src)

# Gather all of our game's source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable with all sources
add_executable(snake_game ${SOURCES} ${PDCURSES_SOURCES})

# Add necessary libraries for Windows
if(WIN32)
    target_link_libraries(snake_game kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 ole32 oleaut32 uuid)
endif()