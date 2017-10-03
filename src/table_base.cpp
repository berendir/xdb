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
#include "table_base.h"
#include "iterator.h"


using namespace xdb;
using namespace std;


table_base::table_base(const std::string &file_name) :
    m_file_name(file_name)
{

}

table_base::~table_base()
{
    close();
}

void table_base::close()
{
    m_stm.close();
}

const_iterator & table_base::begin()
{
    if (!m_begin_const_iterator_cache)
        m_begin_const_iterator_cache.reset(new const_iterator(this, 0, 1000));

    return *m_begin_const_iterator_cache.get();
}

const_iterator & table_base::end()
{
    if (!m_end_const_iterator_cache)
        update_end_const_iterator_cache();

    return *m_end_const_iterator_cache.get();
}

void table_base::update_end_const_iterator_cache()
{
    m_end_const_iterator_cache.reset(new const_iterator(this, size() - 1, 1));
}

