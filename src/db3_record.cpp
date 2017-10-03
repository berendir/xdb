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
#include "db3_record.h"
#include "db3_field.h"
#include "errors.h"

using namespace xdb;
using namespace std;

db3_record::db3_record(std::shared_ptr<std::vector<db3_field_descriptor>> descriptors) :
    record_base(),
    m_descriptors(descriptors),
    m_field_count(m_descriptors->size())
{
    m_fields.resize(descriptors->size());

    m_field_indexes = make_shared<std::unordered_map<std::string,int>>();

    for (int i = 0; i < m_descriptors->size(); ++i) {
        m_fields[i].reset(new db3_field(&m_descriptors->at(i)));
        (*m_field_indexes)[m_fields[i]->name()] = i;
    }
}

db3_record::db3_record(const db3_record &other) :
    record_base(),
    m_descriptors(other.m_descriptors),
    m_fields(other.m_fields.size()),
    m_field_indexes(other.m_field_indexes),
    m_field_count(m_descriptors->size())
{
    for (int i = 0; i < m_descriptors->size(); ++i)
        m_fields[i].reset(other.m_fields[i]->clone());
}

db3_record::~db3_record()
{

}

field_base * db3_record::field(int index) const
{
    if (index < 0 || index >= m_fields.size())
        XDB_THROW_EXCEPTION("XDBXXXX", "Field index out of range");

    return m_fields[index].get();
}

field_base * db3_record::field(const std::string &name) const
{
    int index = -1;

    try {
        index = m_field_indexes->at(name);
    }

    catch (out_of_range) { }

    if (index == -1)
        XDB_VALIDATION_ERROR("XDB0014", "Field with name\"" + name + "\" does not exist");

    return field(index);
}

void db3_record::set_value(const char *data)
{
    for (int i = 0, offset = 1; i < m_field_count; ++i, offset += (*m_descriptors)[i].size)
        m_fields[i]->set_value(&data[offset]);
}
