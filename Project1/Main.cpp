#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
	::srand(static_cast<unsigned int>(time(nullptr)));
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;
	while (true)
	{
		// 게임들의 코드 구조

#pragma region 프레임 관리
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;
#pragma endregion

		// 입력

		// 로직
		player.Update(deltaTick);

		// 랜더링
		board.Render();	// 실행마다 랜덤하게 미로 생성. 
		
	}

}
