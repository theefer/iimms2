/* iimms2 - an XMMS2 client for wmii/dwm (using dmenu)
 * Copyright (C) 2007  Sébastien Cevey
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef IIMMS2_XMMS2ARGUMENTS_HPP
#define IIMMS2_XMMS2ARGUMENTS_HPP

#include <string>
#include <list>

#include <xmmsclient/xmmsclient++.h>

#include <boost/shared_ptr.hpp>

#include "cmd_parser/cmd_parser.h"

// DEBUG
#include <iostream>
using std::cout;
using std::endl;

namespace iimms2
{

	class Xmms2PlaylistArgument : public cmd_parser::tail_argument< std::string >
	{
	public:
		Xmms2PlaylistArgument( const Xmms::Client& client_ );
		virtual ~Xmms2PlaylistArgument();

		static boost::shared_ptr< cmd_parser::argument< std::string > >
		make( const Xmms::Client& client_ );

		void complete( std::list< std::string >& alternatives ) const;

	protected:
		const Xmms::Client& client;

	};

	class Xmms2PlaylistItemArgument : public cmd_parser::tail_argument< std::string >
	{
	public:
		Xmms2PlaylistItemArgument( const Xmms::Client& client_ );
		virtual ~Xmms2PlaylistItemArgument();

		static boost::shared_ptr< cmd_parser::argument< std::string > >
		make( const Xmms::Client& client_ );

		void complete( std::list< std::string >& alternatives ) const;

	protected:
		const Xmms::Client& client;

	};

	class Xmms2SearchArgument : public cmd_parser::tail_argument< std::string >
	{
	public:
		Xmms2SearchArgument( const Xmms::Client& client_ );
		virtual ~Xmms2SearchArgument();

		static boost::shared_ptr< cmd_parser::argument< std::string > >
		make( const Xmms::Client& client_ );

		void complete( std::list< std::string >& alternatives ) const;

	protected:
		const Xmms::Client& client;

	};

	class Xmms2BrowseArgument : public cmd_parser::tail_argument< std::string >
	{
	public:
		Xmms2BrowseArgument( const Xmms::Client& client_ );
		virtual ~Xmms2BrowseArgument();

		static boost::shared_ptr< cmd_parser::argument< std::string > >
		make( const Xmms::Client& client_ );

		std::string extract( cmd_parser::tokeniter& start,
		                     const cmd_parser::tokeniter& end ) const;

		void complete( std::list< std::string >& alternatives ) const;

		void accept( cmd_parser::visitor& v ) const
		{
			cout << "accept in x2 browse agent" << endl;
			v.visit( *this );
		}

	protected:
		const Xmms::Client& client;

	};

}

#endif // IIMMS2_XMMS2ARGUMENTS_HPP
