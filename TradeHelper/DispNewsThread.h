#if !defined(AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_)
#define AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispNewsThread.h : �w�b�_�[ �t�@�C��
//

#include <afxinet.h>
#include "../StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDispNewsThread �X���b�h

class CDispNewsThread : public CWinThread
{
	DECLARE_DYNCREATE(CDispNewsThread)
public:
	CDispNewsThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
protected:
//	CDispNewsThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^

// �A�g���r���[�g
public:
	int m_nMode;
	CString m_strDataDir;
	COleDateTime m_DtPreDate;
	CString m_strCurNewsNo;
	CStringArray m_SaDateTime;
	CStringArray m_SaCode;
	CStringArray m_SaTitle;
	CStringArray m_SaNewsNo;
	CStringArray m_SaNewsUrl;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDispNewsThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDispNewsThread();
protected:
//	virtual ~CDispNewsThread();
	int DlHtml(int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbOptional;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDispNewsThread)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_)
