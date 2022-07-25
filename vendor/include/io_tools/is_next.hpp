//-----------------------------------------------------------------------------
// Copyright (c) 2013-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__is_next__hpp_INCLUDED_
#define _io_tools__is_next__hpp_INCLUDED_

#include <istream>


namespace io_tools{


	inline bool is_next(std::istream& is, char const should_be){
		if(is){
			char in;
			if(is >> in){
				is.putback(in);
				return in == should_be;
			}else if(is.eof()){
				is.clear();
			}
		}
		return false;
	}


}

#endif
