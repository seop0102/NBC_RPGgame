#include "GameManager.h"

int main() {
	GameManager gameManager;

	gameManager.storyManager->startPrologue(); // ÇÁ·Ñ·Î±× ½ÃÀÛ

	gameManager.startGame();

	gameManager.playGame();

	gameManager.endGame();

	return 0;
}