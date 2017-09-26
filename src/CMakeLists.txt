cmake_minimum_required ( VERSION 3.5 )

project ( xdb )

set (HEADERS
    "errors.h"
    "db3_structures.h"
)

set ( SOURCES
    "main.cpp"
    "errors.cpp"
)

add_executable ( ${PROJECT_NAME} ${HEADERS} ${SOURCES} )
