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

#include <vector>
#include <string>
using std::vector;
using std::string;


#include "dictfeed.hpp"
#include "xmms2commands.hpp"

using namespace iimms2;
using namespace Mario;

int
main( int argc, char* argv[] )
{
/*
	Xmms::Client client("iimms2");
	client.connect();

	Xmms::Coll::Universe univ;

	string artist;
	string album;
	string title;

	artist = choice( client, univ, "artist" );
	cout << "selected artist: " << artist << endl;
	Xmms::Coll::Equals cArtist( univ, "artist", artist, true );

	album = choice( client, cArtist, "album" );
	Xmms::Coll::Equals cAlbum( cArtist, "album", album, true );

	title = choice( client, cAlbum, "title" );

	cout << "selected: " << title << endl;
*/

	// FIXME: Read flags (version, help, etc)
	// FIXME: flag to choose if output goes to stdout or dmenu (e.g. for status)

	string input;
	for( int i( 1 ); i < argc; ++i ) {
		if( i > 1 ) input += " ";
		input += argv[i];
	}

	Xmms2Commands x2cmds( CLIENT_NAME );

	vector< string > args;
// FIXME: case insensitive requires theefer-made dmenu...
//	args.push_back( "-i" );
	args.push_back( "-p" );
	args.push_back( "iimms2" );
	AppPipe dmenu_pipe( DMENU_PATH, "dmenu", args );

	Completer comp( x2cmds, dmenu_pipe );
	comp.complete( input );

	return 0;
}
