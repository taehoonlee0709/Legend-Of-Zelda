#include "stdafx.h"
#include "BossGuhu.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "GuhuSlaveEye.h"
#include "FireBallBullet.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "BossStage.h"
#include "BossExplosionEffect.h"
#include "SoundMgr.h"

void CBossGuhu::Initialize()
{
	m_tInfo = { BOSS_GUHU_POSX, BOSS_GUHU_POSY, BOSS_GUHU_COLLISION_CX, BOSS_GUHU_COLLISION_CY };

	m_iHp = 20;

	m_fSpeed = 3.5f;
	m_fDistance = 100.f;
	m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossGuhu/BossGuhu.bmp", L"BossGuhu");



	m_pFrameKey = L"BossGuhu";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 300;

	m_eRender = RENDER_GAMEOBJECT;

	Set_Target(CObjMgr::Get_Instance()->Get_Player());

	m_PatternQueue.push(BOSSPATTERN_FIREBALL); //1500
	m_PatternQueue.push(BOSSPATTERN_IDLE);		//2000
	m_PatternQueue.push(BOSSPATTERN_SPAWN_EYES); //600
	m_PatternQueue.push(BOSSPATTERN_IDLE);
	//m_PatternQueue.push(BOSSPATTERN_ROTATE_EYES); //4900
	m_PatternQueue.push(BOSSPATTERN_IDLE);
	m_PatternQueue.push(BOSSPATTERN_TELEPORT); //3000
	m_PatternQueue.push(BOSSPATTERN_IDLE);
}

int CBossGuhu::Update()
{	
	if (m_bDead)
	{
		for (auto iter = m_GuhuEyeList.begin();
			iter != m_GuhuEyeList.end();
			++iter)
		{
			(*iter)->Set_Dead();
		}
		return OBJ_DEAD;
	}

	DWORD	dwTime = GetTickCount();
	if (m_bAction == true && dwTime > m_tFrame.dwMotionTime) //액션 중인데 그 액션 시간이 다 지나면 트루. 안에서 액션중이 아니다 라고 
	{
		m_bAction = false;

		m_eCurPattern = BOSSPATTERN_IDLE;
		//m_fAngle = 90.f;
	
	}

	if (m_bInvincibility)// 무적 제어. 지금은 그냥 무적 상태이면 다시 되돌림.
		Set_Invincibility();

	if(BOSSPATTERN_TELEPORT == m_eCurPattern && false == m_bInvincibility)
		Set_Invincibility();

	if (m_bAction == false)
	{
		m_bAction = true;
		if (0 < m_PatternQueue.size())
		{
			m_eCurPattern = m_PatternQueue.front();
			m_PatternQueue.pop();

		}
		else
			m_eCurPattern = BOSSPATTERN_IDLE;
			
	}

	//Pattern_Change();
	FireBall();
	Check_Eyes();
	//Rotate_Eyes();
	__super::Update_Rect();
	//Update_Rect();
	return OBJ_NOEVENT;
}

void CBossGuhu::Late_Update()
{
	if (0 >= m_iHp)
	{
		m_bDead = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CObjMgr::Get_Instance()->Create_Effect<CBossExplosionEffect>(m_tInfo.fX, m_tInfo.fY));

	}
	__super::Move_Frame();

	Motion_Change();
}

void CBossGuhu::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - BOSS_GUHU_IMAGE_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
		int(m_tInfo.fY - BOSS_GUHU_IMAGE_CY * 0.5f) + iScrollY,
		(int)BOSS_GUHU_IMAGE_CX,	// 복사 받을 가로, 세로 길이
		(int)BOSS_GUHU_IMAGE_CY,
		hMemDC,		// 복사할 이미지 dc
		(int)BOSS_GUHU_IMAGE_CX * m_tFrame.iFrameStart,
		(int)BOSS_GUHU_IMAGE_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		(int)BOSS_GUHU_IMAGE_CX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)BOSS_GUHU_IMAGE_CY,
		RGB(128, 128, 128));	// 제거하고자 하는 색상값
}

void CBossGuhu::Release()
{
}

void CBossGuhu::Motion_Change()
{
	//DWORD	dwTime = GetTickCount();
	if (m_ePrePattern != m_eCurPattern)
	{
		switch (m_eCurPattern)
		{
		case BOSSPATTERN_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwMotionTime = IDLE_PATTERN_TIME + GetTickCount();
			break;
		case BOSSPATTERN_HIT:
			break;
		case BOSSPATTERN_FIREBALL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwMotionTime = FIREBALL_PATTERN_TIME + GetTickCount();
			m_PatternQueue.push(BOSSPATTERN_FIREBALL);
			m_PatternQueue.push(BOSSPATTERN_IDLE);
			if ((float)BOSS_STAGE_MAX_SCREENX * 0.5f < m_tInfo.fX)
				m_fAngle = 180.f;
			else
				m_fAngle = 0.f;
			break;
		case BOSSPATTERN_TELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwMotionTime = TELEPORT_PATTERN_TIME  + GetTickCount();
			Teleport();
			break;
		case BOSSPATTERN_SPAWN_EYES:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwMotionTime = EYES_SPAWN_PATTERN_TIME + GetTickCount();
			Spawn_Eyes();
			m_PatternQueue.push(BOSSPATTERN_SPAWN_EYES);
			m_PatternQueue.push(BOSSPATTERN_IDLE);
			m_PatternQueue.push(BOSSPATTERN_ROTATE_EYES);
			m_PatternQueue.push(BOSSPATTERN_IDLE);
			break;
		case BOSSPATTERN_ROTATE_EYES:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwMotionTime = ROTATE_EYES_TIME + GetTickCount();
			if ((float)BOSS_STAGE_MAX_SCREENX * 0.5f < m_tInfo.fX)
				m_fAngle = 180.f;
			else
				m_fAngle = 0.f;
			break;
		case BOSSPATTERN_END:
			break;
		default:
			break;
		}

		m_ePrePattern = m_eCurPattern;
	}

}

void CBossGuhu::Pattern_Change()
{

	if (false == m_bAction)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('A'))
		{
			m_bAction = true;
			m_eCurPattern = BOSSPATTERN_FIREBALL;
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('P'))
		{
			m_bAction = true;
			m_eCurPattern = BOSSPATTERN_SPAWN_EYES;
		}
		else
		{
			m_eCurPattern = BOSSPATTERN_IDLE;
		}
	}
}

void CBossGuhu::FireBall()
{
	if (BOSSPATTERN_FIREBALL != m_eCurPattern)
		return;


	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
	for (auto iter = m_GuhuEyeList.begin();
		iter != m_GuhuEyeList.end();
		++iter)
	{
		(*iter)->Set_PosX(m_fSpeed * (float)cos(m_fAngle * PI / 180.f));
	}

	if(m_dwBulletCoolTime + 300 < GetTickCount())
	{
		
		m_dwBulletCoolTime = GetTickCount();
		DWORD dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);
		float fRadian = (float)acos(fWidth / fDiagonal);
		if (m_pTarget->Get_Info().fY < m_tInfo.fY)
			fRadian = 2.f * PI - fRadian;
		float fAngle = fRadian * 180.f / PI;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, Create_Bullet<CFireBallBullet>(m_tInfo.fX, m_tInfo.fY, fAngle, dwMotionTime + (DWORD)FIREBALL_BULLET_RENDER_TIME));
		//++m_iBulletCount;
		//if (5 <= m_iBulletCount)
		//{
		//	m_iBulletCount = 0;
		//	m_eCurPattern = BOSSPATTERN_IDLE;
		//	m_dwBulletCoolTime = GetTickCount();
		//	m_bAction = false;
		//}
	}


}

void CBossGuhu::Teleport()
{
	int iCount(0);
	for (auto iter = m_GuhuEyeList.begin();
		iter != m_GuhuEyeList.end();
		++iter)
	{

		float fAngle = float(iCount++) * 72.f + 54.f;
		(*iter)->Set_Angle(fAngle);

	}

	m_tInfo.fX = BOSS_STAGE_MAX_SCREENX * 0.2f + (rand() % int(BOSS_STAGE_MAX_SCREENX * 0.6f));
	m_tInfo.fY = BOSS_STAGE_MAX_SCREENY * 0.2f + (rand() % int(BOSS_STAGE_MAX_SCREENY * 0.3f));
	for (auto iter = m_GuhuEyeList.begin();
		iter != m_GuhuEyeList.end();
		++iter)
	{
		(*iter)->Set_Pos(m_tInfo.fX + m_fDistance * (float)cos((*iter)->Get_Angle() * PI / 180.f), m_tInfo.fY + m_fDistance * (float)sin((*iter)->Get_Angle() * PI / 180.f));

	}
	if(!m_bInvincibility)
		Set_Invincibility();
	m_PatternQueue.push(BOSSPATTERN_TELEPORT);
	m_PatternQueue.push(BOSSPATTERN_IDLE);
}

void CBossGuhu::Spawn_Eyes()
{
	size_t iEyeCount = 7 - CObjMgr::Get_Instance()->Get_ObjList(OBJ_EYE).size();
	if (BOSSPATTERN_SPAWN_EYES == m_eCurPattern )
	{
		for (size_t i = 7 - iEyeCount ; i < 7; ++i)
		{
			//float fAngle = 54.f + float(i) * 72.f;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EYE, CAbstractFactory<CGuhuSlaveEye>::Create());
			//CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).back()->Set_Target(this);
			m_GuhuEyeList.push_back(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EYE).back());
		}
		int iCount(0);
		for (auto iter = m_GuhuEyeList.begin();
			iter != m_GuhuEyeList.end();
			++iter)
		{

			float fAngle = float(iCount++) * 72.f + 54.f;
			(*iter)->Set_Angle(fAngle);
			(*iter)->Set_Pos(m_tInfo.fX + m_fDistance * (float)cos((*iter)->Get_Angle() * PI / 180.f), m_tInfo.fY + m_fDistance * (float)sin((*iter)->Get_Angle() * PI / 180.f));

		}
		
		CSoundMgr::Get_Instance()->StopSound(SOUND_GUHU);
		CSoundMgr::Get_Instance()->PlaySound(L"BossGuhuEyeSummon.wav", SOUND_GUHU, 1.f);

	}
	else
		return;

}

void CBossGuhu::Rotate_Eyes()
{
	if (BOSSPATTERN_ROTATE_EYES != m_eCurPattern)
	{
		for (auto iter = m_GuhuEyeList.begin();
			iter != m_GuhuEyeList.end();
			++iter)
		{
			m_fDistance = 100.f;
			float fWidth = (*iter)->Get_Info().fX - m_tInfo.fX;
			float fHeight = (*iter)->Get_Info().fY - m_tInfo.fY;
			float fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);
			float fRadian = (float)acos(fWidth / fDiagonal);
			if ((*iter)->Get_Info().fY < m_tInfo.fY)
				fRadian = 2.f * PI - fRadian;
			float fAngle = fRadian * 180.f / PI;
			(*iter)->Set_Pos(m_tInfo.fX + m_fDistance * (float)cos(fAngle * PI / 180.f), m_tInfo.fY + m_fDistance * (float)sin(fAngle * PI / 180.f));
		}
	}
	else
	{
		m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f) * 0.5f;
		for (auto iter = m_GuhuEyeList.begin();
			iter != m_GuhuEyeList.end();
			++iter)
		{
			(*iter)->Set_PosX(m_fSpeed * (float)cos(m_fAngle * PI / 180.f) * 0.25f);
		}
		for (auto iter = m_GuhuEyeList.begin();
			iter != m_GuhuEyeList.end();
			++iter)
		{
			float fWidth = (*iter)->Get_Info().fX - m_tInfo.fX;
			float fHeight = (*iter)->Get_Info().fY - m_tInfo.fY;
			float fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);
			float fRadian = (float)acos(fWidth / fDiagonal);
			if ((*iter)->Get_Info().fY < m_tInfo.fY)
				fRadian = 2.f * PI - fRadian;
			float fAngle = fRadian * 180.f / PI;
			fAngle += 5.f;
			if(350.f>=m_fDistance) 
				m_fDistance += 0.8f;
			(*iter)->Set_Pos(m_tInfo.fX + m_fDistance * (float)cos(fAngle * PI / 180.f), m_tInfo.fY + m_fDistance * (float)sin(fAngle * PI / 180.f));
		}

	}


}

void CBossGuhu::Check_Eyes()
{
	for (auto iter = m_GuhuEyeList.begin();
		iter != m_GuhuEyeList.end();
		)
	{
		if (true == (*iter)->Get_Dead())
		{
			iter = m_GuhuEyeList.erase(iter);
		}
		else
			++iter;
	}
}
