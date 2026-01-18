#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "stage_object.h"

//コンストラクタ
Player::Player() {
    position = (Vector3){0.0f, 0.0f, 0.0f};
    size = (Vector3){0.8f, 1.8f, 0.8f};
    eye_height = 1.6f;
    crouch_depth = 0.0f;

    // カメラの設定
    pov.position = (Vector3){0.0f, eye_height, 0.0f}; //カメラの場所
    pov.target = (Vector3){1.0f, eye_height, 0.0f}; //カメラがどこを見るか
    pov.up = (Vector3){0.0f, 1.0f, 0.0f}; //カメラの上方向(カメラの角度)
    pov.fovy = 60.0f; //視野角
    pov.projection = CAMERA_PERSPECTIVE; //遠近感のある投影

    speed = 4.0f;
    yaw = 135.0f;
    pitch = 0.0f;
    sensitivity = 0.03f;
}

BoundingBox Player::GetHitbox(Vector3 d_pos) { //d_posはプレイヤーの座標からずれている変化量
    float hx = size.x / 2.0f;
    float hy = size.y / 2.0f;
    float hz = size.z / 2.0f;

    return (BoundingBox) {
        (Vector3){position.x + d_pos.x - hx, position.y + d_pos.y, position.z + d_pos.z - hz},
        (Vector3){position.x + d_pos.x + hx, position.y + d_pos.y + size.y, position.z + d_pos.z + hz}
    };
}

void Player::Update(const std::vector<StageObject>& obj) {
    this->Move(obj); //(this->は同じクラスで定義した関数ということを表す)
    this->Crouch();
    this->Jump();
    this->Rotate();
}

void Player::Move(const std::vector<StageObject>& obj) {
    float rad = yaw * DEG2RAD;
    Vector3 vec_forward = {-sinf(rad), 0, cosf(rad)};
    Vector3 vec_right = {-cosf(rad), 0, -sinf(rad)};

    Vector3 vec_add = Vector3Zero(); //これから足すベクトル

    if (IsKeyDown(KEY_W)) vec_add += vec_forward;
    if (IsKeyDown(KEY_A)) vec_add -= vec_right;
    if (IsKeyDown(KEY_S)) vec_add -= vec_forward;
    if (IsKeyDown(KEY_D)) vec_add += vec_right;

    if (Vector3Length(vec_add) > 0) { //ゼロ除算回避
        vec_add = Vector3Normalize(vec_add); //正規化(斜め移動でスピードが√2倍にならないように)

        //当たり判定
        //GetRayCollisionBox(Ray ray, BoundingBox box); //放った光線が箱に当たったかを判定し, 「当たった場所の座標」や「距離」を返す

        //オブジェクトとの衝突判定
        bool move_x = true;
        bool move_z = true;
        for (const auto& item : obj) {
            if (item.GetBoundingBox().max.y <= this->position.y + 0.05f) continue; //床を検知した場合横移動の判定から除外する, 0.05fは乗り越え許容高さ

            if (CheckCollisionBoxes(GetHitbox((Vector3){vec_add.x * speed * GetFrameTime(), 0, 0}), {item.GetBoundingBox().min, item.GetBoundingBox().max})) {
                move_x = false; //一つでもオブジェクトへの衝突判定があればその方向へは移動不可
            }
            if (CheckCollisionBoxes(GetHitbox((Vector3){0, 0, vec_add.z * speed * GetFrameTime()}), {item.GetBoundingBox().min, item.GetBoundingBox().max})) {
                move_z = false;
            }
        }
        //プレイヤーの位置を更新
        if (move_x) this->position.x += vec_add.x * speed * GetFrameTime();
        if (move_z) this->position.z += vec_add.z * speed * GetFrameTime();
        //視点を更新
        pov.position.x = this->position.x;
        pov.position.z = this->position.z;
    }
}

void Player::Rotate() {
    Vector2 mouseDelta = GetMouseDelta(); //1フレーム前からのカーソルの変化量

    yaw += mouseDelta.x * sensitivity; //左右の回転
    pitch -= mouseDelta.y * sensitivity; //上下の回転

    if (pitch > 89.0f) pitch = 89.0f; //上下の角度制限
    if (pitch < -89.0f) pitch = -89.0f;

    float yaw_rad = yaw * DEG2RAD; //ラジアンに変換
    float pitch_rad = pitch * DEG2RAD;

    //カーソルの移動量をベクトルに変換
    Vector3 vec;
    vec.x = -cosf(pitch_rad) * sinf(yaw_rad);
    vec.y = sinf(pitch_rad);
    vec.z = cosf(pitch_rad) * cos(yaw_rad);
    
    pov.target = Vector3Add(pov.position, vec); //視点の方向を更新
}

void Player::Crouch() {
    if (IsKeyDown(KEY_LEFT_SHIFT) && (crouch_depth < 1.0f)) {
        crouch_depth += 0.1f;
        if (crouch_depth > 1.0f) {
            crouch_depth = 1.0f;
        }
    }
    else if (IsKeyUp(KEY_LEFT_SHIFT) && (crouch_depth > 0.0f)) {
        crouch_depth -= 0.1f;
        if (crouch_depth < 0.0f) {
            crouch_depth = 0.0f;
        }
    }

    pov.position.y = this->position.y + eye_height - crouch_depth;
}

void Player::Jump() {
    
}

void Player::ShowHitbox() {
    Vector3 drawPos = {position.x, position.y + size.y/2.0f, position.z};
    DrawCubeWiresV(drawPos, size, WHITE);
}