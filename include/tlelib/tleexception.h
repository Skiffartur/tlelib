/*-----------------------------------------------------------------------------+
 | TLELib                                                                      |
 | Copyright 2011 Sergei V. Fundaev                                            |
 +-----------------------------------------------------------------------------+
 | This file is part of TLELib.                                                |
 |                                                                             |
 | TLELib is free software: you can redistribute it and/or modify              |
 | it under the terms of the GNU Lesser General Public License as published by |
 | the Free Software Foundation, either version 3 of the License, or           |
 | (at your option) any later version.                                         |
 |                                                                             |
 | TLELib is distributed in the hope that it will be useful,                   |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of              |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               |
 | GNU Lesser General Public License for more details.                         |
 |                                                                             |
 | You should have received a copy of the GNU Lesser General Public License    |
 | along with TLELib. If not, see <http://www.gnu.org/licenses/>.              |
 +----------------------------------------------------------------------------*/
/*!
    \file tleexception.h
    \brief File contains the exceptions, generated by TLELib library.
*/

#include <string>
#include <exception>
#include <stdexcept>

#ifndef TLEEXCEPTION_H
#define TLEEXCEPTION_H

namespace tlelib
{

/*!
    \brief The exception object, generated when the string
    is too short and the substring or a symbol cannot
    be taken from it at the given position.
*/
class tle_too_short_string: public std::runtime_error
{
    std::string m_line; //!< line for which the exception is actual
public:
    /*!
        \brief Constructor.
        \param line - line, which is too short.
    */
    tle_too_short_string(const std::string& line)
        : std::runtime_error("Too short string: " + line)
    {
        m_line = line;
    }
    virtual ~tle_too_short_string() throw() {} //!< Destructor.
    /*!
        \brief Get a line, caused the exception.
        \return The line, caused the exception.
    */
    std::string line() const throw() { return m_line; }
};
//------------------------------------------------------------------------------

/*!
    \brief The exception object, generated when the string
    cannot be converted into the specified type.
*/
class tle_invalid_format: public std::runtime_error
{
    std::string m_line; //!< line for which the exception is actual
public:
    /*!
        \brief Constructor.
        \param line - line, from which the substring has been taken for convertation.
    */
    tle_invalid_format(const std::string& line) : std::runtime_error("Invalid element format in line: \"" + line + "\".")
    {
        m_line = line;
    }
    virtual ~tle_invalid_format() throw() {} //!< Destructor.
    /*!
        \brief Get a line, caused the exception.
        \return The line, caused the exception.
    */
    std::string line() const throw() { return m_line; }
};
//------------------------------------------------------------------------------

/*!
    \brief The exception object, generated when the checksum of
    the string is invalid.
*/
class tle_checksum_error: public std::runtime_error
{
    std::string m_line; //!< line for which the exception is actual
    int m_expected_checksum, //!< Expected checksum
        m_actual_checksum;   //!< Actual checksum, specified in the string
public:
    /*!
        \brief Constructor.
        \param line - the string with invalid checksum
        \param expected_checksum - expected checksum for this string
        \param actual_checksum - actual checksum, specified in the string
    */
    tle_checksum_error(const std::string& line, const int expected_checksum, const int actual_checksum)
        : std::runtime_error("Invalid checksum in line \""+ line +"\". Expected checksum: " + int2string(expected_checksum) + ". Actual checksum: " + int2string(expected_checksum) + ".")
    {
        m_line = line;
        m_expected_checksum = expected_checksum;
        m_actual_checksum = actual_checksum;
    }
    virtual ~tle_checksum_error() throw() {} //!< Destructor.
    /*!
        \brief Get a line, caused the exception.
        \return The line, caused the exception.
    */
    std::string line() const throw() { return m_line; }
    /*!
        \brief Get expected checksum
        \return Expected checksum
    */
    int expected_checksum() const throw() { return m_expected_checksum; }
    /*!
        \brief Get actual checksum
        \return Actual checksum
    */
    int actual_checksum() const throw() { return m_actual_checksum; }
};
//------------------------------------------------------------------------------

} // namespace

#endif // TLEEXCEPTION_H