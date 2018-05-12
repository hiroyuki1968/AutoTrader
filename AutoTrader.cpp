// AutoTrader.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "AutoTrader.h"
#include "AutoTraderDlg.h"

#include <Lmcons.h>
#include <shfolder.h>
#include <htmlhelp.h>

#include "AutoTraderVer.h"
#include "AutoTraderDef.h"
#include "Common.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderApp

BEGIN_MESSAGE_MAP(CAutoTraderApp, CWinApp)
	//{{AFX_MSG_MAP(CAutoTraderApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderApp �N���X�̍\�z

CAutoTraderApp::CAutoTraderApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CAutoTraderApp �I�u�W�F�N�g

CAutoTraderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderApp �N���X�̏�����

BOOL CAutoTraderApp::InitInstance()
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

	if (m_hExeCheckMutex) {
		DWORD flOldProtect;
		VirtualProtect((LPVOID)0x00401000, 1, PAGE_READONLY, &flOldProtect);
	}

	AfxGetModuleState()->m_dwVersion = 0x0601;

	int i;
	int imax;

	// Exe �t�H���_
	m_strDir = GetDPathFromFPath(m_pszHelpFilePath);

	// OS �̃o�[�W����
	m_OSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&m_OSVI);

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

	// �A�b�v�f�[�g�t�@�C���폜

	CStringBuffer strCommonDataDir =
		GetLongPath(GetShFolderPath(m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT ? CSIDL_COMMON_APPDATA : CSIDL_APPDATA)) + _T("\\") MAIN_EXENAME;

	CStringBuffer strPersonalDataDir = strDataDir;

	BOOL bEqDataDir = strPersonalDataDir.CompareNoCase(strCommonDataDir) == 0;

	DelWorkFile(0, strCommonDataDir, bEqDataDir);

	// �A�b�v�f�[�g�}�l�[�W���[���[�U�[���`�F�b�N
	if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		HWND hWndUpdateManager;
		if (hWndUpdateManager = FindWindow(NULL, _T("AutoTraderUpdateManager"))) {
			TCHAR lpUserName[UNLEN + 1];
			DWORD dwUserNameSize = UNLEN + 1;
			if (! GetUserName(lpUserName, &dwUserNameSize)) {
				AfxMessageBox(_T("���[�U�[���擾�G���[: ") + GetLastErrorMessage(), MB_ICONSTOP);
				return FALSE;
			}
			CStringBuffer strProductCode;
			if (ReadProductCode(strProductCode))
				return FALSE;
			int nPreInstallVer;
			for (i = 0, imax = _tcslen(lpUserName); i < imax; i ++)
				nPreInstallVer = SendMessage(hWndUpdateManager, WM_USERNAME, lpUserName[i], THIS_VER);
			BOOL bCreateKey = FALSE;
			for (i = 0, imax = strProductCode.GetLength(); i < imax; i ++)
				SendMessage(hWndUpdateManager, WM_PRODUCTCODE, strProductCode[i], 0);
			LRESULT lResult = SendMessage(hWndUpdateManager, WM_USERNAME, 0, 0);
			if (lResult)
				return FALSE;
		}
	}

	CStringBuffer strSrcFPath;
	CStringBuffer strDstFPath;

	if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		// �A�b�v�f�[�g�}�l�[�W���[�I���ҋ@
		CStringBuffer strUpdateManagerFPath(strDataDir + _T("\\") MAIN_EXENAME _T("999999b\\") FNAME_UPDATEMANAGEREXE);
		if (WaitExeFPath(strUpdateManagerFPath, m_OSVI))
			return FALSE;
	}

	// �A�b�v�f�[�g�t�@�C���폜
	DelWorkFile(1, strPersonalDataDir, bEqDataDir);

	// �R�}���h ���C������
	BOOL bUpdateCheck = _tcsicmp(m_lpCmdLine, _T("/UpdateCheck")) == 0;
	BOOL bUninstall = _tcsicmp(m_lpCmdLine, _T("/Uninstall")) == 0;
	BOOL bAutoExec = _tcsicmp(m_lpCmdLine, _T("/AutoExec")) == 0;

	// �A���C���X�g�[��
	if (bUninstall) {
		CStringBuffer strProductCode;
		if (ReadProductCode(strProductCode))
			return FALSE;

		HINSTANCE hShellExecute;
		if ((int)(hShellExecute = ShellExecute(NULL, _T("open"), _T("msiexec"), _T("/x ") + strProductCode, NULL, SW_SHOWNORMAL)) <= 32)
			AfxMessageBox(_T("�A���C���X�g�[���[���s�G���[: ") + GetShellExecuteErrorText(hShellExecute), MB_ICONSTOP);
		return FALSE;
	}

	int nExecMode = 0;
	CStringBuffer strExeMode;
	BOOL bMentenance0 = FALSE;
	BOOL bMentenance1 = FALSE;
	BOOL bMentenance2 = FALSE;
	COleDateTime DtSimStart;
	if (! bUpdateCheck  &&  ! bUninstall  &&  ! bAutoExec) {
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
		DtSimStart = SelExecModeDlg.m_DtSimStart;
	}

	// �E�B���h�E��
#if THIS_VER % 100
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d.%d%s"), THIS_VER / 10000, THIS_VER % 10000 / 100, THIS_VER % 100, THIS_VER % 100 < 51 ? _T("��") : _T("��"));
#else
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d"), THIS_VER / 10000, THIS_VER % 10000 / 100);
#endif
	CStringBuffer strCmdLine = bUpdateCheck ? m_lpCmdLine : pszEmpty;
	CStringBuffer strSpcCmdLine = strCmdLine.IsEmpty() ? pszEmpty : _T(' ') + strCmdLine;
	CStringBuffer strUlCmdLine = strCmdLine.IsEmpty() ? pszEmpty : _T('_') + strCmdLine;
	CStringBuffer strSpcExeMode = strExeMode.IsEmpty() ? pszEmpty : _T(' ') + strExeMode;
	CStringBuffer strUlExeMode = strExeMode.IsEmpty() ? pszEmpty : _T('_') + strExeMode;
	CStringBuffer strMainExeWndNameNoCmdLine = MAIN_EXENAME + strVer;
	CStringBuffer strMainExeWndName = strMainExeWndNameNoCmdLine + strSpcCmdLine + strSpcExeMode;
	CStringBuffer strChartViewerWndName = CHARTVIEWER_EXENAME + strVer + strSpcExeMode;
	CStringBuffer strKehaiViewerWndName = KEHAIVIEWER_EXENAME + strVer + strSpcExeMode;
	CStringBuffer strTradeHelperWndName = TRADEHELPER_EXENAME + strVer + strSpcExeMode;

	// �v���O�����̕����N���}�~
	// �����A�I�[�v���ł���ΈȑO�̃A�v���P�[�V�������N�����Ă���
	if (! bUpdateCheck) {
		CStringBuffer strMutex = StrFormat(MUTEX_INSTANCE _T("_%06d"), THIS_VER) + strUlCmdLine + strUlExeMode;
		HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
		if (hPrevMutex) {
			// �N���[�Y
			CloseHandle(hPrevMutex);
			// ���Ɏ��s����Ă��邩
			CWnd* pWnd;
			if (pWnd = CWnd::FindWindow(NULL, strMainExeWndName)) {
				pWnd->SendMessage(WM_OPENWND);
				SetAbsoluteForegroundWindow(pWnd->GetSafeHwnd());
			}
			return FALSE;
		}
		// �����N���m�F�p�~���[�e�b�N�X�쐬
		m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);
	}

	// �A�b�v�f�[�g�v���t���O
	CStringBuffer strUpdateTxtFPath = strDataDir + _T("\\") FNAME_UPDATETXT;
	BOOL bUpdateAutoTraderReq = FALSE;
	if (CFile::GetStatus(strUpdateTxtFPath, m_FileStatus)) {
		CStringBuffer strUpdateTxt;
		if (ReStrFile(strUpdateTxtFPath, strUpdateTxt))
			return FALSE;
		int nVer;
		if (_stscanf(strUpdateTxt, _T("%*d %d %*s"), &nVer) != 1) {
			AfxMessageBox(_T("�A�b�v�f�[�g�o�[�W�����擾�G���["), MB_ICONSTOP);
			return FALSE;
		}
		if (nVer > THIS_VER)
			bUpdateAutoTraderReq = TRUE;
	}

	CAutoTraderDlg dlg;
	dlg.m_OSVI = m_OSVI;
	dlg.m_nThisVer = THIS_VER;
	dlg.m_strDir = m_strDir;
	dlg.m_strDefaultDataDir = strDefaultDataDir;
	dlg.m_strDataDir = strDataDir;
	dlg.m_bUpdateCheck = bUpdateCheck;
	dlg.m_strMainExeWndName = strMainExeWndName;
	dlg.m_strChartViewerWndName = strChartViewerWndName;
	dlg.m_strKehaiViewerWndName = strKehaiViewerWndName;
	dlg.m_strTradeHelperWndName = strTradeHelperWndName;
	dlg.m_strUlCmdLine = strUlCmdLine;
	dlg.m_strUlExeMode = strUlExeMode;
	dlg.m_bUpdateAutoTraderReq = bUpdateAutoTraderReq;
	dlg.m_nExecMode = nExecMode;
	dlg.m_bMentenance0 = bMentenance0;
	dlg.m_bMentenance1 = bMentenance1;
	dlg.m_bMentenance2 = bMentenance2;
	dlg.m_DtSimStart = DtSimStart;
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

int CAutoTraderApp::ExitInstance() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	if (m_hExeCheckMutex)
		CloseHandle(m_hExeCheckMutex);
	
	return CWinApp::ExitInstance();
}

void CAutoTraderApp::WinHelp(DWORD dwData, UINT nCmd) 
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

int CAutoTraderApp::ReadProductCode(CStringBuffer& strProductCode)
{
	int nRv = 0;

	if (ReStrFile(m_strDir + _T("\\") FNAME_PRODUCTCODE, strProductCode))
		nRv = -1;
	else
		strProductCode.TrimRight();

	return nRv;
}

void CAutoTraderApp::DelWorkFile(int nMode, const CStringBuffer& strDataDir, BOOL bEqDataDir)
{
	CFileFind Ff;
	BOOL bFfFound;

	_TCHAR pszFromFPath[MAX_PATH + 1];

	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;
	fileop.wFunc = FO_DELETE;
	fileop.pFrom = pszFromFPath;
	fileop.pTo = NULL;
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI;

	int nVer;
	BOOL bPatch;
	CStringBuffer strFName;
	CStringBuffer strFPath;

	bFfFound = Ff.FindFile(strDataDir + _T("\\") MAIN_EXENAME _T("??????*"));
	while (bFfFound) {
		bFfFound = Ff.FindNextFile();
		strFName = Ff.GetFileName();
		nVer = _ttoi(strFName.Mid(MAIN_EXENAMELEN, 6));
		if (nVer) {
			bPatch = strFName.Mid(MAIN_EXENAMELEN + 6, 1).CompareNoCase(_T("a")) == 0;
			if (
				bEqDataDir  &&  (nVer < BASE_VER  ||  nVer <= THIS_VER  &&  (bPatch  ||  ! Ff.IsDirectory())  ||  nVer == 999999)
				||  ! bEqDataDir  &&  (nMode == 0  &&  (nVer < BASE_VER  ||  bPatch)  ||  nMode == 1  &&  (nVer <= THIS_VER  ||  nVer == 999999))
			) {
				strFPath = Ff.GetFilePath();
				_tcscpy(pszFromFPath, strFPath);
				pszFromFPath[strFPath.GetLength() + 1] = _T('\0');
				if (SHFileOperation(&fileop))
					break;
			}
		}
	}
	Ff.Close();
}
