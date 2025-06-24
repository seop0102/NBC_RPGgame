#include "GameManager.h"

int main() {
	GameManager gameManager;

	//gameManager.storyManager->startPrologue(); 

	gameManager.startGame();

	gameManager.playGame();

	gameManager.endGame();

	return 0;
}