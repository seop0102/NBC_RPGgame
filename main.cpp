#include "GameManager.h"

int main() {
	GameManager gameManager; 

	gameManager.startGame();

	while ( gameManager.playGame() ) {}

	return 0;
}