#include "stdafx.h"
#include "WandBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
//#include "StaffEffect.h"
#include "TerrainObjMgr.h"
#include "SoundMgr.h"
#include "StaffEffect.h"

void CWandBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/StaffBullet.bmp", L"StaffBullet");
	m_pFrameKey = L"StaffBullet";
	m_tInfo.fCX = WAND_BULLET_RANGECX;
	m_tInfo.fCY = WAND_BULLET_RANGECY;
	m_fSpeed = 4.f;
	m_eRender = RENDER_GAMEOBJECT;

	m_dwDelayTime = GetTickCount() + (DWORD)WAND_BULLET_DELAY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
}

int CWandBullet::Update()
{

	if (m_bDead)
	{
		if (true == m_bInvincibility)
		{
			float fX(m_tInfo.fX), fY(m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CObjMgr::Get_Instance()->Create_Effect<CStaffEffect>(fX, fY));
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"StaffBulletHit.wav", SOUND_EFFECT, 1.f);
		}
		return OBJ_DEAD;
	}
	if (m_dwDelayTime > GetTickCount())
		return OBJ_NOEVENT;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	float		fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	/*if (m_pTarget)
	{
		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		fRadian = (float)acos(fWidth / fDiagonal);

		if (m_pTarget->Get_Info().fY < m_tInfo.fY)
			fRadian = 2.f * PI - fRadian;

	}
	else*/
		fRadian = m_fAngle * PI / 180.f;

	m_tInfo.fX += m_fSpeed * (float)cos(fRadian);
	m_tInfo.fY += m_fSpeed * (float)sin(fRadian);

	__super::Update_Rect();



	return OBJ_NOEVENT;
}

void CWandBullet::Late_Update()
{
	if (m_tFrame.dwMotionTime < GetTickCount())
		m_bDead = true;
	list<CObj*> templist = CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_WALL);
	for (auto iter = templist.begin();
		iter != templist.end();
		++iter)

	{
		RECT rc{};
		if (IntersectRect(&rc, &this->Get_Rect(), &(*iter)->Get_Rect()))
		{
			m_bDead = true;

		}
	}
	__super::Move_Frame();
}

void CWandBullet::Render(HDC hDC)
{
	if (m_dwDelayTime > GetTickCount()) //������ ���� ������ �ȵ�.
		return;
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top + iScrollY,
		(int)WAND_BULLET_RANGECX,	// ���� ���� ����, ���� ����
		(int)WAND_BULLET_RANGECY,
		hMemDC,		// ������ �̹��� dc
		(int)WAND_BULLET_RANGECX * m_tFrame.iFrameStart,
		(int)WAND_BULLET_RANGECY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)WAND_BULLET_RANGECX,	// ������ �̹����� ����, ���� ������
		(int)WAND_BULLET_RANGECY,
		RGB(64, 176, 136));	// �����ϰ��� �ϴ� ����
	//Rectangle(hMemDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

}

void CWandBullet::Release()
{
}


void CWandBullet::Set_Pos(float _fX, float _fY)
{
	if (0.f == m_fAngle) //������
	{
		//m_tInfo.fCX = STAFF_BULLET_RANGECY;
		//m_tInfo.fCY = STAFF_BULLET_RANGECX;
		m_tInfo.fX = _fX + 60.f * 1.25f;
		m_tInfo.fY = _fY;
	}
	else if (90.f == m_fAngle) //�Ʒ���
	{
		//m_tInfo.fCX = STAFF_BULLET_RANGECX;
		//m_tInfo.fCY = STAFF_BULLET_RANGECY;
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY + 60.f * 1.25f;
	}
	else if (180.f == m_fAngle) //����
	{
		//m_tInfo.fCX = STAFF_BULLET_RANGECY;
		//m_tInfo.fCY = STAFF_BULLET_RANGECX;
		m_tInfo.fX = _fX - 60.f * 1.25f;
		m_tInfo.fY = _fY;
	}
	else if (270.f == m_fAngle) //����
	{
		//m_tInfo.fCX = STAFF_BULLET_RANGECX;
		//m_tInfo.fCY = STAFF_BULLET_RANGECY;
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY - 60.f * 1.25f;
	}


}
