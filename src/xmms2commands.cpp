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

#include "xmms2commands.hpp"

#include "xmms2arguments.hpp"

#include <list>
#include <iostream>
using std::cerr;
using std::endl;

using std::string;
using std::list;

using namespace cmd_parser;
using namespace Mario;

namespace iimms2
{

	Xmms2Commands::Xmms2Commands( const string& client_name )
		: client( client_name )
	{
		// FIXME: might fail, okay for status ; assert on connection when needed
		client.connect();

		inter.add_command("play/pause", "Toggle play/pause the playback.")
			.add_signature<void>( "", boost::bind( &Xmms2Commands::doTogglePlayPause, this ) );

		inter.add_command("clear", "Clear the active playlist.")
			.add_signature<void>( "", boost::bind( &Xmms2Commands::doClear, this ) );

		command& stopCmd( inter.add_command("stop", "Stop the playback.") );
		stopCmd.add_signature<void>( "Stop the playback immediately.", boost::bind( &Xmms2Commands::doStopNow, this ) )
			<< kw_argument::make( "now" );
		stopCmd.add_signature<void>( "Stop the playback at the end of the song.", boost::bind( &Xmms2Commands::doStopGracefully, this ) )
			<< kw_argument::make( "gracefully" );
		stopCmd.add_signature<void, int>( "Stop the playback after N seconds.", boost::bind( &Xmms2Commands::doStopAfterTime, this, _1 ) )
			<< kw_argument::make( "after" ) << argument<int>::make( "N" ) << kw_argument::make( "seconds" );
		stopCmd.add_signature<void, int>( "Stop the playback after N tracks.", boost::bind( &Xmms2Commands::doStopAfterTracks, this, _1 ) )
			<< kw_argument::make( "after" ) << argument<int>::make( "N" ) << kw_argument::make( "tracks" );

		inter.add_command("next", "Skip to next song in playlist.")
			.add_signature<void>( "", boost::bind( &Xmms2Commands::doNext, this ) );

		inter.add_command("previous", "Skip to previous song in playlist.")
			.add_signature<void>( "", boost::bind( &Xmms2Commands::doPrevious, this ) );

		inter.add_command("jump", "Jump to another song in the playlist.")
			.add_signature<void, string>( "", boost::bind( &Xmms2Commands::doJump, this, _1 ) )
				<< Xmms2PlaylistItemArgument::make( client );

		inter.add_command("seek", "Seek in the current song.")
			.add_signature<void, string>( "", boost::bind( &Xmms2Commands::doSeek, this, _1 ) )
				<< argument<string>::make( "offset" );

		inter.add_command("load", "Load another playlist.")
			.add_signature<void, string>( "", boost::bind( &Xmms2Commands::doLoad, this, _1 ) )
				<< Xmms2PlaylistArgument::make( client );

		inter.add_command("enqueue", "Enqueue songs in the active playlist.")
			.add_signature<void, string>( "", boost::bind( &Xmms2Commands::doEnqueue, this, _1 ) )
				<< argument<string>::make( "match" );

		inter.add_command("insert", "Insert songs in the active playlist after the playing one.")
			.add_signature<void, string>( "", boost::bind( &Xmms2Commands::doInsert, this, _1 ) )
				<< argument<string>::make( "match" );

		inter.add_command("status", "Print status on standard output.")
			.add_signature<void>( "", boost::bind( &Xmms2Commands::doStatus, this ) );
	}

	Xmms2Commands::~Xmms2Commands()
	{
	}

	FeedPtr
	Xmms2Commands::choices( const string& input ) const
	{
		FeedPtr ptr;

		try {
			list< string > alter;
			inter.complete( input, alter );
			if( alter.size() > 0 ) {
				ptr = makeAlternativesFeed( alter );
			}
		}
		catch( cmd_parser::incompatible_argument_error& e ) {
			// do nothing, no completion
		}

		return ptr;
	}

	FeedPtr
	Xmms2Commands::makeAlternativesFeed( const list< string >& alternatives ) const
	{
		StringListFeed* feed( new StringListFeed );

		string prev;
		list< string >::const_iterator it;
		for( it = alternatives.begin(); it != alternatives.end(); ++it ) {
			if( (it->size() > 0) && (*it != prev) ) {
				feed->push_back( *it );
				prev = *it;
			}
		}

		return FeedPtr( feed );
	}

	void
	Xmms2Commands::doTogglePlayPause() const
	{
		Xmms::Playback::Status status = client.playback.getStatus();
		if( status == Xmms::Playback::PLAYING ) {
			client.playback.pause();
		}
		else {
			client.playback.start();
		}
	}

	void
	Xmms2Commands::doClear() const
	{
		client.playlist.clear();
	}

	void
	Xmms2Commands::doStopNow() const
	{
		client.playback.stop();
	}

	void
	Xmms2Commands::doStopGracefully() const
	{
		// FIXME: fork and listen
		cerr << "stopGracefully - not implemented!" << endl;
	}

	void
	Xmms2Commands::doStopAfterTime( int t ) const
	{
		// FIXME: wait and die
		cerr << "stopAfterTime(" << t << ") - not implemented!" << endl;
	}

	void
	Xmms2Commands::doStopAfterTracks( int t ) const
	{
		// FIXME: wait, listen and die
		cerr << "stopAfterTracks(" << t << ") - not implemented!" << endl;
	}

	void
	Xmms2Commands::doNext() const
	{
		client.playlist.setNextRel( 1 );
		client.playback.tickle();
	}

	void
	Xmms2Commands::doPrevious() const
	{
		client.playlist.setNextRel( -1 );
		client.playback.tickle();
	}

	/* Jump targets:
	 *   [+-] OFFSET       - relative jump using the offset
	 *   POSITION          - jump to given position
	 *   POSITION "." ...  - jump to given position, ignore the rest
	 *   PATTERN           - jump to next track matching the pattern
	 */
	void
	Xmms2Commands::doJump( string target ) const
	{
		if( target.empty() ) {
			return;
		}

		int pos;
		try {
			// Isolate the prefix before the first dot
			// FIXME: parametrize the separator char
			string::size_type dotpos( target.find( '.' ) );
			string id( target.substr( 0, dotpos ) );

			pos = boost::lexical_cast< int >( id );

			// target := [+-] OFFSET
			if( target[0] == '+' || target[0] == '-' ) {
				client.playlist.setNextRel( pos );
			}
			// target := POSITION
			// target := POSITION "." ...
			else {
				client.playlist.setNext( pos );
			}
		}
		// target := PATTERN
		catch( boost::bad_lexical_cast& ) {
			// FIXME: jump to next track matching the pattern
			return;
		}

		client.playback.tickle();
	}

	void
	Xmms2Commands::doSeek( string offset ) const
	{
		if( !offset.empty() ) {
			int pos;
			try {
				pos = boost::lexical_cast< int >( offset );
				if( offset[0] == '+' || offset[0] == '-' ) {
					client.playback.seekMsRel( pos * 1000 );
				}
				else {
					client.playback.seekMs( pos * 1000 );
				}
			}
			catch( boost::bad_lexical_cast& ) {
				// invalid value, error
				cerr << "invalid seeking position: " << offset << endl;
			}
		}
	}

	void
	Xmms2Commands::doLoad( string playlist ) const
	{
		try {
			client.playlist.load( playlist );
			// FIXME: tickle *if* playlist changed
		}
		catch( Xmms::result_error& ) {
			cerr << "could not load playlist: " << playlist << endl;
		}
	}


	/* Match patterns:
	 *   BROWSE-PREFIX     - browse the location (e.g. '/', 'smb://', etc)
	 *   (*|ARTIST)        - select all or one valid artist from the list of artists
	 *   PATTERN           - filter by the given pattern
	 */
	void
	Xmms2Commands::doEnqueue( string match ) const
	{
		// FIXME: Code
	}

	void
	Xmms2Commands::doInsert( string match ) const
	{
		// FIXME: Code
	}

	void
	Xmms2Commands::doStatus() const
	{
		// FIXME: if not connected, display message, else display playing song
	}


}
