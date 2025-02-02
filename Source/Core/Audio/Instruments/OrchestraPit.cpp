/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Common.h"
#include "OrchestraPit.h"
#include "Instrument.h"

OrchestraPit::~OrchestraPit()
{
    this->removeAllOrchestraListeners();
}

void OrchestraPit::addOrchestraListener(OrchestraListener *listener)
{
    jassert(MessageManager::getInstance()->currentThreadHasLockedMessageManager());
    this->orchestraListeners.add(listener);
}

void OrchestraPit::removeOrchestraListener(OrchestraListener *listener)
{
    jassert(MessageManager::getInstance()->currentThreadHasLockedMessageManager());
    this->orchestraListeners.remove(listener);
}

void OrchestraPit::removeAllOrchestraListeners()
{
    jassert(MessageManager::getInstance()->currentThreadHasLockedMessageManager());
    this->orchestraListeners.clear();
}

void OrchestraPit::broadcastRemoveInstrument(Instrument *instrument)
{
    this->orchestraListeners.call(&OrchestraListener::onRemoveInstrument, instrument);
}

void OrchestraPit::broadcastPostRemoveInstrument()
{
    this->orchestraListeners.call(&OrchestraListener::onPostRemoveInstrument);
}

void OrchestraPit::broadcastAddInstrument(Instrument *instrument)
{
    this->orchestraListeners.call(&OrchestraListener::onAddInstrument, instrument);
}
