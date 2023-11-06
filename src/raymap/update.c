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

#include <math.h>

#include <stdio.h>

float _MapEaseInterpolation(float x) {
    return x == 1.f ? 1.f : 1 - pow(2.f, -10.f * x);
}

bool _CheckFloatAroundValue(float x, float r) {
    return (x > r) || (x < -r);
}

void UpdateMap(RMap2D *map) {
    if (map == 0) {
        return;
    }

    if (!map->logic.movable) return;

    float delta = GetFrameTime();

    Rectangle r1;

    r1.width = map->renderer.texture.width;
    r1.height = map->renderer.texture.height;

    Rectangle screen_rect = {};
    screen_rect.width = GetScreenWidth();
    screen_rect.height = GetScreenHeight();

    Vector2 future_position = map->logic.position;
    future_position.x += map->logic._internal[1].x;
    future_position.y += map->logic._internal[1].y;

    r1.x = future_position.x;
    r1.y = future_position.y;

    Rectangle colrect = GetCollisionRec(r1, screen_rect);

    r1.x -= map->logic._internal[1].x;
    r1.y -= map->logic._internal[1].y;

    if (colrect.width != screen_rect.width) {
        map->logic._internal[1].x = 0.f;
    }
    if (colrect.height != screen_rect.height) {
        map->logic._internal[1].y = 0.f;
    }

    map->logic._internal[0] = GetMousePosition();

    map->logic.position.x += map->logic._internal[1].x; // velocity x
    map->logic.position.y += map->logic._internal[1].y; // velocity y

    bool is_negative_velocity_x = false;
    bool is_negative_velocity_y = false;
    
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {   
        Rectangle r1;

        r1.width = map->renderer.texture.width;
        r1.height = map->renderer.texture.height;
        r1.x = map->logic.position.x;
        r1.y = map->logic.position.y;

        if (CheckCollisionPointRec(map->logic._internal[0], r1)) {
            map->logic._internal[1] = GetMouseDelta();

            // map->logic._internal[1].x *= delta * 100.f;
            // map->logic._internal[1].y *= delta * 100.f;

            map->logic._internal[3].x = map->logic._internal[1].x < 0.f;
            map->logic._internal[3].y = map->logic._internal[1].y < 0.f;

            map->logic._internal[2].x = 1.f;
            map->logic._internal[2].y = 1.f;
        }
    } else {
        if ((_CheckFloatAroundValue(map->logic._internal[1].x, 0.f) || _CheckFloatAroundValue(map->logic._internal[1].y, 0.f)) && map->logic._internal[2].y >= 1.f) {

            float interpolation = _MapEaseInterpolation(map->logic._internal[2].x) * delta * 5.5f;

            float max_time = 30.f;

            map->logic._internal[2].x -= delta / max_time;

            if (map->logic._internal[3].x >= 1.f) {
                if (map->logic._internal[1].x <= 0.f) map->logic._internal[1].x += interpolation; 
                else map->logic._internal[1].x = 0.f;
            } else {
                if (map->logic._internal[1].x >= 0.f) map->logic._internal[1].x -= interpolation;
                else map->logic._internal[1].x = 0.f; 
            }
            if (map->logic._internal[3].y >= 1.f) {
                if (map->logic._internal[1].y <= 0.f) map->logic._internal[1].y += interpolation;
                else map->logic._internal[1].y = 0.f;   
            } else {
                if (map->logic._internal[1].y >= 0.f) map->logic._internal[1].y -= interpolation;
                else map->logic._internal[1].y = 0.f;
            }

            float old_velx = map->logic._internal[1].x;
            float old_vely = map->logic._internal[1].y;

            map->logic._internal[1].x = fabs(map->logic._internal[1].x);
            map->logic._internal[1].y = fabs(map->logic._internal[1].y);

            if (map->logic._internal[1].x == interpolation) {
                map->logic._internal[1].x = 0.f;
            } else {
                map->logic._internal[1].x = old_velx;
            }

            if (map->logic._internal[1].y == interpolation) {
                map->logic._internal[1].y = 0.f;
            } else {
                map->logic._internal[1].y = old_vely;
            }

            if ((map->logic._internal[1].x == 0.f) && (map->logic._internal[1].y == 0.f)) map->logic._internal[2].x = 0.f; // stop moving

            printf("vx %f vy %f time %f i %f | vx_neg %d vy_neg %d\n", 
                map->logic._internal[1].x, map->logic._internal[1].y, map->logic._internal[2].x, interpolation,
                (int)map->logic._internal[3].x, (int)map->logic._internal[3].y
            );

            if (map->logic._internal[2].x <= 0.f) map->logic._internal[2].y = 0.f;
        } else {
            map->logic._internal[1].x = 0.f;
            map->logic._internal[1].y = 0.f;
        }
    }
}