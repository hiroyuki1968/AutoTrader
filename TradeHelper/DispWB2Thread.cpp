// DispWB2Thread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "DispWB2Thread.h"

#include "../Common.h"
#include "../AutoTraderDef.h"
#include "TradeHelperDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDispWB2Thread

IMPLEMENT_DYNCREATE(CDispWB2Thread, CWinThread)

CDispWB2Thread::CDispWB2Thread()
{
}

CDispWB2Thread::~CDispWB2Thread()
{
}

BOOL CDispWB2Thread::InitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。

	CInternetSession Session(_T("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/4.0; GTB6.6; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.1; .NET4.0C)"));

	Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
	Session.SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

	m_pServer = NULL;

	try {
		if (m_strFPath.GetLength() && (m_nMode != 2  ||  m_strPreUrl != m_strUrl)) {
			if (! AfxParseURL(m_strUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
				DispErrorLog("URL 解析エラー: %s\n", m_strUrl);
				goto CleanUp;
			}

			m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

			if (DlFile(m_strFPath, CHttpConnection::HTTP_VERB_GET))
				goto CleanUp;

			m_nMode = 1;
			m_strUrl = m_strFPath;
		}
	}
	catch (CFileException* pEx) {
		if (pEx->m_cause != CFileException::sharingViolation)
			DispErrorLog("チャート表示エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
	}
	catch (CException* pEx) {
		DispErrorLog("チャート表示エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
	}

CleanUp:
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
	}
	Session.Close();

	::PostQuitMessage(0);

	return TRUE;
}

int CDispWB2Thread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDispWB2Thread, CWinThread)
	//{{AFX_MSG_MAP(CDispWB2Thread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispWB2Thread メッセージ ハンドラ

int CDispWB2Thread::DlFile(const CString& strFPath, int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	DWORD dwErr;
	int nErrCount = 0;
	CFile* pF = NULL;
	_TCHAR pszTempDPath[MAX_PATH];
	_TCHAR pszTempFPath[MAX_PATH];

	m_pFile = NULL;

	while (1) {
		if (pF) {
			pF->Close();
			delete pF;
			pF = NULL;
		}
		if (m_pFile) {
			m_pFile->Close();
			delete m_pFile;
			m_pFile = NULL;
		}

		if (bReload)
			dwFlags |= INTERNET_FLAG_RELOAD;

		try
		{
			m_pFile = m_pServer->OpenRequest(nVerb, m_strObject, NULL, 1, NULL, NULL, dwFlags | INTERNET_FLAG_DONT_CACHE);

			m_pFile->SendRequest(lpszHeaders, lpszHeaders ? strlen(lpszHeaders) : 0, (LPVOID)lpszOptional, lpszOptional ? strlen(lpszOptional) : 0);

			if (m_pFile->QueryInfoStatusCode(dwStatusCode) == 0) {
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
			while (nRdLen = m_pFile->Read(sz, DL_BUFLEN)) {
				if (pF == NULL)
					if (nRdLen < DL_BUFLEN)
						pF = new CFile(strFPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
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

			if (pF) {
				pF->Close();
				delete pF;
				pF = NULL;
			}

			if (*pszTempFPath != _T('\0')) {
				CFileStatus FileStatus;
				if (CFile::GetStatus(strFPath, FileStatus))
					if (! DeleteFile(strFPath)) {
						DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
				if (! MoveFile(pszTempFPath, strFPath)) {
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
	if (m_pFile) {
		m_pFile->Close();
		delete m_pFile;
	}

	return nRv;
}

void CDispWB2Thread::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	CString strFPath;
	strFPath.Format("%s\\Log\\TradHelperThreadErrorLog%s%d.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	StdioFile.SeekToEnd();
	sb += StrFormat("m_strServerName = %s\n", m_strServerName);
	sb += StrFormat("m_strObject = %s\n", m_strObject);
	sb += StrFormat("m_strObjectC = %s\n", m_strObjectC);
	sb += StrFormat("m_sbOptional = %s\n", m_sbOptional);
	sb += StrFormat("m_nPort = %i\n", m_nPort);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}
