/**
 *  raymap - Gamemap for your raylib games.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <raymap.h>

void UnloadMap(RMap2D *map, bool unload_texture) {
    if (map == 0) {
        TraceLog(LOG_WARNING, "Map is NULL; cannot unload Map!");

        return;
    }

    if (unload_texture) UnloadTexture(map->renderer.texture);

    MemFree(map);
}