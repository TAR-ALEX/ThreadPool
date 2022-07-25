//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__io_c_array__hpp_INCLUDED_
#define _io_tools__io_c_array__hpp_INCLUDED_

#include "expect.hpp"

#include <iostream>
#include <algorithm>


namespace io_tools{ namespace io_c_array{


	template < typename T, std::size_t N >
	std::ostream& operator<<(std::ostream& os, T(&data)[N]){
		os << '{';

		if(N > 0){
			os << data[0];
			for(std::size_t i = 1; i < N; ++i){
				os << ',' << data[i];
			}
		}

		os << '}';

		return os;
	}

	template < typename T, std::size_t N >
	std::istream& operator>>(std::istream& is, T(&data)[N]){
		if(!expect(is, '{')) return is;

		T tmp[N];
		if(N > 0){
			is >> tmp[0];
			for(std::size_t i = 1; i < N; ++i){
				if(!expect(is, ',')) return is;
				is >> tmp[i];
			}
		}

		if(!expect(is, '}')) return is;

		std::move(std::begin(tmp), std::end(tmp), std::begin(data));

		return is;
	}


} }


#endif
