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

#ifndef OPENSTUDIO_PEOPLEINSPECTORVIEW_HPP
#define OPENSTUDIO_PEOPLEINSPECTORVIEW_HPP

#include "ModelObjectInspectorView.hpp"
#include <openstudio/src/model/PeopleDefinition.hpp>

class QGridLayout;
class QPushButton;

namespace openstudio {

class OSDoubleEdit2;
class OSLineEdit2;
class OSQuantityEdit2;
class OSSwitch2;
class OSComboBox2;

class PeopleDefinitionInspectorView : public ModelObjectInspectorView
{
  Q_OBJECT

  public:

    PeopleDefinitionInspectorView(bool isIP, const openstudio::model::Model& model, QWidget * parent = nullptr );

    virtual ~PeopleDefinitionInspectorView() {}

  public slots:
    void addExtensible();

    void removeExtensible();

  protected:

    virtual void onClearSelection() override;

    virtual void onSelectModelObject(const openstudio::model::ModelObject& modelObject) override;

    virtual void onUpdate() override;

    void checkRemoveBtn( QPushButton* btn );

  private:

    void attach(openstudio::model::PeopleDefinition& peopleDefinition);

    void detach();

    void refresh();

    OSComboBox2 * addThermalComfortModelTypeComboBox(int groupIndex);

    QGridLayout* m_mainGridLayout;

    OSLineEdit2* m_nameEdit;

    OSDoubleEdit2* m_numberofPeopleEdit;
    OSQuantityEdit2* m_peopleperSpaceFloorAreaEdit;
    OSQuantityEdit2* m_spaceFloorAreaperPersonEdit;
    OSDoubleEdit2* m_fractionRadiantEdit;
    OSDoubleEdit2* m_sensibleHeatFractionEdit;
    OSQuantityEdit2* m_carbonDioxideGenerationRateEdit;


    // how to handle the extensible groups
    OSSwitch2* m_enableASHRAE55ComfortWarningsSwitch;
    OSComboBox2* m_meanRadiantTemperatureCalculationTypeComboBox;
    std::vector<OSComboBox2*> m_thermalComfortModelTypeComboBoxes;

    bool m_isIP;
    boost::optional<model::PeopleDefinition> m_peopleDefinition;

  public slots:

    void toggleUnits(bool displayIP) override;
};

} // openstudio

#endif // OPENSTUDIO_PEOPLEINSPECTORVIEW_HPP
