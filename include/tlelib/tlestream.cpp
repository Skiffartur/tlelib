/*-----------------------------------------------------------------------------+
 | TLELib                                                                      |
 | Copyright 2011-2014 Sergei Fundaev                                          |
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
    \file tlestream.cpp
    \brief File contains the realization of Stream object.
*/

#define TLE_LINE_LENGTH 72 //!< Length of TLE line

#include <string>
#include <iostream>
#include <tlelib/tlestream.h>

namespace tlelib
{

Stream::Stream(std::istream &source, const FileType fileType)
    : m_source(&source),
      m_fileType(fileType),
      m_enforceParsing(false)
{
}
//------------------------------------------------------------------------------

std::istream &Stream::operator>>(Node &node)
{
    char buf[TLE_LINE_LENGTH] = "";

    m_source->getline(buf, TLE_LINE_LENGTH);
    std::string line1(buf);
    m_source->getline(buf, TLE_LINE_LENGTH);
    std::string line2(buf);

    if (m_fileType == ThreeLines)
    {
        m_source->getline(buf, TLE_LINE_LENGTH);
        std::string line3(buf);
        node.assign(line1, line2, line3, m_enforceParsing);
    }
    else
    {
        node.assign(line1, line2, m_enforceParsing);
    }

    return *m_source;
}
//------------------------------------------------------------------------------

Stream::operator bool()
{
    if (!(*m_source) || m_source->eof())
        return false;

    // Detect if there are tle lines, not read yet
    m_source->get();
    if (!m_source->good() || m_source->eof())
        return false;

    m_source->unget();
    return true;
}
//------------------------------------------------------------------------------

bool Stream::enforceParsing(bool parsingMode)
{
    bool res = m_enforceParsing;
    m_enforceParsing = parsingMode;
    return res;
}
//------------------------------------------------------------------------------

}  // namespace tlelib