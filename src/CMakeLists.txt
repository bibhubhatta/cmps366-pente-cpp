cmake_minimum_required(VERSION 3.25.2)
project(pente_src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
        GIT_TAG master
)
FetchContent_MakeAvailable(tabulate)

add_library(
        pente_lib STATIC
        Serial.cpp Serial.h
        Board.cpp Board.h
        Position.cpp Position.h
        Roster.cpp Roster.h
        Player.h
        Human.cpp Human.h
        Computer.cpp Computer.h
        Exceptions.h
        BoardDisplay.cpp BoardDisplay.h
        MoveAnalysis.cpp MoveAnalysis.h
        Tournament.cpp Tournament.h
        Round.cpp Round.h
        TournamentAnnouncement.cpp TournamentAnnouncement.h
        helpers.cpp helpers.h
        RoundDisplay.cpp RoundDisplay.h
        UnicodeDisplayHelpers.cpp UnicodeDisplayHelpers.h
        Strategy.cpp Strategy.h
)

target_link_libraries(pente_lib
        PUBLIC fmt::fmt
        PUBLIC tabulate::tabulate
)


target_include_directories(pente_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(pente main.cpp)
target_link_libraries(pente pente_lib)