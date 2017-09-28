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

#include <string.h>
#include <sstream>
#include <iostream>

#include "errors.h"


using namespace xdb;

xdb::exception::exception(const std::string &code, const std::string &message, const std::string &function) :
    m_code(code),
    m_message(message),
    m_function(function)
{
    std::ostringstream what_string;

    what_string << "On function \"" << m_function << "\", ";
    what_string << "exception " << m_code << ": ";
    what_string << m_message;

    m_what = new char[std::char_traits<char>::length(what_string.str().data())];
    strcpy(m_what, what_string.str().data());
}

exception::exception(const exception &other) :
    m_code(other.m_code),
    m_message(other.m_message),
    m_function(other.m_function)
{
    m_what = new char[strlen(other.m_what)];
    strcpy(m_what, other.m_what);
}

exception::~exception()
{
    delete m_what;
}

const char * exception::what() const noexcept
{
    return m_what;
}

std::string exception::code() const
{
    return m_code;
}

std::string exception::message() const
{
    return m_message;
}

std::string exception::function() const
{
    return m_function;
}
