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

#ifndef INCLUDED_ORICAD_CORE_ENABLED
#define INCLUDED_ORICAD_CORE_ENABLED

#include <oricad/core/concepts/concept.h>

#include <lager/util.hpp>

#include <variant>

namespace oricad {
namespace core {

/*template <typename T>
struct Enabled
{
  bool enabled = true;
  T value;
};

struct Enable
{};

struct Disable
{};

struct Toggle
{};

struct SetEnabled
{
  bool enabled;
};

template <typename T>
struct EnabledValueAction
{
  typename Concept<T>::Action action;
};

template <typename T>
struct EnabledReducer
{
  static Enabled<T> update(Enabled<T> enabled, typename
Concept<Enabled<T>>::Action action) { return lager::match(std::move(action))(
      [&](EnabledValueAction<T>&& a) {
        if (!enabled.enabled)
          return enabled;
        return {enabled.enabled, Concept<T>::Reducer::update(enabled.value,
a.action)};
      },
      [&](Enable&& a) {
        if (enabled.enabled)
          return enabled;
        return {true, enabled.value};
      },
      [&](Disable&& a) {
        if (!enabled.enabled)
          return enabled;
        return {false, enabled.value};
      },
      [&](Toggle&& a) {
        return {!enabled.enabled, enabled.value};
      },
      [&](SetEnabled&& a) {
        if (enabled.enabled == a.enabled)
          return enabled;
        return {a.enabled, enabled.value};
      }
    );
  }
};

template <typename T>
struct Concept<Enabled<T>>
{
  using Action = std::variant<EnabledValueAction<T>, Enable, Disable, Toggle,
SetEnabled>; using Model = Enabled<T>; using Reducer = EnabledReducer<T>;
};

*/

}
}

#endif
