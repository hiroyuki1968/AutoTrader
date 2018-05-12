// DispStockAveThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "DispStockAveThread.h"

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
// CDispStockAveThread

IMPLEMENT_DYNCREATE(CDispStockAveThread, CWinThread)

CDispStockAveThread::CDispStockAveThread()
{
}

CDispStockAveThread::~CDispStockAveThread()
{
}

BOOL CDispStockAveThread::InitInstance()
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
		static CString strPreCode;
		static CStringArray SaPreKehai;
		static long lPreTradeCount = 0;
		static CStringArray SaPreKehai255;
		static long lPreTradeCount255 = 0;

		int i;
		int nPtr0;
		int nPtr1;
		int nPtr2;
		int nPtr3;
		CHtmlTokenizer HtmlTokenizer;
		CString strTag;
		int nAttr;
		CString strAttr;
		int nAttrLength;
		double dPriceC = m_dPrice;
		long lPrice225;
		double dSum255;
		long lAve255;
		CString strCount;
		CString strStk;
		CString strSijo;
		CString strPrice;
		long lPrice;
		long lPreEndPrice;
		long lPreEndPriceC;
		long lStartPrice;
		long lTradeCount;
		long lStopDiff;
		CKehai0 KehaiWork;
//		int nDayOfWeek = m_DtCur.GetDayOfWeek();
//		int nHour = m_DtCur.GetHour();
//		int nMinute = m_DtCur.GetMinute();

		if (! m_bMentenance1) {
//			if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 11)  ||  ! m_bStockAveThread) {
				if (! AfxParseURL(m_sbQuickInfoUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
					DispErrorLog("URL 解析エラー: %s\n", m_sbQuickInfoUrl);
					goto CleanUp;
				}

				m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

				m_strObject.Format(OBJ_KABU_QUICKHEAD, m_strObjectC);
				if (DlHtml(CHttpConnection::HTTP_VERB_GET, INTERNET_FLAG_RELOAD))
					goto CleanUp;

				m_sbHtml.Replace('\r', '\n');

				if ((nPtr0 = m_sbHtml.Find("日経平均")) == -1)
					goto CleanUp;
				for (i = 0; i < 2; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 8)) == -1)
						goto CleanUp;
				HtmlTokenizer.SetHtml(m_sbHtml);
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
				m_dPrice = atof(HtmlTokenizer.m_strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				for (i = 0; i < 3; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
						goto CleanUp;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
				if (HtmlTokenizer.m_strTag != m_strTime) {
					m_dPrePrice = dPriceC;
					m_strTime = HtmlTokenizer.m_strTag;

					if ((long)(m_dPrice - m_dPrePrice) == 0L) {
						dSum255 = 0.0;
						for (i = 30; i < 60; i ++) {
							if (m_lPrePrice255[i] == 0L) {
								dSum255 = 0.0;
								break;
							}
							dSum255 += m_lPrePrice255[i];
						}
						lAve255 = (long)(dSum255 / 30.0);
						if (lAve255  &&  m_lDiff255 != (long)m_dPrice - lAve255)
							m_lDiff255 = (long)m_dPrice - lAve255;
					}
				}
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				if ((nPtr0 = m_sbHtml.Find("225先物", nPtr0)) == -1)
					goto CleanUp;
				for (i = 0; i < 2; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 7)) == -1)
						goto CleanUp;
				HtmlTokenizer.SetHtml(m_sbHtml);
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (! HtmlTokenizer.HtmlTok())
						goto CleanUp;
				lPrice225 = atol(HtmlTokenizer.m_strTag);
				for (i = 0; i < 59; i ++)
					m_lPrePrice255[i + 1] = m_lPrePrice255[i];
				m_lPrePrice255[0] = lPrice225;

				m_dDiff = (double)lPrice225 + m_lDiff255 - m_dPrice;
//				m_dDiff = (double)lPrice225 - m_dPrice;

				m_sbHtml.Replace("docs/is.css", m_sbQuickInfoUrl + "docs/is.css");
				m_sbHtml.Replace("<body ", "<body leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\" ");
//				m_sbHtml.Replace("width=\"580\"", "width=\"1\"");
				m_sbHtml.Replace("width=\"530\"", "width=\"1\"");
				m_sbHtml.Replace("width=\"80\"", "width=\"1\"");
				m_sbHtml.Replace("日経平均", "日");
				m_sbHtml.Replace("日経JQ平均", "JQ");
				m_sbHtml.Replace("225先物(" + m_strContractMonth0S + ")", "先");
				m_sbHtml.Replace("東証2部指数", "T2");
				m_sbHtml.Replace("TOPIX", "TX");
				m_sbHtml.Replace("align=\"right\" class=\"tp-00td\"", "align=\"right\" class=\"tp-00td\" nowrap");
				m_sbHtml.Replace("ドル/円", "$\\");

				CStdioFile StdioFile0(m_strFPath0, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
				StdioFile0.WriteString(m_sbHtml);
				StdioFile0.Close();
/*
			} else {
				m_dDiff = 0.0;
				m_strFPath0.Empty();
			}
*/

			if (! m_bMentenance2  &&  m_strCode.GetLength()) {
//				if (m_pServer) {
					m_pServer->Close();
					delete m_pServer;
					m_pServer = NULL;
//				}

				if (! AfxParseURL(m_sbCosmoQuoteUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
					DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoQuoteUrl);
					goto CleanUp;
				}

				m_pServer = m_pSession->GetHttpConnection(m_strServerName, m_nPort);

				strStk = m_strCode.Left(4);
				strSijo = m_strCode.Mid(5);
				if (strSijo == "JQ")
					strSijo = "J";
				else if (strSijo == "NG")
					strSijo = "NJ";
				m_strObject.Format(OBJ_COSMOQUOTE0, strStk, strSijo);
				if (DlHtml(CHttpConnection::HTTP_VERB_GET))
					goto CleanUp;
				m_sbHtml.Replace("\r", pszEmpty);

				m_sbKehaiHtml = m_sbHtml;

				if ((nPtr0 = m_sbHtml.Find("現値エリア START", nPtr0)) == -1)
					goto CleanUp;
				HtmlTokenizer.SetHtml(m_sbHtml);
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
						goto CleanUp;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						goto CleanUp;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				lPrice = atol(strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				if ((nPtr0 = m_sbHtml.Find("始値", nPtr0)) == -1)
					goto CleanUp;
				for (i = 0; i < 2; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
						goto CleanUp;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						goto CleanUp;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				lStartPrice = atol(strTag);
				if ((nPtr0 = m_sbHtml.Find("出来高", nPtr0)) == -1)
					goto CleanUp;
				for (i = 0; i < 2; i ++)
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
						goto CleanUp;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						goto CleanUp;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				switch (m_sUnit) {
				case 5L:
				case 50L:
				case 500L:
				case 5000L:
				case 50000L:
					lTradeCount = atol(strTag) / (m_sUnit / 5);
					break;
				default:
					lTradeCount = atol(strTag) / m_sUnit;
				}
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				if ((nPtr0 = m_sbHtml.Find("前日終値", nPtr0)) == -1)
					goto CleanUp;
				if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 8)) == -1)
					goto CleanUp;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (i = 0; i < 2; i ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						goto CleanUp;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				lPreEndPrice = atol(strTag);
				if (! lPrice  &&  ! GetKehai(m_sbKehaiHtml, KehaiWork))
					lPrice = KehaiWork.m_plKehaiPrice[5];
				lPreEndPriceC = lPreEndPrice ? lPreEndPrice : lStartPrice;
				lStopDiff = GetStopDiff(lPreEndPriceC);

				if ((nPtr0 = m_sbHtml.Find("<div class=\"divBody\">")) == -1)
					goto CleanUp;
				nPtr0 += 21;
				if ((nPtr1 = m_sbHtml.Find("<!--気配エリア START-->"), nPtr0) == -1)
					goto CleanUp;
				m_sbHtml.Delete(nPtr0, nPtr1 - nPtr0);
				if ((nPtr0 = m_sbHtml.Find("<!--気配エリア END-->"), nPtr0) == -1)
					goto CleanUp;
				nPtr0 += 21;
				if ((nPtr1 = m_sbHtml.Find("<!--歩み値エリア START-->"), nPtr0) == -1)
					goto CleanUp;
				m_sbHtml.Delete(nPtr0, nPtr1 - nPtr0);
				if ((nPtr0 = m_sbHtml.Find("<!--歩み値エリア END-->"), nPtr0) == -1)
					goto CleanUp;
				if ((nPtr1 = StrReverseFindEx(m_sbHtml, "</div>")) == -1)
					goto CleanUp;
				nPtr1 += 6;
				m_sbHtml.Delete(nPtr0, nPtr1 - nPtr0);

				m_sbHtml.Replace("<link rel=\"stylesheet\" href=\"../css/style_quote.css\" id=\"m\">", pszEmpty);
				m_sbHtml.Replace("<link rel=\"stylesheet\" href=\"../css/style_quote_l.css\" id=\"l\">", pszEmpty);
				m_sbHtml.Replace("<script language=\"javascript\" src=\"../js/cb_styleSheet.js\"></script>", pszEmpty);
				m_sbHtml.Replace("top.checkPropertyStyleSheetNum()", "0");
				m_sbHtml.Replace("top.ReqViewKabu();", pszEmpty);
				m_sbHtml.Replace("changeText(changeStyleSheetNum);", pszEmpty);
				m_sbHtml.Replace("document.getElementById(\"menuLink\").style.display=\"\";", pszEmpty);
				m_sbHtml.Replace("<body ", "<body leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\" ");
				m_sbHtml.Replace("cellpadding=\"1\"", "cellpadding=\"0\"");
				m_sbHtml.Replace("最良指値", "最指");

				HtmlTokenizer.SetHtml(m_sbHtml);
				i = 0;
				while (nPtr0 = HtmlTokenizer.m_nHtmlPtr, HtmlTokenizer.HtmlTok()) {
					if (HtmlTokenizer.IsTagCmd()  &&  HtmlTokenizer.GetTagCmd().CompareNoCase("td") == 0  &&  HtmlTokenizer.FindTagAttr("class", strAttr) == 2) {
						strAttr = StrQTrim(strAttr);
						if (strAttr.Left(11) == "tdKehaiSell"  ||  strAttr.Left(10) == "tdKehaiPrc"  ||  strAttr.Left(10) == "tdKehaiBuy") {
							if (HtmlTokenizer.HtmlTok() == 0)
								goto CleanUp;
							strTag = HtmlTokenizer.m_strTag;
							if (SaPreKehai.GetUpperBound() < i  ||  SaPreKehai[i] != strTag) {
								if (m_strCode == strPreCode) {
									HtmlTokenizer.HtmlReverseTok();
									nPtr1 = HtmlTokenizer.m_nHtmlPtr;
									HtmlTokenizer.HtmlReverseTok();
									HtmlTokenizer.FindTagAttr("class", strAttr);
									nAttrLength = strAttr.GetLength();
									if (
										lTradeCount != lPreTradeCount
										&& (
											((strSijo == "T"  ||  strSijo == "M")  &&  i >= 4 * 3  &&  i < 6 * 3)
											||  ((strSijo == "O"  ||  strSijo == "NJ"  ||  strSijo == "J")  &&  (i < 2 * 3 || i >= 2 * 3 + 4 * 3  &&  i < 2 * 3 + 6 * 3))
										)
									)
										if (strAttr[nAttrLength - 2] == ' ')
											strAttr.SetAt(nAttrLength - 3, '3');
										else
											strAttr.SetAt(nAttrLength - 2, '3');
									else
										if (strAttr[nAttrLength - 2] == ' ')
											strAttr.SetAt(nAttrLength - 3, '2');
										else
											strAttr.SetAt(nAttrLength - 2, '2');
									HtmlTokenizer.ChangeTagAttr(strAttr);
									HtmlTokenizer.m_strHtml.Delete(nPtr0, nPtr1 - nPtr0);
									HtmlTokenizer.m_strHtml.Insert(nPtr0, HtmlTokenizer.m_strTag);
									HtmlTokenizer.m_nHtmlPtr = nPtr0 + HtmlTokenizer.m_nTagLen;
								}
								SaPreKehai.SetAtGrow(i, strTag);
							}
							i ++;
						}
					}
				}
				strPreCode = m_strCode;
				lPreTradeCount = lTradeCount;
				m_sbHtml = HtmlTokenizer.m_strHtml;

				if ((nPtr0 = StrReverseFindEx(m_sbHtml, "</div>")) == -1)
					goto CleanUp;
				nPtr0 += 6;
				m_sbHtml.Insert(
					nPtr0,
					StrFormat(
						"<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">"
						"<tr><td>%s %s</td></tr>"
						"<tr><td>%ld / %ld / %ld</td></tr>"
						"<tr><td>%ld / %ld</td></tr>"
						"<tr><td>%ld / %ld x %d</td></tr>"
						"<tr><td>%ldt %ld%%</td></tr>"
						"<tr><td>%du %dt</td></tr>"
						"</table>",
						m_strCodeEx, StrConvHalfWidth(m_strName),
						lPreEndPriceC + lStopDiff, lPrice, lPreEndPriceC - lStopDiff,
						lPreEndPrice, lStartPrice,
						m_lMaxTradeCount, lTradeCount, m_sUnit,
						(lPreEndPriceC + lStopDiff - lPrice) / GetDiff(lPreEndPriceC + 1L), (lPrice - lPreEndPriceC) * 100 / lStopDiff,
						GetSuryo(lPrice ? lPrice : lPreEndPriceC, m_sUnit), GetTick(lPrice ? lPrice : lPreEndPriceC, m_sUnit)
					)
				);
				if ((nPtr0 = StrFindNoCase(m_sbHtml, "</head>")) == -1)
					goto CleanUp;
				m_sbHtml.Insert(
					nPtr0,
					"<style>\n"
					"th {font-size:10px;}\n"
					"td {font-size:10px;}\n"
					".table3\n"
					"{\n"
					"    BORDER-BOTTOM: #ccddff 1px solid;\n"
					"    BORDER-LEFT: #ccddff 1px solid;\n"
					"    PADDING-BOTTOM: 0px;\n"
					"    PADDING-LEFT: 1px;\n"
					"    PADDING-RIGHT: 1px;\n"
					"    BORDER-COLLAPSE: collapse;\n"
					"    BORDER-TOP: #ccddff 1px solid;\n"
					"    BORDER-RIGHT: #ccddff 1px solid;\n"
					"    PADDING-TOP: 0px\n"
					"}\n"
					"DIV.divKehaiArea\n"
					"{\n"
					"    BORDER-BOTTOM: #cccccc 0px solid;\n"
					"    BORDER-LEFT: #cccccc 0px solid;\n"
					"    PADDING-BOTTOM: 0px;\n"
					"    BACKGROUND-COLOR: #ffffff;\n"
					"    PADDING-LEFT: 0px;\n"
					"    PADDING-RIGHT: 0px;\n"
					"    BORDER-TOP: #cccccc 0px solid;\n"
					"    BORDER-RIGHT: #cccccc 0px solid;\n"
					"    PADDING-TOP: 0px\n"
					"}\n"
					".tdKehaiTitle\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #deeaff;\n"
					"    COLOR: #101010;\n"
					"}\n"
					".tdKehaiBuy0\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #dd1111;\n"
					"}\n"
					".tdKehaiBuy1\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #dd1111;\n"
					"}\n"
					".tdKehaiBuy2\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #00ffff;\n"
					"    COLOR: #dd1111;\n"
					"}\n"
					".tdKehaiBuy3\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #ffff00;\n"
					"    COLOR: #dd1111;\n"
					"}\n"
					".tdKehaiSell0\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #119911;\n"
					"}\n"
					".tdKehaiSell1\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #119911;\n"
					"}\n"
					".tdKehaiSell2\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #00ffff;\n"
					"    COLOR: #119911;\n"
					"}\n"
					".tdKehaiSell3\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #ffff00;\n"
					"    COLOR: #119911;\n"
					"}\n"
					".tdKehaiPrc0\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdKehaiPrc1\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdKehaiPrc2\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #00ffff;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdKehaiPrc3\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #ffff00;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdKehaiFlg0\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdKehaiFlg1\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #222244;\n"
					"}\n"
					"DIV.divListArea\n"
					"{\n"
					"    BORDER-BOTTOM: #cccccc 0px solid;\n"
					"    BORDER-LEFT: #cccccc 0px solid;\n"
					"    PADDING-BOTTOM: 1px;\n"
					"    BACKGROUND-COLOR: #ffffff;\n"
					"    PADDING-LEFT: 1px;\n"
					"    PADDING-RIGHT: 1px;\n"
					"    BORDER-TOP: #cccccc 0px solid;\n"
					"    BORDER-RIGHT: #cccccc 0px solid;\n"
					"    PADDING-TOP: 1px\n"
					"}\n"
					".tdListTitle\n"
					"{\n"
					"    TEXT-ALIGN: left;\n"
					"    BACKGROUND-COLOR: #deeaff;\n"
					"    COLOR: #101010;\n"
					"}\n"
					".tdListNum0\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdListNum1\n"
					"{\n"
					"    TEXT-ALIGN: right;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #222244;\n"
					"}\n"
					".tdListTime0\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #fafaff;\n"
					"    COLOR: #6666aa;\n"
					"}\n"
					".tdListTime1\n"
					"{\n"
					"    TEXT-ALIGN: center;\n"
					"    BACKGROUND-COLOR: #efeff3;\n"
					"    COLOR: #6666aa;\n"
					"}\n"
					"</style>\n"
				);
			} else
				m_sbHtml.Empty();

			CStdioFile StdioFile2(m_strFPath2, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
			StdioFile2.WriteString(m_sbHtml);
			StdioFile2.Close();

//			if (m_pServer) {
				m_pServer->Close();
				delete m_pServer;
				m_pServer = NULL;
//			}

			if (! AfxParseURL(m_sbQuickInfoUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
				DispErrorLog("URL 解析エラー: %s\n", m_sbQuickInfoUrl);
				goto CleanUp;
			}

			m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

//			m_strObject.Format(OBJ_INDEX_QUOTE, m_strObjectC, GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO9) == IDC_RADIO3 ? "101." + m_strContractMonth1 : "101." + m_strContractMonth0);
			m_strObject.Format(OBJ_INDEX_QUOTE, m_strObjectC, "101." + m_strContractMonth0);
			if (DlHtml(CHttpConnection::HTTP_VERB_GET))
				goto CleanUp;

			m_sbHtml.Replace('\r', '\n');

			if ((nPtr0 = m_sbHtml.Find("<!--見出し（銘柄名）　ここから-->")) == -1)
				goto CleanUp;
			if ((nPtr1 = m_sbHtml.Find("<!--左列　ここから-->", nPtr0 + 1)) == -1)
				goto CleanUp;
			for (i = 0; i < 2; i ++)
				if ((nPtr1 = StrFindNoCase(m_sbHtml, "<table ", nPtr1 + 1)) == -1)
					goto CleanUp;
			m_sbHtml.Delete(nPtr0, nPtr1 - nPtr0);
			if ((nPtr0 = StrFindNoCase(m_sbHtml, "</table>", nPtr0 + 1)) == -1)
				goto CleanUp;
			nPtr0 += 8;
			if ((nPtr2 = m_sbHtml.Find("現値", nPtr0 + 1)) == -1)
				goto CleanUp;
			if ((nPtr2 = StrFindNoCase(m_sbHtml, "<font ", nPtr2 + 1)) == -1)
				goto CleanUp;
			if ((nPtr2 = m_sbHtml.Find('>', nPtr2 + 1)) == -1)
				goto CleanUp;
			nPtr2 ++;
			if ((nPtr3 = m_sbHtml.Find('<', nPtr2)) == -1)
				goto CleanUp;
			strPrice = m_sbHtml.Mid(nPtr2, nPtr3 - nPtr2);
			lPrice = atol(strPrice);
			if ((nPtr2 = m_sbHtml.Find("前日比", nPtr3)) == -1)
				goto CleanUp;
			if ((nPtr2 = StrFindNoCase(m_sbHtml, "<font ", nPtr2 + 1)) == -1)
				goto CleanUp;
			if ((nPtr2 = m_sbHtml.Find('>', nPtr2 + 1)) == -1)
				goto CleanUp;
			nPtr2 ++;
			if ((nPtr3 = m_sbHtml.Find('<', nPtr2)) == -1)
				goto CleanUp;
			strPrice = m_sbHtml.Mid(nPtr2, nPtr3 - nPtr2);
			lPreEndPrice = lPrice - atol(strPrice);
			if ((nPtr2 = m_sbHtml.Find("始値", nPtr3)) == -1)
				goto CleanUp;
			if ((nPtr2 = StrFindNoCase(m_sbHtml, "<td ", nPtr2 + 1)) == -1)
				goto CleanUp;
			if ((nPtr2 = m_sbHtml.Find('>', nPtr2 + 1)) == -1)
				goto CleanUp;
			nPtr2 ++;
			if ((nPtr3 = m_sbHtml.Find('<', nPtr2)) == -1)
				goto CleanUp;
			strPrice = m_sbHtml.Mid(nPtr2, nPtr3 - nPtr2);
			lStartPrice = atol(strPrice);
			if ((nPtr2 = m_sbHtml.Find("売買高", nPtr3)) == -1)
				goto CleanUp;
			if ((nPtr2 = StrFindNoCase(m_sbHtml, "<td ", nPtr2 + 1)) == -1)
				goto CleanUp;
			if ((nPtr2 = m_sbHtml.Find('>', nPtr2 + 1)) == -1)
				goto CleanUp;
			nPtr2 ++;
			if ((nPtr3 = m_sbHtml.Find('<', nPtr2)) == -1)
				goto CleanUp;
			strCount = m_sbHtml.Mid(nPtr2, nPtr3 - nPtr2);
			lTradeCount = atol(strCount);
			if ((nPtr1 = m_sbHtml.Find("利用者がこれらの情報を利用して行なう判断の一切について責任を負いません。", nPtr0 + 1)) == -1)
				goto CleanUp;
			if ((nPtr1 = StrFindNoCase(m_sbHtml, "</table>", nPtr1 + 1)) == -1)
				goto CleanUp;
			nPtr1 += 8;
			m_sbHtml.Delete(nPtr0, nPtr1 - nPtr0);

			HtmlTokenizer.SetHtml(m_sbHtml);
			i = 0;
			while (nPtr0 = HtmlTokenizer.m_nHtmlPtr, HtmlTokenizer.HtmlTok()) {
				if (
					HtmlTokenizer.IsTagCmd()
					&&  HtmlTokenizer.GetTagCmd().CompareNoCase("td") == 0
					&&  (
						HtmlTokenizer.FindTagAttr("align", strAttr) == 2
						&&  HtmlTokenizer.FindTagAttr("colspan", strAttr) == 2
						&&  HtmlTokenizer.FindTagAttr("bgcolor", strAttr) == -1
						||  HtmlTokenizer.FindTagAttr("bgcolor", strAttr) == 2
						&&  HtmlTokenizer.FindTagAttr("align", strAttr) == 2
						&&  HtmlTokenizer.FindTagAttr("nowrap", strAttr) == 1
						||  HtmlTokenizer.FindTagAttr("bgcolor", strAttr) == -1
						&&  HtmlTokenizer.FindTagAttr("align", strAttr) == 2
						&&  HtmlTokenizer.FindTagAttr("nowrap", strAttr) == 1
					)
				) {
					if (HtmlTokenizer.HtmlTok() == 0)
						goto CleanUp;
					strTag = HtmlTokenizer.m_strTag;
					if (SaPreKehai255.GetUpperBound() < i  ||  SaPreKehai255[i] != strTag) {
						if (SaPreKehai255.GetUpperBound() >= i) {
							HtmlTokenizer.HtmlReverseTok();
							nPtr1 = HtmlTokenizer.m_nHtmlPtr;
							HtmlTokenizer.HtmlReverseTok();
							nAttr = HtmlTokenizer.FindTagAttr("bgcolor", strAttr);
							if (
								lTradeCount != lPreTradeCount255
								&&  (i < 3 + 2 || i >= 3 + 2 + 7 * 2  &&  i < 3 + 2 + 7 * 2 + 2 * 4)
							)
								strAttr = "\"#ffff00\"";
							else
								strAttr = "\"#00ffff\"";
							if (nAttr == 2)
								HtmlTokenizer.ChangeTagAttr(strAttr);
							else
								HtmlTokenizer.AddTagAttr("bgcolor", strAttr);
							HtmlTokenizer.m_strHtml.Delete(nPtr0, nPtr1 - nPtr0);
							HtmlTokenizer.m_strHtml.Insert(nPtr0, HtmlTokenizer.m_strTag);
							HtmlTokenizer.m_nHtmlPtr = nPtr0 + HtmlTokenizer.m_nTagLen;
						}
						SaPreKehai255.SetAtGrow(i, strTag);
					}
					i ++;
				}
			}
			lPreTradeCount255 = lTradeCount;
			m_sbHtml = HtmlTokenizer.m_strHtml;

			if ((nPtr0 = StrReverseFindEx(m_sbHtml, "</body>")) == -1)
				goto CleanUp;
			m_sbHtml.Insert(
				nPtr0,
				StrFormat(
					"\n"
					"<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n"
					"<tr><td>売買高</td><td>%ld</td></tr>\n"
					"<tr><td>直近終値&nbsp;</td><td>%ld</td></tr>\n"
					"<tr><td>始値</td><td>%ld</td></tr>\n"
					"<tr><td>現値</td><td>%ld</td></tr>\n"
					"</table>",
					lTradeCount,
					lPreEndPrice, lStartPrice,
					lPrice
				)
			);
			if ((nPtr0 = StrFindNoCase(m_sbHtml, "</head>")) == -1)
				goto CleanUp;
			m_sbHtml.Insert(
				nPtr0,
				"<style>\n"
				"th {font-size:10px;}\n"
				"td {font-size:10px;}\n"
				"</style>\n"
			);

			m_sbHtml.Replace("docs/is.css", m_sbQuickInfoUrl + "docs/is.css");
			m_sbHtml.Replace("<script language=\"JavaScript\" src=\"docs/indexcharts.js\"></script>", pszEmpty);
			m_sbHtml.Replace("<body ", "<body leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\" ");
			m_sbHtml.Replace(" onLoad=\"parent.auto_select();\"", pszEmpty);
			m_sbHtml.Replace("cellpadding=\"3\"", "cellpadding=\"0\"");
			m_sbHtml.Replace("最良指値", "最指");

			CStdioFile StdioFile1(m_strFPath1, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
			StdioFile1.WriteString(m_sbHtml);
			StdioFile1.Close();
		}
	}
	catch (CFileException* pEx) {
		if (pEx->m_cause != CFileException::sharingViolation)
			DispErrorLog("日経平均表示エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
	}
	catch (CException* pEx) {
		DispErrorLog("日経平均表示エラー: %s\n", GetExceptionErrorMessage(pEx));
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

int CDispStockAveThread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDispStockAveThread, CWinThread)
	//{{AFX_MSG_MAP(CDispStockAveThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispStockAveThread メッセージ ハンドラ

int CDispStockAveThread::DlHtml(int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	int i;
	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;
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

		break;
	}

	if (m_pFile) {
		m_pFile->Close();
		delete m_pFile;
	}

	return nRv;
}

void CDispStockAveThread::DispErrorLog(LPCTSTR lpszFormat, ...)
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
	sb += StrFormat("m_sbHtml =\n%s", m_sbHtml);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}
