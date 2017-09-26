/*******************************************************************************
** MIT License
**
** Copyright (c) 2017 Berendir Huntinghawk
**
** This file is part of the xdb project.
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

typedef struct {
    char    version;
    uint8_t update_year;
    uint8_t update_month;
    uint8_t update_day;
    int32_t record_day;
    int16_t header_size;
    int16_t record_size;
    char    reserved[18];

} db3_header;


typedef struct {
    char    name[11];
    char    type;
    int32_t data_address;
    uint8_t length;
    uint8_t decimal_places;
    char    reserved[14];

} db3_field_descriptor;


enum db3_data_types {
    string  = 'C',
    date    = 'D',
    boolean = 'L',
    number  = 'N',
    memo    = 'M'
};

const int DB3_TYPE_NO_MEMO = 0x03;
const int DB3_TYPE_MEMO    = 0x83;

}

#endif // XDB_DB3_STRUCTURES_H
