// AutoTrader.h : AUTOTRADER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_)
#define AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� AutoTrader.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CAutoTraderApp : public CWinApp
{
public:
	CAutoTraderApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAutoTraderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int ReadProductCode(CStringBuffer& strProductCode);
	void DelWorkFile(int nMode, const CStringBuffer& strDataDir, BOOL bEqDataDir);
	OSVERSIONINFO m_OSVI;
	CFileStatus m_FileStatus;
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CAutoTraderApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_)
