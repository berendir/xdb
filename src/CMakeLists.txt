cmake_minimum_required ( VERSION 3.5 )

project ( xdb )

set ( PUBLIC_HEADERS
    "errors.h"
    "definitions.h"
    "db3_entry_base.h"
    "field_base.h"
    "record_base.h"
    "table_base.h"
    "iterator.h"
    "xdb.h"
)

set ( PRIVATE_HEADERS
    "db3_structures.h"
    "db3_table.h"
    "utils.h"
    "db3_record.h"
    "db3_field.h"
)

set ( SOURCES
    "errors.cpp"
    "db3_table.cpp"
    "utils.cpp"
    "iterator.cpp"
    "db3_record.cpp"
    "db3_field.cpp"
    "table_base.cpp"
    "xdb.cpp"
)

add_library ( ${PROJECT_NAME} SHARED ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES} )
