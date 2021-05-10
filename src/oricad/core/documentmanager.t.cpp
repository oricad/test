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

#include <catch2/catch_all.hpp>


SCENARIO( "vectors can be sized and resized", "[DocumentManager]" ) {
  GIVEN( "A vector with some items" ) {
    std::vector<int> v( 5 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    WHEN( "the size is increased" ) {
      v.resize( 10 );

      THEN( "the size and capacity change" ) {
        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
      }
    }
    WHEN( "the size is reduced" ) {
      v.resize( 0 );

      THEN( "the size changes but not capacity" ) {
        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
      }
    }
    WHEN( "more capacity is reserved" ) {
      v.reserve( 10 );

      THEN( "the capacity changes but not the size" ) {
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 10 );
      }
    }
    WHEN( "less capacity is reserved" ) {
      v.reserve( 0 );

      THEN( "neither size nor capacity are changed" ) {
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
      }
    }
  }
}
