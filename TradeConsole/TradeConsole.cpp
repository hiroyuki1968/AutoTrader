// TradeConsole.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "TradeConsole.h"
#include "TradeConsoleDlg.h"

#include <shfolder.h>
#include <htmlhelp.h>

// NOTE: This line is a hardcoded reference to an MFC header file
//  this path may need to be changed to refer to the location of VC5 install
//  for successful compilation.
#include <..\src\occimpl.h>
#include "custsite.h"

#include "../Common.h"
#include "../AutoTraderVer.h"
#include "NotesDlg.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleApp

BEGIN_MESSAGE_MAP(CTradeConsoleApp, CWinApp)
	//{{AFX_MSG_MAP(CTradeConsoleApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleApp �N���X�̍\�z

CTradeConsoleApp::CTradeConsoleApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CTradeConsoleApp �I�u�W�F�N�g

CTradeConsoleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleApp �N���X�̏�����

BOOL CTradeConsoleApp::InitInstance()
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

	BOOL bMentenance0 = FALSE;
	BOOL bMentenance1 = FALSE;
	BOOL bMentenance2 = FALSE;
	if (! bAutoExec) {
		CSelExecModeDlg SelExecModeDlg;
		if (SelExecModeDlg.DoModal() == IDCANCEL) {
			PostQuitMessage(0);
			return FALSE;
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
	CStringBuffer strTradeConsoleWndName = TRADECONSOLE_EXENAME + strVer;
	CStringBuffer strTradeHelperWndName = TRADEHELPER_EXENAME + strVer;

	// �v���O�����̕����N���}�~
	// �����A�I�[�v���ł���ΈȑO�̃A�v���P�[�V�������N�����Ă���
	CStringBuffer strMutex = StrFormat(MUTEX_TRADECONSOLE_INSTANCE _T("_%06d"), THIS_VER);
	HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
	if (hPrevMutex) {
		// �N���[�Y
		CloseHandle(hPrevMutex);
		// ���Ɏ��s����Ă��邩
		CWnd* pWnd;
		if (pWnd = CWnd::FindWindow(NULL, strTradeConsoleWndName)) {
			pWnd->SendMessage(WM_OPENWND);
			SetAbsoluteForegroundWindow(pWnd->GetSafeHwnd());
		}
		return FALSE;
	}
	// �����N���m�F�p�~���[�e�b�N�X�쐬
	m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);

	CTradeConsoleDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_strTradeHelperWndName = strTradeHelperWndName;
	dlg.m_strTradeConsoleWndName = strTradeConsoleWndName;
	dlg.m_bMentenance0 = bMentenance0;
	dlg.m_bMentenance1 = bMentenance1;
	dlg.m_bMentenance2 = bMentenance2;
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

int CTradeConsoleApp::ExitInstance() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	if (m_hExeCheckMutex)
		CloseHandle(m_hExeCheckMutex);
	
	return CWinApp::ExitInstance();
}

void CTradeConsoleApp::WinHelp(DWORD dwData, UINT nCmd) 
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
	CTradeConsoleDlg* pTradeConsoleDlg = (CTradeConsoleDlg *)theApp.m_pMainWnd;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (
			lpMsg->message == WM_KEYDOWN
		)
		{
			BOOL bNull = FALSE;

			if (lpMsg->wParam == VK_TAB) {
				if (GetKeyState(VK_CONTROL) < 0) {
					CTabCtrl& TabCtrl1 = pTradeConsoleDlg->m_TabCtrl1;
					int nCurSel = TabCtrl1.GetCurSel();
					if (GetKeyState(VK_SHIFT) < 0) {
						if (-- nCurSel < 0)
							nCurSel = TabCtrl1.GetItemCount() - 1;
					} else
						if (++ nCurSel >= TabCtrl1.GetItemCount())
							nCurSel = 0;
					TabCtrl1.SetCurSel(nCurSel);
					pTradeConsoleDlg->SelchangeTab1();
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

	return CallNextHookEx(pTradeConsoleDlg->m_hHook, nCode, wParam, lParam);
}
