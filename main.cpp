#define _CRTDBG_MAP_ALLOC
#include "GameManager.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gameManager; 

	gameManager.startGame();

	while ( gameManager.playGame() ) {}

	return 0;
}