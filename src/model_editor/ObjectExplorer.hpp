/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef MODELEDITOR_OBJECTEXPLORER_HPP
#define MODELEDITOR_OBJECTEXPLORER_HPP

#include <QWidget>

#include <openstudio/utilities/idf/IdfFile.hpp>

class QLineEdit;
class QListWidget;

class ListWidget;

namespace modeleditor
{

class ObjectExplorer : public QWidget
{
  Q_OBJECT

public:
  ObjectExplorer(openstudio::IddFile& iddFile, QWidget * parent = nullptr);
  virtual ~ObjectExplorer();
  void updateIddFile();

public slots:
  void on_groupTextEdited(const QString&);
  void on_objectTextEdited(const QString&);
  void on_groupItemSelectionChanged();
  void on_objectItemSelectionChanged();

signals:

protected:

private:
  void createWidgets();
  void connectSignalsAndSlots();
  void createLayout();
  void groupTextEdited(const QString& text);
  void objectTextEdited(const QString& text);
  void groupItemSelectionChanged();
  void objectItemSelectionChanged();

  QLineEdit * mGroupEdit;
  QLineEdit * mObjectEdit;
  QListWidget * mGroupList;
  ListWidget * mObjectList;
  openstudio::IddFile mIddFile;
};

} // namespace modeleditor

#endif // MODELEDITOR_OBJECTEXPLORER_HPP
