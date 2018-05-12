#if !defined(COMMON_H__INCLUDED_)
#define COMMON_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

extern _TCHAR pszEmpty[];

CString StrQ(LPCTSTR lpsz, const _TCHAR chQ = _T('"'));
BOOL IsStrQTrim(const CString& str);
CString StrQTrim(const CString& strStr);
CString GetDPathFromFPath(LPCTSTR lpszFPath);
CString GetFNameFromFPath(LPCTSTR lpszFPath);
int ReStrFile(LPCTSTR lpszFPath, CString& str);
int WrStrFile(LPCTSTR lpszFPath, const CString& strStr);
int WaitExeFPath(LPCTSTR lpszExeFPath, const OSVERSIONINFO& osvi);
CString GetLastErrorMessage(DWORD dwLastError = NULL);
CString GetExceptionErrorMessage(CException* pEx);

extern int nPumpWaitingMessages;

void PumpWaitingMessages();

void SetAbsoluteForegroundWindow(HWND hWnd);

#if !defined(COMMON_H__NOSHFOLDER)
CString GetShFolderPath(int nFolder);

CString IToA(int n);
CString LToA(long l);
int StrFindNoCase(const CString& strStr, LPCTSTR lpszTarget, int nIndex = 0);
int StrFindOneOf(LPCTSTR lpszStr, LPCTSTR lpszCharSet, int nStart);
int StrFindNotOf(const CString& strStr, LPCTSTR lpszCharSet, int nStart = 0);
int StrReverseFindEx(const CString& strStr, LPCTSTR lpszTarget, bool bNoCase = false);
int StrReverseFindEx(const CString& strStr, LPCTSTR lpszTarget, int nIndex, bool bNoCase = false);
CString StrFormat(LPCTSTR lpszFormat, ...);
CString StrConvHalfWidth(LPCTSTR lpszStr);
COleDateTime FixDateTime(const COleDateTime& dt);
int ForceDir(const CString& strDir);
void ParseUrlSearch(LPCTSTR lpszUrl, CMapStringToString& MstsSearch);
CString GetLongPath(LPCTSTR lpszPath);
CString GetShellExecuteErrorText(HINSTANCE hInstance);
CString GetHttpStatusText(DWORD dwStatusCode);
DWORD GetAllocationSize(DWORD dwSize);
__int64 GetDiskFreeSpaceInt64(LPCTSTR pszDrive);

int CALLBACK
BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData);
CString FolderDialog(HWND hWnd);

/////////////////////////////////////////////////////////////////////////////
// CDblArray : double 配列クラス

typedef CArray<double, const double&> CDblArray;

/////////////////////////////////////////////////////////////////////////////
// COleDateTimeArray : COleDateTime 配列クラス

typedef CArray<COleDateTime, const COleDateTime&> COleDateTimeArray;

/////////////////////////////////////////////////////////////////////////////
// CMapOleDateTimeToPtr : COleDateTime マップクラス

typedef CMap<COleDateTime, const COleDateTime&, void *, void*&> CMapOleDateTimeToPtr;

/////////////////////////////////////////////////////////////////////////////
// CStringTokenizer

class CStringTokenizer
{
public:
	CStringTokenizer();
	CStringTokenizer(const CString& strStr, LPCTSTR lpszSep);

	void SetStrSep(const CString& strStr, LPCTSTR lpszSep);
	BOOL StrTok(LPCTSTR lpszSep = NULL);

	int m_nStrPtr;
	CString m_strTok;

protected:
	CString m_strStr;
	int m_nStrLen;
	CString m_strSep;
};

#endif // !defined(COMMON_H__NOSHFOLDER)

#endif // !defined(COMMON_H__INCLUDED_)
