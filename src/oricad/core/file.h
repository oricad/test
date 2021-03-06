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

#ifndef INCLUDED_ORICAD_CORE_FILE
#define INCLUDED_ORICAD_CORE_FILE

#include <oricad/core/export.h>

#include <immer/box.hpp>

#include <string>
#include <variant>

namespace oricad {
namespace core {

struct ORICAD_CORE_EXPORT TemporaryFile
{
  std::string contents;
};

bool operator==(const TemporaryFile& lhs, const TemporaryFile& rhs);

struct ORICAD_CORE_EXPORT RegularFile
{
  std::string contents;
};

bool operator==(const RegularFile& lhs, const RegularFile& rhs);

struct ORICAD_CORE_EXPORT SavingFile
{
  std::string oldContents;
  std::string newContents;
};

bool operator==(const SavingFile& lhs, const SavingFile& rhs);

struct ORICAD_CORE_EXPORT SavingTemporaryFile
{
  std::string contents;
};

bool operator==(const SavingTemporaryFile& lhs, const SavingTemporaryFile& rhs);

struct ORICAD_CORE_EXPORT LoadingFile
{};

bool operator==(const LoadingFile& lhs, const LoadingFile& rhs);

using File = std::variant<
  TemporaryFile, RegularFile, SavingFile, LoadingFile, SavingTemporaryFile>;

}
}

#endif
