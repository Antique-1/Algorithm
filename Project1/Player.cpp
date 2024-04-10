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

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = board->GetExitPos();

	Pos front_pos[4] =
	{
		Pos {-1 , 0},	// UP
		Pos {0 , -1},	// LEFT
		Pos {1 , 0},	// DOWN
		Pos {0 , 1},	// RIGHT
	}; // 바라보는 기준 앞의 좌표를 나타내는 배열

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 RightDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // 현제 위치 기준 오른쪽 방향 좌표 추출
		if (CanGo(pos + front_pos[RightDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = RightDir;
			// 앞으로 한 보 전진.
			pos += front_pos[_dir];
			_path.push_back(pos);
		}

		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front_pos[_dir]))
		{
			// 앞으로 한 보 전진.
			pos += front_pos[_dir];
			_path.push_back(pos);
		}

		// 3. 전부 아닐 시
		else
		{
			// 왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT; // 방향을 반시계 순서대로 정의해 놓은것을 이용한 간략한 코드.
		}
	}


	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	reverse(path.begin(), path.end());

	_path = path;
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
