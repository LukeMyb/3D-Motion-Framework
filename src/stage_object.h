#pragma once
#include "raylib.h"

class StageObject {
    public:
        const BoundingBox& GetBoundingBox() const {
            return box;
        }

        StageObject(Vector3 pos, Vector3 size, Color color);
        void Draw() const;
    private:
        Vector3 pos;
        Vector3 size;
        BoundingBox box; //BoundingBoxはヒットボックスの重なりを判定するのに必要な関数の引数として使われていてmaxとminの属性を持ち, これらはcenterとsizeから相互変換可能, 一貫性はないけどいちいち変換するのがめんどいからこれもメンバ変数として持たせとく

        Color color;
        bool is_visible;
};