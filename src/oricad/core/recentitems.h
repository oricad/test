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

#ifndef INCLUDED_ORICAD_CORE_RECENTITEMS
#define INCLUDED_ORICAD_CORE_RECENTITEMS

#include <oricad/core/concepts/defaultconcept.h>
#include <oricad/core/export.h>

#include <immer/flex_vector.hpp>
#include <immer/flex_vector_transient.hpp>
#include <lager/util.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <variant>


namespace oricad {
namespace core {

struct ORICAD_CORE_EXPORT RecentItems
{
  using size_t = typename immer::flex_vector<std::string>::size_type;
  size_t max = 5;
  immer::flex_vector<std::string> items;

  RecentItems add(std::string item)
  {
    // TODO: use transient
    auto newItems = items;
    auto trans = items.transient();
    auto itr = std::find(trans.begin(), trans.end(), item);
    if (itr != trans.end()) {
      auto index = std::distance(trans.begin(), itr);
      newItems = newItems.erase(index);
    } else if (trans.size() >= max) {
      newItems = newItems.take(max - 1);
    }
    return {max, newItems.push_front(item)};
  }

  RecentItems clear()
  {
    return {max, {}};
  }

  RecentItems setMax(size_t max)
  {
    if (max == this->max)
      return {this->max, items};
    if (max <= items.size())
      return {max, items.take(max)};
    return {max, items};
  }
};


struct ORICAD_CORE_EXPORT ClearAction
{
  RecentItems operator()(RecentItems recent)
  {
    return recent.clear();
  }
};

struct ORICAD_CORE_EXPORT AddItem
{
  std::string item;

  RecentItems operator()(RecentItems recent)
  {
    return recent.add(item);
  }
};

struct ORICAD_CORE_EXPORT ChangeMaximum
{
  typename RecentItems::size_t max;

  RecentItems operator()(RecentItems recent)
  {
    return recent.setMax(max);
  }
};

template <>
struct DefaultConcept<RecentItems>
  : BasicConcept<RecentItems, std::variant<ClearAction, AddItem, ChangeMaximum>>
{};


}
}


#endif
