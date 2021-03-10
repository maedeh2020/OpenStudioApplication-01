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

#ifndef SHAREDGUICOMPONENTS_OSLINEEDIT_HPP
#define SHAREDGUICOMPONENTS_OSLINEEDIT_HPP

#include "FieldMethodTypedefs.hpp"

#include <openstudio/nano/nano_signal_slot.hpp>  // Signal-Slot replacement
#include <openstudio/model/Model.hpp>

#include <QLineEdit>

#include <QTimer>

class QFocusEvent;
class QMouseEvent;

namespace openstudio {

class OSItem;

enum DeleteType
{
  NoDelete,
  AlwaysDelete,
  DeleteIfNotDefaulted 
};

class OSLineEdit2Interface : public QLineEdit
{
  Q_OBJECT

 public:

  OSLineEdit2Interface(QWidget* parent = nullptr);

  virtual void enableClickFocus() = 0;
  
  virtual DeleteType deleteType() = 0;

  virtual void setDeleteType(DeleteType deleteType) = 0;

  virtual bool hasData() = 0;  

  virtual void setLocked(bool locked) = 0;  

  virtual boost::optional<model::ModelObject> modelObject() const = 0;

  virtual void bind(const model::ModelObject& modelObject, StringGetter get, boost::optional<StringSetter> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) = 0;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetter get, boost::optional<StringSetter> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) = 0;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetter get,
                    boost::optional<StringSetterOptionalStringReturn> set = boost::none, boost::optional<NoFailAction> reset = boost::none,
                    boost::optional<BasicQuery> isDefaulted = boost::none, boost::optional<BasicQuery> isLocked = boost::none) = 0;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetterBoolArg get, boost::optional<StringSetterOptionalStringReturn> set,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) = 0;

  virtual void bind(const model::ModelObject& modelObject, StringGetter get, boost::optional<StringSetterVoidReturn> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) = 0;

  virtual void unbind() = 0;

 signals:

  void itemClicked(OSItem* item);

  void objectRemoved(boost::optional<model::ParentObject> parent);

  void inFocus(bool inFocus, bool hasData);

 public slots:

  virtual void onItemRemoveClicked() = 0;

};

class OSLineEdit2 : public OSLineEdit2Interface, public Nano::Observer
{
  Q_OBJECT

 public:
  OSLineEdit2(QWidget* parent = nullptr);

  virtual ~OSLineEdit2();

  virtual void enableClickFocus() override;

  virtual DeleteType deleteType() override;

  virtual void setDeleteType(DeleteType deleteType) override;

  virtual bool hasData() override;

  virtual void setLocked(bool locked) override;  

  virtual boost::optional<model::ModelObject> modelObject() const override;

  virtual void bind(const model::ModelObject& modelObject, StringGetter get, boost::optional<StringSetter> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) override;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetter get, boost::optional<StringSetter> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) override;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetter get,
                    boost::optional<StringSetterOptionalStringReturn> set = boost::none, boost::optional<NoFailAction> reset = boost::none,
                    boost::optional<BasicQuery> isDefaulted = boost::none, boost::optional<BasicQuery> isLocked = boost::none) override;

  virtual void bind(const model::ModelObject& modelObject, OptionalStringGetterBoolArg get, boost::optional<StringSetterOptionalStringReturn> set,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) override;

  virtual void bind(const model::ModelObject& modelObject, StringGetter get, boost::optional<StringSetterVoidReturn> set = boost::none,
                    boost::optional<NoFailAction> reset = boost::none, boost::optional<BasicQuery> isDefaulted = boost::none,
                    boost::optional<BasicQuery> isLocked = boost::none) override;

  virtual void unbind() override;

 protected:

  virtual void mouseReleaseEvent(QMouseEvent* event) override;

  virtual void focusInEvent(QFocusEvent* e) override;

  virtual void focusOutEvent(QFocusEvent* e) override;

 signals:

  void itemClicked(OSItem* item);

  void objectRemoved(boost::optional<model::ParentObject> parent);

  void inFocus(bool inFocus, bool hasData);

 public slots:

  virtual void onItemRemoveClicked() override;

 private slots:

  void onEditingFinished();

  void onModelObjectChange();

  void onModelObjectRemove(const Handle& handle);

  void emitItemClicked();

 private:
  // For testing
  friend class OpenStudioLibFixture;

  void onModelObjectChangeInternal(bool startingup);
  void completeBind();
  void adjustWidth();
  void updateStyle();
  bool deleteable() const;
  bool defaulted() const;

  boost::optional<model::ModelObject> m_modelObject;
  boost::optional<StringGetter> m_get;
  boost::optional<OptionalStringGetter> m_getOptional;
  boost::optional<OptionalStringGetterBoolArg> m_getOptionalBoolArg;
  boost::optional<StringSetter> m_set;
  boost::optional<StringSetterOptionalStringReturn> m_setOptionalStringReturn;
  boost::optional<StringSetterVoidReturn> m_setVoidReturn;
  boost::optional<NoFailAction> m_reset;
  boost::optional<BasicQuery> m_isDefaulted;
  boost::optional<BasicQuery> m_isLocked;

  OSItem* m_item = nullptr;

  std::string m_text = "";

  QTimer m_timer;

  bool m_hasClickFocus = false;

  DeleteType m_deleteType = DeleteType::NoDelete;
};

// class OSLineEdit : public QLineEdit, public Nano::Observer
// {
//   Q_OBJECT

//   public:

//   OSLineEdit(QWidget * parent = nullptr);

//   virtual ~OSLineEdit() {}

//   void bind(model::ModelObject & modelObject, const char * property);

//   void unbind();

//   private slots:

//   void onEditingFinished();

//   void onModelObjectChange();

//   void onModelObjectRemove(const Handle& handle);

//   private:

//   boost::optional<model::ModelObject> m_modelObject;

//   std::string m_property;
// };

}  // namespace openstudio

#endif  // SHAREDGUICOMPONENTS_OSLINEEDIT_HPP
