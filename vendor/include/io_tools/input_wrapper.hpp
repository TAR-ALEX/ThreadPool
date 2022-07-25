//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__input_wrapper__hpp_INCLUDED_
#define _io_tools__input_wrapper__hpp_INCLUDED_

#include <sstream>


namespace io_tools{


	template < typename T >
	struct input_wrapper_t{
		input_wrapper_t(T& value): value(value) {}
		input_wrapper_t(input_wrapper_t< T > const& c): value(c.value) {}

		T& value;
	};

	template < typename T >
	decltype(auto) input_wrapper(T& value){
		if constexpr(std::is_floating_point_v< T >){
			return input_wrapper_t< T >{value};
		}else{
			return (value);
		}
	}


	template < typename CharT, typename Traits, typename T >
	std::basic_istream< CharT, Traits >& operator>>(
		std::basic_istream< CharT, Traits >& is,
		input_wrapper_t< T > data
	){
		// float followed by characters (like in 1024x768) don't work,
		// therefor this reads all allowed character before parsing.
		// Attention: Only floats in fixed formatting are implemented

		std::stringstream buffer;
		CharT in;
		if(is){
			bool point_found = false;
			while(is >> in){
				if((in >= '0' && in <= '9') || (!point_found && in == '.')){
					buffer << in;
					if(!point_found && in == '.') point_found = true;
				}else{
					is.putback(in);
					break;
				}
			}

			if(is) buffer >> data.value;
		}


		return is;
	}




}

#endif
