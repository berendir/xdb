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

#ifndef XDB_DB3_TABLE_H
#define XDB_DB3_TABLE_H

#include <vector>
#include <memory>

#include "table_base.h"
#include "db3_structures.h"
#include "db3_record.h"


namespace xdb {

class db3_table : public table_base
{
public:
    db3_table(const std::string &file_name);

    void open();

    int size() const;

    record_base * at(int index);

protected:
    int record_size() const;

    uint32_t record_start() const;

    record_base * create_record() const;

    db3_header m_header;
    std::shared_ptr<std::vector<db3_field_descriptor>> m_field_descriptors;
    uint32_t m_records_start;
    std::unique_ptr<db3_record> m_record;
    int m_last_index;
    std::vector<char> m_single_record_data;
    const int m_header_size;
    int m_field_descriptor_size;
};

}

#endif // XDB_DB3_TABLE_H
