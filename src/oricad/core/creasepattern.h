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

#ifndef INCLUDED_ORICAD_CORE_CREASEPATTERN
#define INCLUDED_ORICAD_CORE_CREASEPATTERN

#include <oricad/core/export.h>

#include <CGAL/Arr_curve_data_traits_2.h>
#include <CGAL/Arr_linear_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

namespace oricad {
namespace core {

enum class EdgeType
{
  BORDER,
  MOUNTAIN,
  VALLEY,
  UNFOLD,
  AUXILIARY,
  UNKNOWN,
  CUT
};

struct ORICAD_CORE_EXPORT MergeEdgeTypes
{
  EdgeType operator()(const EdgeType t1, const EdgeType t2) const
  {
    return t1 == t2 ? t1 : EdgeType::UNKNOWN;
  }
};

using ExactKernel = CGAL::Exact_predicates_exact_constructions_kernel;
using BaseTraits = CGAL::Arr_linear_traits_2<ExactKernel>;
using Traits =
  CGAL::Arr_curve_data_traits_2<BaseTraits, EdgeType, MergeEdgeTypes>;


using Segment = BaseTraits::X_monotone_curve_2;
using Point = Traits::Point_2;
using Curve = Traits::Curve_2;


using CreasePattern = CGAL::Arrangement_2<Traits>;

}
}

#endif
