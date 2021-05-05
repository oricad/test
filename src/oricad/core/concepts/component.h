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

#ifndef INCLUDED_ORICAD_CORE_COMPONENT
#define INCLUDED_ORICAD_CORE_COMPONENT

namespace oricad {
namespace core {

template <typename Model, typename Action, typename Result, typename Reducer>
struct FullComponent
{
  using Model_t = Model;
  using Action_t = Action;
  using Result_t = Result;
  using Reducer_t = Reducer;
};

template <typename Model>
struct Component;

}
}

#endif
