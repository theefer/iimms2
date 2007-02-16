/* mario - a C++ lib for using pipes, feeds, commands and stuff
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

#include "mario.hpp"

#include <stdexcept>

#include <sys/wait.h>

using std::string;
using std::list;
using std::vector;
using std::runtime_error;

namespace Mario
{

	Pipe::Pipe()
	{
	}

	Pipe::~Pipe()
	{
	}


	string
	Pipe::pump( Feed& feed ) const
	{
		int in_pfd[2];
		int out_pfd[2];
		pid_t cpid;

		string selection;

		if( pipe( in_pfd ) == -1 || pipe( out_pfd ) == -1) {
			throw runtime_error( "pipe failed" );
		}

		cpid = fork();
		if( cpid == -1 ) {
			throw runtime_error( "fork failed" );
		}

		if( cpid == 0 ) {    /* Child */
			dup2( in_pfd[0], 0 );    /* make 0 same as read-from end of pipe */
			dup2( out_pfd[1], 1 );   /* make 0 same as read-from end of pipe */
			close( in_pfd[1] );      /* Close unused write end */
			close( out_pfd[0] );     /* Close unused read end */

			// FIXME: handle "failed" execution (non-0 retval)
			dispatch();
			_exit( EXIT_SUCCESS );
		}
		else { /* Parent */
			char buf;

			close( in_pfd[0] );     /* Close unused read end */
			close( out_pfd[1] );    /* Close unused write end */

			for( feed.first() ; feed.valid(); ++feed ) {
				string val( *feed );
				write( in_pfd[1], val.c_str(), val.size() );
				write( in_pfd[1], "\n", 1 );
			}
			close( in_pfd[1] );     /* Reader will see EOF */

			while( read(out_pfd[0], &buf, 1) > 0 ) {
				selection.push_back( buf );
			}

			close( out_pfd[0] );     /* Done reading */
			wait( NULL );
		}

		return selection;
	}


	AppPipe::AppPipe( const string& path_, const string& name_, const vector< string >& args_ )
		: path( path_ ), name( name_ ), args( args_ )
	{
	}

	AppPipe::~AppPipe()
	{
	}

	void
	AppPipe::dispatch() const
	{
		unsigned int i;
		char** argv = new char*[ args.size() + 2 ];
		argv[0] = const_cast< char* >( name.c_str() );
		for( i = 0; i < args.size(); ++i ) {
			argv[i + 1] = const_cast< char* >( args[i].c_str() );
		}
		argv[i + 1] = NULL;

		execvp( path.c_str(), argv );

		// FIXME: leak?
		delete [] argv;
	}


	Feed::Feed()
	{
	}

	Feed::~Feed()
	{
	}


	StringListFeed::StringListFeed()
	{
	}

	StringListFeed::~StringListFeed()
	{
	}

	void
	StringListFeed::push_back( const string& str )
	{
		stringlist.push_back( str );
	}

	void
	StringListFeed::first()
	{
		pos = stringlist.begin();
	}

	bool
	StringListFeed::valid() const
	{
		return pos != stringlist.end();
	}

	string
	StringListFeed::operator *() const
	{
		return *pos;
	}

	void
	StringListFeed::operator ++()
	{
		++pos;
	}


	Commands::Commands()
	{
	}

	Commands::~Commands()
	{
	}

	void
	Commands::run( const string& input ) const
	{
		inter.run( input );
	}


	Context::Context()
	{
	}

	Context::Context( const Context& ctx )
		: env( ctx.env )
	{
	}

	Context::~Context()
	{
	}

	Context
	Context::expand( const string& more ) const
	{
		Context ctx( *this );
		ctx.env.push_back( more );
		return ctx;
	}

	string
	Context::render() const
	{
		string out;
		list< string >::const_iterator it;
		for( it = env.begin(); it != env.end(); ++it ) {
			out.append( *it );
		}

		return out;
	}


	EmptyContext::EmptyContext()
	{
	}

	EmptyContext::~EmptyContext()
	{
	}


	Completer::Completer( const Commands& cmds_, const Pipe& pipe_ )
		: cmds( cmds_ ), pipe( pipe_ )
	{
	}

	Completer::~Completer()
	{
	}

	void
	Completer::complete( const string& input ) const
	{
		EmptyContext ctx;
		complete( ctx, input );
	}

	void
	Completer::complete( const Context& ctx, const string& input ) const
	{
		Context newCtx( ctx.expand( input ) );
		try {
			cmds.run( newCtx.render() );
		}
		catch( cmd_parser::command_not_found_error& e ) {
			acquire( newCtx );
		}
		catch( cmd_parser::wrong_signature_error& e ) {
			acquire( newCtx );
		}
	}

	void
	Completer::acquire( const Context& ctx ) const
	{
		string token;
		FeedPtr choiceFeed( cmds.choices( ctx.render() ) );
		if( choiceFeed ) {
			token = pipe.pump( *choiceFeed );
			complete( ctx, token );
		}
	}

}
