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

#ifndef INCLUDED_ORICAD_CORE_GENERALCONCEPT
#define INCLUDED_ORICAD_CORE_GENERALCONCEPT

#include <oricad/core/concepts/aggregatedattributesconcept.h>
#include <oricad/core/concepts/attributeconcept.h>

#include <lager/util.hpp>

#include <iostream>
#include <type_traits>
#include <variant>

namespace oricad {
namespace core {

struct TestSub
{
  bool second;
};

struct Test
{
  bool first;
  bool other;
  TestSub sub;
};

// GeneralConcept<Test> should be the aggregation of
// GeneralConcept<bool> and GeneralConcept<bool>


using TestConcept =
  AggregatedAttributesConcept<Test, &Test::first, &Test::other>;

struct TestItOut
{
  static void tester2()
  {
    Test t = {true, true};

    // AttributeConcept<&Test::first>::Action act(Toggle{});
    // TestConcept::Action act(Toggle {});
    // t = TestConcept::Reducer::update(t, act);

    std::cout << "First: " << t.first << " and other: " << t.other
              << " and second: " << t.sub.second << std::endl;
  }

  static void tester()
  {
    /*Test t {true, true};
    t = BasicReducer<Test, TestAction>::update(
        t,
        makeAction<Test, bool, &Test::other>(Toggle {})
    );
    std::cout << "Success: " << std::is_same_v<DefaultConcept<bool>::Result,
    bool> << std::endl;
    // dispatch(makeAction<Test, bool, &Test::other>(Toggle {}));
    std::cout << "Other is toggled to false" << t.other << std::endl;
    std::cout << "First is unaltered: " << t.first << std::endl;
    */
  }
};


}
}

#endif  // GENERALCONCEPT_H
