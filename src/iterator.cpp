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
#include "iterator.h"
#include "errors.h"
#include "utils.h"


using namespace xdb;
using namespace std;

const_iterator::const_iterator(table_base *table, int starting_index, int buffer_size) :
    m_table(table),
    m_index(starting_index),
    m_buffer_offset(0)
{
    if (!m_table->is_open())
        XDB_IO_ERROR("XDB0009", "Table is not open");

    if (m_index < 0 || m_index >= m_table->size())
        XDB_OUT_OF_RANGE_ERROR("XDB00010", "Index out of range");

    if (buffer_size == -1)
        buffer_size = m_table->size();

    else if (buffer_size > 0)
        buffer_size = min(buffer_size, m_table->size());

    else
        XDB_VALIDATION_ERROR("XDB0011", "Invalid buffer size");

    m_buffer.resize(m_table->record_size() * buffer_size);

    // TODO: pay attention to file end.
    m_table->m_stm.seekg(m_table->record_start(), fstream::beg);
    m_table->m_stm.read(m_buffer.data(), m_buffer.size());

    m_record.reset(m_table->create_record());
    m_record->set_value(&m_buffer[m_buffer_offset], m_table->record_size());
    m_buffer_offset += m_table->record_size();
}

const_iterator::const_iterator(const const_iterator &mit)
{

}

const_iterator &const_iterator::operator++()
{
    ++m_index;

    if (m_index >= m_table->size())
        XDB_OUT_OF_RANGE_ERROR("XDB0012", "Index out of range");

    if (m_buffer_offset + m_table->record_size() >= m_buffer.size()) {
        m_table->m_stm.seekg(m_table->record_start() + m_index * m_table->record_size(), fstream::beg);
        m_table->m_stm.read(m_buffer.data(), m_buffer.size());
        m_buffer_offset = 0;
    }

    m_record->set_value(&m_buffer[m_buffer_offset]);
    m_buffer_offset += m_table->record_size();
}

bool const_iterator::operator==(const const_iterator &rhs) const
{
    return m_table->m_file_name == rhs.m_table->m_file_name && m_index == rhs.m_index;
}

const record_base * const_iterator::operator->() const
{
    return m_record.get();
}
