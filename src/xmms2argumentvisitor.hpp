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

#ifndef IIMMS2_XMMS2ARGUMENTVISITOR_HPP
#define IIMMS2_XMMS2ARGUMENTVISITOR_HPP

#include <string>

#include <xmmsclient/xmmsclient++.h>

#include <boost/shared_ptr.hpp>

#include "cmd_parser/cmd_parser.h"
#include "mario/mario.hpp"

namespace iimms2
{

	class Xmms2SearchArgument;
	class Xmms2BrowseArgument;

	class Xmms2ArgumentVisitor : public cmd_parser::argument_completion_visitor
	{
		public:
			Xmms2ArgumentVisitor( const Mario::Context& ctx_, const Xmms::Client& client_ );
			~Xmms2ArgumentVisitor();

			void visit( const cmd_parser::_argument& obj );
			void visit( const Xmms2BrowseArgument& obj );

			virtual void argumentVisit( const cmd_parser::_argument& obj );
			virtual void argumentVisit( const Xmms2SearchArgument& obj );
			virtual void argumentVisit( const Xmms2BrowseArgument& obj );

		protected:
			const Mario::Context& ctx;
			const Xmms::Client& client;
	};

}

#endif // IIMMS2_XMMS2ARGUMENTVISITOR_HPP
