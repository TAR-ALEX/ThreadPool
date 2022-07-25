//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__isubstream__hpp_INCLUDED_
#define _io_tools__isubstream__hpp_INCLUDED_

#include "substreambuf.hpp"

#include <memory>


namespace io_tools{


	class isubstream: public std::istream{
	public:
		isubstream(
			std::streambuf* buffer,
			std::streampos start,
			std::streamsize size
		):
			std::istream(&buffer_),
			buffer_(buffer, start, size)
			{}

		isubstream(isubstream const&) = delete;
		isubstream(isubstream&&) = default;

	private:
		substreambuf buffer_;
	};


}


#endif
