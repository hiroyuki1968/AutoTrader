// DlFileThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "autotrader.h"
#include "DlFileThread.h"

#include "Common.h"
#include "AutoTraderDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlFileThread

IMPLEMENT_DYNCREATE(CDlFileThread, CWinThread)

CDlFileThread::CDlFileThread()
{
	m_dwFlags = INTERNET_FLAG_EXISTING_CONNECT;
	m_lpszHeaders =
	m_lpszOptional =
		NULL;
}

CDlFileThread::~CDlFileThread()
{
}

BOOL CDlFileThread::InitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。

	int nRv = -1;

	BOOL bReload = FALSE;
	CInternetSession Session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;
	DWORD dwErr;
	int nErrCount = 0;
	CFile* pF = NULL;
	_TCHAR pszTempDPath[MAX_PATH];
	_TCHAR pszTempFPath[MAX_PATH];

	Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

	while (1) {
		if (pFile) {
			pFile->Close();
			delete pFile;
			pFile = NULL;
		}
		if (pServer) {
			pServer->Close();
			delete pServer;
			pServer = NULL;
		}
		if (pF) {
			pF->Close();
			delete pF;
			pF = NULL;
		}

		if (bReload)
			m_dwFlags |= INTERNET_FLAG_RELOAD;

		try
		{
			pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

			pFile = pServer->OpenRequest(m_nVerb, m_strObject, NULL, 1, NULL, NULL, m_dwFlags | INTERNET_FLAG_DONT_CACHE);

			pFile->SendRequest(m_lpszHeaders, m_lpszHeaders ? strlen(m_lpszHeaders) : 0, (LPVOID)m_lpszOptional, m_lpszOptional ? strlen(m_lpszOptional) : 0);

			if (pFile->QueryInfoStatusCode(dwStatusCode) == 0) {
				DispErrorLog("QueryInfoStatusCode Error: %s\n", GetLastErrorMessage());
				goto CleanUp;
			}

			if (dwStatusCode != HTTP_STATUS_OK) {
				DispErrorLog("HttpStatus Error: %s\n", GetHttpStatusText(dwStatusCode));

				switch (dwStatusCode) {
				case HTTP_STATUS_FORBIDDEN:
				case HTTP_STATUS_SERVER_ERROR:
				case HTTP_STATUS_BAD_GATEWAY:
					if (nErrCount ++ < 80) {
						Sleep(250);
						bReload = TRUE;
						continue;
					}
				}

				goto CleanUp;
			}

			*pszTempFPath = _T('\0');
			while (nRdLen = pFile->Read(sz, DL_BUFLEN)) {
				if (pF == NULL)
					if (nRdLen < DL_BUFLEN)
						pF = new CFile(m_strFPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
					else {
						if (GetTempPath(MAX_PATH, pszTempDPath) == 0) {
							DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
							goto CleanUp;
						}
						if (GetTempFileName(pszTempDPath, _T("atb"), 0, pszTempFPath) == 0) {
							DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
							goto CleanUp;
						}
						pF = new CFile(pszTempFPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
					}
				pF->Write(sz, nRdLen);
			}

			pF->Close();
			delete pF;
			pF = NULL;

			if (*pszTempFPath != _T('\0')) {
				CFileStatus FileStatus;
				if (CFile::GetStatus(m_strFPath, FileStatus))
					if (! DeleteFile(m_strFPath)) {
						DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
				if (! MoveFile(pszTempFPath, m_strFPath)) {
					DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
					goto CleanUp;
				}
			}
		}
		catch (CInternetException* pEx) {
			dwErr = pEx->m_dwError;
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();

			if (
				dwErr == ERROR_INTERNET_TIMEOUT
				||  dwErr == ERROR_INTERNET_NAME_NOT_RESOLVED
				||  dwErr == ERROR_INTERNET_CANNOT_CONNECT
//				||  dwErr == ERROR_INTERNET_CONNECTION_RESET
				||  dwErr == ERROR_HTTP_INVALID_SERVER_RESPONSE
			) {
				if (nErrCount ++ < 80) {
					Sleep(250);
					bReload = TRUE;
					continue;
				}
			}

			goto CleanUp;
		}
		catch (CException* pEx) {
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
			goto CleanUp;
		}

		break;
	}

	nRv = 0;

CleanUp:
	if (pF) {
		pF->Close();
		delete pF;
	}
	if (pFile) {
		pFile->Close();
		delete pFile;
	}
	if (pServer) {
		pServer->Close();
		delete pServer;
	}
	Session.Close();
	if (pF) {
		pF->Close();
		delete pF;
		pF = NULL;
	}

	PostQuitMessage(nRv);

	return TRUE;
}

int CDlFileThread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDlFileThread, CWinThread)
	//{{AFX_MSG_MAP(CDlFileThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlFileThread メッセージ ハンドラ

void CDlFileThread::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	CString strFPath;
	strFPath.Format("%s\\Log\\AutoTraderThreadErrorLog%s%d.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	StdioFile.SeekToEnd();
	sb += StrFormat("m_strServerName = %s\n", m_strServerName);
	sb += StrFormat("m_strObject = %s\n", m_strObject);
	sb += StrFormat("m_nPort = %i\n", m_nPort);
	sb += StrFormat("m_strFPath =\n%s", m_strFPath);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}
