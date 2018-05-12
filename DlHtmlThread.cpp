// DlHtmlThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "AutoTrader.h"
#include "DlHtmlThread.h"

#include "Common.h"
#include "AutoTraderDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlHtmlThread

IMPLEMENT_DYNCREATE(CDlHtmlThread, CWinThread)

CDlHtmlThread::CDlHtmlThread()
{
	m_pSession = NULL;
	m_dwFlags = INTERNET_FLAG_EXISTING_CONNECT;
	m_lpszHeaders =
	m_lpszOptional =
		NULL;
}

CDlHtmlThread::~CDlHtmlThread()
{
}

BOOL CDlHtmlThread::InitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。

	int nRv = -1;

	int i;
	BOOL bReload = FALSE;
	CInternetSession* pSession;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;
	DWORD dwErr;

	srand( (unsigned)time( NULL ) );
	sbHtml = IToA(rand());

	if (m_pSession)
		pSession = m_pSession;
	else {
		pSession = new CInternetSession;

		pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
		pSession->SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);
	}

	for (i = 0; i < 80; i ++) {
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

		if (bReload)
			m_dwFlags |= INTERNET_FLAG_RELOAD;

		try
		{
			pServer = pSession->GetHttpConnection(m_strServerName, m_nPort);

			pFile = pServer->OpenRequest(m_nVerb, m_strObject, NULL, 1, NULL, NULL, m_dwFlags | INTERNET_FLAG_DONT_CACHE);

			pFile->SendRequest(m_lpszHeaders, m_lpszHeaders ? strlen(m_lpszHeaders) : 0, (LPVOID)m_lpszOptional, m_lpszOptional ? strlen(m_lpszOptional) : 0);

			if (pFile->QueryInfoStatusCode(dwStatusCode) == 0) {
				DispErrorLog("QueryInfoStatusCode Error: %s\n", GetLastErrorMessage());
				break;
			}

			if (dwStatusCode != HTTP_STATUS_OK) {
				DispErrorLog("HttpStatus Error: %s\n", GetHttpStatusText(dwStatusCode));

				switch (dwStatusCode) {
				case HTTP_STATUS_FORBIDDEN:
				case HTTP_STATUS_SERVER_ERROR:
				case HTTP_STATUS_BAD_GATEWAY:
					Sleep(250);
					bReload = TRUE;
					continue;
				}

				break;
			}

			m_sbHtml.Empty();
			while (nRdLen = pFile->Read(sz, DL_BUFLEN)) {
				sz[nRdLen] = '\0';
				m_sbHtml += sz;
			}

			if (StrReverseFindEx(m_sbHtml, "</html>", true) == -1) {
				DispErrorLog("Http Read Error\n");

				if (m_sbHtml == sbHtml)
					break;
				sbHtml = m_sbHtml;
				Sleep(250);
				bReload = TRUE;
				continue;
			}

			nRv = 0;
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
				Sleep(250);
				bReload = TRUE;
				continue;
			}
		}
		catch (CException* pEx) {
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}

	if (pFile) {
		pFile->Close();
		delete pFile;
	}
	if (pServer) {
		pServer->Close();
		delete pServer;
	}
	if (m_pSession == NULL) {
		pSession->Close();
		delete pSession;
	}

	PostQuitMessage(nRv);

	return TRUE;
}

int CDlHtmlThread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDlHtmlThread, CWinThread)
	//{{AFX_MSG_MAP(CDlHtmlThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlHtmlThread メッセージ ハンドラ

void CDlHtmlThread::DispErrorLog(LPCTSTR lpszFormat, ...)
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
	sb += StrFormat("m_sbHtml =\n%s", m_sbHtml);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}
