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

#ifndef MARIO_MARIO_HPP
#define MARIO_MARIO_HPP

#include <string>
#include <list>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "cmd_parser/cmd_parser.h"


namespace Mario
{

	class Feed;
	typedef boost::shared_ptr< Feed > FeedPtr;


	class Pipe
	{
	public:
		Pipe();
		virtual ~Pipe();

		// FIXME: arg should be const?
		std::string pump( Feed& feed ) const;

	protected:
		virtual void dispatch() const = 0;
	};


	class AppPipe : public Pipe
	{
	public:
		AppPipe( const std::string& path, const std::string& name,
		         const std::vector< std::string >& args );
		~AppPipe();

	protected:
		std::string path;
		std::string name;
		std::vector< std::string > args;

		void dispatch() const;
	};


	class Feed
	{
	public:
		Feed();
		virtual ~Feed();

		virtual void first() = 0;
		virtual bool valid() const = 0;
		virtual std::string operator *() const = 0;
		virtual void operator ++() = 0;
	};


	class StringListFeed : public Feed
	{
	public:
		StringListFeed();
		~StringListFeed();

		void push_back( const std::string& str );

		void first();
		bool valid() const;
		std::string operator *() const;
		void operator ++();

	protected:
		std::list< std::string > stringlist;
		std::list< std::string >::const_iterator pos;
	};


	class Commands
	{
	public:
		Commands();
		virtual ~Commands();

		void run( const std::string& input ) const;
		virtual FeedPtr choices( const std::string& input ) const = 0;

	protected:
		cmd_parser::interpreter inter;

	};


	class Context
	{
	public:
		Context( const Context& ctx );
		virtual ~Context();

		Context expand( const std::string& more ) const;
		std::string render() const;

	protected:
		Context();

		std::list< std::string > env;
	};


	class EmptyContext : public Context
	{
	public:
		EmptyContext();
		~EmptyContext();
	};


	class Completer
	{
	public:
		Completer( const Commands& cmds_, const Pipe& pipe_ );
		~Completer();

		void complete( const std::string& input ) const;
		void complete( const Context& ctx, const std::string& input ) const;

	private:
		const Commands& cmds;
		const Pipe& pipe;

		void acquire( const Context& ctx ) const;
	};

}

#endif // MARIO_MARIO_HPP
