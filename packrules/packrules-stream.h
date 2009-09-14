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

#ifndef PACKRULES_STREAM_H
#define PACKRULES_STREAM_H

#include <ostream>
#include <string>

class logStream { //: public std::ostream {
 public:
	logStream(const std::string& prefix);

	bool         enabled(void);
	unsigned int lines(void);
	
	// Manipulators
	//logStream& enable(logStream& ls);
	//logStream& disable(logStream& ls);
	//logStream& endl(logStream& ls);

	// operator<<
	logStream&   operator<<(int i);
	logStream&   operator<<(unsigned int i);
	logStream&   operator<<(char c);
	logStream&   operator<<(const char * s);
	logStream&   operator<<(std::string s);
	logStream&   operator<<(const std::string * s);
	logStream&   operator<<(logStream& (*pf)(logStream& ls));

 private:
	void         doPrefix(void);
	bool         _prefixed;
	std::string  _prefix;
	bool         _enabled;
	unsigned int _lines;
};

logStream& enable(logStream& ls);
logStream& disable(logStream& ls);
logStream& endl(logStream& ls);

#endif // PACKRULES_STREAM_H */
