// RandChart.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "RandChart.h"
#include "RandChartDlg.h"

#include <shfolder.h>
#include <htmlhelp.h>

#include "../Common.h"
#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "RandChartDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp

BEGIN_MESSAGE_MAP(CRandChartApp, CWinApp)
	//{{AFX_MSG_MAP(CRandChartApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp �N���X�̍\�z

CRandChartApp::CRandChartApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CRandChartApp �I�u�W�F�N�g

CRandChartApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp �N���X�̏�����

BOOL CRandChartApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	AfxGetModuleState()->m_dwVersion = 0x0601;

	if (m_hExeCheckMutex) {
		DWORD flOldProtect;
		VirtualProtect((LPVOID)0x00401000, 1, PAGE_READONLY, &flOldProtect);
	}

	// Exe �t�H���_
	m_strDir = GetDPathFromFPath(m_pszHelpFilePath);

	// �f�t�H���g�f�[�^�t�H���_
	CStringBuffer strAppDataDir = GetLongPath(GetShFolderPath(CSIDL_APPDATA | CSIDL_FLAG_CREATE));
	if (strAppDataDir.IsEmpty()) {
		AfxMessageBox(_T("�A�v���P�[�V�����f�[�^�t�H���_�p�X���擾�G���["), MB_ICONSTOP);
		return FALSE;
	}
	if (strAppDataDir.Right(1) == _T("\\"))
		strAppDataDir = strAppDataDir.Left(strAppDataDir.GetLength() - 1);
	CStringBuffer strDefaultDataDir = strAppDataDir + _T("\\") DNAME_AUTOTRADER;

	HKEY hKey;
	_TCHAR lpRegData[MAX_PATH];
	DWORD cbRegDataSize;

	// BaseStatus
	CStringBuffer strDataDir;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		// �f�[�^�t�H���_
		cbRegDataSize = MAX_PATH;
		if (RegQueryValueEx(hKey, REG_KEY_DATAFOLDER, NULL, NULL, (LPBYTE)lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			strDataDir = lpRegData;
		RegCloseKey(hKey);
	}
	if (strDataDir.IsEmpty())
		strDataDir = strDefaultDataDir;

	// �E�B���h�E��
#if THIS_VER % 100
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d.%d%s"), THIS_VER / 10000, THIS_VER % 10000 / 100, THIS_VER % 100, THIS_VER % 100 < 51 ? _T("��") : _T("��"));
#else
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d"), THIS_VER / 10000, THIS_VER % 10000 / 100);
#endif
	CStringBuffer strRandChartWndName = RANDCHART_EXENAME + strVer;

	CRandChartDlg dlg;
	dlg.m_nThisVer = THIS_VER;
	dlg.m_strDir = m_strDir;
	dlg.m_strDataDir = strDataDir;
	dlg.m_strRandChartWndName = strRandChartWndName;
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

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

void CRandChartApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	//������OS���̃`�F�b�N���s���Ƃ悢
	//OSVERSIONINFO os_info;
	//os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//GetVersionEx(&os_info);

	//����͍쐬����HtmlHelp�ɂ��قȂ�
	//dwData��ϊ�����R�[�h���K�v
	_TCHAR* szFileName = FNAME_HELP_HTM;

	CString strHelpPath = m_pszHelpFilePath;
	strHelpPath = strHelpPath.Left(strHelpPath.ReverseFind(_T('\\')) + 1) + FNAME_HELP_CHM;

	HtmlHelp(NULL, strHelpPath, HH_DISPLAY_TOPIC, (DWORD)szFileName);
	
// ��{�N���X�̃����o�֐��͌Ă΂Ȃ�
//	CWinApp::WinHelp(dwData, nCmd);
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CRandChartDlg* pRandChartDlg = (CRandChartDlg *)theApp.m_pMainWnd;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (
			lpMsg->message == WM_KEYDOWN
		)
		{
			BOOL bNull = FALSE;

			switch (lpMsg->wParam) {
			case VK_SPACE:
				pRandChartDlg->SetParam();
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_INSERT:
				pRandChartDlg->m_nMode = 0;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_DELETE:
				pRandChartDlg->m_nMode = 1;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_LEFT:
				if (pRandChartDlg->m_nIndex)
					pRandChartDlg->m_nIndex --;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_UP:
				pRandChartDlg->m_nIndex = pRandChartDlg->m_Pa.GetUpperBound();
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_RIGHT:
				if (pRandChartDlg->m_nIndex < pRandChartDlg->m_Pa.GetUpperBound())
					pRandChartDlg->m_nIndex ++;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_DOWN:
				pRandChartDlg->m_nIndex = 0;
				pRandChartDlg->Disp();
				bNull = TRUE;
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pRandChartDlg->m_hHook, nCode, wParam, lParam);
}
