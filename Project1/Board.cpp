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
	

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
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


	// 랜덤하게 미로 맵을 생성하는 알고리즘
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;
			if (x == _size - 2 && y == _size - 2)
				continue;

			// 오른쪽과 아래 길을 전부 이동할 수 있는 공간으로 뚫어주기
			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			if (x == _size - 2)
			{
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			// 짝수 타일의 오른쪽이나 아래 랜덤하게 뚫기
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
