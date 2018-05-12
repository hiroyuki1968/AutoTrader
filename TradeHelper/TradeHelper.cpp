// TradeHelper.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "TradeHelper.h"
#include "TradeHelperDlg.h"

#include <shfolder.h>
#include <htmlhelp.h>

// NOTE: This line is a hardcoded reference to an MFC header file
//  this path may need to be changed to refer to the location of VC5 install
//  for successful compilation.
#include <..\src\occimpl.h>
#include "../TradeConsole/custsite.h"

#include "../Common.h"
#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "NotesDlg.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperApp

BEGIN_MESSAGE_MAP(CTradeHelperApp, CWinApp)
	//{{AFX_MSG_MAP(CTradeHelperApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperApp �N���X�̍\�z

CTradeHelperApp::CTradeHelperApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CTradeHelperApp �I�u�W�F�N�g

CTradeHelperApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperApp �N���X�̏�����

BOOL CTradeHelperApp::InitInstance()
{
	// Create a custom control manager class so we can overide the site
	CCustomOccManager *pMgr = new CCustomOccManager;

	// Set our control containment up but using our control container 
	// management class instead of MFC's default
//	AfxEnableControlContainer();
	AfxEnableControlContainer(pMgr);

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	if (m_hExeCheckMutex) {
		DWORD flOldProtect;
		VirtualProtect((LPVOID)0x00401000, 1, PAGE_READONLY, &flOldProtect);
	}

	AfxGetModuleState()->m_dwVersion = 0x0601;

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

	CString strLastStatusIniFPath = strDataDir + _T("\\") FNAME_LASTSTATUS;
	char pszBuf[MAX_PATH];
	GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_EXENOTES, "False", pszBuf, MAX_PATH, strLastStatusIniFPath);
	if (strcmp(pszBuf, "True")) {
		CNotesDlg NotesDlg;
		BOOL bExeNotes = FALSE;
		if (NotesDlg.DoModal() == IDOK)
			strcpy(pszBuf, NotesDlg.m_bExeNotes ? "True" : "False");
	}
	WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_EXENOTES, pszBuf, strLastStatusIniFPath);

	BOOL bAutoExec = _tcsicmp(m_lpCmdLine, _T("/AutoExec")) == 0;

	int nExecMode = 0;
	CStringBuffer strExeMode;
	BOOL bMentenance0 = FALSE;
	BOOL bMentenance1 = FALSE;
	BOOL bMentenance2 = FALSE;
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
		bMentenance0 = SelExecModeDlg.m_bMentenance0;
		bMentenance1 = SelExecModeDlg.m_bMentenance1;
		bMentenance2 = SelExecModeDlg.m_bMentenance2;
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
	CStringBuffer strTradeConsoleWndName = TRADECONSOLE_EXENAME + strVer;

	// �v���O�����̕����N���}�~
	// �����A�I�[�v���ł���ΈȑO�̃A�v���P�[�V�������N�����Ă���
	CStringBuffer strMutex = StrFormat(MUTEX_TRADEHELPER_INSTANCE _T("_%06d"), THIS_VER) + strUlExeMode;
	HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
	if (hPrevMutex) {
		// �N���[�Y
		CloseHandle(hPrevMutex);
		// ���Ɏ��s����Ă��邩
		CWnd* pWnd;
		if (pWnd = CWnd::FindWindow(NULL, strTradeHelperWndName)) {
			pWnd->SendMessage(WM_OPENWND);
			SetAbsoluteForegroundWindow(pWnd->GetSafeHwnd());
		}
		return FALSE;
	}
	// �����N���m�F�p�~���[�e�b�N�X�쐬
	m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);

	CTradeHelperDlg dlg;
	dlg.m_nThisVer = THIS_VER;
	dlg.m_strDir = m_strDir;
	dlg.m_strDataDir = strDataDir;
	dlg.m_strMainExeWndName = strMainExeWndName;
	dlg.m_strChartViewerWndName = strChartViewerWndName;
	dlg.m_strKehaiViewerWndName = strKehaiViewerWndName;
	dlg.m_strTradeHelperWndName = strTradeHelperWndName;
	dlg.m_strTradeConsoleWndName = strTradeConsoleWndName;
	dlg.m_strUlExeMode = strUlExeMode;
	dlg.m_nExecMode = nExecMode;
	dlg.m_bMentenance0 = bMentenance0;
	dlg.m_bMentenance1 = bMentenance1;
	dlg.m_bMentenance2 = bMentenance2;
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

void CTradeHelperApp::WinHelp(DWORD dwData, UINT nCmd) 
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
	CTradeHelperDlg* pTradeHelperDlg = (CTradeHelperDlg *)theApp.m_pMainWnd;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (
			lpMsg->message == WM_KEYDOWN
			||  lpMsg->message == WM_KEYUP
		)
		{
			BOOL bNull = FALSE;

			if (lpMsg->message == WM_KEYDOWN) {
				HWND hwnd = lpMsg->hwnd;
				TCHAR pszClassName[26];
				BOOL bNotEdit;

				GetClassName(lpMsg->hwnd, pszClassName, sizeof(pszClassName) / sizeof(TCHAR));
				bNotEdit = strcmp(pszClassName, "Edit")  ||  hwnd == pTradeHelperDlg->m_Edit1.m_hWnd;

				switch (lpMsg->wParam) {
				case VK_F2:
					pTradeHelperDlg->ButtonF2();
					bNull = TRUE;
					break;
				case VK_F3:
					pTradeHelperDlg->ButtonF3();
					bNull = TRUE;
					break;
				case VK_F4:
					pTradeHelperDlg->ButtonF4();
					bNull = TRUE;
					break;
				case VK_F6:
					pTradeHelperDlg->ButtonF6();
					bNull = TRUE;
					break;
				case VK_F7:
					pTradeHelperDlg->ButtonF7();
					bNull = TRUE;
					break;
				case VK_F8:
					pTradeHelperDlg->ButtonF8();
					bNull = TRUE;
					break;
				case VK_F9:
					pTradeHelperDlg->ButtonF9();
					bNull = TRUE;
					break;
				case VK_F11:
					pTradeHelperDlg->ButtonF11();
					bNull = TRUE;
					break;
				case VK_F12:
					pTradeHelperDlg->ButtonF12();
					bNull = TRUE;
					break;
				case VK_LEFT:
					if (bNotEdit) {
						if (pTradeHelperDlg->m_Check5.GetCheck() == 1) {
							SYSTEMTIME StDate;
							COleDateTime DtDate;
							COleDateTimeSpan Dts1Day(1, 0, 0, 0);
							int nDayOfWeek;
							pTradeHelperDlg->m_MonthCalCtrl1.GetCurSel(&StDate);
							DtDate.SetDate(StDate.wYear, StDate.wMonth, StDate.wDay);
							do {
								DtDate -= Dts1Day;
								nDayOfWeek = DtDate.GetDayOfWeek();
							} while (nDayOfWeek == 1  ||  nDayOfWeek == 7);
							DtDate.GetAsSystemTime(StDate);
							pTradeHelperDlg->m_MonthCalCtrl1.SetCurSel(&StDate);
							pTradeHelperDlg->SetWMUserTimer(0, 9, NULL);
							pTradeHelperDlg->SetWMUserTimer(0, 10, NULL);
							pTradeHelperDlg->SetWMUserTimer(0, 15, NULL);
						} else {
							CWnd* pWnd;
							if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strChartViewerWndName)))
								pWnd->PostMessage(WM_USER + 6, 0);
							if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strKehaiViewerWndName)))
								pWnd->PostMessage(WM_USER + 6, 0);
						}
						bNull = TRUE;
					}
					break;
				case VK_RIGHT:
					if (bNotEdit) {
						if (pTradeHelperDlg->m_Check5.GetCheck() == 1) {
							SYSTEMTIME StDate;
							COleDateTime DtDate;
							COleDateTimeSpan Dts1Day(1, 0, 0, 0);
							int nDayOfWeek;
							pTradeHelperDlg->m_MonthCalCtrl1.GetCurSel(&StDate);
							DtDate.SetDate(StDate.wYear, StDate.wMonth, StDate.wDay);
							do {
								DtDate += Dts1Day;
								nDayOfWeek = DtDate.GetDayOfWeek();
							} while (nDayOfWeek == 1  ||  nDayOfWeek == 7);
							DtDate.GetAsSystemTime(StDate);
							pTradeHelperDlg->m_MonthCalCtrl1.SetCurSel(&StDate);
							pTradeHelperDlg->SetWMUserTimer(0, 9, NULL);
							pTradeHelperDlg->SetWMUserTimer(0, 10, NULL);
							pTradeHelperDlg->SetWMUserTimer(0, 15, NULL);
						} else {
							CWnd* pWnd;
							if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strChartViewerWndName)))
								pWnd->PostMessage(WM_USER + 6, 2);
							if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strKehaiViewerWndName)))
								pWnd->PostMessage(WM_USER + 6, 2);
						}
						bNull = TRUE;
					}
					break;
				case VK_INSERT:
					if (GetKeyState(VK_SHIFT) < 0) {
						pTradeHelperDlg->SetWMUserTimer(0U, 29, NULL);
						pTradeHelperDlg->SetWMUserTimer(0U, 31, NULL);
					} else if (GetKeyState(VK_CONTROL) < 0)
						pTradeHelperDlg->SetWMUserTimer(0U, 22, NULL);
					else {
						pTradeHelperDlg->SetWMUserTimer(0U, 11, NULL);
						pTradeHelperDlg->SetTimer(33, 500U, NULL);
						pTradeHelperDlg->SetWMUserTimer(4000U, 34, NULL);
					}
					bNull = TRUE;
					break;
				case VK_DELETE:
					if (bNotEdit) {
						if (GetKeyState(VK_SHIFT) < 0) {
							pTradeHelperDlg->SetWMUserTimer(0U, 30, NULL);
							pTradeHelperDlg->SetWMUserTimer(0U, 32, NULL);
						} else if (GetKeyState(VK_CONTROL) < 0)
							pTradeHelperDlg->SetWMUserTimer(0U, 23, NULL);
						else
							pTradeHelperDlg->SetWMUserTimer(0U, 12, NULL);
						bNull = TRUE;
					}
				}
			} else {
				switch (lpMsg->wParam) {
				case VK_F5:
					pTradeHelperDlg->ButtonF5();
					bNull = TRUE;
					break;
				case VK_SNAPSHOT:
					if (pTradeHelperDlg->m_Check5.GetCheck() == 1) {
						SYSTEMTIME StDate;
						COleDateTime DtCur = COleDateTime::GetCurrentTime();
						COleDateTime DtDate = DtCur;
						COleDateTimeSpan Dts1Day(1, 0, 0, 0);
						int nCurYear = DtCur.GetYear();
						int nCurMonth = DtCur.GetMonth();
						int nCurDay = DtCur.GetDay();
						int nCurHour = DtCur.GetHour();
						int nDayOfWeek;
						while (
							(nDayOfWeek = DtDate.GetDayOfWeek()) == 1
							||  nDayOfWeek == 7
							||  nCurHour < 17  &&  DtDate.GetYear() == nCurYear  &&  DtDate.GetMonth() == nCurMonth  &&  DtDate.GetDay() == nCurDay
						)
							DtDate -= Dts1Day;
						DtDate.GetAsSystemTime(StDate);
						pTradeHelperDlg->m_MonthCalCtrl1.SetCurSel(&StDate);
						pTradeHelperDlg->SetWMUserTimer(0, 9, NULL);
						pTradeHelperDlg->SetWMUserTimer(0, 10, NULL);
						pTradeHelperDlg->SetWMUserTimer(0, 15, NULL);
					}
					{
						CWnd* pWnd;
						if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strChartViewerWndName)))
							pWnd->PostMessage(WM_USER + 6, 1);
						if ((pWnd = CWnd::FindWindow(NULL, pTradeHelperDlg->m_strKehaiViewerWndName)))
							pWnd->PostMessage(WM_USER + 6, 1);
						bNull = TRUE;
					}
				}
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pTradeHelperDlg->m_hHook, nCode, wParam, lParam);
}
