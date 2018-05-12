// RandChart.h : RANDCHART �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_RANDCHART_H__9D529842_AC5E_441D_BECE_835520435AD0__INCLUDED_)
#define AFX_RANDCHART_H__9D529842_AC5E_441D_BECE_835520435AD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� RandChart.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CRandChartApp : public CWinApp
{
public:
	CRandChartApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRandChartApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CRandChartApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RANDCHART_H__9D529842_AC5E_441D_BECE_835520435AD0__INCLUDED_)
