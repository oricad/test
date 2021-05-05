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

#include <oricad/gui/qtdocumentioservice.h>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include <gsl/gsl>

namespace oricad {
namespace gui {

void QtDocumentIOService::saveDocumentContents(
  std::string contents, std::string path)
{
  QString fileName = QString::fromStdString(path);
  Expects(!fileName.isEmpty());

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::information(
      nullptr, tr("Unable to open file"), file.errorString());
    return;
  }
  QDataStream out(&file);
  out << QString::fromStdString(contents);
}

std::string QtDocumentIOService::loadDocumentContents(std::string path)
{
  QString fileName = QString::fromStdString(path);
  Expects(!fileName.isEmpty());

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(
      nullptr, tr("Unable to open file"), file.errorString());
    return "";  // TODO: error handling
  }
  QDataStream in(&file);
  QString contents;
  in >> contents;
  return contents.toStdString();
}

std::string QtDocumentIOService::getOpenFileName()
{
  QString fileName = QFileDialog::getOpenFileName(
    nullptr, tr("Open document"), "", tr("Documents (*.txt);;All Files (*)"));
  return fileName.toStdString();
}

std::string QtDocumentIOService::getSaveFileName()
{
  QString fileName = QFileDialog::getSaveFileName(
    nullptr, tr("Save document"), "", tr("Document (*.txt);;All Files (*)"));
  return fileName.toStdString();
}

}
}
