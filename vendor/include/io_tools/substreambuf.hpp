//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/io_tools
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _io_tools__substreambuf__hpp_INCLUDED_
#define _io_tools__substreambuf__hpp_INCLUDED_

#include <streambuf>


namespace io_tools{


	class substreambuf : public std::streambuf{
	public:

		substreambuf(std::streambuf *sbuf, std::size_t start, std::size_t len) : m_sbuf(sbuf), m_start(start), m_len(len), m_pos(0)
		{
			std::streampos p = m_sbuf->pubseekpos(start);
			setbuf(NULL, 0);
		}

	protected:

		int underflow()
		{
			if (m_pos + std::streamsize(1) >= m_len)
				return traits_type::eof();
			return m_sbuf->sgetc();
		}

		int uflow()
		{
			if (m_pos + std::streamsize(1) > m_len)
				return traits_type::eof();
			m_pos += std::streamsize(1);
			return m_sbuf->sbumpc();
		}

		std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out)
		{
			std::streampos cursor;

			if (way == std::ios_base::beg)
				cursor = off;
			else if (way == std::ios_base::cur)
				cursor = m_pos + off;
			else if (way == std::ios_base::end)
				cursor = m_len - off;

			if (cursor < 0 || cursor >= m_len)
				return std::streampos(-1);
			m_pos = cursor;
			if (m_sbuf->pubseekpos(m_start + m_pos, which) == std::streampos(-1))
				return std::streampos(-1);

			return m_pos;
		}

		std::streampos seekpos(std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out)
		{
			if (sp < 0 || sp >= m_len)
				return std::streampos(-1);
			m_pos = sp;
			if (m_sbuf->pubseekpos(m_start + m_pos, which) == std::streampos(-1))
				return std::streampos(-1);
			return m_pos;
		}

	private:
		std::streambuf *m_sbuf;
		std::streampos m_start;
		std::streamsize m_len;
		std::streampos m_pos;
	};

}


#endif
