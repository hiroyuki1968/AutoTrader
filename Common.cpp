#include "stdafx.h"
#include "Common.h"

#include <AFXPRIV.H>
#include <tlhelp32.h>
#include <afxinet.h>
#include <shfolder.h>

_TCHAR pszEmpty[] = _T("");

CString StrQ(LPCTSTR lpsz, const _TCHAR chQ)
{
	return (CString)chQ + lpsz + chQ;
}

BOOL IsStrQTrim(const CString& str)
{
	_TCHAR chQ = str[0];
	return (chQ == _T('\'')  ||  chQ == _T('\"'))  &&  str[str.GetLength() - 1] == chQ;
}

CString StrQTrim(const CString& str)
{
	if (IsStrQTrim(str))
		return str.Mid(1, str.GetLength() - 2);

	return str;
}

CString GetDPathFromFPath(LPCTSTR lpszFPath)
{
	CString strFPath(lpszFPath);
	return strFPath.Left(strFPath.ReverseFind(_T('\\')));
}

CString GetFNameFromFPath(LPCTSTR lpszFPath)
{
	CString strFPath(lpszFPath);
	return strFPath.Mid(strFPath.ReverseFind(_T('\\')) + 1);
}

int ReStrFile(LPCTSTR lpszFPath, CString& str)
{
	int nRv = 0;

	try {
		CStdioFile StdioFile(lpszFPath, CFile::modeRead);
		CString strLine;
		str.Empty();
		while (StdioFile.ReadString(strLine)) {
			str += strLine;
			str += _T('\n');
		}
		StdioFile.Close();
	}
	catch (CException* pEx) {
		AfxMessageBox((CString)lpszFPath + _T(" ファイル読み込みエラー: ") + GetExceptionErrorMessage(pEx), MB_ICONSTOP);
		nRv = -1;
		pEx->Delete();
	}

	return nRv;
}

int WrStrFile(LPCTSTR lpszFPath, const CString& str)
{
	int nRv = 0;

	CFileStatus FileStatus;
	for (int i = 0; i < 20000 / 250  &&  CFile::GetStatus(lpszFPath, FileStatus); i ++) {
		if (DeleteFile(lpszFPath))
			break;
		Sleep(250);
	}

	try {
		CStdioFile StdioFile(lpszFPath, CFile::modeCreate | CFile::modeWrite);
		StdioFile.WriteString(str);
		StdioFile.Close();
	}
	catch (CException* pEx) {
		AfxMessageBox((CString)lpszFPath + _T(" ファイル書き出しエラー: ") + GetExceptionErrorMessage(pEx), MB_ICONSTOP);
		nRv = -1;
		pEx->Delete();
	}

	return nRv;
}

int WaitExeFPath(LPCTSTR lpszExeFPath, const OSVERSIONINFO& osvi)
{
	int nRv = 0;

	HANDLE hSnapshot = NULL;
	do {
		if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == (HANDLE)-1) {
			AfxMessageBox(_T("プロセスのスナップショット作成エラー: ") + GetLastErrorMessage(), MB_ICONSTOP);
			nRv = -1;
			break;
		}

		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe)) {
			CString strExeFPath(lpszExeFPath);
			if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
				strExeFPath = GetFNameFromFPath(strExeFPath);

			DWORD dwCurProcessID = GetCurrentProcessId();
			HANDLE hProcess;
			do {
				if (pe.th32ProcessID != dwCurProcessID  &&  strExeFPath.CompareNoCase(pe.szExeFile) == 0) {
					if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID)) == NULL) {
						DWORD dwLastError = GetLastError();
						if (dwLastError != ERROR_INVALID_PARAMETER) {
							AfxMessageBox(strExeFPath + _T(" プロセスハンドルオープンエラー: ") + GetLastErrorMessage(dwLastError), MB_ICONSTOP);
							nRv = -1;
						}
						break;
					}
					if (WaitForSingleObject(hProcess, INFINITE) != WAIT_OBJECT_0) {
						AfxMessageBox(strExeFPath + _T(" プロセス終了待機エラー: ") + GetLastErrorMessage(), MB_ICONSTOP);
						nRv = -1;
					}
					if (! CloseHandle(hProcess)  &&  nRv == 0) {
						AfxMessageBox(strExeFPath + _T(" プロセスハンドルクローズエラー: ") + GetLastErrorMessage(), MB_ICONSTOP);
						nRv = -1;
					}
					break;
				}
			} while (Process32Next(hSnapshot, &pe));
		}
	} while (0);
	if (hSnapshot)
		if (! CloseHandle(hSnapshot)) {
			AfxMessageBox(_T("プロセスのスナップショットハンドルクローズエラー: ") + GetLastErrorMessage(), MB_ICONSTOP);
			nRv = -1;
		}

	return nRv;
}

CString GetLastErrorMessage(DWORD dwLastError)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwLastError ? dwLastError : GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	CString strMsg((LPCTSTR)lpMsgBuf);
	// Free the buffer.
	LocalFree( lpMsgBuf );

	return strMsg;
}

CString GetExceptionErrorMessage(CException* pEx)
{
	TCHAR   szCause[255];

	pEx->GetErrorMessage(szCause, 255);
	return szCause;
}

int nPumpWaitingMessages = 0;

void PumpWaitingMessages()
{
	nPumpWaitingMessages ++;

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (msg.message == WM_QUIT)
			break;
		::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		::TranslateMessage(&msg);
		::DispatchMessage (&msg);
	}

	nPumpWaitingMessages --;
}

#ifndef SPI_GETFOREGROUNDLOCKTIMEOUT
#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#endif
#ifndef SPI_SETFOREGROUNDLOCKTIMEOUT
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
#endif

void SetAbsoluteForegroundWindow(HWND hWnd)
{
	SetForegroundWindow(hWnd);

	int nTargetID, nForegroundID;
	DWORD sp_time;

	// フォアグラウンドウィンドウを作成したスレッドのIDを取得
	nForegroundID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	// 目的のウィンドウを作成したスレッドのIDを取得
	nTargetID = GetWindowThreadProcessId(hWnd, NULL );

	// スレッドのインプット状態を結び付ける
	AttachThreadInput(nTargetID, nForegroundID, TRUE );  // TRUE で結び付け

	// 現在の設定を sp_time に保存
	SystemParametersInfo( SPI_GETFOREGROUNDLOCKTIMEOUT,0,&sp_time,0);
	// ウィンドウの切り替え時間を 0ms にする
	SystemParametersInfo( SPI_SETFOREGROUNDLOCKTIMEOUT,0,(LPVOID)0,0);

	// ウィンドウをフォアグラウンドに持ってくる
	SetForegroundWindow(hWnd);

	// 設定を元に戻す
	SystemParametersInfo( SPI_SETFOREGROUNDLOCKTIMEOUT,0,(LPVOID)sp_time,0);

	// スレッドのインプット状態を切り離す
	AttachThreadInput(nTargetID, nForegroundID, FALSE );  // FALSE で切り離し
}

#if !defined(COMMON_H__NOSHFOLDER)

CString GetShFolderPath(int nFolder)
{
	CString strRv;

	TCHAR szFolderPath[MAX_PATH];
	if(SUCCEEDED(SHGetFolderPath(NULL, nFolder, NULL, 0, szFolderPath)))
		strRv = szFolderPath;

	return strRv;
}


CString IToA(int n)
{
	_TCHAR psz[12];
	_itoa(n, psz, 10);

	return psz;
}

CString LToA(long l)
{
	_TCHAR psz[12];
	_ltoa(l, psz, 10);

	return psz;
}

int StrFindNoCase(const CString& str, LPCTSTR lpszTarget, int nIndex)
{
	int nRv;
	CString strUTarget(lpszTarget);
	CString strLTarget(lpszTarget);
	strUTarget.MakeUpper();
	strLTarget.MakeLower();
	int nUIndex = str.Find(strUTarget, nIndex);
	int nLIndex = str.Find(strLTarget, nIndex);
	if (nUIndex != -1  &&  nLIndex != -1)
		nRv = nUIndex < nLIndex ? nUIndex : nLIndex;
	else
		nRv = nUIndex < nLIndex ? nLIndex : nUIndex;

	return nRv;
}

int StrFindOneOf(LPCTSTR lpszStr, LPCTSTR lpszCharSet, int nStart)
{
	_TCHAR* pch;
	if ((pch = _tcspbrk(lpszStr + nStart, lpszCharSet)) == NULL)
		return -1;

	return pch - lpszStr;
}

int StrFindNotOf(const CString& str, LPCTSTR lpszCharSet, int nStart)
{
	int nStrPtr = nStart + _tcsspn((LPCTSTR)str + nStart, lpszCharSet);
	if (nStrPtr >= str.GetLength())
		return -1;

	return nStrPtr;
}

int StrReverseFindEx(const CString& str, LPCTSTR lpszTarget, bool bNoCase) {
	return StrReverseFindEx(str, lpszTarget, str.GetLength() - _tcslen(lpszTarget), bNoCase);
}

int StrReverseFindEx(const CString& str, LPCTSTR lpszTarget, int nIndex, bool bNoCase) {
	int i;
	int j;
	CString strTarget(lpszTarget);
	int nTargetLen = strTarget.GetLength();
	BOOL bNotFound;
	BOOL bFound = FALSE;

	if (bNoCase)
		strTarget.MakeUpper();

	if (nIndex < 0)
		return -1;
	if (nIndex > str.GetLength() - nTargetLen)
		nIndex = str.GetLength() - nTargetLen;

	for (i = nIndex; i >= 0; i --) {
		bNotFound = FALSE;
		for (j = 0; j < nTargetLen; j ++)
			if (((bNoCase ? toupper(str[i + j]) : str[i + j])) != strTarget[j]) {
				bNotFound = TRUE;
				break;
			}
		if (! bNotFound) {
			bFound = TRUE;
			break;
		}
	}
	if (! bFound)
		return -1;

	return i;
}

CString StrFormat(LPCTSTR lpszFormat, ...)
{
	CString str;

	va_list vl;
	va_start(vl, lpszFormat);
	str.FormatV(lpszFormat, vl);
	va_end(vl);

	return str;
}

CString StrConvHalfWidth(LPCTSTR lpszStr)
{
	CString strRv;

	int nStrLen = _tcslen(lpszStr);
	int nBufLen = nStrLen + 1;
	_TCHAR* lpszBuf = new _TCHAR[nBufLen];
	if (LCMapString(MAKELCID(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT), SORT_JAPANESE_XJIS), LCMAP_HALFWIDTH, lpszStr, nStrLen + 1, lpszBuf, nBufLen))
		strRv = lpszBuf;
	delete lpszBuf;

	return strRv;
}

COleDateTime FixDateTime(const COleDateTime& dt)
{
	return(COleDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond()));
}

int ForceDir(const CString& strDir)
{
	CString strCurDir;
	CFileStatus FileStatus;

	int nIndex = -1;
	do {
		nIndex = strDir.Find(_T('\\'), nIndex + 1);
		if (nIndex == -1)
			strCurDir = strDir;
		else
			strCurDir = strDir.Left(nIndex);
		if (strCurDir.Right(1) != _T(":")) {
			if (! CFile::GetStatus(strCurDir, FileStatus))
				if (! CreateDirectory(strCurDir, NULL))
					return -1;
		}
	} while (nIndex != -1);

	return 0;
}

void ParseUrlSearch(LPCTSTR lpszUrl, CMapStringToString& MstsSearch)
{
	CString strUrl(lpszUrl);
	int nUrlLen = strUrl.GetLength();
	int nIndex0 = strUrl.ReverseFind(_T('?'));
	int nIndex1;
	int nIndex2;
	int nIndex3;
	int nIndex4;
	int nIndex5;

	MstsSearch.RemoveAll();

	while (nIndex0 != -1) {
		nIndex0 ++;
		nIndex1 = nIndex2 = strUrl.Find(_T('&'), nIndex0);
		if (nIndex2 == -1)
			nIndex2 = nUrlLen;
		nIndex3 = nIndex4 = strUrl.Find(_T('='), nIndex0);
		if (nIndex4 == -1)
			nIndex4 = nIndex5 = nIndex2;
		else
			nIndex5 = nIndex4 + 1;
		MstsSearch[strUrl.Mid(nIndex0, nIndex4 - nIndex0)] = strUrl.Mid(nIndex5, nIndex2 - nIndex5);
		nIndex0 = nIndex1;
	}
}

CString GetLongPath(LPCTSTR lpszPath)
{
	USES_CONVERSION;

	CString strRv = lpszPath;

	IMalloc      *pMalloc;

	if ( NOERROR == SHGetMalloc( &pMalloc ) )
	{
		IShellFolder *pshf;

		if ( NOERROR == SHGetDesktopFolder( &pshf ) )
		{
			WCHAR        *wcShortPath;
			ULONG         chEaten;
			ITEMIDLIST   *pidl;

			wcShortPath = T2W(lpszPath);
			if ( NOERROR == pshf->ParseDisplayName( NULL, NULL, wcShortPath, &chEaten, &pidl, NULL ) ) // pidl を取得
			{
				char LongPath[MAX_PATH];

				if ( SHGetPathFromIDList( pidl, LongPath ) ) // パス名を pidl より取得
					strRv = A2CT(LongPath); // 成功
				pMalloc->Free( pidl );
			}
			pshf->Release();
		}
		pMalloc->Release();
	}

	return strRv;
}

CString GetShellExecuteErrorText(HINSTANCE hInstance)
{
	CString strText;

	switch ((int)hInstance) {
	case 0:
		strText = _T("メモリまたはリソースが不足しています。");
		break;
/*
	case ERROR_FILE_NOT_FOUND:
		strText = _T("指定されたファイルが見つかりませんでした。");
		break;
	case ERROR_PATH_NOT_FOUND:
		strText = _T("指定されたパスが見つかりませんでした。");
		break;
*/
	case ERROR_BAD_FORMAT:
		strText = _T(".exe ファイルが無効です。Win32 の .exe ではないか、.exe イメージ内にエラーがあります。");
		break;
	case SE_ERR_ACCESSDENIED:
		strText = _T("オペレーティングシステムが、指定されたファイルへのアクセスを拒否しました。");
		break;
	case SE_ERR_ASSOCINCOMPLETE:
		strText = _T("ファイル名の関連付けが不完全または無効です。");
		break;
	case SE_ERR_DDEBUSY:
		strText = _T("ほかの DDE トランザクションが現在処理中なので、DDE トランザクションを完了できませんでした。");
		break;
	case SE_ERR_DDEFAIL:
		strText = _T("DDE トランザクションが失敗しました。");
		break;
	case SE_ERR_DDETIMEOUT:
		strText = _T("要求がタイムアウトしたので、DDE トランザクションを完了できませんでした。");
		break;
	case SE_ERR_DLLNOTFOUND:
		strText = _T("指定されたダイナミックリンクライブラリ（DLL）が見つかりませんでした。");
		break;
	case SE_ERR_FNF:
		strText = _T("指定されたファイルが見つかりませんでした。");
		break;
	case SE_ERR_NOASSOC:
		strText = _T("指定されたファイル拡張子に関連付けられたアプリケーションがありません。印刷可能ではないファイルを印刷しようとした場合も、このエラーが返ります。");
		break;
	case SE_ERR_OOM:
		strText = _T("操作を完了するのに十分なメモリがありません。");
		break;
	case SE_ERR_PNF:
		strText = _T("指定されたパスが、見つかりませんでした。");
		break;
	case SE_ERR_SHARE:
		strText = _T("共有違反が発生しました。");
	}

	return strText;
}

CString GetHttpStatusText(DWORD dwStatusCode)
{
	CString strText;

	switch (dwStatusCode) {
	case HTTP_STATUS_CONTINUE:
		strText = _T("OK to continue with request");
		break;
	case HTTP_STATUS_SWITCH_PROTOCOLS:
		strText = _T("server has switched protocols in upgrade header");
		break;

	case HTTP_STATUS_CREATED:
		strText = _T("object created, reason = new URI");
		break;
	case HTTP_STATUS_ACCEPTED:
		strText = _T("async completion (TBS)");
		break;
	case HTTP_STATUS_PARTIAL:
		strText = _T("partial completion");
		break;
	case HTTP_STATUS_NO_CONTENT:
		strText = _T("no info to return");
		break;
	case HTTP_STATUS_RESET_CONTENT:
		strText = _T("request completed, but clear form");
		break;
	case HTTP_STATUS_PARTIAL_CONTENT:
		strText = _T("partial GET furfilled");
		break;

	case HTTP_STATUS_AMBIGUOUS:
		strText = _T("server couldn't decide what to return");
		break;
	case HTTP_STATUS_MOVED:
		strText = _T("object permanently moved");
		break;
	case HTTP_STATUS_REDIRECT:
		strText = _T("object temporarily moved");
		break;
	case HTTP_STATUS_REDIRECT_METHOD:
		strText = _T("redirection w/ new access method");
		break;
	case HTTP_STATUS_NOT_MODIFIED:
		strText = _T("if-modified-since was not modified");
		break;
	case HTTP_STATUS_USE_PROXY:
		strText = _T("redirection to proxy, location header specifies proxy to use");
		break;
	case HTTP_STATUS_REDIRECT_KEEP_VERB:
		strText = _T("HTTP/1.1: keep same verb");
		break;

	case HTTP_STATUS_BAD_REQUEST:
		strText = _T("不適切な要求です");
		break;
	case HTTP_STATUS_DENIED:
		strText = _T("access denied");
		break;
	case HTTP_STATUS_PAYMENT_REQ:
		strText = _T("payment required");
		break;
	case HTTP_STATUS_FORBIDDEN:
		strText = _T("request forbidden");
		break;
	case HTTP_STATUS_NOT_FOUND:
		strText = _T("要求された URL が見つかりません");
		break;
	case HTTP_STATUS_BAD_METHOD:
		strText = _T("サーバーは要求された方式をサポートしていません");
		break;
	case HTTP_STATUS_NONE_ACCEPTABLE:
		strText = _T("no response acceptable to client found");
		break;
	case HTTP_STATUS_PROXY_AUTH_REQ:
		strText = _T("proxy authentication required");
		break;
	case HTTP_STATUS_REQUEST_TIMEOUT:
		strText = _T("server timed out waiting for request");
		break;
	case HTTP_STATUS_CONFLICT:
		strText = _T("user should resubmit with more info");
		break;
	case HTTP_STATUS_GONE:
		strText = _T("the resource is no longer available");
		break;
	case HTTP_STATUS_LENGTH_REQUIRED:
		strText = _T("the server refused to accept request w/o a length");
		break;
	case HTTP_STATUS_PRECOND_FAILED:
		strText = _T("precondition given in request failed");
		break;
	case HTTP_STATUS_REQUEST_TOO_LARGE:
		strText = _T("request entity was too large");
		break;
	case HTTP_STATUS_URI_TOO_LONG:
		strText = _T("request URI too long");
		break;
	case HTTP_STATUS_UNSUPPORTED_MEDIA:
		strText = _T("unsupported media type");
		break;

	case HTTP_STATUS_SERVER_ERROR:
		strText = _T("原因不明のサーバー エラー");
		break;
	case HTTP_STATUS_NOT_SUPPORTED:
		strText = _T("required not supported");
		break;
	case HTTP_STATUS_BAD_GATEWAY:
		strText = _T("error response received from gateway");
		break;
	case HTTP_STATUS_SERVICE_UNAVAIL:
		strText = _T("サーバー容量の限界です");
		break;
	case HTTP_STATUS_GATEWAY_TIMEOUT:
		strText = _T("timed out waiting for gateway");
		break;
	case HTTP_STATUS_VERSION_NOT_SUP:
		strText = _T("HTTP version not supported");
	}

	return strText;
}

DWORD GetAllocationSize(DWORD dwSize)
{
	DWORD dwRv;

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD dwAllocationGranularity = SystemInfo.dwAllocationGranularity;

	dwRv = dwSize / dwAllocationGranularity * dwAllocationGranularity;
	if (dwSize % dwAllocationGranularity)
		dwRv += dwAllocationGranularity;

	return dwRv;
}

__int64 GetDiskFreeSpaceInt64(LPCTSTR pszDrive)
{
	__int64 nRv = 0i64;

	CString strDrive = pszDrive;
	if (strDrive.Right(2) == _T(":\\"))
		strDrive.Delete(strDrive.GetLength() - 1);
	else {
		_TCHAR ch = strDrive.Right(1)[0];
		if (ch != _T(':')  &&  ch != _T('\\'))
			strDrive += _T('\\');
	}

	FARPROC pGetDiskFreeSpaceEx;
	BOOL fResult;

	pGetDiskFreeSpaceEx = GetProcAddress(GetModuleHandle("kernel32.dll"),
		"GetDiskFreeSpaceExA");
	if (pGetDiskFreeSpaceEx)
	{
		ULARGE_INTEGER i64FreeBytesToCaller;
		ULARGE_INTEGER i64TotalBytes;
		ULARGE_INTEGER i64FreeBytes;

		fResult = ((int (CALLBACK *)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER))pGetDiskFreeSpaceEx) (strDrive,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		// GetDiskFreeSpaceEx の結果を処理する。
		nRv = fResult ? i64FreeBytes.QuadPart : -1i64;
	}
	else
	{
		DWORD dwSectPerClust;
		DWORD dwBytesPerSect;
		DWORD dwFreeClusters;
		DWORD dwTotalClusters;

		fResult = GetDiskFreeSpace (strDrive,
			&dwSectPerClust,
			&dwBytesPerSect,
			&dwFreeClusters,
			&dwTotalClusters);
		// GetDiskFreeSpace の結果を処理する。
		nRv = fResult ? (__int64)dwFreeClusters * dwSectPerClust * dwBytesPerSect : -1i64;
	}

	return nRv;
}

int CALLBACK
BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData) {
	TCHAR szDir[MAX_PATH];

	switch(uMsg) {
	case BFFM_INITIALIZED: {
		if (GetCurrentDirectory(sizeof(szDir)/sizeof(TCHAR), szDir)) {
			// WParam is TRUE since you are passing a path.
			// It would be FALSE if you were passing a pidl.
			SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
		}
		break;
	}
	case BFFM_SELCHANGED: {
		// Set the status window to the currently selected path.
		if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir)) {
			SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

CString FolderDialog(HWND hWnd)
{
	BROWSEINFO bi;
	TCHAR szDir[MAX_PATH];
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;

	szDir[0] = '\0';
	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		ZeroMemory(&bi,sizeof(bi));
		bi.hwndOwner = hWnd;
		bi.pszDisplayName = 0;
		bi.pidlRoot = 0;
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
		bi.lpfn = BrowseCallbackProc;

		pidl = SHBrowseForFolder(&bi);
		if (pidl) {
			if (! SHGetPathFromIDList(pidl,szDir)) {
				szDir[0] = '\0';
			}

			// In C++: pMalloc->Free(pidl); pMalloc->Release();
			pMalloc->Free(pidl); pMalloc->Release();
//			pMalloc->lpVtbl->Free(pMalloc,pidl);
//			pMalloc->lpVtbl->Release(pMalloc);
		}
	}

	return szDir;
}

/////////////////////////////////////////////////////////////////////////////
// CStringTokenizer

CStringTokenizer::CStringTokenizer()
{
}

CStringTokenizer::CStringTokenizer(const CString& str, LPCTSTR lpszSep)
{
	SetStrSep(str, lpszSep);
}

void CStringTokenizer::SetStrSep(const CString& str, LPCTSTR lpszSep)
{
	m_strStr = str;
	m_nStrLen = m_strStr.GetLength();
	m_strSep = lpszSep;
	m_nStrPtr = 0;
}

BOOL CStringTokenizer::StrTok(LPCTSTR lpszSep)
{
	if (lpszSep)
		m_strSep = lpszSep;

	if (m_nStrPtr >= m_nStrLen)
		return FALSE;

	int nTmpPtr;
	int nStrLen = 0;

	do {
		if ((nTmpPtr = StrFindOneOf(m_strStr, m_strSep, m_nStrPtr)) == -1) {
			nStrLen = m_nStrLen - m_nStrPtr;
			break;
		}
		if (nTmpPtr != m_nStrPtr) {
			nStrLen = nTmpPtr - m_nStrPtr;
			break;
		}
		m_nStrPtr = nTmpPtr + 1;
	} while (m_nStrPtr < m_nStrLen);

	nTmpPtr = m_nStrPtr;

	m_nStrPtr += nStrLen + 1;

	m_strTok = m_strStr.Mid(nTmpPtr, nStrLen);

	return TRUE;
}

#endif // !defined(COMMON_H__NOSHFOLDER)
