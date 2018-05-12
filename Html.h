#if !defined(HTML_H__INCLUDED_)
#define HTML_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHtmlTokenizer

class CHtmlTokenizer
{
public:
	CHtmlTokenizer();
	CHtmlTokenizer(const CString& strHtml, BOOL bPreTag = FALSE);

	void SetHtml(const CString& strHtml, BOOL bPreTag = FALSE);
	void AddHtml(const CString& strHtml);
	BOOL HtmlTok();
	BOOL HtmlReverseTok();
	BOOL IsTagCmd() const;
	CString GetTagCmd() const;

	int TagAttrTok(CString& strKey, CString& strValue);
	int FindTagAttr(LPCTSTR lpszKey, CString& strValue);
//	int ChangeTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue);
	void ChangeTagAttr(LPCTSTR lpszValue);
	void AddTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue);
	int DelTagAttr(LPCTSTR lpszKey);
	void DelTagAttr();

	CString m_strHtml;
	int m_nHtmlPtr;

	CString m_strTag;
	int m_nTagLen;

protected:
	void SetTagParm();

	int m_nHtmlLen;
	CString m_strPreTag;

	CString m_strKey;
	int m_nTagPtr;
	int m_nAttrPtr;
	int m_nAttrLen;
};

#endif // !defined(HTML_H__INCLUDED_)
