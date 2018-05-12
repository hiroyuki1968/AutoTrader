#include "stdafx.h"
#include "TradeHelperProc.h"

#include "../Common.h"
#include "../Html.h"
#include "TradeHelperDef.h"

int CSortableFunashiArray::Compare0(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l01 = pFunashi1->lLowPrice ? pFunashi1->lLowPrice : pFunashi1->lPreEndPrice;
	long l02 = pFunashi2->lLowPrice ? pFunashi2->lLowPrice : pFunashi2->lPreEndPrice;
	long l1 = (pFunashi1->lPrice - l01) / pFunashi1->lDiffLow;
	long l2 = (pFunashi2->lPrice - l02) / pFunashi2->lDiffLow;
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	}
	return l1 > l2 ? -1 : l1 < l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare1(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l01 = pFunashi1->lHighPrice ? pFunashi1->lHighPrice : pFunashi1->lPreEndPrice;
	long l02 = pFunashi2->lHighPrice ? pFunashi2->lHighPrice : pFunashi2->lPreEndPrice;
	long l1 = (pFunashi1->lPrice - l01) / pFunashi1->lDiffHigh;
	long l2 = (pFunashi2->lPrice - l02) / pFunashi2->lDiffHigh;
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	}
	return l1 < l2 ? -1 : l1 > l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare2(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l01 = pFunashi1->lLowPrice ? pFunashi1->lLowPrice : pFunashi1->lPreEndPrice;
	long l02 = pFunashi2->lLowPrice ? pFunashi2->lLowPrice : pFunashi2->lPreEndPrice;
	long l1 = (pFunashi1->lPrice - l01) / pFunashi1->lDiffLow / GetTick(l01, pFunashi1->sUnit);
	long l2 = (pFunashi2->lPrice - l02) / pFunashi2->lDiffLow / GetTick(l02, pFunashi2->sUnit);
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	}
	return l1 > l2 ? -1 : l1 < l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare3(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l01 = pFunashi1->lHighPrice ? pFunashi1->lHighPrice : pFunashi1->lPreEndPrice;
	long l02 = pFunashi2->lHighPrice ? pFunashi2->lHighPrice : pFunashi2->lPreEndPrice;
	long l1 = (pFunashi1->lPrice - l01) / pFunashi1->lDiffHigh / GetTick(l01, pFunashi1->sUnit);
	long l2 = (pFunashi2->lPrice - l02) / pFunashi2->lDiffHigh / GetTick(l02, pFunashi2->sUnit);
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	}
	return l1 < l2 ? -1 : l1 > l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare4(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
	long l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lLowPrice ? pFunashi1->lLowPrice : pFunashi1->lPreEndPrice)) / pFunashi1->lDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lLowPrice ? pFunashi2->lLowPrice : pFunashi2->lPreEndPrice)) / pFunashi2->lDiff;
	}
	return l1 > l2 ? -1 : l1 < l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare5(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l1 = (pFunashi1->lPrice - (pFunashi1->lPreEndPrice ? pFunashi1->lPreEndPrice : pFunashi1->lStartPrice)) * 100 / pFunashi1->lStopDiff;
	long l2 = (pFunashi2->lPrice - (pFunashi2->lPreEndPrice ? pFunashi2->lPreEndPrice : pFunashi2->lStartPrice)) * 100 / pFunashi2->lStopDiff;
	if (l1 == l2) {
		l1 = (pFunashi1->lPrice - (pFunashi1->lLowPrice ? pFunashi1->lLowPrice : pFunashi1->lPreEndPrice)) / pFunashi1->lDiff;
		l2 = (pFunashi2->lPrice - (pFunashi2->lLowPrice ? pFunashi2->lLowPrice : pFunashi2->lPreEndPrice)) / pFunashi2->lDiff;
	}
	return l1 < l2 ? -1 : l1 > l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare6(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	__int64 n1 = (__int64)pFunashi1->lTradeCount *  pFunashi1->lDiff;
	__int64 n2 = (__int64)pFunashi2->lTradeCount *  pFunashi2->lDiff;
	return n1 > n2 ? -1 : n1 < n2 ? 1 : 0;
}

int CSortableFunashiArray::Compare7(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	__int64 n1 = (__int64)pFunashi1->lPrice * pFunashi1->lTradeCount;
	__int64 n2 = (__int64)pFunashi2->lPrice * pFunashi2->lTradeCount;
	return n1 > n2 ? -1 : n1 < n2 ? 1 : 0;
}

int CSortableFunashiArray::Compare8(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	double d1 = (double)pFunashi1->lTradeCount / pFunashi1->lPreEndTradeCount;
	double d2 = (double)pFunashi2->lTradeCount / pFunashi2->lPreEndTradeCount;
	return d1 > d2 ? -1 : d1 < d2 ? 1 : 0;
}

int CSortableFunashiArray::Compare9(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l1 = pFunashi1->lPrice;
	long l2 = pFunashi2->lPrice;
	if (l1 == l2) {
		l1 = pFunashi1->lTradeCount;
		l2 = pFunashi2->lTradeCount;
	}
	return l1 > l2 ? -1 : l1 < l2 ? 1 : 0;
}

int CSortableFunashiArray::Compare10(const Funashi * pFunashi1, const Funashi * pFunashi2)
{
	ASSERT(pFunashi1);
	ASSERT(pFunashi2);
	long l1 = pFunashi1->lPrice;
	long l2 = pFunashi2->lPrice;
	if (l1 == l2) {
		l1 = pFunashi1->lTradeCount;
		l2 = pFunashi2->lTradeCount;
	}
	return l1 < l2 ? -1 : l1 > l2 ? 1 : 0;
}

void CSortableFunashiArray::Sort(FUNASHICOMPAREFN pfnCompare /*= CSortableFunashiArray::Compare */)
{
	Funashi * prgFunashi = GetData();
	qsort(prgFunashi,GetSize(),sizeof(Funashi),(GENERICCOMPAREFN)pfnCompare);
}

//const char* pszStreamerWndName = "https://ot3.qhit.net/?F=livedoor&Time=55&rf=N# - KAZAKA Streamer - Windows Internet Explorer";
//const char* pszStreamerClassName = "IEFrame";

int GetSuryo(long lPrice, short sUnit)
{
	return lPrice ? ZAN / (lPrice * sUnit) : 0;
}

int GetTick(long lPrice, short sUnit)
{
	int n0 = GetSuryo(lPrice, sUnit);
	int n1 = (n0 ? n0 : 1) * sUnit * GetDiff(lPrice + 1L);
	int n2 = 5000L / n1;

	if (5000L % n1)
		n2 ++;

	return n2 ? n2 : 1;
}

int GetKehai(const CStringBuffer& sbKehaiHtml, CKehai0& KehaiWork)
{
	int nRv = -1;

	int k;
	int l;
	BOOL bData;
	int nPtr0;
	int nPtr1;
	CHtmlTokenizer HtmlTokenizer;
	CStringBuffer sbTag;
	long lKehaiSpecial;

	bData = FALSE;

	// 東証、名証、大証、ヘラクレス
	if ((nPtr0 = sbKehaiHtml.Find("買数量")) == -1)
		goto DataCleanUp;
	if ((nPtr1 = sbKehaiHtml.Find("最良指値", nPtr0 + 6)) != -1)
		nPtr0 = nPtr1;
	HtmlTokenizer.SetHtml(sbKehaiHtml);
	for (k = 0; k < 5; k ++) {
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<tr>", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 4)) == -1)
			goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		lKehaiSpecial = sbTag == "特"  ||  sbTag == "連"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ||  sbTag == "停"  ||  sbTag == "レ"  ? -1 : 1;
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		sbTag.Replace(",", pszEmpty);
		KehaiWork.m_plKehaiCount[k] = atol(sbTag) * lKehaiSpecial;
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		sbTag.Replace(",", pszEmpty);
		KehaiWork.m_plKehaiPrice[k] = atol(sbTag);
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
	}
	for (k = 5; k < 10; k ++) {
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<tr>", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		for (l = 0; l < 3; l ++)
			if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 4)) == -1)
				goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		sbTag.Replace(",", pszEmpty);
		KehaiWork.m_plKehaiPrice[k] = atol(sbTag);
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		sbTag.Replace(",", pszEmpty);
		KehaiWork.m_plKehaiCount[k] = atol(sbTag);
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
		if ((nPtr0 = StrFindNoCase(sbKehaiHtml, "<td ", nPtr0 + 1)) == -1)
			goto DataCleanUp;
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (l = 0; l < 2; l ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				goto DataCleanUp;
		sbTag = HtmlTokenizer.m_strTag;
		lKehaiSpecial = sbTag == "特"  ||  sbTag == "連"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ||  sbTag == "停"  ||  sbTag == "レ"  ? -1 : 1;
		KehaiWork.m_plKehaiCount[k] *= lKehaiSpecial;
		nPtr0 = HtmlTokenizer.m_nHtmlPtr;
	}

	bData = TRUE;

DataCleanUp:
	if (! bData)
		goto CleanUp;


	nRv = 0;

CleanUp:

	return nRv;
}

UINT StockAveBeepThreadProc(LPVOID pParam)
{
	double* pdDiff = (double *)pParam;

	if (*pdDiff < -25.0) {
		Beep(1000, 10);
		Beep(900, 10);
		Beep(800, 10);
		Beep(700, 10);
		Beep(600, 10);
		Beep(500, 10);
		Beep(400, 10);
		Beep(300, 10);
		Beep(200, 10);
		Beep(100, 10);
	} else if (*pdDiff < -15.0) {
		Beep(400, 50);
		Beep(200, 50);
//	} else if (*pdDiff < -5.0)
//		Beep(400, 100);
	}
	else if (*pdDiff > 25.0) {
		Beep(3200, 10);
		Beep(3300, 10);
		Beep(3400, 10);
		Beep(3500, 10);
		Beep(3600, 10);
		Beep(3700, 10);
		Beep(3800, 10);
		Beep(3900, 10);
		Beep(4000, 10);
		Beep(4100, 10);
	} else if (*pdDiff > 15.0) {
		Beep(1600, 50);
		Beep(3200, 50);
//	} else if (*pdDiff > 5.0)
//		Beep(800, 100);
	}

	return 0;   // thread completed successfully
}
