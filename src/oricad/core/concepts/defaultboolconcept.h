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

#ifndef INCLUDED_ORICAD_CORE_DEFAULTBOOLCONCEPT
#define INCLUDED_ORICAD_CORE_DEFAULTBOOLCONCEPT

#include <oricad/core/concepts/defaultconcept.h>

#include <variant>

namespace oricad {
namespace core {

struct Toggle
{
  bool operator()(bool model)
  {
    return !model;
  }
};

struct SetTrue
{
  bool operator()(bool model)
  {
    return true;
  }
};

struct SetFalse
{
  bool operator()(bool model)
  {
    return false;
  }
};

template <>
struct DefaultConcept<bool>
  : public BasicConcept<
      bool, std::variant<SetValue<bool>, Toggle, SetTrue, SetFalse>>
{};

}
}

#endif
