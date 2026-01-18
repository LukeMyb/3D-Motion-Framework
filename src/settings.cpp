#include "raylib.h"
#include "raymath.h"
#include "settings.h"

Settings::Settings() {
    SetConfigFlags(FLAG_FULLSCREEN_MODE); //フルスクリーン
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "raylib [core] example - basic window"); //ウィンドウサイズとタイトル
    SetTargetFPS(60); //フレームレート
    DisableCursor(); //カーソル非表示
}