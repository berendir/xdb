/*******************************************************************************
** MIT License
**
** Copyright (c) 2017 Berendir Huntinghawk
**
** This file is part of the xdb project.
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

#ifndef XDB_ERRORS_H
#define XDB_ERRORS_H

#include <exception>
#include <string>


namespace xdb {

/**
 * @brief The exception class is the base exception class for all the project's
 *  exceptions.
 */
class exception : public std::exception
{
public:
    exception(const std::string &code, const std::string &message, const std::string &function);

    exception(const exception &other);

    virtual ~exception();

    const char * what() const noexcept;

    std::string code() const;

    std::string message() const;

    std::string function() const;

private:
    std::string m_code;
    std::string m_message;
    std::string m_function;
    char * m_what;
};

}

#define XDB_THROW_EXCEPTION(c, m) throw xdb::exception((c), (m), __FUNCTION__)

#endif // XDB_ERRORS_H
