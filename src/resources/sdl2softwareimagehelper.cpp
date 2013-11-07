/*
 *  The ManaPlus Client
 *  Copyright (C) 2004-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011-2013  The ManaPlus Developers
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

#ifdef USE_SDL2

#include "resources/sdl2softwareimagehelper.h"

#include "resources/dye.h"
#include "resources/resourcemanager.h"

#include "logger.h"
#include "main.h"

#include "resources/image.h"

#include "utils/sdlcheckutils.h"

#include <SDL_image.h>

#include "debug.h"

bool SDL2SoftwareImageHelper::mEnableAlphaCache = false;
SDL_PixelFormat *SDL2SoftwareImageHelper::mFormat = nullptr;

Image *SDL2SoftwareImageHelper::load(SDL_RWops *const rw, Dye const &dye) const
{
    SDL_Surface *const tmpImage = loadPng(rw);
    if (!tmpImage)
    {
        logger->log("Error, image load failed: %s", IMG_GetError());
        return nullptr;
    }

    SDL_PixelFormat rgba;
    rgba.palette = nullptr;
    rgba.BitsPerPixel = 32;
    rgba.BytesPerPixel = 4;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rgba.Rmask = 0x000000FF;
    rgba.Gmask = 0x0000FF00;
    rgba.Bmask = 0x00FF0000;
    rgba.Amask = 0xFF000000;
#else
    rgba.Rmask = 0xFF000000;
    rgba.Gmask = 0x00FF0000;
    rgba.Bmask = 0x0000FF00;
    rgba.Amask = 0x000000FF;
#endif

    SDL_Surface *const surf = MSDL_ConvertSurface(
        tmpImage, &rgba, SDL_SWSURFACE);
    MSDL_FreeSurface(tmpImage);

    uint32_t *pixels = static_cast<uint32_t *>(surf->pixels);
    const int type = dye.getType();

    switch (type)
    {
        case 1:
        {
            const DyePalette *const pal = dye.getSPalete();
            if (pal)
                pal->replaceSColor(pixels, surf->w * surf->h);
            break;
        }
        case 2:
        {
            const DyePalette *const pal = dye.getAPalete();
            if (pal)
                pal->replaceAColor(pixels, surf->w * surf->h);
            break;
        }
        case 0:
        default:
        {
            dye.normalDye(pixels, surf->w * surf->h);
            break;
        }
    }

    Image *const image = load(surf);
    MSDL_FreeSurface(surf);
    return image;
}

Image *SDL2SoftwareImageHelper::load(SDL_Surface *const tmpImage) const
{
    return _SDLload(tmpImage);
}

Image *SDL2SoftwareImageHelper::createTextSurface(SDL_Surface *const tmpImage,
                                                  const int width A_UNUSED,
                                                  const int height A_UNUSED,
                                                  const float alpha) const
{
    if (!tmpImage)
        return nullptr;

    Image *const img = _SDLload(tmpImage);
    if (img)
        img->setAlpha(alpha);
    return img;
}

SDL_Surface* SDL2SoftwareImageHelper::SDLDuplicateSurface(SDL_Surface *const
                                                          tmpImage)
{
    if (!tmpImage || !tmpImage->format)
        return nullptr;

    return MSDL_ConvertSurface(tmpImage, tmpImage->format, SDL_SWSURFACE);
}

Image *SDL2SoftwareImageHelper::_SDLload(SDL_Surface *tmpImage) const
{
    if (!tmpImage)
        return nullptr;

    SDL_Surface *image = SDL_ConvertSurface(tmpImage, mFormat, 0);
    return new Image(image, false, nullptr);
}

SDL_Surface *SDL2SoftwareImageHelper::create32BitSurface(int width,
                                                         int height) const
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const int rmask = 0xff000000;
    const int gmask = 0x00ff0000;
    const int bmask = 0x0000ff00;
    const int amask = 0x000000ff;
#else
    const int rmask = 0x000000ff;
    const int gmask = 0x0000ff00;
    const int bmask = 0x00ff0000;
    const int amask = 0xff000000;
#endif

    return MSDL_CreateRGBSurface(SDL_SWSURFACE,
        width, height, 32, rmask, gmask, bmask, amask);
}

int SDL2SoftwareImageHelper::combineSurface(SDL_Surface *const src,
                                            SDL_Rect *const srcrect,
                                            SDL_Surface *const dst,
                                            SDL_Rect *const dstrect)
{
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_BLEND);
    SDL_BlitSurface(src, srcrect, dst, dstrect);
    return 1;
}

#endif  // USE_SDL2
