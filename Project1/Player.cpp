#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// ������ �����ϱ� ������ ��� ����
	Pos dest = board->GetExitPos();

	Pos front_pos[4] =
	{
		Pos {-1 , 0},	// UP
		Pos {0 , -1},	// LEFT
		Pos {1 , 0},	// DOWN
		Pos {0 , 1},	// RIGHT
	}; // �ٶ󺸴� ���� ���� ��ǥ�� ��Ÿ���� �迭

	while (pos != dest)
	{
		// 1. ���� �ٶ󺸴� ���� �������� ���������� �� �� �ִ��� Ȯ��
		int32 RightDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // ���� ��ġ ���� ������ ���� ��ǥ ����
		if (CanGo(pos + front_pos[RightDir]))
		{
			// ������ �������� 90�� ȸ��
			_dir = RightDir;
			// ������ �� �� ����.
			pos += front_pos[_dir];
			_path.push_back(pos);
		}

		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front_pos[_dir]))
		{
			// ������ �� �� ����.
			pos += front_pos[_dir];
			_path.push_back(pos);
		}

		// 3. ���� �ƴ� ��
		else
		{
			// ���� �������� 90�� ȸ��.
			_dir = (_dir + 1) % DIR_COUNT; // ������ �ݽð� ������� ������ �������� �̿��� ������ �ڵ�.
		}
	}
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tiletype = _board->GetTileType(pos);
	return !(tiletype == TileType::WALL);
}
