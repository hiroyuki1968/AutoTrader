#if !defined(STRINGBUFFER_H__INCLUDED_)
#define STRINGBUFFER_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringBuffer : public CString
{
public:
// Constructors

	// constructs empty CString
	CStringBuffer();
	// from a single character
	CStringBuffer(TCHAR ch, int nRepeat = 1);
	// from an ANSI string (converts to TCHAR)
	CStringBuffer(LPCSTR lpsz);
	// from a UNICODE string (converts to TCHAR)
	CStringBuffer(LPCWSTR lpsz);
	// subset of characters from an ANSI string (converts to TCHAR)
	CStringBuffer(LPCSTR lpch, int nLength);
	// subset of characters from a UNICODE string (converts to TCHAR)
	CStringBuffer(LPCWSTR lpch, int nLength);
	// from unsigned characters
	CStringBuffer(const unsigned char* psz);

// Attributes & Operations

	// return single character at zero-based index
	TCHAR GetAt(int nIndex) const;
	// return single character at zero-based index
	TCHAR operator[](int nIndex) const;

	// delete nCount characters starting at zero-based index
	int Delete(int nIndex, int nCount = 1);

	int Update(int nIndex, int nCount, LPCTSTR pstr);

	// Access to string implementation buffer as "C" character array

	// get pointer to modifiable buffer at least as long as nMinBufLength
	LPTSTR GetBuffer(int nMinBufLength = 0);

	void SetBufferLength(int nNewLength);

// Implementation
protected:

	// implementation helpers
	void AllocBuffer(int nLen);

// No change function from AFX.H
public:
// Constructors

	// copy constructor
	CStringBuffer(const CString& stringSrc);

// Attributes & Operations

	// set a single character at zero-based index
	void SetAt(int nIndex, TCHAR ch);

	// overloaded assignment

	// ref-counted copy from another CString
	const CString& operator=(const CString& stringSrc);
	// set string content to single character
	const CString& operator=(TCHAR ch);
#ifdef _UNICODE
	const CString& operator=(char ch);
#endif
	// copy string content from ANSI string (converts to TCHAR)
	const CString& operator=(LPCSTR lpsz);
	// copy string content from UNICODE string (converts to TCHAR)
	const CString& operator=(LPCWSTR lpsz);
	// copy string content from unsigned chars
	const CString& operator=(const unsigned char* psz);

	// string concatenation

	// concatenate from another CString
	const CString& operator+=(const CString& string);

	// concatenate a single character
	const CString& operator+=(TCHAR ch);
#ifdef _UNICODE
	// concatenate an ANSI character after converting it to TCHAR
	const CString& operator+=(char ch);
#endif
	// concatenate a UNICODE character after converting it to TCHAR
	const CString& operator+=(LPCTSTR lpsz);

	friend CString AFXAPI operator+(const CStringBuffer& string1,
			const CStringBuffer& string2);
	friend CString AFXAPI operator+(const CStringBuffer& string1,
			const CString& string2);
	friend CString AFXAPI operator+(const CString& string1,
			const CStringBuffer& string2);
	friend CString AFXAPI operator+(const CStringBuffer& string, TCHAR ch);
	friend CString AFXAPI operator+(TCHAR ch, const CStringBuffer& string);
#ifdef _UNICODE
	friend CString AFXAPI operator+(const CStringBuffer& string, char ch);
	friend CString AFXAPI operator+(char ch, const CStringBuffer& string);
#endif
	friend CString AFXAPI operator+(const CStringBuffer& string, LPCTSTR lpsz);
	friend CString AFXAPI operator+(LPCTSTR lpsz, const CStringBuffer& string);

	// simple sub-string extraction

	// return nCount characters starting at zero-based nFirst
	CString Mid(int nFirst, int nCount) const;
	// return all characters starting at zero-based nFirst
	CString Mid(int nFirst) const;
	// return first nCount characters in string
	CString Left(int nCount) const;
	// return nCount characters from end of string
	CString Right(int nCount) const;

	//  characters from beginning that are also in passed string
	CString SpanIncluding(LPCTSTR lpszCharSet) const;
	// characters from beginning that are not also in passed string
	CString SpanExcluding(LPCTSTR lpszCharSet) const;

	// upper/lower/reverse conversion

	// NLS aware conversion to uppercase
	void MakeUpper();
	// NLS aware conversion to lowercase
	void MakeLower();
	// reverse string right-to-left
	void MakeReverse();

	// trimming whitespace (either side)

	// remove whitespace starting from right edge
	void TrimRight();
	// remove whitespace starting from left side
	void TrimLeft();

	// trimming anything (either side)

	// remove continuous occurrences of chTarget starting from right
	void TrimRight(TCHAR chTarget);
	// remove continuous occcurrences of characters in passed string,
	// starting from right
	void TrimRight(LPCTSTR lpszTargets);
	// remove continuous occurrences of chTarget starting from left
	void TrimLeft(TCHAR chTarget);
	// remove continuous occcurrences of characters in
	// passed string, starting from left
	void TrimLeft(LPCTSTR lpszTargets);

	// advanced manipulation

	// replace occurrences of chOld with chNew
	int Replace(TCHAR chOld, TCHAR chNew);
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
	int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew);
	// remove occurrences of chRemove
	int Remove(TCHAR chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, TCHAR ch);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, LPCTSTR pstr);

	// simple formatting

	// printf-like formatting using passed string
	void AFX_CDECL Format(LPCTSTR lpszFormat, ...);
	// printf-like formatting using referenced string resource
	void AFX_CDECL Format(UINT nFormatID, ...);
	// printf-like formatting using variable arguments parameter
	void FormatV(LPCTSTR lpszFormat, va_list argList);

	// formatting for localization (uses FormatMessage API)

	// format using FormatMessage API on passed string
	void AFX_CDECL FormatMessage(LPCTSTR lpszFormat, ...);
	// format using FormatMessage API on referenced string resource
	void AFX_CDECL FormatMessage(UINT nFormatID, ...);

#ifndef _UNICODE
	// ANSI <-> OEM support (convert string in place)

	// convert string from ANSI to OEM in-place
	void AnsiToOem();
	// convert string from OEM to ANSI in-place
	void OemToAnsi();
#endif

#ifndef _AFX_NO_BSTR_SUPPORT
	// OLE BSTR support (use for OLE automation)

	// return a BSTR initialized with this CString's data
	BSTR AllocSysString() const;
	// reallocates the passed BSTR, copies content of this CString to it
	BSTR SetSysString(BSTR* pbstr) const;
#endif

	// Access to string implementation buffer as "C" character array

	// get pointer to modifiable buffer exactly as long as nNewLength
	LPTSTR GetBufferSetLength(int nNewLength);
	// release memory allocated to but unused by string
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn refcounting off

// Implementation
protected:
	// implementation helpers
	void AllocCopy(CStringBuffer& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);
	void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data);
	void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData);
	void CopyBeforeWrite();
	void AllocBeforeWrite(int nLen);
	static int PASCAL SafeStrlen(LPCTSTR lpsz);
};

#endif // !defined(STRINGBUFFER_H__INCLUDED_)
