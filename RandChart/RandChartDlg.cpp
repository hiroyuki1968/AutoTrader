// RandChartDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "RandChart.h"
#include "RandChartDlg.h"

#include <afxdao.h>
#include "../Common.h"
#include "../License.h"
#include "../AutoTraderDef.h"
#include "RemitRegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRandChartDlg �_�C�A���O

CRandChartDlg::CRandChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRandChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRandChartDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRandChartDlg)
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebBrowser21);
	DDX_Control(pDX, IDC_TEXT1, m_Text1);
	DDX_Control(pDX, IDC_TEXT2, m_Text2);
	DDX_Control(pDX, IDC_TEXT3, m_Text3);
	DDX_Control(pDX, IDC_TEXT4, m_Text4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRandChartDlg, CDialog)
	//{{AFX_MSG_MAP(CRandChartDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandChartDlg ���b�Z�[�W �n���h��

BOOL CRandChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	SetWindowText(m_strRandChartWndName);

	int i;
	char pszBuf[MAX_PATH];

	if (CheckLicense()) {
		PostQuitMessage(0);
		return TRUE;
	}

	srand( (unsigned)time( NULL ) );

	GetTempPath(MAX_PATH, m_strTempDir.GetBuffer(MAX_PATH));
	m_strTempDir.ReleaseBuffer();
//	m_strTempCompressDir = m_strTempDir + "Compress";

	m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARA;
//	m_strDBFPath = m_strTempCompressDir + "\\" FNAME_DB;
	m_strDBFPath = m_strTempDir + FNAME_DB;
	if (! CFile::GetStatus(m_strDBFPath, m_FileStatus))
		m_strDBFPath = m_strDataDir + "\\" FNAME_DB;
	m_strDstFPath = m_strTempDir + "RandChart.gif";

	for (i = 0; ; i ++) {
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
			m_SaSelCode.Add(pszBuf);
		} else
			break;
	}

	HiashiAnalyze();

	m_nMode = 0;
	m_nIndex = -1;

	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CRandChartDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CRandChartDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRandChartDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CRandChartDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
	CDialog::OnOK();
}

void CRandChartDlg::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
	CDialog::OnCancel();
}
int CRandChartDlg::HiashiAnalyze()
{
	int nRv = -1;

	CDaoDatabase Database;

	m_SaHiashiCode.RemoveAll();

	try
	{
		COleVariant var;

		Database.Open(m_strDBFPath, FALSE, TRUE);

		CDaoRecordset RsInfo(&Database);
		RsInfo.Open(dbOpenTable, TBL_INFO);
		RsInfo.SetCurrentIndex(pszPrimaryKey);

		while (! RsInfo.IsEOF()) {
			RsInfo.GetFieldValue(0, var);
			m_SaHiashiCode.Add(V_BSTRT((LPVARIANT)var));

			RsInfo.MoveNext();
		}
	}
	catch (CException* pEx) {
		MessageBox(StrFormat("���������f�[�^���̓G���[: %s\n", GetExceptionErrorMessage(pEx)));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:

	return nRv;
}

int CRandChartDlg::CodeToName(CString& strCode, CString& strName, CString* pstrSijoName, short* psUnit, long* plHighPrice, long* plLowPrice, long* plPreEndPrice, long* plTradeCount, CString* pstrCodeEx) 
{
	int nRv = -1;

	if (strCode.GetLength() < 4) {
		strName.Empty();
		if (pstrSijoName)
			pstrSijoName->Empty();
		if (psUnit)
			*psUnit = 1;
		if (plHighPrice)
			*plHighPrice = 0L;
		if (plLowPrice)
			*plLowPrice = 0L;
		if (plPreEndPrice)
			*plPreEndPrice = 0L;
		if (plTradeCount)
			*plTradeCount = 0L;
		if (pstrCodeEx)
			pstrCodeEx->Empty();
		return nRv;
	}

	MainCodeName MainCodeName;
	if (m_MstmCodeMainCodeName.Lookup(strCode, MainCodeName) && (pstrSijoName == NULL  ||  MainCodeName.strSijoName.GetLength()) && (psUnit == NULL  ||  MainCodeName.sUnit) && (plHighPrice == NULL  ||  MainCodeName.lHighPrice) && (plLowPrice == NULL  ||  MainCodeName.lLowPrice) && (plPreEndPrice == NULL  ||  MainCodeName.lPreEndPrice) && (plTradeCount == NULL  ||  MainCodeName.lTradeCount) && (pstrCodeEx == NULL  ||  MainCodeName.strMainCodeEx.GetLength()  &&  MainCodeName.nNewsCount == m_MstpNewsCode.GetCount())) {
		strCode = MainCodeName.strMainCode;
		strName = MainCodeName.strName;
		if (pstrSijoName)
			*pstrSijoName = MainCodeName.strSijoName;
		if (psUnit)
			*psUnit = MainCodeName.sUnit;
		if (plHighPrice)
			*plHighPrice = MainCodeName.lHighPrice;
		if (plLowPrice)
			*plLowPrice = MainCodeName.lLowPrice;
		if (plPreEndPrice)
			*plPreEndPrice = MainCodeName.lPreEndPrice;
		if (plTradeCount)
			*plTradeCount = MainCodeName.lTradeCount;
		if (pstrCodeEx)
			*pstrCodeEx = MainCodeName.strMainCodeEx;
		return 0;
	}

	CDaoDatabase Database;

	while (1) {
		try
		{
			Database.Open(m_strDBFPath, FALSE, TRUE);

			CDaoRecordset RsInfo(&Database);
			if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
				RsInfo.Open(
					dbOpenSnapshot,
					StrFormat(
						"SELECT "
							FLD_IN_CODE ", "
							FLD_IN_NAME ", "
							FLD_IN_SIJO ", "
							FLD_IN_UNIT
						" FROM " TBL_INFO
						" WHERE "
							FLD_IN_CODE " Like '%s*'",
						strCode
					)
				);

			if (plHighPrice  ||  plLowPrice  ||  plPreEndPrice  ||  plTradeCount  ||  ! RsInfo.IsEOF()) {
				CDaoRecordset* pRsWork = &RsInfo;
				CDaoRecordset RsInHi(&Database);

				if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
					RsInfo.MoveLast();
				if (plHighPrice  ||  plLowPrice  ||  plPreEndPrice  ||  plTradeCount  ||  RsInfo.GetRecordCount() >= 2) {
					RsInHi.Open(
						dbOpenSnapshot,
						StrFormat(
							"SELECT "
								TBL_INFO "." FLD_IN_CODE ", "
								TBL_INFO "." FLD_IN_NAME ", "
								TBL_INFO "." FLD_IN_SIJO ", "
								TBL_INFO "." FLD_IN_UNIT ", "
								TBL_HIASHI "." FLD_HI_DATE ", "
								TBL_HIASHI "." FLD_HI_STARTPRICE ", "
								TBL_HIASHI "." FLD_HI_HIGHPRICE ", "
								TBL_HIASHI "." FLD_HI_LOWPRICE ", "
								TBL_HIASHI "." FLD_HI_TRADECOUNT
							" FROM " TBL_INFO ", " TBL_HIASHI
							" WHERE "
								TBL_INFO "." FLD_IN_CODE " = " TBL_HIASHI "." FLD_HI_CODE
								" AND " TBL_HIASHI "." FLD_HI_DATE " >= #%s#"
								" AND " TBL_HIASHI "." FLD_HI_TRADECOUNT " > 0"
								" AND " TBL_INFO "." FLD_IN_CODE " Like '%s*'"
							" ORDER BY "
								TBL_HIASHI "." FLD_HI_DATE " DESC, "
								TBL_HIASHI "." FLD_HI_TRADECOUNT " DESC",
							(COleDateTime::GetCurrentTime() - COleDateTimeSpan(37, 0, 0, 0)).Format("%Y/%m/%d"), strCode
						),
						dbForwardOnly
					);
					if (RsInHi.IsEOF()) {
						if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
							RsInfo.MoveFirst();
					} else
						pRsWork = &RsInHi;
				}

				if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL  ||  pRsWork == &RsInHi) {
					COleVariant var;
					CString strMainCode;
					CString strSijoName;

					pRsWork->GetFieldValue(0, var);
					strMainCode = V_BSTRT((LPVARIANT)var);

					pRsWork->GetFieldValue(1, var);
					strName = V_BSTRT((LPVARIANT)var);

					if (pstrSijoName || pstrCodeEx) {
						pRsWork->GetFieldValue(2, var);
						strSijoName = V_BSTRT((LPVARIANT)var);

						if (pstrSijoName)
							*pstrSijoName = strSijoName;
					}

					if (psUnit) {
						pRsWork->GetFieldValue(3, var);
						*psUnit = var.iVal;
					}

					if ((plHighPrice || plLowPrice || plPreEndPrice || plTradeCount)  &&  pRsWork == &RsInHi) {
						COleDateTime DtDate;
						long lStartPrice;
						long lHighPrice;
						long lLowPrice;
						long lPreEndPrice;
						long lTradeCount = 0;
						COleVariant pKeyArray[2];

						do {
							pRsWork->GetFieldValue(8, var);
							if (var.lVal > lTradeCount) {
								lTradeCount = var.lVal;

								pRsWork->GetFieldValue(4, var);
								DtDate = var.date;

								pRsWork->GetFieldValue(5, var);
								lStartPrice = var.lVal;

								pRsWork->GetFieldValue(6, var);
								lHighPrice = var.lVal;

								pRsWork->GetFieldValue(7, var);
								lLowPrice = var.lVal;
							}
							pRsWork->MoveNext();
						} while (! pRsWork->IsEOF());

						CDaoRecordset RsHiashi(&Database);
						RsHiashi.Open(dbOpenTable, TBL_HIASHI);
						RsHiashi.SetCurrentIndex(pszPrimaryKey);

						pKeyArray[0] = COleVariant(DtDate - COleDateTimeSpan(1, 0, 0, 0));
						pKeyArray[1] = COleVariant(strMainCode, VT_BSTRT);
						if (RsHiashi.Seek("=", pKeyArray, 2)) {
							RsHiashi.GetFieldValue(5, var);
							lPreEndPrice = var.lVal;
						} else
							lPreEndPrice = lStartPrice;

						*plTradeCount = lTradeCount;
						if (plHighPrice)
							*plHighPrice = lHighPrice;
						if (plLowPrice)
							*plLowPrice = lLowPrice;
						if (plPreEndPrice)
							*plPreEndPrice = lPreEndPrice;
					}

					if (pstrCodeEx) {
						void* pVoid;
						CString strSijo;

						*pstrCodeEx = strMainCode;
						if (m_MstpNewsCode.Lookup(strMainCode, pVoid))
							(*pstrCodeEx).SetAt(4, '*');
						else if (m_MstpNewsCode2.Lookup(strMainCode, pVoid))
							(*pstrCodeEx).SetAt(4, '+');
						strSijo = strMainCode.Mid(5);
						if (strSijo == "T") {
							if (strSijoName.Left(10) == "����ϻް��")
								*pstrCodeEx += 'M';
							else if (strSijoName.Left(8) == "���؂Q��")
								*pstrCodeEx += '2';
						} else if (strSijo == "O")
							if (strSijoName.Left(8) == "��؂Q��")
								*pstrCodeEx += '2';
					}

					MainCodeName.strMainCode = strMainCode;
					MainCodeName.strName = strName;
					MainCodeName.strSijoName = pstrSijoName ? *pstrSijoName : pszEmpty;
					MainCodeName.sUnit = psUnit ? *psUnit : 0;
					MainCodeName.lHighPrice = plHighPrice ? *plHighPrice : 0;
					MainCodeName.lLowPrice = plLowPrice ? *plLowPrice : 0;
					MainCodeName.lPreEndPrice = plPreEndPrice ? *plPreEndPrice : 0;
					MainCodeName.lTradeCount = plTradeCount ? *plTradeCount : 0;
					MainCodeName.strMainCodeEx = pstrCodeEx ? *pstrCodeEx : pszEmpty;
					MainCodeName.nNewsCount = m_MstpNewsCode.GetCount();

					m_MstmCodeMainCodeName[strCode] = MainCodeName;

					strCode = strMainCode;

					nRv = 0;
				}
			}
		}
		catch (CDaoException* pEx) {
			if (
				pEx->m_scode == E_DAO_FileLockingUnavailable
				||  pEx->m_scode == E_DAO_TooManyActiveUsers
				||  pEx->m_scode == DBDAOERR(3734)
			) {
				Sleep(100);
				continue;
			}
			MessageBox(StrFormat("DAO �������擾�G���[: %s\n", GetExceptionErrorMessage(pEx)));
			pEx->Delete();
		}
		catch (CException* pEx) {
			MessageBox("�������擾�G���[: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}

	return nRv;
}

void CRandChartDlg::SetParam() 
{
	CFileFind Ff;
	CString strFName;
	CString strCode;
	CString strMainCode;
	CString strCodeEx;
	CString strName;
	CString strSijoName;
	short sUnit;
	COleDateTime Dt;
	CString strSrcFPath0;
	CString strSrcFPath1;
	COleDateTime DtCur = COleDateTime::GetCurrentTime();
	COleDateTime DtStart(2008, 4, 2, 0, 0, 0);
	COleDateTime DtEnd(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay(), 0, 0, 0);
	int nDays = (int)(DtEnd - DtStart).GetTotalDays() + 1;
	Parm ParmWork;

	if (Ff.FindFile(m_strDataDir + "\\Chart\\0000 FX MinuteChart\\*.gif")) {
		Ff.FindNextFile();
		strFName = Ff.GetFileName();
		if (atoi(strFName.Left(8)))
			DtStart.SetDate(atoi(strFName.Left(4)), atoi(strFName.Mid(4, 2)), atoi(strFName.Mid(6, 2)));
	}
	Ff.Close();

	while (1) {
		if (m_Check1.GetCheck() == 1)
			strCode = m_SaHiashiCode[rand() % m_SaHiashiCode.GetSize()];
		else
			strCode = m_SaSelCode[rand() % m_SaSelCode.GetSize()];
		strMainCode = strCode.Left(4);
		CodeToName(strMainCode, strName, &strSijoName, &sUnit, NULL, NULL, NULL, NULL, &strCodeEx);

		if (strMainCode.GetLength() > 4  &&  strCode == strMainCode) {
			if (strName[0] == '!')
				strName.Delete(0);
			Dt = DtStart + COleDateTimeSpan(rand() % nDays, 0, 0, 0);
			strSrcFPath0.Format(
				"%s\\Chart\\%s\\%s %s %s\\%d%02d%02d.gif",
				m_strDataDir, strSijoName,
				strCode.Left(4), strCode.Mid(5), strName,
				Dt.GetYear(), Dt.GetMonth(), Dt.GetDay()
			);
			strSrcFPath1.Format(
				"%s\\Chart\\0000 Today DayChart\\%s\\%s %s %s.gif",
				m_strDataDir, strSijoName,
				strCode.Left(4), strCode.Mid(5), strName
			);
			if (CFile::GetStatus(strSrcFPath0, m_FileStatus)) {
				ParmWork.strCode = strCodeEx;
				ParmWork.strName = strName;
				ParmWork.sUnit = sUnit;
				ParmWork.Dt = Dt;
				ParmWork.strSrcFPath0 = strSrcFPath0;
				ParmWork.strSrcFPath1 = strSrcFPath1;
				m_nIndex = m_Pa.Add(ParmWork);
				break;
			}
		}
	}
}

void CRandChartDlg::Disp() 
{
	Parm& ParmWork = m_Pa[m_nIndex];
	CString strSrcFPath = m_nMode ? ParmWork.strSrcFPath1 : ParmWork.strSrcFPath0;

	if (CopyFile(strSrcFPath, m_strDstFPath, FALSE)) {
		m_Text1.SetWindowText(ParmWork.Dt.Format("%Y/%m/%d"));
		m_Text2.SetWindowText(ParmWork.strCode);
		m_Text3.SetWindowText(IToA(ParmWork.sUnit));
		m_Text4.SetWindowText(ParmWork.strName);
		if (m_WebBrowser21.GetLocationURL().IsEmpty())
			m_WebBrowser21.Navigate(m_strDstFPath, NULL, NULL, NULL, NULL);
		else
			m_WebBrowser21.Refresh();
	} else
		MessageBox(StrFormat("%s %s �R�s�[�G���[: %s\n", strSrcFPath, m_strDstFPath, GetLastErrorMessage()));
}

int CRandChartDlg::CheckLicense()
{
	// �ϐ�
	LPBYTE lpRegData;
	DWORD cbRegDataSize;
	BOOL bNeedRemit = FALSE;
	// ���W�X�g���I�[�v��
	HKEY hKey;
	BOOL bRegOpen = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
		bRegOpen = TRUE;
	else
		bNeedRemit = TRUE;
	// ����N�����擾
	DWORD dwIYear;
	DWORD dwIMon;
	DWORD dwIDay;
	CTime TIDate;
	BOOL bIDate = FALSE;
	if (bRegOpen) {
		cbRegDataSize = sizeof(dwIYear);
		if (RegQueryValueEx(hKey, REG_KEY_IYEAR, NULL, NULL, (LPBYTE)&dwIYear, &cbRegDataSize) == ERROR_SUCCESS) {
			cbRegDataSize = sizeof(dwIMon);
			if (RegQueryValueEx(hKey, REG_KEY_IMON, NULL, NULL, (LPBYTE)&dwIMon, &cbRegDataSize) == ERROR_SUCCESS) {
				cbRegDataSize = sizeof(dwIDay);
				if (RegQueryValueEx(hKey, REG_KEY_IDAY, NULL, NULL, (LPBYTE)&dwIDay, &cbRegDataSize) == ERROR_SUCCESS) {
					dwIYear = DecodeSecretDWord(dwIYear);
					dwIMon = DecodeSecretDWord(dwIMon);
					dwIDay = DecodeSecretDWord(dwIDay);
					TIDate = CTime::CTime(dwIYear, dwIMon, dwIDay, 0, 0, 0);
					bIDate = TRUE;
				}
			}
		}
	}
	// �ŐV�C���X�g�[���o�[�W����
	DWORD dwIVer;
	BOOL bIVer = FALSE;
	if (bIDate) {
		cbRegDataSize = sizeof(dwIVer);
		if (RegQueryValueEx(hKey, REG_KEY_IVER, NULL, NULL, (LPBYTE)&dwIVer, &cbRegDataSize) == ERROR_SUCCESS) {
			dwIVer = DecodeSecretDWord(dwIVer);
			bIVer = TRUE;
		}
	}
	// �o�^���[���A�h���X�擾
	CString strMailAddr;
	if (! bNeedRemit) {
		lpRegData = (LPBYTE)new _TCHAR[MADDR_BUFLEN];
		cbRegDataSize = MADDR_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_MADDR, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS)
			strMailAddr = lpRegData;
		else
			bNeedRemit = TRUE;
		delete [] lpRegData;
	}
	// ���C�Z���X�L�[�擾
	CString strLicenseKey;
	if (! bNeedRemit) {
		lpRegData = (LPBYTE)new _TCHAR[LKEY_BUFLEN];
		cbRegDataSize = LKEY_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_LKEY, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS)
			strLicenseKey = lpRegData;
		else
			bNeedRemit = TRUE;
		delete [] lpRegData;
	}
	// ���W�X�g���N���[�Y
	if (bRegOpen)
		RegCloseKey(hKey);
	if (! bNeedRemit) {
		// �f�R�[�h
		strMailAddr = DecodeSecretString(strMailAddr);
		strLicenseKey = DecodeSecretString(strLicenseKey);
		// ���C�Z���X�`�F�b�N
		if (! CheckLicenseKey(SECRET_KEY, strMailAddr, strLicenseKey))
			bNeedRemit = TRUE;
		else {
			// ���C�Z���X�J�n���`�F�b�N
			if (strMailAddr.GetLength() <= 8)
				bNeedRemit = TRUE;
			else {
				CString strDate = strMailAddr.Right(8);
				COleDateTime DtDate;
				if (DtDate.SetDate(atoi(strDate.Left(4)), atoi(strDate.Mid(4, 2)), atoi(strDate.Mid(6))))
					bNeedRemit = TRUE;
				else {
					COleDateTime DtCur = COleDateTime::GetCurrentTime();
					if (DtCur < DtDate  ||  DtCur >= DtDate + COleDateTimeSpan(30, 0, 0, 0))
						bNeedRemit = TRUE;
				}
			}
		}
	}
	// �����o�^�_�C�A���O
	if (bNeedRemit) {
		CRemitRegDlg dlg;
		dlg.m_bIDate = bIDate;
		dlg.m_TIDate = TIDate;
		dlg.m_bIVer = bIVer;
		dlg.m_dwIVer = dwIVer;
		if (dlg.DoModal() == IDCANCEL)
			return -1;
	}

	return 0;
}
