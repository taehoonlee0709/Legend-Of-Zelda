#pragma once
#include "Define.h"
#include "Obj.h"

enum ITEMCODE { SWORD, WAND, SHIELD, BOOMERANG, ITEMCODE_END };

class CItem : public CObj
{

public:
	CItem() : m_eItemCode(ITEMCODE_END)
	{
		ZeroMemory(&m_tItemInfo, sizeof(ITEM));
	}
	virtual ~CItem() {}


public:
	virtual void Initialize(); //���⼭ �̸��̶� ���� �־��ָ� �ɵ�.������ Ŭ��������.
	virtual int Update()
	{
		if (true == m_bDead)
			return OBJ_DEAD;
		__super::Update_Rect();
		return OBJ_NOEVENT;
	}
	void Late_Update() override;
	void Render(HDC hDC) override;
	virtual void Release() { return; }

	ITEMCODE Get_ItemCode() { return m_eItemCode; }
	void Set_ItemCode(ITEMCODE _eId) { m_eItemCode = _eId; }

protected:
	ITEM		m_tItemInfo;
	ITEMCODE	m_eItemCode;

	// CObj��(��) ���� ��ӵ�

};

