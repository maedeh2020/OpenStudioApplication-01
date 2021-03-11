/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2020-2020, OpenStudio Coalition and other contributors. All rights reserved.
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

#include "OSCheckBox.hpp"

#include <openstudio/model/ModelObject.hpp>
#include <openstudio/model/ModelObject_Impl.hpp>

#include <QString>
#include <QFocusEvent>
#include <QStyle>

namespace openstudio {

OSCheckBox3::OSCheckBox3(QWidget* parent) : QCheckBox(parent) {
  this->setCheckable(true);

  this->setProperty("defaulted", false);
  this->setProperty("focused", false);
  this->setStyleSheet("QCheckBox[defaulted=\"true\"][focused=\"true\"] { color:green; background:#ffc627; } "
                      "QCheckBox[defaulted=\"true\"][focused=\"false\"] { color:green; background:white; } "
                      "QCheckBox[defaulted=\"false\"][focused=\"true\"] { color:black; background:#ffc627; } "
                      "QCheckBox[defaulted=\"false\"][focused=\"false\"] { color:black; background:white; } ");

  setEnabled(false);
}

OSCheckBox3::~OSCheckBox3() {}

void OSCheckBox3::bind(const model::ModelObject& modelObject, BoolGetter get, boost::optional<BoolSetter> set, boost::optional<NoFailAction> reset,
                       boost::optional<BasicQuery> isDefaulted) {
  m_modelObject = modelObject;
  m_get = get;
  m_set = set;
  m_reset = reset;
  m_isDefaulted = isDefaulted;

  setEnabled(true);

  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
    .get()
    ->openstudio::model::detail::ModelObject_Impl::onChange.connect<OSCheckBox3, &OSCheckBox3::onModelObjectChange>(this);
  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
    .get()
    ->openstudio::model::detail::ModelObject_Impl::onRemoveFromWorkspace.connect<OSCheckBox3, &OSCheckBox3::onModelObjectRemove>(this);

  connect(this, &OSCheckBox3::toggled, this, &OSCheckBox3::onToggled);
  bool checked = (*m_get)();

  this->setChecked(checked);
}

void OSCheckBox3::bind(const model::ModelObject& modelObject, BoolGetter get, boost::optional<BoolSetterBoolReturn> set,
                       boost::optional<NoFailAction> reset, boost::optional<BasicQuery> isDefaulted) {
  m_modelObject = modelObject;
  m_get = get;
  m_setBoolReturn = set;
  m_reset = reset;
  m_isDefaulted = isDefaulted;

  setEnabled(true);

  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->onChange.connect<OSCheckBox3, &OSCheckBox3::onModelObjectChange>(this);

  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
    .get()
    ->onRemoveFromWorkspace.connect<OSCheckBox3, &OSCheckBox3::onModelObjectRemove>(this);

  connect(this, &OSCheckBox3::toggled, this, &OSCheckBox3::onToggled);
  bool checked = (*m_get)();

  this->setChecked(checked);
}

void OSCheckBox3::enableClickFocus() {
  this->setFocusPolicy(Qt::ClickFocus);
}

void OSCheckBox3::setLocked(bool locked) {
  setEnabled(!locked);
}

void OSCheckBox3::unbind() {
  if (m_modelObject) {
    m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->onChange.disconnect<OSCheckBox3, &OSCheckBox3::onModelObjectChange>(
      this);
    m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
      .get()
      ->onRemoveFromWorkspace.disconnect<OSCheckBox3, &OSCheckBox3::onModelObjectRemove>(this);

    m_get.reset();
    m_set.reset();
    m_setBoolReturn.reset();
    m_reset.reset();
    m_isDefaulted.reset();
    setEnabled(false);
  }
}

void OSCheckBox3::onToggled(bool checked) {
  emit inFocus(true, true);  // fake that is has data
  if (m_modelObject && m_set) {
    if ((*m_get)() != checked) {
      (*m_set)(checked);
    }
  } else if (m_modelObject && m_setBoolReturn) {
    if ((*m_get)() != checked) {
      (*m_setBoolReturn)(checked);
    }
  }
}

void OSCheckBox3::onModelObjectChange() {
  if (m_modelObject) {
    if ((*m_get)() != this->isChecked()) {
      this->blockSignals(true);
      this->setChecked((*m_get)());
      this->blockSignals(false);
    }
  }
}

void OSCheckBox3::onModelObjectRemove(const Handle& handle) {
  unbind();
}

bool OSCheckBox3::defaulted() const {
  bool result = false;
  if (m_isDefaulted) {
    result = (*m_isDefaulted)();
  }
  return result;
}

void OSCheckBox3::updateStyle() {
  this->style()->unpolish(this);
  this->style()->polish(this);
}

void OSCheckBox3::focusInEvent(QFocusEvent* e) {
  if ((e->reason() == Qt::MouseFocusReason) && (this->focusPolicy() == Qt::ClickFocus)) {
    this->setProperty("focused", true);
    updateStyle();

    emit inFocus(true, true);
  }
  QWidget::focusInEvent(e);
}

void OSCheckBox3::focusOutEvent(QFocusEvent* e) {
  if ((e->reason() == Qt::MouseFocusReason) && (this->focusPolicy() == Qt::ClickFocus)) {
    this->setProperty("focused", false);
    updateStyle();

    emit inFocus(false, false);
  }
  // Pass it on for further processing
  QWidget::focusOutEvent(e);
}

OSCheckBox2::OSCheckBox2(QWidget* parent) : QPushButton(parent) {
  setObjectName("StandardGrayButton");
  this->setAcceptDrops(false);

  this->setCheckable(true);

  setEnabled(false);

  this->setProperty("defaulted", false);
  this->setProperty("focused", false);
  this->setStyleSheet("QLineEdit[defaulted=\"true\"][focused=\"true\"] { color:green; background:#ffc627; } "
                      "QLineEdit[defaulted=\"true\"][focused=\"false\"] { color:green; background:white; } "
                      "QLineEdit[defaulted=\"false\"][focused=\"true\"] { color:black; background:#ffc627; } "
                      "QLineEdit[defaulted=\"false\"][focused=\"false\"] { color:black; background:white; } ");
}

void OSCheckBox2::bind(const model::ModelObject& modelObject, BoolGetter get, boost::optional<BoolSetter> set, boost::optional<NoFailAction> reset,
                       boost::optional<BasicQuery> isDefaulted) {
  m_modelObject = modelObject;
  m_get = get;
  m_set = set;
  m_reset = reset;
  m_isDefaulted = isDefaulted;

  setEnabled(true);

  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->onChange.connect<OSCheckBox2, &OSCheckBox2::onModelObjectChange>(this);

  m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
    .get()
    ->onRemoveFromWorkspace.connect<OSCheckBox2, &OSCheckBox2::onModelObjectRemove>(this);

  connect(this, &OSCheckBox2::toggled, this, &OSCheckBox2::onToggled);
  bool checked = (*m_get)();

  this->setChecked(checked);
}

void OSCheckBox2::unbind() {
  if (m_modelObject) {
    m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->onChange.disconnect<OSCheckBox2, &OSCheckBox2::onModelObjectChange>(
      this);
    m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()
      .get()
      ->onRemoveFromWorkspace.disconnect<OSCheckBox2, &OSCheckBox2::onModelObjectRemove>(this);

    m_get.reset();
    m_set.reset();
    m_reset.reset();
    m_isDefaulted.reset();
    setEnabled(false);
  }
}

void OSCheckBox2::focusInEvent(QFocusEvent* e) {
  if ((e->reason() == Qt::MouseFocusReason) && (this->focusPolicy() == Qt::ClickFocus)) {
    this->setProperty("focused", true);
    updateStyle();

    emit inFocus(true, true);
  }
  QWidget::focusInEvent(e);
}

void OSCheckBox2::focusOutEvent(QFocusEvent* e) {
  if ((e->reason() == Qt::MouseFocusReason) && (this->focusPolicy() == Qt::ClickFocus)) {
    this->setProperty("focused", false);
    updateStyle();

    emit inFocus(false, false);
  }
  // Pass it on for further processing
  QWidget::focusOutEvent(e);
}

void OSCheckBox2::onToggled(bool checked) {
  if (m_modelObject && m_set) {
    if ((*m_get)() != checked) {
      (*m_set)(checked);
    }
  }
}

void OSCheckBox2::onModelObjectChange() {
  if (m_modelObject) {
    this->setChecked((*m_get)());
  }
}

void OSCheckBox2::onModelObjectRemove(const Handle& handle) {
  unbind();
}

bool OSCheckBox2::defaulted() const {
  bool result = false;
  if (m_isDefaulted) {
    result = (*m_isDefaulted)();
  }
  return result;
}

void OSCheckBox2::updateStyle() {
  this->style()->unpolish(this);
  this->style()->polish(this);
}

// OSCheckBox::OSCheckBox( QWidget * parent )
//   : QPushButton(parent)
// {
//   setObjectName("StandardGrayButton");
//   this->setAcceptDrops(false);

//   this->setCheckable(true);

//   setEnabled(false);
// }

// void OSCheckBox::bind(model::ModelObject & modelObject, const char * property)
// {
//   m_modelObject = modelObject;

//   m_property = property;

//   setEnabled(true);

//   m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->openstudio::model::detail::ModelObject_Impl::onChange.connect<OSCheckBox, &OSCheckBox::onModelObjectChange>(this);

//   m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get()->openstudio::model::detail::ModelObject_Impl::onRemoveFromWorkspace.connect<OSCheckBox, &OSCheckBox::onModelObjectRemove>(this);

//   connect(this, &OSCheckBox::toggled, this, &OSCheckBox::onToggled);
//   bool checked = m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()->property(m_property.c_str()).toBool();

//   this->setChecked(checked);
// }

// void OSCheckBox::unbind()
// {
//   if (m_modelObject){
//     this->disconnect(m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>().get());
//     m_modelObject.reset();
//     m_property = "";
//     setEnabled(false);
//   }
// }

// void OSCheckBox::onToggled(bool checked)
// {
//   if( m_modelObject )
//   {
//     m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()->setProperty(m_property.c_str(),checked);
//   }
// }

// void OSCheckBox::onModelObjectChange()
// {
//   if( m_modelObject )
//   {
//     bool checked = m_modelObject->getImpl<openstudio::model::detail::ModelObject_Impl>()->property(m_property.c_str()).toBool();

//     this->setChecked(checked);
//   }
// }

// void OSCheckBox::onModelObjectRemove(const Handle& handle)
// {
//   m_modelObject.reset();
//   m_property = "";
//   setEnabled(false);
// }

}  // namespace openstudio
