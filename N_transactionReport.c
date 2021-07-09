#include <string.h> 
#include "N_common.h"
#include "N_utility.h"
#include "N_dateTime.h"
#include "N_printerWrapper.h" 
#include "N_printer.h"
#include "N_error.h"
#include "N_binaryTree.h"
#include "N_menu.h"
#include "N_scheduling.h"
#include "N_merchantSpec.h"
#include "N_cardSpec.h"
#include "N_connection.h"
#include "N_connectionWrapper.h"
#include "N_messaging.h"
#include "N_fileManageWrapper.h"
#include "N_fileManage.h" 
#include "N_terminalReport.h" 
#include "N_printer.h" 
#include "N_getUserInput.h" 
#include "N_transactionReport.h"
#include "N_transactions.h"
#include "N_terminalSpec.h" 
#include "N_POSSpecific.h"
#include "N_displayWrapper.h" 
#include "N_display.h" 
#include "N_initialize.h"
#include "N_log.h"
#include "N_userManagement.h"

#define LAST_CUSTOMER_BUY_RECIEPT_FILE        		"rpbuy0100"
#define LAST_CUSTOMER_BILL_RECIEPT_FILE        		"rpbill0100"
#define LAST_CUSTOMER_CHARGE_RECIEPT_FILE           "rpchrg0100" 
#define LAST_CUSTOMER_LOAN_PAY_RECIEPT_FILE        	"rploan0100"
#define LAST_CUSTOMER_ETC_RECIEPT_FILE              "rpetc0100"
#define LAST_CUSTOMER_TOPUP_RECIEPT_FILE            "rptpu0100"     //MRF_TOPUP
#define LAST_CUSTOMER_ROLL_REQUEST_RECIEPT_FILE     "rprr0100"      //HNO_ADD_ROLL
#define LAST_CUSTOMER_CHARITY_RECIEPT_FILE     		"rpcht0100"

#define BUY_LOG_FILE             					"bl"            //Buy Log
#define BILL_PAY_LOG_FILE                   		"bpl"			//Bill Pay Log
#define CHARGE_LOG_FILE                         	"chl"			//Charge Log
#define LOAN_PAY_LOG_FILE                   		"lpl"
#define ETC_LOG_FILE                                "etl"           
#define TOPUP_LOG_FILE                              "tpl"           //MRF_TOPUP
#define ROLL_LOG_FILE                               "rpl"           //HNO_ADD_ROLL
#define SUPERVISOR_LOG_FILE                         "spl"
#define CHARITY_LOG_FILE							"cht1"	
#define INITIALIZE_LOG_FILE                   		"inl"   //HNO_INIT

#define REVERSAL_BUY_LOG_FILE                   	"revbuylog"
#define REVERSAL_BILLPAY_LOG_FILE               	"revbillog"
#define REVERSAL_CHARGE_LOG_FILE               		"revchrglog"
#define REVERSAL_LOAN_PAY_FILE               		"revloanlog"
#define REVERSAL_ETC_FILE                           "revetclog"
#define REVERSAL_TOPUP_FILE                         "revtpulog"     //MRF_TOPUP
#define TRANS_ERROR_LOG_FILE        				"dtrerr0100"
#define REVERSAL_CHARITY_LOG_FILE               	"revchartog"

/*********************************LOG NUMBER TRANS*********************************/
#if defined( CASTLES_V5S) || defined (VX520) //ABS:ADD
#define SEPERATED_STR_SIZE							250 //ABS:ADD
#define MAX_BUY_TRANS_LOG_RECORDS                   1000
#define MAX_BILL_PAY_TRANS_LOG_RECORDS              1000
#define MAX_CHARGE_TRANS_LOG_RECORDS                1000
#define MAX_LOAN_PAY_TRANS_LOG_RECORDS              1000
#define MAX_ETC_TRANS_LOG_RECORDS                   1000 
#define MAX_TOPUP_TRANS_LOG_RECORDS                 1000 //MRF_TOPUP
#define MAX_SUPERVISOR_TRANS_LOG_RECORDS            200 
#define MAX_TRANS_ERROR_LOG_RECORDS                 200 
#define MAX_ROLL_REQUEST_TRANS_LOG_RECORDS          10 
#define MAX_CHARITY_TRANS_LOG_RECORD 				100
#define MAX_INITIALIZE_TRANS_LOG_RECORDS            100//HNO_INIT

#define MAX_LINE_SUCCESS_TRANS_DISPLAY              3500
#define MAX_LINE_UNSUCCESS_TRANS_DISPLAY            2000

#define MAX_UNSUCCESS_BUY_TRANS                     500
#define MAX_UNSUCCESS_CHARGE_TRANS                  500
#define MAX_UNSUCCESS_BILLPAY_TRANS                 500
#define MAX_UNSUCCESS_LOANPAY_TRANS                 500
#define MAX_UNSUCCESS_ETC_TRANS                     500 
#define MAX_UNSUCCESS_TOPUP_TRANS                   500 //MRF_TOPUP 
#define MAX_UNSUCCESS_CHARITY_TRANS                 50
#endif

#ifdef INGENICO5100

#define MAX_BUY_TRANS_LOG_RECORDS                   600 // max buy log records
#define MAX_BILL_PAY_TRANS_LOG_RECORDS              100 // max BILLpAY log records
#define MAX_CHARGE_TRANS_LOG_RECORDS                200 // max charge log records
#define MAX_LOAN_PAY_TRANS_LOG_RECORDS              100 // max BILLpAY log records
#define MAX_TRANS_ERROR_LOG_RECORDS                 50/* //mgh 250*/ // max error log records
#define MAX_SUPERVISOR_TRANS_LOG_RECORDS            100
#define MAX_ETC_TRANS_LOG_RECORDS                   100
#define MAX_TOPUP_TRANS_LOG_RECORDS                 100 //MRF_TOPUP

#define MAX_LINE_SUCCESS_TRANS_DISPLAY              350 /*MRF_IDENT 3500*/ //max line to display success transactions
#define MAX_LINE_UNSUCCESS_TRANS_DISPLAY            200 /*MRF_IDENT 2000*/ //max line to display unsuccess transactions

#define MAX_UNSUCCESS_BUY_TRANS                     50
#define MAX_UNSUCCESS_CHARGE_TRANS                  50
#define MAX_UNSUCCESS_BILLPAY_TRANS	                50
#define MAX_UNSUCCESS_LOANPAY_TRANS	                50 
#define MAX_UNSUCCESS_ETC_TRANS                     50
#define MAX_UNSUCCESS_TOPUP_TRANS                   50 //MRF_TOPUP
#endif

#if defined(ICT250) || defined(IWL220)

#define MAX_LINE_SUCCESS_TRANS_DISPLAY              200//3500 //max line to display success transactions
#define MAX_LINE_UNSUCCESS_TRANS_DISPLAY            200 //max line to display unsuccess transactions
#define SEPERATED_STR_SIZE							50 //HNO_IDENT

#define MAX_BUY_TRANS_LOG_RECORDS                   400 // max buy log records //HNO: change 200 to 550
#define MAX_BILL_PAY_TRANS_LOG_RECORDS              500 // max BILLpAY log records //HNO: change 200 to 1000
#define MAX_INSURANCE_TRANS_LOG_RECORDS             10 // max INSURANCE log records //HNO: change 200 to 1000
#define MAX_CHARGE_TRANS_LOG_RECORDS                300 // max charge log records //HNO: change 200 to 1000
#define MAX_TRANS_ERROR_LOG_RECORDS                 300/* //mgh 250*/ // max error log records //HNO: change 200 to 1000
#define MAX_LOAN_PAY_TRANS_LOG_RECORDS              300	//HNO_LOAN
#define MAX_TOPUP_TRANS_LOG_RECORDS                 30 //MRF_TOPUP
#define MAX_ETC_TRANS_LOG_RECORDS                   300 //MRF_ETC
#define MAX_SUPERVISOR_TRANS_LOG_RECORDS            100  //MRF
#define MAX_ROLL_REQUEST_TRANS_LOG_RECORDS          100  //MRF
#define MAX_CHARITY_TRANS_LOG_RECORD 				100	//HNO_CHARITY
#define MAX_INITIALIZE_TRANS_LOG_RECORDS            100//HNO_INIT

#define MAX_UNSUCCESS_BUY_TRANS                     50
#define MAX_UNSUCCESS_CHARGE_TRANS                  50
#define MAX_UNSUCCESS_BILLPAY_TRANS                 50
#define MAX_UNSUCCESS_LOANPAY_TRANS                 50
#define MAX_UNSUCCESS_ETC_TRANS                     50 //MRF_ETC
#define MAX_UNSUCCESS_TOPUP_TRANS                   50 //MRF_TOPUP
#define MAX_UNSUCCESS_CHARITY_TRANS                 50	//HNO_CHARITY

#endif

/****************Identifier Code for supervisor****************/
#define TEST_POS                                    1001
#define UPDATE_APP                                  1002
#define UPDATE_GUIDE                                1003
#define VISITOR_CASE                                1004
#define PERIODIC_VISIT                              1005
#define UPDATE_CONTRACT                             1006
#define UPDATE_LABLE                                1007
#define CHANGE_TERMINAL                             1008 
#define REMOVE_POS                                  1009
#define INSTALLATION_TRANS                          1010
#define ENTRANCE									1111 //+MRF_971026
#define EXIT										1112 //+MRF_971026

//1: mean the header is printed, do not print it again
//0: mean the header should be printed
static uint8 prePrintFlags = 0;//[20] = {0};

void    addBuyReport(messageSpecST* messageSpec);
void    addBillPayReport(messageSpecST* messageSpec);
void    addChargeReport(messageSpecST* messageSpec);
void    addLoanPayReport(messageSpecST* messageSpec);
void    addETCReport(messageSpecST* messageSpec);
void    addTopupReport(messageSpecST* messageSpec);
void    addSupervisiorReport(messageSpecST* messageSpec);

void    getIssuerBankName(uint8* BIN, uint8* Name);
void    getBillPayTypeStr(int16 billType, uint8* billTypeStr);
uint8   printChargeType(uint8 chargeType, uint8* nominalValueWithComma);

void resetPrePrintFlags(void)
{
    prePrintFlags = 0;
}

void makeTransPrintDataLog(filesST* files, messageSpecST* messageSpec)                        
{
    int16                       retValue 					= FAILURE; /** write in file function return value */
    uint8                       fileName[FILE_NAME_LENTGH]	= {0};
	uint8                       loginUserName[15 + 1]       = {0};
    lastCustomerReceiptST       lastCustomerReceipt;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*****Make Trans Print Data Log*****");
    
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (messageSpec->transType == TRANS_BUY)
    {
    	strcpy(fileName, LAST_CUSTOMER_BUY_RECIEPT_FILE);

		if (getPOSService().shiftService == TRUE)
		{
			getLoginUser(loginUserName);
			if(strcmp("„œÌ—", loginUserName) != 0)
				strcat(fileName, loginUserName);
		}
    }

    else if (messageSpec->transType == TRANS_BILLPAY)
    	strcpy(fileName, LAST_CUSTOMER_BILL_RECIEPT_FILE); 
    else if (messageSpec->transType == TRANS_BUYCHARGE) 
        strcpy(fileName, LAST_CUSTOMER_CHARGE_RECIEPT_FILE);
    else if (messageSpec->transType == TRANS_LOANPAY)
        strcpy(fileName, LAST_CUSTOMER_LOAN_PAY_RECIEPT_FILE); 
     else if (messageSpec->transType == TRANS_ETC)
        strcpy(fileName, LAST_CUSTOMER_ETC_RECIEPT_FILE); 
     else if (messageSpec->transType == TRANS_TOPUP)		//MRF_TOPUP
        strcpy(fileName, LAST_CUSTOMER_TOPUP_RECIEPT_FILE); 
     else if (messageSpec->transType == TRANS_ROLL_REQUEST)//HNO_ADD_ROLL
        strcpy(fileName, LAST_CUSTOMER_ROLL_REQUEST_RECIEPT_FILE);
     else if (messageSpec->transType == TRANS_CHARITY)
        strcpy(fileName, LAST_CUSTOMER_CHARITY_RECIEPT_FILE);
    
    strcpy(lastCustomerReceipt.PAN, messageSpec->cardSpec.PAN);
    strcpy(lastCustomerReceipt.amount, messageSpec->amount);
    strcpy(lastCustomerReceipt.approvalCode, messageSpec->approvalCode);
    strcpy(lastCustomerReceipt.customerName, messageSpec->cardSpec.customerName);
    strcpy(lastCustomerReceipt.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(lastCustomerReceipt.preAmount, messageSpec->preAmount);
    strcpy(lastCustomerReceipt.depositID, messageSpec->depositID);
    strcpy(lastCustomerReceipt.tipAmount, messageSpec->tipAmount);
    
    lastCustomerReceipt.billSpec = messageSpec->billSpec;
    lastCustomerReceipt.dateTime = messageSpec->dateTime;
    lastCustomerReceipt.merchantSpec = messageSpec->merchantSpec;
    lastCustomerReceipt.transType = messageSpec->transType;
    lastCustomerReceipt.buyChargeSpec = messageSpec->buyChargeSpec;    
    lastCustomerReceipt.loanPay = messageSpec->loanPay;
    lastCustomerReceipt.ETC = messageSpec->ETC;
    lastCustomerReceipt.topup = messageSpec->topup; //MRF_TOPUP
    lastCustomerReceipt.rollRequest = messageSpec->rollRequest; //HNO_ADD_ROLL
    lastCustomerReceipt.charity = messageSpec->charity;
    
    
    if (messageSpec->responseStatus != FAILURE)
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**UPDATE: lastCustomerBuyReceiptFile");
	    retValue = updateFileInfo(fileName, &lastCustomerReceipt, sizeof(lastCustomerReceiptST));    
	    if (retValue != SUCCESS)
	        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }

    if (messageSpec->transType != TRANS_BUYCHARGE)
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**UPDATE: customerReceiptFile");
        retValue = updateFileInfo(files->customerReceiptFile, &lastCustomerReceipt, sizeof(lastCustomerReceiptST));    
        if (retValue != SUCCESS)
            addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM) ;
    }
}

void addBuyReport(messageSpecST* messageSpec)  
{
    int16           retValue						= FAILURE;		/** write in file function return value */
    uint8			fileName[FILE_NAME_LENTGH]		= {0};
    uint8           activeUserName[16]              = {0};
    buyTransLogST   transaction;
	

    memset(&transaction, 0, sizeof(buyTransLogST));
    
    strcpy(fileName, BUY_LOG_FILE);
    
	if (getPOSService().shiftService)
	{
		getActiveUser(activeUserName);
		if(strcmp("„œÌ—", activeUserName) != 0)
			strcat(fileName, activeUserName);
	}
    
    transaction.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->cardSpec.PAN, transaction.PAN);
    strcpy(transaction.amount, messageSpec->amount); 
    strcpy(transaction.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(transaction.depositID, messageSpec->depositID);
    strcpy(transaction.tipAmount, messageSpec->tipAmount);
    
    retValue = appendFixedFileInfo(fileName, &transaction, sizeof(buyTransLogST), MAX_BUY_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
}
 
void addBillPayReport(messageSpecST* messageSpec)  
{
    int16          		retValue                    = FAILURE;              /** write in file function return value */
    uint8				fileName[FILE_NAME_LENTGH]	= {0};
    billPayTransLogST   transaction;                                        /** billPay transaction detail */
    
    memset(&transaction, 0, sizeof(billPayTransLogST));
    strcpy(fileName, BILL_PAY_LOG_FILE);
    
    transaction.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->cardSpec.PAN, transaction.PAN);
    strcpy(transaction.billAmount, messageSpec->billSpec.billAmount); 
    strcpy(transaction.billID, messageSpec->billSpec.billID);
    strcpy(transaction.paymentID, messageSpec->billSpec.paymentID);
    strcpy(transaction.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    
    retValue = appendFixedFileInfo(fileName, &transaction, sizeof(billPayTransLogST), MAX_BILL_PAY_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}

uint8 prePrint(int printRecLines, filesST* files)
{
	dateTimeST	dateTime	= {0, 0};
	
	dateTime = getDateTime();
    if (!printReceiptHeader(&dateTime, printRecLines, files))
        return FALSE;
    
    prePrintFlags = 1;
	return TRUE;
}

uint8 printUnsuccessTrans(uint8 transType)
{
    uint8 transName[12] = {0};
    
    if (!PrinterAccess(TRUE))    
        return FALSE;
    
    getIsoTransactionName(transName, transType);
    
    if (!printOneStringFarsi(transName, PRN_NORM, ALIGN_CENTER))
        return FALSE;
    
    printStar();
    
    if (!printOneStringFarsi(" —«ò‰‘ «‰Ã«„ ‰‘œ!", PRN_NORM, ALIGN_CENTER))
        return FALSE;
    
    printStar();
    printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}


/**
 * print header of transaction receipt.
 * @param   dateTime transaction date and time.
 * @param   prinrRecLines print recied header lines?
 * @see     printLogo()
 * @see     printReceiptDateTime()
 * @return  TRUE or FALSE.
 */
uint8 printReceiptHeader(dateTimeST* dateTime, int printRecLines, filesST* files) 
{
    uint8           marketName[100]		= {0};			/** market name */
    uint8           headerLine1[31]		= {0};          /** line1 of header message postal code*/
    uint8           headerLine2[31]		= {0};          /** line2 of header message phone*/
    uint8           headerLine3[300]	= {0};          /** line3 of header message Address MRF & HNO */
    uint8           shift[22]           = {0};
	uint8           activeUserName[16]  = { 0 };
    merchantSpecST  merchantSpec;

    memset(&merchantSpec, 0, sizeof(merchantSpecST));    
    
    readMerchantSpec(files, &merchantSpec); //TODO: MRF OUTPUT NOT CHECKED
#ifndef VX520
    initPrinter(); 
#endif
    if (!PrinterAccess(TRUE))    
        return FALSE;
    
    /** PRINT LOGO */
#if defined(ICT250) || defined(IWL220)
    if (!printLogo(files, BankLogo))
    	return FALSE;
#else
	if (!printLogo(files, ShaparakLogo))
		return FALSE;
#endif

    /** PRINT MARKET NAME */
    strcpy(marketName, merchantSpec.marketName);
    removePad(marketName, ' ');
    
    if (strlen(marketName) > 0) 
    {    
#ifdef VX520
		if (!printOneString_FAEN(marketName, PRN_NORM, ALIGN_CENTER))//..ABS_971201
                return FALSE;
#else
        if (!printOneStringFarsi(marketName, PRN_NORM, ALIGN_CENTER))//MRF_971017
                return FALSE;
#endif
    }
    

    /** PRINT HEADER LINES */
    if (printRecLines) 
    {
        /** PRINT CODE POSTI */
        strcpy(headerLine1, merchantSpec.postalCodeMarket); // MRF: SIZE OF VARIABLE NOT EQUAL
        removePad(headerLine1, ' ');
        
       if (strlen(headerLine1) > 0) 
		{
			if (!printTwoStringNumericFarsi(headerLine1, "òœÅ” Ì", PRN_NORM))
				return FALSE;
		}
        
        /** PRINT TEL NUMBER */
       strcpy(headerLine2, merchantSpec.merchantPhone); // MRF: SIZE OF VARIABLE NOT EQUAL
       removePad(headerLine2, ' ');
       if (strlen(headerLine2) > 0) 
       {
			if (!printTwoStringNumericFarsi(headerLine2, "‘„«—Â  ·›‰", PRN_NORM))
                return FALSE;
       } 
       
       /**PRINT ADDRESS MARKET*/
       strcpy(headerLine3,merchantSpec.marketAddress);
       removePad(headerLine3,' ');
       if (strlen(headerLine3) > 0)
            if (!printOneStringFarsi(headerLine3,PRN_NORM,ALIGN_CENTER))
                return FALSE;
    }  

    /** PRINT ACTIVE USER */
     if (getPOSService().shiftService)
	 {
		 getActiveUser(activeUserName);
		 if (!strcmp(activeUserName, ""))
         {
#ifdef VX520
			 printTwoStringNumericFarsi("---", "‘Ì›  ›⁄«·", PRN_NORM);
#else
			 printTwoString("‘Ì›  ›⁄«·:", "---", PRN_NORM, TRUE);
#endif	
         }
         else
         {
            strcpy(shift, "‘Ì›  ");
			strcat(shift, activeUserName);
            printTwoStringFarsi(shift, "‘Ì›  ›⁄«·:", PRN_NORM);
         }
     }
      
    /** PRINT STAR */ 
//    if (!printStar()) -MRF_971017
//        return FALSE; 
    
    return TRUE;
}


/**
 * print footer of transaction receipt.
 * @param   reprint is reprint receipt?
 * @param   printTel print tel?
 * @param   emptyLine print empty lines end of receipt?
 * @return  TRUE or FALSE.
 */
uint8 printTransactionFooter(uint8 reprint, uint8 customer, uint8 emptyLine, filesST* files) 
{
    uint8               telNo[20]       = {0};
    uint8               footerMseg[31]	= {0};
    merchantSpecST      merchantSpec;
    
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "*********printTransactionFooter*********");
    
    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    readMerchantSpec(files, &merchantSpec);    
  
    if (!PrinterAccess(TRUE))    
        return FALSE;
    
    if ((!customer && !reprint )&& (fileExist(SUPERVISOR_FILE) != SUCCESS))
    {
        if (!printOneStringFarsi("«„÷«¡ „‘ —Ì:", PRN_NORM, ALIGN_RIGHT))
               return FALSE;
    }

    if (strlen((const char*)merchantSpec.helpPhone) > 0) 
    {
        strcpy(telNo, "021-");
        
        removePad(merchantSpec.helpPhone, ' ');
        strcat(telNo, merchantSpec.helpPhone);

        selectSmallPrinterFontFarsi();
#ifdef CASTLES_V5S //MRF_TTF
        reversPartString(telNo);
#endif
        if (fileExist(SUPERVISOR_FILE) != SUCCESS)
        {
            if (merchantSpec.merchantID[0] == '1')
            {
#ifdef VX520
					if (!printTwoStringNumericFarsi(telNo, "›‰ ¬Ê« ò«— ", PRN_SMALL)) //ABS:CHANGE:960808
#else
					 if (!printTwoStringFarsi(telNo,"›‰ ¬Ê« ò«— ", PRN_SMALL))
#endif
                {
                    selectNormalPrinterFontFarsi();
                    return FALSE;
                }
            }
            else if (merchantSpec.merchantID[0] == '2') //#MRF_971204
            {
                if (!printTwoStringFarsi(telNo,"»Â Å—œ«Œ  „· ", PRN_SMALL))
                {
                    selectNormalPrinterFontFarsi();
                    return FALSE;
                }
                    
            }
        }
        selectNormalPrinterFontFarsi();
    }   

    if (!reprint && strlen(merchantSpec.footerLine) > 0) 
    {
        strcpy(footerMseg, merchantSpec.footerLine);
        removePad(footerMseg, ' ');
        
        if (strlen(footerMseg) > 0) 
        {
            if (!printOneStringFarsi(footerMseg, PRN_NORM, ALIGN_CENTER))
                return FALSE;
        }
    }

    printBlankLines(BLANK_LINES_COUNT);
    return TRUE;
}


uint8 printTransactionCommonPart(messageSpecST* messageSpec, uint8 customer, uint8 rePrint, filesST* files)
{
    uint8           cardID[17]              = {0};          /** card ID */
    uint8           stanNo[7]               = {0};          /** stan string */
    uint8           valueWithComma[19 + 1]  = {0};          /** value with comma string */
    uint8           amountPrintBuffer[20]   = {0}; 
    uint8           IssuerName[20]          = {0};
    uint8           reversalCancelled       = FALSE; 
    uint8           supervisor              = FALSE;
    uint8           transType[30]           = {0};
    uint8           title[40]               = {0};
    uint8           tmp[30]                 = {0};
    uint8           printStr[100]           = {0};
    uint8           buffer[50]              = {0};
    uint8           phoneNumber[12]         = {0};
    uint8           output[12]              = {0};
    uint8           reversStr[250]          = {0};
    uint8           chargeID[20]			= {0};
    uint8           chargeTypeStr[20 + 1] 	= {0};
    uint8           chargeStr[20]			= {0};
    uint8           instituteName[50]		= {0};
    terminalSpecST  terminalCapability      = getTerminalCapability();
    serviceSpecST   POSService              = getPOSService();
    uint8           dstCardID[19 + 1]       = {0};
    int				count                   = 0;
    uint8           shGabzValue[14]         = {0};
    uint8           shPardakhtValue[14] 	= {0};
    uint8           billTypeStr[15 + 1]     = {0};
	uint8			BIN[7]					= {0};
    uint8           model[20]               = {0};
    
    if (!PrinterAccess(TRUE))    
        return reversalCancelled;

    //+MRF_971214
    getDeviceModel(model);
    if ((fileExist(SUPERVISOR_FILE) == SUCCESS) && //For detect supervisor
            (fileExist(files->reversalReceiptFile) != SUCCESS)) 
        supervisor = TRUE;
    
    getIsoTransactionName(transType, messageSpec->transType); 
    
    /** PRINT TITLE */
    if ((rePrint == REPRINT) || (rePrint == CHARGE_REPRINT ))
    {
        strcpy(tmp,"—”Ìœ „Ãœœ „‘ —Ì");
        sprintf(title,"%s/",transType);        
        strcat(title, tmp);
        if (!printOneStringFarsi(title, PRN_NORM, ALIGN_CENTER))
            return reversalCancelled;
    }
    else if (customer)
    {
        if (messageSpec->transType  == TRANS_BALANCE 
                || messageSpec->transType  == TRANS_ETC_TRACKING
                || messageSpec->transType  == TRANS_LOAN_TRACKING)
        {
            sprintf(title,"%s",transType);
            if (!printOneStringFarsi(title, PRN_NORM, ALIGN_CENTER))
                return reversalCancelled;
        }
        else
        {   
            strcpy(tmp,"—”Ìœ „‘ —Ì");
            sprintf(title,"%s/",transType);        
            strcat(title, tmp);
            if (!printOneStringFarsi(title, PRN_NORM, ALIGN_CENTER))
                return reversalCancelled;
        }
    }
    else
    {
        if (!supervisor)
        {
            strcpy(tmp,"—”Ìœ Å–Ì—‰œÂ");
            sprintf(title,"%s/",transType);        
            strcat(title, tmp);
            if (!printOneStringFarsi(title, PRN_NORM, ALIGN_CENTER))
                return reversalCancelled;
        }
    }  

    
    if(messageSpec->transType == TRANS_CHARITY)
    {
    	getCharityInstituteName(instituteName, messageSpec->charity.InstituteCode);
    	if(!printOneStringFarsi(instituteName, PRN_NORM, ALIGN_CENTER))
    		return reversalCancelled;
    }
    
    /** PRINT TERMINAL ID */
    if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.terminalID, "‘„«—Â Å«Ì«‰Â", PRN_NORM))
        return reversalCancelled;
    
    /** PRINT MERCHANT ID */
    /**if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.merchantID, "‘„«—Â Å–Ì—‰œÂ", PRN_NORM))
        return reversalCancelled;*/
    
    /** PRINT DEPOSIT ID */ 
    if ((getPOSService().depositID) && (messageSpec->transType == TRANS_BUY)
            && (fileExist(SUPERVISOR_FILE) != SUCCESS)
            &&(messageSpec->responseStatus == SUCCESS))
    {           if (strlen(messageSpec->depositID) > 0)
                {
                    if (!printTwoStringNumericFarsi(messageSpec->depositID, "‘‰«”Â Ê«—Ì“", PRN_NORM))
                        return reversalCancelled;
                }
    }
    
    if(messageSpec->transType == TRANS_BUYCHARGE)
    {
        count = messageSpec->charge.chargeCount;

        /**PRINT CHARGE SERIAL*/
        if ((messageSpec->responseStatus == SUCCESS) || (messageSpec->responseStatus == 8) 
                    || (messageSpec->responseStatus == 16))
        {
            if (!PrinterAccess(TRUE))
                return reversalCancelled;
            
            sprintf(chargeID, "%ld", messageSpec->buyChargeSpec.id);
        	if (!printTwoStringNumericFarsi(chargeID,"‘‰«”Â ‘«—é",PRN_NORM))
        		return reversalCancelled;

        	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "chargeID: %s", chargeID);
            removePad(messageSpec->buyChargeSpec.serial, ' ');
#ifndef VX520	//++ABS:980223
            if (!printTwoStringNumericFarsi(messageSpec->buyChargeSpec.serial, "”—Ì«· ‘«—é", PRN_NORM))
                return reversalCancelled;
#else
			if (!printTwoStringNumericFarsi(messageSpec->buyChargeSpec.serial, "”—Ì«·", PRN_NORM))
				return reversalCancelled;
#endif

                if (rePrint == NO_REPRINT)
                {
                    //Remove reversal and add settlement after serial for security of PIN
                    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalTransFile");
                    fileRemove(files->reversalTransFile);
                    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
                    fileRemove(files->reversalReceiptFile);

                    addTransToSettlementFile(files, messageSpec);
                    makeTransPrintDataLog(files, messageSpec);
                    addChargeReport(messageSpec);
       
                    /** save charge information for print complete report **/
					strcpy(messageSpec->charge.chargeInfo[count].serial, messageSpec->buyChargeSpec.serial);
					strcpy(messageSpec->charge.chargeInfo[count].amount, messageSpec->buyChargeSpec.amount);
					strcpy(messageSpec->charge.chargeInfo[count].PIN, messageSpec->buyChargeSpec.PIN);
					messageSpec->charge.chargeInfo[count].type = messageSpec->buyChargeSpec.type;
					messageSpec->charge.chargeInfo[count].dateTime = messageSpec->dateTime;
					strcpy(messageSpec->charge.chargeInfo[count].ReferenceNumber, messageSpec->retrievalReferenceNumber);
					messageSpec->charge.id = messageSpec->buyChargeSpec.id;
                    savechargeInfo(messageSpec->charge,count);
                    reversalCancelled = TRUE;
                }
                if ((rePrint == CHARGE_REPRINT) || (rePrint == NO_REPRINT))
                {
                    /**PRINT PIN */
                    makeChargePIN(messageSpec->buyChargeSpec.PIN, messageSpec->buyChargeSpec.type);
                }
        }
        else
        {
        	getChargeTypeStr(messageSpec->buyChargeSpec.type, chargeTypeStr);
#ifdef VX520
			printTwoStringFarsi(chargeTypeStr, "‰Ê⁄ ‘«—é:", PRN_NORM);//ABS:CHANGE
#elif  !defined(CASTLES_V5S)//#MRF_971019
        	printTwoStringNumericFarsi(chargeTypeStr, "‰Ê⁄ ‘«—é", PRN_NORM);
#endif
        }
    }
    
    if (messageSpec->transType == TRANS_TOPUP && customer == TRUE) //MRF_TOPUP
    {
        /** PRINT MOBILE NUMBER */
        maskMobileNumbers(messageSpec->topup.mobileNo, output);
        
#ifdef CASTLES_V5S //MRF_TTF
        phoneNumber[0] = '0';
        strcat(phoneNumber, output);
        reversPartString(phoneNumber);
#else
        phoneNumber[0] = '0';
        strcat(phoneNumber, output);
#endif
        if (!printTwoStringNumericFarsi(phoneNumber, "‘„«—Â  ·›‰ Â„—«Â", PRN_NORM))
            return reversalCancelled;
    }
    
    
    if ((messageSpec->transType == TRANS_LOANPAY) || (messageSpec->transType == TRANS_LOAN_TRACKING))
    {
        /** PRINT DESTINATION CARD NUMBER */
            maskCardId(messageSpec->loanPay.destinationCardPAN, dstCardID);
#ifdef CASTLES_V5S //MRF_TTF
        reversPartString(dstCardID);
#endif
#ifdef VX520
		if (!printTwoStringNumericFarsi(dstCardID, "ò«—  ﬁ”ÿ", PRN_NORM)) //..ABS:980223
			return reversalCancelled;
#else
            if (!printTwoStringFarsi(dstCardID, "‘„«—Â ò«—  ﬁ”ÿ:", PRN_NORM))
                return reversalCancelled;
#endif           
        /** PRINT DESTINATION NAME */
        memset(printStr, 0, sizeof(printStr));
        sprintf(printStr, "%s %s", messageSpec->loanPay.destinationCardHolderName, messageSpec->loanPay.destinationCardHolderFamily);

        if (!printTwoStringFarsi(printStr, "»Â ‰«„:", PRN_NORM)) //#MRF_971019 :REMOVE IFDEF BECAUSE SAME THAT//ABS:CHANGE:961213
            return reversalCancelled;
        
        messageSpec->merchantSpec.recieveSTAN = messageSpec->loanPay.STAN;
    }
    
    if (messageSpec->transType == TRANS_BILLPAY)
    {
        getBillPayTypeStr(messageSpec->billSpec.type, billTypeStr);
        memcpy(shGabzValue, messageSpec->billSpec.billID, 13);
        shGabzValue[13] = 0;
        removePadLeft(shGabzValue,'0'); 
        
        if (!printTwoStringNumericFarsi(shGabzValue, billTypeStr, PRN_NORM))//#MRF_971018
            return reversalCancelled;

        /** PRINT SHENASE PARDAKHT */
        memcpy(shPardakhtValue, messageSpec->billSpec.paymentID, 13);
        shPardakhtValue[13] = 0;
        removePadLeft(shPardakhtValue, '0');  
        if (!printTwoStringNumericFarsi(shPardakhtValue, "‘‰«”Â Å—œ«Œ ", PRN_NORM))
            return reversalCancelled;
    }
    
    if (messageSpec->transType == TRANS_ETC || messageSpec->transType == TRANS_ETC_TRACKING)
    {
        {   /** PRINT SERIAL ETC */
#ifndef VX520
            if (!printTwoStringNumericFarsi(messageSpec->ETC.serialETC, "”—Ì«· »—ç”»", PRN_NORM)) 
                return reversalCancelled;
#else
			if (!printTwoStringNumericFarsi(messageSpec->ETC.serialETC, "”—Ì«·", PRN_NORM))
			return reversalCancelled;
#endif

            /** PRINT DESTINATION NAME */
            sprintf(printStr, "%s %s", messageSpec->ETC.cardHolderName, messageSpec->ETC.cardHolderFamily);
            if (!printTwoStringFarsi(printStr, "»Â ‰«„:", PRN_NORM))
                return reversalCancelled;
        }
        messageSpec->merchantSpec.recieveSTAN = messageSpec->ETC.STAN;
    }
    
    if ((!supervisor) || (rePrint))
    {
        /** PRINT CARD NUMBER */
        if (messageSpec->transType == TRANS_ETC_TRACKING)
        	maskCardId(messageSpec->ETC.PAN, cardID);
        else if(messageSpec->transType == TRANS_LOAN_TRACKING)
        	maskCardId(messageSpec->loanPay.PAN, cardID);
        else
        	maskCardId(messageSpec->cardSpec.PAN, cardID);
        
        removePad(cardID, ' ');
        
        /** PRINT ISSUER BANK */
        strncpy(BIN, cardID, 6);
        BIN[6] = 0;
        getIssuerBankName(BIN, IssuerName);
        
#ifdef CASTLES_V5S  //MRF_TTF
        strcpy(reversStr, cardID);
        reversPartString(reversStr); 
        if (!printTwoStringNumericFarsi(reversStr,IssuerName, PRN_NORM)) //+MRF_971017
            return reversalCancelled;
#else
     if (!printTwoStringNumericFarsi(cardID, IssuerName, PRN_NORM))
            return reversalCancelled;  
#endif
            
    /** PRINT STAN */
    sprintf(stanNo, "%ld", messageSpec->merchantSpec.recieveSTAN);
    if (!printTwoStringNumericFarsi(stanNo, "‘„«—Â ÅÌêÌ—Ì", PRN_NORM))
        return reversalCancelled;
    }
    
    /** PRINT DATE AND TIME */
    if (!printReceiptDateTime(&(messageSpec->dateTime), TRUE)) 
        return reversalCancelled;
        
    /** PRINT REFERENCE NUMBER */
    if ((messageSpec->responseStatus == SUCCESS) || (messageSpec->responseStatus == 8)
            || (messageSpec->responseStatus == 16))
    {
        removePad(messageSpec->retrievalReferenceNumber, ' ');

        if (!printTwoStringNumericFarsi(messageSpec->retrievalReferenceNumber, "‘„«—Â „—Ã⁄", PRN_NORM))
                return reversalCancelled;        
    }
    
    /** PRINT TIP AMOUNT *///+HNO_970924
    if ((getPOSService().tip) && (messageSpec->transType == TRANS_BUY) && ((!messageSpec->pcPos))
            && (fileExist(SUPERVISOR_FILE) != SUCCESS))
    {
        if (strlen(messageSpec->tipAmount) != 0 && (messageSpec->tipAmount[0] != '0'))//MRF_NEW20
        {
            makeValueWithCommaStr(messageSpec->tipAmount, valueWithComma);
            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„»·€ «‰⁄«„", PRN_NORM, ALIGN_RIGHT, TRUE))
                return reversalCancelled;
        }
    }
    
    /** PRINT CHARGE INFORMATION */ 
    if (messageSpec->transType == TRANS_BUYCHARGE) 
        makeValueWithCommaStr(messageSpec->buyChargeSpec.amount, valueWithComma);

    if ((messageSpec->transType == TRANS_ETC_TRACKING) || messageSpec->transType == TRANS_LOAN_TRACKING)
        return TRUE;
    
    if ((!supervisor)|| (rePrint))
    {   
        /** PRINT TRANS STATUS */
        if ((messageSpec->responseStatus != SUCCESS) && (messageSpec->responseStatus != 8)
                && (messageSpec->responseStatus != 16))
        {
            uint8 errorMessage[50] = {0};
            uint8 errorCode[10]    = {0};
            int   shpState         = 0; 
            
            sprintf(errorCode, "%2d", messageSpec->responseStatus);
            shpState = getShaparakMessages(errorMessage, messageSpec->responseStatus);

            if ((rePrint == NO_REPRINT) && (shpState == WARNING_TRANS || shpState == NO_RECEIVE || shpState == DUPLICATE_TRANS))
            {
                if (customer) 
                {
                    if ((messageSpec->transType != TRANS_ETC) && (messageSpec->transType != TRANS_TOPUP)
                    		&& (messageSpec->transType != TRANS_LOANPAY))
                    {
                        if (strcmp(model,VEGA3000) != 0) //+MRF_971214
                        {
                            if (!printTwoStringNumericFarsi(errorCode, "⁄„·Ì«  ‰«„Ê›ﬁ", PRN_NORM_INVERSE))
                                return reversalCancelled;
                        }
                        else if (!printTwoStringNumericFarsi(errorCode, "⁄„·Ì«  ‰«„Ê›ﬁ", PRN_NORM))
                                    return reversalCancelled;
                    }
                    else if (messageSpec->transType == TRANS_ETC || messageSpec->transType == TRANS_TOPUP
                    		|| messageSpec->transType == TRANS_LOANPAY) //MRF_TOPUP
                    {
						if (strcmp(model, VEGA3000) != 0)//+MRF_971214
						{
							if (!printTwoStringNumericFarsi(errorCode, "⁄„·Ì«  ‰«„‘Œ’", PRN_NORM_INVERSE))
								return reversalCancelled;
						}
                         else if (!printTwoStringNumericFarsi(errorCode, "⁄„·Ì«  ‰«„‘Œ’", PRN_NORM))
									return reversalCancelled; 
                        
                    }
                }
                else if (!printOneStringFarsi("⁄„·Ì«  ‰«„Ê›ﬁ)Â‘œ«—(", PRN_NORM, ALIGN_CENTER))
                        return reversalCancelled;    
            }  
            else if (strcmp(model,VEGA3000) != 0)//#MRF_971214
            {
                showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "BIIIILLL2222");
                if (!printTwoStringNumericFarsi(errorCode, errorMessage, PRN_NORM_INVERSE))
                     return reversalCancelled; 
            }
            else if (!printTwoStringFarsi(errorCode, errorMessage, PRN_NORM))
            {
                    return reversalCancelled; 
            }
            
            if ((messageSpec->transType == TRANS_BUY || messageSpec->transType == TRANS_BILLPAY || 
                    messageSpec->transType == TRANS_BUYCHARGE || messageSpec->transType == TRANS_CHARITY) && 
                    (shpState == INVALID_TRANS || shpState == NO_RECEIVE))
            {
#ifdef CASTLES_V5S //MRF_TTF
                if (!printOneStringFarsi("œ— ’Ê—  ò”— ÊÃÂ «“ Õ”«» ‘„« „»·€ „–òÊ— ÿÌ 72 ”«⁄  »Â Õ”«» ‘„« ⁄Êœ  œ«œÂ ŒÊ«Âœ ‘œ œ— €Ì— «Ì‰ ’Ê—  ÃÂ  ÅÌêÌ—Ì ·ÿ›« »« ‘„«—Â  ·›‰ 43570-021  „«” Õ«’· ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
                    return reversalCancelled;
#else
#if defined(ICT250) || defined(IWL220)//HNO_ADD
            	if (!printOneStringFarsi("œ— ’Ê—  ò”—ÊÃÂ «“Õ”«» ‘„« „»·€ „–òÊ— ÿÌ 72",PRN_NORM, ALIGN_CENTER))
					return reversalCancelled;
				if (!printOneStringFarsi("”«⁄  »Â Õ”«» ‘„«⁄Êœ  ŒÊ«Âœ ‘œ œ— €Ì—", PRN_NORM,ALIGN_CENTER))
					return reversalCancelled;
				if (!printOneStringFarsi("«Ì‰’Ê—  ÃÂ  ÅÌêÌ—Ì ·ÿ›« »« ‘„«—Â  ·›‰", PRN_NORM,ALIGN_CENTER))
					return reversalCancelled;
				if (!printOneStringFarsi("021-43570 „«” Õ«’· ›—„«ÌÌœ", PRN_NORM,ALIGN_CENTER))
					return reversalCancelled;
#else
                if (!printOneStringFarsi("œ— ’Ê—  ò”— ÊÃÂ «“ Õ”«» ‘„« „»·€ „–òÊ— ÿÌ 72 ”«⁄  »Â Õ”«» ‘„« ⁄Êœ  œ«œÂ ŒÊ«Âœ ‘œ œ— €Ì— «Ì‰ ’Ê—  ÃÂ  ÅÌêÌ—Ì ·ÿ›« »« ‘„«—Â  ·›‰ 021-43570  „«” Õ«’· ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
                    return reversalCancelled;
#endif
#endif
            }
            else if (((messageSpec->transType == TRANS_ETC)|| (messageSpec->transType == TRANS_LOANPAY)) &&
                    (shpState == INVALID_TRANS || shpState == NO_RECEIVE))
             {
				#if defined(ICT250) || defined(IWL220)
                    if (!printOneStringFarsi("‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì«  —« «“ ÿ—Ìﬁ  —«ò‰‘", PRN_NORM, ALIGN_CENTER))
                        return FALSE;
                    if (!printOneStringFarsi("—ÂêÌ—Ì ÅÌêÌ—Ì ‰„«ÌÌœ", PRN_NORM, ALIGN_CENTER))
                        return FALSE;
				#else
                    if (!printOneStringFarsi("‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì«  —« «“ ÿ—Ìﬁ  —«ò‰‘ —ÂêÌ—Ì° ÅÌêÌ—Ì ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
                        return FALSE; 
#endif
             }
            else if ((messageSpec->transType == TRANS_TOPUP) && //MRF_TOPUP
                    (shpState == INVALID_TRANS || shpState == NO_RECEIVE))
             {
				#ifdef INGENICO
				 if (!printOneStringFarsi("œ— ’Ê—  ⁄œ„ ‘«—é  ·›‰ Â„—«Â ‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì« .", PRN_NORM, ALIGN_CENTER))
					return FALSE;
				 if (!printOneStringFarsi("—« «“ ÿ—Ìﬁ «Å—« Ê— Â„—«Â „Ê—œ ‰Ÿ— ÅÌêÌ—Ì ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
					return FALSE;
				#else
                 if (!printOneStringFarsi("œ— ’Ê—  ⁄œ„ ‘«—é  ·›‰ Â„—«Â ‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì«  —« «“ ÿ—Ìﬁ «Å—« Ê— Â„—«Â „Ê—œ ‰Ÿ— ÅÌêÌ—Ì ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
                    return FALSE; 
				#endif
             }
        }  
        else if (strcmp(model,VEGA3000) != 0)//#MRF_971214
        {
            if (!printOneStringFarsi("  ⁄„·Ì«  „Ê›ﬁ   " , PRN_BIG_INVERSE, ALIGN_CENTER))
                return reversalCancelled;
        }   
        else if (!printOneStringFarsi("  ⁄„·Ì«  „Ê›ﬁ   " , PRN_BIG, ALIGN_CENTER))
        {
                return reversalCancelled;
        }
        
        /** PRINT AMOUNT */
        if ((messageSpec->responseStatus == SUCCESS) || (messageSpec->responseStatus == 8) 
                || (messageSpec->responseStatus == 16))
        {
            if (!PrinterAccess(TRUE))
                return reversalCancelled;
            
            if (messageSpec->transType == TRANS_BALANCE)
            {
                 /** PRINT "MANDEH HESAB" */
                if (messageSpec->balanceSpec.accountBalance[0] != 0) 
                {
                    removePadLeft(messageSpec->balanceSpec.accountBalance, '0');
                    if (strlen((const char*)messageSpec->balanceSpec.accountBalance) == 0)
                    {
                        valueWithComma[0] = '0';
                        valueWithComma[1] = 0;
                    }
                    else 
                        makeValueWithCommaStr(messageSpec->balanceSpec.accountBalance, valueWithComma);
                    
//#MRF_971019 		  sprintf(amountPrintBuffer, "%s—Ì«·", valueWithComma);
//                    removePadLeft(amountPrintBuffer,'0');
//                    if (!printTwoStringNumericFarsi(amountPrintBuffer,"„ÊÃÊœÌ", PRN_NORM_INVERSE))//#MRF_971019
					if (!printThreeStringFarsi("—Ì«·", valueWithComma, "„ÊÃÊœÌ", PRN_NORM, ALIGN_RIGHT, TRUE))
                        return reversalCancelled;
                }
            }   
            else 
            {
                if (messageSpec->transType == TRANS_BUYCHARGE)
                    makeValueWithCommaStr(messageSpec->buyChargeSpec.amount, valueWithComma);   
                else if (messageSpec->transType == TRANS_ETC)
                    makeValueWithCommaStr(messageSpec->ETC.amount, valueWithComma); 
                else if (messageSpec->transType == TRANS_LOANPAY)
                    makeValueWithCommaStr(messageSpec->loanPay.payAmount, valueWithComma);
                else 
                    makeValueWithCommaStr(messageSpec->amount, valueWithComma);   
                
                //+HNO_970924
                if ((POSService.discount) && (!messageSpec->pcPos) && (messageSpec->transType == TRANS_BUY))
                {
                    //#MRF_971019
                   makeValueWithCommaStr(messageSpec->preAmount, valueWithComma);
                   if (!printThreeStringFarsi("—Ì«·", valueWithComma , "„»·€", PRN_NORM, ALIGN_RIGHT, TRUE))
                        return reversalCancelled; 

//                  //#ABS_980217
                    makeValueWithCommaStr(messageSpec->amount, valueWithComma);
//                    sprintf(amountPrintBuffer, "%s—Ì«·", valueWithComma);
//                    removePadLeft(amountPrintBuffer,'0');
//                    if (!printTwoStringNumericFarsi(amountPrintBuffer,"„»·€ »«  Œ›Ì›", PRN_NORM_INVERSE))//#MRF_971018
					if (!printThreeStringFarsi("—Ì«·", valueWithComma, "„»·€ »«  Œ›Ì›", PRN_NORM, ALIGN_RIGHT, TRUE))
                        return reversalCancelled;
                }
                else
                {
                    //#ABS_980217
//                    sprintf(amountPrintBuffer, "%s—Ì«·", valueWithComma);
//                    removePadLeft(amountPrintBuffer,'0');
//                    if (!printTwoStringNumericFarsi(amountPrintBuffer,"„»·€", PRN_NORM_INVERSE))//#MRF_971018
					if (!printThreeStringFarsi("—Ì«·", valueWithComma, "„»·€", PRN_BIG, ALIGN_RIGHT, TRUE))

                        return reversalCancelled;
                }
            }
        }
    }
    
    if ((terminalCapability.pcPosCapability) && (POSService.PcPOSService))
    {
        if((customer) && (rePrint == NO_REPRINT))
        {
            if(strlen(messageSpec->information.advertise1) > 0)
                printOneStringFarsi(messageSpec->information.advertise1, PRN_NORM, ALIGN_CENTER);
        }
        if((!customer))
        {
            if(strlen(messageSpec->information.advertise2) > 0)
                printOneStringFarsi(messageSpec->information.advertise2, PRN_NORM, ALIGN_CENTER);
        }
    }

    return TRUE;
}


/**
 * print balance transaction receipt.
 * @param   PAN card number.
 * @param   available mablaghe ghabele bardasht.
 * @param   leger mande hesab.
 * @see     printReceiptHeader()
 * @see     printTransactionFooter()
 */
void printBalanceReceipt(filesST* files, messageSpecST* messageSpec) 
{
    uint8		valueWithComma[50]		= {0};          /** string format of value with comma */
    uint8		cardID[17]          	= {0};          /** card ID */
    uint8   	amountPrintBuffer[20]   = {0};
    dateTimeST	nowDateTime				= {0, 0};
    
    memset(&nowDateTime , 0,sizeof(dateTimeST));
    
    if (!PrinterAccess(TRUE))    
        return;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);    
    
    /** PRINT HEADER */
    if (!prePrintFlags)
    {
		if (!printReceiptHeader(&nowDateTime, TRUE, files)) 
			return;
    }
    
    prePrintFlags = 0;
       
    printTransactionCommonPart(messageSpec, TRUE, FALSE, files);
    printOneStringFarsi("ò«—„“œ ⁄„·Ì«  „ÊÃÊœÌ1,206—Ì«·",PRN_NORM,ALIGN_CENTER);//#MRF_971019
        
    /** PRINT FOOTER */    
    if (!printTransactionFooter(FALSE, TRUE, TRUE, files)) 
        return;    
}


/**
 * print buy transaction receipt.
 * @param   transactionInfo transaction information.
 * @param   customer is costomer receipt?
 * @see     printReceiptHeader()
 * @see     printTransactionJointPart()
 * @see     printTransactionFooter()
 * @return  TRUE or FALSE.
 */
uint8 printTransactionBuy(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)                           
{
    uint8	reversalCancelled           = FALSE;
    int8    i                           = 0;
    
    if (!PrinterAccess(TRUE))    
        return reversalCancelled;    

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);  
    
    /** PRINT HEADER */
    if (!prePrintFlags)
    	if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files)) 
    		return reversalCancelled;  
    
    prePrintFlags = 0;
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "preAmount: %s", messageSpec->preAmount);
    
    /** PRINT COMMON PART */
    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files)) 
        return reversalCancelled; 
        
    if ((customer && !rePrint) && ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8) 
            || (messageSpec->responseStatus == 16) ))
    {   
        /** CANCEL REVERSAL & ... */
        reversalCancelled = TRUE;
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalTransFile");
        fileRemove(files->reversalTransFile);
        
        addTransToSettlementFile(files, messageSpec);
        makeTransPrintDataLog(files, messageSpec);
    	addBuyReport(messageSpec);
    }
    
    if (strlen(messageSpec->reward) > 0 &&  customer)
    {
        printStar();
#ifdef INGENICO	//HNO_IDENT
    	printOneStringFarsi("‘„« »—‰œÂ ŒÊ‘ ‘«‰” Ã‘‰Ê«—Â »Â«—", PRN_BIG, ALIGN_CENTER);
    	printOneStringFarsi(" œ— »Â«— ‘œÌœ.ÃÂ  œ—Ì«›  Ã«Ì“Â »«", PRN_BIG, ALIGN_CENTER);
    	printOneStringFarsi("‘„«—Â «„œ«œ „‘ —Ì«‰  „«” »êÌ—Ìœ:)", PRN_BIG, ALIGN_CENTER);
#else
        printOneStringFarsi(messageSpec->reward, PRN_BIG, ALIGN_CENTER);
#endif
        printStar();
    }
    
    if(!customer)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
        fileRemove(files->customerReceiptFile);
    }
    
    /** PRINT TRANSACTION FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files)) 
        return reversalCancelled; // this true because print is complete

    if (strlen(messageSpec->reward) > 0 &&  customer)
        LEDBlink(2);


    if ((!reversalCancelled) && (!rePrint))
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);        
    }
    
    return reversalCancelled;
}

void getBillPayTypeStr(int16 billType, uint8* billTypeStr)
{
	switch (billType)
    {
        case 1:
        	strcpy(billTypeStr, "ﬁ»÷ ¬»");
            break;
        case 2:
        	strcpy(billTypeStr, "ﬁ»÷ »—ﬁ");
            break;
        case 3:
        	strcpy(billTypeStr, "ﬁ»÷ ê«“");
            break;
        case 4:
        	strcpy(billTypeStr, "ﬁ»÷  ·›‰");
            break;
        case 5:
        	strcpy(billTypeStr, "ﬁ»÷  ·›‰ Â„—«Â");
            break;
        case 6:
        	strcpy(billTypeStr, "ﬁ»÷ ‘Â—œ«—Ì");
            break;
        case 8:
        	strcpy(billTypeStr, "ﬁ»÷ „«·Ì« ");
            break;
        case 9:
//        	strcpy(billTypeStr, "Ã—«∆„ —«Â‰„«ÌÌ/—«‰‰œêÌ"); -MRF_971018
            strcpy(billTypeStr, "ﬁ»÷ Ã—Ì„Â");
            break;
    }
}


void printBillTypeStr(int16 billType)
{
	uint8	billTypeStr[15 + 1]		= {0};
	
    getBillPayTypeStr(billType, billTypeStr);
    printOneStringFarsi(billTypeStr, PRN_NORM, ALIGN_CENTER);
}


/**
 * print bill pay transaction receipt.
 * @param   dateTime transaction date and time.
 * @param   PAN card number.
 * @param   value amount.
 * @param   Stan stan, transaction number.
 * @param   approvalCode approval code.
 * @param   shGhbzPrdkht shenaseh ghabz & shenaseh pardakht.
 * @see     printReceiptHeader()
 * @see     printTransactionFooter()
 * @return  TRUE or FALSE.
 */
uint8 printTransactionBillPay(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint) 
{
    uint8	reversalCancelled		= FALSE;		/** is reversal canceled? */
    uint8	valueWithComma[20]		= {0};
    uint8   amountPrintBuffer[20]   = {0};

    if (!PrinterAccess(TRUE))    
        return reversalCancelled;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
            return reversalCancelled;
 
    prePrintFlags = 0;
    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
        return reversalCancelled;

    if ((customer && !rePrint) && ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8) 
            || (messageSpec->responseStatus == 16)))
    { 
        /** CANCEL REVERSAL & ... */
        reversalCancelled = TRUE;
        
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);
        
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalTransFile");
        fileRemove(files->reversalTransFile);
        
        addTransToSettlementFile(files, messageSpec);           
        makeTransPrintDataLog(files, messageSpec);
    	addBillPayReport(messageSpec);
    }
    
    if(!customer)
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
        fileRemove(files->customerReceiptFile);
    }
    
    /** PRINT FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files)) 
        return reversalCancelled;
    
   if ((!reversalCancelled) && (!rePrint))
    {
	   showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);        
    }
    
    return reversalCancelled;
}


void getChargeTypeStr(uint8 chargeType, uint8* chargeTypeStr)
{
    switch (chargeType) 
    {
        case MULTI_MCI:
        	strcpy(chargeTypeStr, "Â„—«Â «Ê·");
            break;
        case MULTI_IRANCELL:
        	strcpy(chargeTypeStr, "«Ì—«‰”·");
            break; 
        case MULTI_RIGHTEL:
        	strcpy(chargeTypeStr, "—«Ì ·");
            break;
        default:
            break;
    }	
}


uint8 printChargeType(uint8 chargeType, uint8* nominalValueWithComma)
{
	uint8	chargeTypeStr[15 + 1] = {0};
	
	getChargeTypeStr(chargeType, chargeTypeStr);
    
    if (!printTwoStringFarsi(chargeTypeStr,"‰Ê⁄ ‘«—é:", PRN_NORM))
        return FALSE;
	return TRUE;
}


/**
 * add buy charge report to file.
 * @param   dateTime transaction date & time.    
 * @param   chargeType charge type.  
 * @param   value amount.  
 */
void addChargeReport(messageSpecST* messageSpec) 
{
    int16       retValue                    = FAILURE;                  /** file function return value */
    uint8       fileName[FILE_NAME_LENTGH]	= {0};
    chargeLogST charge;                                                 /** charge detail, for save in file */
  
    memset(&charge, 0, sizeof(chargeLogST)); 
    
    strcpy(fileName, CHARGE_LOG_FILE);
    
    charge.dateTime = messageSpec->dateTime;
    charge.type = messageSpec->buyChargeSpec.type;
    strcpy(charge.amount, messageSpec->buyChargeSpec.amount);
    strcpy(charge.realAmount, messageSpec->buyChargeSpec.realAmount);
    maskCardId(messageSpec->cardSpec.PAN, charge.PAN);
    strcpy(charge.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(charge.serial, messageSpec->buyChargeSpec.serial);
 
   retValue = appendFixedFileInfo(fileName, &charge , sizeof(chargeLogST), MAX_CHARGE_TRANS_LOG_RECORDS);    
   if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM); 
}

void addLoanPayReport(messageSpecST* messageSpec)  
{
    int16          		retValue                    = FAILURE;          /** write in file function return value */
    uint8				fileName[FILE_NAME_LENTGH]	= {0};
    loanPayTransLogST   loanPay;                                        /** billPay transaction detail */
    
    memset(&loanPay, 0, sizeof(loanPayTransLogST));
    strcpy(fileName, LOAN_PAY_LOG_FILE);
    
    loanPay.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->loanPay.destinationCardPAN, loanPay.destinationCardPAN);
    strcpy(loanPay.amount, messageSpec->loanPay.payAmount); 
    maskCardId(messageSpec->cardSpec.PAN, loanPay.PAN);
    strcpy(loanPay.destinationCardHolderName, messageSpec->loanPay.destinationCardHolderName);
    strcpy(loanPay.destinationCardHolderFamily, messageSpec->loanPay.destinationCardHolderFamily);
    strcpy(loanPay.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
   
    retValue = appendFixedFileInfo(fileName, &loanPay, 
                                     sizeof(loanPayTransLogST), MAX_LOAN_PAY_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
}


uint8 printTransactionBuyCharge(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)
{
    uint8       reversalCancelled           = FALSE;            /** is reversal canceled? */
    uint8*      reversedStr[50]             = {0};
    
    if (!PrinterAccess(TRUE))    
        return reversalCancelled;
    
    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);  

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files)) 
            return reversalCancelled;
    
    prePrintFlags = 0;
    
    /** PRINT COMMON PART */
    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files)) 
        return reversalCancelled;
    
     if ((customer && !rePrint) && ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8) 
            || (messageSpec->responseStatus == 16)))
     {
        /** CANCEL REVERSAL */
        reversalCancelled = TRUE;
     }
    
    //--MRF_971211: DELETE USING DESCRIPTIONS
    
    if(!customer)
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
        fileRemove(files->customerReceiptFile);
    }
    
    /** PRINT TRANSACTION FOOTER */
    if (!printTransactionFooter(FALSE, TRUE, TRUE, files)) 
        return reversalCancelled; // this true because print is complete
        
    if ((!reversalCancelled) && (!rePrint))
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);        
    }
    
    return reversalCancelled;
}


/**
 * print reversal receipt for some failed transaction.
 * @param   showPrinterError show printer error?
 * @see     printReceiptHeader()
 * @see     printTransactionFooter()
 * @return  TRUE or FALSE.
 */
uint8 printReversal(filesST* files) 
{
    reversalTransST         reversalInfo;			
    merchantSpecST          merchantSpec;
    messageSpecST           messageSpec;
    dateTimeST              dateTime;
    lastCustomerReceiptST	lastCustomerReceipt;
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****printReversal Start****");
  
    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&reversalInfo, 0, sizeof(reversalTransST));
    memset(&dateTime, 0, sizeof(dateTimeST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));
    
    if (!PrinterAccess(TRUE))  
        return FALSE;  
    
    if (!readMerchantSpec(files, &(messageSpec.merchantSpec)))
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);   
        return TRUE;
    }
     
    if (!readReversalInfo(files->reversalReceiptFile, &messageSpec))
    {
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);   
        return TRUE;
    }
    
    if (messageSpec.responseStatus == SUCCESS)
        messageSpec.responseStatus = 95; //mgh: for managing reversal printer
    
    switch (messageSpec.transType)
    {
        case TRANS_BUY:
            if (!printTransactionBuy(files, &messageSpec, TRUE, NO_REPRINT))
                return FALSE;
            break;
        case TRANS_BUYCHARGE:
            if (!printTransactionBuyCharge(files, &messageSpec, TRUE, NO_REPRINT))
                return FALSE;
            break;
        case TRANS_BILLPAY:
            if (!printTransactionBillPay(files ,&messageSpec, TRUE, NO_REPRINT))
                return FALSE;
            break;
        case TRANS_TOPUP: //MRF_TOPUP
            if (!printTransactionBuyChargeTopup(files, &messageSpec, TRUE, NO_REPRINT))
                return FALSE;
            break;
        case TRANS_CHARITY:
            if (!printTransactionCharity(files, &messageSpec, TRUE, NO_REPRINT))
                return FALSE;
            break;
        default:
            break;
    }
    
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
    fileRemove(files->reversalReceiptFile);
    
    return TRUE;
}

void addUnsuccessTransLog(messageSpecST* messageSpec)
{
    
    int16               retValue2                 = FAILURE;
    int16               maxRecord                 = 0;
    int8                logName[FILE_NAME_LENTGH] = {0};
    uint8               activeUserName[16]        = { 0 };
    reversalTransST     reversalInfo;
	

    memset(&reversalInfo, 0, sizeof(reversalTransST));
    
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "****addUnsuccessTransLog****");
    
	maskCardId(messageSpec->cardSpec.PAN, reversalInfo.PAN);
    strcpy(reversalInfo.amount, messageSpec->amount);
    reversalInfo.STAN       = messageSpec->merchantSpec.recieveSTAN ;
    reversalInfo.billSpec   = messageSpec->billSpec;
    reversalInfo.chargeType = messageSpec->buyChargeSpec.type;
    reversalInfo.transType  = messageSpec->transType;
    reversalInfo.SWdateTime = messageSpec->SWdateTime;
    reversalInfo.dateTime   = messageSpec->dateTime;
    reversalInfo.charity	= messageSpec->charity;
    
    switch (reversalInfo.transType) 
    {
        case TRANS_BUY:
            strcpy(logName, REVERSAL_BUY_LOG_FILE);

			if (getPOSService().shiftService)
			{
				getActiveUser(activeUserName);
                if(strcmp("„œÌ—", activeUserName) != 0)//+MRF_980224
                    strcat(logName, activeUserName);
			}
            maxRecord = MAX_UNSUCCESS_BUY_TRANS;
            break;
        case TRANS_BUYCHARGE:
            strcpy(logName, REVERSAL_CHARGE_LOG_FILE);
            maxRecord = MAX_UNSUCCESS_CHARGE_TRANS;
            break;
        case TRANS_BILLPAY:
            strcpy(logName, REVERSAL_BILLPAY_LOG_FILE);
            maxRecord = MAX_UNSUCCESS_BILLPAY_TRANS;
            break;
        case TRANS_LOANPAY:
            strcpy(logName, REVERSAL_LOAN_PAY_FILE);
            maxRecord = MAX_UNSUCCESS_LOANPAY_TRANS;
            break;
        case TRANS_ETC:
            strcpy(logName, REVERSAL_ETC_FILE);
            maxRecord = MAX_UNSUCCESS_LOANPAY_TRANS;
            break;
        case TRANS_CHARITY:
        	strcpy(logName,REVERSAL_CHARITY_LOG_FILE);
        	maxRecord = MAX_UNSUCCESS_CHARITY_TRANS;
            break;
        default:
            break;
    }

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**APPEND: reversalLogFile");
    retValue2 = appendFixedFileInfo(logName, &reversalInfo, sizeof (reversalTransST), maxRecord);
    if (retValue2 != SUCCESS) 
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "err #8");
        addSystemErrorReport(retValue2, ERR_TYPE_FILE_SYSTEM);
    }
}


void structCpy(lastCustomerReceiptST* lastCustomerReceipt, messageSpecST* messageSpec)
{
    strcpy(messageSpec->cardSpec.PAN, lastCustomerReceipt->PAN);
    strcpy(messageSpec->amount, lastCustomerReceipt->amount);
    strcpy(messageSpec->approvalCode, lastCustomerReceipt->approvalCode);
    strcpy(messageSpec->cardSpec.customerName, lastCustomerReceipt->customerName);
    strcpy(messageSpec->retrievalReferenceNumber, lastCustomerReceipt->retrievalReferenceNumber);
    strcpy(messageSpec->preAmount, lastCustomerReceipt->preAmount);
    strcpy(messageSpec->depositID, lastCustomerReceipt->depositID);
    strcpy(messageSpec->tipAmount, lastCustomerReceipt->tipAmount);
     
    messageSpec->dateTime = lastCustomerReceipt->dateTime;
    messageSpec->merchantSpec = lastCustomerReceipt->merchantSpec;
    messageSpec->transType = lastCustomerReceipt->transType;
    messageSpec->billSpec = lastCustomerReceipt->billSpec;
    
    messageSpec->buyChargeSpec = lastCustomerReceipt->buyChargeSpec;
    
    messageSpec->loanPay = lastCustomerReceipt->loanPay;
    messageSpec->topup = lastCustomerReceipt->topup; //MRF_TOPUP
    messageSpec->ETC = lastCustomerReceipt->ETC;
    messageSpec->charity = lastCustomerReceipt->charity;
}


uint8 readLastCustomerReceiptFile(uint8* fileName, lastCustomerReceiptST* lastCustomerReceipt)
{
	uint32      fileLength	= sizeof(lastCustomerReceiptST);    /** lenght of last buy transaction info file */
	int16       retValue	= FAILURE;							/** read file function return value */
	
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "before fileLength: %d", fileLength);
	retValue = readFileInfo(fileName, lastCustomerReceipt, &fileLength);    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "fileLength: %d", fileLength);
    
    if (retValue != SUCCESS)
    {
    	if (retValue != ERR_FILE_NOT_FOUND)
    		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    return TRUE;
}


/**
 * reprint last buy transaction receipt.
 * @see     printTransactionReprint()
*/
uint8 reprintBuyTransaction(argumentListST* args)
{    
    filesST*                files						= (filesST*) (args->argumentName);
    uint8                   fileName[FILE_NAME_LENTGH]	= {0};
    uint8					loginUserName[15 + 1] 		= { 0 }; 
    uint8					selectUser[16]				= {0};
    messageSpecST           messageSpec;
    lastCustomerReceiptST	lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));
    
    strcpy(fileName, LAST_CUSTOMER_BUY_RECIEPT_FILE);

	if (getPOSService().shiftService == TRUE)
	{
		if(!displayUsersList(selectUser, FALSE))
			return FALSE;
		if(strcmp("„œÌ—", selectUser) != 0)
			strcat(fileName, selectUser);
	}

    if (!readLastCustomerReceiptFile(fileName, &lastCustomerReceipt))
    	return FALSE;
    
    structCpy(&lastCustomerReceipt, &messageSpec);    
    printTransactionBuy(files, &messageSpec, TRUE, REPRINT);

	return TRUE;
}


/**
 * reprint last bill transaction receipt.
 * @see     printTransactionReprint()
*/
uint8 reprintBillTransaction(argumentListST* args)
{    
    filesST*				files	= (filesST*) (args->argumentName);
    messageSpecST			messageSpec;
    lastCustomerReceiptST   lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_BILL_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;
    
    structCpy(&lastCustomerReceipt, &messageSpec);
    printTransactionBillPay(files, &messageSpec, TRUE, REPRINT);
    
	return TRUE;
}


uint8 reprintLoanPayTransaction(argumentListST* args)
{
    filesST*                    files	= (filesST*) (args->argumentName);
    messageSpecST               messageSpec;									/** last buy transaction information */
    lastCustomerReceiptST       lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_LOAN_PAY_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;

    structCpy(&lastCustomerReceipt, &messageSpec);
    printLoanPayTransaction(files, &messageSpec, TRUE, TRUE);

    return TRUE;
}


/**
 * print successful terminal configuration report.
 */
void successInitializeReport(filesST* files, messageSpecST* messageSpec)//HNO_INIT
{
    dateTimeST  nowDateTime     = messageSpec->dateTime;
    

    if (!PrinterAccess(TRUE))    
        return;
    
    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);
    if (!prePrintFlags)
    {
    	printReceiptHeader(&nowDateTime, FALSE, files);
    }
    
    /** PRINT SUCCESSFUL CONFIG MESSAGE */
    if (!printOneStringFarsi("ÅÌﬂ—»‰œÌ „Ê›ﬁ", PRN_NORM, ALIGN_CENTER))
        return;

    prePrintFlags = 0;
    
    /** PRINT TERMINAL ID */
    if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.terminalID, "Å«Ì«‰Â", PRN_NORM))//ABS:delete shomare
        return;

    /** PRINT MERCHANT ID */
    if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.merchantID, "Å–Ì—‰œÂ", PRN_NORM))//ABS:delete shomare
        return;
    
     /** PRINT DATE AND TIME */ 
    if (!printReceiptDateTime(&nowDateTime, TRUE))
        return;
    
    /** PRINT DASHES */
    printBlankLines(BLANK_LINES_COUNT);
}

void addTransactionErrorReport(uint8 transactionType, int errorCode, uint8 knownError)  
{
    int16        retValue                   = FAILURE;      /** write in file function return value */
    uint8        fileName[FILE_NAME_LENTGH]	= {0};
    transErrorST error;                                     /** transaction error detail */

    memset(&error, 0, sizeof(transErrorST));
    
    error.dateTime = getDateTime();
    error.transType = transactionType;
    error.errorCode = errorCode;

    strcpy(fileName, TRANS_ERROR_LOG_FILE);

    retValue = appendFixedFileInfo(fileName, &error, sizeof(transErrorST), MAX_TRANS_ERROR_LOG_RECORDS);  
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
}


uint8 readBoxReportFile(uint8* fileName, void* transaction, uint16 structLen, uint16 maxRecord, 
						uint32* userDateJalali, int* transactionNum)
{
    uint32          currentDate             = 0;				/** current date */
    dateTimeST      currentDateTime         = {0, 0};           /** current date and time */
    uint32          userDateGerigorian      = 0;				/** entered date by user (gerigorian) */
    uint8           getDateRes              = 0;
    int             searchTransRes          = -2;               /** search for transaction with specified date in transactions file */
    int             startRecordNum          = 0;				/** start record number of transactions with specified date in file */
    int             endRecordNum            = 0;				/** end record number of transactions with specified date in file */
    int16           retValue                = FAILURE;
	
    if (fileExist(fileName) != SUCCESS) 
    {
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    currentDate = systemDateTimeToDate();
    currentDateTime = getDateTime();
    gregorianToJalali(userDateJalali, currentDateTime.date);

	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "fileName:");
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "%s", fileName);
    while (TRUE) 
    {
        getDateRes = KBD_TIMEOUT;
        
        getDateRes = getDateFromUser("Ê—Êœ  «—ÌŒ:", FALSE, userDateJalali);
        if (getDateRes == KBD_CANCEL || getDateRes == KBD_TIMEOUT) 
            return FALSE;
     
        jalaliToGregorian(&userDateGerigorian , *userDateJalali);

		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "currentDate is : %d", currentDate);
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "userDateGerigorian is : %d", userDateGerigorian);

        if (currentDate < userDateGerigorian) 
        {
            displayMessageBox(" «—ÌŒ Ê«—œ ‘œÂ „⁄ »— ‰Ì” ", MSG_ERROR);
            continue;
        }
        else 
            break;
    }

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "date: %d", userDateGerigorian);
    searchTransRes = searchDateRangeInFixedFile(fileName, structLen, 0, userDateGerigorian, 
		userDateGerigorian, maxRecord, &startRecordNum, &endRecordNum);    
    
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "searchTransRes is : %d", searchTransRes);
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "startRecordNum is : %d", startRecordNum);
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "endRecordNum is : %d", endRecordNum);

    if (searchTransRes == -2 || startRecordNum == -2 || endRecordNum == -2) 
    {
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    if (startRecordNum == -1 || endRecordNum == -1) 
    {
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    *transactionNum = endRecordNum - startRecordNum + 1;
    
    retValue = readFixedFileInfoArray(fileName,(uint8*) transaction, structLen, startRecordNum, 
                                        *transactionNum, maxRecord);    
	
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "retValue is : %d", retValue);
    if (retValue != SUCCESS) 
    {
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    return TRUE;
}

uint8 merchantBoxReport(argumentListST* args)
{    
    filesST*        files                                       = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    buyTransLogST   transactions[MAX_BUY_TRANS_LOG_RECORDS] 	= {0};
    int				transactionNumber                           = 0;            /** charge number with specified date in file */
    int				counter                                     = 0;            /** loop counter */
    uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
    uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
    uint8			fileName[FILE_NAME_LENTGH]                  = {0};
    uint8			activeUser[15 + 1]                          = {0};
    uint8			title[30]                                   = {0};
    uint8			activeUserTitle[15 + 1]                     = {0};
    uint8           check                                       = FALSE;
    uint8           sumDailyValues[15 + 1]                      = {0};
    uint8			tempSumValues[15 + 1]                       = {0}; 
    uint8			valueWithComma[20]                          = {0}; 
    uint8           transNum[5]                                 = {0};
    uint8			selectUser[16]								= {0};
    int             sumCountValues                      		= 0;
    uint8           sumAllUsersValues[15 + 1]                   = {0};
    uint8			shift[22] 									= {0};
	uint8			loginUserName[15 + 1]						= {0};

    strcpy(fileName, BUY_LOG_FILE);
	strcpy(title, "ê“«—‘ ’‰œÊﬁ Œ—Ìœ");

	if(getPOSService().shiftService == TRUE)
	{
		getLoginUser(loginUserName); 
		if (strcmp("„œÌ—", loginUserName) == 0)
		{
			if(!displayUsersList(selectUser, TRUE))
				return FALSE;

			if (strcmp("ò·ÌÂ ò«—»—«‰", selectUser) == 0)
			{
				userNodeST*	currentNode				= NULL;
				uint8		user[16]				= {0};

				currentNode = getUserList();
			    if (!getDateTimeDistanceFromUser(&startDateTime, &endDateTime, activeUserTitle, activeUser))
			        return FALSE;

			    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
			    	return FALSE;

				while(currentNode)
				{
					memset(&fileName, 0, sizeof(fileName));
					memset(&valueWithComma, 0, sizeof(valueWithComma));
					memset(&sumDailyValues, 0, sizeof(sumDailyValues));

					strcpy(fileName, BUY_LOG_FILE);//file name without catting is just for admin

					strcpy(user, currentNode->data.userName);
					if(strcmp("„œÌ—", currentNode->data.userName) != 0)
						strcat(fileName, currentNode->data.userName);

					currentNode = currentNode->next;
					showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fileName allusers: %s", fileName);

					if(!readAllUsersTransactionListFile(fileName, transactions, sizeof(buyTransLogST), MAX_BUY_TRANS_LOG_RECORDS,
																	&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
					{
						transactionNumber = 0;
						requestedNum = 0;
					}

					for (counter = requestedNum - 1; counter >= 0; counter--)
						sumStringNumbers(sumDailyValues, transactions[counter].amount, sumDailyValues);

					sumCountValues = transactionNumber + sumCountValues;//sum count of all users transactions

				    strcpy(shift, "‘Ì›  ");
				    strcat(shift, user);
				    printTwoStringFarsi(shift, "‘„«—Â ‘Ì› :", PRN_NORM);

				    sprintf(transNum, "%d", transactionNumber);
				    if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
				        return FALSE;

				    makeValueWithCommaStr(sumDailyValues, valueWithComma);
				    if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
				        return FALSE;

				    printDash();

				    sumStringNumbers(sumAllUsersValues, sumDailyValues, sumAllUsersValues);
				}

			    makeValueWithCommaStr(sumAllUsersValues, valueWithComma);

			    /** PRINT TRANSACTIONS NUMBER IN DATES */
			    sprintf(transNum, "%d", sumCountValues);
			    if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ ò·", PRN_NORM))
			        return FALSE;

			    if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "Ã„⁄ ò·", PRN_NORM, ALIGN_RIGHT, TRUE))
			        return FALSE;

			    printStar();
			    printBlankLines(BLANK_LINES_COUNT);

			    return TRUE;
			}
			else
				if(strcmp("„œÌ—", selectUser) != 0)
					strcat(fileName, selectUser);
		}
		else
		{
			strcat(fileName, loginUserName);
			strcpy(selectUser, loginUserName);
		}
	}

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fileName: %s", fileName);
    if (!readTransactionListFile(fileName, transactions, sizeof(buyTransLogST), MAX_BUY_TRANS_LOG_RECORDS,
				    						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    for (counter = requestedNum - 1; counter >= 0; counter--)
        sumStringNumbers(sumDailyValues, transactions[counter].amount, sumDailyValues);
    
    makeValueWithCommaStr(sumDailyValues, valueWithComma);
    
    /** PRINT TRANSACTIONS NUMBER IN DATES */
    if(getPOSService().shiftService == TRUE)
    {
		strcpy(shift, "‘Ì›  ");
		strcat(shift, selectUser);
		printTwoStringFarsi(shift, "‘„«—Â ‘Ì› :", PRN_NORM);
    }

    sprintf(transNum, "%d", requestedNum); //#MRF_971226
    if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
        return FALSE;

    if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
        return FALSE;
    
    printStar();
    printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}

uint8 readTransactionListFile(uint8* fileName, void* transaction, uint16 structLen, uint16 maxRecord, 
							  	dateTimeST* startDateTime, dateTimeST* endDateTime, int* transactionNum,
								uint32* requestedNum,uint8* activeUserTitle, uint8* activeUser)
{
    int             searchTransRes          = -2;			/** search for transaction with specified date in transactions file */
    int             startRecordNum          = 0;			/** start record number of transactions with specified date in file */
    int             endRecordNum            = 0;			/** end record number of transactions with specified date in file */
    int				beginIndexInFile		= 0;            /** index of beginning requested transaction in transactions file */
    int16			retValue 				= FAILURE;
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**readTransactionListFile**");
    
    if (fileExist(fileName) != SUCCESS) 
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "File transaction unsuccess not exist!");
    	displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
    	return FALSE;
    }
    
    if (!(getDateTimeDistanceFromUser(startDateTime, endDateTime, activeUserTitle, activeUser)))
        return FALSE;

    searchTransRes = searchDateTimeRangeInFixedFile(fileName, structLen, 0,
    												startDateTime, endDateTime, maxRecord, 
                                                    &startRecordNum, &endRecordNum);
    
    if (searchTransRes == -2 || startRecordNum == -2 || endRecordNum == -2) 
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in Start time trans not exist !!");
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
    if (startRecordNum == -1 || endRecordNum == -1)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in End time trans not exist !!");
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }

    *transactionNum = endRecordNum - startRecordNum + 1;

    *requestedNum = *transactionNum;
    
    editNumericValue(requestedNum, " ⁄œ«œ  —«ò‰‘:", 0, maxRecord, FALSE, FALSE);

    if (*requestedNum > maxRecord)
    	if (*transactionNum <= maxRecord)
    		*requestedNum = *transactionNum;
    	else
    		*requestedNum = maxRecord;
    
    if (*requestedNum == 0 || *requestedNum > *transactionNum) 
        *requestedNum = *transactionNum;
    
    //show the last transactions
    beginIndexInFile = *transactionNum - *requestedNum + startRecordNum;
    
    retValue = readFixedFileInfoArray(fileName,(uint8*) transaction, structLen, beginIndexInFile, 
                                        *requestedNum, maxRecord);  
    if (retValue != SUCCESS) 
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in readFixedFileInfoArray trans not exist !!");
        displayMessageBox(" —«ò‰‘Ì Ì«›  ‰‘œ!", MSG_INFO);
        return FALSE;
    }
    
   
    return TRUE;
}


void fillTransListHeaderLines(uint8 lines[][32], uint16* index, uint8* title, uint8* activeUserTitle, uint8* activeUser,
		dateTimeST* startDateTime, dateTimeST* endDateTime)
{
	uint32			jalaliDate              	= 0;            /** jalali date */
    int				yearFrom                	= 0;            /** start year */
    int				monthFrom               	= 0;            /** start month */
    int				dayFrom                 	= 0;            /** start day */
    int				yearTo                  	= 0;            /** end year */
    int				monthTo                 	= 0;            /** end month */
    int				dayTo                   	= 0;            /** end day */
    int				hourFrom                	= 0;            /** start hour */
    int				minuteFrom               	= 0;            /** start minute */
    int				hourTo                  	= 0;            /** end hour */
    int				minuteTo                 	= 0;            /** end minute */
    uint16			i							= *index;
    uint8			startDateValueStr[11]   	= {0};
    uint8			endDateValueStr[11]     	= {0};
    uint8			startTimeValueStr[11]   	= {0};
    uint8			endTimeValueStr[11]     	= {0};
    uint8           spaceCountStr[50]           = {0};
    terminalSpecST	terminalCapability			= getTerminalCapability();
       
    gregorianToJalali(&jalaliDate, startDateTime->date);
    yearFrom 	= getYear(jalaliDate);
    monthFrom 	= getMonth(jalaliDate);
    dayFrom 	= getDay(jalaliDate);
    hourFrom    = getHour(startDateTime->time);
    minuteFrom 	= getMinute(startDateTime->time);
       
    gregorianToJalali(&jalaliDate , endDateTime->date);
    yearTo 		= getYear(jalaliDate);
    monthTo		= getMonth(jalaliDate);
    dayTo 		= getDay(jalaliDate);
    hourTo      = getHour(endDateTime->time);
    minuteTo 	= getMinute(endDateTime->time);
    
	/** LINE 0 : TITLE */
    if (!terminalCapability.graphicCapability)	//MRF_IDENT
    	justifyOneStringFarsi(title, lines[i++], PRN_NORM, ALIGN_CENTER);
    
    /** LINE 1 : START DATE */
    memset(spaceCountStr,' ', SPACE_COUNT);
    sprintf(startDateValueStr, "%04d/%02d/%02d", yearFrom, monthFrom, dayFrom);
    sprintf(startTimeValueStr, "%02d:%02d", hourFrom, minuteFrom);

#if defined(ICT250) || defined(IWL220)//HNO_ADD
    justifyOneStringFarsi("“„«‰ ‘—Ê⁄:", lines[i++], PRN_NORM, ALIGN_RIGHT);
	sprintf(lines[i++], "%c%c%c%s       %s", PRN_NORM, ALIGN_CENTER, FARSI,
			startDateValueStr, startTimeValueStr);
#else
    justifyTwoStringFarsi("", "“„«‰ ‘—Ê⁄", lines[i++], PRN_NORM);
    sprintf(lines[i++], "%c%c%c%s%s%s", PRN_NORM, ALIGN_CENTER, FARSI, startDateValueStr,spaceCountStr, startTimeValueStr);
#endif
    
    /** LINE 2 : END DATE */
    sprintf(endDateValueStr, "%04d/%02d/%02d", yearTo, monthTo, dayTo);
    sprintf(endTimeValueStr, "%02d:%02d", hourTo, minuteTo);
#if defined(ICT250) || defined(IWL220)//HNO_ADD
    justifyOneStringFarsi("“„«‰ Å«Ì«‰:", lines[i++], PRN_NORM, ALIGN_RIGHT);
	sprintf(lines[i++], "%c%c%c%s       %s", PRN_NORM, ALIGN_CENTER, FARSI,endDateValueStr, endTimeValueStr);
#else
    justifyTwoStringFarsi("", "“„«‰ Å«Ì«‰", lines[i++], PRN_NORM);
    sprintf(lines[i++], "%c%c%c%s%s%s", PRN_NORM, ALIGN_CENTER, FARSI, endDateValueStr,spaceCountStr, endTimeValueStr);
#endif
    /** ACTIVE USER */
// mgh_93	if (getActiveUser(activeUser))
//    {
//	    justifyTwoStringFarsi("", activeUserTitle, lines[i++], PRN_NORM);
//	    sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, activeUser);
//    }
    
    /** LINE 3 : DASHES */
    justifyOneStringFarsi(DISPLAY_DASH, lines[i++], PRN_NORM, ALIGN_CENTER);
    *index = i;
}


void fillTransListCommonPartLines(uint8 lines[][32], uint16* index, uint8* amount, uint8* pan,
										uint8* referenceNum, uint32 stan, dateTimeST* dateTime, uint8* depositID)
{
	uint16			i							= *index;
	uint8			valueWithComma[20]			= {0};          /** value with comma */
	uint8           separatedStr[10][250]    	= {0, 0}; //ABS:CHANGE:960801
	uint8			maskedPAN[20]				= {0};
	uint8			transDateStr[11]			= {0};
	uint8			timeValueStr[6]         	= {0};
	uint8           loop                    	= 0; 
	uint8           wordWrapIndex           	= 0; 
	uint32			jalaliDate              	= 0;            /** jalali date */
	int				transYear               	= 0;
    int				transMonth              	= 0;
    int				transDay                	= 0;
    int				transHour               	= 0;
    int				transMinute             	= 0;
    uint8           spaceCountStr[50]           = {0};
    uint8           panOut[20]                  = {0};
    uint8           BIN[7]                      = {0};
	
    /** TRANSACTIONS LOG ; LINE 1 & 2: TRANSACTION VALUE */
    justifyTwoStringFarsi("", "„»·€", lines[i++], PRN_NORM);

    makeValueWithCommaStr(amount, valueWithComma); 
    
    //sprintf(lines[i++], "%c%c%c%s%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma, " —Ì«·");

    if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT - strlen(" —Ì«·"))
    {
        if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT)
        {
            loop = wordWrapEnglish(valueWithComma, separatedStr, DISPLAY_CHARACTER_COUNT);
            for (wordWrapIndex = 0; wordWrapIndex <= loop; wordWrapIndex++)
            {
                sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, separatedStr[wordWrapIndex]);
            }
        }
        else
        {
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma);
        }
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, "—Ì«·");
    }
    else
    {
        sprintf(lines[i++], "%c%c%c%s%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma, " —Ì«·");
    }
    
    strncpy(BIN, pan, 6);
    if (strcmp(BIN,SUPERVISOR_BIN) != 0)
    {
        /** TRANSACTIONS LOG ; LINE 3 & 4: TRANSACTION CARD NUMBER */
        justifyTwoStringFarsi("", "‘„«—Â ò«— ", lines[i++], PRN_NORM);
        //mgh: ?! maskCardId(pan, panOut); //ABS
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, pan);
    }
    
    /** TRANSACTIONS LOG ; LINE 5 & 6: TRANSACTION REFERENCE NUMBER */
    if (referenceNum)
        if (strlen(referenceNum) > 0)
        {
            justifyTwoStringFarsi("", "‘„«—Â „—Ã⁄", lines[i++], PRN_NORM);
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, referenceNum);
        }
    
    if (getPOSService().depositID)//MRF_NEW17
        if (strlen(depositID) > 0)
        {
            justifyTwoStringFarsi("", "‘‰«”Â Ê«—Ì“", lines[i++], PRN_NORM);
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, depositID);
        }
    
    if (stan > 0)
    {
	    justifyTwoStringFarsi("", "‘„«—Â ÅÌêÌ—Ì", lines[i++], PRN_NORM);
	    sprintf(lines[i++], "%c%c%c%ld", PRN_NORM, ALIGN_LEFT, FARSI, stan);
    }

    /** TRANSACTIONS LOG ; LINE 7 : TRANSACTION DATE AND TIME */
    gregorianToJalali(&jalaliDate, dateTime->date);
    transYear = getYear(jalaliDate);
    transMonth = getMonth(jalaliDate);
    transDay = getDay(jalaliDate);
		
    justifyTwoStringFarsi("", "“„«‰  —«ò‰‘", lines[i++], PRN_NORM);
    
    memset(spaceCountStr,' ', SPACE_COUNT);
    sprintf(transDateStr, "%04d/%02d/%02d", transYear, transMonth, transDay);
    transHour = getHour(dateTime->time);
    transMinute = getMinute(dateTime->time);
    sprintf(timeValueStr, "%02d:%02d", transHour, transMinute);
    sprintf(lines[i++], "%c%c%c%s%s%s", PRN_NORM, ALIGN_CENTER, FARSI, transDateStr,spaceCountStr, timeValueStr);
    
    /** TRANSACTIONS LOG ; LINE 8: DASHES */
    justifyOneStringFarsi(DISPLAY_DASH, lines[i++], PRN_NORM, ALIGN_CENTER);
    //-- sumValues += transactions[counter].amount;
    *index = i;
}


void fillTransListFooterLines(uint8 lines[][32], uint16* index, int transactionNumber, 
									uint8 displayCount, uint8* sumValue) 
{
	uint8			transNum[10]				= {0};          /** transactions number in dates, exist or listed */////ABS:CHANGE:960801
	uint8           separatedStr[10][250]    	= {0, 0}; //ABS:CHANGE:960801
	uint8           loop                    	= 0; 
	uint8           wordWrapIndex           	= 0; 
	uint16			i							= *index;
	uint8			valueWithComma[20]          = {0};          /** value with comma */
	
    makeValueWithCommaStr(sumValue, valueWithComma);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", valueWithComma);
    
	/** LINE (TRANSACTTIONS LOG + 4) : TRANSACTIONS NUMBER IN DATES */
    sprintf(transNum, "%d", transactionNumber);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", transNum);
    justifyTwoStringFarsi(transNum, " ⁄œ«œ", lines[i++], PRN_NORM);
    
    /** LINE (TRANSACTTIONS LOG + 5) : REQUESTED TRANSACTIONS */
    sprintf(transNum, "%ld", displayCount);
    justifyTwoStringFarsi(transNum, "·Ì”  ‘œÂ", lines[i++], PRN_NORM);
   
    /** LINE (TRANSACTIONS LOG + (6 & 7 & 8)) : SUM OF TRANSACTIONS VALUE */
    justifyTwoStringFarsi("", "„Ã„Ê⁄", lines[i++], PRN_NORM);

    if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT - strlen(" —Ì«·"))
    {
        if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT)
        {
            loop = wordWrapEnglish(valueWithComma, separatedStr, DISPLAY_CHARACTER_COUNT);
            for (wordWrapIndex = 0; wordWrapIndex <= loop; wordWrapIndex++)
            {
                sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, separatedStr[wordWrapIndex]);
            }
        }
        else
        {
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma);
        }
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, "—Ì«·");
    }
    else
    {
        sprintf(lines[i++], "%c%c%c%s%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma, " —Ì«·");
    }
    *index = i;
}


uint8 printTransactionListHeader(filesST* files, uint8* title, uint8* activeUserTitle, uint8* activeUser, 
		dateTimeST* startDateTime, dateTimeST* endDateTime)
{
    dateTimeST		dateTime;
    merchantSpecST  merchantSpec;
	
    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    memset(&dateTime, 0, sizeof(dateTimeST));
    
    if (!PrinterAccess(TRUE))    
           return FALSE;
    
   displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);
   
    /** PRINT HEADER */
    dateTime = getDateTime(); 
    if (!printReceiptHeader(&dateTime, TRUE, files)) 
        return FALSE;

    if (cancelFunction())
        return FALSE;

    /** PRINT TITLE */
    if (!printOneStringFarsi(title, PRN_NORM, ALIGN_CENTER))
        return FALSE;
 
    /** PRINT DATE AND TIME */
    if (!printReceiptDateTime(startDateTime, FALSE)) 
        return FALSE;
    
    if (cancelFunction())
        return FALSE;
    
    /** PRINT DATE AND TIME */
    if (!printReceiptDateTime(endDateTime, FALSE)) //MRF_NEW3
        return FALSE;
    
    if (cancelFunction())
        return FALSE;
    
    /** PRINT TERMINAL ID */
    if (readMerchantSpec(files, &merchantSpec))
    {
        if (!printTwoStringNumericFarsi(merchantSpec.terminalID, "‘„«—Â Å«Ì«‰Â", PRN_NORM))
            return FALSE;
    }
    
    /** PRINT DASHES */
    if (!printStar())
        return FALSE;

    if (cancelFunction())
        return FALSE;
    
    return TRUE;
}


uint8 printTransactionListCommonPart(uint8* amount, uint8* pan, uint8* referenceNum, uint32 stan, dateTimeST* dateTime, uint8* depositID)
{
    uint8	valueWithComma[40]		= {0};			/** value with comma, string form */
    uint8   timeStr[100]            = {0};
    uint8	stanStr[8 + 1]			= {0};
    
     
    makeValueWithCommaStr(amount, valueWithComma);
	
    /** PRINT REFERENCE NUMBER */
    if (referenceNum)
    {
        removePad(referenceNum, ' ');
        if (strlen(referenceNum) > 0)
        {
#ifdef VX520  //ABS:ADD
			if (!printTwoStringNumericFarsi(referenceNum, "‘„«—Â „—Ã⁄", PRN_NORM))
				return FALSE;
#else
			strcat(referenceNum, "|");
			if (!printTwoStringNumericFarsi(referenceNum, "|‘„«—Â „—Ã⁄", PRN_NORM))
				return FALSE;
#endif
        }
    }
    
     if (getPOSService().depositID)
        if (strlen(depositID) > 0)
        {
#ifdef VX520
			if (!printTwoStringNumericFarsi(depositID, "‘‰«”Â Ê«—Ì“", PRN_NORM))
				return FALSE;
#else
            strcat(depositID, "|");
			if (!printTwoStringNumericFarsi(depositID, "|‘‰«”Â Ê«—Ì“", PRN_NORM))
				return FALSE;
#endif
        }
    
    if (stan > 0)
    {
#ifdef VX520
		sprintf(stanStr, "%ld", stan);
		if (!printTwoStringNumericFarsi(stanStr, "‘„«—Â ÅÌêÌ—Ì", PRN_NORM))
			return FALSE;
#else
		sprintf(stanStr, "%ld|", stan);
		if (!printTwoStringNumericFarsi(stanStr, "|‘„«—Â ÅÌêÌ—Ì", PRN_NORM))
			return FALSE;
#endif
    }
    
    /** PRINT AMOUNT & DATE */
    setTimeForPrint(dateTime, timeStr);
#ifdef VX520
	strcat(timeStr, " —Ì«·");
	printTwoStringFarsi(timeStr,valueWithComma, PRN_NORM);
#else
	strcat(valueWithComma, "—Ì«·|");
	printTwoStringFarsi(valueWithComma, timeStr, PRN_NORM);
#endif
    
   
    return TRUE;
}

uint8 printTransactionListFooter(int transactionNumber, uint32 requestedNum, uint8* sumValues)
{
	uint8			transNum[10]				= {0};          /** transactions number in dates, exist or listed */
	uint8           amountPrintBuffer[20]   	= {0}; 
	uint8			valueWithComma[20]			= {0};          /** value with comma */
	
	makeValueWithCommaStr(sumValues, valueWithComma);
    
	/** PRINT TRANSACTIONS NUMBER IN DATES */
    sprintf(transNum, "%d", transactionNumber);
    if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
        return FALSE;
    
    if (cancelFunction())
        return FALSE;
    
    /** PRINT REQUESTED TRANSACTIONS NUMBER */
    sprintf(transNum, "%ld", requestedNum);
    if (!printTwoStringNumericFarsi(transNum, "·Ì”  ‘œÂ", PRN_NORM))
        return FALSE;

    if (cancelFunction())
        return FALSE;
    
    /** PRINT TRANSACTIONS VALUE */
//     if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "Ã„⁄ ò·", PRN_NORM, ALIGN_RIGHT, TRUE))
//         return FALSE;
    
    if (!printOneStringFarsi("„Ã„Ê⁄:", PRN_NORM, ALIGN_RIGHT)) //MRF_OPTIMIZE :THIS AND UNDER PART SHOUD BE COMMENT
        return FALSE;
    
    sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma); 
    if (!printOneStringFarsi(amountPrintBuffer, PRN_BIG, ALIGN_CENTER))
        return FALSE;

    /** PRINT EMPTY LINES */
   printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}


uint8 displayTransactionBuyList(buyTransLogST* transactions, int transactionNumber, uint32 requestedNum, uint8* title,
		dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]			= {0, 0};		//HNO:change 700 to 3500 & 3 to 4 line for footer /** 3: fot the last three lines */
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};      	/** sum of listed transactions value */
	int				counter                 	= 0;            /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();

	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Request: %d", requestedNum);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "transactions: %d", transactionNumber);
    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0 ; counter--) 
    {
    	//mgh: adding two string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if ( i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 8)) //6: header, 4: footer, 8: body 
    	{
	    	fillTransListCommonPartLines(lines, &i, transactions[counter].amount, transactions[counter].PAN,
	    			transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime) , transactions[counter].depositID); //MRF_NEW17
	    	displayedCount++;
	    	strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sum %s", sumValues);
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    
    if (!terminalCapability.graphicCapability) //MRF_IDENT
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader(title, lines, i, DISPLAY_TIMEOUT, FALSE,buyTransPic);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}


uint8 transactionBuyList(argumentListST* args)
{    
    filesST*        files                                       = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    buyTransLogST   transactions[MAX_BUY_TRANS_LOG_RECORDS] 	= {0};
    int				transactionNumber                           = 0;            /** charge number with specified date in file */
    int				counter                                     = 0;            /** loop counter */
    uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
    uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
    uint8			fileName[FILE_NAME_LENTGH]                  = {0};
    uint8			activeUser[15 + 1]                          = {0};
    uint8			title[30]                                   = {0};
    uint8			activeUserTitle[15 + 1]                     = {0};
    uint8           check                                       = FALSE;
    uint8           sumDailyValues[15 + 1]                      = {0};
    uint8			tempSumValues[15 + 1]                       = {0}; 
    uint8			valueWithComma[20]                          = {0}; 
    uint8   		amountPrintBuffer[20]   					= {0};
    uint8			selectUser[16]								= {0};
    uint8           shift[22]           						= {0};
	uint8           loginUserName[15 + 1] = { 0 }; //ABS:ADD

    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "*********transactionBuyList********");
    strcpy(fileName, BUY_LOG_FILE);

	if(getPOSService().shiftService == TRUE)//HNO_SHIFT
	{
		getLoginUser(loginUserName);	//ABS:ADD
		if (strcmp("„œÌ—", loginUserName) == 0)//HNO_IDENT9 //admin can see all users report
		{
			if (!displayUsersList(selectUser, FALSE))//ABS
			return FALSE;
			if(strcmp("„œÌ—", selectUser) != 0)//HNO_SHIFT10
				strcat(fileName, selectUser);
		}
		else
		{
			strcat(fileName, loginUserName);//ABS:ADD
			strcpy(selectUser, loginUserName);//ABS:ADD
		}
	}

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "fileName: %s", fileName);
    
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ Œ—Ìœ");

    if (!readTransactionListFile(fileName, transactions, sizeof(buyTransLogST), MAX_BUY_TRANS_LOG_RECORDS, 
    						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
    
    
    if (!displayTransactionBuyList(transactions, transactionNumber, requestedNum, "Œ—Ìœ „Ê›ﬁ", &startDateTime,
    		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
    	return FALSE;
    
    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    /** PRINT TRANSACTIONS DETAILS */
    if (! printReceiptDate(transactions[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;
    
   if(getPOSService().shiftService == TRUE)//HNO_SHIFT3
   {
	   strcpy(shift, "‘Ì›  ");
	   strcat(shift, selectUser);
	   printTwoStringFarsi(shift, "‘„«—Â ‘Ì› :", PRN_NORM);//HNO_SHIFT
   }
    
    printDash3();
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {   
        if (check != 0)
        {
           if (!printReceiptDate(transactions[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }
        
        if (!printTransactionListCommonPart(transactions[counter].amount, transactions[counter].PAN, 
                    transactions[counter].retrievalReferenceNumber, 0, 
                &(transactions[counter].dateTime), transactions[counter].depositID))//MRF_NEW17
            return FALSE;

        check = compareDates(&transactions[counter].dateTime, &transactions[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumDailyValues);
        
        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();
        
        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);
            
            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;
            
            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }
        
        if (cancelFunction())
            return FALSE;
    }
    
    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;
    
    return TRUE;
}

uint8 displayTransactionBillPayList(billPayTransLogST* transactions, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]			= {0, 0};	//HNO:change 700 to 3500 &3 to 4 for header	/** 3: fot the last three lines */
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};      	/** sum of listed transactions value */
	int				counter                 	= 0;            /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	uint8			shGabzValue[18]				= {0};
	uint8			shPardakhtValue[14]			= {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();
    uint8           depositID[11 + 1]           = {0};//MRF_NEW17 //ABS_NEW1
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].billAmount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);

        if (i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 12)) //6: header, 4: footer, 12: body
    	{
	    	/** TRANSACTIONS LOG ; LINE 1: TRANSACTION BILL ID */
	    	memcpy(shGabzValue, transactions[counter].billID, 13);
		    shGabzValue[13] = 0;
		    removePadLeft(shGabzValue,'0');
		    
		    justifyTwoStringFarsi("", "‘‰«”Â ﬁ»÷", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, shGabzValue);
		            
	        /** TRANSACTIONS LOG ; LINE 2: TRANSACTION PAYEMNT ID */
	        memcpy(shPardakhtValue, transactions[counter].paymentID, 13);
		    shPardakhtValue[13] = 0;
		    removePadLeft(shPardakhtValue, '0');  
	        
	    	justifyTwoStringFarsi("", "‘‰«”Â Å—œ«Œ ", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, shPardakhtValue);
	
	        fillTransListCommonPartLines(lines, &i, transactions[counter].billAmount, transactions[counter].PAN,
	        		transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime), depositID); //MRF_NEW17
	        
	        displayedCount++;
	        strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    
    if (!terminalCapability.graphicCapability) //MRF_IDENT
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE, billTransPic);
    
	if (key != KBD_ENTER && key != KBD_CONFIRM) 
        return FALSE;
	else
		return TRUE;
}

//HNO
uint8 displayTransactionLoanPayList(loanPayTransLogST* loanPay, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]			= {0, 0};	//HNO:change 700 to 3500 &3 to 4 for header	/** 3: fot the last three lines */
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};      	/** sum of listed transactions value */
	int				counter                 	= 0;            /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	uint8			destinationCard[16]         = {0};
	uint8			nameStr[20]                 = {0};
    uint8			familyStr[20]               = {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();
    uint8          depositID[11 + 1]           = {0};//MRF_NEW17  //ABS_NEW1
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, loanPay[counter].amount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);

        if (i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 12)) //6: header, 4: footer, 12: body
    	{
	    	/** TRANSACTIONS LOG ; LINE 1: TRANSACTION loan pan */
	    	memcpy(destinationCard, loanPay[counter].destinationCardPAN, 16);
		    destinationCard[16] = 0;
		    removePadLeft(destinationCard,'0');
       
		    justifyTwoStringFarsi("", "‘„«—Â ò«—  ﬁ”ÿ", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, destinationCard);
		            
	        /** TRANSACTIONS LOG ; LINE 2: TRANSACTION card holder name */
	        memcpy(nameStr, loanPay[counter].destinationCardHolderName, strlen(loanPay[counter].destinationCardHolderName));
            memcpy(familyStr, loanPay[counter].destinationCardHolderFamily, strlen(loanPay[counter].destinationCardHolderFamily));
            strcat(nameStr," ");
            strcat(nameStr,familyStr);
	        
	    	justifyTwoStringFarsi("", "»Â ‰«„", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, nameStr);
            memset(nameStr,0,sizeof(nameStr));
	
	        fillTransListCommonPartLines(lines, &i, loanPay[counter].amount, loanPay[counter].PAN,
	        		loanPay[counter].retrievalReferenceNumber, 0, 
                    &(loanPay[counter].dateTime), depositID); //MRF_NEW17
	        
	        displayedCount++;
	        strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    if (!terminalCapability.graphicCapability) //MRF_IDENT
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE, sucessLoanPay);
    
	if (key != KBD_ENTER && key != KBD_CONFIRM) 
        return FALSE;
	else
		return TRUE;
}


uint8 transactionBillPayList(argumentListST* args)
{    
    filesST*        	files                                             = (filesST*) (args->argumentName);
    dateTimeST			startDateTime                                     = {0, 0};
    dateTimeST			endDateTime                                       = {0, 0};
    billPayTransLogST   transactions[MAX_BILL_PAY_TRANS_LOG_RECORDS]      = {0};
    int					transactionNumber                                 = 0;    /** charge number with specified date in file */
    int					counter                                           = 0;    /** loop counter */
    uint32				requestedNum                                      = 0;    /** user requested transaction number, integer form */
    uint8				shGabzValue[15]                                   = {0};
    uint8				shPardakhtValue[14]                               = {0};
    uint8               sumValues[15 + 1]                                 = {0}; 
    uint8				fileName[FILE_NAME_LENTGH]                        = {0};
    uint8				activeUser[15 + 1]                                = {0};
    uint8				activeUserTitle[15 + 1]                           = {0};
    uint8				title[30]                                         = {0};
    uint8               check                                             = FALSE;
    uint8               sumDailyValues[15 + 1]                            = {0};
    uint8               tempSumValues[15 + 1]                             = {0}; 
    uint8               valueWithComma[20]                                = {0}; 
    uint8               depositID[11 + 1]                                 = {0};

    strcpy(fileName, BILL_PAY_LOG_FILE);
    
    if (!readTransactionListFile(fileName, transactions, sizeof(billPayTransLogST), MAX_BILL_PAY_TRANS_LOG_RECORDS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
        
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ ﬁ»÷");

    if (!displayTransactionBillPayList(transactions, transactionNumber, requestedNum, "ﬁ»÷ „Ê›ﬁ", &startDateTime,
                		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
        	return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;
    
    if (! printReceiptDate(transactions[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;
    
    printDash3();
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(transactions[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }
        
    	/** PRINT BiLL ID */
        memset(shGabzValue, 0, sizeof(shGabzValue));
	    strncat(shGabzValue, transactions[counter].billID, 13);
#ifdef VX520		
		//strcat(shGabzValue, "|");//ABS:COMMENT
		shGabzValue[14] = 0;
		removePadLeft(shGabzValue, '0');
		if (!printTwoStringNumericFarsi(shGabzValue, "‘‰«”Â ﬁ»÷", PRN_NORM))//ABS:CHANGE
			return FALSE;

		/** PRINT PAYMENT ID */
		memset(shPardakhtValue, 0, sizeof(shPardakhtValue)); 
		strncat(shPardakhtValue, transactions[counter].paymentID, 13);
		//strcat(shPardakhtValue, "|"); //ABS:COMMENT
		shGabzValue[14] = 0;
		removePadLeft(shPardakhtValue, '0');
		if (!printTwoStringNumericFarsi(shPardakhtValue, "‘‰«”Â Å—œ«Œ ", PRN_NORM))	//ABS:CHANGE
			return FALSE;
#else
        strcat(shGabzValue, "|");
	    shGabzValue[14] = 0;
	    removePadLeft(shGabzValue,'0');
	    if (!printTwoStringNumericFarsi(shGabzValue, "|‘‰«”Â ﬁ»÷", PRN_NORM))
	        return FALSE;
	    
	    /** PRINT PAYMENT ID */
        memset(shPardakhtValue, 0, sizeof(shPardakhtValue));
	    strncat(shPardakhtValue, transactions[counter].paymentID, 13);
        strcat(shPardakhtValue, "|");
	    shGabzValue[14] = 0;
	    removePadLeft(shPardakhtValue,'0');
	    if (!printTwoStringNumericFarsi(shPardakhtValue, "|‘‰«”Â Å—œ«Œ ", PRN_NORM))
	        return FALSE;
#endif
	    
    	if (!printTransactionListCommonPart(transactions[counter].billAmount, transactions[counter].PAN, 
    			transactions[counter].retrievalReferenceNumber, 0, &(transactions[counter].dateTime), depositID))//MRF_NEW17
    		return FALSE;
        
        check = compareDates(&transactions[counter].dateTime, &transactions[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, transactions[counter].billAmount, sumDailyValues);
        
        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();
        
        if (check != 0)
         {
             makeValueWithCommaStr(sumDailyValues, valueWithComma);

             if (!printThreeStringFarsi("—Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                 return FALSE;

             printStar();
             memset(sumDailyValues, 0, sizeof(sumDailyValues));
         }
        
        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}

//transactionNumber
uint8 displayTransactionErrorList(transErrorST* errors, int errorNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser)
{
	int				counter                                          = 0;            
	int				errorYear                                        = 0;
    int				errorMonth                                       = 0; 
    int				errorDay                                         = 0;
    int				errorHour                                        = 0;
    int				errorMinute                                      = 0; 
    uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 4][32]  = {0,0};
	uint16  		i                                                = 0;
    uint32			jalaliDate                                       = 0;  
    uint8			key                                              = KBD_CANCEL;
	uint8			displayedCount                                   = 0;  
    uint8			dateValueStr[18]                                 = {0};
    uint8			timeValueStr[6]                                  = {0};
    uint8			transType[20]                                    = {0};
    uint8			errorCode[11]                                    = {0};
    uint8			errorsNum[10]                                    = {0};
    uint8           spaceCountStr[10]                                = {0};
	terminalSpecST  terminalCapability                               = getTerminalCapability();
    
    memset(lines, 0, sizeof(lines));
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**displayTransactionErrorList**");
    
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	
    /** ERRORS LOG */
    for (counter = requestedNum - 1; counter >= 0 && (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 8)); counter--) // change 2 to 4 and 5 line for body to 8
    {
        /** ERRORS LOG ; LINE 1 & 2: ERROR DATE AND TIME */
        gregorianToJalali(&jalaliDate , errors[counter].dateTime.date);
        
        errorYear = getYear(jalaliDate);
        errorMonth = getMonth(jalaliDate);
        errorDay = getDay(jalaliDate);
        errorHour = getHour(errors[counter].dateTime.time);
        errorMinute = getMinute(errors[counter].dateTime.time);
        
        /** ERRORS LOG ; LINE 3: ERROR TRANSACTION TYPE */
        memset(transType, 0, sizeof(transType));
        getIsoTransactionName(transType, errors[counter].transType);
        justifyTwoStringFarsi("", "‰Ê⁄  —«ò‰‘", lines[i++], PRN_NORM);
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, transType);
        
        /** ERRORS LOG ; LINE 4: ERROR CODE */
        sprintf(errorCode, "%d", errors[counter].errorCode);
        justifyTwoStringFarsi(errorCode, "Œÿ«Ì", lines[i++], PRN_NORM);
        
        /** ERRORS LOG ; LINE 5 & 6: ERROR MESSAGE & DASHES */
        memset(spaceCountStr,' ', SPACE_COUNT);
        sprintf(dateValueStr, "%04d/%02d/%02d", errorYear, errorMonth, errorDay);
        sprintf(timeValueStr, "%02d:%02d", errorHour, errorMinute);
        sprintf(lines[i++], "%c%c%c%s%s%s", PRN_NORM, ALIGN_CENTER, FARSI, dateValueStr, spaceCountStr, timeValueStr);
        justifyOneStringFarsi(DISPLAY_DASH, lines[i++], PRN_NORM, ALIGN_CENTER);
        displayedCount++;
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
   		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
   		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
   	}
    
    /** LINE (ERRORS LOG + 4) : ERRORS NUMBER IN DATES */
    sprintf(errorsNum, "%d", errorNumber);
    justifyTwoStringFarsi(errorsNum, " ⁄œ«œ", lines[i++], PRN_NORM);
    
    /** LINE (ERRORS LOG + 5) : REQUESTED ERRORS */
    sprintf(errorsNum, "%d", displayedCount);
    justifyTwoStringFarsi(errorsNum, "·Ì”  ‘œÂ", lines[i++], PRN_NORM);
    
    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE,bankingErrors);
    
    if (key != KBD_ENTER && key != KBD_CONFIRM) 
        return FALSE;
    else
    	return TRUE;
}


/**
 * display & print transactions error report.
 * @param   known known or unknown error?
 * @see     searchDateRangeInFixedFile()
 * @see     readFixedFileInfoArray()
 * @see     displayScrollable()
 * @see     printLogo()
 * @see     printReceiptDateTime()
 */
uint8 transactionsErrorList(argumentListST* args)
{
    filesST*        files                                   = (filesST*) (args->argumentName);
    uint8			fileName[FILE_NAME_LENTGH]              = {0};				/** transactions error file name */
    dateTimeST		startDateTime                           = {0, 0};
    dateTimeST		endDateTime                             = {0, 0};
    int				errorNumber                             = 0;				/** errors number with specified date in file */
    int				counter                                 = 0;				//mgh int -> uint16			/** loop counter */
    uint32  		requestedNum                            = 0;				/** user requested errors number, integer form */
    uint8			errorsNum[10]                           = {0};				/** errors number in dates, exist or listed */
    uint8			printStr[100]                           = {0};				/** print styring */
    uint8			transType[10]                           = {0};				//Length of array must be 10 : MRF_NEW10
    uint8			errorCode[11]                           = {0};
    uint8			tmp                                     = 0;				/** temp needed argument */
    uint8			activeUser[15 + 1]                      = {0};
    uint8			activeUserTitle[15 + 1]                 = {0};
    uint8			title[30]                               = {0};
    transErrorST    errors[MAX_TRANS_ERROR_LOG_RECORDS]     = {0};
    merchantSpecST  merchantSpec;
    dateTimeST      dateTime;
    
    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    memset(&dateTime, 0, sizeof(dateTimeST));
    memset(errors, 0, sizeof(errors)); 

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****transactionsErrorList****");
    strcpy(fileName, TRANS_ERROR_LOG_FILE);
    
    if (!readTransactionListFile(fileName, errors, sizeof(transErrorST), MAX_TRANS_ERROR_LOG_RECORDS, 
            						&startDateTime, &endDateTime, &errorNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
    
    strcpy(title,"Œÿ«Â«Ì »«‰ﬂÌ");

    if (!displayTransactionErrorList(errors, errorNumber, requestedNum, title, &startDateTime,
                   		&endDateTime, activeUserTitle, activeUser))
    {
       	return FALSE;
    }
    
    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    {
    	return FALSE;
    }
	
    /** PRINT ERRORS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        /** PRINT ERROR TRANSACTION TYPE */
        memset(transType, 0, sizeof(transType));
        getIsoTransactionName(transType, errors[counter].transType);

        if (cancelFunction())
            return FALSE;
    
        /** PRINT ERROR CODE */
        memset(errorCode, 0, sizeof(errorCode));
        sprintf(errorCode, "%d", errors[counter].errorCode);

#ifdef VX520
		if (!printTwoStringNumericFarsi(errorCode, transType, PRN_NORM))
			return FALSE;
#else
		if (!printTwoStringFarsi(errorCode, transType, PRN_NORM))
            return FALSE;
#endif	
        if (cancelFunction())
            return FALSE;
    
        /** PRINT ERROR MESSAGE */
        getIsoErrorMessage(printStr, errors[counter].errorCode, &tmp);
        
        if (!printOneStringFarsi(printStr, PRN_NORM, ALIGN_RIGHT))
        	return FALSE;
        
        if (cancelFunction())
            return FALSE;
    
        if (!printReceiptDateTime(&errors[counter].dateTime, TRUE))
            return FALSE;
        
        if (cancelFunction())
            return FALSE;

        if (!printDash())
            return FALSE;
    }

    /** PRINT ERRORS NUMBER IN DATES */
    sprintf(errorsNum, "%ld", errorNumber);
    if (!printTwoStringNumericFarsi(errorsNum, " ⁄œ«œ", PRN_NORM))
        return FALSE;

    if (cancelFunction())
        return FALSE;
    
    /** PRINT REQUESTED ERRORS NUMBER */
    sprintf(errorsNum, "%ld", requestedNum);
    if (!printTwoStringNumericFarsi(errorsNum, "·Ì”  ‘œÂ", PRN_NORM))
        return FALSE;

    /** PRINT EMPTY LINES */
    printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}

uint8 displayunsuccessBuyTransaction(reversalTransST* reversalInfo, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 4][32]	= {0, 0};
	uint16  		i                       						= 0;
	uint8			tempSumValues[15 + 1]   						= {0};                          /** sum of listed transactions value */
	int				counter                 						= 0;                            /** loop counter */
	uint8			key 											= KBD_CANCEL;
	uint8			displayedCount          						= 0;                            /** display counter */
	uint8			displayedSumValues[15 + 1]						= {0};
	uint8			referenceNum[1]									= {0};
	terminalSpecST  terminalCapability								= getTerminalCapability();
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 8))
    	{
            
            fillTransListCommonPartLines(lines, &i, reversalInfo[counter].amount, reversalInfo[counter].PAN, 
    				referenceNum, reversalInfo[counter].STAN,
                    /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
                    &(reversalInfo[counter].SWdateTime), reversalInfo[counter].depositID); //MRF_NEW17
                    
    		displayedCount++;
    		strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
	}
 
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);

    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE,buyUnsuccessTransPic);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else 
    	return TRUE;
}


uint8 displayunsuccessBillPayTransaction(reversalTransST* reversalInfo, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 4][32]		= {0, 0};		//HNO:change 400 to 2000 and 3 to 4 for footer /** 3: fot the last three lines */
	uint16  		i                       							= 0;
	uint8			tempSumValues[15 + 1]   							= {0};       	/** sum of listed transactions value */
	int				counter                 							= 0;            /** loop counter */
	uint8			key 												= KBD_CANCEL;
	uint8			displayedCount          							= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]							= {0};
	uint8			referenceNum[1]										= {0};
    uint8			shGabzValue[18]										= {0};
	uint8			shPardakhtValue[14]									= {0};
	terminalSpecST  terminalCapability									= getTerminalCapability();
    uint8          depositID[11 + 1]                                   = {0};
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].billSpec.billAmount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 12))//6 for header,4 for footer and 12 for body
    	{
            /** TRANSACTIONS LOG ; LINE 1: TRANSACTION BILL ID */
	    	memcpy(shGabzValue, reversalInfo[counter].billSpec.billID, 13);
		    shGabzValue[13] = 0;
		    removePadLeft(shGabzValue,'0');
		    
		    justifyTwoStringFarsi("", "‘‰«”Â ﬁ»÷", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, shGabzValue);
		            
	        /** TRANSACTIONS LOG ; LINE 2: TRANSACTION PAYEMNT ID */
	        memcpy(shPardakhtValue, reversalInfo[counter].billSpec.paymentID, 13);
		    shPardakhtValue[13] = 0;
		    removePadLeft(shPardakhtValue, '0');  
	        
	    	justifyTwoStringFarsi("", "‘‰«”Â Å—œ«Œ ", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, shPardakhtValue);
            
    		fillTransListCommonPartLines(lines, &i, reversalInfo[counter].billSpec.billAmount, reversalInfo[counter].PAN, 
    				referenceNum, reversalInfo[counter].STAN, 
                    /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
                    &(reversalInfo[counter].SWdateTime), depositID);
    		displayedCount++;
    		strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
	}
 
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    
    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
	else
		key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE,unsuccessBillPic);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else 
    	return TRUE;
}



uint8 unsuccessBuyTransaction(argumentListST* args)
{    
    filesST*        			files                                 = (filesST*) (args->argumentName);
    dateTimeST					startDateTime                         = {0, 0};
    dateTimeST					endDateTime                           = {0, 0};
    reversalTransST				reversalInfo[MAX_UNSUCCESS_BUY_TRANS] = {0};
    int							transactionNumber					  = 0;            /** charge number with specified date in file */
    int							counter                 			  = 0;            /** loop counter */
    uint32						requestedNum						  = 0;            /** user requested transaction number, integer form */
    uint8						sumValues[15 + 1]       			  = {0};          /** sum of listed transactions value */
    uint8						fileName[FILE_NAME_LENTGH]			  = {0};
    uint8						activeUser[15 + 1]					  = {0};
    uint8						activeUserTitle[15 + 1]				  = {0};
    uint8						title[30]                   		  = {0};
    uint8						referenceNum[1]						  = {0};
    uint8                       check                       		  = FALSE;
    uint8                       sumDailyValues[15 + 1]      		  = {0};
    uint8                       tempSumValues[15 + 1]       		  = {0}; 
    uint8                       valueWithComma[20]          		  = {0}; 
    uint8						selectUser[16]						  = {0};
    uint8						shift[22]							  = {0};
	uint8						loginUserName[15 + 1]				  = { 0 };

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****unsuccessBUY****");
    
    strcpy(fileName, REVERSAL_BUY_LOG_FILE);
    
	if(getPOSService().shiftService == TRUE)
	{
		getLoginUser(loginUserName);
		if (strcmp("„œÌ—", loginUserName) == 0)//admin can see all users report
		{
			if (!displayUsersList(selectUser, FALSE))
			return FALSE;
			if(strcmp("„œÌ—", selectUser) != 0)
				strcat(fileName, selectUser);
		}
		else
		{
			strcat(fileName, loginUserName);
			strcpy(selectUser, loginUserName);
		}
	}

    if (!readTransactionListFile(fileName, reversalInfo, sizeof(reversalTransST), MAX_UNSUCCESS_BUY_TRANS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    strcpy(title, "—Ì“ —«ò‰‘ ‰«„Ê›ﬁ Œ—Ìœ");
    if (!displayunsuccessBuyTransaction(reversalInfo, transactionNumber, requestedNum, "Œ—Ìœ ‰«„Ê›ﬁ", &startDateTime,
                   		&endDateTime, activeUserTitle, activeUser, sumValues))
        	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    if (!printReceiptDate(reversalInfo[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;

    if(getPOSService().shiftService == TRUE)
    {
		strcpy(shift, "‘Ì›  ");
		strcat(shift, selectUser);
		printTwoStringFarsi(shift, "‘„«—Â ‘Ì› :", PRN_NORM);
    }

    printDash3();
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(reversalInfo[counter].dateTime.date," «—ÌŒ"))
               return FALSE;

           printDash3();
        }
        
    	if (!printTransactionListCommonPart(reversalInfo[counter].amount, 
				reversalInfo[counter].PAN, referenceNum, 
    			reversalInfo[counter].STAN,
				/*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
				&(reversalInfo[counter].SWdateTime), reversalInfo[counter].depositID))
    		return FALSE;

        check = compareDates(&reversalInfo[counter].dateTime, &reversalInfo[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumDailyValues);
        
        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();
        
        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);

            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }
        
        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


uint8 unsuccessBillPayTransaction(argumentListST* args)
{    
	filesST*        			files                   				  = (filesST*) (args->argumentName);
    dateTimeST					startDateTime                             = {0, 0};
    dateTimeST					endDateTime                               = {0, 0};
    reversalTransST				reversalInfo[MAX_UNSUCCESS_BILLPAY_TRANS] = {0};
    int							transactionNumber						  = 0;                /** charge number with specified date in file */
    int							counter                 				  = 0;                /** loop counter */
    uint32						requestedNum							  = 0;                /** user requested transaction number, integer form */
    uint8						sumValues[15 + 1]       				  = {0};              /** sum of listed transactions value */
    uint8						fileName[FILE_NAME_LENTGH]				  = {0};
    uint8						activeUser[15 + 1]						  = {0};
    uint8						activeUserTitle[15 + 1]					  = {0};
    uint8						title[30]                   			  = {0};
    uint8						referenceNum[1]							  = {0};
    uint8                       check                       			  = FALSE;
    uint8                       sumDailyValues[15 + 1]      			  = {0};
    uint8                       tempSumValues[15 + 1]       			  = {0}; 
    uint8                       valueWithComma[20]          			  = {0};
    uint8                       depositID[11 + 1]           			  = {0};


	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****unsuccessBillPayTransaction****");
    strcpy(fileName, REVERSAL_BILLPAY_LOG_FILE);
    
    if (!readTransactionListFile(fileName, reversalInfo, sizeof(reversalTransST), MAX_UNSUCCESS_BILLPAY_TRANS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    strcpy(title, "—Ì“ —«ò‰‘ ‰«„Ê›ﬁ ﬁ»÷");
    if (!displayunsuccessBillPayTransaction(reversalInfo, transactionNumber, requestedNum, "ﬁ»÷ ‰«„Ê›ﬁ", &startDateTime,
                   		&endDateTime, activeUserTitle, activeUser, sumValues))
           	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    if (!printReceiptDate(reversalInfo[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;
    
    printDash3();
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(reversalInfo[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }
        
    	if (!printTransactionListCommonPart(reversalInfo[counter].billSpec.billAmount,
				reversalInfo[counter].PAN, referenceNum, 
    			reversalInfo[counter].STAN,
				/*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/&(reversalInfo[counter].SWdateTime), depositID))//MRF_NEW17
    		return FALSE;
        
        check = compareDates(&reversalInfo[counter].dateTime, &reversalInfo[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumDailyValues);
        
        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();
        
        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);

            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }

        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


//delete all user dependant files, such as transaction list files
void deleteDependantFiles(uint8 index)
{
	uint8 	userIndex[4]               = {0};
	uint8	fileName[FILE_NAME_LENTGH] = {0};
	
	sprintf(userIndex, "%d", index);
	
	strcpy(fileName, CHARGE_LOG_FILE);
	strcat(fileName, userIndex);
	fileRemove(fileName);
	
	strcpy(fileName, BILL_PAY_LOG_FILE);
	strcat(fileName, userIndex);
	fileRemove(fileName);
	
	strcpy(fileName, BUY_LOG_FILE);
	strcat(fileName, userIndex);
	fileRemove(fileName);
    
    //MRF
    strcpy(fileName, SUPERVISOR_LOG_FILE);
	strcat(fileName, userIndex);
	fileRemove(fileName);
}

void getIssuerBankName(uint8* BINstr, uint8* Name)
{
	int32			BIN;
	
    BIN = strToInt(BINstr);//ABS:CHANGE:960801
    switch(BIN)
    {
        case 627961:
            strcpy(Name, "’‰⁄  Ê „⁄œ‰");
            break;
        case 610433:
            strcpy(Name, "„· ");
            break;
        case 589463:
            strcpy(Name, "—›«Â ò«—ê—«‰");
            break;
        case 628023:
            strcpy(Name, "„”ò‰");
            break;
        case 589210:
        case 604932:
            strcpy(Name, "”ÅÂ");
            break;
        case 603770:
            strcpy(Name, "ò‘«Ê—“Ì");
            break;
        case 603799:
            strcpy(Name, "„·Ì");
            break;
        case 627353:
        case 585983:
            strcpy(Name, " Ã«— ");
            break;
        case 603769:
            strcpy(Name, "’«œ—« ");
            break;
        case 627648:
            strcpy(Name, " Ê”⁄Â ’«œ—« ");
            break;
        case 627760:
            strcpy(Name, "Å”  »«‰ò");
            break;
        case 502908:
            strcpy(Name, " Ê”⁄Â  ⁄«Ê‰");
            break;
        case 628157:
//            strcpy(Name, "„Ê””Â «⁄ »«—Ì  Ê”⁄Â");//-MRF_971017
            strcpy(Name, " Ê”⁄Â");
            break;
        case 627488:
            strcpy(Name, "ò«—¬›—Ì‰");
            break;
        case 622106:
            strcpy(Name, "Å«—”Ì«‰");
            break;
        case 627412:
            strcpy(Name, "«ﬁ ’«œ ‰ÊÌ‰");
            break;
        case 621986:
            strcpy(Name, "”«„«‰");
            break;
        case 502229:
            strcpy(Name, "Å«”«—ê«œ");
            break;
        case 639607:
            strcpy(Name, "”—„«ÌÂ");
            break;
        case 639346:
            strcpy(Name, "”Ì‰«");
            break;
        case 606373:
//            strcpy(Name, "ﬁ—÷ «·Õ”‰Â „Â— «Ì—«‰");//-MRF_971017
            strcpy(Name, "„Â— «Ì—«‰");
            break;
        case 504706:
            strcpy(Name, "‘Â—");
            break;
        case 636214:
            strcpy(Name, "¬Ì‰œÂ");
            break;
        case 627381:
            strcpy(Name, "«‰’«—");
            break;
        case 505416:
            strcpy(Name, "ê—œ‘ê—Ì");
            break;
        case 636949:
            strcpy(Name, "«Ì—«‰Ì«‰");
            break;
        case 502938:
            strcpy(Name, "œÌ");
            break;
        case 505785:
            strcpy(Name, "«Ì—«‰ “„Ì‰");
            break;
        case 504172:
            strcpy(Name, "—”«· ");
            break;
        case 505809:
            strcpy(Name, "Œ«Ê—„Ì«‰Â");
            break;
        case 585947:
            strcpy(Name, "Œ«Ê—„Ì«‰Â");
            break;
        case 639599:
            strcpy(Name, "ﬁÊ«„Ì‰");
            break;
        case 505801:
//            strcpy(Name,"„Ê””Â „«·Ì Ê «⁄ »«—Ì òÊÀ—");//-MRF_971017
            strcpy(Name,"òÊÀ—");
            break;
        case 606256:
//            strcpy(Name, "„Ê””Â „«·Ì Ê «⁄ »«—Ì ⁄”ò—ÌÂ");//-MRF_971017
             strcpy(Name, "⁄”ò—ÌÂ");
            break;
        case 10060:
            strcpy(Name, "»«‰ò „—ò“Ì");
            break;
        case 636795:
//            strcpy(Name, "«œ«—Â „⁄«„·«  —Ì«·Ì »«‰ò „—ò“Ì");
            strcpy(Name, "»«‰ò „—ò“Ì");//-MRF_971017
            break;
        case 581672:
//            strcpy(Name, "‘»òÂ «·ò —Ê‰ÌòÌ Å—œ«Œ  ò«— _ ‘«Å—ò");//-MRF_971017
            strcpy(Name, "‘«Å—ò");
            break;
        case 581874:
            strcpy(Name, "«Ì—«‰ Ê‰“Ê∆·«");
            break;
        case 507677:
//            strcpy(Name, "„Ê””Â «⁄ »«—Ì ‰Ê—");//-MRF_971017
            strcpy(Name, "‰Ê—");
            break;
        default:
            strcpy(Name, "‰«„‘Œ’");
            break;
    }
}


uint8 readReversalInfo(int8* fileName, messageSpecST* messageSpec) 
{
    reversalTransST		reversalInfo;
    uint32              sizeOfFile 	= sizeof(reversalTransST); 	/** size of reversal message file */
    int16               retValue	= FAILURE; 					/** read file function return value */
    int16               retValue2	= FAILURE;
    int16               maxRecord   = 0;
    int8                logName[FILE_NAME_LENTGH]     = {0};

    memset(&reversalInfo, 0, sizeof(reversalTransST));

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "****readReversalInfo****");
    retValue = readFileInfo(fileName, &reversalInfo, &sizeOfFile);    
    if (retValue != SUCCESS) 
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "retval File reversal = %d", retValue);
        return FALSE;
    }

    strcpy(messageSpec->cardSpec.PAN, reversalInfo.PAN);
    strcpy(messageSpec->amount, reversalInfo.amount);
    strcpy(messageSpec->retrievalReferenceNumber, reversalInfo.retrievalReferenceNumber);
    strcpy(messageSpec->buyChargeSpec.realAmount, reversalInfo.ChargeRealAmount);
    messageSpec->merchantSpec.recieveSTAN = reversalInfo.STAN;
    messageSpec->transType                = reversalInfo.transType;
    messageSpec->dateTime                 = reversalInfo.SWdateTime;
    messageSpec->SWdateTime               = reversalInfo.SWdateTime;
    messageSpec->responseStatus           = reversalInfo.responseStatus;
    messageSpec->billSpec                 = reversalInfo.billSpec;
    messageSpec->buyChargeSpec.type       = reversalInfo.chargeType;
    messageSpec->topup                    = reversalInfo.topup; //MRF_TOPUP
    messageSpec->charity                  = reversalInfo.charity; //HNO_DEBUG2

    return TRUE;
}




uint8 transactionChargeList(argumentListST* args)
{    
    filesST*        files                                       = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    chargeLogST     transactions[MAX_CHARGE_TRANS_LOG_RECORDS]  = {0};	
    int				transactionNumber                           = 0;            /** charge number with specified date in file */
    int				counter                                     = 0;            /** loop counter */
    uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
    uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
    uint8			fileName[FILE_NAME_LENTGH]                  = {0};
    uint8			activeUser[15 + 1]                          = {0};
    uint8			title[30]                                   = {0};
    uint8			activeUserTitle[15 + 1]                     = {0};
    uint8           chargeTypeStr[16]                           = {0};
    int             chargeType                                  = 0;
    uint8           check                                       = FALSE;
    uint8           sumDailyValues[15 + 1]                      = {0};
    uint8			tempSumValues[15 + 1]                       = {0}; 
    uint8			valueWithComma[20]                          = {0}; 
    uint8           depositID[11 + 1]                           = {0};
    
    strcpy(fileName, CHARGE_LOG_FILE);
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");

    
    if (!readTransactionListFile(fileName, transactions, sizeof(chargeLogST), MAX_CHARGE_TRANS_LOG_RECORDS, 
    						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "****transactionChargeList****");
    
    /** LINE 0 : HEADER */
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ ‘«—é");

    if (!displayTransactionChargeList(transactions, transactionNumber, requestedNum, "‘«—é „Ê›ﬁ", &startDateTime,
    		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
    	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    if (! printReceiptDate(transactions[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;
    
    printDash3();
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {   
        if (check != 0)
        {
           if (!printReceiptDate(transactions[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }
        
        /** TRANSACTIONS LOG ; LINE 1: CHARGE TYPE */
        chargeType = transactions[counter].type;
        
        getChargeTypeStr(chargeType, chargeTypeStr);
#ifdef VX520
		if (!printTwoStringFarsi(chargeTypeStr, "‰Ê⁄ ‘«—é:", PRN_NORM))
			return FALSE;
#else
        strcat(chargeTypeStr, "|");
        if (!printTwoStringFarsi(chargeTypeStr,"|‰Ê⁄ ‘«—é:", PRN_NORM))
            return FALSE;
#endif
    	if (!printTransactionListCommonPart(transactions[counter].amount, transactions[counter].PAN, 
        			transactions[counter].retrievalReferenceNumber, 0, &(transactions[counter].dateTime), depositID))//MRF)NEW17
    		return FALSE;
        
        check = compareDates(&transactions[counter].dateTime, &transactions[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumDailyValues);
        
        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();
        
        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);

            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }
        
        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;
    
    return TRUE;
}

uint8 displayTransactionChargeList(chargeLogST* transactions, int transactionNumber, uint32 requestedNum, uint8* title,
		dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	int				counter                 						= 0;            			/** loop counter */
	int             chargeType                  					= 0;			
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]	= {0, 0};			
	uint16  		i                       						= 0;			
	uint8			tempSumValues[15 + 1]   						= {0};      				/** sum of listed transactions value */
	uint8			key 											= KBD_CANCEL;			
	uint8			displayedCount          						= 0;            			/** display counter */
	uint8			displayedSumValues[15 + 1]						= {0};
    uint8           chargeTypeStr[16]           					= {0};
	terminalSpecST  terminalCapability								= getTerminalCapability();
    uint8           depositID[11 + 1]                               = {0};
   
	     			                   
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0 ; counter--) 
    {
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumValues);
        
    	if ( i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 10)) //6: header, 4: footer, 10: body 
    	{
            /** TRANSACTIONS LOG ; LINE 1: CHARGE TYPE */
	    	chargeType = transactions[counter].type;
            getChargeTypeStr(chargeType, chargeTypeStr);
		    justifyTwoStringFarsi("", "‰Ê⁄ ‘«—é", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, chargeTypeStr);
	        
	    	fillTransListCommonPartLines(lines, &i, transactions[counter].amount,
					transactions[counter].PAN,
	    			transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime), depositID);
	    	displayedCount++;
	    	strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    
    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader(title, lines, i, DISPLAY_TIMEOUT, FALSE, chargeTrans);
    
    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}


uint8 unsuccessChargeTransaction(argumentListST* args)
{    
    filesST*        			files                   				 = (filesST*) (args->argumentName);
    dateTimeST					startDateTime							 = {0, 0};
    dateTimeST					endDateTime								 = {0, 0};
	reversalTransST				reversalInfo[MAX_UNSUCCESS_CHARGE_TRANS] = {0}; 
    int							transactionNumber						 = 0;   /** charge number with specified date in file */
	int                         chargeType                  			 = 0;
    int							counter                 				 = 0;   /** loop counter */
	uint32						requestedNum							 = 0;   /** user requested transaction number, integer form */
    uint8						sumValues[15 + 1]       				 = {0}; /** sum of listed transactions value */
    uint8						fileName[FILE_NAME_LENTGH]				 = {0};
    uint8						activeUser[15 + 1]						 = {0};
    uint8						activeUserTitle[15 + 1]					 = {0};
    uint8						title[30]                                = {0};
    uint8						referenceNum[1]							 = {0};
    uint8                       chargeTypeStr[16]           			 = {0};
    uint8                       depositID[11 + 1]                        = {0};


	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****uunsuccessChargeTransaction****");
    strcpy(fileName, REVERSAL_CHARGE_LOG_FILE);
    
    if (!readTransactionListFile(fileName, reversalInfo, sizeof(reversalTransST), MAX_UNSUCCESS_CHARGE_TRANS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    strcpy(title, "—Ì“ —«ò‰‘ ‰«„Ê›ﬁ ‘«—é");
    if (!displayUnsuccessChargeTransaction(reversalInfo, transactionNumber, 
			requestedNum, "‘«—é ‰«„Ê›ﬁ", &startDateTime,
				&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
           	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    if (!printReceiptDate(reversalInfo[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;
    
    printDash3();
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        /** TRANSACTIONS LOG ; LINE 1: CHARGE TYPE */
        chargeType = reversalInfo[counter].chargeType;
        getChargeTypeStr(chargeType, chargeTypeStr);
#ifdef VX520
		if (!printTwoStringFarsi(chargeTypeStr, "‰Ê⁄ ‘«—é:", PRN_NORM))
			return FALSE;
#else
        strcat(chargeTypeStr, "|");
        if (!printTwoStringFarsi(chargeTypeStr,"|‰Ê⁄ ‘«—é:", PRN_NORM))
            return FALSE;
#endif
    	if (!printTransactionListCommonPart(reversalInfo[counter].amount, 
				reversalInfo[counter].PAN, referenceNum, 
    			reversalInfo[counter].STAN, /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
				&(reversalInfo[counter].SWdateTime), depositID))
    		return FALSE;

        if (cancelFunction())
            return FALSE;

        if (!printDash())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


uint8 displayUnsuccessChargeTransaction(reversalTransST* reversalInfo, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 3][32]	= {0, 0};			//HNO:change 400 to2000 /** 3: fot the last three lines */
	uint16  		i                       						= 0;	
	uint8			tempSumValues[15 + 1]   						= {0};       		/** sum of listed transactions value */
	int				counter                 						= 0;           		/** loop counter */
	uint8			key 											= KBD_CANCEL;		
	uint8			displayedCount          						= 0;           		/** display counter */
	uint8			displayedSumValues[15 + 1]						= {0};
	uint8			referenceNum[1]									= {0};
    uint8           chargeTypeStr[16]           					= {0};
    int             chargeType                  					= 0;
	terminalSpecST  terminalCapability								= getTerminalCapability();
    uint8           depositID[11 + 1]           					= {0};
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumValues);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 10))
    	{
             /** TRANSACTIONS LOG ; LINE 1: CHARGE TYPE */
	    	chargeType = reversalInfo[counter].chargeType;
            getChargeTypeStr(chargeType, chargeTypeStr);
		    justifyTwoStringFarsi("", "‰Ê⁄ ‘«—é", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, chargeTypeStr);
            
    		fillTransListCommonPartLines(lines, &i, reversalInfo[counter].amount, reversalInfo[counter].PAN, 
    				referenceNum, reversalInfo[counter].STAN,
                    /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
                    &(reversalInfo[counter].SWdateTime), depositID);
    		displayedCount++;
    		strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
	}
 
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);

    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE, unsucessChargeTrans);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else 
    	return TRUE;
}


uint8 reprintChargeTransaction(argumentListST* args)
{    
    filesST*				files	= (filesST*) (args->argumentName);
    messageSpecST			messageSpec;									
    lastCustomerReceiptST   lastCustomerReceipt;
    cardTracksST            cardTracks;
    cardSpecST              cardSpec;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));
    memset(&cardTracks, 0, sizeof(cardTracksST));
    memset(&cardSpec, 0, sizeof(cardSpecST));
    
    
    displayMessage("·ÿ›« ò«—  —« »ò‘Ìœ...", DISPLAY_START_LINE + 1, ALL_LINES);
    if(getCardHandle() <= 0)
        enableMSR(); 

    if (!readMagnetCardWait(cardTracks.track1, cardTracks.track2, cardTracks.track3, &cardTracks.track1Len, &cardTracks.track2Len, &cardTracks.track3Len))
    { 
        return FALSE;
    }    

    if (!readTrackData(files, &cardTracks, &cardSpec, FALSE)) 
    {
        return FALSE;
    }

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_CHARGE_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "lastCustomerReceipt.ID: %d",lastCustomerReceipt.buyChargeSpec.id);
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "lastCustomerReceipt.serial: %s",lastCustomerReceipt.buyChargeSpec.serial);
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "lastCustomerReceipt.PIN: %s",lastCustomerReceipt.buyChargeSpec.PIN);
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "lastCustomerReceipt.usingDescription: %s",lastCustomerReceipt.buyChargeSpec.usingDescription);
    
    if (fileExist(SUPERVISOR_FILE) == SUCCESS)//+HNO_971113 when we swipe supervisor card, supervisor file created so we have'nt footer
    	fileRemove(SUPERVISOR_FILE);

	if (strcmp(lastCustomerReceipt.PAN, cardSpec.PAN) == 0)
    {
        structCpy(&lastCustomerReceipt, &messageSpec);
        printTransactionBuyCharge(files, &messageSpec, TRUE, CHARGE_REPRINT);
    }
    else 
    {
        structCpy(&lastCustomerReceipt, &messageSpec);
        printTransactionBuyCharge(files, &messageSpec, TRUE, REPRINT);
    }
    
	return TRUE;
}


uint8 printLoanPayTransaction(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)
{
	if (!PrinterAccess(TRUE))
		return FALSE;

	displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

	/** PRINT HEADER */
	if (!prePrintFlags)
		if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
			return FALSE;

	prePrintFlags = 0;

	if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
		return FALSE;

	if(!customer)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
		fileRemove(files->customerReceiptFile);
	}
	/** PRINT FOOTER */
	if (!printTransactionFooter(rePrint, customer, TRUE, files))
		return FALSE;

	return TRUE;
}


uint8 printLoanTrakingTransaction(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)
{
    uint8   errorCode[10]           = {0};
    uint8   len                     = 0;
    uint8   status[109]             = {0};
    uint8	valueWithComma[30]		= {0};
    uint8   amountPrintBuffer[20]   = {0};

    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**print LOAN TrakingTransaction**");

    if (!PrinterAccess(TRUE))
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
            return FALSE;
    
    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
        return FALSE;
    
    //HNO_IDENT
    makeValueWithCommaStr(messageSpec->loanPay.payAmount, valueWithComma);
#ifndef VX520
    sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma);
    if(!printTwoStringNumericFarsi(amountPrintBuffer, "„»·€", PRN_NORM))
		return FALSE;
#else
	if (!printThreeStringFarsi(" —Ì«·", valueWithComma, "„»·€", PRN_NORM, ALIGN_RIGHT, TRUE))
		return FALSE;
#endif

    if ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8)
            || (messageSpec->responseStatus == 16))
    {
        //CHANGE THIS PART SAME ETC
#ifdef CASTLES_V5S //MRF_TTF
        sprintf(errorCode,"òœ:%s",messageSpec->loanPay.error);
#else
        sprintf(errorCode,"òœ %s:",messageSpec->loanPay.error);
#endif
        
        len = strlen(messageSpec->loanPay.status);
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "len of status: %d", len);

#if defined(ICT250) || defined(IWL220)
        if ( len < 43)
        {
           if(!printTwoStringFarsi(errorCode, messageSpec->loanPay.status, PRN_NORM))
                return FALSE;
        }

        else
        {
        	if(!printOneStringFarsi("⁄„·Ì«  „Ê›ﬁÌ  ¬„Ì“ »ÊœÂ Ê ÿÌ 72 ”«⁄  Ê«—Ì“ ", PRN_NORM, ALIGN_CENTER))
        		return FALSE;
        	if(!printTwoStringFarsi(errorCode, "„Ìê—œœ     ",PRN_NORM))
        		return FALSE;
        }
#else
        if ( len < 30)
        {
            if (!printTwoStringFarsi(errorCode, messageSpec->loanPay.status, PRN_NORM_INVERSE))
                return FALSE;
        }
        else
        {
            strcpy(status, messageSpec->loanPay.status);
            strcat(status, "  ");
            strcat(status, errorCode);
            if (!printOneStringFarsi(status, PRN_NORM, ALIGN_CENTER))
                return FALSE;
        }
#endif
    }
    else
    {
        if (!printOneStringFarsi("—ÂêÌ—Ì  —«ò‰‘ «‰Ã«„ ‰‘œ", PRN_NORM, ALIGN_CENTER))
            return FALSE;
    }

    /** PRINT FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files))
        return FALSE;

    return TRUE;
}


uint8 transactionLoanPayList(argumentListST* args)
{    
    filesST*        	files                                        = (filesST*) (args->argumentName);
    dateTimeST			startDateTime                                = {0, 0};
    dateTimeST			endDateTime                                  = {0, 0};
    int					transactionNumber                            = 0;            /** charge number with specified date in file */
    uint32				requestedNum                                 = 0;            /** user requested transaction number, integer form */
    int					counter                                      = 0;            /** loop counter */
    uint8				destinationCard[18]                          = {0};
    uint8				nameStr[20]                                  = {0};
    uint8               sumValues[15 + 1]                            = {0}; 
    uint8				fileName[FILE_NAME_LENTGH]                   = {0};
    uint8				activeUser[15 + 1]                           = {0};
    uint8				activeUserTitle[15 + 1]                      = {0};
    uint8				title[30]                                    = {0};
    uint8               check                                        = FALSE;
    uint8               sumDailyValues[15 + 1]                       = {0};
    uint8               tempSumValues[15 + 1]                        = {0};
    uint8               valueWithComma[20]                           = {0};
    loanPayTransLogST   loanPay[MAX_LOAN_PAY_TRANS_LOG_RECORDS]      = {0};		//HNO: change 200 to 1000
    uint8               depositID[11 + 1]                            = {0};


    strcpy(fileName, LOAN_PAY_LOG_FILE);
    
    if (!readTransactionListFile(fileName, loanPay, sizeof(loanPayTransLogST),
			MAX_LOAN_PAY_TRANS_LOG_RECORDS, 
			&startDateTime, &endDateTime, &transactionNumber, 
			&requestedNum, activeUserTitle, activeUser))
    	return FALSE;
        
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ ﬁ”ÿ"); //MGH: change name to lower size

    if (!displayTransactionLoanPayList(loanPay, transactionNumber, requestedNum, "ﬁ”ÿ „Ê›ﬁ", &startDateTime,
                		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
        	return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;
    
    if (!printReceiptDate(loanPay[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;

    printDash3();

    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
         {
            if (!printReceiptDate(loanPay[counter].dateTime.date," «—ÌŒ"))
                return FALSE;
            printDash3();
         }
        
#ifdef VX520
		if (!printTwoStringNumericFarsi(loanPay[counter].destinationCardPAN, "ò«—  ﬁ”ÿ", PRN_NORM))
			return FALSE;
		
		sprintf(nameStr, "%s %s", loanPay[counter].destinationCardHolderName, loanPay[counter].destinationCardHolderFamily);
		if (!printTwoStringFarsi(nameStr, "»Â ‰«„:", PRN_NORM)) //++ABS:980223
			return FALSE;
#else
        #ifdef CASTLES_V5S //MRF_TTF
        reversPartString(loanPay[counter].destinationCardPAN);
        #endif

    	/** PRINT card Pan */
        maskCardId(loanPay[counter].destinationCardPAN, destinationCard);

        strcat(loanPay[counter].destinationCardPAN,"|");
	    if (!printTwoStringNumericFarsi(loanPay[counter].destinationCardPAN, "|ò«—  ﬁ”ÿ", PRN_NORM)) //MRF_NEW8
	        return FALSE;
       
	
        sprintf(nameStr, "%s %s", loanPay[counter].destinationCardHolderName, loanPay[counter].destinationCardHolderFamily);
        strcat(nameStr, "|");
	    if (!printTwoStringNumericFarsi(nameStr, "|»Â ‰«„", PRN_NORM))
	        return FALSE;
#endif

    	if (!printTransactionListCommonPart(loanPay[counter].amount, loanPay[counter].PAN, 
    			loanPay[counter].retrievalReferenceNumber, 0, &(loanPay[counter].dateTime), depositID))//MRF_NEW17
    		return FALSE;

        check = compareDates(&loanPay[counter].dateTime, &loanPay[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, loanPay[counter].amount, sumDailyValues);

        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();

        if (check != 0)
         {
             makeValueWithCommaStr(sumDailyValues, valueWithComma);
             if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                 return FALSE;

             printStar();
             memset(sumDailyValues, 0, sizeof(sumDailyValues));
         }

        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}

uint8 printTransactionSupervisor(messageSpecST* messageSpec, filesST* files)
{
    uint8               reversalCancelled           = FALSE;
    uint8               customer                    = FALSE;
    int                 amount                      = 0;
    int16               retValue                    = 0;
    uint32              len                         = sizeof(supervisorSpec);
    uint8               valueWithComma[12 + 1]      = {0};
    uint8               activity[100]               = {0};
    uint8   			amountPrintBuffer[20]       = {0};
    supervisorSpec      supervisor;
    
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "printTransactionSupervisor", "********START**********");
    
    memset(&supervisor, 0 , sizeof(supervisorSpec));
	
    if (!PrinterAccess(TRUE))    
        return reversalCancelled;    

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);    

    /** PRINT HEADER */
    if (!prePrintFlags)
    	if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files)) 
    		return reversalCancelled;  
    
    prePrintFlags = 0;
    printOneStringFarsi("—”Ìœ Å‘ Ì»«‰", PRN_NORM, ALIGN_CENTER);
    
    amount = atoi(messageSpec->amount);

	switch (amount)
	{
		case TEST_POS:
			strcpy(activity," ”  ”·«„ ");
			break;
		case UPDATE_APP:
			strcpy(activity,"»Â —Ê“—”«‰Ì ‰—„ «›“«—");
			break;
		case UPDATE_GUIDE:
			strcpy(activity,"»Â —Ê“—”«‰Ì —«Â‰„«");
			break;
		case VISITOR_CASE:
			strcpy(activity,"»«“œÌœ „Ê—œÌ");
			break;
		case PERIODIC_VISIT:
			strcpy(activity,"»«“œÌœ œÊ—Â «Ì");
			break;
		case UPDATE_CONTRACT:
			strcpy(activity,"»Â —Ê“—”«‰Ì ﬁ—«—œ«œ");
			break;
		case UPDATE_LABLE:
			strcpy(activity,"»Â —Ê“—”«‰Ì »—ç”»");
			break;
		case CHANGE_TERMINAL:
			strcpy(activity," ⁄ÊÌ÷ Å«Ì«‰Â ›—Ê‘");
			break;
		case REMOVE_POS:
			strcpy(activity,"Ã„⁄ ¬Ê—Ì Å«Ì«‰Â");
			break;
		case INSTALLATION_TRANS:
			strcpy(activity,"‰’»");
			break;
		case ENTRANCE: //+MRF_971026
			strcpy(activity,"Ê—Êœ");
			break;
		case EXIT: //+MRF_971026
			strcpy(activity,"Œ—ÊÃ");
			break;
		default:
			strcpy(activity,"⁄„·Ì«  ‰«„⁄ »—");
			break;

	}
    
    retValue = readFileInfo(SUPERVISOR_FILE, &supervisor , &len);
    if (retValue != SUCCESS)
    {   
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
        return FALSE;
    }
    else
    {
        removePadLeft(supervisor.personnelID, '0');
        printTwoStringNumericFarsi(supervisor.personnelID, "òœÅ‘ Ì»«‰", PRN_NORM);
        printTwoStringFarsi(activity,"⁄‰Ê«‰:", PRN_NORM);
    }
    
    strcpy(messageSpec->supervisor.activity, activity);
    strcpy(messageSpec->supervisor.personnelID, supervisor.personnelID);
    strcpy(messageSpec->supervisor.codeMeli, supervisor.codeMeli);
    
    /** PRINT COMMON PART */
    if (!printTransactionCommonPart(messageSpec, FALSE, FALSE, files)) 
        return FALSE;     
    
    if (messageSpec->responseStatus == 0)
        if (!PrinterAccess(TRUE))    
            return FALSE;   
#if defined (CASTLES_V5S) || defined (INGENICO)
    printOneStringFarsi("⁄„·Ì«  „Ê›ﬁ", PRN_BIG, ALIGN_CENTER);
#else
    printOneStringFarsi("⁄„·Ì«  „Ê›ﬁ", PRN_NORM_INVERSE, ALIGN_CENTER);
#endif
	
	//START #MRF_971029
	makeValueWithCommaStr(messageSpec->amount, valueWithComma);
	//sprintf(amountPrintBuffer, "%s—Ì«·", valueWithComma);
	//removePadLeft(amountPrintBuffer,'0');
	//if (!printTwoStringNumericFarsi(amountPrintBuffer,"„»·€", PRN_NORM_INVERSE))
	if (!printThreeStringFarsi("—Ì«·", valueWithComma, "„»·€", PRN_NORM_INVERSE, ALIGN_RIGHT, TRUE))//..ABS_971207
		return reversalCancelled;
	//END #MRF_971029
    
    /** PRINT TRANSACTION FOOTER */
    printTransactionFooter(FALSE, FALSE, TRUE, files); 
    addSupervisiorReport(messageSpec);
    
    fileRemove(SUPERVISOR_FILE);
    
    return FALSE;
}

void addSupervisiorReport(messageSpecST* messageSpec)  
{
    int16                   retValue						= FAILURE;		/** write in file function return value */
    uint8                   fileName[FILE_NAME_LENTGH]		= {0};
    supervisorTransLogST    transaction;
    
    memset(&transaction, 0, sizeof(supervisorTransLogST));
    
    strcpy(fileName, SUPERVISOR_LOG_FILE);
    
    transaction.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->cardSpec.PAN, transaction.PAN);
    strcpy(transaction.amount, messageSpec->amount); 
    strcpy(transaction.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(transaction.personnelID, messageSpec->supervisor.personnelID);
    strcpy(transaction.codeMeli, messageSpec->supervisor.codeMeli);
    strcpy(transaction.activity, messageSpec->supervisor.activity);
    
    retValue = appendFixedFileInfo(fileName, &transaction, 
                                     sizeof(supervisorTransLogST), MAX_SUPERVISOR_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}


uint8 displayTransactionSupervisorList(supervisorTransLogST* transactions, int transactionNumber, uint32 requestedNum, uint8* title,
		dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8				lines[700 + 3][32]				= {0, 0};				/** 3: fot the last three lines */
	uint16  			i                       		= 0;		
	uint8				tempSumValues[15 + 1]   		= {0};      			/** sum of listed transactions value */
	int					counter                 		= 0;            		/** loop counter */
	uint8				key 							= KBD_CANCEL;		
	uint8				displayedCount          		= 0;            		/** display counter */
	uint8				displayedSumValues[15 + 1]		= {0};
	terminalSpecST  	terminalCapability				= getTerminalCapability();
    uint8           	depositID[11 + 1]           	= {0};
	     			                   
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);

    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0 ; counter--) 
    {
    	//mgh: adding two string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if ( i < (100 - 6 - 4 - 8)) //6: header, 4: footer, 8: body 
    	{
            justifyTwoStringFarsi("", "⁄‰Ê«‰", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, transactions[counter].activity);
			
            removePadLeft(transactions[counter].personnelID, '0');
		    justifyTwoStringFarsi("", "òœ Å‘ Ì»«‰", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, transactions[counter].personnelID);
            
	    	fillTransListCommonPartLines(lines, &i, transactions[counter].amount, transactions[counter].PAN,
	    			transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime), depositID);
	    	displayedCount++;
	    	strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    if (!terminalCapability.graphicCapability) 
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
     	key = displayScrollableWithHeader(title, lines, i, DISPLAY_TIMEOUT, FALSE,supervisorActivitiesPic);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}


/**
 * display & print buy transaction list report.
 * @see     searchDateRangeInFixedFile()
 * @see     readFixedFileInfoArray()
 * @see     displayScrollable()
 * @see     printLogo()
 * @see     printReceiptDateTime()
 * @see     show_one_log()
 */
uint8 transactionSupervisorList(argumentListST* args)
{    
	filesST*                files                   						= (filesST*) (args->argumentName);
						
    dateTimeST              startDateTime									= {0, 0};
    dateTimeST              endDateTime										= {0, 0};
    int                     transactionNumber								= 0;            /** charge number with specified date in file */
    uint32                  requestedNum									= 0;            /** user requested transaction number, integer form */
    int                     counter                 						= 0;            /** loop counter */
    uint8                   sumValues[15 + 1]       						= {0};          /** sum of listed transactions value */
    supervisorTransLogST    transactions[MAX_SUPERVISOR_TRANS_LOG_RECORDS]  = {0};//#MRF_970924
    uint8                   fileName[FILE_NAME_LENTGH]						= {0};
    uint8                   transType										= TRANS_BUY;
    uint8                   activeUser[15 + 1]								= {0};
    uint8                   title[30]                   					= {0};
    uint8                   activeUserTitle[15 + 1]							= {0};
    uint8                   depositID[11 + 1]           					= {0};
    
    
    strcpy(fileName, SUPERVISOR_LOG_FILE);
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");

    if (!readTransactionListFile(fileName, transactions, sizeof(supervisorTransLogST), MAX_SUPERVISOR_TRANS_LOG_RECORDS, 
    						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
    
    showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "transaction Buy List 5");
    
    strcpy(title, "⁄„·Ì«  Å‘ Ì»«‰");//ABS:CHANGE

    if (!displayTransactionSupervisorList(transactions, transactionNumber, requestedNum, title, &startDateTime,
    		&endDateTime, activeUserTitle, activeUser, sumValues))
    	return FALSE;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "display list");
    
    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
#ifndef VX520
        strcat(transactions[counter].activity, "|");
	    if (!printTwoStringNumericFarsi(transactions[counter].activity, "|⁄‰Ê«‰", PRN_NORM))
	        return FALSE;
		
        removePadLeft(transactions[counter].personnelID, '0');
        strcat(transactions[counter].personnelID,"|");
        if (!printTwoStringNumericFarsi(transactions[counter].personnelID, "|òœ Å‘ Ì»«‰", PRN_NORM))
            return FALSE;
#else
		printTwoStringFarsi(transactions[counter].activity, "⁄‰Ê«‰:", PRN_NORM);
		removePadLeft(transactions[counter].personnelID, '0');
		printTwoStringNumericFarsi(transactions[counter].personnelID, "òœ Å‘ Ì»«‰", PRN_NORM);

#endif
    	if (!printTransactionListCommonPart(transactions[counter].amount,
				transactions[counter].PAN, 
				transactions[counter].retrievalReferenceNumber, 0,
				&(transactions[counter].dateTime), depositID))
    		return FALSE;
        
        if (cancelFunction())
            return FALSE;

        if (!printDash())
            return FALSE;
    }
    
    /** PRINT EMPTY LINES */
    printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}

uint8 merchantChargeReport(argumentListST* args)
{    
    filesST*		files                   				= (filesST*) (args->argumentName);
    uint32          userDateJalali          				= 0;				/** entered date by user (jalali) */
    int             reportYear              				= 0;				/** report year */
    int             reportMonth             				= 0;				/** report month */
    int             reportDay               				= 0;				/** report day */
    int             transactionNumber       				= 0;				/** transactions number with specified date in file */
    uint8           transValueSum[15 + 1]   				= {0};				/** sum of transactions value */
    uint8           tempSumValues[15 + 1]   				= {0};
    int             counter                 				= 0;				/** loop counter */
    uint8           lines[15][32]           				= {0};				/** display lines */
    uint8           valueWithComma[20]      				= {0};				/** sum value with comma, string form */
    chargeLogST     transactions[MAX_CHARGE_TRANS_LOG_RECORDS] = {0}; 
    uint8           dateValueStr[11]        				= {0};
    uint8           transNum[10]            				= {0};
    uint8           numStr[7]               				= {0};
    uint16          i                                       = 0;
    uint8           key                                     = KBD_CANCEL;
	uint8           separatedStr[10][SEPERATED_STR_SIZE] 	= { 0, 0 };//ABS:CHANGE	//HNO_IDENT8  change 250 to 50 because it crash
    uint8           wordWrapIndex           				= 0; 
    uint8           loop                    				= 0; 
    uint8           amountPrintBuffer[20]   				= {0}; 
    uint8           fileName[FILE_NAME_LENTGH]				= {0};
    uint8			transType								= TRANS_BUYCHARGE;
    uint8			activeUser[15 + 1]						= {0};
    uint8			activeUserTitle[15 + 1]					= {0};
    merchantSpecST	merchantSpec;
    dateTimeST		dateTime;
    uint8           chargeType[15 + 1]                      = {0};
    uint8           buffer[12 + 1]                          = {0};
    dateTimeST		startDateTime                           = {0, 0};
    dateTimeST		endDateTime                             = {0, 0};
    uint32			requestedNum                            = 0;
    uint8			title[30]                               = {0};
    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    memset(&dateTime, 0, sizeof(dateTimeST));
    memset(lines, 0, sizeof(lines));

    strcpy(fileName, CHARGE_LOG_FILE);
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");
    strcpy(title, "ê“«—‘ ’‰œÊﬁ ‘«—é");

    if (!readTransactionListFile(fileName, transactions, sizeof(chargeLogST), MAX_CHARGE_TRANS_LOG_RECORDS, 
                        &startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    return FALSE;
   
    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    return FALSE;

    /** ACTIVE USER */
    if (strlen(activeUser) > 0)
    {
	    justifyTwoStringFarsi("", activeUserTitle, lines[i++], PRN_NORM);
	    sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, activeUser);
    }

    /** LINE 2 : TRANSACTION NUMBER */
    sprintf(transNum, "%d", requestedNum); //#MRF_971226
    justifyTwoStringFarsi(transNum, " ⁄œ«œ", lines[i++], PRN_NORM);
     
    if (!PrinterAccess(TRUE))    
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);
    
    //mgh: adding 2string...
    for (counter = 0; counter < transactionNumber; counter++)
    {
        strcpy(tempSumValues, transValueSum);
        sumStringNumbers(tempSumValues, transactions[counter].amount, transValueSum);
        makeValueWithCommaStr(transValueSum, valueWithComma);
        
        if  (transactions[counter].type == MULTI_IRANCELL)
            {
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "MULTI_IRANCELL");
                if (strcmp(transactions[counter].amount, "10000") == 0)
                    chargeType[1]++;
                    else if (strcmp(transactions[counter].amount, "20000") == 0)
                        chargeType[2]++;
                        else if (strcmp(transactions[counter].amount, "50000") == 0)
                            chargeType[3]++;
                             else if (strcmp(transactions[counter].amount, "100000") == 0)
                                 chargeType[4]++;
                                else if (strcmp(transactions[counter].amount, "200000") == 0)
                                    chargeType[5]++;
            }
        else if (transactions[counter].type == MULTI_MCI)
            {
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "MULTI_MCI");
                 if (strcmp(transactions[counter].amount, "10000") == 0)
                     chargeType[6]++;
                    else if (strcmp(transactions[counter].amount, "20000") == 0)
                        chargeType[7]++;
                        else if (strcmp(transactions[counter].amount, "50000") == 0)
                            chargeType[8]++;
                             else if (strcmp(transactions[counter].amount, "100000") == 0)
                                 chargeType[9]++;
                                else if (strcmp(transactions[counter].amount, "200000") == 0)
                                    chargeType[10]++;
            }
        else if (transactions[counter].type == MULTI_RIGHTEL)       
            {
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "MULTI_RIGHTEL");
                if (strcmp(transactions[counter].amount, "20000") == 0)
                    chargeType[11]++;
                    else if (strcmp(transactions[counter].amount, "50000") == 0)
                        chargeType[12]++;
                        else if (strcmp(transactions[counter].amount, "100000") == 0)
                            chargeType[13]++;
                             else if (strcmp(transactions[counter].amount, "200000") == 0)
                                 chargeType[14]++;
                                else if (strcmp(transactions[counter].amount, "500000") == 0)
                                    chargeType[15]++;
            }
    }
    
    /*Irancell*/
    if (!printOneStringFarsi("«Ì—«‰”·", PRN_NORM, ALIGN_CENTER))
        return FALSE;
//    sprintf(buffer,"%d",chargeType[1]);   //-MRF_970807
//    if (!printTwoStringNumericFarsi(buffer, "10,000 —Ì«·Ì", PRN_NORM))
//        return FALSE;
    sprintf(buffer,"%d",chargeType[2]);
    if (!printTwoStringNumericFarsi(buffer, "20,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[3]);
    if (!printTwoStringNumericFarsi(buffer, "50,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[4]);
    if (!printTwoStringNumericFarsi(buffer, "100,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[5]);
    if (!printTwoStringNumericFarsi(buffer, "200,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    
    /*Hamrahe Aval*/
    if (!printOneStringFarsi("Â„—«Â «Ê·", PRN_NORM, ALIGN_CENTER))
        return FALSE;
    sprintf(buffer,"%d",chargeType[6]);
    if (!printTwoStringNumericFarsi(buffer, "10,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[7]);
    if (!printTwoStringNumericFarsi(buffer, "20,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[8]);
    if (!printTwoStringNumericFarsi(buffer, "50,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[9]);
    if (!printTwoStringNumericFarsi(buffer, "100,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[10]);
    if (!printTwoStringNumericFarsi(buffer, "200,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    
    /*Rightel*/
    if (!printOneStringFarsi("—«Ì ·", PRN_NORM, ALIGN_CENTER))
        return FALSE;
    sprintf(buffer,"%d",chargeType[11]);
    if (!printTwoStringNumericFarsi(buffer, "20,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[12]);
    if (!printTwoStringNumericFarsi(buffer, "50,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[13]);
    if (!printTwoStringNumericFarsi(buffer, "100,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[14]);
    if (!printTwoStringNumericFarsi(buffer, "200,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    sprintf(buffer,"%d",chargeType[15]);
    if (!printTwoStringNumericFarsi(buffer, "500,000 —Ì«·Ì", PRN_NORM))
        return FALSE;
    
    /** PRINT DASHES */
    if (!printStar())
        return FALSE;
    
    /** PRINT TRANSACTION NUMBER */
    sprintf(numStr, "%d", requestedNum); //#MRF_971226
    if (!printTwoStringNumericFarsi(numStr, " ⁄œ«œ", PRN_NORM))
            return FALSE;
    /** PRINT TRANSACTION TOTAL AMOUNT */
    if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT - strlen(" —Ì«·"))
    {
        if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT)
        {
            loop = wordWrapEnglish(valueWithComma, separatedStr, DISPLAY_CHARACTER_COUNT);
            for (wordWrapIndex = 0; wordWrapIndex <= loop; wordWrapIndex++)
            {
                sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, separatedStr[wordWrapIndex]);
            }
        }
        else
        {
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma);
        }
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, "—Ì«·");
    }
    else
    {
        sprintf(lines[i++], "%c%c%c%s%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma, " —Ì«·");
    }
    
    /** PRINT TRANSACTIONS VALUE */
    if (strlen(valueWithComma) + strlen(" —Ì«·") + strlen("„Ã„Ê⁄:") <= getPrinterCharacterCount())
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "First");    
         if (!printThreeStringFarsi(" —Ì«·", valueWithComma, "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
            return FALSE;
    }
    else if (strlen(valueWithComma) + strlen(" —Ì«·") <= getPrinterCharacterCount())
    {
        if (!printOneStringFarsi("„Ã„Ê⁄:", PRN_NORM, ALIGN_RIGHT))
            return FALSE;

        sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma);
        if (!printOneStringFarsi(amountPrintBuffer, PRN_NORM, ALIGN_CENTER))
            return FALSE;
    }
    else
    {
        if (!printOneStringFarsi("„Ã„Ê⁄:", PRN_NORM, ALIGN_RIGHT))
            return FALSE;
        if (!printOneStringFarsi(valueWithComma, PRN_NORM, ALIGN_CENTER))
            return FALSE;       
        if (!printOneStringFarsi("—Ì«·", PRN_NORM, ALIGN_LEFT))
            return FALSE;       
    }

    /** PRINT EMPTY LINES */
    printBlankLines(BLANK_LINES_COUNT);
    
    return TRUE;
}


uint8 merchantLOANReport(argumentListST* args)
{
	filesST*        files                                       = (filesST*) (args->argumentName);
	dateTimeST		startDateTime                               = {0, 0};
	dateTimeST		endDateTime                                 = {0, 0};
	loanPayTransLogST   transactions[MAX_LOAN_PAY_TRANS_LOG_RECORDS] 	= {0};
	int				transactionNumber                           = 0;            /** charge number with specified date in file */
	int				counter                                     = 0;            /** loop counter */
	uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
	uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
	uint8			fileName[FILE_NAME_LENTGH]                  = {0};
	uint8			activeUser[15 + 1]                          = {0};
	uint8			title[30]                                   = {0};
	uint8			activeUserTitle[15 + 1]                     = {0};
	uint8           check                                       = FALSE;
	uint8           sumDailyValues[15 + 1]                      = {0};
	uint8			tempSumValues[15 + 1]                       = {0};
	uint8			valueWithComma[20]                          = {0};
	uint8           transNum[5]                                 = {0};

	strcpy(fileName, LOAN_PAY_LOG_FILE);

	strcpy(title, "ê“«—‘ ’‰œÊﬁ ﬁ”ÿ");

	if (!readTransactionListFile(fileName, transactions, sizeof(loanPayTransLogST), MAX_LOAN_PAY_TRANS_LOG_RECORDS,
							&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
		return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;

	for (counter = requestedNum - 1; counter >= 0; counter--)
		sumStringNumbers(sumDailyValues, transactions[counter].amount, sumDailyValues);

	makeValueWithCommaStr(sumDailyValues, valueWithComma);

	/** PRINT TRANSACTIONS NUMBER IN DATES */
	sprintf(transNum, "%d", transactionNumber);
	if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
		return FALSE;

	//HNO_IDENT remove #ifdef
	if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
		return FALSE;

	printStar();
	printBlankLines(BLANK_LINES_COUNT);

	return TRUE;

}

//MRF_ETC
uint8 printETCTransaction(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)  
{ 

    if (!PrinterAccess(TRUE))    
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
            return FALSE;
    
    prePrintFlags = 0;

    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
        return FALSE;
   
    if(!customer)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
        fileRemove(files->customerReceiptFile);
    }
    
    /** PRINT FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files)) 
        return FALSE;
    
    return TRUE;
}


void addETCReport(messageSpecST* messageSpec)  
{
    int16          		retValue                    = FAILURE;		/** write in file function return value */
    uint8				fileName[FILE_NAME_LENTGH]	= {0};
    ETCTransLogST       ETC;
    
    memset(&ETC, 0, sizeof(ETCTransLogST));
    strcpy(fileName, ETC_LOG_FILE);
    
    ETC.dateTime = messageSpec->dateTime;
    strcpy(ETC.amount, messageSpec->ETC.amount); 
    maskCardId(messageSpec->cardSpec.PAN, ETC.PAN);
    strcpy(ETC.cardHolderName, messageSpec->ETC.cardHolderName);
    strcpy(ETC.cardHolderFamily, messageSpec->ETC.cardHolderFamily);
    strcpy(ETC.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(ETC.serialETC, messageSpec->ETC.serialETC);
   
    retValue = appendFixedFileInfo(fileName, &ETC, 
				sizeof(ETCTransLogST), MAX_ETC_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
}

//MRF_ETC
uint8 reprintETCTransaction(argumentListST* args)
{    
    filesST*                        files	= (filesST*) (args->argumentName);
    messageSpecST                   messageSpec;
    lastCustomerReceiptST           lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_ETC_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;
    
    structCpy(&lastCustomerReceipt, &messageSpec);
    printETCTransaction(files, &messageSpec, TRUE, TRUE);
    
    return TRUE;
}


uint8 transactionETCList(argumentListST* args)
{    
    filesST*        	files                               = (filesST*) (args->argumentName);
    dateTimeST			startDateTime                       = {0, 0};
    dateTimeST			endDateTime                         = {0, 0};
    int					transactionNumber                   = 0;            /** charge number with specified date in file */
    uint32				requestedNum                        = 0;            /** user requested transaction number, integer form */
    int					counter                             = 0;            /** loop counter */
    uint8				serialETC[13 + 1]                   = {0};
    uint8				nameStr[20]                         = {0};
    uint8               sumValues[15 + 1]                   = {0}; 
    uint8				fileName[FILE_NAME_LENTGH]          = {0}; 
    uint8				activeUser[15 + 1]                  = {0};
    uint8				activeUserTitle[15 + 1]             = {0};
    uint8				title[30]                           = {0};
    uint8           	sumDailyValues[15 + 1]              = {0};
    uint8				tempSumValues[15 + 1]               = {0};
    uint8				valueWithComma[20]                  = {0};
    uint8           	check                               = FALSE;
    ETCTransLogST       ETC[MAX_ETC_TRANS_LOG_RECORDS]      = {0}; 
    uint8               depositID[11 + 1]                   = {0};


    strcpy(fileName, ETC_LOG_FILE);
    
    if (!readTransactionListFile(fileName, ETC, sizeof(ETCTransLogST), MAX_ETC_TRANS_LOG_RECORDS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
        
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ ⁄Ê«—÷"); 

    if (!displayTransactionETCList(ETC, transactionNumber, requestedNum, "⁄Ê«—÷ „Ê›ﬁ", &startDateTime,
                		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
        	return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;
    
    if (! printReceiptDate(ETC[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;

    printDash3();

    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(ETC[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }
        /** PRINT SERIAL ETC */
#ifdef VX520
		if (!printTwoStringNumericFarsi(ETC[counter].serialETC, "”—Ì«·", PRN_NORM))
			return FALSE;
		sprintf(nameStr, "%s %s", ETC[counter].cardHolderName, ETC[counter].cardHolderFamily);
		printTwoStringFarsi(nameStr, "»Â ‰«„:", PRN_NORM);

#else
        strcat(ETC[counter].serialETC, "|");
	    if (!printTwoStringNumericFarsi(ETC[counter].serialETC, "|”—Ì«· »—ç”»", PRN_NORM))
	        return FALSE;
        
        sprintf(nameStr, "%s %s", ETC[counter].cardHolderName, ETC[counter].cardHolderFamily);
        strcat(nameStr, "|");
        printTwoStringFarsi(nameStr, "|»Â ‰«„:", PRN_NORM);
#endif      
    	if (!printTransactionListCommonPart(ETC[counter].amount, ETC[counter].PAN, 
    			ETC[counter].retrievalReferenceNumber, 0, &(ETC[counter].dateTime), depositID))//MRF_NEW17
    		return FALSE;
    	
        check = compareDates(&ETC[counter].dateTime, &ETC[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, ETC[counter].amount, sumDailyValues);

        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();

        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);
            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }

        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


uint8 displayTransactionETCList(ETCTransLogST* ETC, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]	= {0, 0};	
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};                      /** sum of listed transactions value */
	int				counter                 	= 0;                        /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;                        /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	uint8			destinationCard[16]         = {0};
	uint8			nameStr[20]                 = {0};
    uint8			familyStr[20]               = {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();
    uint8           depositID[11 + 1]           = {0};
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        /* Adding 2string */
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, ETC[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);

        if (i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 12)) //6: header, 4: footer, 12: body
    	{
	    	/** TRANSACTIONS LOG ; LINE 1: TRANSACTION ETC */
            /* SERIAL ETC*/
		    justifyTwoStringFarsi("", "”—Ì«· »—ç”»", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, ETC[counter].serialETC);
		            
	        /** TRANSACTIONS LOG ; LINE 2: TRANSACTION card holder name */
	        memcpy(nameStr, ETC[counter].cardHolderName, strlen(ETC[counter].cardHolderName));
            memcpy(familyStr, ETC[counter].cardHolderFamily, strlen(ETC[counter].cardHolderFamily));
            strcat(nameStr," ");
            strcat(nameStr,familyStr);
	        
	    	justifyTwoStringFarsi("", "»Â ‰«„", lines[i++], PRN_NORM);
	        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, nameStr);
            memset(nameStr,0,sizeof(nameStr));
	
	        fillTransListCommonPartLines(lines, &i, ETC[counter].amount, ETC[counter].PAN,
	        		ETC[counter].retrievalReferenceNumber, 0, 
                    &(ETC[counter].dateTime), depositID);
	        
	        displayedCount++;
	        strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE, successETC);

    if (key != KBD_ENTER && key != KBD_CONFIRM) 
        return FALSE;
	else
		return TRUE;
}


uint8 merchantETCReport(argumentListST* args)
{    
    filesST*		files                   				= (filesST*) (args->argumentName);
    int             transactionNumber       				= 0;				/** transactions number with specified date in file */
    int             counter                 				= 0;				/** loop counter */
    uint8           valueWithComma[20]      				= {0};				/** sum value with comma, string form */
    uint8           transNum[10]            				= {0};
    uint8           fileName[FILE_NAME_LENTGH]				= {0};
    uint32			requestedNum                            = 0;
    uint8			activeUser[15 + 1]						= {0};
    uint8			activeUserTitle[15 + 1]					= {0};
    uint8           sumDailyValues[15 + 1]                  = {0};
    uint8			title[30]                               = {0};

    dateTimeST		dateTime;
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    ETCTransLogST   transactions[MAX_ETC_TRANS_LOG_RECORDS] 	= {0};

    memset(&dateTime, 0, sizeof(dateTimeST));

    strcpy(fileName, ETC_LOG_FILE);
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");
    strcpy(title, "ê“«—‘ ’‰œÊﬁ ⁄Ê«—÷");
    
    if (!readTransactionListFile(fileName, transactions, sizeof(ETCTransLogST), MAX_ETC_TRANS_LOG_RECORDS,
                        &startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    return FALSE;
    
    for (counter = requestedNum - 1; counter >= 0; counter--)
        sumStringNumbers(sumDailyValues, transactions[counter].amount, sumDailyValues);

    makeValueWithCommaStr(sumDailyValues, valueWithComma);

    /** PRINT TRANSACTIONS NUMBER IN DATES */
    sprintf(transNum, "%d", requestedNum); //#MRF_971226
    if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
        return FALSE;

    if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
        return FALSE;
    
    printStar();
    printBlankLines(BLANK_LINES_COUNT);//HNO_IDENT

    return TRUE;
}

//*************************  Buy Charge Topup  ***************************
//MRF_TOPUP
uint8 printTransactionBuyChargeTopup(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)                           
{
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "printTransactionBuyChargeTopup", "********START**********");
    
    if (!PrinterAccess(TRUE))    
        return FALSE;    

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);  
    
    /** PRINT HEADER */
    if (!prePrintFlags)
    	if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files)) 
    		return FALSE;  
    
    prePrintFlags = 0;
    
    /** PRINT COMMON PART */
    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files)) 
        return FALSE;
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "responseStatus: %d", messageSpec->responseStatus);
    if ((customer && !rePrint) && ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8) 
            || (messageSpec->responseStatus == 16)))
    { 
        makeTransPrintDataLog(files, messageSpec);
    	addTopupReport(messageSpec);
    }
    
    if(!customer)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: customerReceiptFile");
        fileRemove(files->customerReceiptFile);
    }
    
    /** PRINT TRANSACTION FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files)) 
        return FALSE; // this true because print is complete

    if (!rePrint)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile1");
        fileRemove(files->reversalReceiptFile);        
    }
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "printTransactionBuy", "********END***********");
    return TRUE;
}

//MRF_TOPUP
void addTopupReport(messageSpecST* messageSpec)  
{
    int16               retValue						= FAILURE;		/** write in file function return value */
    uint8               fileName[FILE_NAME_LENTGH]		= {0};
    uint8               oldFileName[FILE_NAME_LENTGH]	= {0};
    int32               shiftNO							= 0;
    uint8               shiftNOStr[8 + 1]				= {0};
    TopupTransLogST     topup;
    
    memset(&topup, 0, sizeof(TopupTransLogST));
    
    strcpy(fileName, TOPUP_LOG_FILE);
    
    topup.dateTime = messageSpec->dateTime;
    strcpy(topup.amount, messageSpec->amount);
    maskCardId(messageSpec->cardSpec.PAN, topup.PAN);
    strcpy(topup.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    topup.type = messageSpec->topup.type;
    topup.operatorType = messageSpec->topup.operatorType;
    strcpy(topup.mobileNo, messageSpec->topup.mobileNo);
    
    retValue = appendFixedFileInfo(fileName, &topup, 
                                     sizeof(TopupTransLogST), MAX_TOPUP_TRANS_LOG_RECORDS);    
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}


uint8 reprintTopupTransaction(argumentListST* args)
{    
    filesST*                        files	= (filesST*) (args->argumentName);
    messageSpecST                   messageSpec;
    lastCustomerReceiptST           lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_TOPUP_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;
    
    structCpy(&lastCustomerReceipt, &messageSpec);
    printTransactionBuyChargeTopup(files, &messageSpec, TRUE, TRUE);
    
    return TRUE;
}

//MRF_ETC
uint8 unsuccessTopupTransaction(argumentListST* args)
{    
    filesST*        			files                   	= (filesST*) (args->argumentName);
    dateTimeST					startDateTime				= {0, 0};
    dateTimeST					endDateTime					= {0, 0};
    int							transactionNumber			= 0;            /** charge number with specified date in file */
    uint32						requestedNum				= 0;            /** user requested transaction number, integer form */
    int							counter                 	= 0;            /** loop counter */
    uint8						sumValues[15 + 1]       	= {0};			/** sum of listed transactions value */
    uint8						fileName[FILE_NAME_LENTGH]	= {0};
    uint8						activeUser[15 + 1]			= {0};
    uint8						activeUserTitle[15 + 1]		= {0};
    uint8						title[30]                   = {0};
    uint8						referenceNum[1]				= {0};
    uint8                       serialETC[13 + 1]           = {0};
    uint8                       nameStr[20]                 = {0};
    reversalTransST				reversalInfo[50]   			= {0};
    uint8                       depositID[11 + 1]           = {0};
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "UNSUCCESS ETC");
    
    strcpy(fileName, REVERSAL_ETC_FILE);
    
    if (!readTransactionListFile(fileName, reversalInfo, sizeof(reversalTransST), MAX_UNSUCCESS_TOPUP_TRANS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    strcpy(title, "—Ì“ —«ò‰‘ ‰«„Ê›ﬁ ‘«—é „” ﬁÌ„");
    
    if (!displayunsuccessTopupTransaction(reversalInfo, transactionNumber, requestedNum, title, &startDateTime,
                   		&endDateTime, activeUserTitle, activeUser, sumValues))
           	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
                       
        if (!printTransactionListCommonPart(reversalInfo[counter].amount, reversalInfo[counter].PAN, referenceNum, 
    			reversalInfo[counter].STAN, /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
				&(reversalInfo[counter].SWdateTime), depositID))
    		return FALSE;       

        if (cancelFunction())
            return FALSE;

        if (!printDash())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


uint8 printETCTrakingTransaction(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)  
{   
    uint8   errorCode[20]       	= {0};
    uint8   len                 	= 0;
    uint8   status[220]          	= {0};
    uint8	valueWithComma[30]		= {0};
    uint8   amountPrintBuffer[20]   = {0};
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**printETCTrakingTransaction**");
    
    if (!PrinterAccess(TRUE))    
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
            return FALSE;

    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
        return FALSE;
    
    makeValueWithCommaStr(messageSpec->ETC.amount, valueWithComma);
#ifndef VX520
    sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma);
    if(!printTwoStringNumericFarsi(amountPrintBuffer, "„»·€", PRN_NORM))
		return FALSE;
#else
	if (!printThreeStringFarsi(" —Ì«·", valueWithComma, "„»·€", PRN_NORM, ALIGN_RIGHT, TRUE))
		return FALSE;
#endif
     
    if ((messageSpec->responseStatus == SUCCESS) 
            || (messageSpec->responseStatus == 8) 
            || (messageSpec->responseStatus == 16))
    {
#ifdef CASTLES_V5S //MRF_TTF
        sprintf(errorCode,"òœ:%s",messageSpec->ETC.error);
#else
        sprintf(errorCode,"òœ %s:",messageSpec->ETC.error);
#endif
        
        len = strlen(messageSpec->ETC.status);
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "len of status: %d", len);

#if defined(ICT250) || defined(IWL220)
        if ( len < 43)
        {
           if(!printTwoStringFarsi(errorCode, messageSpec->ETC.status, PRN_NORM))
                return FALSE;
        }

        else
        {
        	if(!printOneStringFarsi("⁄„·Ì«  „Ê›ﬁÌ  ¬„Ì“ »ÊœÂ Ê ÿÌ 72 ”«⁄  Ê«—Ì“ ", PRN_NORM, ALIGN_CENTER))
        		return FALSE;
        	if(!printTwoStringFarsi(errorCode, "„Ìê—œœ     ",PRN_NORM))
        		return FALSE;
        }
#else
        if ( len < 30)
        {
            if (!printTwoStringFarsi(errorCode, messageSpec->ETC.status, PRN_NORM_INVERSE))
                return FALSE;
        }
        else
        {
            strcpy(status, messageSpec->ETC.status);
            strcat(status, "  ");
            strcat(status, errorCode);
            if (!printOneStringFarsi(status, PRN_NORM, ALIGN_CENTER))
                return FALSE;
        }
#endif
    }
    else
    {
        if (!printOneStringFarsi("—ÂêÌ—Ì  —«ò‰‘ «‰Ã«„ ‰‘œ", PRN_NORM, ALIGN_CENTER))
            return FALSE;
    }

    /** PRINT FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files)) 
        return FALSE;

    return TRUE;
}


uint8 displayunsuccessTopupTransaction(reversalTransST* reversalInfo, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
    uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 4][32]			= {0, 0};		//HNO:change 400 to 2000 and 3 to 4 for footer /** 3: for the last three lines */
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};       	/** sum of listed transactions value */
	int				counter                 	= 0;            /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	uint8			referenceNum[1]				= {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();
    uint8           depositID[11 + 1]           = {0};
	
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
	    
    for (counter = requestedNum - 1; counter >= 0; counter--) 
    {
        //mgh: adding 2string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 8))
    	{
    		fillTransListCommonPartLines(lines, &i, reversalInfo[counter].amount, reversalInfo[counter].PAN, 
    				referenceNum, reversalInfo[counter].STAN, 
                    /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/
                    &(reversalInfo[counter].SWdateTime), depositID); 
    		displayedCount++;
    		strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
	}
 
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);

    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE, unsuccessTopup);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else 
    	return TRUE;
}

//MRF_TOPUP
uint8 transactionTopupList(argumentListST* args)
{    
    filesST*        	files                                        = (filesST*) (args->argumentName);
    dateTimeST			startDateTime                                = {0, 0};
    dateTimeST			endDateTime                                  = {0, 0};
    int					transactionNumber                            = 0;            /** charge number with specified date in file */
    uint32				requestedNum                                 = 0;            /** user requested transaction number, integer form */
    int					counter                                      = 0;            /** loop counter */
    uint8				serialETC[13 + 1]                            = {0};
    uint8				nameStr[20]                                  = {0};
    uint8               sumValues[15 + 1]                            = {0}; 
    uint8				fileName[FILE_NAME_LENTGH]                   = {0};
    uint8				activeUser[15 + 1]                           = {0};
    uint8				activeUserTitle[15 + 1]                      = {0};
    uint8				title[30]                                    = {0};
    TopupTransLogST     transactions[MAX_TOPUP_TRANS_LOG_RECORDS]    = {0}; 
    uint8               depositID[11 + 1]                            = {0};


    strcpy(fileName, TOPUP_LOG_FILE);
    
    if (!readTransactionListFile(fileName, transactions, sizeof(TopupTransLogST), MAX_TOPUP_TRANS_LOG_RECORDS, 
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
        
    strcpy(title, "—Ì“  —«ò‰‘ „Ê›ﬁ ‘«—é „” ﬁÌ„"); 

    if (!displayTransactionTopupList(transactions, transactionNumber, requestedNum, title, &startDateTime,
                		&endDateTime, activeUserTitle, activeUser, sumValues))
        	return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;
    
    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (!printTransactionListCommonPart(transactions[counter].amount, transactions[counter].PAN, 
        			transactions[counter].retrievalReferenceNumber, 0, &(transactions[counter].dateTime), depositID))//MRF_NEW17
    		return FALSE;
        
        if (cancelFunction())
            return FALSE;

        if (!printDash())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}

//MRF_TOPUP
uint8 displayTransactionTopupList(TopupTransLogST* transactions, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]			= {0, 0};		//HNO:change 700 to 3500 & 3 to 4 line for footer /** 3: fot the last three lines */
	uint16  		i                       	= 0;
	uint8			tempSumValues[15 + 1]   	= {0};      	/** sum of listed transactions value */
	int				counter                 	= 0;            /** loop counter */
	uint8			key 						= KBD_CANCEL;
	uint8			displayedCount          	= 0;            /** display counter */
	uint8			displayedSumValues[15 + 1]	= {0};
	terminalSpecST  terminalCapability			= getTerminalCapability();
    uint8           depositID[11 + 1]           = {0};
	
	     			                   
	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Request: %d", requestedNum);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "transactoins: %d", transactionNumber);
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0 ; counter--) 
    {
    	//mgh: adding two string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);
        
    	if ( i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 8)) //6: header, 4: footer, 8: body 
    	{
	    	fillTransListCommonPartLines(lines, &i, transactions[counter].amount, transactions[counter].PAN,
	    			transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime), depositID); 
	    	displayedCount++;
	    	strcpy(displayedSumValues, sumValues);
    	}
    }
    
    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sum %s", sumValues);
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);
    
    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader(title, lines, i, DISPLAY_TIMEOUT, FALSE, successTopup);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}

//MRF_TOPUP
uint8 merchantTopupReport(argumentListST* args)
{    
    filesST*		files                   				= (filesST*) (args->argumentName);
    uint32          userDateJalali          				= 0;				/** entered date by user (jalali) */
    int             reportYear              				= 0;				/** report year */
    int             reportMonth             				= 0;				/** report month */
    int             reportDay               				= 0;				/** report day */
    int             transactionNumber       				= 0;				/** transactions number with specified date in file */
    uint8           transValueSum[15 + 1]   				= {0};				/** sum of transactions value */
    uint8           tempSumValues[15 + 1]   				= {0};
    int             counter                 				= 0;				/** loop counter */
    uint8           lines[15][32]           				= {0};				/** display lines */
    uint8           valueWithComma[20]      				= {0};				/** sum value with comma, string form */
    TopupTransLogST transactions[MAX_TOPUP_TRANS_LOG_RECORDS] = {0}; 
    uint8           dateValueStr[11]        				= {0};
    uint8           transNum[10]            				= {0};
    uint8           numStr[7]               				= {0};
    uint16          i                                       = 0;
    uint8           key                                     = KBD_CANCEL;
    uint8           separatedStr[10][250]    				= {0, 0}; //ABS:CHANGE:960802
    uint8           wordWrapIndex           				= 0; 
    uint8           loop                    				= 0; 
    uint8           amountPrintBuffer[20]   				= {0}; 
    uint8           fileName[FILE_NAME_LENTGH]				= {0};
    uint8			transType								= TRANS_TOPUP;
    uint8			activeUser[15 + 1]						= {0};
    uint8			activeUserTitle[15 + 1]					= {0};
    merchantSpecST	merchantSpec;
    dateTimeST		dateTime;

    memset(&merchantSpec, 0, sizeof(merchantSpecST));
    memset(&dateTime, 0, sizeof(dateTimeST));
    memset(lines, 0, sizeof(lines));

    strcpy(fileName, TOPUP_LOG_FILE);
    strcpy(activeUserTitle, "ò«—»— ›⁄«·");
    
    if (!readBoxReportFile(fileName, transactions, sizeof(TopupTransLogST), MAX_TOPUP_TRANS_LOG_RECORDS,
    		&userDateJalali, &transactionNumber))
    	return FALSE;
    
    reportYear = getYear(userDateJalali);
    reportMonth = getMonth(userDateJalali);
    reportDay = getDay(userDateJalali);

   /* Adding 2string...*/
    for (counter = 0; counter < transactionNumber; counter++)
    {
        strcpy(tempSumValues, transValueSum);
        sumStringNumbers(tempSumValues, transactions[counter].amount, transValueSum);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "transValueSum= %s", transValueSum);
    }

    /** LINE 0 : HEADER */
    justifyOneStringFarsi("ê“«—‘ ’‰œÊﬁ Œ—Ìœ ‘«—é ¬‰Ì", lines[i++], PRN_NORM, ALIGN_CENTER);
    
    /** ACTIVE USER */
    if (strlen(activeUser) > 0)
    {
	    justifyTwoStringFarsi("", activeUserTitle, lines[i++], PRN_NORM);
	    sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, activeUser);
    }
    
    /** LINE 1 : DATE */
    justifyTwoStringFarsi("", " «—ÌŒ", lines[i++], PRN_NORM);

    sprintf(dateValueStr, "%04d/%02d/%02d", reportYear, reportMonth, reportDay);
    sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, dateValueStr);
    
    /** LINE 2 : TRANSACTION NUMBER */
    sprintf(transNum, "%d", transactionNumber);
    justifyTwoStringFarsi(transNum, " ⁄œ«œ", lines[i++], PRN_NORM);
    
    /** LINE 3 , 4 , 5 : TRANSACTIONS VALUE */
    justifyTwoStringFarsi(" ", "„Ã„Ê⁄", lines[i++], PRN_NORM);

    
    makeValueWithCommaStr(transValueSum, valueWithComma);
    if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT - strlen(" —Ì«·"))
    {
        if (strlen(valueWithComma) >= DISPLAY_CHARACTER_COUNT)
        {
            loop = wordWrapEnglish(valueWithComma, separatedStr, DISPLAY_CHARACTER_COUNT);
            for (wordWrapIndex = 0; wordWrapIndex <= loop; wordWrapIndex++)
            {
                sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, separatedStr[wordWrapIndex]);
            }
        }
        else
        {
            sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma);
        }
        sprintf(lines[i++], "%c%c%c%s", PRN_NORM, ALIGN_LEFT, FARSI, "—Ì«·");
    }
    else
    {
        sprintf(lines[i++], "%c%c%c%s%s", PRN_NORM, ALIGN_LEFT, FARSI, valueWithComma, " —Ì«·");
    }
    
    if (!PrinterAccess(TRUE))    
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);
    
    /** PRINT HEADER */
    dateTime = getDateTime();
    if (!printReceiptHeader(&dateTime, TRUE, files)) 
        return FALSE;
 
    /** PRINT HEADER */
    if (!printOneStringFarsi("ê“«—‘ ’‰œÊﬁ Œ—Ìœ ‘«—é ¬‰Ì", PRN_NORM, ALIGN_CENTER))
        return FALSE;
    
    printReceiptDate(dateTime.date," «—ÌŒ");
    
    /** PRINT ACTIVE USER */
    strcat(activeUserTitle, ":");
    if (strlen(activeUser) > 0)
	    if (!printTwoString(activeUser, activeUserTitle, PRN_NORM, FALSE))
	        return FALSE;
    
    /** PRINT TERMINAL ID */
    if (readMerchantSpec(files, &merchantSpec))
    {
        if (!printTwoStringNumericFarsi(merchantSpec.terminalID, "‘„«—Â Å«Ì«‰Â", PRN_NORM))
            return FALSE;
    }

    /** PRINT DASHES */
    if (!printStar())
        return FALSE;
    
    /** PRINT TRANSACTION NUMBER */
    sprintf(numStr, "%d", transactionNumber);
    if (!printTwoStringNumericFarsi(numStr, " ⁄œ«œ", PRN_NORM))
            return FALSE;

    /** PRINT TRANSACTIONS VALUE */
    if (strlen(valueWithComma) + strlen(" —Ì«·") + strlen("„Ã„Ê⁄:") <= getPrinterCharacterCount())
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "First");    
         if (!printThreeStringFarsi(" —Ì«·", valueWithComma, "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
            return FALSE;
    }
    else if (strlen(valueWithComma) + strlen(" —Ì«·") <= getPrinterCharacterCount())
    {
        if (!printOneStringFarsi("„Ã„Ê⁄:", PRN_NORM, ALIGN_RIGHT))
            return FALSE;

        sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma);
        if (!printOneStringFarsi(amountPrintBuffer, PRN_NORM, ALIGN_CENTER))
            return FALSE;
    }
    else
    {
        if (!printOneStringFarsi("„Ã„Ê⁄:", PRN_NORM, ALIGN_RIGHT))
            return FALSE;
        if (!printOneStringFarsi(valueWithComma, PRN_NORM, ALIGN_CENTER))
            return FALSE;       
        if (!printOneStringFarsi("—Ì«·", PRN_NORM, ALIGN_LEFT))
            return FALSE;       
    }

    /** PRINT EMPTY LINES */
    printBlankLines(BLANK_LINES_COUNT);

    return TRUE;
}

void addLoanReport(messageSpecST* messageSpec)
{
    int16          		retValue		= FAILURE;		/** write in file function return value */
    uint8				fileName[20]	= {0};
    loanPayTransLogST   loanPay;					/** loan transaction detail */

    memset(&loanPay, 0, sizeof(loanPayTransLogST));
    strcpy(fileName, LOAN_PAY_LOG_FILE);

    loanPay.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->loanPay.destinationCardPAN, loanPay.destinationCardPAN);
    strcpy(loanPay.amount, messageSpec->loanPay.payAmount);
    maskCardId(messageSpec->cardSpec.PAN, loanPay.destinationCardPAN);
    strcpy(loanPay.destinationCardHolderName, messageSpec->loanPay.destinationCardHolderName);
    strcpy(loanPay.destinationCardHolderFamily, messageSpec->loanPay.destinationCardHolderFamily);
    strcpy(loanPay.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(loanPay.PAN, messageSpec->cardSpec.PAN);

    retValue = appendFixedFileInfo(fileName, &loanPay,
                                     sizeof(loanPayTransLogST), MAX_LOAN_PAY_TRANS_LOG_RECORDS);
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}

//HNO_ADD_ROLL
uint8 printRollRequestTrans(filesST* files, messageSpecST* messageSpec)
{
	uint8	stanNo[7]               = {0};

    if (!PrinterAccess(TRUE))
        return FALSE;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
    	if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
    		return FALSE;

    prePrintFlags = 0;

    if (!printOneStringFarsi("—”Ìœ œ—ŒÊ«”  —Ê·", PRN_NORM, ALIGN_CENTER))
        return FALSE;

    /** PRINT TERMINAL ID */
    if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.terminalID, "‘„«—Â Å«Ì«‰Â", PRN_NORM))
        return FALSE;

    /** PRINT MERCHANT ID */
    if (!printTwoStringNumericFarsi(messageSpec->merchantSpec.merchantID, "‘„«—Â Å–Ì—‰œÂ", PRN_NORM))
        return FALSE;

    /** PRINT STAN */
    sprintf(stanNo, "%ld", messageSpec->merchantSpec.recieveSTAN);
    if (!printTwoStringNumericFarsi(stanNo, "‘„«—Â ÅÌêÌ—Ì", PRN_NORM))
        return FALSE;

    /** PRINT DATE AND TIME */
    if (!printReceiptDateTime(&(messageSpec->dateTime), TRUE))
        return FALSE;

    /** PRINT REFERENCE NUMBER */
    if ((messageSpec->responseStatus == SUCCESS) || (messageSpec->responseStatus == 8)
            || (messageSpec->responseStatus == 16))
    {
        removePad(messageSpec->retrievalReferenceNumber, ' ');
        if (!printTwoStringNumericFarsi(messageSpec->retrievalReferenceNumber, "‘„«—Â „—Ã⁄", PRN_NORM))
                return FALSE;
    }

    /** COUNT OF ROLL REQUEST */
    if (!printTwoStringNumericFarsi(messageSpec->rollRequest.rollCount, " ⁄œ«œ —Ê· œ—ŒÊ«” Ì", PRN_NORM))
		return FALSE;

    /** PRINT TRANS STATUS */
	if ((messageSpec->responseStatus != SUCCESS) && (messageSpec->responseStatus != 8)
		   && (messageSpec->responseStatus != 16))
	{
	   uint8 errorMessage[50] = {0};
	   uint8 errorCode[10]    = {0};
	   int   shpState         = 0;

		#ifdef CASTLES_V5S //MRF_TTF
		sprintf(errorCode, "òœ:%2d", messageSpec->responseStatus);
		#else
	    sprintf(errorCode, "òœ %2d :", messageSpec->responseStatus);
		#endif
	    shpState = getShaparakMessages(errorMessage, messageSpec->responseStatus);

	    if ((shpState == WARNING_TRANS || shpState == NO_RECEIVE || shpState == DUPLICATE_TRANS))
	    {
			if (!printTwoStringFarsi(errorCode, "⁄„·Ì«  ‰«„‘Œ’", PRN_NORM_INVERSE))
				return FALSE;
			#if defined(ICT250) || defined(IWL220)
			if (!printOneStringFarsi("‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì«  —« «“ ÿ—Ìﬁ  —«ò‰‘", PRN_NORM, ALIGN_CENTER))
				return FALSE;
			if (!printOneStringFarsi("—ÂêÌ—Ì ÅÌêÌ—Ì ‰„«ÌÌœ", PRN_NORM, ALIGN_CENTER))
				return FALSE;
			#else
			if (!printOneStringFarsi("‰ ÌÃÂ ﬁÿ⁄Ì ⁄„·Ì«  —« «“ ÿ—Ìﬁ  —«ò‰‘ —ÂêÌ—Ì° ÅÌêÌ—Ì ‰„«ÌÌœ.", PRN_NORM, ALIGN_CENTER))
				return FALSE;
			#endif
	   }
	   else if (!printTwoStringFarsi(errorCode, errorMessage, PRN_NORM_INVERSE))
	   {
			   return FALSE;
	   }
	}
	else if (!printOneStringFarsi("⁄„·Ì«  „Ê›ﬁ", PRN_BIG, ALIGN_CENTER))
		   return FALSE;


    /** PRINT TRANSACTION FOOTER */
    printTransactionFooter(FALSE, TRUE, TRUE, files);

    return TRUE;
}

//HNO_ADD_ROLL
void addRollRequestReport(messageSpecST* messageSpec)
{
    int16           retValue						= FAILURE;		/** write in file function return value */
    uint8			fileName[FILE_NAME_LENTGH]		= {0};
    rollTransLogST  transaction;

    memset(&transaction, 0, sizeof(rollTransLogST));

    strcpy(fileName, ROLL_LOG_FILE);
	
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "add roll request log");
    transaction.dateTime = messageSpec->dateTime;
    strcpy(transaction.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(transaction.rollCount, messageSpec->rollRequest.rollCount);

    retValue = appendFixedFileInfo(fileName, &transaction,
                                     sizeof(rollTransLogST), MAX_ROLL_REQUEST_TRANS_LOG_RECORDS);
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}

//HNO_ADD_ROLL
uint8 reprintRollRequestTransaction(argumentListST* args)
{
    filesST*				files	= (filesST*) (args->argumentName);
    messageSpecST			messageSpec;									/** last buy transaction information */
    lastCustomerReceiptST   lastCustomerReceipt;

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    if (!readLastCustomerReceiptFile(LAST_CUSTOMER_ROLL_REQUEST_RECIEPT_FILE, &lastCustomerReceipt))
    	return FALSE;

    structCpy(&lastCustomerReceipt, &messageSpec);
    printRollRequestTrans(files, &messageSpec);

    return TRUE;
}


/**
 * This function report latest successful transactions with fundamental informations.
 * @param   args [input]
 * @return  TRUE & FAlSE.
 */
uint8 completeChargeReport(argumentListST* args)
{
    filesST*        		files                       = (filesST*) (args->argumentName);
    uint8           		IDstr[6 + 1]    			= {0};
    uint8					id[7]						= {0};
    uint32					ID							= 0;
    uint32          		requestedNum      			= 0;
    uint8           		chargeTypeStr[10]   		= {0};
    uint8           		chargeStr[20]   			= {0};
    uint8					cardID[17]					= {0};
    uint8					valueWithComma[19 + 1]  	= {0};
    uint8   				amountPrintBuffer[20]   	= {0};
    uint8					countStr[7]					= {0};
    int             		transactionNumber 			= 0;
    int 					i 							= 0;
    int						count						= 0;
    cardTracksST    		cardTracks;
    cardSpecST      		cardSpec;
    chargeST				charge;
    dateTimeST				dateTime;

    memset(&charge, 0, sizeof(chargeST));
    memset(&cardTracks, 0, sizeof(cardTracksST));
    memset(&cardSpec, 0, sizeof(cardSpecST));
    memset(&dateTime, 0, sizeof(dateTimeST));

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**completeChargeReport**");

	if (!getStringValue("Ê—Êœ ‘‰«”Â ‘«—é:", 12, 1, IDstr, FALSE, FALSE, FALSE, "0", 0))
		return FALSE;

	ID = atoi(IDstr);
	if (!readSTANTransFromFile(CHARGE_INFO_FILE, &charge, sizeof(chargeST), MAX_CHARGE_TRANS, ID,
			&transactionNumber, &requestedNum))

	{
		displayMessageBox("⁄œ„ ÊÃÊœ «ÿ·«⁄«  ‘«—é!",WARNING_TRANS);
		return FALSE;
	}

	displayMessage("·ÿ›« ò«—  —« »ò‘Ìœ. . .", DISPLAY_START_LINE + 1, ALL_LINES);
	if(getCardHandle() <= 0)
		enableMSR();

	if (!readMagnetCardWait(cardTracks.track1, cardTracks.track2, cardTracks.track3, &cardTracks.track1Len, &cardTracks.track2Len, &cardTracks.track3Len))
	{
		return FALSE;
	}

	if (!readTrackData(files, &cardTracks, &cardSpec, FALSE))
	{
		return FALSE;
	}

	if (strcmp(charge.PAN, cardSpec.PAN) == 0)
	{
        clearDisplay(); //MRF_NEW12
        displayMessage("œ— Õ«· ç«Å ê“«—‘. . .", DISPLAY_START_LINE + 1, ALL_LINES);//MRF_NEW12
        
		/** PRINT HEADER */
		dateTime = getDateTime();
		if (!prePrintFlags)
			if (!printReceiptHeader(&dateTime, TRUE, files))
				return FALSE;

		if (!PrinterAccess(TRUE))
			return FALSE;

        /** PRINT TITLE */
        if (!printOneStringFarsi("ê“«—‘ œ” Â «Ì ‘«—é", PRN_NORM, ALIGN_CENTER))
            return FALSE;

		/** PRINT TERMINAL ID */
		if (!printTwoStringNumericFarsi(charge.terminalID, "‘„«—Â Å«Ì«‰Â", PRN_NORM))
			return FALSE;

		sprintf(id, "%ld", charge.id);
		if (!printTwoStringNumericFarsi(id,"‘‰«”Â ‘«—é",PRN_NORM))
			return FALSE;

		sprintf(countStr, "%d", charge.chargeCount);
		if (!printTwoStringNumericFarsi(countStr," ⁄œ«œ",PRN_NORM))
			return FALSE;

		/** PRINT PAN CARD */
		maskCardId(cardSpec.PAN, cardID);
		removePad(cardID, ' ');
        
#ifdef CASTLES_V5S //MRF_NEW10
        reversPartString(cardID);
#endif
        if (!printTwoStringNumericFarsi(cardID, "‘„«—Â ò«— ", PRN_NORM))
			return FALSE;

		printStar();

		count = charge.chargeCount;
		for(i = 1 ; i <= count ; i++)
		{
			/** PRINT CHARGE TYPE & CHARGE AMOUNT*/
			getChargeTypeStr(charge.chargeInfo[i].type, chargeTypeStr);
			strcpy(chargeStr,  "„»·€ ‘«—é");
			strcat(chargeStr, chargeTypeStr);//cat charge type to amount charge
            makeValueWithCommaStr(charge.chargeInfo[i].amount, valueWithComma);
            sprintf(amountPrintBuffer, "%s —Ì«·", valueWithComma);
			if (!printTwoStringNumericFarsi(amountPrintBuffer, chargeStr, PRN_NORM))
				return FALSE;

			/** PRINT CHARGE SERIAL*/
			removePad(charge.chargeInfo[i].serial, ' ');
#ifndef VX520		//++ABS:980223
			if (!printTwoStringNumericFarsi(charge.chargeInfo[i].serial, "”—Ì«· ‘«—é", PRN_NORM))
				return FALSE;
#else
			if (!printTwoStringNumericFarsi(charge.chargeInfo[i].serial, "”—Ì«·", PRN_NORM))
				return FALSE;
#endif
			if (!printTwoStringNumericFarsi(charge.chargeInfo[i].PIN, "—„“ ‘«—é", PRN_NORM))
				return FALSE;

	        removePad(charge.chargeInfo[i].ReferenceNumber, ' ');
	        if (!printTwoStringNumericFarsi(charge.chargeInfo[i].ReferenceNumber, "‘„«—Â „—Ã⁄", PRN_NORM))
	                return FALSE;

	        /** PRINT DATE AND TIME */
	        if (!printReceiptDateTime(&(charge.chargeInfo[i].dateTime), TRUE))
	            return FALSE;

			printDash3();
		}

		if(!printOneStringFarsi("„”∆Ê·Ì  «Ì‰ —”Ìœ »Â ⁄ÂœÂ Å–Ì—‰œÂ «” ", PRN_NORM, ALIGN_CENTER))
			return FALSE;

		printBlankLines(BLANK_LINES_COUNT);
    }
    else
    	displayMessageBox("ò«—  „⁄ »— ‰Ì” !",WARNING_TRANS);
    
    return TRUE;
}


uint8 readAllUsersTransactionListFile(uint8* fileName, void* transaction, uint16 structLen, uint16 maxRecord,
							  	dateTimeST* startDateTime, dateTimeST* endDateTime, int* transactionNum,
								uint32* requestedNum,uint8* activeUserTitle, uint8* activeUser)
{
    int             searchTransRes          = -2;			/** search for transaction with specified date in transactions file */
    int             startRecordNum          = 0;			/** start record number of transactions with specified date in file */
    int             endRecordNum            = 0;			/** end record number of transactions with specified date in file */
    int				beginIndexInFile		= 0;            /** index of beginning requested transaction in transactions file */
    int16			retValue 				= FAILURE;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**readallusersTransactionListFile**");

    if (fileExist(fileName) != SUCCESS)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "File transaction unsuccess not exist!");
    	return FALSE;
    }

    searchTransRes = searchDateTimeRangeInFixedFile(fileName, structLen, 0,
    		startDateTime, endDateTime, maxRecord, &startRecordNum, &endRecordNum);

    if (searchTransRes == -2 || startRecordNum == -2 || endRecordNum == -2)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in Start time trans not exist !!");
        return FALSE;
    }

    if (startRecordNum == -1 || endRecordNum == -1)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in End time trans not exist !!");
        return FALSE;
    }

    *transactionNum = endRecordNum - startRecordNum + 1;

    *requestedNum = *transactionNum;

    if (*requestedNum > maxRecord)
    	if (*transactionNum <= maxRecord)
    		*requestedNum = *transactionNum;
    	else
    		*requestedNum = maxRecord;

    if (*requestedNum == 0 || *requestedNum > *transactionNum)
        *requestedNum = *transactionNum;

    //show the last transactions
    beginIndexInFile = *transactionNum - *requestedNum + startRecordNum;

    retValue = readFixedFileInfoArray(fileName,(uint8*) transaction, structLen, beginIndexInFile,
                                        *requestedNum, maxRecord);
    if (retValue != SUCCESS)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", " in readFixedFileInfoArray trans not exist !!");
        return FALSE;
    }

    return TRUE;
}


uint8 deletAllDependentFilesShift(void)
{
    int16           retValue                = FAILURE;
    userNodeST*     currentNode             = NULL;
    uint8           file1[FILE_NAME_LENTGH] = {0};
    uint8           file2[FILE_NAME_LENTGH] = {0};
    uint8           file3[FILE_NAME_LENTGH] = {0};
    uint8           username[16 + 1]        = {0};
  
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**deletAllDependentFilesShift");
    
    currentNode = getUserList();
    while (currentNode)
    {
        showLog(ALL_POS, __FILE__, __LINE__, FATAL , "", "%s", currentNode->data.userName);
        strcpy(file1, LAST_CUSTOMER_BUY_RECIEPT_FILE);
        strcpy(file2, BUY_LOG_FILE);
        strcpy(file3, REVERSAL_BUY_LOG_FILE);

        strcpy(username, currentNode->data.userName);
        if (strcmp(username , "„œÌ—") == 0)
        {
            retValue = fileRemove(file1);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file1);
            if (retValue != SUCCESS)
                return retValue;

            retValue = fileRemove(file2);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file2);
            if (retValue != SUCCESS)
                return retValue;

            retValue = fileRemove(file3);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file3);
            if (retValue != SUCCESS)
                return retValue;
        }
        else
        {
            retValue = deletUserFiles(username);
            if (retValue != SUCCESS)
                   return retValue;
        }
        currentNode = currentNode->next;
    }
    
    return SUCCESS;
}

uint8 deletUserFiles(uint8* username)
{
    int16           retValue                = FAILURE;
    uint8           file1[FILE_NAME_LENTGH] = {0};
    uint8           file2[FILE_NAME_LENTGH] = {0};
    uint8           file3[FILE_NAME_LENTGH] = {0};
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**deletUserFiles");
    
    strcpy(file1, LAST_CUSTOMER_BUY_RECIEPT_FILE);
    strcpy(file2, BUY_LOG_FILE);
    strcpy(file3, REVERSAL_BUY_LOG_FILE);
            
    strcat(file1, username);
    strcat(file2, username);
    strcat(file3, username);

    retValue = fileRemove(file1);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file1);
    if (retValue != SUCCESS)
            return retValue;

    retValue = fileRemove(file2);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file2);
    if (retValue != SUCCESS)
            return retValue;

    retValue = fileRemove(file3);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**FileRemove:%s", file3);
    if (retValue != SUCCESS)
            return retValue;
    
    return SUCCESS;
}


uint8 printTransactionCharity(filesST* files, messageSpecST* messageSpec, uint8 customer, uint8 rePrint)
{
    uint8	reversalCancelled		= FALSE;		/** is reversal canceled? */
    uint8	valueWithComma[20]		= {0};
    uint8   amountPrintBuffer[20]   = {0}; 

    if (!PrinterAccess(TRUE))
        return reversalCancelled;

    displayMessage("ç«Å —”Ìœ ...", DISPLAY_START_LINE + 1, ALL_LINES);

    /** PRINT HEADER */
    if (!prePrintFlags)
        if (!printReceiptHeader(&(messageSpec->dateTime), TRUE, files))
            return reversalCancelled;

    prePrintFlags = 0;

    if (!printTransactionCommonPart(messageSpec, customer, rePrint, files))
        return reversalCancelled;

    if ((customer && !rePrint) && ((messageSpec->responseStatus == SUCCESS)
            || (messageSpec->responseStatus == 8)
            || (messageSpec->responseStatus == 16)))
    {
        /** CANCEL REVERSAL & ... */
        reversalCancelled = TRUE;

        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);

        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalTransFile");
        fileRemove(files->reversalTransFile);

        addTransToSettlementFile(files, messageSpec);
        makeTransPrintDataLog(files, messageSpec);
    	addCharityReport(messageSpec);
    }

    /** PRINT FOOTER */
    if (!printTransactionFooter(rePrint, customer, TRUE, files))
        return reversalCancelled;

   if ((!reversalCancelled) && (!rePrint))
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**REMOVE: reversalReceiptFile");
        fileRemove(files->reversalReceiptFile);
    }

    return reversalCancelled;
}

//HNO_CHARITY
void addCharityReport(messageSpecST* messageSpec)
{
    int16           retValue						= FAILURE;		/** write in file function return value */
    uint8			fileName[FILE_NAME_LENTGH]		= {0};
    charityST   	transaction;

    memset(&transaction, 0, sizeof(charityST));

    strcpy(fileName, CHARITY_LOG_FILE);

    transaction.dateTime = messageSpec->dateTime;
    maskCardId(messageSpec->cardSpec.PAN, transaction.PAN);
    strcpy(transaction.amount, messageSpec->amount);
    strcpy(transaction.retrievalReferenceNumber, messageSpec->retrievalReferenceNumber);
    strcpy(transaction.InstituteCode, messageSpec->charity.InstituteCode);//HNO_DEBUG

    retValue = appendFixedFileInfo(fileName, &transaction,
                                     sizeof(charityST), MAX_CHARITY_TRANS_LOG_RECORD);
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
}

//HNO_CHARITY
uint8 displayTransactionCharityList(charityST* transactions, int transactionNumber, uint32 requestedNum, uint8* title,
		dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8					lines[MAX_LINE_SUCCESS_TRANS_DISPLAY + 4][32]	= {0, 0};				//HNO:change 700 to 3500 & 3 to 4 line for footer /** 3: fot the last three lines */
	uint16  				i                       						= 0;		
	uint8					tempSumValues[15 + 1]   						= {0};      			/** sum of listed transactions value */
	int						counter                 						= 0;            		/** loop counter */
	uint8					key 											= KBD_CANCEL;		
	uint8					displayedCount          						= 0;            		/** display counter */
	uint8					displayedSumValues[15 + 1]						= {0};
	terminalSpecST  		terminalCapability								= getTerminalCapability();
    uint8           		depositID[11 + 1]           					= {0};

	
	memset(lines, 0, sizeof(lines));
	
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);
    
    /** TRANSACTIONS LOG */
    for (counter = requestedNum - 1; counter >= 0 ; counter--)
    {
    	//mgh: adding two string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);

    	if ( i < (MAX_LINE_SUCCESS_TRANS_DISPLAY - 6 - 4 - 8)) //6: header, 4: footer, 8: body
    	{
	    	fillTransListCommonPartLines(lines, &i, transactions[counter].amount, transactions[counter].PAN,
	    			transactions[counter].retrievalReferenceNumber, 0, 
                    &(transactions[counter].dateTime), depositID);
	    	displayedCount++;
	    	strcpy(displayedSumValues, sumValues);
    	}
    }

    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
    	justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
    }

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sum %s", sumValues);
    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);

    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader(title, lines, i, DISPLAY_TIMEOUT, FALSE,successCharity);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}


uint8 transactionCharityList(argumentListST* args)
{
    filesST*        files                                       = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    charityST   	transactions[MAX_CHARITY_TRANS_LOG_RECORD] 	= {0};
    int				transactionNumber                           = 0;            /** charge number with specified date in file */
    int				counter                                     = 0;            /** loop counter */
    uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
    uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
    uint8			fileName[FILE_NAME_LENTGH]                  = {0};
    uint8			activeUser[15 + 1]                          = {0};
    uint8			title[30]                                   = {0};
    uint8			activeUserTitle[15 + 1]                     = {0};
    uint8           check                                       = FALSE;
    uint8           sumDailyValues[15 + 1]                      = {0};
    uint8			tempSumValues[15 + 1]                       = {0};
    uint8			valueWithComma[20]                          = {0};
    uint8			instituteName[50]							= {0};//HNO_DEBUG
    uint8           depositID[11 + 1]                           = {0};


    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "*********charityList********");
    strcpy(fileName, CHARITY_LOG_FILE);

    if (!readTransactionListFile(fileName, transactions, sizeof(charityST), MAX_CHARITY_TRANS_LOG_RECORD,
    						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

    /** LINE 0 : HEADER */
    strcpy(title, "—Ì“ —«ò‰‘ „Ê›ﬁ ‰ÌòÊò«—Ì");

    if (!displayTransactionCharityList(transactions, transactionNumber, requestedNum, "‰ÌòÊò«—Ì „Ê›ﬁ", &startDateTime,
    		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
    	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;

    if (! printReceiptDate(transactions[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;

    printDash3();

    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(transactions[counter].dateTime.date," «—ÌŒ"))
               return FALSE;
           printDash3();
        }

        //HNO_DEBUG
        getCharityInstituteName(instituteName, transactions[counter].InstituteCode);
#ifdef VX520
		if (!printTwoStringFarsi(instituteName, "‰«„ „Ê””Â:", PRN_NORM))
			return FALSE;
#else
        strcat(instituteName, "|");
        if (!printTwoStringFarsi(instituteName, "|‰«„ „Ê””Â:", PRN_NORM))
            return FALSE;
#endif
    	if (!printTransactionListCommonPart(transactions[counter].amount, transactions[counter].PAN,
        			transactions[counter].retrievalReferenceNumber, 0, &(transactions[counter].dateTime), depositID))//MRF_NEW17
    		return FALSE;

        check = compareDates(&transactions[counter].dateTime, &transactions[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, transactions[counter].amount, sumDailyValues);

        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();

        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);

            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }

        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))//HNO_DEBUG2
    	return FALSE;

    return TRUE;
}


uint8 displayunsuccessCharityTransaction(reversalTransST* reversalInfo, int transactionNumber, uint32 requestedNum,
		uint8* title, dateTimeST* startDateTime, dateTimeST* endDateTime, uint8* activeUserTitle, uint8* activeUser, uint8* sumValues)
{
	uint8			lines[MAX_LINE_UNSUCCESS_TRANS_DISPLAY + 4][32]	= {0, 0};
	uint16  		i                       						= 0;
	uint8			tempSumValues[15 + 1]   						= {0};                          /** sum of listed transactions value */
	int				counter                 						= 0;                            /** loop counter */
	uint8			key 											= KBD_CANCEL;
	uint8			displayedCount          						= 0;                            /** display counter */
	uint8			displayedSumValues[15 + 1]						= {0};
	uint8			referenceNum[1]									= {0};
	terminalSpecST  terminalCapability								= getTerminalCapability();
    uint8           depositID[11 + 1]                               = {0};

	memset(lines, 0, sizeof(lines));
	fillTransListHeaderLines(lines, &i, title, activeUserTitle, activeUser, startDateTime, endDateTime);

    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        //mgh: adding 2string...
        strcpy(tempSumValues, sumValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumValues);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sumValues= %s", sumValues);

    	if (i < (MAX_LINE_UNSUCCESS_TRANS_DISPLAY - 6 - 4 - 8))
    	{
            fillTransListCommonPartLines(lines, &i, reversalInfo[counter].amount, reversalInfo[counter].PAN,
    				referenceNum, reversalInfo[counter].STAN,
                    &(reversalInfo[counter].SWdateTime), depositID); 

    		displayedCount++;
    		strcpy(displayedSumValues, sumValues);
    	}
    }

    if (requestedNum != displayedCount) //displayed transactions are less than requested
    {
    	justifyOneStringFarsi("»—«Ì „‘«ÂœÂ ò«„·", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi(" —«ò‰‘ Â« ·Ì” ", lines[i++], PRN_NORM, ALIGN_CENTER);
		justifyOneStringFarsi("—« ç«Å ‰„«ÌÌœ.", lines[i++], PRN_NORM, ALIGN_CENTER);
	}

    fillTransListFooterLines(lines, &i, transactionNumber, displayedCount, displayedSumValues);

    if (!terminalCapability.graphicCapability)
    	key = displayScrollable("", lines, i, DISPLAY_TIMEOUT, FALSE);
    else
    	key = displayScrollableWithHeader("", lines, i, DISPLAY_TIMEOUT, FALSE,unsuccessCharity);

    if (key != KBD_ENTER && key != KBD_CONFIRM)
        return FALSE;
    else
    	return TRUE;
}


uint8 unsuccessCharityTransaction(argumentListST* args)
{
    filesST*        			files                                 = (filesST*) (args->argumentName);
    dateTimeST					startDateTime                         = {0, 0};
    dateTimeST					endDateTime                           = {0, 0};
    reversalTransST				reversalInfo[MAX_UNSUCCESS_CHARITY_TRANS] = {0};
    int							transactionNumber			= 0;            /** charge number with specified date in file */
    int							counter                 	= 0;            /** loop counter */
    uint32						requestedNum				= 0;            /** user requested transaction number, integer form */
    uint8						sumValues[15 + 1]       	= {0};          /** sum of listed transactions value */
    uint8						fileName[FILE_NAME_LENTGH]	= {0};
    uint8						activeUser[15 + 1]			= {0};
    uint8						activeUserTitle[15 + 1]		= {0};
    uint8						title[30]                   = {0};
    uint8						referenceNum[1]				= {0};
    uint8                       check                       = FALSE;
    uint8                       sumDailyValues[15 + 1]      = {0};
    uint8                       tempSumValues[15 + 1]       = {0};
    uint8                       valueWithComma[20]          = {0};
	uint8						instituteName[50]			= {0};//HNO_DEBUG
    uint8                       depositID[11 + 1]           = {0};

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****unsuccess charity****");

    strcpy(fileName, REVERSAL_CHARITY_LOG_FILE);

    if (!readTransactionListFile(fileName, reversalInfo, sizeof(reversalTransST), MAX_UNSUCCESS_CHARITY_TRANS,
        						&startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
    
	strcpy(title, "—Ì“ —«ò‰‘ ‰«„Ê›ﬁ ‰ÌòÊò«—Ì");
    if (!displayunsuccessCharityTransaction(reversalInfo, transactionNumber, requestedNum, "‰ÌòÊò«—Ì ‰«„Ê›ﬁ", &startDateTime,
                   		&endDateTime, activeUserTitle, activeUser, sumValues))//ABS:CHANGE
           	return FALSE;

    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
    	return FALSE;

    if (!printReceiptDate(reversalInfo[requestedNum - 1].dateTime.date," «—ÌŒ"))
       return FALSE;

    printDash3();

    /** PRINT TRANSACTIONS DETAILS */
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        if (check != 0)
        {
           if (!printReceiptDate(reversalInfo[counter].dateTime.date," «—ÌŒ"))
               return FALSE;

           printDash3();
        }
        
        getCharityInstituteName(instituteName, reversalInfo[counter].charity.InstituteCode);

#ifdef VX520
		if (!printTwoStringFarsi(instituteName, "‰«„ „Ê””Â:", PRN_NORM))
			return FALSE;
#else   
        strcat(instituteName, "|");
        if (!printTwoStringFarsi(instituteName, "|‰«„ „Ê””Â:", PRN_NORM))
            return FALSE;
#endif

    	if (!printTransactionListCommonPart(reversalInfo[counter].amount, reversalInfo[counter].PAN, referenceNum,
    			reversalInfo[counter].STAN, /*--MRF_NEW2 &(reversalInfo[counter].dateTime)*/&(reversalInfo[counter].SWdateTime), depositID))//MRF_NEW17
    		return FALSE;

        check = compareDates(&reversalInfo[counter].dateTime, &reversalInfo[counter - 1].dateTime, FALSE);
        strcpy(tempSumValues, sumDailyValues);
        sumStringNumbers(tempSumValues, reversalInfo[counter].amount, sumDailyValues);

        if (counter != 0 && check == 0)
            printDash2();
        else
            printDash3();

        if (check != 0)
        {
            makeValueWithCommaStr(sumDailyValues, valueWithComma);

            if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
                return FALSE;

            printStar();
            memset(sumDailyValues, 0, sizeof(sumDailyValues));
        }

        if (cancelFunction())
            return FALSE;
    }

    if (!printTransactionListFooter(transactionNumber, requestedNum, sumValues))
    	return FALSE;

    return TRUE;
}


uint8 reprintCharityTransaction(argumentListST* args)
{
    filesST*                files						= (filesST*) (args->argumentName);
    uint8                   fileName[FILE_NAME_LENTGH]	= {0};
    messageSpecST           messageSpec;
    lastCustomerReceiptST	lastCustomerReceipt;
    uint8					loginUserName[15 + 1] 		= { 0 };
	uint8					selectUser[16]				= {0};

    memset(&messageSpec, 0, sizeof(messageSpecST));
    memset(&lastCustomerReceipt, 0, sizeof(lastCustomerReceiptST));

    strcpy(fileName, LAST_CUSTOMER_CHARITY_RECIEPT_FILE);

    if (!readLastCustomerReceiptFile(fileName, &lastCustomerReceipt))
    	return FALSE;

    structCpy(&lastCustomerReceipt, &messageSpec);
    printTransactionCharity(files, &messageSpec, TRUE, REPRINT);

	return TRUE;
}


uint8 merchantCharityReport(argumentListST* args)
{
    filesST*        files                                       = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                               = {0, 0};
    dateTimeST		endDateTime                                 = {0, 0};
    charityST	    transactions[MAX_CHARITY_TRANS_LOG_RECORD] 	= {0};
    int				transactionNumber                           = 0;            /** charge number with specified date in file */
    int				counter                                     = 0;            /** loop counter */
    uint32			requestedNum                                = 0;            /** user requested transaction number, integer form */
    uint8			sumValues[15 + 1]                           = {0};          /** sum of listed transactions value */
    uint8			fileName[FILE_NAME_LENTGH]                  = {0};
    uint8			activeUser[15 + 1]                          = {0};
    uint8			title[30]                                   = {0};
    uint8			activeUserTitle[15 + 1]                     = {0};
    uint8           check                                       = FALSE;
    uint8           sumDailyValues[15 + 1]                      = {0};
    uint8			tempSumValues[15 + 1]                       = {0};
    uint8			valueWithComma[20]                          = {0};
    uint8           transNum[5]                                 = {0};
    int             sumCountValues                      		= 0;
    uint8           sumAllUsersValues[15 + 1]                   = {0};

    strcpy(fileName, CHARITY_LOG_FILE);
	strcpy(title, "ê“«—‘ ’‰œÊﬁ ‰ÌòÊò«—Ì");

	//HNO_DEBUG
    if (!readTransactionListFile(fileName, transactions, sizeof(charityST), MAX_CHARITY_TRANS_LOG_RECORD,
                        &startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;

	if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
		return FALSE;

	for (counter = requestedNum - 1; counter >= 0; counter--)
		sumStringNumbers(sumDailyValues, transactions[counter].amount, sumDailyValues);

	makeValueWithCommaStr(sumDailyValues, valueWithComma);

	sprintf(transNum, "%d", requestedNum); //#MRF_971226
	if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
		return FALSE;

	if (!printThreeStringFarsi(" —Ì«·", valueWithComma , "„Ã„Ê⁄", PRN_NORM, ALIGN_RIGHT, TRUE))
		return FALSE;

	printStar();
	printBlankLines(BLANK_LINES_COUNT);

    return TRUE;
}

//HNO_INIT
void addInitializeReport(messageSpecST* messageSpec, uint8 response)  
{
    int16                               retValue                    = FAILURE;          /** write in file function return value */
    uint8                               fileName[FILE_NAME_LENTGH]	= {0}; 
    InitializeLogST                     initialize;                                        /** billPay transaction detail */
    
    memset(&initialize, 0, sizeof(InitializeLogST));
    strcpy(fileName, INITIALIZE_LOG_FILE);
   
    initialize.dateTime = messageSpec->dateTime;
    strcpy(initialize.macVersion, messageSpec->versionKey.macVersion);
    strcpy(initialize.pinVersion, messageSpec->versionKey.pinVersion);
    initialize.transType = messageSpec->transType;
   
    if(response)
    {
        strcpy(initialize.errorMsg, "„Ê›ﬁ");
        retValue = updateFixedFileLastRecord(fileName, &initialize, 
                sizeof(InitializeLogST), MAX_INITIALIZE_TRANS_LOG_RECORDS); 
    }
      
    else
    {
        strcpy(initialize.errorMsg , "‰«„Ê›ﬁ");
        retValue = appendFixedFileInfo(fileName, &initialize, 
            sizeof(InitializeLogST), MAX_INITIALIZE_TRANS_LOG_RECORDS);
    }
    
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);

}

//HNO_INIT
uint8 transactionInitializeList(argumentListST* args)
{
    filesST*        files                               = (filesST*) (args->argumentName);
    dateTimeST		startDateTime                       = {0, 0};
    dateTimeST		endDateTime                         = {0, 0};
    int             transactionNumber                   = 0;            /** charge number with specified date in file */
    uint32			requestedNum                        = 0;            /** user requested transaction number, integer form */
    int				counter                             = 0;            /** loop counter */
    uint8			fileName[FILE_NAME_LENTGH]          = {0}; 
    uint8			activeUser[15 + 1]                  = {0};
    uint8			activeUserTitle[15 + 1]             = {0};
    uint8			title[30]                           = {0};
    uint8			transNum[10]                        = {0};
    InitializeLogST transactions[MAX_INITIALIZE_TRANS_LOG_RECORDS]      = {0}; 

    strcpy(fileName, INITIALIZE_LOG_FILE);
    
    if (!readTransactionListFile(fileName, transactions, sizeof(InitializeLogST), MAX_INITIALIZE_TRANS_LOG_RECORDS, 
                &startDateTime, &endDateTime, &transactionNumber, &requestedNum, activeUserTitle, activeUser))
    	return FALSE;
        
    strcpy(title, "ê“«—‘ ÅÌò—»‰œÌ"); 
    if (!printTransactionListHeader(files, title, activeUserTitle, activeUser, &startDateTime, &endDateTime))
        return FALSE;
    
    for (counter = requestedNum - 1; counter >= 0; counter--)
    {
        printReceiptDateTime(&(transactions[counter].dateTime), TRUE);
        
        if (!printTwoStringNumericFarsi(transactions[counter].macVersion, "‘„«—Â ò·Ìœ „ò", PRN_NORM))
            return FALSE;
        if (!printTwoStringNumericFarsi(transactions[counter].pinVersion, "‘„«—Â ò·Ìœ ÅÌ‰", PRN_NORM))
            return FALSE;
        if(transactions[counter].transType == TRANS_INITIALIZE)
			if (!printTwoStringFarsi(transactions[counter].errorMsg, " —«ò‰‘ ÅÌò—»‰œÌ:", PRN_NORM))//ABS:CHANGE
                return FALSE;
        if(transactions[counter].transType == TRANS_LOGON)
            if (!printTwoStringFarsi(transactions[counter].errorMsg, " —«ò‰‘  »«œ· ò·Ìœ", PRN_NORM))
                return FALSE;

        printDash3();
    }

    if (cancelFunction())
        return FALSE;
    
    sprintf(transNum, "%d", transactionNumber);
if (!printTwoStringNumericFarsi(transNum, " ⁄œ«œ", PRN_NORM))
    return FALSE;
    
    printBlankLines(BLANK_LINES_COUNT);

    return TRUE;
}


uint8 convertMessageSpecST(void)
{
    
}

