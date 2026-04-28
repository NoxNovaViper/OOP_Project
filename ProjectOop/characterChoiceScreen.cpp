#include "characterChoiceScreen.h"

characterChoiceScreen::characterChoiceScreen(bool singlePlayer) {
    p1Choice = 0;
    p2Choice = 0;
    isSinglePlayer = singlePlayer;
    selectionDone = false;
}

void characterChoiceScreen::player1Select(int characterType) {
    p1Choice = characterType;
}

void characterChoiceScreen::player2Select(int characterType) {
    p2Choice = characterType;
}

void characterChoiceScreen::confirmSelection() {
    selectionDone = true;
}

void characterChoiceScreen::draw() {}