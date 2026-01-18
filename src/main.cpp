#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "settings.h"
#include "player.h"
#include "stage_object.h"
#include "map.h"
#include "ui.h"

int main() {
    Settings settings; //コンストラクタでウィンドウなどの設定してる
    Player p;
    Map map;
    UI ui;

    while (!WindowShouldClose()) {
        p.Update(map.GetObjects()); //プレイヤーの動きを更新

        BeginDrawing();
        ClearBackground(GetColor(0x007FFFFF));
        BeginMode3D(p.GetPov());

        //描画
        p.ShowHitbox();
        for (const auto& item : map.GetObjects()) item.Draw(); //foreach(autoはコレクションの型から自動で単体の型を予測する)

        EndMode3D();
        ui.Update(p); //UIの更新
        EndDrawing();
    }

    CloseWindow(); // ウィンドウを閉じる
    return 0;
}