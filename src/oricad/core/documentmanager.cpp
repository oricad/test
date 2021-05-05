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

#include <oricad/core/documentioservice.h>
#include <oricad/core/documentmanager.h>

#include <lager/context.hpp>
#include <lager/deps.hpp>

#include <gsl/gsl>
#include <iostream>

namespace oricad {
namespace core {

DocumentManager DocumentManager::setDocument(DocumentId id, Document document)
{
  documents = documents.set(id, document);
  return *this;
}

using Result = typename Component<DocumentManager>::Result_t;
using Effect = typename Component<DocumentManager>::Effect_t;

Result SaveDocument::operator()(DocumentManager manager)
{
  auto document = manager.documents.find(id);
  if (document == nullptr) {
    return {manager, lager::noop};
  }
  if (!document->hasUnsavedContents()) {
    return {manager, lager::noop};
  }
  if (std::holds_alternative<TemporaryFile>(document->from)) {
    TemporaryFile file = std::get<TemporaryFile>(document->from);
    SavingTemporaryFile newFile{file.name, file.contents};
    return {
      manager.setDocument(id, Document{newFile, document->contents}),
      saveTemporaryFileEffect()};
  } else if (std::holds_alternative<RegularFile>(document->from)) {
    RegularFile file = std::get<RegularFile>(document->from);
    SavingFile newFile{file.path, file.contents};
    return {
      manager.setDocument(id, Document{newFile, document->contents}),
      saveRegularFileEffect(document->contents, file.path)};
  }

  std::cout << "Trying to save a loading/saving file" << std::endl;
  return {manager, lager::noop};
}

Effect SaveDocument::saveTemporaryFileEffect()
{
  return [&](auto&& ctx) {
    auto& io = lager::get<DocumentIOService&>(ctx);
    std::string fileName = io.getSaveFileName();
    ctx.dispatch(SaveDocumentAs{id, fileName});
  };
}

Effect
SaveDocument::saveRegularFileEffect(std::string contents, std::string path)
{
  return [&](auto&& ctx) {
    DocumentIOService& io = lager::get<DocumentIOService&>(ctx);
    io.saveDocumentContents(contents, path);
    ctx.dispatch(SaveDone{id});
  };
}

Result SaveDocumentAs::operator()(DocumentManager manager)
{
  auto document = manager.documents.find(id);
  if (document == nullptr) {
    return {manager, lager::noop};
  }
  if (
    std::holds_alternative<TemporaryFile>(document->from)
    || std::holds_alternative<RegularFile>(document->from))
  {
    if (!path.has_value()) {
      return {manager, [&](auto&& ctx) {
                auto& io = lager::get<DocumentIOService&>(ctx);
                ctx.dispatch(SaveDocumentAs{id, io.getSaveFileName()});
              }};
    }
    std::string oldContents =
      std::holds_alternative<TemporaryFile>(document->from)
      ? std::get<TemporaryFile>(document->from).contents
      : std::get<RegularFile>(document->from).contents;

    SavingFile newFile{path.value(), oldContents, document->contents};
    return {
      DocumentManager{
        manager.documents.set(id, Document{newFile, document->contents}),
        manager.activeDocumentId},
      [this, document](auto&& ctx) {
        auto& io = lager::get<DocumentIOService&>(ctx);
        io.saveDocumentContents(document->contents, path.value());
        ctx.dispatch(SaveDone{id});
      }};
  }
  std::cout << "Trying to save a loading/saving file" << std::endl;
  return {manager, lager::noop};
}

Result SaveDone::operator()(DocumentManager manager)
{
  auto document = manager.documents.find(id);
  if (document == nullptr) {
    return {manager, lager::noop};
  }
  if (!std::holds_alternative<SavingFile>(document->from)) {
    return {manager, lager::noop};
  }

  SavingFile file = std::get<SavingFile>(document->from);
  RegularFile newFile{file.path, file.newContents};

  return {
    DocumentManager{
      manager.documents.set(id, Document{newFile, document->contents})},
    lager::noop};
}

Result CloseDocument::operator()(DocumentManager manager)
{
  auto document = manager.documents.find(id);
  if (document == nullptr) {
    return {manager, lager::noop};
  }
  if (
    std::holds_alternative<TemporaryFile>(document->from)
    || std::holds_alternative<RegularFile>(document->from))
  {
    bool dirty = std::holds_alternative<TemporaryFile>(document->from)
      ? std::get<TemporaryFile>(document->from).contents != document->contents
      : std::get<RegularFile>(document->from).contents != document->contents;
    if (dirty) {
      // ask whether to save
    }
    // TODO: update activeDocumentId
    return {
      DocumentManager{manager.documents.erase(id), manager.activeDocumentId},
      lager::noop};
  }
  std::cout << "Cannot close while saving/loading" << std::endl;
  return {manager, lager::noop};
}

Result OpenDocument::operator()(DocumentManager manager)
{
  return {manager, [](auto&& ctx) {
            auto& io = lager::get<DocumentIOService&>(ctx);
            std::string fileName = io.getOpenFileName();
            // TODO: if valid file
            ctx.dispatch(LoadDocument{fileName});
          }};
}

Result LoadDocument::operator()(DocumentManager manager)
{
  // generate a new id
  // TODO: very rudimentary id generation
  static DocumentManager::DocumentId id = 0;
  ++id;
  LoadingFile file{path};

  // "" should std::null_opt or empty list or whatever
  return {
    DocumentManager{
      manager.documents.set(id, Document{file, ""}), manager.activeDocumentId},
    [this](auto&& ctx) {
      DocumentIOService& io = lager::get<DocumentIOService&>(ctx);
      ctx.dispatch(LoadDone{id, io.loadDocumentContents(path)});
    }};
}

Result LoadDone::operator()(DocumentManager manager)
{
  auto document = manager.documents.find(id);
  if (!std::holds_alternative<LoadingFile>(document->from)) {
    return {manager, lager::noop};
  }
  LoadingFile file = std::get<LoadingFile>(document->from);
  RegularFile newFile{file.path, contents};

  return {
    DocumentManager{
      manager.documents.set(id, Document{newFile, contents}),
      manager.activeDocumentId},
    lager::noop};
}

Result NewDocument::operator()(DocumentManager manager)
{
  static DocumentManager::DocumentId id = 1000;
  ++id;
  return {
    DocumentManager{
      manager.documents.set(id, Document{TemporaryFile{"Untitled", ""}, ""}),
      manager.activeDocumentId},
    lager::noop};
}

}
}
