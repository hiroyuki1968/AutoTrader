#if !defined(AUTOTRADERPROC_H__INCLUDED_)
#define AUTOTRADERPROC_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "StringBuffer.h"

typedef struct {
	CString strMainCode;
	CString strName;
	CString strSijoName;
	short sUnit;
	long lHighPrice;
	long lLowPrice;
	long lPreEndPrice;
	long lTradeCount;
	CString strMainCodeEx;
	int nNewsCount;
} MainCodeName;

/////////////////////////////////////////////////////////////////////////////
// CKehai : Kehai クラス

class CKehai0
{
public:
	CKehai0();
	Empty();
	long m_plKehaiPrice[10];
	long m_plKehaiCount[10];
};

class CKehai1
{
public:
	CKehai1();
	Empty();
	long m_plKehaiPrice[2];
	long m_plKehaiCount[2];
};

/////////////////////////////////////////////////////////////////////////////
// CFunashi : Funashi クラス

class CFunashi0
{
public:
	CFunashi0();
	Empty();
	int m_nType;
	COleDateTime m_DtDateTime;
	long m_lPrice;
	long m_lTradeCount;
	double m_dVwap;
	CKehai0 m_Kehai;
};

class CFunashi1
{
public:
	CFunashi1();
	Empty();
	int m_nType;
	COleDateTime m_DtDateTime;
	long m_lPrice;
	long m_lTradeCount;
};

class CFunashi2
{
public:
	CFunashi2();
	Empty();
	int m_nType;
	COleDateTime m_DtDateTime;
	long m_lPrice;
	CKehai1 m_Kehai;
};

/////////////////////////////////////////////////////////////////////////////
// CKehai0Array : Kehai 配列クラス

typedef CArray<CKehai0, const CKehai0&> CKehai0Array;

/////////////////////////////////////////////////////////////////////////////
// CStringToMainCodeNameMap : CString MainCodeName マップクラス

typedef CMap<CString, LPCTSTR, MainCodeName, const MainCodeName&> CMapStringToMainCodeName;

/////////////////////////////////////////////////////////////////////////////
// CStringToCFunashi0Map : CString CFunashi0 マップクラス

typedef CMap<CString, LPCTSTR, CFunashi0, const CFunashi0&> CMapStringToCFunashi0;

/////////////////////////////////////////////////////////////////////////////

extern const _TCHAR* ppszUrlLogin[];
extern const _TCHAR* ppszObjLogin[];
extern const _TCHAR* ppszOptLogin[];

extern const _TCHAR* pszX;

extern const _TCHAR* pszPrimaryKey;
extern const _TCHAR* pszSecondaryKey;

extern const _TCHAR* ppszPfKey[];

extern COleDateTimeSpan DtsCurrentTime;

COleDateTime GetCurrentTimeEx();
int RegCreateKeyAutoTrader(HKEY& hKey);
int RegCloseKeyAutoTrader(const HKEY hKey);
CStringBuffer ConvVer(LPCTSTR lpszVer);
long GetStopDiff(long lPrice);
long GetDiff(long lPrice);

#endif // !defined(AUTOTRADERPROC_H__INCLUDED_)
