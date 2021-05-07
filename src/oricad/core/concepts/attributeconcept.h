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

#ifndef INCLUDED_ORICAD_CORE_ATTRIBUTECONCEPT
#define INCLUDED_ORICAD_CORE_ATTRIBUTECONCEPT

#include <oricad/core/concepts/attributeaction.h>
#include <oricad/core/concepts/defaultconcept.h>
#include <oricad/core/export.h>

namespace oricad {
namespace core {

template <auto attribute>
struct ORICAD_CORE_EXPORT DefaulAttributeConceptHelper;

template <typename Model, typename Attribute, Attribute Model::*attribute>
struct ORICAD_CORE_EXPORT DefaulAttributeConceptHelper<attribute>
{
  using type = DefaultConcept<Attribute>;
};

template <auto attribute>
using DefaulAttributeConceptHelper_t =
  typename DefaulAttributeConceptHelper<attribute>::type;

template <
  typename Model, typename Attribute, Attribute Model::*attribute,
  typename Concept = DefaultConcept<Attribute>>
struct ORICAD_CORE_EXPORT AttributeConceptHelper
  : BasicConcept<Model, AttributeAction<Model, Attribute, attribute, Concept>>
{};

template <
  auto attribute, typename Concept = DefaulAttributeConceptHelper_t<attribute>>
struct ORICAD_CORE_EXPORT AttributeConcept
{};

template <
  typename Model, typename Attribute, Attribute Model::*attribute,
  typename Concept>
struct ORICAD_CORE_EXPORT AttributeConcept<attribute, Concept>
  : AttributeConceptHelper<Model, Attribute, attribute, Concept>
{};

template <
  auto attribute, typename Concept = DefaulAttributeConceptHelper_t<attribute>>
typename AttributeConcept<attribute, Concept>::Action
makeAction(typename Concept::Action action)
{
  return typename AttributeConcept<attribute, Concept>::Action{action};
}

}
}

#endif
