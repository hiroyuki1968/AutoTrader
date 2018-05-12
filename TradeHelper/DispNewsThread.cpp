// DispNewsThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "DispNewsThread.h"

#include "../Common.h"
#include "../Html.h"
#include "../AutoTraderDef.h"
#include "TradeHelperDef.h"
#include "../AutoTraderProc.h"
#include "TradeHelperProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDispNewsThread

IMPLEMENT_DYNCREATE(CDispNewsThread, CWinThread)

CDispNewsThread::CDispNewsThread()
{
}

CDispNewsThread::~CDispNewsThread()
{
}

BOOL CDispNewsThread::InitInstance()
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
		int i;
		int j;
		int k;
		int nPtr0;
		CHtmlTokenizer HtmlTokenizer;
		CStringBuffer sbValue;
		CString strTime;
		CString strCode;
		CString strName;
		CString strNo;
		CString strUrl;
		CString strTitle;
		CMapStringToString MstsSearch;
		BOOL bBreak = FALSE;
		COleDateTime DtCurDate;
		COleDateTime DtDate;
		COleDateTime DtNextDate;
		CString strDate;
		COleDateTimeSpan Dts1Day(1, 0, 0, 0);
		CString strYear;
		CString strMonth;
		CString strDay;
		CString strYYList;
		CString strMMList;
		BOOL bDlFirst = FALSE;
		int nDayOfWeek;
		int nRowspan;
		int nHidSelectFromDate = 0;

		strUrl = m_nMode == 0 ? URL_NEWS : URL_KESSAN;
		if (! AfxParseURL(strUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
			DispErrorLog("URL 解析エラー: %s\n", strUrl);
			goto CleanUp;
		}

		m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

		if (m_nMode == 0) {
			for (i = 1; ; i ++) {
				if (! bDlFirst) {
					if (DlHtml(CHttpConnection::HTTP_VERB_GET))
						break;
					if ((nPtr0 = m_sbHtml.Find("検索期間")) == -1)
						goto CleanUp;
					if ((nPtr0 = m_sbHtml.Find("<option ", nPtr0 + 1)) == -1)
						goto CleanUp;
					HtmlTokenizer.SetHtml(m_sbHtml);
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp;
					if (! DtCurDate.ParseDateTime(HtmlTokenizer.m_strTag))
						goto CleanUp;
					DtDate = DtCurDate;
					bDlFirst = TRUE;
				} else {
					strDate = DtDate.Format("%Y/%m/%d");
//					m_sbOptional.Format(OPT_NEWS, strDate, DtDate == DtCurDate ? pszEmpty : strDate, i);
					strUrl.Format(URL_NEWS "?" OPT_NEWS, strDate, DtDate == DtCurDate ? pszEmpty : strDate, nHidSelectFromDate ? IToA(nHidSelectFromDate) : pszEmpty, i == 1 ? pszEmpty : IToA(i));
					if (! AfxParseURL(strUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
						DispErrorLog("URL 解析エラー: %s\n", strUrl);
						goto CleanUp;
					}
//					if (DlHtml(CHttpConnection::HTTP_VERB_POST, NULL, HEA_POST, m_sbOptional))
					if (DlHtml(CHttpConnection::HTTP_VERB_GET))
						break;
				}

				if ((nPtr0 = m_sbHtml.Find("表題")) == -1) {
					if (DtDate <= m_DtPreDate)
						break;
					DtDate -= Dts1Day;
					nHidSelectFromDate ++;
					i = 0;
					continue;
				}
				HtmlTokenizer.SetHtml(m_sbHtml);
				nRowspan = 0;
				for (j = 0; j < 50; j ++) {
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<tr ", nPtr0 + 1)) == -1)
						break;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("class", sbValue) != 2)
						goto CleanUp;
					if (StrQTrim(sbValue) != "tr3")
						break;
					if (! nRowspan) {
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp;
						if (HtmlTokenizer.FindTagAttr("rowspan", sbValue) != 2)
							goto CleanUp;
						nRowspan = atoi(StrQTrim(sbValue));
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp;
						strTime = HtmlTokenizer.m_strTag;
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp;
						if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
							goto CleanUp;
						ParseUrlSearch(StrQTrim(sbValue), MstsSearch);
						if (! MstsSearch.Lookup("scode", strCode))
							goto CleanUp;
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					}
					for (k = 0; k < 2; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 3; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
						goto CleanUp;
					ParseUrlSearch(StrQTrim(sbValue), MstsSearch);
					if (! MstsSearch.Lookup("ano", strNo))
						goto CleanUp;
					if (! MstsSearch.Lookup("t", strUrl))
						goto CleanUp;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					strTitle = StrConvHalfWidth(HtmlTokenizer.m_strTag);
					strTitle.TrimRight();
					strTitle.TrimLeft();
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
//					if (nRowspan) {
//						nRowspan --;
//						if (nRowspan)
						if (-- nRowspan) {
							strNo += IToA(nRowspan);
							j --;
						}
//					}

					if (strNo == m_strCurNewsNo  ||  DtDate == m_DtPreDate  &&  strTime < "15:00") {
						bBreak = TRUE;
						break;
					}

					m_SaDateTime.Add(strTime);
					m_SaCode.Add(strCode);
					m_SaNewsNo.Add(strNo);
					m_SaNewsUrl.Add(strUrl);
					m_SaTitle.Add(strTitle);
				}
				if (bBreak)
					break;
				if ((nPtr0 = m_sbHtml.Find("次へ", nPtr0 + 1)) == -1) {
					if (DtDate <= m_DtPreDate)
						break;
					DtDate -= Dts1Day;
					nHidSelectFromDate ++;
					i = 0;
				} else {
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlReverseTok())
						goto CleanUp;
					if (HtmlTokenizer.GetTagCmd().CompareNoCase("a")) {
						if (DtDate <= m_DtPreDate)
							break;
						DtDate -= Dts1Day;
						nHidSelectFromDate ++;
						i = 0;
					}
				}
			}
		} else {
			for (i = 1; ; i ++) {
				if (! bDlFirst) {
					if (DlHtml(CHttpConnection::HTTP_VERB_GET))
						break;
				} else
					if (i == 1) {
						m_sbOptional.Format(OPT_KESSAN, "date", strMonth, strDay, pszEmpty, strYYList, strMMList, DtDate.GetMonth(), DtDate.GetDay());
						if (DlHtml(CHttpConnection::HTTP_VERB_POST, NULL, HEA_POST, m_sbOptional))
							break;
					} else {
						m_sbOptional.Format(OPT_KESSAN, pszEmpty, strMonth, strDay, IToA(i), strYYList, strMMList, DtDate.GetMonth(), DtDate.GetDay());
						if (DlHtml(CHttpConnection::HTTP_VERB_POST, NULL, HEA_POST, m_sbOptional))
							break;
					}

//				if (i == 1) {
				if (! bDlFirst) {
					if ((nPtr0 = m_sbHtml.Find("取引所集計日以降の変更はこちら")) == -1)
						goto CleanUp;
					for (k = 0; k < 4; k ++)
						if ((nPtr0 = m_sbHtml.Find("<input ", nPtr0 + 1)) == -1)
							goto CleanUp;
					HtmlTokenizer.SetHtml(m_sbHtml);
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("value", sbValue) != 2)
						goto CleanUp;
					strMonth = StrQTrim(sbValue);
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					if ((nPtr0 = m_sbHtml.Find("<input ", nPtr0 + 1)) == -1)
						goto CleanUp;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("value", sbValue) != 2)
						goto CleanUp;
					strDay = StrQTrim(sbValue);
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					if ((nPtr0 = m_sbHtml.Find("日付で検索", nPtr0 + 1)) == -1)
						goto CleanUp;
					if ((nPtr0 = m_sbHtml.Find("<input ", nPtr0 + 1)) == -1)
						goto CleanUp;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("value", sbValue) != 2)
						goto CleanUp;
					strYYList = StrQTrim(sbValue);
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					if ((nPtr0 = m_sbHtml.Find("<input ", nPtr0 + 1)) == -1)
						goto CleanUp;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("value", sbValue) != 2)
						goto CleanUp;
					strMMList = StrQTrim(sbValue);

					strYear = strYYList.Right(5).Left(4);
					if (! DtCurDate.ParseDateTime(strYear + '/' + strMonth + '/' + strDay))
						goto CleanUp;
					DtDate = DtCurDate;
//				}
//				if (! bDlFirst) {
					DtNextDate = DtCurDate;
					do {
						DtNextDate += Dts1Day;
					} while ((nDayOfWeek = DtNextDate.GetDayOfWeek()) == 1  ||  nDayOfWeek == 7);

					bDlFirst = TRUE;

					if (COleDateTime::GetCurrentTime().GetHour() >= 15) {
						DtDate += Dts1Day;
						DtNextDate += Dts1Day;
						i = 0;
						continue;
					}
				}

//				if ((nPtr0 = m_sbHtml.Find("連結")) == -1) {
				if ((nPtr0 = m_sbHtml.Find("決算種別")) == -1) {
					if (DtDate >= DtNextDate)
						break;
					DtDate += Dts1Day;
					i = 0;
					continue;
				}
				HtmlTokenizer.SetHtml(m_sbHtml);
				strDate = DtDate.Format("%m/%d");
				for (j = 0; j < 50; j ++) {
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<tr ", nPtr0 + 1)) == -1)
						break;
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<a ", nPtr0 + 1)) == -1)
						goto CleanUp;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
					if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
						goto CleanUp;
					ParseUrlSearch(StrQTrim(sbValue), MstsSearch);
					if (! MstsSearch.Lookup("scode", strCode))
						goto CleanUp;
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;

					m_SaCode.Add(strCode);
					m_SaDateTime.Add(strDate);
				}
				if ((nPtr0 = m_sbHtml.Find("次の50件", nPtr0 + 1)) == -1) {
					if (DtDate >= DtNextDate)
						break;
					DtDate += Dts1Day;
					i = 0;
				} else {
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlReverseTok())
						goto CleanUp;
					if (HtmlTokenizer.GetTagCmd().CompareNoCase("a")) {
						if (DtDate >= DtNextDate)
							break;
						DtDate += Dts1Day;
						i = 0;
					}
				}
			}
		}
	}
	catch (CException* pEx) {
		DispErrorLog("適時開示速報表示エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
	}

CleanUp:
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
	}
	Session.Close();

	PostQuitMessage(0);

	return TRUE;
}

int CDispNewsThread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDispNewsThread, CWinThread)
	//{{AFX_MSG_MAP(CDispNewsThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispNewsThread メッセージ ハンドラ

int CDispNewsThread::DlHtml(int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	int i;
	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;
	LPWSTR lpWideCharStr = NULL;
	int cchWideChar;
	DWORD dwErr;

	srand( (unsigned)time( NULL ) );
	sbHtml = IToA(rand());

	m_pFile = NULL;

	for (i = 0; i < 80; i ++) {
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
			while (nRdLen = m_pFile->Read(sz, DL_BUFLEN)) {
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

		if (nRv == 0) {
			nRv = -1;

			m_sbHtml.Replace(_T("\r"), pszEmpty);

			if ((m_sbHtml[0] & 0xff) == 0xef  &&  (m_sbHtml[1] & 0xff) == 0xbb  &&  (m_sbHtml[2] & 0xff) == 0xbf)
				m_sbHtml.Delete(0, 3);
			if ((cchWideChar = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)m_sbHtml, -1, NULL, 0)) == 0) {
				DispErrorLog("MultiByteToWideChar Error: %s\n", GetLastErrorMessage());
				break;
			}
			lpWideCharStr = (LPWSTR)new char[cchWideChar * 2];
			if (MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)m_sbHtml, -1, lpWideCharStr, cchWideChar) == 0) {
				DispErrorLog("MultiByteToWideChar Error: %s\n", GetLastErrorMessage());
				break;
			}
			m_sbHtml = (LPCWSTR)lpWideCharStr;
			delete [] lpWideCharStr;
			lpWideCharStr = NULL;

			nRv = 0;
		}

		break;
	}

	if (lpWideCharStr)
		delete [] lpWideCharStr;
	if (m_pFile) {
		m_pFile->Close();
		delete m_pFile;
	}

	return nRv;
}

void CDispNewsThread::DispErrorLog(LPCTSTR lpszFormat, ...)
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
	sb += StrFormat("m_sbOptional = %s\n", m_sbOptional);
	sb += StrFormat("m_nPort = %i\n", m_nPort);
	sb += StrFormat("m_sbHtml =\n%s", m_sbHtml);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}
