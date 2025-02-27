#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_CX  160.f
#define DUNGEON_DOOR_CY  120.f


class CBossRoomGate :
	public CObj
{
public:

	CBossRoomGate() {}
	~CBossRoomGate() {}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void CollisionPlayer();
};

