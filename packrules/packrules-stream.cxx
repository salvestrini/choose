//
// Copyright (C) 2008, 2009 Francesco Salvestrini
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#include <iostream>
#include "assert.h"

#include "include/config.h"

#include "packrules/packrules-stream.h"

logStream::logStream(const std::string& prefix) :
	_prefixed(false),
	_prefix(prefix),
	_enabled(true),
	_lines(0)
{
}

bool logStream::enabled(void)
{
	return _enabled;
}

void logStream::doPrefix(void)
{
	if (!_prefixed) {
		if (_prefix.size()) {
			std::cout << _prefix << ": ";
		}
		_prefixed = true;
		_lines++;
	}
}

unsigned int logStream::lines(void)
{
	return _lines;
}

logStream& logStream::operator<<(int i)
{
	if (_enabled) {
		doPrefix();
		std::cout << i;
	}

	return *this;
}

logStream& logStream::operator<<(unsigned int i)
{
	if (_enabled) {
		doPrefix();
		std::cout << i;
	}

	return *this;
}

logStream& logStream::operator<<(char c)
{
	if (_enabled) {
		doPrefix();
		std::cout << c;
	}

	return *this;
}

logStream& logStream::operator<<(const char * s)
{
	if (_enabled) {
		doPrefix();
		std::cout << s;
	}

	return *this;
}

logStream& logStream::operator<<(const std::string * s)
{
	if (_enabled) {
		doPrefix();
		std::cout << (* s);
	}

	return *this;
}

logStream& logStream::operator<<(std::string s)
{
	if (_enabled) {
		doPrefix();
		std::cout << s;
	}

	return *this;
}

logStream& logStream::operator<<(logStream& (*pf)(logStream&))
{
	assert(pf);
	
	if (pf == endl) {
		if (_enabled) {
			std::cout << std::endl;
			std::cout.flush();
			_prefixed = false;
		}
	} else if (pf == enable) {
		_enabled = true;
	} else if (pf == disable) {
		_enabled = false;
	}

	return *this;
}

logStream& enable(logStream& ls)
{
	return ls;
}

logStream& disable(logStream& ls)
{
	return ls;
}

logStream& endl(logStream& ls)
{
	return ls;
}
