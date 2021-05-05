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

#include <oricad/core/creasepattern.h>
#include <oricad/core/creasepatternemptyutil.h>

namespace oricad {
namespace core {

std::unique_ptr<CreasePattern> CreasePatternEmptyUtil::square()
{
  auto cp = new CreasePattern();

  Point p1(0, 0);
  Point p2(1, 0);
  Point p3(1, 1);
  Point p4(0, 1);

  Curve s1(Segment(p1, p2), EdgeType::BORDER);
  Curve s2(Segment(p2, p3), EdgeType::BORDER);
  Curve s3(Segment(p3, p4), EdgeType::BORDER);
  Curve s4(Segment(p4, p1), EdgeType::BORDER);

  insert_non_intersecting_curve(*cp, s1);
  insert_non_intersecting_curve(*cp, s2);
  insert_non_intersecting_curve(*cp, s3);
  insert_non_intersecting_curve(*cp, s4);
  return std::unique_ptr<CreasePattern>(cp);
}

}
}
