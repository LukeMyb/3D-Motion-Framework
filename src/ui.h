#pragma once
#include "raylib.h"
#include "raymath.h"
#include "player.h"

class UI {
    public:
        UI();
        void Update(Player p);
        void ShowCoordinates(Player p);
        void ShowPointer();
    private:
};