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

int main() {
    InitWindow(640, 480, "raylib [core] example - basic window");

    SetTargetFPS(144);

    int szx = 1000;
    int szy = 1000;

    RenderTexture2D txt2 = LoadRenderTexture(szx, szy);

    BeginTextureMode(txt2);

    ClearBackground(WHITE);
    for (int i = 0; i < szx; i += 50) {
        DrawLine(i, 0, i, szy, GRAY);
        for (int j = 0; j < szy; j += 50) {
            DrawLine(0, j, szx, j, GRAY); 
        }
    }

    EndTextureMode();

    RMap2D *map = LoadMap(txt2.texture);

    while (!WindowShouldClose()) {
        UpdateMap(map);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawMap(map, 0, 0);

            DrawFPS(5, 5);
        EndDrawing();
    }

    UnloadMap(map, false);

    UnloadRenderTexture(txt2);

    CloseWindow();

    return 0;
}