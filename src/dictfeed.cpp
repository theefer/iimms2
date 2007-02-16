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

#include "dictfeed.hpp"

using std::string;
using std::runtime_error;

using namespace Xmms;


namespace iimms2
{

	DictFeed::DictFeed( const List< Dict >& dictlist_, const string& key_ )
		: dictlist( dictlist_ ), key( key_ )
	{
		// Move to first valid entry
		if( dictlist.isValid() ) {
			++dictlist;
		}
	}

	DictFeed::~DictFeed()
	{
	}

	void
	DictFeed::first()
	{
		return dictlist.first();
	}

	bool
	DictFeed::valid() const
	{
		return dictlist.isValid();
	}

	string
	DictFeed::operator *() const
	{
		if( (*dictlist).contains( key ) ) {
			return dictlist->get< string >( key );
		}

		throw runtime_error( "invalid dereference of key " + key + " in dictfeed!" );
	}

	void
	DictFeed::operator ++()
	{
		++dictlist;
	}

}
