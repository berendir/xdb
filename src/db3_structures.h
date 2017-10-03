/*******************************************************************************
** MIT License
**
** Copyright (c) 2017 Berendir Huntinghawk
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to
** deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
** sell copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
*******************************************************************************/

#ifndef XDB_DB3_STRUCTURES_H
#define XDB_DB3_STRUCTURES_H

#include <cstdint>


namespace xdb {

struct db3_header {
    char     version;
    uint8_t  update_year;
    uint8_t  update_month;
    uint8_t  update_day;
    uint32_t record_count;
    uint16_t header_size;
    uint16_t record_size;
    char     reserved[18];
};


struct db3_field_descriptor {
    char    name[11];
    char    type;
    int32_t data_address;
    uint8_t size;
    uint8_t decimal_places;
    char    reserved[14];
};


const char DB3_TYPE_NO_MEMO = 0x03;
const char DB3_TYPE_MEMO    = 0x83;
const char DB3_HEADER_LIMIT = 0x0D;

}

#endif // XDB_DB3_STRUCTURES_H
