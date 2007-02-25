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

#include "xmms2argumentvisitor.hpp"

#include "xmms2arguments.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace iimms2
{
	Xmms2ArgumentVisitor::Xmms2ArgumentVisitor( const Mario::Context& ctx_,
	                                            const Xmms::Client& client_ )
		: argument_completion_visitor( ctx_.render() ), ctx( ctx_ ),
		  client( client_ )
	{
	}

	Xmms2ArgumentVisitor::~Xmms2ArgumentVisitor()
	{
	}

	void
	Xmms2ArgumentVisitor::visit( const cmd_parser::_argument& obj )
	{
		cout << "x2av: _argument" << endl;
		argumentVisit( obj );
		//argumentVisit( dynamic_cast< const Xmms2BrowseArgument& >( obj ) );
	}

	void
	Xmms2ArgumentVisitor::visit( const Xmms2BrowseArgument& obj )
	{
		cout << "x2av: Xmms2BrowseArgument" << endl;
		argumentVisit( obj );
	}

	void
	Xmms2ArgumentVisitor::argumentVisit( const cmd_parser::_argument& obj )
	{
		cout << "x2av: v2: _argument" << endl;
		argument_completion_visitor::visit( obj );
	}

	void
	Xmms2ArgumentVisitor::argumentVisit( const Xmms2SearchArgument& obj )
	{
		cout << "x2av: v2: Xmms2SearchArgument" << endl;
		// FIXME: Do something here
		argument_completion_visitor::visit( obj );
	}

	void
	Xmms2ArgumentVisitor::argumentVisit( const Xmms2BrowseArgument& obj )
	{
		cout << "x2av: v2: Xmms2BrowseArgument" << endl;
		// FIXME: Do something here
		//argument_completion_visitor::visit( obj );
		std::string path;
		while( pos != end ) {
			path.append( *pos );
			++pos;
		}

		try {
			Xmms::List< Xmms::Dict > res = client.xform.browse( path );
			if( res.isValid() ) {
				alternatives.push_back( "*" );
			}
			for( ; res.isValid(); ++res ) {
				std::string file;
				if( res->contains( "realpath" ) ) {
					file = res->get< std::string >( "realpath" );
				}
				else {
					file = res->get< std::string >( "path" );
				}
				if( res->get< int >( "isdir" ) ) {
					file.append( "/" );
				}
				alternatives.push_back( file );
			}
		}
		catch( Xmms::result_error& ) {
			// Bad path, no completion
		}
	}

}
