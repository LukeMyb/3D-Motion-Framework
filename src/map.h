#pragma once
#include <vector>
#include "raylib.h"
#include "stage_object.h"

class Map {
    public:
        Map();
        const std::vector<StageObject>& GetObjects() const { //最初のconstは戻り値の保護, もう一つはこのメソッドの保護 //メソッドを介してprivateのメンバ変数を返すことで一方通行にできて外部からは読み取り専用として扱うことができる(カプセル化)
            return obj;
        }
    private:
        std::vector<StageObject> obj; //stdは標準ライブラリの名前空間, vectorは動的配列, <>は型
};