// KehaiViewer.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "KehaiViewer.h"
#include "KehaiViewerDlg.h"

#include <shfolder.h>
#include <htmlhelp.h>

#include "../Common.h"
#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "KehaiViewerDef.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerApp

BEGIN_MESSAGE_MAP(CKehaiViewerApp, CWinApp)
	//{{AFX_MSG_MAP(CKehaiViewerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerApp �N���X�̍\�z

CKehaiViewerApp::CKehaiViewerApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CKehaiViewerApp �I�u�W�F�N�g

CKehaiViewerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerApp �N���X�̏�����

BOOL CKehaiViewerApp::InitInstance()
{
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

	BOOL bAutoExec = _tcsicmp(m_lpCmdLine, _T("/AutoExec")) == 0;

	int nExecMode = 0;
	CStringBuffer strExeMode;
	if (! bAutoExec) {
		CSelExecModeDlg SelExecModeDlg;
		if (SelExecModeDlg.DoModal() == IDCANCEL) {
			PostQuitMessage(0);
			return FALSE;
		}
		switch (nExecMode = SelExecModeDlg.m_nExecMode) {
		case 1:
			strExeMode = "TimeSim";
			break;
		case 2:
			strExeMode = "RealTimeSim";
		}
	}

	// �E�B���h�E��
#if THIS_VER % 100
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d.%d%s"), THIS_VER / 10000, THIS_VER % 10000 / 100, THIS_VER % 100, THIS_VER % 100 < 51 ? _T("��") : _T("��"));
#else
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d"), THIS_VER / 10000, THIS_VER % 10000 / 100);
#endif
	CStringBuffer strSpcExeMode = strExeMode.IsEmpty() ? pszEmpty : _T(' ') + strExeMode;
	CStringBuffer strUlExeMode = strExeMode.IsEmpty() ? pszEmpty : _T('_') + strExeMode;
	CStringBuffer strMainExeWndNameNoCmdLine = MAIN_EXENAME + strVer;
	CStringBuffer strMainExeWndName = strMainExeWndNameNoCmdLine + strSpcExeMode;
	CStringBuffer strChartViewerWndName = CHARTVIEWER_EXENAME + strVer + strSpcExeMode;
	CStringBuffer strKehaiViewerWndName = KEHAIVIEWER_EXENAME + strVer + strSpcExeMode;
	CStringBuffer strTradeHelperWndName = TRADEHELPER_EXENAME + strVer + strSpcExeMode;

	// �v���O�����̕����N���}�~
	// �����A�I�[�v���ł���ΈȑO�̃A�v���P�[�V�������N�����Ă���
	CStringBuffer strMutex = StrFormat(MUTEX_KEHAIVIEWER_INSTANCE _T("_%06d"), THIS_VER) + strUlExeMode;
	HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
	if (hPrevMutex) {
		// �N���[�Y
		CloseHandle(hPrevMutex);
		// ���Ɏ��s����Ă��邩
		CWnd* pWnd;
		if (pWnd = CWnd::FindWindow(NULL, strKehaiViewerWndName)) {
			pWnd->SendMessage(WM_OPENWND);
			SetAbsoluteForegroundWindow(pWnd->GetSafeHwnd());
		}
		return FALSE;
	}
	// �����N���m�F�p�~���[�e�b�N�X�쐬
	m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);

	CKehaiViewerDlg dlg;
	dlg.m_nThisVer = THIS_VER;
	dlg.m_strDir = m_strDir;
	dlg.m_strDataDir = strDataDir;
	dlg.m_strMainExeWndName = strMainExeWndName;
	dlg.m_strChartViewerWndName = strChartViewerWndName;
	dlg.m_strKehaiViewerWndName = strKehaiViewerWndName;
	dlg.m_strTradeHelperWndName = strTradeHelperWndName;
	dlg.m_strUlExeMode = strUlExeMode;
	dlg.m_nExecMode = nExecMode;
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

int CKehaiViewerApp::ExitInstance() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	if (m_hExeCheckMutex)
		CloseHandle(m_hExeCheckMutex);
	
	return CWinApp::ExitInstance();
}

void CKehaiViewerApp::WinHelp(DWORD dwData, UINT nCmd) 
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
	CKehaiViewerDlg* pKehaiViewerDlg = (CKehaiViewerDlg *)theApp.m_pMainWnd;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (
			lpMsg->message == WM_KEYDOWN
			||  lpMsg->message == WM_KEYUP
		)
		{
			CWnd* pWnd;
			BOOL bNull = FALSE;

			if (lpMsg->message == WM_KEYDOWN) {
				switch (lpMsg->wParam) {
				case VK_F2:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 6);
					bNull = TRUE;
					break;
				case VK_F3:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 7);
					bNull = TRUE;
					break;
				case VK_F4:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 8);
					bNull = TRUE;
					break;
				case VK_F5:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 9);
					bNull = TRUE;
					break;
				case VK_F6:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 10);
					bNull = TRUE;
					break;
				case VK_F7:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 11);
					bNull = TRUE;
					break;
				case VK_F8:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 12);
					bNull = TRUE;
					break;
				case VK_F9:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 13);
					bNull = TRUE;
					break;
				case VK_F11:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 14);
					bNull = TRUE;
					break;
				case VK_F12:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						pWnd->PostMessage(WM_USER + 5, 15);
					bNull = TRUE;
					break;
				case VK_LEFT:
					if (-- pKehaiViewerDlg->m_nPage < 0)
						pKehaiViewerDlg->m_nPage = 1 + pKehaiViewerDlg->m_SaSelCode.GetUpperBound() / 10;
					pKehaiViewerDlg->KillWMUserTimer(4);
					pKehaiViewerDlg->SetWMUserTimer(0, 4, NULL);
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strChartViewerWndName)))
						pWnd->PostMessage(WM_USER + 5, pKehaiViewerDlg->m_nPage);
					bNull = TRUE;
					break;
				case VK_UP:
					pKehaiViewerDlg->m_nPage = 0;
					pKehaiViewerDlg->KillWMUserTimer(2);
					pKehaiViewerDlg->SetWMUserTimer(0, 2, NULL);
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strChartViewerWndName)))
						pWnd->PostMessage(WM_USER + 5, pKehaiViewerDlg->m_nPage);
					bNull = TRUE;
					break;
				case VK_RIGHT:
					if (++ pKehaiViewerDlg->m_nPage > 1 + pKehaiViewerDlg->m_SaSelCode.GetUpperBound() / 10)
						pKehaiViewerDlg->m_nPage = 0;
					pKehaiViewerDlg->KillWMUserTimer(4);
					pKehaiViewerDlg->SetWMUserTimer(0, 4, NULL);
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strChartViewerWndName)))
						pWnd->PostMessage(WM_USER + 5, pKehaiViewerDlg->m_nPage);
					bNull = TRUE;
					break;
				case VK_INSERT:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						if (GetKeyState(VK_SHIFT) < 0)
							pWnd->PostMessage(WM_USER + 5, 0);
						else if (GetKeyState(VK_CONTROL) < 0)
							pWnd->PostMessage(WM_USER + 5, 1);
						else
							pWnd->PostMessage(WM_USER + 5, 2);
					bNull = TRUE;
					break;
				case VK_DELETE:
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strTradeHelperWndName)))
						if (GetKeyState(VK_SHIFT) < 0)
							pWnd->PostMessage(WM_USER + 5, 3);
						else if (GetKeyState(VK_CONTROL) < 0)
							pWnd->PostMessage(WM_USER + 5, 4);
						else
							pWnd->PostMessage(WM_USER + 5, 5);
					bNull = TRUE;
				}
			} else {
				switch (lpMsg->wParam) {
				case VK_SNAPSHOT:
					pKehaiViewerDlg->m_nPage = 0;
					pKehaiViewerDlg->KillWMUserTimer(4);
					pKehaiViewerDlg->SetWMUserTimer(0, 4, NULL);
					if ((pWnd = CWnd::FindWindow(NULL, pKehaiViewerDlg->m_strChartViewerWndName)))
						pWnd->PostMessage(WM_USER + 5, pKehaiViewerDlg->m_nPage);
					bNull = TRUE;
				}
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pKehaiViewerDlg->m_hHook, nCode, wParam, lParam);
}
