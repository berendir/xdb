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
#include "db3_field.h"
#include "errors.h"

using namespace xdb;
using namespace std;


db3_field::db3_field(db3_field_descriptor *descriptor) :
    m_descriptor(descriptor),
    m_size(descriptor->size)
{
    switch (m_descriptor->type) {

        case string:
            m_data.string = new std::string();
            break;

        case date:
            m_data.date = new tm();
            break;

        default:
            break;
    }
}

db3_field::db3_field(const db3_field &other) :
    m_descriptor(other.m_descriptor),
    m_data(),
    m_size(other.m_size)
{
    switch (m_descriptor->type) {

        case string:
            m_data.string = new std::string(*other.m_data.string);
            break;

        case date:
            m_data.date = new tm(*other.m_data.date);
            break;

        default:
            m_data = other.m_data;
            break;
    }
}


db3_field::~db3_field()
{
    switch (m_descriptor->type) {

        case string:
            delete m_data.string;
            break;

        case date:
            delete m_data.date;
            break;

        default:
            break;
    }
}

std::string db3_field::name() const
{
    return m_descriptor ? std::string(m_descriptor->name) : "";
}

field_type db3_field::type() const
{
    return m_descriptor ? (field_type) m_descriptor->type : unknown;
}

std::string db3_field::toString() const
{
    return *m_data.string;
}

tm db3_field::toDate() const
{
    return *m_data.date;
}

bool db3_field::toBool() const
{
    return m_data.boolean;
}

double db3_field::toNumber() const
{
    return m_data.number;
}

void db3_field::set_value(const char *data)
{
    switch (m_descriptor->type) {

        case string:
            *m_data.string = std::string(data, m_size);
            break;

        case date:
            m_data.date->tm_year = atoi(std::string(data, 4).c_str());
            m_data.date->tm_mon = atoi(std::string(&data[4], 2).c_str());
            m_data.date->tm_mday = atoi(std::string(&data[6], 2).c_str());
            break;

        case boolean:
            if (data[0] == '0' || data[0] == 'F' || data[0] == 'N')
                m_data.boolean = false;
            else
                m_data.boolean = true;
            break;

        case number:
            m_data.number = atof(std::string(data, m_size).c_str());
            break;

        default:
            XDB_VALIDATION_ERROR("XDB0015", "Invalid field type");
    }
}
