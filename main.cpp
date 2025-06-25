#include "GameManager.h"

int main() {
	GameManager gameManager; 

	gameManager.startGame();

	while ( gameManager.playGame() ) {}

	gameManager.endGame();

	return 0;
}