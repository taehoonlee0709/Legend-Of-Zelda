#pragma once
#include "Obj.h"

#define BLOCK_DOOR_CX  146.f
#define BLOCK_DOOR_CY  97.f


class CDoorBlock :
	public CObj
{
public:

	CDoorBlock() {}
	~CDoorBlock() {}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void CollisionPlayer();
};

