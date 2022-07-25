//-----------------------------------------------------------------------------
// Copyright (c) 2013-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__expect__hpp_INCLUDED_
#define _io_tools__expect__hpp_INCLUDED_

#include "extract_if_is.hpp"


namespace io_tools{


	template < typename ShouldBe >
	inline bool expect(std::istream& is, ShouldBe const& should_be){
		if(is){
			auto pos = is.tellg();
			ShouldBe in;
			if(is >> in){
				if(in == should_be){
					return true;
				}
				is.seekg(pos);
			}else if(is.eof()){
				is.clear();
				is.seekg(pos);
			}

			is.setstate(std::ios_base::failbit);
		}
		return false;

	}

	inline bool expect(std::istream& is, char const should_be){
		auto result = extract_if_is(is, should_be);
		if(!result){
			is.setstate(std::ios_base::failbit);
		}
		return result;
	}


}

#endif
