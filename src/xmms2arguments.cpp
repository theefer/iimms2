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

#include "xmms2arguments.hpp"

#include <sstream>

namespace iimms2
{

	Xmms2PlaylistArgument::Xmms2PlaylistArgument( const Xmms::Client& client_ )
		: cmd_parser::tail_argument< std::string >( "playlist" ), client( client_ )
	{
	}

	Xmms2PlaylistArgument::~Xmms2PlaylistArgument()
	{
	}

	boost::shared_ptr< cmd_parser::argument< std::string > >
	Xmms2PlaylistArgument::make( const Xmms::Client& client_ )
	{
		return boost::shared_ptr< cmd_parser::argument< std::string > >(
		       new Xmms2PlaylistArgument( client_ ) );
	}

	void
	Xmms2PlaylistArgument::complete( std::list< std::string >& alternatives ) const
	{
		Xmms::List< std::string > playlists = client.playlist.list();
		for( ; playlists.isValid(); ++playlists ) {
			// FIXME: highlight current playlist
			if( (*playlists)[0] != '_' ) {
				alternatives.push_back( *playlists );
			}
		}
	}


	Xmms2PlaylistItemArgument::Xmms2PlaylistItemArgument( const Xmms::Client& client_ )
		: cmd_parser::tail_argument< std::string >( "track" ), client( client_ )
	{
	}

	Xmms2PlaylistItemArgument::~Xmms2PlaylistItemArgument()
	{
	}

	boost::shared_ptr< cmd_parser::argument< std::string > >
	Xmms2PlaylistItemArgument::make( const Xmms::Client& client_ )
	{
		return boost::shared_ptr< cmd_parser::argument< std::string > >(
		       new Xmms2PlaylistItemArgument( client_ ) );
	}

	void
	Xmms2PlaylistItemArgument::complete( std::list< std::string >& alternatives ) const
	{
		Xmms::List< unsigned int > entries = client.playlist.listEntries();
		for( int pos( 1 ) ; entries.isValid(); ++entries, ++pos ) {
			std::stringstream info;
			Xmms::Dict mediainfo = client.medialib.getInfo( *entries );

			// FIXME: highlight current pos
			// FIXME: Configurable?
			info << pos << ". ";
			if( mediainfo.contains( "artist" ) ) {
				info << mediainfo["artist"];
				if( mediainfo.contains( "title" ) ) {
					info << " - ";
				}
			}
			if( mediainfo.contains( "title" ) ) {
				info << mediainfo["title"];
			}

			alternatives.push_back( info.str() );
		}
	}


	Xmms2SearchArgument::Xmms2SearchArgument( const Xmms::Client& client_ )
		: cmd_parser::tail_argument< std::string >( "playlist" ), client( client_ )
	{
	}

	Xmms2SearchArgument::~Xmms2SearchArgument()
	{
	}

	boost::shared_ptr< cmd_parser::argument< std::string > >
	Xmms2SearchArgument::make( const Xmms::Client& client_ )
	{
		return boost::shared_ptr< cmd_parser::argument< std::string > >(
		       new Xmms2SearchArgument( client_ ) );
	}

	void
	Xmms2SearchArgument::complete( std::list< std::string >& alternatives ) const
	{
		// FIXME: What do we do here?
	}


	Xmms2BrowseArgument::Xmms2BrowseArgument( const Xmms::Client& client_ )
		: cmd_parser::tail_argument< std::string >( "playlist" ), client( client_ )
	{
	}

	Xmms2BrowseArgument::~Xmms2BrowseArgument()
	{
	}

	boost::shared_ptr< cmd_parser::argument< std::string > >
	Xmms2BrowseArgument::make( const Xmms::Client& client_ )
	{
		return boost::shared_ptr< cmd_parser::argument< std::string > >(
		       new Xmms2BrowseArgument( client_ ) );
	}

	std::string
	Xmms2BrowseArgument::extract( cmd_parser::tokeniter& start,
	                              const cmd_parser::tokeniter& end ) const
	{
		cmd_parser::tokeniter pos( start );

		// FIXME: only parse tokens ending with '/'
		std::string val( cmd_parser::tail_argument< std::string >::extract( pos, end ) );

		// Ending with a '/': incomplete path!
		if( val[ val.size() - 1 ] == '/' ) {
			throw cmd_parser::incompatible_argument_error( "incomplete path" );
		}

		// Default protocol if starting with / is file://
		if( val[0] == '/' ) {
			val.insert( 0, "file://" );
		}

		// There might be spaces after '/' in the context rendering, remove'em
		std::string::size_type s;
		while( (s = val.find( "/ " )) != std::string::npos ) {
			val.erase( s + 1, 1 );
		}

		// Update token iterator
		start = pos;
		return val;
	}

	void
	Xmms2BrowseArgument::complete( std::list< std::string >& alternatives ) const
	{
		// FIXME: What do we do here?
		cmd_parser::tail_argument< std::string >::complete( alternatives );
	}

}
