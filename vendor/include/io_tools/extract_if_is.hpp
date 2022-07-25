//-----------------------------------------------------------------------------
// Copyright (c) 2013-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__extract_if_is__hpp_INCLUDED_
#define _io_tools__extract_if_is__hpp_INCLUDED_

#include <istream>


namespace io_tools{


	inline bool extract_if_is(std::istream& is, char const should_be){
		if(is){
			char in;
			if(is >> in){
				if(in == should_be){
					return true;
				}
				is.putback(in);
			}else if(is.eof()){
				is.clear();
			}
		}
		return false;
	}


}

#endif
