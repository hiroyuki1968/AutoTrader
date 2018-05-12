// KehaiViewer.h : KEHAIVIEWER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_KEHAIVIEWER_H__F3C67F68_82A4_4E74_A908_D9DEEB4DFE56__INCLUDED_)
#define AFX_KEHAIVIEWER_H__F3C67F68_82A4_4E74_A908_D9DEEB4DFE56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� KehaiViewer.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CKehaiViewerApp : public CWinApp
{
public:
	CKehaiViewerApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CKehaiViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CKehaiViewerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_KEHAIVIEWER_H__F3C67F68_82A4_4E74_A908_D9DEEB4DFE56__INCLUDED_)
