// TradeConsole.h : TRADECONSOLE �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_TRADECONSOLE_H__1032A44B_BF7C_44ED_A5FC_0626CC9AD9B4__INCLUDED_)
#define AFX_TRADECONSOLE_H__1032A44B_BF7C_44ED_A5FC_0626CC9AD9B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� TradeConsole.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CTradeConsoleApp : public CWinApp
{
public:
	CTradeConsoleApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTradeConsoleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CTradeConsoleApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TRADECONSOLE_H__1032A44B_BF7C_44ED_A5FC_0626CC9AD9B4__INCLUDED_)
