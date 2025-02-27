#pragma once
#include "Obj.h"
#include "Item.h"
enum STATE { IDLE, WALK, ATTACK, WAND_STATE, SWORD_STATE, SHIELD_STATE, BOOMERANG_STATE, HIT, ROLL, GET_ITEM, DEAD, STATE_END };
#define BULLET_RENDER_TIME 3000

class CPlayer : public CObj
{

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void		Update_Rect();
	void		Get_Hit();
	void		Get_Item(CObj* _pItem);
	void		Motion_Change();

private:
	void		Key_Input();
	void		OffSet();
	void		OffSet2();
	void		Use_Item(ITEMCODE _eItemCode);
	STATE		ItemCode_To_State(ITEMCODE _eid);

	CObj* Create_Shield();

	template<typename T>
	CObj* Create_Bullet(float fX, float fY, float fAngle, DWORD dwTime);

private:
	list<CObj*>* m_pBullet;
	list<CObj*>* m_pShield;
	POINT			m_tPosin;
	bool				m_bAction;

	float			m_fPower;
	float			m_fTime;


	STATE			m_eCurState;
	STATE			m_ePreState;
};


template<typename T>
inline CObj* CPlayer::Create_Bullet(float fX, float fY, float fAngle, DWORD dwTime)
{
	CObj* pBullet = new T;

	pBullet->Initialize();
	pBullet->Set_Angle(fAngle);
	pBullet->Set_Pos(fX, fY);
	pBullet->Set_MotionTime(dwTime);

	return pBullet;
}