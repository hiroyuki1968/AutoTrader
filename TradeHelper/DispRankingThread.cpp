// DispRankingThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "DispRankingThread.h"

#pragma warning(push)
#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
    no_namespace rename("EOF", "EndOfFile")
#pragma warning(pop)

#include <icrsint.h>
#include "../Common.h"
#include "../Html.h"
#include "../AutoTraderDef.h"
#include "TradeHelperDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Function declarations
inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

/////////////////////////////////////////////////////////////////////////////
// CDispRankingThread

IMPLEMENT_DYNCREATE(CDispRankingThread, CWinThread)

CDispRankingThread::CDispRankingThread()
{
}

CDispRankingThread::~CDispRankingThread()
{
}

BOOL CDispRankingThread::InitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。

	if (m_nMode < 9) {
		_ConnectionPtr  pConnection;
		_RecordsetPtr   pRst0;
		_RecordsetPtr   pRst1;
		_variant_t      vt;
		_variant_t      vtKeyValues;
		SAFEARRAY       *pSa = NULL;
		long            ix;

		int i;
		int imax;
		COleDateTime DtCur = GetCurrentTimeEx();
		COleDateTime DtLast;
		int nDayOfWeek;
		int nHour;
		int nMinute;
		BOOL bKehaiTime;
		CString strCode;
		CMapStringToPtr MstCode;
		void* pVoid;
		CStringArray SaCode;
		CString strCode0;
		CString strCode1;
		COleDateTime DtDateTime0;
		COleDateTime DtDateTime1;
		Funashi FunashiWork;
		Info InfoWork;
		CSortableFunashiArray Sfa;
		long lPreEndPrice;
		CString strSijo;
		CString strSijoName;
		CString strCodeEx;
		long lPrice;
		long lDiff;
		long lDiffPrice;
		CString strDiffPrice;
		CString strName;
		long lStopDiffRatio;
		CString strStopDiffRatio;
		long lTradeCount1000;
		long lHighPrice;
		long lLowPrice;
		BOOL bCoInitialize = FALSE;

		try
		{
			if(FAILED(::CoInitialize(NULL)))
				goto CleanUp0;
			bCoInitialize = TRUE;

			TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
			pConnection->Open ((LPCTSTR)("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_strDBFPath), pszEmpty, pszEmpty, adConnectUnspecified);

			TESTHR(pRst0.CreateInstance(__uuidof(Recordset)));
			TESTHR(pRst1.CreateInstance(__uuidof(Recordset)));

			pSa = SafeArrayCreateVector(VT_VARIANT, 0, 1);
			if (!pSa) _com_issue_error(E_OUTOFMEMORY);

			vtKeyValues.vt = VT_ARRAY | VT_VARIANT;
			vtKeyValues.parray = pSa;

			ix = 0;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtCur)));

			pRst0->Open (TBL_FUNASHIDATETIME, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszPrimaryKey;
			pRst0->Seek(vtKeyValues, adSeekBeforeEQ);
			if (pRst0->EndOfFile)
				goto CleanUp0;
			DtLast = (double)pRst0->Fields->Item[FLD_FD_DATETIME]->Value;
			pRst0->Close();

		   TESTHR(SafeArrayDestroy(pSa));

			nDayOfWeek = DtLast.GetDayOfWeek();
			nHour = DtLast.GetHour();
			nMinute = DtLast.GetMinute();
			bKehaiTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 9  ||  nHour == 12  &&  (nMinute >= 5  &&  nMinute < 30));

			pSa = SafeArrayCreateVector(VT_VARIANT, 0, 2);
			if (!pSa) _com_issue_error(E_OUTOFMEMORY);

			vtKeyValues.parray = pSa;

			ix = 1;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(COleDateTime(9999, 12, 31, 23, 59, 59))));

			ix = 0;

			pRst0->Open (TBL_FUNASHI0, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszSecondaryKey;
			strCode.Empty();
			while (1) {
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(strCode)));
				pRst0->Seek(vtKeyValues, adSeekAfter);
				if (pRst0->EndOfFile)
					break;
				strCode = (char *)(_bstr_t)pRst0->Fields->Item[FLD_FU_CODE]->Value;
				if (! MstCode.Lookup(strCode, pVoid)  &&  m_pMstpSelCode->Lookup(strCode, pVoid)) {
					SaCode.Add(strCode);
					MstCode[strCode] = NULL;
				}
			}
			pRst0->Close();

			pRst0->Open (bKehaiTime ? TBL_FUNASHI2 : TBL_FUNASHI1, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszSecondaryKey;
			strCode.Empty();
			while (1) {
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(strCode)));
				pRst0->Seek(vtKeyValues, adSeekAfter);
				if (pRst0->EndOfFile)
					break;
				strCode = (char *)(_bstr_t)pRst0->Fields->Item[FLD_FU_CODE]->Value;
				if (! MstCode.Lookup(strCode, pVoid)  &&  m_pMstpSelCode->Lookup(strCode, pVoid)) {
					SaCode.Add(strCode);
					MstCode[strCode] = NULL;
				}
			}
			pRst0->Close();

			ix = 1;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtLast)));

			ix = 0;

			pRst0->Open (TBL_FUNASHI0, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszSecondaryKey;
			pRst1->Open (bKehaiTime ? TBL_FUNASHI2 : TBL_FUNASHI1, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst1->Index = pszSecondaryKey;
			for (i = 0, imax = SaCode.GetSize(); i < imax; i ++) {
				strCode = SaCode[i];
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(strCode)));

				pRst0->Seek(vtKeyValues, adSeekBeforeEQ);
				strCode0 = (char *)(_bstr_t)pRst0->Fields->Item[FLD_FU_CODE]->Value;
				DtDateTime0 = (double)pRst0->Fields->Item[FLD_FD_DATETIME]->Value;

				pRst1->Seek(vtKeyValues, adSeekBeforeEQ);
				if (pRst1->EndOfFile)
					strCode1.Empty();
				else {
					strCode1 = (char *)(_bstr_t)pRst1->Fields->Item[FLD_FU_CODE]->Value;
					DtDateTime1 = (double)pRst1->Fields->Item[FLD_FD_DATETIME]->Value;
				}

				FunashiWork.strCode = strCode;

				if (strCode0 == strCode  &&  (strCode1 != strCode  ||  DtDateTime0 >= DtDateTime1)) {
					vt = pRst0->Fields->Item[bKehaiTime ? FLD_FU_KEHAIPRICE "5" : FLD_FU_PRICE]->Value;
					FunashiWork.lPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					if (! bKehaiTime) {
						vt = pRst0->Fields->Item[FLD_FU_TRADECOUNT]->Value;
						FunashiWork.lTradeCount = vt.vt == VT_NULL ? 0L : (long)vt;
					}
				} else if (strCode1 == strCode  &&  (strCode0 != strCode  ||  DtDateTime1 > DtDateTime0)) {
					vt = pRst1->Fields->Item[bKehaiTime ? FLD_FU_KEHAIPRICE "1" : FLD_FU_PRICE]->Value;
					FunashiWork.lPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					if (! bKehaiTime) {
						vt = pRst1->Fields->Item[FLD_FU_TRADECOUNT]->Value;
						FunashiWork.lTradeCount = vt.vt == VT_NULL ? 0L : (long)vt;
					}
				} else
					continue;

				Sfa.Add(FunashiWork);
			}
			pRst1->Close();
			pRst0->Close();

			DtLast.SetDate(DtLast.GetYear(), DtLast.GetMonth(), DtLast.GetDay());
			ix = 1;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtLast)));

			ix = 0;

			pRst0->Open (TBL_HIASHI, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszSecondaryKey;
			for (i = 0, imax = SaCode.GetSize(); i < imax; i ++) {
				strCode = SaCode[i];
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(strCode)));
				pRst0->Seek(vtKeyValues, adSeekBefore);

				if (pRst0->EndOfFile  ||  (char *)(_bstr_t)pRst0->Fields->Item[FLD_HI_CODE]->Value != strCode) {
					Sfa[i].lPreEndPrice = Sfa[i].lPreEndTradeCount = 0L;
					Sfa[i].lDiff = Sfa[i].lStopDiff = 1L;
				} else {
					vt = pRst0->Fields->Item[FLD_HI_PRICE]->Value;
					Sfa[i].lPreEndPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					vt = pRst0->Fields->Item[FLD_HI_TRADECOUNT]->Value;
					Sfa[i].lPreEndTradeCount = vt.vt == VT_NULL ? 0L : (long)vt;

					Sfa[i].lDiff = GetDiff(Sfa[i].lPreEndPrice + 1L);
					Sfa[i].lStopDiff = GetStopDiff(Sfa[i].lPreEndPrice);
				}
			}
			pRst0->Close();

			ix = 0;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtLast)));

			ix = 1;

			pRst0->Open (TBL_HIASHI, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst0->Index = pszPrimaryKey;
			for (i = 0, imax = SaCode.GetSize(); i < imax; i ++) {
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(SaCode[i])));
				pRst0->Seek(vtKeyValues, adSeekFirstEQ);

				if (pRst0->EndOfFile) {
					Sfa[i].lStartPrice = Sfa[i].lHighPrice = Sfa[i].lLowPrice = 0L;

					Sfa[i].lDiffHigh = GetDiff(Sfa[i].lPreEndPrice);
					Sfa[i].lDiffLow = GetDiff(Sfa[i].lPreEndPrice + 1L);
				} else {
					vt = pRst0->Fields->Item[FLD_HI_STARTPRICE]->Value;
					Sfa[i].lStartPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					vt = pRst0->Fields->Item[FLD_HI_HIGHPRICE]->Value;
					Sfa[i].lHighPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					vt = pRst0->Fields->Item[FLD_HI_LOWPRICE]->Value;
					Sfa[i].lLowPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					if (bKehaiTime) {
						vt = pRst0->Fields->Item[FLD_HI_TRADECOUNT]->Value;
						Sfa[i].lTradeCount = vt.vt == VT_NULL ? 0L : (long)vt;
					}

					Sfa[i].lDiffHigh = GetDiff(Sfa[i].lHighPrice);
					Sfa[i].lDiffLow = GetDiff(Sfa[i].lLowPrice + 1L);
				}
			}
			pRst0->Close();

			::CoUninitialize();
			bCoInitialize = FALSE;

			switch (m_nMode) {
			case 0:
//				Sfa.Sort();
				Sfa.Sort(CSortableFunashiArray::Compare2);
				break;
			case 1:
//				Sfa.Sort(CSortableFunashiArray::Compare1);
				Sfa.Sort(CSortableFunashiArray::Compare3);
				break;
			case 2:
				Sfa.Sort(CSortableFunashiArray::Compare4);
				break;
			case 3:
				Sfa.Sort(CSortableFunashiArray::Compare5);
				break;
			case 4:
				Sfa.Sort(CSortableFunashiArray::Compare6);
				break;
			case 5:
				Sfa.Sort(CSortableFunashiArray::Compare7);
				break;
			case 6:
				Sfa.Sort(CSortableFunashiArray::Compare8);
				break;
			case 7:
				Sfa.Sort(CSortableFunashiArray::Compare9);
				break;
			default:
				Sfa.Sort(CSortableFunashiArray::Compare10);
			}

			for (i = 0, imax = Sfa.GetSize(); i < imax; i ++) {
				strCode = Sfa[i].strCode;
				if (m_pMstiCodeInfo->Lookup(strCode, InfoWork)) {
					if (! (lPreEndPrice = Sfa[i].lPreEndPrice))
						lPreEndPrice = Sfa[i].lStartPrice;
					strSijo = strCode.Mid(5);
					strSijoName = InfoWork.strSijo;
					strCodeEx = strCode;
					if (strSijo == "T") {
						if (strSijoName.Left(10) == "東証ﾏｻﾞｰｽﾞ")
							strCodeEx += 'M';
						else if (strSijoName.Left(8) == "東証２部")
							strCodeEx += '2';
					} else if (strSijo == "O")
						if (strSijoName.Left(8) == "大証２部")
							strCodeEx += '2';
					lPrice = Sfa[i].lPrice;
					lDiff = GetDiff(lPreEndPrice + 1L);
					lDiffPrice = lPrice / lDiff;
					strDiffPrice = LToA(lDiffPrice);
					strName = StrConvHalfWidth(InfoWork.strName).Left(10 - 1 - strDiffPrice.GetLength());
					lStopDiffRatio = (lPrice - lPreEndPrice) * 100 / GetStopDiff(lPreEndPrice);
					if (lStopDiffRatio <= -100)
						strStopDiffRatio = "-00";
					else
						strStopDiffRatio = LToA(lStopDiffRatio);
					lTradeCount1000 = Sfa[i].lTradeCount * lDiff / 1000L;
					m_SaList.Add(
						StrFormat(
							"%s %s%s %s %s %s",
							(strCodeEx + ' ').Left(7),
							strName,
							CString(' ', 10 - strName.GetLength() - 1 - strDiffPrice.GetLength()),
							strDiffPrice,
							("  " + strStopDiffRatio).Right(3),
							lTradeCount1000 < 10000L ? ("   " + LToA(lTradeCount1000)).Right(4) : "9999"
						)
					);
					m_SaCode.Add(strCode);
					m_DwaTradeCount1000.Add(lTradeCount1000);
					m_DwaDiffPrice.Add(lDiffPrice);
					if (m_nMode == 1  ||  m_nMode == 3) {
						lHighPrice = Sfa[i].lHighPrice ? Sfa[i].lHighPrice : lPreEndPrice;
						m_DwaLowDiffPrice.Add((lPrice - lHighPrice) / GetDiff(lHighPrice) / GetTick(lHighPrice, InfoWork.sUnit));
					} else {
						lLowPrice = Sfa[i].lLowPrice ? Sfa[i].lLowPrice : lPreEndPrice;
						m_DwaLowDiffPrice.Add((lPrice - lLowPrice) / GetDiff(lLowPrice + 1L) / GetTick(lLowPrice, InfoWork.sUnit));
					}
				}
			}
		}
		catch (_com_error &e) {
			ErrorPtr  pErr = NULL;

			for (long i = 0, imax = pConnection->Errors->Count; i < imax; i ++) {
				pErr = pConnection->Errors->GetItem(i);
				DispErrorLog("ADO ランキング表示エラー: %s\n", pErr->Description);
			}
			DispErrorLog("COM ランキング表示エラー: %s, %s\n", e.ErrorMessage(), e.Description());
		}
		catch (CException* pEx) {
			DispErrorLog("ランキング表示エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

CleanUp0:
		if (bCoInitialize)
			::CoUninitialize();
	} else if (m_nMode < 18) {
		CInternetSession* pSession = NULL;

		_ConnectionPtr  pConnection;
		_RecordsetPtr   pRst;
		_variant_t      vt;
		_variant_t      vtKeyValues;
		SAFEARRAY       *pSa = NULL;
		long            ix;

		int i;
		int j;
		int k;
		int imax;
		int jmax;
		CString strObjRank0;
		CString strObjRank1;
		CStringBuffer psbHtml[14];
		COleDateTime DtCur = COleDateTime::GetCurrentTime();
		COleDateTime DtLast;
		int nPtr0;
		CHtmlTokenizer HtmlTokenizer;
		CStringBuffer sbTag;
		CString strCode;
		CString strPrice;
		CString strPreEndPriceDiff;
		CString strTradeCount;
		Funashi FunashiWork;
		Info InfoWork;
		CSortableFunashiArray Sfa;
		CStringArray SaCode;
		CUIntArray UiaIndex;
		CString strReqCode;
		long lStartPrice;
		long lHighPrice;
		long lLowPrice;
		CString strSijo;
		CString strSijoName;
		CString strCodeEx;
		long lPrice;
		long lPreEndPrice;
		long lDiff;
		long lDiffPrice;
		CString strDiffPrice;
		CString strName;
		long lStopDiffRatio;
		CString strStopDiffRatio;
		long lTradeCount1000;
		BOOL bCoInitialize = FALSE;

		m_pServer = NULL;

		try {
			pSession = new CInternetSession(_T("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/4.0; GTB6.6; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.1; .NET4.0C)"));

			pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
			pSession->SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

			if (! AfxParseURL(m_sbQuickInfoUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
				DispErrorLog("URL 解析エラー: %s\n", m_sbQuickInfoUrl);
				goto CleanUp1;
			}

			m_pServer = pSession->GetHttpConnection(m_strServerName, m_nPort);

			switch (m_nMode) {
			case 9:
				strObjRank0 = OBJ_RANK0;
				strObjRank1 = OBJ_RANK1;
				break;
			case 10:
				strObjRank0 = OBJ_RANK2;
				strObjRank1 = OBJ_RANK3;
				break;
			case 11:
				strObjRank0 = OBJ_RANK0;
				strObjRank1 = OBJ_RANK1;
				break;
			case 12:
				strObjRank0 = OBJ_RANK2;
				strObjRank1 = OBJ_RANK3;
				break;
			case 13:
				strObjRank0 = OBJ_RANK4;
				strObjRank1 = OBJ_RANK5;
				break;
			case 14:
				strObjRank0 = OBJ_RANK6;
				strObjRank1 = OBJ_RANK7;
				break;
			case 15:
				strObjRank0 = OBJ_RANK8;
				strObjRank1 = OBJ_RANK9;
				break;
			case 16:
				strObjRank0 = OBJ_RANK0;
				strObjRank1 = OBJ_RANK1;
				break;
			default:
				strObjRank0 = OBJ_RANK2;
				strObjRank1 = OBJ_RANK3;
			}

//			for (i = 0; i < 14; i ++) {
			for (i = 0; i < 12; i ++) {
				switch (i) {
				case 0:
					m_strObject.Format(strObjRank0, m_strObjectC, "T", "%82P%95%94");
					break;
				case 1:
					m_strObject.Format(strObjRank1, m_strObjectC, "T", "%82P%95%94");
					break;
				case 2:
					m_strObject.Format(strObjRank0, m_strObjectC, "T", "%82Q%95%94");
					break;
				case 3:
					m_strObject.Format(strObjRank1, m_strObjectC, "T", "%82Q%95%94");
					break;
				case 4:
					m_strObject.Format(strObjRank0, m_strObjectC, "T", "%CF%BB%DE%B0%BD%DE");
					break;
				case 5:
					m_strObject.Format(strObjRank1, m_strObjectC, "T", "%CF%BB%DE%B0%BD%DE");
					break;
				case 6:
					m_strObject.Format(strObjRank0, m_strObjectC, "O", "%82P%95%94");
					break;
				case 7:
					m_strObject.Format(strObjRank1, m_strObjectC, "O", "%82P%95%94");
					break;
				case 8:
					m_strObject.Format(strObjRank0, m_strObjectC, "O", "%82Q%95%94");
					break;
				case 9:
					m_strObject.Format(strObjRank1, m_strObjectC, "O", "%82Q%95%94");
					break;
/*
				case 10:
					m_strObject.Format(strObjRank0, m_strObjectC, "NJ", pszEmpty);
					break;
				case 11:
					m_strObject.Format(strObjRank1, m_strObjectC, "NJ", pszEmpty);
					break;
				case 12:
*/
				case 10:
					m_strObject.Format(strObjRank0, m_strObjectC, "JQ", pszEmpty);
					break;
				default:
					m_strObject.Format(strObjRank1, m_strObjectC, "JQ", pszEmpty);
				}
				if (DlHtml(CHttpConnection::HTTP_VERB_GET))
					continue;

				psbHtml[i] = m_sbHtml;
			}

			m_pServer->Close();
			delete m_pServer;
			m_pServer = NULL;

//			for (i = 0; i < 14; i ++) {
			for (i = 0; i < 12; i ++) {
				m_sbHtml = psbHtml[i];

				if (m_sbHtml.IsEmpty())
					continue;
				if ((nPtr0 = m_sbHtml.Find("騰落率")) == -1)
					goto CleanUp1;
				HtmlTokenizer.SetHtml(m_sbHtml);
				for (j = 0; j < 20; j ++) {
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<tr ", nPtr0 + 1)) == -1)
						break;
					for (k = 0; k < 2; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 3; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp1;
					strCode = HtmlTokenizer.m_strTag;
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
						goto CleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp1;
					strName = StrConvHalfWidth(HtmlTokenizer.m_strTag);
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					for (k = 0; k < 3; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp1;
					strPrice = HtmlTokenizer.m_strTag;
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					for (k = 0; k < 2; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 3; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp1;
					strPreEndPriceDiff = HtmlTokenizer.m_strTag;
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;
					for (k = 0; k < 2; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if (! HtmlTokenizer.HtmlTok())
							goto CleanUp1;
					strTradeCount = HtmlTokenizer.m_strTag;
					nPtr0 = HtmlTokenizer.m_nHtmlPtr;

					if (m_pMstiCodeInfo->Lookup(strCode, InfoWork)) {
						FunashiWork.strCode = strCode;
						FunashiWork.lPrice = atol(strPrice);
						FunashiWork.lTradeCount = (long)(atof(strTradeCount) * 1000);
						FunashiWork.lPreEndPrice = InfoWork.lPreEndPrice;
						FunashiWork.lPreEndTradeCount = InfoWork.lPreEndTradeCount;
						FunashiWork.lDiff = GetDiff(InfoWork.lPreEndPrice + 1L);
						FunashiWork.lStopDiff = GetStopDiff(InfoWork.lPreEndPrice);

						Sfa.Add(FunashiWork);
					}
				}
			}

			if(FAILED(::CoInitialize(NULL)))
				goto CleanUp1;
			bCoInitialize = TRUE;

			TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
			pConnection->Open ((LPCTSTR)("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_strDBFPath), pszEmpty, pszEmpty, adConnectUnspecified);

			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));

			pSa = SafeArrayCreateVector(VT_VARIANT, 0, 1);
			if (!pSa) _com_issue_error(E_OUTOFMEMORY);

			vtKeyValues.vt = VT_ARRAY | VT_VARIANT;
			vtKeyValues.parray = pSa;

			ix = 0;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtCur)));

			pRst->Open (TBL_FUNASHIDATETIME, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst->Index = pszPrimaryKey;
			pRst->Seek(vtKeyValues, adSeekBeforeEQ);
			if (pRst->EndOfFile)
				goto CleanUp1;
			DtLast = (double)pRst->Fields->Item[FLD_FD_DATETIME]->Value;
			pRst->Close();

		   TESTHR(SafeArrayDestroy(pSa));

			pSa = SafeArrayCreateVector(VT_VARIANT, 0, 2);
			if (!pSa) _com_issue_error(E_OUTOFMEMORY);

			vtKeyValues.parray = pSa;

			DtLast.SetDate(DtLast.GetYear(), DtLast.GetMonth(), DtLast.GetDay());
			ix = 0;
			TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(DtLast)));

			ix = 1;

			pRst->Open (TBL_HIASHI, _variant_t((IDispatch *) pConnection, true), adOpenForwardOnly, adLockReadOnly, adCmdTableDirect);
			pRst->Index = pszPrimaryKey;

			for (i = 0, imax = Sfa.GetSize(); i < imax; i ++) {
				TESTHR(SafeArrayPutElement(pSa, &ix, &_variant_t(Sfa[i].strCode)));
				pRst->Seek(vtKeyValues, adSeekFirstEQ);

				if (pRst->EndOfFile) {
					Sfa[i].lStartPrice = Sfa[i].lHighPrice = Sfa[i].lLowPrice = 0L;

					Sfa[i].lDiffHigh = GetDiff(Sfa[i].lPreEndPrice);
					Sfa[i].lDiffLow = GetDiff(Sfa[i].lPreEndPrice + 1L);
				} else {
					vt = pRst->Fields->Item[FLD_HI_STARTPRICE]->Value;
					Sfa[i].lStartPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					vt = pRst->Fields->Item[FLD_HI_HIGHPRICE]->Value;
					Sfa[i].lHighPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					vt = pRst->Fields->Item[FLD_HI_LOWPRICE]->Value;
					Sfa[i].lLowPrice = vt.vt == VT_NULL ? 0L : (long)vt;

					Sfa[i].lDiffHigh = GetDiff(Sfa[i].lHighPrice);
					Sfa[i].lDiffLow = GetDiff(Sfa[i].lLowPrice + 1L);
				}
			}
			pRst->Close();

			::CoUninitialize();
			bCoInitialize = FALSE;

			for (i = 0, imax = Sfa.GetSize(); i < imax; i ++)
				if (m_pMstiCodeInfo->Lookup(Sfa[i].strCode, InfoWork))
					Sfa[i].sUnit = InfoWork.sUnit;
				else
					Sfa[i].sUnit = 1;

			if (! m_bMentenance2) {
				if (! AfxParseURL(m_sbCosmoQuoteUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
					DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoQuoteUrl);
					goto CleanUp1;
				}

				m_pServer = m_pSession->GetHttpConnection(m_strServerName, m_nPort);

				for (i = 0, imax = Sfa.GetSize(); i < imax; i ++) {
					if (Sfa[i].lStartPrice == 0L  ||  Sfa[i].lHighPrice == 0L  ||  Sfa[i].lLowPrice == 0L) {
						SaCode.Add(Sfa[i].strCode);
						UiaIndex.Add(i);
					}
					if (SaCode.GetSize() == 20  ||  i == imax - 1  &&  SaCode.GetSize()) {
						strReqCode.Empty();
						for (j = 0, jmax = SaCode.GetSize(); j < jmax; j ++) {
							strCode = SaCode[j];
							strSijo = strCode.Mid(5);
							if (strSijo == "JQ")
								strSijo = "J";
							else if (strSijo == "NG")
								strSijo = "NJ";
							if (j)
								strReqCode += '*';
							strReqCode += strCode.Left(4) + "%23" + strSijo + "%241";
						}
						m_strObject.Format(OBJ_COSMOQUOTE1, strReqCode);
						if (DlHtml(CHttpConnection::HTTP_VERB_GET))
							break;

						if ((nPtr0 = m_sbHtml.Find("騰落率")) == -1)
							goto CleanUp1;
						HtmlTokenizer.SetHtml(m_sbHtml);
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (j = 0; ; j ++) {
							lStartPrice = lHighPrice = lLowPrice = 0L;
							if ((nPtr0 = StrFindNoCase(m_sbHtml, "<tr>", nPtr0 + 1)) == -1)
								break;
							if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 4)) == -1)
								goto CleanUp1;
							HtmlTokenizer.m_nHtmlPtr = nPtr0;
							for (k = 0; k < 3; k ++)
								if (HtmlTokenizer.HtmlTok() == 0)
									goto CleanUp1;
							strCode = HtmlTokenizer.m_strTag;
							nPtr0 = HtmlTokenizer.m_nHtmlPtr;
							if (strCode.IsEmpty())
								continue;
							for (k = 0; k < 2; k ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
									goto CleanUp1;
							HtmlTokenizer.m_nHtmlPtr = nPtr0;
							for (k = 0; k < 2; k ++)
								if (HtmlTokenizer.HtmlTok() == 0)
									goto CleanUp1;
							strSijo = HtmlTokenizer.m_strTag;
							if (strSijo == "東証")
								strSijo = 'T';
							else if (strSijo == "大証")
								strSijo = 'O';
							else if (strSijo == "ＨＣ")
								strSijo = "NG";
							else if (strSijo == "ＪＱ")
								strSijo = "JQ";
							else if (strSijo == "名証")
								strSijo = 'M';
							strCode += '/' + strSijo;
							nPtr0 = HtmlTokenizer.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
								goto CleanUp1;
							HtmlTokenizer.m_nHtmlPtr = nPtr0;
							for (k = 0; k < 2; k ++)
								if (HtmlTokenizer.HtmlTok() == 0)
									goto CleanUp1;
							sbTag = HtmlTokenizer.m_strTag;
							sbTag.Replace(",", pszEmpty);
							lPrice = atol(sbTag);
							nPtr0 = HtmlTokenizer.m_nHtmlPtr;
							if (lPrice) {
								for (k = 0; k < 2; k ++)
									if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
										goto CleanUp1;
								for (k = 0; k < 2; k ++)
									if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
										goto CleanUp1;
								HtmlTokenizer.m_nHtmlPtr = nPtr0;
								for (k = 0; k < 2; k ++)
									if (HtmlTokenizer.HtmlTok() == 0)
										goto CleanUp1;
								sbTag = HtmlTokenizer.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lStartPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
									goto CleanUp1;
								HtmlTokenizer.m_nHtmlPtr = nPtr0;
								for (k = 0; k < 2; k ++)
									if (HtmlTokenizer.HtmlTok() == 0)
										goto CleanUp1;
								sbTag = HtmlTokenizer.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lHighPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
									goto CleanUp1;
								HtmlTokenizer.m_nHtmlPtr = nPtr0;
								for (k = 0; k < 2; k ++)
									if (HtmlTokenizer.HtmlTok() == 0)
										goto CleanUp1;
								sbTag = HtmlTokenizer.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lLowPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
									goto CleanUp1;
								HtmlTokenizer.m_nHtmlPtr = nPtr0;
							}

							if (SaCode[j] == strCode) {
								k = UiaIndex[j];
								Sfa[k].lStartPrice = lStartPrice;
								Sfa[k].lHighPrice = lHighPrice;
								Sfa[k].lLowPrice = lLowPrice;

								Sfa[k].lDiffHigh = GetDiff(lHighPrice);
								Sfa[k].lDiffLow = GetDiff(lLowPrice + 1L);
							}
						}

						SaCode.RemoveAll();
						UiaIndex.RemoveAll();
					}
				}
			}

			switch (m_nMode) {
			case 9:
				Sfa.Sort(CSortableFunashiArray::Compare2);
				break;
			case 10:
				Sfa.Sort(CSortableFunashiArray::Compare3);
				break;
			case 11:
				Sfa.Sort(CSortableFunashiArray::Compare4);
				break;
			case 12:
				Sfa.Sort(CSortableFunashiArray::Compare5);
				break;
			case 13:
				Sfa.Sort(CSortableFunashiArray::Compare6);
				break;
			case 14:
				Sfa.Sort(CSortableFunashiArray::Compare7);
				break;
			case 15:
				Sfa.Sort(CSortableFunashiArray::Compare8);
				break;
			case 16:
				Sfa.Sort(CSortableFunashiArray::Compare9);
				break;
			default:
				Sfa.Sort(CSortableFunashiArray::Compare10);
			}

			for (i = 0, imax = Sfa.GetSize(); i < imax; i ++) {
				strCode = Sfa[i].strCode;
				if (m_pMstiCodeInfo->Lookup(strCode, InfoWork)) {
					if (! (lPreEndPrice = Sfa[i].lPreEndPrice))
						lPreEndPrice = Sfa[i].lStartPrice;
					strSijo = strCode.Mid(5);
					strSijoName = InfoWork.strSijo;
					strCodeEx = strCode;
					if (strSijo == "T") {
						if (strSijoName.Left(10) == "東証ﾏｻﾞｰｽﾞ")
							strCodeEx += 'M';
						else if (strSijoName.Left(8) == "東証２部")
							strCodeEx += '2';
					} else if (strSijo == "O")
						if (strSijoName.Left(8) == "大証２部")
							strCodeEx += '2';
					lPrice = Sfa[i].lPrice;
					lDiff = GetDiff(lPreEndPrice + 1L);
					switch (lDiff) {
					case 5L:
					case 50L:
					case 500L:
					case 5000L:
					case 50000L:
						lDiffPrice = lPrice / (lDiff / 5);
						break;
					default:
						lDiffPrice = lPrice / lDiff;
					}
					strDiffPrice = LToA(lDiffPrice);
					strName = StrConvHalfWidth(InfoWork.strName).Left(10 - 1 - strDiffPrice.GetLength());
					lStopDiffRatio = (lPrice - lPreEndPrice) * 100 / GetStopDiff(lPreEndPrice);
					if (lStopDiffRatio <= -100)
						strStopDiffRatio = "-00";
					else
						strStopDiffRatio = LToA(lStopDiffRatio);
					switch (lDiff) {
					case 5L:
					case 50L:
					case 500L:
					case 5000L:
					case 50000L:
						lTradeCount1000 = Sfa[i].lTradeCount * (lDiff * 2) / 1000L;
						break;
					default:
						lTradeCount1000 = Sfa[i].lTradeCount * lDiff / 1000L;
					}
					m_SaList.Add(
						StrFormat(
							"%s %s%s %s %s %s",
							(strCodeEx + ' ').Left(7),
							strName,
							CString(' ', 10 - strName.GetLength() - 1 - strDiffPrice.GetLength()),
							strDiffPrice,
							("  " + strStopDiffRatio).Right(3),
							lTradeCount1000 < 10000L ? ("   " + LToA(lTradeCount1000)).Right(4) : "9999"
						)
					);
					m_SaCode.Add(strCode);
					m_DwaTradeCount1000.Add(lTradeCount1000);
					m_DwaDiffPrice.Add(lDiffPrice);
					if (m_nMode == 10  ||  m_nMode == 12) {
						lHighPrice = Sfa[i].lHighPrice ? Sfa[i].lHighPrice : lPreEndPrice;
						m_DwaLowDiffPrice.Add((lPrice - lHighPrice) / GetDiff(lHighPrice) / GetTick(lHighPrice, InfoWork.sUnit));
					} else {
						lLowPrice = Sfa[i].lLowPrice ? Sfa[i].lLowPrice : lPreEndPrice;
						m_DwaLowDiffPrice.Add((lPrice - lLowPrice) / GetDiff(lLowPrice + 1L) / GetTick(lLowPrice, InfoWork.sUnit));
					}
				}
			}
		}
		catch (_com_error &e) {
			ErrorPtr  pErr = NULL;

			for (long i = 0, imax = pConnection->Errors->Count; i < imax; i ++) {
				pErr = pConnection->Errors->GetItem(i);
				DispErrorLog("ADO ランキング表示エラー: %s\n", pErr->Description);
			}
			DispErrorLog("COM ランキング表示エラー: %s, %s\n", e.ErrorMessage(), e.Description());
		}
		catch (CException* pEx) {
			DispErrorLog("ランキング表示エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

CleanUp1:
		if (bCoInitialize)
			::CoUninitialize();
		if (m_pServer) {
			m_pServer->Close();
			delete m_pServer;
		}
		if (pSession) {
			pSession->Close();
			delete pSession;
		}
	} else {
		m_pServer = NULL;

		try {
			int i;
			int j;
			int k;
			int l;
			CString strObjRank0;
			CString strObjRank1;
			int nPtr0;
			CHtmlTokenizer HtmlTokenizer;
			CString strCode;
			CString strSijo;
			CString strName;
			CString strSijoName;
			CString strPrice;
			CString strPreEndPriceDiff;
			CString strTime;
			char chTimeMin;
			CString strTimeSS;
			Info InfoWork;
			long lPrice;
			long lPreEndPrice;
			long lDiff;
			long lDiffPrice;
			CString strDiffPrice;
			BOOL bBreak;
			CStringArray SaList;
			CString strCurPrice;
			CString strUpCount;
			void* pVoid;

			if (! AfxParseURL(m_sbCosmoQuoteUrl, m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
				DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoQuoteUrl);
				goto CleanUp2;
			}

			m_pServer = m_pSession->GetHttpConnection(m_strServerName, m_nPort);

			strObjRank0 = OBJ_RANK13;
			strObjRank1 = OBJ_RANK14;

			for (l = 0; l < 4; l ++) {
				strTimeSS.Empty();
				bBreak = FALSE;
				for (i = 0; ; i ++) {
					if (i == 0)
						switch (l) {
						case 0:
							m_strObject.Format(strObjRank0, "0019");
							break;
						case 1:
							m_strObject.Format(strObjRank0, "0017");
							break;
						case 2:
							m_strObject.Format(strObjRank0, "0006");
							break;
						default:
							m_strObject.Format(strObjRank0, "0001");
						}
					else
						switch (l) {
						case 0:
							m_strObject.Format(strObjRank1, "0019", i + 1);
							break;
						case 1:
							m_strObject.Format(strObjRank1, "0017", i + 1);
							break;
						case 2:
							m_strObject.Format(strObjRank1, "0006", i + 1);
							break;
						default:
							m_strObject.Format(strObjRank1, "0001", i + 1);
						}
					if (DlHtml(CHttpConnection::HTTP_VERB_GET))
						break;
					m_sbHtml.Replace("\r", pszEmpty);

					if ((nPtr0 = m_sbHtml.Find("<!-- 買特別気配表 end -->")) == -1)
						goto CleanUp2;
					m_sbHtml.Delete(nPtr0, m_sbHtml.GetLength());

					if ((nPtr0 = m_sbHtml.Find("前日比率")) == -1)
						goto CleanUp2;
					HtmlTokenizer.SetHtml(m_sbHtml);
					for (j = 0; ; j ++) {
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<tr>", nPtr0 + 1)) == -1)
							break;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 3; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strCode = HtmlTokenizer.m_strTag;
						switch (l) {
						case 0:
							strCode += "/NG";
							break;
						case 1:
							strCode += "/JQ";
							break;
						case 2:
							strCode += "/O";
							break;
						default:
							strCode += "/T";
						}
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 3; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strName = StrConvHalfWidth(HtmlTokenizer.m_strTag);
						if (l == 3)
							strName.Replace("M-", pszEmpty);
						strName.Replace(" ", pszEmpty);
						strName.Replace("&amp;", "&");
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
								goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strPrice = HtmlTokenizer.m_strTag;
						strPrice.Replace(",", pszEmpty);
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strTime = HtmlTokenizer.m_strTag;
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strCurPrice = HtmlTokenizer.m_strTag;
						if (strCurPrice[0] == '<')
							strCurPrice.Empty();
						strCurPrice.Replace(",", pszEmpty);
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtml, "<td ", nPtr0 + 1)) == -1)
							goto CleanUp2;
						HtmlTokenizer.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (! HtmlTokenizer.HtmlTok())
								goto CleanUp2;
						strPreEndPriceDiff = HtmlTokenizer.m_strTag;
						if (strPreEndPriceDiff[0] == '<')
							strPreEndPriceDiff.Empty();
						strPreEndPriceDiff.Replace(",", pszEmpty);
						nPtr0 = HtmlTokenizer.m_nHtmlPtr;

						if (strTimeSS.IsEmpty()) {
							chTimeMin = strTime[4];
							if (chTimeMin == '0'  ||  chTimeMin == '5')
								strTimeSS = strTime;
//							else
//								continue;
						} else
							if (strTime != strTimeSS) {
								bBreak = TRUE;
								break;
							}
						if (m_pMstiCodeInfo->Lookup(strCode, InfoWork)) {
							lPrice = atol(strPrice);
							lPreEndPrice = lPrice - atol(strPreEndPriceDiff);

							lDiff = GetDiff(lPreEndPrice + 1L);
							switch (lDiff) {
							case 5L:
							case 50L:
							case 500L:
							case 5000L:
							case 50000L:
								lDiffPrice = lPrice / (lDiff / 5);
								break;
							default:
								lDiffPrice = lPrice / lDiff;
							}
							strDiffPrice = LToA(lDiffPrice);
							strSijoName = InfoWork.strSijo;
							if (strSijo == "T") {
								if (strSijoName.Left(10) == "東証ﾏｻﾞｰｽﾞ")
									strCode += 'M';
								else if (strSijoName.Left(8) == "東証２部")
									strCode += '2';
							} else if (strSijo == "O")
								if (strSijoName.Left(8) == "大証２部")
									strCode += '2';
							strName = strName.Left(13 - 1 - strDiffPrice.GetLength());
							strUpCount = strCurPrice.GetLength() ? LToA((lPrice - atol(strCurPrice)) / GetDiff(lPrice)) : pszEmpty;
							if (m_pMstpSelCode->Lookup(strCode, pVoid))
								m_SaList.Add((strCode + "  ").Left(8) + strName + CString(' ', 13 - strName.GetLength() - strDiffPrice.GetLength()) + strDiffPrice + ("   " + strUpCount).Right(3) + ' ' + strTime);
							else
								SaList.Add((strCode + "  ").Left(8) + strName + CString(' ', 13 - strName.GetLength() - strDiffPrice.GetLength()) + strDiffPrice + ("   " + strUpCount).Right(3) + ' ' + strTime);
						}
					}
					if (bBreak  ||  m_sbHtml.Find(">次<") == -1)
						break;
				}
			}
			m_SaList.Append(SaList);
		}
		catch (CException* pEx) {
			DispErrorLog("ランキング表示エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

CleanUp2:
		if (m_pServer) {
			m_pServer->Close();
			delete m_pServer;
		}
	}

	PostQuitMessage(0);

	return TRUE;
}

int CDispRankingThread::ExitInstance()
{
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDispRankingThread, CWinThread)
	//{{AFX_MSG_MAP(CDispRankingThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispRankingThread メッセージ ハンドラ

int CDispRankingThread::DlHtml(int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
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

void CDispRankingThread::DispErrorLog(LPCTSTR lpszFormat, ...)
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
