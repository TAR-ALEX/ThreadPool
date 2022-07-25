//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__io_std_array__hpp_INCLUDED_
#define _io_tools__io_std_array__hpp_INCLUDED_

#include "io_c_array.hpp"

#include <array>


namespace io_tools{ namespace io_std_array{


	template < typename T, std::size_t N >
	std::ostream& operator<<(std::ostream& os, std::array< T, N > const& data){
		static_assert(N > 0, "arrays with size 0 are not supported");
		using ::io_tools::io_c_array::operator<<;
		return os << reinterpret_cast< T const(&)[N] >(data);
	}

	template < typename T, std::size_t N >
	std::istream& operator>>(std::istream& is, std::array< T, N >& data){
		static_assert(N > 0, "arrays with size 0 are not supported");
		using ::io_tools::io_c_array::operator>>;
		return is >> reinterpret_cast< T(&)[N] >(data);
	}


} }


#endif
