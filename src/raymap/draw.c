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

/*
    void DrawMap(RMap2D *map, float x, float y);
    void DrawMapV(RMap2D *map, Vector2 position);
    void DrawMapEx(RMap2D *map, Vector2 position, float rotation);
*/

void DrawMapEx(RMap2D *map, Vector2 position, float rotation, float scale) {
    if (map == 0) {
        return;
    }

    Vector2 final_position = map->logic.position;
    final_position.x += position.x;
    final_position.y += position.y;

    Rectangle rect = {};
    rect.width = map->renderer.texture.width;
    rect.height = -map->renderer.texture.height;

    Rectangle rect_dest;
    rect_dest.x = final_position.x;
    rect_dest.y = final_position.y;
    rect_dest.width = map->renderer.texture.width * scale;
    rect_dest.height = map->renderer.texture.height * scale;

    DrawTexturePro(map->renderer.texture, rect, rect_dest, (Vector2){0,0}, rotation, WHITE);

    return;
}

void DrawMapV(RMap2D *map, Vector2 position) {
    return DrawMapEx(map, position, 0.f, 1.f);
}

void DrawMap(RMap2D *map, float x, float y) {
    Vector2 v;
    v.x = x;
    v.y = y;

    return DrawMapV(map, v);
}