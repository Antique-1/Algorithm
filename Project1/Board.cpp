#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);
	

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y, x });
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}
}


// Binary Tree 미로 생성 알고리즘
// - Maze For Programmers

void Board::GenerateMap()
{
	// 짝수, 짝수 위치의 타일을 초록색(EMPTY) 블록으로 설정
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}


	// 짝수마다 뚫린 타일의 오른쪽 or 아래쪽을 랜덤하게 뚫어 미로를 생성하는 알고리즘
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			const int randValue = ::rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				_tile[y + 1][x] = TileType::EMPTY;
			}
		}
	}

	// 마지막줄 타일을 벽으로 바꾸기
	for (int32 x = 0; x < _size; x++)
		_tile[_size - 1][x] = TileType::WALL;
	for (int32 y = 0; y < _size; y++)
		_tile[y][_size - 1] = TileType::WALL;
}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE;

	if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW; // 플레이어 위치를 노란색으로

	if (GetExitPos() == pos)
		return ConsoleColor::BLUE; // 끝을 파란색

	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case	TileType::EMPTY:
		return ConsoleColor::GREEN;
	case	TileType::WALL:
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;
}
