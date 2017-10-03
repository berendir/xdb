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

#ifndef XDB_TABLE_BASE_H
#define XDB_TABLE_BASE_H

#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "record_base.h"


namespace xdb {

class const_iterator;

class table_base {

    friend class const_iterator;

public:
    table_base(const std::string &file_name);

    virtual ~table_base();

    virtual void open() = 0;

    virtual void close();

    inline bool is_open() const { return m_stm.is_open(); }

    virtual int size() const = 0;

    virtual record_base * at(int index) = 0;

    const_iterator & begin();

    const_iterator & end();

protected:
    virtual int record_size() const = 0;

    virtual uint32_t record_start() const = 0;

    virtual record_base * create_record() const = 0;

    void update_end_const_iterator_cache();

    const std::string m_file_name;
    std::fstream m_stm;
    std::unique_ptr<const_iterator> m_begin_const_iterator_cache;
    std::unique_ptr<const_iterator> m_end_const_iterator_cache;
};

}

#endif // XDB_TABLE_BASE_H
