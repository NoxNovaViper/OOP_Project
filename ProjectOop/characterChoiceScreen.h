#pragma once
#include "Player.h"
class characterChoiceScreen {
private:
    int p1Choice;
    int p2Choice;
    bool isSinglePlayer;
    bool selectionDone;

public:
    characterChoiceScreen(bool singlePlayer);
    void player1Select(int characterType);
    void player2Select(int characterType);
    void confirmSelection();
    void draw();

    int getPlayer1Choice() const { return p1Choice; }
    int getPlayer2Choice() const { return p2Choice; }
    bool getSelectionDone() const { return selectionDone; }
};