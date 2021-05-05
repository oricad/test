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

#include <oricad/core/file.h>

namespace oricad {
namespace core {

bool operator==(const TemporaryFile& lhs, const TemporaryFile& rhs)
{
  return lhs.name == rhs.name && lhs.contents == rhs.contents;
}

bool operator==(const RegularFile& lhs, const RegularFile& rhs)
{
  return lhs.path == rhs.path && lhs.contents == rhs.contents;
}

bool operator==(const SavingFile& lhs, const SavingFile& rhs)
{
  return lhs.path == rhs.path && lhs.oldContents == rhs.oldContents
    && lhs.newContents == rhs.newContents;
}

bool operator==(const SavingTemporaryFile& lhs, const SavingTemporaryFile& rhs)
{
  return lhs.name == rhs.name && lhs.contents == rhs.contents;
}


bool operator==(const LoadingFile& lhs, const LoadingFile& rhs)
{
  return lhs.path == rhs.path;
}

}
}
