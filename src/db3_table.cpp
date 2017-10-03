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

#include <iostream>

#include "db3_table.h"
#include "errors.h"
#include "utils.h"

using namespace xdb;
using namespace std;


db3_table::db3_table(const std::string &file_name) :
    table_base(file_name),
    m_last_index(-1),
    m_header_size(sizeof(db3_header)),
    m_field_descriptor_size(sizeof(db3_field_descriptor))
{
    m_stm.open(m_file_name);

    if (!is_open())
        XDB_IO_ERROR("XDB0003", "Impossible to open file");

    m_stm.read((char*) &m_header, sizeof(m_header));

    if (m_header.version != DB3_TYPE_MEMO && m_header.version != DB3_TYPE_NO_MEMO)
        XDB_THROW_EXCEPTION("XDB0004", "Unsupported file type");

    m_stm.close();
}

void db3_table::open()
{
    m_stm.open(m_file_name);

    if (!is_open())
        XDB_IO_ERROR("XDB0005", "Impossible to open file");

    const int HEADER_SIZE = sizeof(db3_header);
    const int FIELD_DESCRIPTOR_SIZE = sizeof(db3_field_descriptor);

    int64_t calculated_file_size = m_header.header_size;
    calculated_file_size += m_header.record_size * m_header.record_count;
    calculated_file_size += 1;

    if (file_size(m_file_name) != calculated_file_size)
        XDB_VALIDATION_ERROR("XDB0006", "File size verification failed");

    int field_count = (m_header.header_size - HEADER_SIZE) / FIELD_DESCRIPTOR_SIZE;

    m_field_descriptors = make_shared<vector<db3_field_descriptor>>(field_count);

    m_stm.seekg(HEADER_SIZE, ios_base::beg);
    m_stm.read((char*) m_field_descriptors->data(), FIELD_DESCRIPTOR_SIZE * field_count);

    if (m_stm.get() != DB3_HEADER_LIMIT)
        XDB_VALIDATION_ERROR("XDB0007", "Field descriptors delimiter not found");

    m_records_start = m_stm.tellp();

    m_record.reset(new db3_record(m_field_descriptors));
    m_single_record_data.resize(m_header.record_size);
}

int db3_table::size() const
{
    return is_open() ? m_header.record_count : -1;
}

record_base * db3_table::at(int index)
{
    if (index < 0 || index >= m_header.record_count)
        XDB_OUT_OF_RANGE_ERROR("XDB0008", "Index out of range");

    if (index == m_last_index)
        return m_record.get();

    m_stm.seekp(m_records_start + index * m_header.record_size);
    m_stm.read(m_single_record_data.data(), m_single_record_data.size());
    m_record->set_value(m_single_record_data.data(), m_single_record_data.size());

    m_last_index = index;

    return m_record.get();
}

int db3_table::record_size() const
{
    return m_header.record_size;
}

uint32_t db3_table::record_start() const
{
    int field_count = (m_header.header_size - m_header_size) / m_field_descriptor_size;
    return m_header_size + field_count * m_field_descriptor_size + 1;
}

record_base * db3_table::create_record() const
{
    return new db3_record(m_field_descriptors);
}
