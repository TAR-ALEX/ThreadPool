//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__range_to_string__hpp_INCLUDED_
#define _io_tools__range_to_string__hpp_INCLUDED_

#include <sstream>
#include <string_view>


namespace io_tools{


	template < typename Range >
	inline std::string range_to_string(
		Range const& range,
		std::string_view delimiter = ", "
	){
		using std::begin;
		using std::end;

		std::ostringstream os;
		auto iter = begin(range);
		auto const e = end(range);
		if(iter != e){
			os << *iter++;
			while(iter != e){
				os << delimiter << *iter++;
			}
		}

		return os.str();
	}

	template < typename T, std::size_t N >
	inline std::string range_to_string(
		T(&range)[N],
		std::string_view delimiter = ", "
	){
		return range_to_string< T(&)[N] >(range, delimiter);
	}


}


#endif
