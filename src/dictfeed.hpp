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

#ifndef IIMMS2_DICTFEED_HPP
#define IIMMS2_DICTFEED_HPP

#include <string>
#include <stdexcept>

#include <xmmsclient/xmmsclient++.h>

#include "mario/mario.hpp"


namespace iimms2
{

	class DictFeed : public Mario::Feed
	{
	public:
		DictFeed( const Xmms::List< Xmms::Dict >& dictlist, const std::string& key );
		~DictFeed();

		bool valid() const;
		std::string operator *() const;
		void operator ++();

	protected:
		Xmms::List< Xmms::Dict > dictlist;
		std::string key;
	};

}

#endif // IIMMS2_DICTFEED_HPP
