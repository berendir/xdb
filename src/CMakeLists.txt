cmake_minimum_required ( VERSION 3.5 )

project ( xdb )


set ( PUBLIC_HEADERS
    "errors.h"
    "definitions.h"
    "db3_entry_base.h"
    "field_base.h"
    "record_base.h"
    "table_base.h"
)

set ( PRIVATE_HEADERS
    "db3_structures.h"
    "db3_table.h"
    "utils.h"
)

set ( SOURCES
    "main.cpp"
    "errors.cpp"
    "db3_table.cpp"
    "utils.cpp"
)

add_executable ( ${PROJECT_NAME} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES} )
