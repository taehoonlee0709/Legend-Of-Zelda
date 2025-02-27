#pragma once
#include "Scene.h"
//StartArea
#define EDIT_MAX_SCREENX 3021
#define EDIT_MAX_SCREENY 2067
//BossStage
//#define MAXSCREENX 3021
//#define MAXSCREENY 2067

class CMyEdit : public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void	Key_Input();
};

