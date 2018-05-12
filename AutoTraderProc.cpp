#include "stdafx.h"
#include "AutoTraderProc.h"

#include "AutoTraderDef.h"
#include "Common.h"

const _TCHAR* ppszUrlLogin[] = {URL_LOGIN0, URL_LOGIN1, NULL};
const _TCHAR* ppszObjLogin[] = {OBJ_LOGIN0, OBJ_LOGIN1};
const _TCHAR* ppszOptLogin[] = {OPT_LOGIN0, OPT_LOGIN1};

const _TCHAR* pszX = "x";

const _TCHAR* pszPrimaryKey = "PrimaryKey";
const _TCHAR* pszSecondaryKey = "SecondaryKey";

const _TCHAR* ppszPfKey[] = {
	PF_KEY_AUTOTRADERUPDATETYPE,
	PF_KEY_AUTOTRADERUPDATEDATE,

	NULL
};

COleDateTimeSpan DtsCurrentTime(0, 0, 0, 0);

COleDateTime GetCurrentTimeEx()
{
	return COleDateTime::GetCurrentTime() - DtsCurrentTime;
}

int RegCreateKeyAutoTrader(HKEY& hKey)
{
	LONG nRegFunc;
	if ((nRegFunc = RegCreateKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL)) != ERROR_SUCCESS) {
		AfxMessageBox(_T("レジストリサブキー作成エラー: ") + GetLastErrorMessage(nRegFunc), MB_ICONSTOP);
		return -1;
	}

	return 0;
}

int RegCloseKeyAutoTrader(const HKEY hKey)
{
	LONG nRegFunc;
	if ((nRegFunc = RegCloseKey(hKey)) != ERROR_SUCCESS) {
		AfxMessageBox(_T("レジストリクローズエラー: ") + GetLastErrorMessage(nRegFunc), MB_ICONSTOP);
		return -1;
	}

	return 0;
}

CStringBuffer ConvVer(LPCTSTR lpszVer)
{
	CStringBuffer strRv;

	CStringBuffer strVer = lpszVer;

	int nMajor = _ttoi(strVer.Left(2));
	int nMinor = _ttoi(strVer.Mid(2, 2));
	int nRev = _ttoi(strVer.Mid(4));

	if (nRev == 0)
		strRv.Format("%d.%d", nMajor, nMinor);
	else if (nRev >= 51)
		strRv.Format("%d.%d.%dβ", nMajor, nMinor, nRev);
	else
		strRv.Format("%d.%d.%dα", nMajor, nMinor, nRev);

	return strRv;
}

long GetStopDiff(long lPrice)
{
	long lRv;

	if (lPrice < 100L)
		lRv = 30L;
	else if (lPrice < 200L)
		lRv = 50L;
	else if (lPrice < 500L)
		lRv = 80L;
	else if (lPrice < 700L)
		lRv = 100L;
	else if (lPrice < 1000L)
		lRv = 150L;
	else if (lPrice < 1500L)
		lRv = 300L;
	else if (lPrice < 2000L)
		lRv = 400L;
	else if (lPrice < 3000L)
		lRv = 500L;
	else if (lPrice < 5000L)
		lRv = 700L;
	else if (lPrice < 7000L)
		lRv = 1000L;
	else if (lPrice < 10000L)
		lRv = 1500L;
	else if (lPrice < 15000L)
		lRv = 3000L;
	else if (lPrice < 20000L)
		lRv = 4000L;
	else if (lPrice < 30000L)
		lRv = 5000L;
	else if (lPrice < 50000L)
		lRv = 7000L;
	else if (lPrice < 70000L)
		lRv = 10000L;
	else if (lPrice < 100000L)
		lRv = 15000L;
	else if (lPrice < 150000L)
		lRv = 30000L;
	else if (lPrice < 200000L)
		lRv = 40000L;
	else if (lPrice < 300000L)
		lRv = 50000L;
	else if (lPrice < 500000L)
		lRv = 70000L;
	else if (lPrice < 700000L)
		lRv = 100000L;
	else if (lPrice < 1000000L)
		lRv = 150000L;
	else if (lPrice < 1500000L)
		lRv = 300000L;
	else if (lPrice < 2000000L)
		lRv = 400000L;
	else if (lPrice < 3000000L)
		lRv = 500000L;
	else if (lPrice < 5000000L)
		lRv = 700000L;
	else if (lPrice < 7000000L)
		lRv = 1000000L;
	else if (lPrice < 10000000L)
		lRv = 1500000L;
	else if (lPrice < 15000000L)
		lRv = 3000000L;
	else if (lPrice < 20000000L)
		lRv = 4000000L;
	else if (lPrice < 30000000L)
		lRv = 5000000L;
	else if (lPrice < 50000000L)
		lRv = 7000000L;
	else
		lRv = 10000000L;

	return lRv;
}

long GetDiff(long lPrice)
{
	long lRv;

	if (lPrice <= 3000L)
		lRv = 1L;
	else if (lPrice <= 5000L)
		lRv = 5L;
	else if (lPrice <= 30000L)
		lRv = 10L;
	else if (lPrice <= 50000L)
		lRv = 50L;
	else if (lPrice <= 300000L)
		lRv = 100L;
	else if (lPrice <= 500000L)
		lRv = 500L;
	else if (lPrice <= 3000000L)
		lRv = 1000L;
	else if (lPrice <= 5000000L)
		lRv = 5000L;
	else if (lPrice <= 30000000L)
		lRv = 10000L;
	else if (lPrice <= 50000000L)
		lRv = 50000L;
	else
		lRv = 100000L;

	return lRv;
}

CKehai0::CKehai0()
{
	Empty();
}

CKehai0::Empty()
{
	ZeroMemory(this, sizeof(CKehai0));
}

CKehai1::CKehai1()
{
	Empty();
}

CKehai1::Empty()
{
	ZeroMemory(this, sizeof(CKehai1));
}

CFunashi0::CFunashi0()
{
	m_nType = 0;
	m_lPrice = m_lTradeCount = 0L;
	m_dVwap = 0.0;
}

CFunashi0::Empty()
{
	m_nType = 0;
	m_DtDateTime = COleDateTime();
	m_lPrice = m_lTradeCount = 0L;
	m_dVwap = 0.0;
}

CFunashi1::CFunashi1()
{
	m_nType = 1;
	m_lPrice = m_lTradeCount = 0L;
}

CFunashi1::Empty()
{
	m_nType = 1;
	m_DtDateTime = COleDateTime();
	m_lPrice = m_lTradeCount = 0L;
}

CFunashi2::CFunashi2()
{
	m_nType = 2;
	m_lPrice = 0L;
	m_Kehai.Empty();
}

CFunashi2::Empty()
{
	m_nType = 2;
	m_DtDateTime = COleDateTime();
	m_lPrice = 0L;
	m_Kehai.Empty();
}
