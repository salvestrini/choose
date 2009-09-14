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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>
#include <ctype.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "config.h"

#include "packrules/packrules-common.h"
#include "packrules/packrules-stream.h"

static void version(void)
{
	lmsg << "packrules "
	     << "(" << PACKAGE_NAME << " " << PACKAGE_VERSION << ")" << endl;
	lmsg << "Written by Francesco Salvestrini" << endl;
	lmsg << endl;
	lmsg << "This is free software; see the source for copying conditions."
	        "There is NO" << endl;
	lmsg << "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
		"PARTICULAR PURPOSE." << endl;
}

static void hint(std::string s)
{
	assert(s.size());

	lmsg << s << endl;
	lmsg << "Try `" << PROGRAM_NAME 
	     << " --help' for more information." << endl;
}

static struct option options[] = {
	{ "input",   1, 0, 'i' },
	{ "output",  1, 0, 'o' },
	{ "path",    1, 0, 'p' },
	{ "version", 0, 0, 'V' },
	{ "fatal",   0, 0, 'f' },
	{ "debug",   0, 0, 'd' },
	{ "verbose", 0, 0, 'v' },
	{ "help",    0, 0, 'h' },
	{ 0,         0, 0, 0   }
};

static struct {
	const char * description; 
} options_extra[] = {
	{ "set input file" },
	{ "set output file" },
	{ "set path" },
	{ "dump version information, then exit" },
	{ "warnings are fatal" },
	{ "enable debugging" },
	{ "enable verbose messages" },
	{ "display this help and exit" },
	{ 0 }
};

static void help(void)
{
	unsigned int i;
	unsigned int max_val;
	unsigned int desc_indent;

	lmsg << "Usage: " << PROGRAM_NAME << " [OPTION]..." << endl;
	lmsg << endl;

	max_val     = 0;

	for (i = 0; options[i].name; i++) {

		if (max_val < strlen(options[i].name)) {
			max_val = strlen(options[i].name);
		}
		assert(max_val > 0);
	}
	desc_indent = 7 + max_val + 2;

	for (i = 0; options[i].name; i++) {
		unsigned int j;
		unsigned int k;
		unsigned int l;

		j = 0;
		k = 0;
		l = 0;

		assert(options[i].name);
		assert(options[i].val);
		assert(options_extra[i].description);

		lmsg << "  -" << (char) options[i].val
		     << ", "
		     << "--"  << (char *) options[i].name;

		for (j = 0; j < (max_val - strlen(options[i].name)); j++) {
			lmsg << " ";
		}

		lmsg << "  " << options_extra[i].description
		     << endl;
	}

	lmsg << endl;
	lmsg << "Report bugs to <" << PACKAGE_BUGREPORT << ">" << endl;
}

static std::string::size_type skip_whites(const std::string &    in,
					  std::string::size_type start)
{
	std::string::size_type stop;

	stop = start;
	while ((stop < in.size()) && isspace(in.at(stop))) {
		stop++;
	}

	ldbg << "String without leading spaces: "
	     << "'" <<  in.substr(stop, std::string::npos) << "'" << endl;

	return stop;
}		     

static std::string get_source(const std::string & line)
{
	std::string            retval;
	std::string::size_type start;
	std::string::size_type stop;

	retval = std::string("");

	ldbg << "Input line is '" << line << "'" << endl;

	if (line.size() == 0) {
		ldbg << "Line is empty" << endl;
		return retval;
	}

	start = 0;

	start = skip_whites(line, start);
	if (start == std::string::npos) {
		ldbg << "Line is empty" << endl;
		return retval;
	}

	if (line.find("#", start) !=
	    std::string::npos) {
		ldbg << "Got comment" << endl;
		return retval;
	}

	if (line.find("source ", start) ==
	    std::string::npos) {
		ldbg << "No source directive found !!!" << endl;
		return retval;
	}

	ldbg << "Line contains source directive, probably ..." << endl;

	start = skip_whites(line, start);
	if (start == std::string::npos) {
		return retval;
	}

	start = line.find("\"", start);
	if (start == std::string::npos) {
		return retval;
	}
	start++;
	ldbg << "Start is: " << start << endl;

	stop = line.find("\"", start);
	if (stop == std::string::npos) {
		return retval;
	}
	stop--;
	ldbg << "Stop is:  " << stop << endl;

	ldbg << "Total length is:  " << line.size()  << endl;
	ldbg << "Source length is: " << stop - start << endl;

	retval = line.substr(start, stop - start + 1);

	return retval;
}

static bool process(const std::string & path,
		    const std::string & in_filename,
		    std::ostream &      out_stream)
{
	assert(out_stream);

	std::string filename;
	filename = path + std::string("/") + in_filename;

	lvrb << "Processing '" << filename << "'" << endl;

	std::ifstream in_stream(filename.c_str(), std::ios_base::in);
	if (in_stream.fail()) {
		lerr << "Cannot open input file "
		     << "'" << filename << "' "
		     << " for reading" << endl;
		return false;
	}

	std::string line;
	while (!std::getline(in_stream, line).eof()) {
		
		ldbg << "" << endl;
		ldbg << "New line: '" << line << "'" << endl;
		
		std::string source;
		source = get_source(line);
		if (source.size() != 0) {
			ldbg << "Line is a source line" << endl;
			if (!process(path, source, out_stream)) {
				return false;
			}

			continue;
		}

		ldbg << "Line '" << line << "' Is a normal line" << endl;
		
		out_stream << line << std::endl;
	}
	
	in_stream.close();

	return true;
}

int main(int    argc,
	 char * argv[])
{
	std::string     in_filename;
	std::string     out_filename;
	std::string     path;
	bool            debug;
	bool            verbose;
	bool            fatal;

	int             c;
	int             this_option_optind;
	int             option_index;

	path       = std::string("");
	debug      = false;
	verbose    = false;
	fatal      = false;

	ldbg << disable;
	lvrb << disable;

	opterr = 0;
	while (1) {
		this_option_optind = optind ? optind : 1;
		option_index       = 0;
		
		c = getopt_long(argc, argv,
				":i:o:p:fVndvh",
				options, &option_index);
		if (c == -1) {
			// No more options
			break;
		}
		
		switch (c) {
		case 'i':
			in_filename = std::string(optarg);
			break;
			
		case 'o':
			out_filename = std::string(optarg);
			break;
			
		case 'p':
			path = std::string(optarg);
			break;

		case 'f':
			fatal = true;
			break;

		case 'V':
			version();
			exit(EXIT_SUCCESS);
			
		case 'v':
			verbose = true;
			lvrb << enable;
			break;

		case 'd':
			debug = true;
			ldbg << enable;
			break;

		case 'h':
			help();
			exit(EXIT_SUCCESS);
			
		case ':':
			hint("Missing argument for option");
			exit(EXIT_FAILURE);

		case '?':
			hint("Unrecognized option");
			exit(EXIT_FAILURE);
			
		default:
			assert(0);
		}
	}
	
	ldbg << "Input file:  " << "'" << in_filename  << "'" << endl;
	ldbg << "Output file: " << "'" << out_filename << "'" << endl;
	ldbg << "Path:        " << "'" << path         << "'" << endl;
	ldbg << "Fatals:      " << (fatal   ? "on" : "off")   << endl;
	ldbg << "Verbose:     " << (verbose ? "on" : "off")   << endl;
	ldbg << "Debugging:   " << (debug   ? "on" : "off")   << endl;
	
	if (optind < argc) {
		ldbg << "Unhandled non-option ARGV-elements:" << endl;
		while (optind < argc) {
			ldbg << "  " << argv[optind] << endl;
			optind++;
		}
	}

	//
	// Setup
	//

	ldbg << "Path:    " << path         << endl;
	ldbg << "Infile:  " << in_filename  << endl;
	ldbg << "Outfile: " << out_filename << endl;

	// Input file
	if (!in_filename.size()) {
		hint("Missing input file name");
		exit(EXIT_FAILURE);
	}
	
	// Output file
	if (!out_filename.size()) {
		hint("Missing output file name");
		exit(EXIT_FAILURE);
	}
	std::ofstream out_stream(out_filename.c_str(),
				 std::ios_base::out | std::ios_base::trunc);
	if (out_stream.fail()) {
		lerr << "Cannot open output file "
		     << "'" << out_filename << "' " 
		     << "for writing" << endl;
		exit(EXIT_FAILURE);
	}
	
	// Path
	if (path.size() == 0) {
		path = std::string("./");
	}

	// Main program
	int retval;

	retval = process(path, in_filename, out_stream);
	if (!retval) {
		lerr << "Error parsing input file " << in_filename << endl;
		exit(EXIT_FAILURE);
	}

	out_stream.close();

	ldbg << "Exiting with a good return value" << endl;

	exit(EXIT_SUCCESS);
}
