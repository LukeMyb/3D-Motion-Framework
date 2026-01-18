#include "raylib.h"
#include "raymath.h"
#include "stage_object.h"

StageObject::StageObject(Vector3 cent, Vector3 siz, Color c) {
    this->pos = cent;
    this->size = siz;
    this->box.min = (Vector3){pos.x, pos.y, pos.z};
    this->box.max = (Vector3){pos.x + size.x, pos.y + size.y, pos.z + size.z};

    this->color = c;
    this->is_visible = true;
}

void StageObject::Draw() const {
    Vector3 drawPos = Vector3Add(pos, Vector3Scale(size, 0.5f)); //角からサイズを半分足した場所を描画の中心にする
    DrawCubeV(drawPos, size, color);
    DrawCubeWiresV(drawPos, size, WHITE);
}