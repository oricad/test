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

#ifndef INCLUDED_ORICAD_CORE_DOCUMENTMANAGER
#define INCLUDED_ORICAD_CORE_DOCUMENTMANAGER

#include <oricad/core/concepts/component.h>
#include <oricad/core/concepts/reducer.h>
#include <oricad/core/document.h>
#include <oricad/core/documentioservice.h>
#include <oricad/core/export.h>

#include <immer/box.hpp>
#include <immer/flex_vector.hpp>
#include <immer/map.hpp>
#include <lager/context.hpp>

#include <functional>
#include <map>
#include <string>

namespace oricad {
namespace core {

struct SaveDocument;
struct SaveDocumentAs;
struct SaveDone;
struct CloseDocument;
struct OpenDocument;
struct LoadDocument;
struct LoadDone;
struct NewDocument;

struct DocumentManager;

template <>
struct ORICAD_CORE_EXPORT Component<DocumentManager>
{
  using Model_t = DocumentManager;
  using Action_t = std::variant<
    SaveDocument, SaveDocumentAs, SaveDone, CloseDocument, OpenDocument,
    LoadDocument, LoadDone, NewDocument>;
  using Deps_t = lager::deps<DocumentIOService&>;
  using Effect_t = lager::effect<Action_t, Deps_t>;
  using Result_t = std::pair<Model_t, Effect_t>;
  using Reducer_t = Reducer<Model_t, Result_t, Action_t>;

  using Context_t = lager::context<Action_t, Deps_t>;
};

struct ORICAD_CORE_EXPORT DocumentId
{
  immer::box<std::string> path;
  bool temporary = false;
};

bool operator==(const DocumentId& lhs, const DocumentId& rhs);

struct DocumentKeyValue
{
  DocumentId key;
  Document value;
};

struct ORICAD_CORE_EXPORT DocumentManager
{
  using Documents = immer::map<DocumentId, Document>;

  Documents documents;
  DocumentId activeDocumentId;

  DocumentManager setDocument(DocumentId id, Document document);
};


struct ORICAD_CORE_EXPORT SaveDocument
{
  DocumentId id;


  Component<DocumentManager>::Result_t operator()(DocumentManager);


  Component<DocumentManager>::Effect_t saveTemporaryFileEffect();
  Component<DocumentManager>::Effect_t
  saveRegularFileEffect(std::string contents, std::string path);
};

struct ORICAD_CORE_EXPORT SaveDocumentAs
{
  DocumentId id;
  std::optional<std::string> path;

  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT SaveDone
{
  DocumentId id;

  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT CloseDocument
{
  DocumentId id;

  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT NewDocument
{
  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT OpenDocument
{
  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT LoadDocument
{
  std::string path;

  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

struct ORICAD_CORE_EXPORT LoadDone
{
  DocumentId id;
  std::string contents;

  Component<DocumentManager>::Result_t operator()(DocumentManager);
};

}
}

namespace std {

template <>
struct hash<oricad::core::DocumentId>
{
  std::size_t operator()(const oricad::core::DocumentId& id) const
  {
    std::size_t h1 = std::hash<immer::box<std::string>>{}(id.path);
    std::size_t h2 = std::hash<bool>{}(id.temporary);
    return h1 ^ (h2 << 1);
  }
};

}

#endif
