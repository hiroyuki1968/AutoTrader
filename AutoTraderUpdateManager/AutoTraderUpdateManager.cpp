// AutoTraderUpdateManager.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "AutoTraderUpdateManager.h"
//#include "AutoTraderUpdateManagerDlg.h"

#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp

BEGIN_MESSAGE_MAP(CAutoTraderUpdateManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CAutoTraderUpdateManagerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp �N���X�̍\�z

CAutoTraderUpdateManagerApp::CAutoTraderUpdateManagerApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CAutoTraderUpdateManagerApp �I�u�W�F�N�g

CAutoTraderUpdateManagerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp �N���X�̏�����

BOOL CAutoTraderUpdateManagerApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

/*
	CAutoTraderUpdateManagerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
*/
	m_pMainWnd = &m_AutoTraderUpdateManagerWnd;
	CString strDefaultWndClassName(AfxRegisterWndClass(NULL));
	if (! m_AutoTraderUpdateManagerWnd.CreateEx(WS_EX_TOOLWINDOW, strDefaultWndClassName, _T("AutoTraderUpdateManager"), NULL, 0, 0, 1, 1, GetDesktopWindow(), NULL)) {
		AfxMessageBox(_T("�E�B���h�E�쐬�G���[: ") + GetLastErrorMessage(), MB_ICONSTOP);
		return FALSE;
	}

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
//	return FALSE;
	return TRUE;
}
