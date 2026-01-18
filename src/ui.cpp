#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "ui.h"
#include "player.h"

UI::UI() {

}

void UI::Update(Player p) {
    ShowCoordinates(p);
    ShowPointer();
}

void UI::ShowCoordinates(Player p) {
    DrawText(TextFormat("X:%.1f, Y:%.1f, Z:%.1f", p.GetPos().x, p.GetPos().y, p.GetPos().z), 20, 100, 20, LIGHTGRAY);
}

void UI::ShowPointer() {
    DrawLine(GetMonitorWidth(0)/2-10, GetMonitorHeight(0)/2, GetMonitorWidth(0)/2+10, GetMonitorHeight(0)/2, LIGHTGRAY);
    DrawLine(GetMonitorWidth(0)/2, GetMonitorHeight(0)/2-10, GetMonitorWidth(0)/2, GetMonitorHeight(0)/2+10, LIGHTGRAY);
}