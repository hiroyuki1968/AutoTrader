// AutoTraderUpdateManager.h : AUTOTRADERUPDATEMANAGER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "AutoTraderUpdateManagerWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� AutoTraderUpdateManager.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CAutoTraderUpdateManagerApp : public CWinApp
{
public:
	CAutoTraderUpdateManagerApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	CAutoTraderUpdateManagerWnd m_AutoTraderUpdateManagerWnd;

	//{{AFX_MSG(CAutoTraderUpdateManagerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_)
