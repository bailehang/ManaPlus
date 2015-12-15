/*
 *  The ManaPlus Client
 *  Copyright (C) 2004-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011-2015  The ManaPlus Developers
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

#ifndef RESOURCES_SDL2IMAGEHELPER_H
#define RESOURCES_SDL2IMAGEHELPER_H

#ifdef USE_OPENGL

#include "resources/screenshothelper.h"

#include "resources/fboinfo.h"

#include "localconsts.h"

class OpenGLScreenshotHelper final : public ScreenshotHelper
{
    public:
        OpenGLScreenshotHelper();

        A_DELETE_COPY(OpenGLScreenshotHelper)

        ~OpenGLScreenshotHelper();

        void prepare(const int width,
                     const int height) override final;

        SDL_Surface *getScreenshot(const int width,
                                   const int height) override final;

    private:
        FBOInfo mFbo;
};

#endif  // USE_OPENGL
#endif  // RESOURCES_SDL2IMAGEHELPER_H
