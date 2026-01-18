#pragma once //重複してインクルードしないように
#include <vector>
#include "raylib.h"
#include "stage_object.h"

class Player {
    public:
        Player();
        void Update(const std::vector<StageObject>& obj); //以下のメソッドを実行 //&は実体の引数を渡されたときそのアドレスから値を参照するということ
        void Move(const std::vector<StageObject>& obj); //入力に基づいてxz平面上の移動ベクトルを計算し, 衝突判定を行う
        void Crouch(); //しゃがみ
        void Jump();
        void Rotate(); //視点移動
        void ShowHitbox();
        BoundingBox GetHitbox(Vector3 d_pos); //現在の座標からヒットボックス同士が接触しているか判定するための座標への変換

        //main.cppで視点データを取得できるように
        Camera3D GetPov() const {
            return pov;
        }

        const Vector3 GetPos() const {
            return position;
        }
    private: //クラス内でしか呼び出せない(カプセル化)
        Vector3 position; //プレイヤーの足元の座標
        Vector3 size;
        float eye_height; //立ち状態の目の高さ
        float crouch_depth; //しゃがみによる沈み込み量
        
        Camera3D pov;
        float speed; //移動速度

        float yaw; //左右の回転
        float pitch; //上下の回転
        float sensitivity; //感度
};