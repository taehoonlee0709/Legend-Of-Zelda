#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }

	RECT		Get_Rect() { return m_tRect; }
	void		Set_Dead() { m_bDead = true;  }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	bool		Get_Dead() { return m_bDead; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	TCHAR*		Get_FrameKey() { return m_pFrameKey; }

	int			Get_Hp() { return m_iHp; }
	void		Set_Hp(int _iValue)
	{
		if (0 <= m_iHp + _iValue)
			m_iHp += _iValue;
	}
	float		Get_Angle() { return m_fAngle; }

	bool		Get_Invincibility() { return m_bInvincibility; }
	void		Set_Invincibility() { m_bInvincibility = !m_bInvincibility; }

	INFO		Get_Info() { return m_tInfo; }
	void		Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	RENDERID	Get_RenderID() { return m_eRender; }
	void		Set_MotionTime(DWORD _dwTime) { m_tFrame.dwMotionTime = _dwTime; }

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

public:
	void		Update_Rect();
	void		Move_Frame();
		
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	int				m_iHp;

	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;
	bool			m_bInvincibility; //무적 상태

	DIRECTION	m_eDir;
	bool		m_bDead;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	RENDERID	m_eRender;
};

