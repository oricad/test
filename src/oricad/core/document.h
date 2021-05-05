/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright 2021 Simon Marynissen <marynissen.simon@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INCLUDED_ORICAD_CORE_DOCUMENT
#define INCLUDED_ORICAD_CORE_DOCUMENT

#include <oricad/core/file.h>

#include <string>

namespace oricad {
namespace core {

struct Document
{
  File from;
  std::string contents;
  // history stuff here

  // unsaved stuff if from.contents != contents (in case of a non-loading file)
  bool hasUnsavedContents() const;
};


bool operator==(const Document& lhs, const Document& rhs);

}
}

#endif
