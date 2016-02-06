/*
 *  The ManaPlus Client
 *  Copyright (C) 2012-2016  The ManaPlus Developers
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

#ifndef GUI_WIDGETS_WIDGET2_H
#define GUI_WIDGETS_WIDGET2_H

#include "const/gui/theme.h"

#include "gui/themecolorsidoperators.h"
#include "gui/theme.h"

class Widget;

class Widget2 notfinal
{
    public:
        virtual ~Widget2()
        {
        }

        inline const Color &getThemeColor(const ThemeColorIdT type,
                                          const unsigned int alpha = 255U)
                                          const A_WARN_UNUSED
        {
            return theme->getColor(type + mPaletteOffset, alpha);
        }

        inline const Color &getThemeCharColor(const signed char c,
                                              bool &valid)
                                              const A_WARN_UNUSED
        {
            if (!theme)
                return Palette::BLACK;
            const ThemeColorIdT colorId = theme->getIdByChar(c, valid);
            if (valid)
                return theme->getColor(colorId + mPaletteOffset, 255U);
            else
                return Palette::BLACK;
        }

        virtual void setWidget2(const Widget2 *const widget)
        {
            mPaletteOffset = widget ? widget->mPaletteOffset : 0;
        }

        void setPalette(int palette)
        {
            mPaletteOffset = palette * static_cast<int>(
                ThemeColorId::THEME_COLORS_END);
            checkPalette();
            setWidget2(this);
        }

        void checkPalette()
        {
            if (mPaletteOffset < 0 ||
                mPaletteOffset >= THEME_PALETTES * static_cast<int>(
                ThemeColorId::THEME_COLORS_END))
            {
                mPaletteOffset = 0;
            }
        }

        void setForegroundColor2(const Color &color)
        {
            mForegroundColor2 = color;
        }

        Widget* getWindow() const A_WARN_UNUSED
        {
            return mWindow;
        }

        virtual void setWindow(Widget *const window)
        {
            mWindow = window;
        }

    protected:
        explicit Widget2(const Widget2 *const widget) :
            mPaletteOffset(widget ? widget->mPaletteOffset : 0),
            mWindow(widget ? widget->getWindow() : nullptr),
            mForegroundColor2()
        {
            checkPalette();
        }

        int mPaletteOffset;
        Widget *mWindow;
        Color mForegroundColor2;
};

extern RenderType openGLMode;

#endif  // GUI_WIDGETS_WIDGET2_H
