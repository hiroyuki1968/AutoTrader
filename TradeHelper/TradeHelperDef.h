#if !defined(TRADEHELPERDEF_H__INCLUDED_)
#define TRADEHELPERDEF_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../AutoTraderDef.h"

//#define TIMESFREE
//#define SURYO					1

#define FNAME_CHART0			"Chart0.gif"
#define FNAME_CHART1			"Chart1.gif"
#define FNAME_ORDER				"Order.csv"

//#define URL_NEWS				"http://company.nikkei.co.jp/disclose/"
#define URL_NEWS				"http://www.nikkei.com/markets/kigyo/disclose/index.aspx"
//#define URL_KESSAN				"http://markets.nikkei.co.jp/kokunai/money-schedule/kessan.aspx"
#define URL_KESSAN				"http://www.nikkei.com/markets/kigyo/money-schedule/kessan.aspx"

#define OBJ_INDEX_QUOTE			"%squote.cgi?F=template/tp_quote_11&QCODE=%s&ORG=template/tp_sf@_01&SESSION_ID="
//#define OBJ_KABU_QUICKHEAD		"%squote.cgi?F=template/tp_00"
#define OBJ_KABU_QUICKHEAD		"%sqsearch.exe?F=tp_00"
#define OBJ_RANK0				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DYRP&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=DYRP&TARGET97="
#define OBJ_RANK1				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DYRP&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=DYRP&TARGET97=&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK2				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=DYRP&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=DYRP"
#define OBJ_RANK3				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=DYRP&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=DYRP&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK4				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DV&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97="
#define OBJ_RANK5				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DV&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK6				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DJ&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97="
#define OBJ_RANK7				"%sqsearch.exe?F=template/tp_rank_01&REFINDEX=-DJ&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK8				"%sqsearch.exe?F=template/tp_rank_04&REFINDEX=-KYUZOU2&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=KYUZOU2"
#define OBJ_RANK9				"%sqsearch.exe?F=template/tp_rank_04&REFINDEX=-KYUZOU2&KEY1=%s&KEY2=%s&KEY3=&TARGET95=&TARGET96=&TARGET97=KYUZOU2&GO_BEFORE=&BEFORE=20"
#define OBJ_RANK10				"%sqsearch.exe?F=template/tp_tokubetsukehai_02&KEY1="
#define OBJ_RANK11				"%sqsearch.exe?F=template/tp_tokubetsukehai_02&KEY1=&GO_BEFORE=&BEFORE=%d"
#define OBJ_RANK12				"/cosmo_basicplus/asp-bin/cb_c_rank.aspx?req_code=R%c.%s%%23%s&suffix_code=%%23%s%%241&kind=R%c"
#define OBJ_RANK13				"/cosmo_basicplus/asp-bin/cb_cd_tokubetukehai.aspx?req_code=&exchange_code=%s"
#define OBJ_RANK14				"/cosmo_basicplus/asp-bin/cb_cd_tokubetukehai.aspx?req_code=&exchange_code=%s&page_no=%d"

#define OPT_KAI_ODR_SIJI		"odrjoken=1&updataUrl=&meigCd=%s&sinkbShitei=0&sijo=%d&suryo=%ld&nariSasiKbn=%d&kakaku=%s&execCnd=0&yukokikan=%d&yukokigenDate=0000&execUrl=%s"
#define OPT_URI_ODR_SIJI		"odrjoken=1&meigCd=%s&sinkbShitei=0&specifyMeig=1&sijo=%d&suryo=%ld&nariSasiKbn=%d&kakaku=%s&execCnd=0&yukokikan=%d&yukokigenDate=0000&kozaKbn=1&execUrl=íçï∂&chkkakunin=1"
#define OPT_TSEI_KAI_SIJI		"odrExecYmd=%s&odrNo=%05d&tseiKaisu=%d&tseiKbn=0&menuId=M503&specifyMeig=1&sijo=%s&tseiFlg=2&suryo=%ld&uchideki=%ld&bbaiTani=%hd&tseiSu=&afterNariSasiKbn=%d&tseiKakaku=%s&execUrl=é¿çs"
#define OPT_TSEI_URI_SIJI		"odrExecYmd=%s&odrNo=%05d&tseiKaisu=%d&tseiKbn=0&menuId=M503&specifyMeig=1&sijo=%s&tseiFlg=2&suryo=%ld&tseiSu=&bbaiTani=%hd&afterNariSasiKbn=%d&tseiKakaku=%s"
//#define OPT_NEWS				"kwd=&FromDate=%s&sortorder=1&hidFromDate=%s&hidSelectFromDate=&hidKwd&HID_PAGE_NO=%d&scode=&hidErrorMsgDisp=False"
#define OPT_NEWS				"kwd=&FromDate=%s&sortorder=1&hidFromDate=%s&hidSelectFromDate=%s&hidKwd=&HID_PAGE_NO=%s&scode=&hidErrorMsgDisp=False"
//#define OPT_KESSAN				"HID_SUBMIT_VALUE=%s&HID_INDATA=&HID_KESSAN=&HID_MM=%s&HID_DD=%s&HID_GYOSYO=&HID_GYOSYONAME=&=1&HID_PAGE_NO=%s&InData=&kessan=0&yylist=%s&mmlist=%s&mm=%d&dd=%02d&gyosyu=0"
#define OPT_KESSAN				"HID_SUBMIT_VALUE=%s&HID_INDATA=&HID_KESSAN=&HID_MM=%s&HID_DD=%s&HID_GYOSYO=&HID_GYOSYONAME=&HID_PAGE_NO=%s&InData=&kessan=0&yylist=%s&mmlist=%s&mm=%d&dd=%02d&gyosyu=0"

#define MUTEX_TRADEHELPER_INSTANCE	_T("Mutex_" TRADEHELPER_EXENAME "_Instance")

#endif // !defined(TRADEHELPERDEF_H__INCLUDED_)
