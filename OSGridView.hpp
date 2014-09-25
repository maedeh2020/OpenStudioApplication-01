/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef SHAREDGUICOMPONENTS_OSGRIDVIEW_HPP
#define SHAREDGUICOMPONENTS_OSGRIDVIEW_HPP

#include <QWidget>
#include <QTimer>

#include "../openstudio_lib/OSItem.hpp"

#include "../model/ModelObject.hpp"

class QGridLayout;
class QLabel;
class QString;

namespace openstudio{

class ModelSubTabView;
class OSCollapsibleView;
class OSDropZone;
class OSGridController;
class OSItem;

class OSGridView : public QWidget
{
  Q_OBJECT

public:

  OSGridView(OSGridController * gridController,
    const QString & headerText,
    const QString & dropZoneText,
    bool useHeader,
    QWidget * parent = nullptr);

  virtual ~OSGridView() {};

  QGridLayout * m_gridLayout;

  OSDropZone * m_dropZone;

  virtual ModelSubTabView * modelSubTabView();

signals:

  void itemSelected(OSItem *);

  void dropZoneItemClicked(OSItem* item);

  void gridRowSelected(OSItem*);

public slots:

  void onSelectionCleared();

  void refreshAll();

  void refreshGrid();

  void refreshRow(int row);

  void requestRefreshAll();

  void requestRefreshGrid();

  void requestRefreshRow(int row);


private slots:

  void refreshCell(int row, int column);

  void deleteAll();

  void addWidget(int row, int column);

  void removeWidget(int row, int column);

  void setHorizontalHeader(std::vector<QWidget *> widgets);

  void setHorizontalHeader(std::vector<QString> names);

  void selectCategory(int index);

  void onDropZoneItemClicked(OSItem* item);

  void doRefresh();

  void doRowSelect();

private:

  enum RefreshType
  {
    RefreshAll,
    RefreshGrid
  };

  void setGridController(OSGridController * gridController);

  OSCollapsibleView * m_CollapsibleView;

  OSGridController * m_gridController;

  std::vector<RefreshType> m_refreshRequests;

  QTimer m_timer;
};

} // openstudio

#endif // SHAREDGUICOMPONENTS_OSGRIDVIEW_HPP
