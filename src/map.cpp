#include "raylib.h"
#include "raymath.h"
#include "stage_object.h"
#include "map.h"

//オブジェクトの設置
Map::Map() {
    obj.push_back(StageObject({-50.0f, -1.0f, -50.0f}, {100.0f, 1.0f, 100.0f}, GetColor(0x007F00FF))); //地面
    obj.push_back(StageObject({-3.0f, 0.0f, -3.0f}, {1.0f, 1.0f, 1.0f}, GRAY));
    obj.push_back(StageObject({3.0f, 0.0f, -3.0f}, {1.0f, 1.0f, 1.0f}, GRAY));
    obj.push_back(StageObject({-3.0f, 0.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, GRAY));
    obj.push_back(StageObject({3.0f, 0.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, GRAY));
    obj.push_back(StageObject({0.0f, 0.0f, -10.0f}, {20.0f, 10.0f, 1.0f}, GRAY));
}