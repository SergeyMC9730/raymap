#include <raymap.h>

Vector2 GetMousePositionInMapSpace(RMap2D *map) {
    Vector2 mouse = GetMousePosition();

    mouse.x -= map->logic.position.x;
    mouse.y -= map->logic.position.y;

    return mouse;
}