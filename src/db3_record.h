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

#ifndef XDB_DB3_RECORD_H
#define XDB_DB3_RECORD_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "record_base.h"
#include "db3_structures.h"
#include "db3_field.h"


namespace xdb {

class db3_record : public record_base
{
    friend class db3_table;

public:
    ~db3_record();

    virtual field_base * field(int index) const;

    virtual field_base * field(const std::string &name) const;

protected:
    db3_record(std::shared_ptr<std::vector<db3_field_descriptor>> descriptors);

    db3_record(const db3_record &other);

    inline db3_record * clone() const { return new db3_record(*this); }

    void set_value(const char *data);

    std::shared_ptr<std::vector<db3_field_descriptor>> m_descriptors;
    std::vector<std::unique_ptr<db3_field>> m_fields;
    std::shared_ptr<std::unordered_map<std::string,int>> m_field_indexes;
    const int m_field_count;
};

}

#endif // XDB_DB3_RECORD_H
