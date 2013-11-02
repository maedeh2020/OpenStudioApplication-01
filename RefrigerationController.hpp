/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.  
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

#ifndef OPENSTUDIO_REFRIGERATIONCONTROLLER_H
#define OPENSTUDIO_REFRIGERATIONCONTROLLER_H

#include <QObject>
#include "../shared_gui_components/OSListController.hpp"

namespace openstudio {

class RefrigerationSystemGridItem;
class RefrigerationSystemListController;
class RefrigerationScene;

class RefrigerationController : public QObject
{
  Q_OBJECT

  public:

  RefrigerationController();

  QSharedPointer<RefrigerationScene> refrigerationScene() const;

  private:

  QSharedPointer<RefrigerationSystemGridItem> m_refrigerationSystemGridItem;

  QSharedPointer<RefrigerationSystemListController> m_refrigerationSystemListController;

  QSharedPointer<RefrigerationScene> m_refrigerationScene;
};

class RefrigerationSystemListController : public OSListController
{
  Q_OBJECT

  public:

  QSharedPointer<OSListItem> itemAt(int i);

  int count();
};

class RefrigerationSystemListItem : public OSListItem
{
  Q_OBJECT

  public:

  RefrigerationSystemListItem(OSListController * listController = 0);

  virtual ~RefrigerationSystemListItem() {}
};

} // openstudio

#endif // OPENSTUDIO_REFRIGERATIONCONTROLLER_H

