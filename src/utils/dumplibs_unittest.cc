/*
 *  The ManaPlus Client
 *  Copyright (C) 2017  The ManaPlus Developers
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

#include "catch.hpp"
#include "logger.h"

#include "utils/stringutils.h"

#include <png.h>
#include <SDL_image.h>
PRAGMACLANG6(GCC diagnostic push)
PRAGMACLANG6(GCC diagnostic ignored "-Wold-style-cast")
#include <SDL_net.h>
PRAGMACLANG6(GCC diagnostic pop)
#include <SDL_ttf.h>
#include <physfs.h>
#include <zlib.h>

#include <curl/curl.h>

#include <libxml/xmlversion.h>

#include "debug.h"

TEST_CASE("dumplibs tests")
{
    logger = new Logger();

    SECTION("zlib")
    {
        const std::string build = ZLIB_VERSION;
        const std::string link = zlibVersion();
        REQUIRE(build == link);
    }

    SECTION("physfs")
    {
        PHYSFS_Version buildVersion;
        PHYSFS_Version linkVersion;
        PHYSFS_VERSION(&buildVersion);
        PHYSFS_getLinkedVersion(&linkVersion);

        const std::string build = strprintf("%d.%d.%d",
            buildVersion.major,
            buildVersion.minor,
            buildVersion.patch);
        const std::string link = strprintf("%d.%d.%d",
            linkVersion.major,
            linkVersion.minor,
            linkVersion.patch);

        REQUIRE(build == link);
    }

    SECTION("sdl")
    {
        const SDL_version *linkVersion = nullptr;
#ifdef USE_SDL2
        SDL_version sdlVersion;
        sdlVersion.major = 0;
        sdlVersion.minor = 0;
        sdlVersion.patch = 0;
        SDL_GetVersion(&sdlVersion);
        linkVersion = &sdlVersion;
#else  // USE_SDL2
        linkVersion = SDL_Linked_Version();
#endif  // USE_SDL2

        const std::string build = strprintf("%d.%d.%d",
            SDL_MAJOR_VERSION,
            SDL_MINOR_VERSION,
            SDL_PATCHLEVEL);
        const std::string link = strprintf("%d.%d.%d",
            linkVersion->major,
            linkVersion->minor,
            linkVersion->patch);

        REQUIRE(build == link);
    }

    SECTION("sdl_net")
    {
        const SDL_version *const linkVersion = SDLNet_Linked_Version();

        const std::string build = strprintf("%d.%d.%d",
            SDL_NET_MAJOR_VERSION,
            SDL_NET_MINOR_VERSION,
            SDL_NET_PATCHLEVEL);
        const std::string link = strprintf("%d.%d.%d",
            linkVersion->major,
            linkVersion->minor,
            linkVersion->patch);

        REQUIRE(build == link);
    }

    SECTION("sdl_image")
    {
        const SDL_version *const linkVersion = IMG_Linked_Version();

        const std::string build = strprintf("%d.%d.%d",
            SDL_IMAGE_MAJOR_VERSION,
            SDL_IMAGE_MINOR_VERSION,
            SDL_IMAGE_PATCHLEVEL);
        const std::string link = strprintf("%d.%d.%d",
            linkVersion->major,
            linkVersion->minor,
            linkVersion->patch);

        REQUIRE(build == link);
    }

    SECTION("sdl_ttf")
    {
        const SDL_version *const linkVersion = TTF_Linked_Version();

        const std::string build = strprintf("%d.%d.%d",
            SDL_TTF_MAJOR_VERSION,
            SDL_TTF_MINOR_VERSION,
            SDL_TTF_PATCHLEVEL);
        const std::string link = strprintf("%d.%d.%d",
            linkVersion->major,
            linkVersion->minor,
            linkVersion->patch);

        REQUIRE(build == link);
    }
}