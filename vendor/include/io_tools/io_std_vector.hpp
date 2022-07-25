//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__io_std_vector__hpp_INCLUDED_
#define _io_tools__io_std_vector__hpp_INCLUDED_

#include "expect.hpp"

#include <iostream>
#include <vector>


namespace io_tools{ namespace io_std_vector{


	template < typename T >
	std::ostream& operator<<(std::ostream& os, std::vector< T > const& data){
		os << '{';

		if(data.size() > 0){
			os << data[0];
			for(std::size_t i = 1; i < data.size(); ++i){
				os << ',' << data[i];
			}
		}

		os << '}';

		return os;
	}

	template < typename T >
	std::istream& operator>>(std::istream& is, std::vector< T >& data){
		if(!expect(is, '{')) return is;

		std::vector< T > tmp;
		{
			T value;
			is >> value;
			tmp.push_back(std::move(value));
		}

		for(;;){
			if(!extract_if_is(is, ',')){
				if(!expect(is, '}')) return is;

				data = std::move(tmp);

				return is;
			}

			T value;
			is >> value;
			tmp.push_back(std::move(value));
		}

		return is;
	}


} }


#endif
