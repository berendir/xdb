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

#ifndef XDB_DB3_FIELD_H
#define XDB_DB3_FIELD_H

#include <memory>
#include "field_base.h"
#include "db3_structures.h"


namespace xdb {

union db3_field_data {
    std::string *string;
    std::tm *date;
    double number;
    bool boolean;
};

class db3_field : public field_base
{
    friend class db3_record;

public:
    ~db3_field();

    std::string name() const;

    field_type type() const;

    std::string toString() const;

    std::tm toDate() const;

    bool toBool() const;

    double toNumber() const;

protected:
    db3_field(db3_field_descriptor *descriptor);

    db3_field(const db3_field &other);

    db3_field * clone() const { return new db3_field(*this); }

    void set_value(const char *data);

    db3_field_descriptor *m_descriptor;
    db3_field_data m_data;
    const int m_size;
};

}

#endif // XDB_DB3_FIELD_H
