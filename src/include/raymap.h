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

#pragma once

#include <raylib.h>

#include <stdbool.h>

#pragma pack(push, 1)
struct RMap {
    struct Renderer {
        Texture2D texture; // Texture for drawing
    } renderer;
    struct Logic {
        Vector2 position; // Position

        Vector2 _internal[4];

        bool movable; // Can move map around with mouse
    } logic;
};

// RMap2D, same as RMap
typedef struct RMap RMap2D;

#pragma pack(pop)

// Loads map
RMap2D *LoadMap(Texture2D texture);

// Unloads map
void UnloadMap(RMap2D *map, bool unload_texture);

// Update map logic
void UpdateMap(RMap2D *map);

// Draw map functions
void DrawMap(RMap2D *map, float x, float y);
void DrawMapV(RMap2D *map, Vector2 position);
void DrawMapEx(RMap2D *map, Vector2 position, float rotation, float scale);

Vector2 GetMousePositionInMapSpace(RMap2D *map);