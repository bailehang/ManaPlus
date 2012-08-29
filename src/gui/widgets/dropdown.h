/*
 *  The ManaPlus Client
 *  Copyright (C) 2006-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011-2012  The ManaPlus Developers
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

#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <guichan/widgets/dropdown.hpp>

#include "localconsts.h"

class Image;
class ImageRect;

/**
 * A drop down box from which you can select different values.
 *
 * A ListModel provides the contents of the drop down. To be able to use
 * DropDown you must give DropDown an implemented ListModel which represents
 * your list.
 */
class DropDown : public gcn::DropDown
{
    public:
        /**
         * Contructor.
         *
         * @param listModel the ListModel to use.
         * @param scrollArea the ScrollArea to use.
         * @param listBox the listBox to use.
         * @see ListModel, ScrollArea, ListBox.
         */
        DropDown(gcn::ListModel *const listModel = nullptr,
                 gcn::ActionListener *const listener = nullptr,
                 const std::string &eventId = "");

        ~DropDown();

        /**
         * Update the alpha value to the graphic components.
         */
        void updateAlpha();

        void draw(gcn::Graphics *graphics);

        void drawFrame(gcn::Graphics *graphics);

        // Inherited from FocusListener

        void focusLost(const gcn::Event& event);

        // Inherited from KeyListener

        void keyPressed(gcn::KeyEvent& keyEvent);

        // Inherited from MouseListener

        void mousePressed(gcn::MouseEvent& mouseEvent);

        void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent);

        void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent);

        void setSelectedString(std::string str);

        std::string getSelectedString() const;

    protected:
        /**
         * Draws the button with the little down arrow.
         *
         * @param graphics a Graphics object to draw with.
         */
        void drawButton(gcn::Graphics *graphics);

        gcn::Color mShadowColor;
        gcn::Color mHighlightColor;

        // Add own Images.
        static int instances;
        static Image *buttons[2][2];
        static ImageRect skinRect;
        static float mAlpha;
};

#endif // end DROPDOWN_H
