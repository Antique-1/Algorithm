#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

// 우수법을 이용한 미로 탈출 알고리즘

int main()
{
	::srand(static_cast<unsigned int>(time(nullptr)));
	board.Init(31, &player);
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
		board.Render();	// 생성한 미로를 랜더링하여 화면에 보이게 출력

	}

}
