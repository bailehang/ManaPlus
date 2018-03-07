/*
 *  The ManaPlus Client
 *  Copyright (C) 2018  The ManaPlus Developers
 *
 *  This file is part of The ManaPlus Client.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PINCODEMANAGER_H
#define PINCODEMANAGER_H

#include "enums/simpletypes/beingid.h"

#include "enums/gui/pincodestate.h"

#include <string>

#include "localconsts.h"

class PincodeDialog;
class Window;

class PincodeManager final
{
    public:
        PincodeManager();

        A_DELETE_COPY(PincodeManager)

        ~PincodeManager();

        void init();

        void updateState();

        void pinOk();

        void wrongPin();

        void setSeed(const uint32_t seed)
        { mSeed = seed; }

        void setAccountId(const BeingId id)
        { mAccountId = id; }

        void setState(const PincodeState state)
        { mState = state; }

        void clearDialog(const PincodeDialog *const PincodeDialog);

        void setNewPincode(const std::string &pincode);

        void sendPincode(const std::string &pincode);

        void closeDialogs();

    protected:
        std::string mNewPincode;
        uint32_t mSeed;
        BeingId mAccountId;
        Window *mDialog;
        PincodeState mState;
};

extern PincodeManager pincodeManager;

#endif  // PINCODEMANAGER_H