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

#ifndef XDB_ITERATOR_H
#define XDB_ITERATOR_H


#include <iterator>
#include <vector>
#include <memory>

#include "table_base.h"
#include "record_base.h"


namespace xdb {

class const_iterator : public std::iterator<std::input_iterator_tag, record_base>
{
public:
    const_iterator(table_base *table, int starting_index, int buffer_size);

    const_iterator(const const_iterator& mit);

    const_iterator& operator++();

    bool operator==(const const_iterator& rhs) const;

    inline bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

    const record_base * operator->() const;

protected:
    table_base *m_table;
    std::vector<char> m_buffer;
    int m_index;
    std::unique_ptr<record_base> m_record;
    int m_buffer_offset;
};

}

#endif // XDB_ITERATOR_H
