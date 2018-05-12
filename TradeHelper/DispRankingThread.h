#if !defined(AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_)
#define AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispRankingThread.h : �w�b�_�[ �t�@�C��
//

#include <afxinet.h>
#include "../StringBuffer.h"
#include "../AutoTraderProc.h"
#include "TradeHelperProc.h"



/////////////////////////////////////////////////////////////////////////////
// CDispRankingThread �X���b�h

class CDispRankingThread : public CWinThread
{
	DECLARE_DYNCREATE(CDispRankingThread)
public:
	CDispRankingThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
protected:
//	CDispRankingThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^

// �A�g���r���[�g
public:
	BOOL m_bMentenance2;
	CString m_strDataDir;
	int m_nMode;
	CString m_strDBFPath;
	CInternetSession* m_pSession;
	CStringBuffer m_sbQuickInfoUrl;
	CStringBuffer m_sbCosmoQuoteUrl;
	CStringToInfoMap* m_pMstiCodeInfo;
	CMapStringToPtr* m_pMstpSelCode;
	CStringArray m_SaList;
	CStringArray m_SaCode;
	CDWordArray m_DwaTradeCount1000;
	CDWordArray m_DwaDiffPrice;
	CDWordArray m_DwaLowDiffPrice;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDispRankingThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDispRankingThread();
protected:
//	virtual ~CDispRankingThread();
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
	//{{AFX_MSG(CDispRankingThread)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_)
