#if !defined(AUTOTRADERDEF_H__INCLUDED_)
#define AUTOTRADERDEF_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ZAN						495000L
#define ZAN_TRADE				495000L
#define ZAN_OUTPUT				0
#define LOGNAME_THREADID
//#define PRICELIST
//#define NICELIST
//#define GETHIASHI
//#define GETALLHIASHI
//#define GETFUNASHI
//#define GETCHART
//#define COMPACTDB
//#define SKIP_FUNASHIANALYZE
#define PRE_HOUR				14
#define TIMESIM_PRE_HOUR		14
#define BUY_END_HOUR			14
#define BUY_END_MINUTE			55
//#define BUY_END_HOUR			10
//#define BUY_END_MINUTE			45
#define TIMESIM_BUY_END_HOUR	14
#define TIMESIM_BUY_END_MINUTE	55
//#define TIMESIM_BUY_END_HOUR	10
//#define TIMESIM_BUY_END_MINUTE	45
#define TIMEUNIT				1
#define NICECODE_MAXCOUNT		10
#define MEMMAPPASIZE			(sizeof(long) + (60 * 4 + 60 + 55 + 15 + 2) * 60 / TIMEUNIT * sizeof(long))

#define LOCKOFF_H_DIFF			2
#define LOCKOFF_L_DIFF			2
#define BUY_DIFF				4
//#define PROFIT_CUT_A			9L
//#define PROFIT_CUT_B			10L
#define PROFIT_CUT_A			5L
#define PROFIT_CUT_B			10L
#define AVEUP_PROFIT_CUT_A		8L
#define AVEUP_PROFIT_CUT_B		10L
#define LOSS_CUT_DIFF			3L
//#define LOSS_CUT_DIFF			6L
//#define LOSS_CUT_DIFF			8L
#define HAZARD_DIFF				8L
//#define SELL_PRICE_MINUTE		2
#define SELL_PRICE_MINUTE		(10 * 12)
//#define SELL_HAZARD_MINUTE		2
#define SELL_HAZARD_MINUTE		(10 * 12)
//#define SELL_HAZARD_MINUTE		(300 * 12)
#define LOSS_STOP				10L

//#define HIASHI_LONG_COUNT		25
//#define HIASHI_SHORT_COUNT		12
#define HIASHI_LONG_COUNT		1
#define HIASHI_SHORT_COUNT		0
//#define FUNASHI_LONG_COUNT		12
//#define FUNASHI_SHORT_COUNT		12
#define FUNASHI_LONG_COUNT		((60 + 20) / TIMEUNIT)
#define FUNASHI_SHORT_COUNT		0

#define MADDR_BUFLEN			256
#define LKEY_BUFLEN				256
#define IDPWD_BUFLEN			256

#define MAIN_EXENAME			"AutoTrader"
#define MAIN_EXENAMELEN			10

#define CHARTVIEWER_EXENAME		"ChartViewer"
#define KEHAIVIEWER_EXENAME		"KehaiViewer"
#define TRADEHELPER_EXENAME		"TradeHelper"
#define TRADECONSOLE_EXENAME	"TradeConsole"
#define UPDATEMANAGER_EXENAME	MAIN_EXENAME _T("UpdateManager")

#define FNAME_MAINEXE			MAIN_EXENAME _T(".exe")
#define FNAME_UPDATEMANAGEREXE	UPDATEMANAGER_EXENAME _T(".exe")

#define URL_UPDATE0				_T("http://www8.tok2.com/home2/hashikun/lib/")
#define URL_UPDATE0_ALPHA		_T("http://www8.tok2.com/home2/hashikun/lib-alpha/")
#define URL_UPDATE0_BETA		_T("http://www8.tok2.com/home2/hashikun/lib-beta/")

#define TESTURL_UPDATE0			_T("http://www8.tok2.com/home2/hashikun/0lib/")
#define TESTURL_UPDATE0_ALPHA	_T("http://www8.tok2.com/home2/hashikun/0lib-alpha/")
#define TESTURL_UPDATE0_BETA	_T("http://www8.tok2.com/home2/hashikun/0lib-beta/")

#define URL_UPDATE1				_T("http://hp.vector.co.jp/authors/VA030717/lib/")

#define FNAME_UPDATETXT			_T("update-autotrader.txt")
#define FNAME_AUTOEXECTXT		_T("AutoExec.TXT")

#define FNAME_PRODUCTCODE		_T("ProductCode.txt")
#define FNAME_LASTSTATUS		_T("LastStatus.INI")

#define FNAME_HELP_CHM			MAIN_EXENAME _T(".chm")
#define FNAME_HELP_HTM			MAIN_EXENAME _T(".htm")
#define FNAME_DB				MAIN_EXENAME ".mdb"
#define FNAME_TEMPDB			MAIN_EXENAME "~.mdb"
#define FNAME_RTSDB				MAIN_EXENAME "Rts.mdb"
#define FNAME_MEIGARA			"Meigara.INI"
#define FNAME_MEIGARASIM		"MeigaraSim.INI"
#define FNAME_MEIGARARTS		"MeigaraRts.INI"
#define FNAME_NEWS				"News.INI"
#define FNAME_STOCKAVE			"StockAve.html"
#define FNAME_QUOTE0			"Quote0.html"
#define FNAME_QUOTE1			"Quote1.html"

#define DNAME_AUTOTRADER		MAIN_EXENAME

#define URL_LOGIN0				"https://espc.jip-jet.ne.jp/login.con?code=063"
#define URL_LOGIN1				"https://www.deal.matsui.co.jp/ITS/login/MemberLogin.jsp"
#define URL_LOGIN2				"https://home.cosmo-sec.co.jp/net/trade/Exchange.html"
#define URL_TRADE0				"https://trade.net.sec.kazaka.jp/"
#define URL_ODRYAK_ICHIRAN		"https://espc.jip-jet.ne.jp/topmenu.do?menuNo=1&category=ST&server_id=%s&ssnid=%s&menuNo=1&category=ST"
#define URL_MATSUIQUOTE			"http://ot2.qweb.ne.jp/matsui"
#define URL_COSMOQUOTE			"http://wwwc.marketviewer.net/"

#define OBJ_LOGIN0				"/certification2.con"
#define OBJ_LOGIN1				"/servlet/ITS/login/MemberLoginEnter"
#define OBJ_QUICKREAD			"/servlet/ITS/info/QuickReadAgree"
#define OBJ_QSEARCH				"%sqsearch.exe?F=template%%2Ftp%%5Fkensaku%%5F01&GO_BEFORE=&BEFORE=%d"
#define OBJ_KABU_HIASHI			"%sqsearch.exe?F=template/tp_kabu_hiashi&QCODE=%s"
#define OBJ_KABU_ICHIRAN		"%sqsearch.exe?F=template%%2Ftp%%5Fkabu%%5Fichiran&GO_BEFORE=&BEFORE=%d"
#define OBJ_KABU_KAKAKU			"%squote.cgi?F=template/tp_kabu_kakaku&QCODE=%s"
#define OBJ_KABU_QUOTE			"%squote.cgi?F=template/tp_kabu_quote&QCODE=%s"
#define OBJ_COSMOQUOTE0			"/cosmo_basicplus/asp-bin/cb_f_quote.aspx?req_code=%s%%23%s%%241"
#define OBJ_COSMOQUOTE1			"/cosmo_basicplus/asp-bin/cb_c_qlist.aspx?req_code=%s&sheet_no=1&"
#define OBJ_COSMOQUOTE2			"/cosmo_basicplus/asp-bin/cb_c_qlist.aspx?req_code=%s&sheet_no=1&kehai_flg=1"
#define OBJ_KABU_CHART_L		"%schart03.exe?template=ini/chart031&basequote=%s&mode=D&lower=V"
//#define OBJ_KABU_DAYCHART_L		"%schart21.exe?template=ini/chart21&basequote=%s&mode=&size=1&lower=V&point=OFF&begin=&end="
#define OBJ_KABU_DAYCHART_L		"%schart22.exe?template=ini/chart22&basequote=%s&mode=D&size=1&begin=&end="
#define OBJ_INDEX_CHART_L		"%schart03.exe?template=ini/chart03_shisuu_1&basequote=%s"
#define OBJ_INDEX_DAYCHART_L	"%schart21.exe?template=ini/chart21_shisuu&basequote=%s&mode=D&size=1"
#define OBJ_RANK_TOP0			"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DYRP&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=DYRP&TARGET97="
#define OBJ_RANK_TOP1			"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DYRP&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=DYRP&TARGET97=&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK_BOTTOM0		"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=DYRP&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=&TARGET97=DYRP"
#define OBJ_RANK_BOTTOM1		"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=DYRP&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=&TARGET97=DYRP&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK_KYUZOU0		"%sqsearch.exe?F=template/tp_rank_04&REFINDEX=-KYUZOU2&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=&TARGET97=KYUZOU2"
#define OBJ_RANK_KYUZOU1		"%sqsearch.exe?F=template/tp_rank_04&REFINDEX=-KYUZOU2&KEY1=&KEY2=&KEY3=&TARGET95=&TARGET96=&TARGET97=KYUZOU2&GO_BEFORE=&BEFORE=20"

#define OPT_LOGIN0				"code=063&s_value=&shop=650&customer=%s&pass=%s"
#define OPT_LOGIN1				"attrFromJsp=/ITS/login/MemberLogin.jsp&clientCD=%s&passwd=%s&easyTradeFlg=0"
#define OPT_LOGIN2				"sent=&PageID=IZJG0000.IZG0010&rootID=0&JSESSIONID=%s&MCD=031&KOB=%s&PSW=%s&LOGIN=ÉçÉOÉCÉì"
#define OPT_QUICKREAD			"attrSrcKey=null&fromPage=ISWEB"

#define HEA_POST				"Content-Type: application/x-www-form-urlencoded"

#define DL_BUFLEN				4096

#define TBL_INFO				"Info"
#define TBL_HIASHI				"Hiashi"
#define TBL_FUNASHI0			"Funashi0"
#define TBL_FUNASHI1			"Funashi1"
#define TBL_FUNASHI2			"Funashi2"
#define TBL_FUNASHIDATETIME		"FunashiDateTime"

#define FLD_IN_CODE				"Code"
#define FLD_IN_NAME				"Name"
#define FLD_IN_SIJO				"Sijo"
#define FLD_IN_TYPE				"Type"
#define FLD_IN_UNIT				"Unit"

#define FLD_HI_DATE				"Day"
#define FLD_HI_CODE				"Code"
#define FLD_HI_STARTPRICE		"StartPrice"
#define FLD_HI_HIGHPRICE		"HighPrice"
#define FLD_HI_LOWPRICE			"LowPrice"
#define FLD_HI_PRICE			"Price"
#define FLD_HI_TRADECOUNT		"TradeCount"

#define FLD_FU_DATETIME			"DateTime"
#define FLD_FU_CODE				"Code"
#define FLD_FU_PRICE			"Price"
#define FLD_FU_TRADECOUNT		"TradeCount"
#define FLD_FU_VWAP				"VWAP"
#define FLD_FU_KEHAIPRICE		"KehaiPrice"
#define FLD_FU_KEHAICOUNT		"KehaiCount"

#define FLD_FD_DATETIME			"DateTime"

#define FLD_PA_DIFF				"Diff"
#define FLD_PA_MAXDIFF			"MaxDiff"
#define FLD_PA_MINDIFF			"MinDiff"
#define FLD_PA_COUNT			"Count"

#define SECRET_KEY				_T("")

#define REG_SUBKEY_UNINSTALL	_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define REG_KEY_INSTALLLOCATION	_T("InstallLocation")

#define REG_SUBKEY_TVCAT		_T("Software\\TVCat")
#define REG_SUBKEY_AUTOTRADER	_T("Software\\") DNAME_AUTOTRADER

#define REG_KEY_IYEAR			_T("Data0")
#define REG_KEY_IMON			_T("Data1")
#define REG_KEY_IDAY			_T("Data2")

#define REG_KEY_MADDR			_T("Data3")
#define REG_KEY_LKEY			_T("Data4")

#define REG_KEY_IVER			_T("Data5")

#define REG_KEY_TREASUREID		_T("Data6")
#define REG_KEY_TREASUREPWD		_T("Data7")

#define REG_KEY_MATSUIID		_T("Data8")
#define REG_KEY_MATSUIPWD		_T("Data9")

#define REG_KEY_COSMOID			_T("Data10")
#define REG_KEY_COSMOPWD		_T("Data11")

#define REG_KEY_DATAFOLDER		_T("DataFolder")
#define REG_KEY_TESTURL			_T("TestUrl")

#define PF_APP_GENERAL			"General"

#define PF_KEY_AUTOTRADERUPDATETYPE		_T("AutoTraderUpdateType")
#define PF_KEY_AUTOTRADERUPDATEDATE		_T("AutoTraderUpdateDate")
#define PF_KEY_EXENOTES					_T("ExeNotes")

#define PF_KEY_CODE				"Code"
#define PF_KEY_LOCKON			"LockOn"
#define PF_KEY_SELCODE			"SelCode"
#define PF_KEY_HIASHICODE		"HiashiCode"

#define PF_KEY_NEWSCODE			"NewsCode"
#define PF_KEY_NEWSCODE2		"KessanCode"

#define MUTEX_INSTANCE			_T("Mutex_" MAIN_EXENAME "_Instance")

#define WM_OPENWND				(WM_USER + 0x401)

#define WM_USERNAME				(WM_USER + 0x300)
#define WM_PRODUCTCODE			(WM_USER + 0x301)

#endif // !defined(AUTOTRADERDEF_H__INCLUDED_)
