#pragma once

#define TEXTBOX_CX 672
#define TEXTBOX_CY 144
#define TEXTBOX_LEFT ((WINCX - TEXTBOX_CX) * 0.5f)
#define TEXTBOX_TOP (WINCY - 192)
#define TEXTBOX_RIGHT ((WINCX + TEXTBOX_CX) * 0.5f)
#define TEXTBOX_BOTTOM (TEXTBOX_TOP + TEXTBOX_CY)

class CTextBoxMgr
{
private:
	CTextBoxMgr();
	~CTextBoxMgr();

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Set_Text(TCHAR* _szText) { m_szText = _szText; }
	TCHAR* Get_Text() { return m_szText; }

	void		Set_IsTextBoxON();
	bool		Get_IsTextBoxON() { return m_bIsTextBoxON; }

	void		Key_Input();


private:
	TCHAR* m_szText;
	bool m_bIsTextBoxON;


public:
	static CTextBoxMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTextBoxMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTextBoxMgr* m_pInstance;

};
