// TradeHelper.h : TRADEHELPER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_)
#define AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� TradeHelper.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CTradeHelperApp : public CWinApp
{
public:
	CTradeHelperApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTradeHelperApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CTradeHelperApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_)
