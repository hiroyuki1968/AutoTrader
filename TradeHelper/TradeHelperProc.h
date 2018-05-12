#if !defined(TRADEHELPERPROC_H__INCLUDED_)
#define TRADEHELPERPROC_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <afxinet.h>
#include "../StringBuffer.h"
#include "../AutoTraderProc.h"

typedef struct {
	CString strName;
	CString strSijo;
	short sUnit;
	long lPreEndPrice;
	long lPreEndTradeCount;
} Info;

typedef struct {
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbOptional;
} DlParm;

typedef struct {
	long plTradeCount1000[5];
	long lCheckedTradeCount1000;
	long lDiffPrice;
	long lCheckedDiffPrice;
} RankingAttr;

typedef struct {
	CString strCode;
	long lStartPrice;
	long lHighPrice;
	long lLowPrice;
	long lPrice;
	long lTradeCount;
	long lPreEndPrice;
	long lPreEndTradeCount;
	long lDiff;
	long lDiffHigh;
	long lDiffLow;
	long lStopDiff;
	short sUnit;
} Funashi;

/////////////////////////////////////////////////////////////////////////////
// CDlParmArray : DlParm 配列クラス

typedef CArray<DlParm, const DlParm&> CDlParmArray;

/////////////////////////////////////////////////////////////////////////////
// CFunashiArray : Funashi 配列クラス

typedef CArray<Funashi, const Funashi&> CFunashiArray;

/////////////////////////////////////////////////////////////////////////////
// CStringToInfoMap : CString Info マップクラス

typedef CMap<CString, LPCTSTR, Info, const Info&> CStringToInfoMap;

/////////////////////////////////////////////////////////////////////////////
// CStringToRankingAttrMap : CString RankingAttr マップクラス

typedef CMap<CString, LPCTSTR, RankingAttr, const RankingAttr&> CStringToRankingAttrMap;

/////////////////////////////////////////////////////////////////////////////
// CSortableFunashiArray : Funashi ソート配列クラス

typedef int (__cdecl *GENERICCOMPAREFN)(const void * elem1, const void * elem2);
typedef int (__cdecl *FUNASHICOMPAREFN)(const Funashi * elem1, const Funashi * elem2);

class CSortableFunashiArray : public CFunashiArray
{
public:
	void Sort(FUNASHICOMPAREFN pfnCompare = Compare0);
	static int __cdecl Compare0(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare1(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare2(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare3(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare4(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare5(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare6(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare7(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare8(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare9(const Funashi * pFunashi1, const Funashi * pFunashi2);
	static int __cdecl Compare10(const Funashi * pFunashi1, const Funashi * pFunashi2);
};

/////////////////////////////////////////////////////////////////////////////

//extern const char* pszStreamerWndName;
//extern const char* pszStreamerClassName;

int GetSuryo(long lPrice, short sUnit);
int GetTick(long lPrice, short sUnit);
int GetKehai(const CStringBuffer& sbKehaiHtml, CKehai0& KehaiWork);

UINT StockAveBeepThreadProc(LPVOID pParam);

#endif // !defined(TRADEHELPERPROC_H__INCLUDED_)
