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

#ifndef IIMMS2_XMMS2COMMANDS_HPP
#define IIMMS2_XMMS2COMMANDS_HPP

#include <string>

#include <xmmsclient/xmmsclient++.h>

#include "mario/mario.hpp"


namespace iimms2
{

	class Xmms2Commands : public Mario::Commands
	{

		enum BrowseAction
		{
			BROWSE_ENQUEUE,
			BROWSE_INSERT
		};

	public:
		Xmms2Commands( const std::string& client_name );
		~Xmms2Commands();

		Mario::FeedPtr choices( const Mario::Context& ctx ) const;

		Mario::FeedPtr
		makeAlternativesFeed( const std::list< std::string >& alternatives
		                    ) const;

		void doTogglePlayPause() const;
		void doClear() const;
		void doStopNow() const;
		void doStopGracefully() const;
		void doStopAfterTime( int t ) const;
		void doStopAfterTracks( int t ) const;
		void doNext() const;
		void doPrevious() const;
		void doJump( std::string target ) const;
		void doSeek( std::string offset ) const;
		void doLoad( std::string playlist ) const;
		void doEnqueue( std::string match ) const;
		void doInsert( std::string match ) const;
		void doSearch( std::string match ) const;
		void doBrowse( std::string match, BrowseAction action ) const;
		void doStatus() const;

	private:
		Xmms::Client client;

	};

}

#endif // IIMMS2_XMMS2COMMANDS_HPP
