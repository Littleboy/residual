/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#ifndef GRIM_COLORMAP_H
#define GRIM_COLORMAP_H

#include "common/endian.h"

#include "engines/grim/resource.h"
#include "engines/grim/object.h"

namespace Grim {

class CMap : public Object {
	GRIM_OBJECT(ColorMap)
public:
	// Load a colormap from the given data.
	CMap(const char *fileName, const char *data, int len) :
		Object() {
		_fname = fileName;
		if (len < 4 || READ_BE_UINT32(data) != MKTAG('C','M','P',' '))
			error("Invalid magic loading colormap");
		memcpy(_colors, data + 64, sizeof(_colors));
	}
	CMap() : Object() {}
	~CMap() {
		if (g_resourceloader)
			g_resourceloader->uncacheColormap(this);
	}
	const char *filename() const { return _fname.c_str(); }

	// The color data, in RGB format
	char _colors[256 * 3];
	Common::String _fname;

	bool operator==(const CMap &c) const {
		if (_fname != c._fname) {
			return false;
		}

		return true;
	}
};

} // end of namespace Grim

#endif
