
//uint8 reader(void);
static uint8 menu[100][40];
void iterator(mxml_node_t*        node);
mxml_node_t *				/* O - Element node or NULL */
mxmlFind(mxml_node_t *node,	/* I - Current node */
mxml_node_t *top,	/* I - Top node */
const char  *name,	/* I - Element name or NULL for any */
const char  *attr,	/* I - Attribute name, or NULL for none */
const char  *value,	/* I - Attribute value, or NULL for any */
int         descend);
static uint8           	activeUserName[16] = { 0 };//+HNO,ABS_971128
/*
* Add Item in tree menu.
* @param   menuItemList [input]: menu item list
* @param   menuItemNameEN [input]: parent node
* @param   menuItemNameEN [input]: child node
* @return  None.
*/
void addMenuItemList(menuItemST** menuItemList, enum menuItemNameEN  parent, enum menuItemNameEN child);
void fillFileInfo(serverSpecST* serverSpec, uint8 server);



struct {
	uint8      val;
	uint8 *str;
} conversion2[] = {
	{ FARSI, "FARSI" },
	{ ENGLISH, "ENGLISH" },
	{ 10, "10" },
	{ ALIGN_CENTER, "ALIGN_CENTER" },
	{ ALIGN_LEFT, "ALIGN_LEFT" },
	{ ALIGN_RIGHT, "ALIGN_RIGHT" },
	{ 0, "0" },
	{ TRUE, "TRUE" },
	{ FALSE, "FALSE" },
	{ NORMAL_STRING, "NORMAL_STRING" },
	{ SMALL_STRING, "SMALL_STRING" },
	{ BIG_STRING, "BIG_STRING" },
	{ SMALL_INVERT_STRING, "SMALL_INVERT_STRING" },
	{ NORMAL_INVERT_STRING, "NORMAL_INVERT_STRING" },
	{ BIG_INVERT_STRING, "BIG_INVERT_STRING" },
	{ NULL, "NULL" },
	{ 0, "0" },
	{ 1, "1" },
	{ 2, "2" },
	{ 3, "3" },
	{ 4, "4" },
	{ 5, "5" },
	{ 6, "6" },
	{ 7, "7" },
	{ 8, "8" },
	{ 9, "9" },
};

uint8 str2define(const char *str)
{
	int j;
	for (j = 0; j < 26; ++j)
	if (!strcmp(str, conversion2[j].str))
		return conversion2[j].val;
}


struct {
	enum menuItemNameEN      val;
	uint8 *str;
} conversion[] = {
	{ 0, "0" },
	{ MENU_CARD_ROOT, "MENU_CARD_ROOT" },
	{ MENU_CARD_ITEM_BUY, "MENU_CARD_ITEM_BUY" },
	{ MENU_CARD_ITEM_BALANCE, "MENU_CARD_ITEM_BALANCE" },
	{ MENU_CARD_ITEM_BILL_PAY, "MENU_CARD_ITEM_BILL_PAY" },
	{ MENU_CARD_ITEM_BUY_CHARGE, "MENU_CARD_ITEM_BUY_CHARGE" },
	{ MENU_CARD_IRANCELL, "MENU_CARD_IRANCELL" },
	{ MENU_CARD_IRANCELL_20000, "MENU_CARD_IRANCELL_20000" },
	{ MENU_CARD_IRANCELL_50000, "MENU_CARD_IRANCELL_50000" },
	{ MENU_CARD_IRANCELL_100000, "MENU_CARD_IRANCELL_100000" },
	{ MENU_CARD_IRANCELL_200000, "MENU_CARD_IRANCELL_200000" },
	{ MENU_CARD_IRANCELL_500000, "MENU_CARD_IRANCELL_500000" },
	{ MENU_CARD_MCI, "MENU_CARD_MCI" },
	{ MENU_CARD_MCI_10000, "MENU_CARD_MCI_10000" },
	{ MENU_CARD_MCI_20000, "MENU_CARD_MCI_20000" },
	{ MENU_CARD_MCI_50000, "MENU_CARD_MCI_50000" },
	{ MENU_CARD_MCI_100000, "MENU_CARD_MCI_100000" },
	{ MENU_CARD_MCI_200000, "MENU_CARD_MCI_200000" },
	{ MENU_CARD_MCI_500000, "MENU_CARD_MCI_500000" },
	{ MENU_CARD_RIGHTEL, "MENU_CARD_RIGHTEL" },
	{ MENU_CARD_RIGHTEL_20000, "MENU_CARD_RIGHTEL_20000" },
	{ MENU_CARD_RIGHTEL_50000, "MENU_CARD_RIGHTEL_50000" },
	{ MENU_CARD_RIGHTEL_100000, "MENU_CARD_RIGHTEL_100000" },
	{ MENU_CARD_RIGHTEL_200000, "MENU_CARD_RIGHTEL_200000" },
	{ MENU_CARD_RIGHTEL_500000, "MENU_CARD_RIGHTEL_500000" },
	{ MENU_CARD_ITEM_BUY_MULTI_CHARGE, "MENU_CARD_ITEM_BUY_MULTI_CHARGE" },
	{ MENU_CARD_MULTI_IRANCELL, "MENU_CARD_MULTI_IRANCELL" },
	{ MENU_CARD_MULTI_IRANCELL_20000, "MENU_CARD_MULTI_IRANCELL_20000" },
	{ MENU_CARD_MULTI_IRANCELL_50000, "MENU_CARD_MULTI_IRANCELL_50000" },
	{ MENU_CARD_MULTI_IRANCELL_100000, "MENU_CARD_MULTI_IRANCELL_100000" },
	{ MENU_CARD_MULTI_IRANCELL_200000, "MENU_CARD_MULTI_IRANCELL_200000" },
	{ MENU_CARD_MULTI_IRANCELL_500000, "MENU_CARD_MULTI_IRANCELL_500000" },
	{ MENU_CARD_MULTI_MCI, "MENU_CARD_MULTI_MCI" },
	{ MENU_CARD_MULTI_MCI_10000, "MENU_CARD_MULTI_MCI_10000" },
	{ MENU_CARD_MULTI_MCI_20000, "MENU_CARD_MULTI_MCI_20000" },
	{ MENU_CARD_MULTI_MCI_50000, "MENU_CARD_MULTI_MCI_50000" },
	{ MENU_CARD_MULTI_MCI_100000, "MENU_CARD_MULTI_MCI_100000" },
	{ MENU_CARD_MULTI_MCI_200000, "MENU_CARD_MULTI_MCI_200000" },
	{ MENU_CARD_MULTI_MCI_500000, "MENU_CARD_MULTI_MCI_500000" },
	{ MENU_CARD_MULTI_RIGHTEL, "MENU_CARD_MULTI_RIGHTEL" },
	{ MENU_CARD_MULTI_RIGHTEL_20000, "MENU_CARD_MULTI_RIGHTEL_20000" },
	{ MENU_CARD_MULTI_RIGHTEL_50000, "MENU_CARD_MULTI_RIGHTEL_50000" },
	{ MENU_CARD_MULTI_RIGHTEL_100000, "MENU_CARD_MULTI_RIGHTEL_100000" },
	{ MENU_CARD_MULTI_RIGHTEL_200000, "MENU_CARD_MULTI_RIGHTEL_200000" },
	{ MENU_CARD_MULTI_RIGHTEL_500000, "MENU_CARD_MULTI_RIGHTEL_500000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_CHARGE, "MENU_CARD_ITEM_BUY_TOPUP_CHARGE" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_10000, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_10000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_20000, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_20000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_50000, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_50000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_100000, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_100000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_200000, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_200000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_OTHER_AMOUNT, "MENU_CARD_ITEM_BUY_TOPUP_IRANCELL_OTHER_AMOUNT" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI, "MENU_CARD_ITEM_BUY_TOPUP_MCI" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_10000, "MENU_CARD_ITEM_BUY_TOPUP_MCI_10000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_20000, "MENU_CARD_ITEM_BUY_TOPUP_MCI_20000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_50000, "MENU_CARD_ITEM_BUY_TOPUP_MCI_50000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_100000, "MENU_CARD_ITEM_BUY_TOPUP_MCI_100000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_200000, "MENU_CARD_ITEM_BUY_TOPUP_MCI_200000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_MCI_OTHER_AMOUNT, "MENU_CARD_ITEM_BUY_TOPUP_MCI_OTHER_AMOUNT" },
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL" },
	{MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_20000, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_20000"},
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_50000, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_50000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_100000, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_100000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_200000, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_200000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_500000, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_500000" },
	{ MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_OTHER_AMOUNT, "MENU_CARD_ITEM_BUY_TOPUP_RIGHTEL_OTHER_AMOUNT" },
	{ MENU_CARD_ITEM_LOAN_PAYMENT, "MENU_CARD_ITEM_LOAN_PAYMENT" },
	{ MENU_CARD_ITEM_ETC, "MENU_CARD_ITEM_ETC" },
	{ MENU_CARD_ITEM_CHARITY, "MENU_CARD_ITEM_CHARITY" },
	{ MENU_CARD_ITEM_BEHZISTI_CHARITY, "MENU_CARD_ITEM_BEHZISTI_CHARITY" },
	{ MENU_CARD_ITEM_MAHAK_CHARITY, "MENU_CARD_ITEM_MAHAK_CHARITY" },
	{ MENU_CARD_ITEM_KAHRIZAK_CHARITY, "MENU_CARD_ITEM_KAHRIZAK_CHARITY" },
	{ MENU_CARD_ITEM_KOMITEH_EMDAD_CHARITY, "MENU_CARD_ITEM_KOMITEH_EMDAD_CHARITY" },
	{ MENU_CARD_ITEM_BONYADE_MASKANE_ENGHELAB_CHARITY, "MENU_CARD_ITEM_BONYADE_MASKANE_ENGHELAB_CHARITY" },
	{ MENU_CARD_ITEM_ASHRAFOLANBIA_CHARITY, "MENU_CARD_ITEM_ASHRAFOLANBIA_CHARITY" },
	{ MENU_KEY_ROOT, "MENU_KEY_ROOT" },
	{MENU_ITEM_USER, "MENU_ITEM_USER"},
	{ MENU_ITEM_BUY, "MENU_ITEM_BUY" },
	{ MENU_ITEM_BALANCE, "MENU_ITEM_BALANCE" },
	{ MENU_ITEM_BILL_PAY, "MENU_ITEM_BILL_PAY" },
	{ MENU_ITEM_BUY_CHARGE, "MENU_ITEM_BUY_CHARGE" },
	{ MENU_IRANCELL, "MENU_IRANCELL" },
	{ MENU_IRANCELL_10000, "MENU_IRANCELL_10000" },
	{ MENU_IRANCELL_20000, "MENU_IRANCELL_20000" },
	{ MENU_IRANCELL_50000, "MENU_IRANCELL_50000" },
	{ MENU_IRANCELL_100000, "MENU_IRANCELL_100000" },
	{ MENU_IRANCELL_200000, "MENU_IRANCELL_200000" },
	{ MENU_IRANCELL_500000, "MENU_IRANCELL_500000" },
	{ MENU_MCI, "MENU_MCI" },
	{ MENU_MCI_10000, "MENU_MCI_10000" },
	{ MENU_MCI_20000, "MENU_MCI_20000" },
	{ MENU_MCI_50000, "MENU_MCI_50000" },
	{ MENU_MCI_100000, "MENU_MCI_100000" },
	{ MENU_MCI_200000, "MENU_MCI_200000" },
	{ MENU_MCI_500000, "MENU_MCI_500000" },
	{ MENU_RIGHTEL, "MENU_RIGHTEL" },
	{ MENU_RIGHTEL_20000, "MENU_RIGHTEL_20000" },
	{ MENU_RIGHTEL_50000, "MENU_RIGHTEL_50000" },
	{ MENU_RIGHTEL_100000, "MENU_RIGHTEL_100000" },
	{ MENU_RIGHTEL_200000, "MENU_RIGHTEL_200000" },
	{ MENU_RIGHTEL_500000, "MENU_RIGHTEL_500000" },
	{ MENU_ITEM_BUY_MULTI_CHARGE, "MENU_ITEM_BUY_MULTI_CHARGE" },
	{ MENU_MULTI_IRANCELL, "MENU_MULTI_IRANCELL" },
	{ MENU_MULTI_IRANCELL_10000, "MENU_MULTI_IRANCELL_10000" },
	{ MENU_MULTI_IRANCELL_20000, "MENU_MULTI_IRANCELL_20000" },
	{ MENU_MULTI_IRANCELL_50000, "MENU_MULTI_IRANCELL_50000" },
	{ MENU_MULTI_IRANCELL_100000, "MENU_MULTI_IRANCELL_100000" },
	{ MENU_MULTI_IRANCELL_200000, "MENU_MULTI_IRANCELL_200000" },
	{ MENU_MULTI_IRANCELL_500000, "MENU_MULTI_IRANCELL_500000" },
	{ MENU_MULTI_MCI, "MENU_MULTI_MCI" },
	{ MENU_MULTI_MCI_10000, "MENU_MULTI_MCI_10000" },
	{ MENU_MULTI_MCI_20000, "MENU_MULTI_MCI_20000" },
	{ MENU_MULTI_MCI_50000, "MENU_MULTI_MCI_50000" },
	{ MENU_MULTI_MCI_100000, "MENU_MULTI_MCI_100000" },
	{ MENU_MULTI_MCI_200000, "MENU_MULTI_MCI_200000" },
	{ MENU_MULTI_MCI_500000, "MENU_MULTI_MCI_500000" },
	{ MENU_MULTI_RIGHTEL, "MENU_MULTI_RIGHTEL" },
	{ MENU_MULTI_RIGHTEL_20000, "MENU_MULTI_RIGHTEL_20000" },
	{ MENU_MULTI_RIGHTEL_50000, "MENU_MULTI_RIGHTEL_50000" },
	{ MENU_MULTI_RIGHTEL_100000, "MENU_MULTI_RIGHTEL_100000" },
	{ MENU_MULTI_RIGHTEL_200000, "MENU_MULTI_RIGHTEL_200000" },
	{ MENU_MULTI_RIGHTEL_500000, "MENU_MULTI_RIGHTEL_500000" },
	{ MENU_ITEM_LOAN_SERVICE, "MENU_ITEM_LOAN_SERVICE" },
	{ MENU_ITEM_LOAN_PAYMENT, "MENU_ITEM_LOAN_PAYMENT" },
	{ MENU_ITEM_TRACKING_LOAN, "MENU_ITEM_TRACKING_LOAN" },
	{ MENU_PC_POS, "MENU_PC_POS" },
	{ MENU_ITEM_ETC, "MENU_ITEM_ETC" },
	{ MENU_ITEM_BUY_ETC, "MENU_ITEM_BUY_ETC" },
	{ MENU_ITEM_TRACKING_ETC, "MENU_ITEM_TRACKING_ETC" },
	{ MENU_ITEM_CHARITY, "MENU_ITEM_CHARITY" },
	{ MENU_BEHZISTI_CHARITY, "MENU_BEHZISTI_CHARITY" },
	{ MENU_MAHAK_CHARITY, "MENU_MAHAK_CHARITY" },
	{ MENU_KAHRIZAK_CHARITY, "MENU_KAHRIZAK_CHARITY" },
	{ MENU_KOMITEH_EMDAD_CHARITY, "MENU_KOMITEH_EMDAD_CHARITY" },
	{ MENU_BONYADE_MASKANE_ENGHELAB_CHARITY, "MENU_BONYADE_MASKANE_ENGHELAB_CHARITY" },
	{ MENU_ASHRAFOLANBIA_CHARITY, "MENU_ASHRAFOLANBIA_CHARITY" },
	{ MENU_MERCHANT, "MENU_MERCHANT" },
	{ MENU_MERCHANT_CHANGE_PASS, "MENU_MERCHANT_CHANGE_PASS" },
	{ MENU_MERCHANT_TURN_OFF, "MENU_MERCHANT_TURN_OFF" },
	{ MENU_MERCHANT_SETTING, "MENU_MERCHANT_SETTING" },
	{ MENU_MERCHANT_SERVICE_SETTING, "MENU_MERCHANT_SERVICE_SETTING" },
	{ MENU_MERCHANT_KBD_SOUND, "MENU_MERCHANT_KBD_SOUND" },
	{ MENU_MERCHANT_KBD_SOUND_ON, "MENU_MERCHANT_KBD_SOUND_ON" },
	{ MENU_MERCHANT_KBD_SOUND_OFF, "MENU_MERCHANT_KBD_SOUND_OFF" },
	{ MENU_MERCHANT_KBD_LIGHT, "MENU_MERCHANT_KBD_LIGHT" },
	{ MENU_MERCHANT_KBD_LIGHT_ON, "MENU_MERCHANT_KBD_LIGHT_ON" },
	{ MENU_MERCHANT_KBD_LIGHT_OFF, "MENU_MERCHANT_KBD_LIGHT_OFF" },
	{ MENU_MERCHANT_REPORTS, "MENU_MERCHANT_REPORTS" },
	{ MENU_REPORT_CASH, "MENU_REPORT_CASH" },
	{ MENU_REPORT_CASH_BUY, "MENU_REPORT_CASH_BUY" },
	{ MENU_REPORT_CASH_CHARGE, "MENU_REPORT_CASH_CHARGE" },
	{ MENU_REPORT_CASH_ETC, "MENU_REPORT_CASH_ETC" },
	{ MENU_REPORT_CASH_LOANPAY, "MENU_REPORT_CASH_LOANPAY" },
	{ MENU_REPORT_CASH_TOPUP, "MENU_REPORT_CASH_TOPUP" },
	{ MENU_REPORT_CASH_CHARITY, "MENU_REPORT_CASH_CHARITY" },
	{ MENU_REPRINT_TRANSACTION, "MENU_REPRINT_TRANSACTION" },
	{ MENU_REPRINT_TRANSACTION_BUY, "MENU_REPRINT_TRANSACTION_BUY" },
	{ MENU_REPRINT_TRANSACTION_BILL, "MENU_REPRINT_TRANSACTION_BILL" },
	{ MENU_REPRINT_TRANSACTION_BUY_CHARGE, "MENU_REPRINT_TRANSACTION_BUY_CHARGE" },
	{ MENU_REPRINT_TRANSACTION_LOAN_PAY, "MENU_REPRINT_TRANSACTION_LOAN_PAY" },
	{ MENU_REPRINT_TRANSACTION_ETC, "MENU_REPRINT_TRANSACTION_ETC" },
	{ MENU_REPRINT_TRANSACTION_TOPUP, "MENU_REPRINT_TRANSACTION_TOPUP" },
	{ MENU_REPRINT_TRANSACTION_CHARITY, "MENU_REPRINT_TRANSACTION_CHARITY" },
	{ MENU_REPORT_LIST_TRANSACTION, "MENU_REPORT_LIST_TRANSACTION" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS, "MENU_REPORT_LIST_TRANSACTION_SUCCESS" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_BUY, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_BUY" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_BILL, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_BILL" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARGE, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARGE" },
	{ MENU_REPORT_LIST_TRANSACTION_CHARGE_ABSTRACT, "MENU_REPORT_LIST_TRANSACTION_CHARGE_ABSTRACT" },
	{ MENU_REPORT_LIST_TRANSACTION_CHARGE_DETAIL, "MENU_REPORT_LIST_TRANSACTION_CHARGE_DETAIL" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_LOAN_PAY, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_LOAN_PAY" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_ETC, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_ETC" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARITY, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARITY" },
	{ MENU_REPORT_LIST_TRANSACTION_SUCCESS_TOPUP, "MENU_REPORT_LIST_TRANSACTION_SUCCESS_TOPUP" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BUY, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BUY" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARGE, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARGE" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BILL_PAY, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BILL_PAY" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_LOAN_PAY, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_LOAN_PAY" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_ETC, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_ETC" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_TOPUP, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_TOPUP" },
	{ MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARITY, "MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARITY" },
	{ MENU_REPORT_HARDWARE, "MENU_REPORT_HARDWARE" },
	{ MENU_REPORT_INITIALIZE_TRANS, "MENU_REPORT_INITIALIZE_TRANS" },
	{ MENU_MERCHANT_SHIFT, "MENU_MERCHANT_SHIFT" },
	{ MENU_MERCHANT_SHIFTMANAGE, "MENU_MERCHANT_SHIFTMANAGE" },
	{ MENU_SHIFTMANAGE_CREATE_USER, "MENU_SHIFTMANAGE_CREATE_USER" },
	{ MENU_SHIFTMANAGE_DELETE_USER, "MENU_SHIFTMANAGE_DELETE_USER" },
	{ MENU_SHIFTMANAGE_REPORTS_USERS_LIST, "MENU_SHIFTMANAGE_REPORTS_USERS_LIST" },
	{ MENU_SHIFTMANAGE_RESET_PASS, "MENU_SHIFTMANAGE_RESET_PASS" },
	{ MENU_USERS_OPEN, "MENU_USERS_OPEN" },
	{ MENU_USERS_CLOSE, "MENU_USERS_CLOSE" },
	{ MENU_USERS_REPORT, "MENU_USERS_REPORT" },
	{ MENU_SUPERVISOR, "MENU_SUPERVISOR" },
	{ MENU_SETTING, "MENU_SETTING" },
	{ MENU_BANKING_SETTING, "MENU_BANKING_SETTING" },
	{ MENU_SETTING_CONNECTION, "MENU_SETTING_CONNECTION" },
	{ MENUE_PCPOS_CONNECTION, "MENUE_PCPOS_CONNECTION" },
	{ MENU_POS_CONNECTION, "MENU_POS_CONNECTION" },
	{ MENU_CONNECTION1, "MENU_CONNECTION1" },
	{ MENU_CONN1_TYPE, "MENU_CONN1_TYPE" },
	{ MENU_CONN1_PARAM, "MENU_CONN1_PARAM" },
	{ MENU_CONNECTION2, "MENU_CONNECTION2" },
	{ MENU_CONN2_TYPE, "MENU_CONN2_TYPE" },
	{ MENU_CONN2_PARAM, "MENU_CONN2_PARAM" },
	{ MENU_CONNECTION3, "MENU_CONNECTION3" },
	{ MENU_CONN3_TYPE, "MENU_CONN3_TYPE" },
	{ MENU_CONN3_PARAM, "MENU_CONN3_PARAM" },
	{ MENU_CONNECTION4, "MENU_CONNECTION4" },
	{ MENU_CONN4_TYPE, "MENU_CONN4_TYPE" },
	{ MENU_CONN4_PARAM, "MENU_CONN4_PARAM" },
	{ MENU_CONNECTION5, "MENU_CONNECTION5" },
	{ MENU_CONN5_TYPE, "MENU_CONN5_TYPE" },
	{ MENU_CONN5_PARAM, "MENU_CONN5_PARAM" },
	{ MENU_CONNECTION6, "MENU_CONNECTION6" },
	{ MENU_CONN6_TYPE, "MENU_CONN6_TYPE" },
	{ MENU_CONN6_PARAM, "MENU_CONN6_PARAM" },
	{ MENU_SETTING_SERVICES, "MENU_SETTING_SERVICES" },
	{ MENU_CONFIGURATION, "MENU_CONFIGURATION" },
	{ MENU_TMS, "MENU_TMS" },
	{ MENU_TMS_GET_SETTING, "MENU_TMS_GET_SETTING" },
	{ MENU_TMS_UPDATE, "MENU_TMS_UPDATE" },
	{ MENU_TMS_SETTING, "MENU_TMS_SETTING" },
	{ MENU_TMS_TYPE, "MENU_TMS_TYPE" },
	{ MENU_TMS_PARAM, "MENU_TMS_PARAM" },
	{ MENU_SUPERVISOR_CHANGE_PASS, "MENU_SUPERVISOR_CHANGE_PASS" },
	{ MENU_RESET_MERCHANT_PASS, "MENU_RESET_MERCHANT_PASS" },
	{ MENU_PRINT_KEYS, "MENU_PRINT_KEYS" },
	{ MENU_REPORT, "MENU_REPORT" },
	{ MENU_REPORT_TMS, "MENU_REPORT_TMS" },
	{ MENU_TRANSACTION_ERROR_LIST, "MENU_TRANSACTION_ERROR_LIST" },
	{ MENU_SYSTEM_ERROR_LIST, "MENU_SYSTEM_ERROR_LIST" },
	{ MENU_REPORT_SUPERVISOR_ACTIVITIES, "MENU_REPORT_SUPERVISOR_ACTIVITIES" },
	{ MENU_SETTING_REPORT, "MENU_SETTING_REPORT" },
	{ MENU_LOCK_SIM_CARD, "MENU_LOCK_SIM_CARD" },
	{ MENU_MANAGEMENT_ROOT, "MENU_MANAGEMENT_ROOT" },
	{ MENU_LOG, "MENU_LOG" },
	{ MENU_LOG_TYPE, "MENU_LOG_TYPE" },
	{ MENU_LOG_TRACE, "MENU_LOG_TRACE" },
	{ MENU_LOG_DEBUG, "MENU_LOG_DEBUG" },
	{ MENU_LOG_FATAL, "MENU_LOG_FATAL" },
	{ MENU_LOG_RELEASE, "MENU_LOG_RELEASE" },
	{ MENU_LOG_PORT, "MENU_LOG_PORT" },
	{ MENU_PRINT_SUPERVISEOR_PASS, "MENU_PRINT_SUPERVISEOR_PASS" },
	{ MENU_SET_DATE_TIME, "MENU_SET_DATE_TIME" },
	{ MENU_SET_SERIAL_NUM, "MENU_SET_SERIAL_NUM" },
	{ MENU_SET_COMFIRM_SERIAL, "MENU_SET_COMFIRM_SERIAL" },
	{ MENU_SET_RESET_SERIAL, "MENU_SET_RESET_SERIAL" },
	{ MENU_DELETE_FILSE, "MENU_DELETE_FILSE" },
	{ MENU_PIN_UNLOCK, "MENU_PIN_UNLOCK" },
	{ MENU_ITEM_COUNT,"MENU_ITEM_COUNT" },
};

enum menuItemNameEN
str2enum(const char *str)
{
	int j;
	for (j = 0; j < MENU_ITEM_COUNT; ++j)
	if (!strcmp(str, conversion[j].str))
		return conversion[j].val;	
}









/*
* Fill file information.
* @param   serverSpec [input]: management the number of switches
* @param   server [input]: the number of switch
* @return  None.
*/
void fillFileInfo(serverSpecST* serverSpec, uint8 server)
{
	sprintf(serverSpec->files.connFiles[0], "%s%d", CONN_FILE1, server);
	sprintf(serverSpec->files.connFiles[1], "%s%d", CONN_FILE2, server);
	sprintf(serverSpec->files.connFiles[2], "%s%d", CONN_FILE3, server);
	sprintf(serverSpec->files.connFiles[3], "%s%d", CONN_FILE4, server);
	sprintf(serverSpec->files.connFiles[4], "%s%d", CONN_FILE5, server);
	sprintf(serverSpec->files.connFiles[5], "%s%d", CONN_FILE6, server);
	sprintf(serverSpec->files.customerReceiptFile, "%s%d", CUSTOMER_RECEIPT_FILE, server);
	sprintf(serverSpec->files.generalConnInfoFile, "%s%d", GENERAL_CONN_INFO_FILE, server);
	sprintf(serverSpec->files.macKeyFile, "%s%d", MAC_KEY_FILE, server);
	sprintf(serverSpec->files.masterKeyFile, "%s%d", MASTER_KEY_FILE, server);
	sprintf(serverSpec->files.merchantSpecFile, "%s%d", MERCHANT_SPEC_FILE, server);
	sprintf(serverSpec->files.pinKeyFile, "%s%d", PIN_KEY_FILE, server);
	sprintf(serverSpec->files.prefixFile, "%s%d", PREFIX_FILE, server);
	sprintf(serverSpec->files.reversalReceiptFile, "%s%d", REVERSAL_RECEIPT_FILE, server);
	sprintf(serverSpec->files.reversalTransFile, "%s%d", REVERSAL_TRANS_FILE, server);
	sprintf(serverSpec->files.scheduleFile, "%s%d", SCHEDULE_FILE, server);
	sprintf(serverSpec->files.settelmentInfoFile, "%s%d", SETTLEMENT_INFO_FILE, server);
	sprintf(serverSpec->files.settingFile, "%s%d", SETTING_FILE, server);
	sprintf(serverSpec->files.versionFile, "%s%d", VERSIONS_FILE, server);
	sprintf(serverSpec->files.binFile, "%s%d", BIN_FILE, server);
	sprintf(serverSpec->files.configXml, "%d%s", server, CONFIG_XML);
	sprintf(serverSpec->files.logonInfoFile, "%s%d", LOGON_INFO_FILE, server);
	sprintf(serverSpec->files.generalKey, "%s%d", GENERAL_KEY_FILE, server);
	sprintf(serverSpec->files.versionKeyFile, "%s%d", VERSION_KEY_FILE, server);
	sprintf(serverSpec->files.kcvFile, "%s%d", KCV_FILE, server);
	sprintf(serverSpec->files.voucherKeyFile, "%s%d", VOUCHER_KEY_FILE, server);
	sprintf(serverSpec->files.ETCInfo, "%s%d", ETC_INFO_FILE, server);
	sprintf(serverSpec->files.ETCTemp, "%s%d", UNKNOWN_ETC_INFO_FILE, server);
	sprintf(serverSpec->files.loanInfo, "%s%d", LOAN_INFO_FILE, server);
	sprintf(serverSpec->files.loanTemp, "%s%d", UNKNOWN_LOAN_INFO_FILE, server);
	sprintf(serverSpec->files.rollTemp, "%s%d", ROLL_INFO_FILE, server);
	sprintf(serverSpec->files.chargeInfo, "%s%d", CHARGE_INFO_FILE, server);
	sprintf(serverSpec->files.pcPosFiles, "%s%d", PCPOS_INFO_FILE, server);//HNO_TCP
}


/**
* define and menu Items in Screen.
* @param serverSpec
*/
void defineMenuItems(serverSpecST* serverSpec)
{
	serverSpecST*   serverSpec0 = serverSpec;
	serverSpecST*   serverSpec1 = serverSpec0->next;
	serverSpecST*   serverSpec2 = serverSpec1->next;
	uint8*          connNumber = (uint8*)calloc(6, sizeof(uint8));
	uint8*          keyMenu = (uint8*)malloc(sizeof(uint8));
	uint8*          cardMenu = (uint8*)malloc(sizeof(uint8));
	uint8*          barCode = (uint8*)malloc(sizeof(uint8));
	uint8*          manually = (uint8*)malloc(sizeof(uint8));
	uint8*          onlineCharge = (uint8*)malloc(sizeof(uint8));
	uint8*          offlineCharge = (uint8*)malloc(sizeof(uint8));
	messageSpecST*	messageSpec = NULL;
	terminalSpecST  terminalCapability = getTerminalCapability();

	
	int menus = 0;
	int index = 0;
	//******************************************
	int32               fileId = 0;
	mxml_node_t*        tree = NULL;
	mxml_node_t*        node = NULL;
	mxml_index_t*       switchIndex = NULL;
	int16               retValue = 0;
	uint8               buffer[80000] = { 0 };
	uint32              sizeOfFile = 0;
	uint64 num = 0;
	uint8 title[100] = {0};
	uint8(*function[MENU_ITEM_COUNT])(argumentListST* arguments);
	int val1[4] = NULL;
	int varnum = 0;
	uint8               errorMsg[50] = { 0 };
	//******************************************
	
	


	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "defineMenuItems");

	connNumber[0] = 1;
	connNumber[1] = 2;
	connNumber[2] = 3;
	connNumber[3] = 4;
	connNumber[4] = 5;
	connNumber[5] = 6;

	//barcode reader parameters, billPay transaction
	*barCode = TRUE;
	*manually = FALSE;

	*keyMenu = TRUE;
	*cardMenu = FALSE;

	*onlineCharge = TRUE;
	*offlineCharge = FALSE;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Menu Items...");

	//menuIndex,                                                		//parentMenuIndex,               				//language   //timeOut      //align        //color   //visible    //checkPass//title                   //size    ,index,(*function)(argumentListST* arguments),argumentCount.
	/************************************ MENU KEY F1 (Main Menu) ************************************/
//	
//
	function[MENU_KEY_ROOT] = NULL;
	function[MENU_ITEM_USER] = NULL; 
	function[MENU_MERCHANT] = checkMerchantMenuPassword;
	function[MENU_SUPERVISOR] = checkSupervisorMenuPassword;
	function[MENU_ITEM_BUY] = buyTrans;
	function[MENU_ITEM_BALANCE] = balanceTrans;
	function[MENU_ITEM_BILL_PAY] = billPayTrans;
	function[MENU_ITEM_BUY_CHARGE] = NULL;
	function[MENU_ITEM_BUY_MULTI_CHARGE] = NULL;
	function[MENU_ITEM_CHARITY] = NULL;
	function[MENU_ITEM_LOAN_SERVICE] = NULL;
	function[MENU_ITEM_ETC] = NULL;
	function[MENU_BEHZISTI_CHARITY] = behzistiCharity;
	function[MENU_MAHAK_CHARITY] = mahakCharity;
	function[MENU_KAHRIZAK_CHARITY] = kahrizakCharity;
	function[MENU_KOMITEH_EMDAD_CHARITY] = komitehEmdadCharity;
	function[MENU_BONYADE_MASKANE_ENGHELAB_CHARITY] = bonyadeMaskaneEnghelabCharity;
	function[MENU_ASHRAFOLANBIA_CHARITY] = ashrafolAnbiaCharity;
	function[MENU_PC_POS] = PCPOS;
	function[MENU_ITEM_LOAN_PAYMENT] = loanPayTrans;
	function[MENU_ITEM_TRACKING_LOAN] = LoanPayTrackingTrans;
	function[MENU_ITEM_BUY_ETC] = ETCTrans;
	function[MENU_ITEM_TRACKING_ETC] = ETCTrackingTrans;
	function[MENU_IRANCELL] = NULL;
	function[MENU_MCI] = NULL;
	function[MENU_RIGHTEL] = NULL;
	function[MENU_IRANCELL_20000] = buyMultiChargeIrancell20000;
	function[MENU_IRANCELL_50000] = buyMultiChargeIrancell50000;
	function[MENU_IRANCELL_100000] = buyMultiChargeIrancell100000;
	function[MENU_IRANCELL_200000] = buyMultiChargeIrancell200000;
	function[MENU_MCI_10000, MENU_MCI] = buyMultiChargeMCI10000;
	function[MENU_MCI_20000, MENU_MCI] = buyMultiChargeMCI20000;
	function[MENU_MCI_50000, MENU_MCI] = buyMultiChargeMCI50000;
	function[MENU_MCI_100000, MENU_MCI] = buyMultiChargeMCI100000;
	function[MENU_MCI_200000, MENU_MCI] = buyMultiChargeMCI200000;
	function[MENU_RIGHTEL_20000] = buyMultiChargeRightel20000;
	function[MENU_RIGHTEL_50000] = buyMultiChargeRightel50000;
	function[MENU_RIGHTEL_100000] = buyMultiChargeRightel100000;
	function[MENU_RIGHTEL_200000] = buyMultiChargeRightel200000;
	function[MENU_RIGHTEL_500000] = buyMultiChargeRightel500000;
	function[MENU_MULTI_IRANCELL] = NULL;
	function[MENU_MULTI_MCI] = NULL;
	function[MENU_MULTI_RIGHTEL] = NULL;
	function[MENU_MULTI_IRANCELL_20000] = buyMultiChargeIrancell20000;
	function[MENU_MULTI_IRANCELL_50000] = buyMultiChargeIrancell50000;
	function[MENU_MULTI_IRANCELL_100000] = buyMultiChargeIrancell100000;
	function[MENU_MULTI_IRANCELL_200000] = buyMultiChargeIrancell200000;
	function[MENU_MULTI_MCI_10000] = buyMultiChargeMCI10000;
	function[MENU_MULTI_MCI_20000] = buyMultiChargeMCI20000;
	function[MENU_MULTI_MCI_50000] = buyMultiChargeMCI50000;
	function[MENU_MULTI_MCI_100000] = buyMultiChargeMCI100000;
	function[MENU_MULTI_MCI_200000] = buyMultiChargeMCI200000;
	function[MENU_MULTI_RIGHTEL_20000] = buyMultiChargeRightel20000;
	function[MENU_MULTI_RIGHTEL_50000] = buyMultiChargeRightel50000;
	function[MENU_MULTI_RIGHTEL_100000] = buyMultiChargeRightel100000;
	function[MENU_MULTI_RIGHTEL_200000] = buyMultiChargeRightel200000;
	function[MENU_MULTI_RIGHTEL_500000] = buyMultiChargeRightel500000;
	function[MENU_MERCHANT_SHIFT] = checkShiftServiceAccessibility;
	function[MENU_MERCHANT_REPORTS] = NULL;
	function[MENU_MERCHANT_CHANGE_PASS] = changeMerchantMenuPassword;
	function[MENU_MERCHANT_SETTING] = userSetting;
	function[MENU_MERCHANT_SERVICE_SETTING] = setupMerchantServices;
	function[MENU_MERCHANT_TURN_OFF] = turnOffTerminal;
	function[MENU_MERCHANT_SHIFTMANAGE] = checkAdminAccessibility;
	function[MENU_USERS_OPEN] = activateUser;
	function[MENU_USERS_CLOSE] = deactivateUser;
	function[MENU_SHIFTMANAGE_CREATE_USER] = addUser;
	function[MENU_SHIFTMANAGE_DELETE_USER] = deleteUser;
	function[MENU_SHIFTMANAGE_REPORTS_USERS_LIST] = printUsersList;
	function[MENU_SHIFTMANAGE_RESET_PASS] = resetUserMenuPassword;
	function[MENU_REPORT_CASH] = NULL;
	function[MENU_REPRINT_TRANSACTION] = NULL;
	function[MENU_REPORT_LIST_TRANSACTION] = NULL;
	function[MENU_REPORT_HARDWARE] = hardwareReport;
	function[MENU_REPORT_INITIALIZE_TRANS] = transactionInitializeList;
	function[MENU_REPORT_CASH_BUY] = merchantBoxReport;
	function[MENU_REPORT_CASH_CHARGE] = merchantChargeReport;
	function[MENU_REPORT_CASH_CHARITY] = merchantCharityReport;
	function[MENU_REPORT_CASH_LOANPAY] = merchantLOANReport;
	function[MENU_REPORT_CASH_ETC] = merchantETCReport;
	function[MENU_REPRINT_TRANSACTION_BUY] = reprintBuyTransaction;
	function[MENU_REPRINT_TRANSACTION_BILL] = reprintBillTransaction;
	function[MENU_REPRINT_TRANSACTION_BUY_CHARGE] = reprintChargeTransaction;
	function[MENU_REPRINT_TRANSACTION_CHARITY] = reprintCharityTransaction;
	function[MENU_REPRINT_TRANSACTION_LOAN_PAY] = reprintLoanPayTransaction;
	function[MENU_REPRINT_TRANSACTION_ETC] = reprintETCTransaction;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS] = NULL;
	function[MENU_REPORT_LIST_TRANSACTION_UNSUCCESS] = NULL;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_BUY] = transactionBuyList;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_BILL] = transactionBillPayList;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARGE] = NULL;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_CHARITY] = transactionCharityList;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_LOAN_PAY] = transactionLoanPayList;
	function[MENU_REPORT_LIST_TRANSACTION_SUCCESS_ETC] = transactionETCList;
	function[MENU_REPORT_LIST_TRANSACTION_CHARGE_ABSTRACT] = transactionChargeList;
	function[MENU_REPORT_LIST_TRANSACTION_CHARGE_DETAIL] = completeChargeReport;
	function[MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BUY] = unsuccessBuyTransaction;
	function[MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_BILL_PAY] = unsuccessBillPayTransaction;
	function[MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARGE] = unsuccessChargeTransaction;
	function[MENU_REPORT_LIST_TRANSACTION_UNSUCCESS_CHARITY] = unsuccessCharityTransaction;
	function[MENU_SETTING] = NULL;
	function[MENU_CONFIGURATION] = initializeTrans;
	function[MENU_TMS] = NULL;
	function[MENU_REPORT] = NULL;
	function[MENU_RESET_MERCHANT_PASS] = resetMerchantMenuPasswordMenu;
	function[MENU_LOCK_SIM_CARD] = PINLock;
	function[MENU_BANKING_SETTING] = setupGeneralConfig;
	function[MENU_SETTING_CONNECTION] = checkBankConnNumberVisibility;
	function[MENU_SETTING_SERVICES] = setupServices;
	function[MENU_PRINT_KEYS] = NULL;
	function[MENU_SUPERVISOR_CHANGE_PASS] = changeSupervisorMenuPassword;
	function[MENU_POS_CONNECTION] = NULL;
	function[MENUE_PCPOS_CONNECTION] = setupPcPosConnection;
	function[MENU_CONNECTION1] = NULL;
	function[MENU_CONNECTION2] = NULL;
	function[MENU_CONNECTION3] = NULL;
	function[MENU_CONNECTION4] = NULL;
	function[MENU_CONNECTION5] = NULL;
	function[MENU_CONNECTION6] = NULL;
	function[MENU_CONN1_TYPE] = setupConnectionType;
	function[MENU_CONN1_PARAM] = setupConnection;
	function[MENU_CONN2_TYPE] = setupConnectionType;
	function[MENU_CONN2_PARAM] = setupConnection;
	function[MENU_CONN3_TYPE] = setupConnectionType;
	function[MENU_CONN3_PARAM] = setupConnection;
	function[MENU_CONN4_TYPE] = setupConnectionType;
	function[MENU_CONN4_PARAM] = setupConnection;
	function[MENU_CONN5_TYPE] = setupConnectionType;
	function[MENU_CONN5_PARAM] = setupConnection;
	function[MENU_CONN6_TYPE] = setupConnectionType;
	function[MENU_CONN6_PARAM] = setupConnection;
	function[MENU_TMS_GET_SETTING] = TMSConfigManually;
	function[MENU_TMS_UPDATE] = TMSUpdateManually;
	function[MENU_TMS_SETTING] = NULL;
	function[MENU_TMS_TYPE] = setupConnectionTypeTMS;
	function[MENU_TMS_PARAM] = setupConnectionTMS;
	function[MENU_TRANSACTION_ERROR_LIST] = transactionsErrorList;
	function[MENU_SYSTEM_ERROR_LIST] = systemErrorList;
	function[MENU_REPORT_TMS] = TMSReport;
	function[MENU_REPORT_SUPERVISOR_ACTIVITIES] = transactionSupervisorList;
	function[MENU_SETTING_REPORT] = settingReport;
	function[MENU_MANAGEMENT_ROOT] = NULL;
	function[MENU_LOG] = NULL;
	function[MENU_SET_DATE_TIME] = setUserDateAndTime;
	function[MENU_PRINT_SUPERVISEOR_PASS] = printSupervisorPass;
	function[MENU_SET_SERIAL_NUM] = NULL;
	function[MENU_PIN_UNLOCK] = PINUnLock;
	function[MENU_DELETE_FILSE] = deleteFiles;
	function[MENU_LOG_TYPE] = setLogType;
	function[MENU_LOG_PORT] = setLogPort;
	function[MENU_SET_COMFIRM_SERIAL] = setUserSerialNumber;
	function[MENU_SET_RESET_SERIAL] = resetSerialNumber;
	function[MENU_CARD_ROOT] = NULL;
	function[MENU_CARD_ITEM_BUY] = buyTrans;
	function[MENU_CARD_ITEM_BALANCE] = balanceTrans;
	function[MENU_CARD_ITEM_BILL_PAY] = billPayTrans;
	function[MENU_CARD_ITEM_BUY_CHARGE] = NULL;
	function[MENU_CARD_ITEM_BUY_MULTI_CHARGE] = NULL;
	function[MENU_CARD_ITEM_CHARITY] = NULL;
	function[MENU_CARD_ITEM_LOAN_PAYMENT] = loanPayTrans;
	function[MENU_CARD_ITEM_ETC] = ETCTrans;
	function[MENU_CARD_IRANCELL] = NULL;
	function[MENU_CARD_MCI] = NULL;
	function[MENU_CARD_RIGHTEL] = NULL;
	function[MENU_CARD_IRANCELL_20000] = buyMultiChargeIrancell20000;
	function[MENU_CARD_IRANCELL_50000] = buyMultiChargeIrancell50000;
	function[MENU_CARD_IRANCELL_100000] = buyMultiChargeIrancell100000;
	function[MENU_CARD_IRANCELL_200000] = buyMultiChargeIrancell200000;
	function[MENU_CARD_MCI_10000] = buyMultiChargeMCI10000;
	function[MENU_CARD_MCI_20000] = buyMultiChargeMCI20000;
	function[MENU_CARD_MCI_50000] = buyMultiChargeMCI50000;
	function[MENU_CARD_MCI_100000] = buyMultiChargeMCI100000;
	function[MENU_CARD_MCI_200000] = buyMultiChargeMCI200000;
	function[MENU_CARD_RIGHTEL_20000] = buyMultiChargeRightel20000;
	function[MENU_CARD_RIGHTEL_50000] = buyMultiChargeRightel50000;
	function[MENU_CARD_RIGHTEL_100000] = buyMultiChargeRightel100000;
	function[MENU_CARD_RIGHTEL_200000] = buyMultiChargeRightel200000;
	function[MENU_CARD_RIGHTEL_500000] = buyMultiChargeRightel500000;
	function[MENU_CARD_MULTI_IRANCELL] = NULL;
	function[MENU_CARD_MULTI_MCI] = NULL;
	function[MENU_CARD_MULTI_RIGHTEL] = NULL;
	function[MENU_CARD_MULTI_IRANCELL_20000] = buyMultiChargeIrancell20000;
	function[MENU_CARD_MULTI_IRANCELL_50000] = buyMultiChargeIrancell50000;
	function[MENU_CARD_MULTI_IRANCELL_100000] = buyMultiChargeIrancell100000;
	function[MENU_CARD_MULTI_IRANCELL_200000] = buyMultiChargeIrancell200000;
	function[MENU_CARD_MULTI_MCI_10000] = buyMultiChargeMCI10000;
	function[MENU_CARD_MULTI_MCI_20000] = buyMultiChargeMCI20000;
	function[MENU_CARD_MULTI_MCI_50000] = buyMultiChargeMCI50000;
	function[MENU_CARD_MULTI_MCI_100000] = buyMultiChargeMCI100000;
	function[MENU_CARD_MULTI_MCI_200000] = buyMultiChargeMCI200000;
	function[MENU_CARD_MULTI_RIGHTEL_20000] = buyMultiChargeRightel20000;
	function[MENU_CARD_MULTI_RIGHTEL_50000] = buyMultiChargeRightel50000;
	function[MENU_CARD_MULTI_RIGHTEL_100000] = buyMultiChargeRightel100000;
	function[MENU_CARD_MULTI_RIGHTEL_200000] = buyMultiChargeRightel200000;
	function[MENU_CARD_MULTI_RIGHTEL_500000] = buyMultiChargeRightel500000;
	function[MENU_CARD_ITEM_BEHZISTI_CHARITY] = behzistiCharity;
	function[MENU_CARD_ITEM_MAHAK_CHARITY] = mahakCharity;
	function[MENU_CARD_ITEM_KAHRIZAK_CHARITY] = kahrizakCharity;
	function[MENU_CARD_ITEM_KOMITEH_EMDAD_CHARITY] = komitehEmdadCharity;
	function[MENU_CARD_ITEM_BONYADE_MASKANE_ENGHELAB_CHARITY] = bonyadeMaskaneEnghelabCharity;
	function[MENU_CARD_ITEM_ASHRAFOLANBIA_CHARITY] = ashrafolAnbiaCharity;


	if (retValue = fileSize("f:menu.xml", &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		getSystemErrorMessage(errorMsg, retValue, ERR_TYPE_FILE_SYSTEM);
		displayMessageBox(errorMsg, MSG_ERROR);
		//return FALSE;
	}

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fileSize");
	if (retValue = readFileInfo("f:menu.xml", buffer, &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		getSystemErrorMessage(errorMsg, retValue, ERR_TYPE_FILE_SYSTEM);
		displayMessageBox(errorMsg, MSG_ERROR);
		//return FALSE;
	}


	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "strlen(buffer)= %d", strlen(buffer));
	//convertCp1256ToIransystem(buffer);
	tree = mxmlLoadString(NULL, buffer, NULL);

	closeFile(fileId);

	if (tree == NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "NULL tree");
		//return FALSE;
	}

	//showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "bufff=%s", buffer);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "XML OK");
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Parsing xml start");

	switchIndex = mxmlIndexNew(tree, "MENU", NULL);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "switchIndex->num_nodes=%d", switchIndex->num_nodes);



	for (num = 0; num < switchIndex->num_nodes; num++)
	{
		val1[0] = NULL;
		val1[1] = NULL;
		val1[2] = NULL;
		val1[3] = NULL;
		val1[4] = NULL;

		strcpy(title, "");

		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "num=%ld",num);

		node = mxmlIndexEnum(switchIndex);
		
		if (str2define(node->value.element.attrs[2].value)==FARSI)			
			strcpy(title, convert_PersianUtf8_To_Cp1256(node->value.element.attrs[8].value));
		else if (str2define(node->value.element.attrs[2].value) == ENGLISH)
			strcpy(title,(node->value.element.attrs[8].value));

		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "title=%s", title);


		for (varnum = 0; varnum < atoi(node->value.element.attrs[11].value); varnum++)
		{
			val1[varnum] = str2define(node->value.element.attrs[varnum + 12].value);
		}
		

		setMenuItem(str2enum(node->value.element.attrs[0].value), 
			str2enum(node->value.element.attrs[1].value), 
			str2define(node->value.element.attrs[2].value), 
			str2define(node->value.element.attrs[3].value), 
			str2define(node->value.element.attrs[4].value), 
			str2define(node->value.element.attrs[5].value), 
			str2define(node->value.element.attrs[6].value), 
			str2define(node->value.element.attrs[7].value), 
			title,		
			str2define(node->value.element.attrs[9].value),1, 
			(*function[str2enum(node->value.element.attrs[10].value)]), 
			6, &(serverSpec0->files), val1[0], val1[1], val1[2], val1[3], val1[4]);


	}


}

/*
* Add Item in tree menu.
* @param   menuItemList [input]: menu item list
* @param   menuItemNameEN [input]: parent node
* @param   menuItemNameEN [input]: child node
* @return  None.
*/
void addMenuItemList(menuItemST** menuItemList, enum menuItemNameEN parent, enum menuItemNameEN child)
{
	menuItemST**    menuPointer = menuItemList;
	menuItemST*     menuItemValue = *menuItemList;
	if (menuItemValue == NULL)
	{
		*menuPointer = (menuItemST*)malloc(sizeof(menuItemST));
		menuItemValue = *menuPointer;
		menuItemValue->parent = parent;
		menuItemValue->child = child;
		menuItemValue->next = NULL;
	}
	else
	{
		while (menuItemValue->next != NULL)
			menuItemValue = menuItemValue->next;

		menuItemValue->next = (menuItemST*)malloc(sizeof(menuItemST));
		menuItemValue = menuItemValue->next;
		(menuItemValue)->parent = parent;
		(menuItemValue)->child = child;
		(menuItemValue)->next = NULL;
	}
}


/** ------------------------------------------------------------------------ **/
/**                                XML PART                                  **/
/** ------------------------------------------------------------------------ **/
/*
* String to token.
* @param   str [input]: string
* @param   token [input]: token
* @see     showLog().
* @return  None.
*/
void strToToken(uint8* str, uint8* token)
{
	char* tokenPtr = NULL;

	memset(token, 0, 3);
	if (str[0] == 0)
	{
		token[0] = 0;
		return;
	}

	tokenPtr = strstr(str, ".");
	if (tokenPtr == 0)
	{
		strcpy(token, str);
		str[0] = 0;
	}
	else
	{
		strncpy(token, str, strlen(str) - strlen(tokenPtr));
		strcpy(str, tokenPtr + 1);
	}
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "TOKEN: %s", token);
}

/*
* Read integer number.
* @param   value [input]: value of number
* @param   data [input]: data
* @return  None.
*/
void readInteger(uint8* value, mxml_node_t* data)
{
	*value = (uint8)data->value.integer;
}

/*
* Read string.
* @param   str [input]: string
* @param   data [input]: data
* @param   size [input]: size of string
* @return  None.
*/
void readString(uint8* str, mxml_node_t* data, uint8 size)
{
	memset(str, 0, size);
	

	if (strlen(data->value.text.string) <= size)
	{
		strncat(str, data->value.text.string, size - strlen(str));
	}
	
	data = data->next;
	if (data != NULL && strlen(data->value.text.string) > 0)   // space in tag 
	{
		memset(str, 0, size);
	}

}

/*
* Read string with space.
* @param   str [input]: string
* @param   data [input]: data
* @param   size [input]: size of string
* @return  None.
*/
void readStringWithSpace(uint8* str, mxml_node_t* data, uint8 size)
{
	memset(str, 0, size);

	if (strlen(data->value.text.string) <= size)
	{
		strncat(str, data->value.text.string, size - strlen(str));
	}

	do
	{
		data = data->next;
		if (data != NULL && strlen(data->value.text.string) > 0)   // space in tag 
		{
			strncat(str, " ", size - strlen(str));

			strncat(str, data->value.text.string, size - strlen(str));
		}

	} while (data != NULL);
}

/*
* Check string numeric.
* @param   str [input]: string
* @param   data [input]: data
* @param   size [input]: size of string
* @return  retVal(TRUE or FALSE).
*/
uint8 checkStringNumeric(uint8* str, uint8 size, uint8 type)
{
	uint8*	tmp = NULL;
	uint8	retVal = TRUE;

	if (strlen(str) <= 0 || strlen(str) > size)
		retVal = FALSE;

	tmp = str;
	while (*tmp != '\0' && retVal != FALSE)
	{
		if (*tmp >= '0' && *tmp <= '9')
		{
			*tmp++;
		}
		else
		{
			retVal = FALSE;
			break;
		}
	}

	tmp = str;
	switch (type)
	{
	case STRING_NUMBER:
		if (*tmp == '0')
		{
			retVal = FALSE;
		}
		break;
	case STRING_PHONE:
		break;
	case STRING_PREFIX:
		if (strlen(tmp) == 0)
		{
			retVal = TRUE;
		}
		break;
	default:
		break;
	}

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "checkStringNumeric is %d", retVal);
	return retVal;
}

//***************************** Init XML Files *******************************//  

/*
* Initialize general connection information from Xml like:connectioncount,posnii,etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   generalConnInfo [input]: general connection information
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     initGeneralConnectionCountDefaults().
* @see     showLog().
* @see     initGeneralConnectionTPDUNIIDefaults().
* @see     initGeneralConnectionMessageNiiDefaults().
* @return  TRUE or FALSE.
*/
uint8 initGeneralConnectionFromXml(mxml_node_t* serverXmlHead, generalConnInfoST* generalConnInfo)
{
	mxml_node_t* data = NULL;
	uint8        dataIsCorrect = FALSE;
	uint8        buffer[512] = { 0 };
	uint8        model[20] = { 0 };//MRF_NEW18

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "connectioncount", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL)
		{
			readString(buffer, data->child, 1);
			if (checkStringNumeric(buffer, 1, STRING_NUMBER))
			{
				generalConnInfo->connectionCount = (uint8)strToInt(buffer);
				if (generalConnInfo->connectionCount <= 6 || generalConnInfo->connectionCount >= 1)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initGeneralConnectionCountDefaults(generalConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "posnii", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL)
		{
			readString(buffer, data->child, 3);
			if (checkStringNumeric(buffer, 3, STRING_NUMBER))
			{
				generalConnInfo->POSNii = strToInt(buffer);
				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", buffer);
				if (generalConnInfo->POSNii > 0 || generalConnInfo->POSNii <= 999)
				{
					showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "nii set success");
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initGeneralConnectionTPDUNIIDefaults(generalConnInfo);


	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "swinii", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL)
		{
			readString(buffer, data->child, 3);
			if (checkStringNumeric(buffer, 3, STRING_NUMBER))
			{
				generalConnInfo->SWINii = strToInt(buffer);
				if (generalConnInfo->SWINii > 0 || generalConnInfo->SWINii <= 999)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}

	if (!dataIsCorrect)
		initGeneralConnectionMessageNiiDefaults(generalConnInfo);


	//mgh_added970528
	getDeviceModel(&model[0]); //ABS_NEW1
	if (strcmp(model, "VEGA3000") == 0)
	{
		dataIsCorrect = FALSE;
		data = mxmlFindElement(serverXmlHead, serverXmlHead, "secondswinii", NULL, NULL, MXML_DESCEND);
		if (data != NULL)
		{
			if (data->child != NULL)
			{
				readString(buffer, data->child, 3);
				if (checkStringNumeric(buffer, 3, STRING_NUMBER))
				{
					generalConnInfo->SWINii = strToInt(buffer);
					if (generalConnInfo->SWINii > 0 || generalConnInfo->SWINii <= 999)
					{
						dataIsCorrect = TRUE;
					}
				}
			}
		}

		if (!dataIsCorrect)
			initGeneralConnectionMessageNiiDefaults(generalConnInfo);
	}

	return TRUE;
}

/*
* Initialize HDLC connection information from Xml like:phone number,prefix,etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   HDLCConnInfo [input]: HDLC connection information
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     initHDLCConnectionPhoneDefaults().
* @see     initHDLCConnectionPrefixDefaults().
* @see     initHDLCConnectionRetriesDefaults().
* @see     initHDLCConnectionCommunicationTimeoutDefaults().
* @return  TRUE or FALSE.
*/
uint8 initHDLCConnectionFromXml(mxml_node_t* serverXmlHead, HDLCConnInfoST* HDLCConnInfo)
{
	mxml_node_t* data = NULL;
	uint8        dataIsCorrect = FALSE;
	uint8        buffer[512] = { 0 };

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "phone", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);
			if (checkStringNumeric(buffer, 16, STRING_PHONE))
			{
				strcpy(HDLCConnInfo->phone, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initHDLCConnectionPhoneDefaults(HDLCConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "prefix", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 6);
			if (checkStringNumeric(buffer, 6, STRING_PREFIX))
			{
				strcpy(HDLCConnInfo->prefix, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initHDLCConnectionPrefixDefaults(HDLCConnInfo);


	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "dialing", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL)
		{
			readString(buffer, data->child, 5);
			//            strToUpper(buffer);
			if (strcmp(buffer, "tone") == 0)
			{
				HDLCConnInfo->useToneDialing = TRUE;
				dataIsCorrect = TRUE;
			}
			else if (strcmp(buffer, "pulse") == 0)
			{
				dataIsCorrect = TRUE;
				HDLCConnInfo->useToneDialing = FALSE;
			}
		}
	}

	if (!dataIsCorrect)
		initHDLCConnectionUseToneDialingDefaults(HDLCConnInfo);


	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "retries", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 1);

			if (checkStringNumeric(buffer, 1, STRING_NUMBER))
			{
				HDLCConnInfo->retries = strToInt(buffer);
				if (HDLCConnInfo->retries >= 1 || HDLCConnInfo->retries <= 9)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initHDLCConnectionRetriesDefaults(HDLCConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "communicationTimeOut", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 3);

			if (checkStringNumeric(buffer, 3, STRING_NUMBER))
			{
				HDLCConnInfo->communicationTimeout = strToInt(buffer);
				if (HDLCConnInfo->communicationTimeout >= 1 ||
					HDLCConnInfo->communicationTimeout <= 180)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initHDLCConnectionCommunicationTimeoutDefaults(HDLCConnInfo);

	return TRUE;
}

/*
* Initialize LAN connection information from Xml ,for example:tcpPort,ipAddress,etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   LANConnInfo [input]: LAN connection information
* @see     showLog().
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     initLanConnectionTcpPortDefaults().
* @see     strToToken().
* @see     initLanConnectionLocalIpAddressDefaults().
* @see     initLanConnectionGatewayDefaults().
* @see     initLanConnectionNetworkMaskDefaults().
* @return  TRUE or FALSE.
*/
uint8 initLanConnectionFromXml(mxml_node_t* serverXmlHead, LANConnInfoST* LANConnInfo)
{
	mxml_node_t* 	data = NULL;
	uint8        	dataIsCorrect = FALSE;
	uint8        	buffer[512] = { 0 };
	uint8       	token[3] = { 0 };
	uint8        	i = 0;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "init LAN XML");

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "dhcp", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "data != NULL");

		if (data->child != NULL)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "data->child != NULL");

			readInteger(&LANConnInfo->dhcp, data->child);
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "LANConnInfo->dhcp is : %d", LANConnInfo->dhcp);
			dataIsCorrect = TRUE;
		}
	}
	if (!dataIsCorrect)
		initLanConnectionDhcpDefaults(LANConnInfo);


	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "tcpPort", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 5);

			if (checkStringNumeric(buffer, 5, STRING_NUMBER))
			{
				LANConnInfo->tcpPort = strToInt(buffer);
				if (LANConnInfo->tcpPort >= 1 || LANConnInfo->tcpPort <= 99999)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initLanConnectionTcpPortDefaults(LANConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "ipAddress", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "IP address");
			readString(buffer, data->child, 16);
			strToToken(buffer, token);

			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					LANConnInfo->ipAddress[i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			LANConnInfo->ipAddress[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initLanConnectionLocalIpAddressDefaults(LANConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "localIpAddress", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);

			strToToken(buffer, token);
			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					LANConnInfo->localIpAddress[i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			LANConnInfo->localIpAddress[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initLanConnectionLocalIpAddressDefaults(LANConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "gateway", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);

			strToToken(buffer, token);
			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					LANConnInfo->gateway[i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			LANConnInfo->gateway[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initLanConnectionGatewayDefaults(LANConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "networkMask", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);
			strToToken(buffer, token);
			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					LANConnInfo->networkMask[i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			LANConnInfo->networkMask[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initLanConnectionNetworkMaskDefaults(LANConnInfo);

	return TRUE;
}

/*
* Initialize GPRS connection information from XML ,for example:tcpPort, ipAddress,etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   GPRSConnInfo [input]: GPRS connection information
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     initGPRSConnectionTcpPortDefaults().
* @see     strToToken().
* @see     initGPRSConnectionIpAddressDefaults().
* @see     initGPRSConnectionApnDefaults().
* @see     initGPRSConnectionPinDefaults().
* @return  TRUE or FALSE.
*/
uint8 initGPRSConnectionFromXml(mxml_node_t* serverXmlHead, GPRSConnInfoST* GPRSConnInfo)
{
	mxml_node_t* 	data = NULL;
	uint8        	dataIsCorrect = FALSE;
	uint8        	buffer[512] = { 0 };
	uint8       	token[3] = { 0 };
	uint8        	i = 0;

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "tcpPort", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 5);

			if (checkStringNumeric(buffer, 5, STRING_NUMBER))
			{
				GPRSConnInfo->tcpPort = strToInt(buffer);
				if (GPRSConnInfo->tcpPort >= 1 /*|| GPRSConnInfo->tcpPort <= 99999*/)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initGPRSConnectionTcpPortDefaults(GPRSConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "ipAddress", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);

			strToToken(buffer, token);
			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					GPRSConnInfo->ipAddress[(int)i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			GPRSConnInfo->ipAddress[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initGPRSConnectionIpAddressDefaults(GPRSConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "apn", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 3);
			if (strcmp(buffer, "mtn") == 0)
			{
				strcpy(GPRSConnInfo->apn, "MTN");
				dataIsCorrect = TRUE;
			}
			else if (strcmp(buffer, "mci") == 0)
			{
				strcpy(GPRSConnInfo->apn, "MCINET");
				dataIsCorrect = TRUE;
			}
			else if (strcmp(buffer, "rightel") == 0) //MRF_GPRS
			{
				strcpy(GPRSConnInfo->apn, "RighTel");
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initGPRSConnectionApnDefaults(GPRSConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "pin", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 4);
			if (checkStringNumeric(buffer, 4, STRING_NUMBER))
			{
				strncpy(GPRSConnInfo->pin, buffer, 4);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initGPRSConnectionPinDefaults(GPRSConnInfo);

	return TRUE;
}

/*
* Initialize PPP connection information from XML, for example:phone, prefix, etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   PPPConnInfo [input]: PPP connection information
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     initPPPConnectionPhoneDefaults().
* @see     strToToken().
* @see     initPPPConnectionPrefixDefaults().
* @see     initPPPConnectionRetriesDefaults().
* @see     initPPPConnectionCommunicationTimeoutDefaults().
* @see     initPPPConnectionTcpPortDefaults().
* @see     initPPPConnectionIpAddressDefaults().
* @see     initPPPConnectionUserDefaults().
* @see     initPPPConnectionPasswordDefaults().
* @return  TRUE or FALSE.
*/
uint8 initPPPConnectionFromXml(mxml_node_t* serverXmlHead, PPPConnInfoST* PPPConnInfo)
{
	mxml_node_t* 	data = NULL;
	uint8        	dataIsCorrect = FALSE;
	uint8        	buffer[512] = { 0 };
	uint8       	token[3] = { 0 };
	uint8        	i = 0;

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "phone", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);
			if (checkStringNumeric(buffer, 16, STRING_PHONE))
			{
				strcpy(PPPConnInfo->HDLCConnInfo.phone, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionPhoneDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "prefix", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 6);
			if (checkStringNumeric(buffer, 6, STRING_PREFIX))
			{

				strcpy(PPPConnInfo->HDLCConnInfo.prefix, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionPrefixDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "retries", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 1);

			if (checkStringNumeric(buffer, 1, STRING_NUMBER))
			{
				PPPConnInfo->HDLCConnInfo.retries = strToInt(buffer);
				if (PPPConnInfo->HDLCConnInfo.retries >= 0 || PPPConnInfo->HDLCConnInfo.retries <= 9)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionRetriesDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "communicationTimeOut", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 3);

			if (checkStringNumeric(buffer, 3, STRING_NUMBER))
			{
				PPPConnInfo->HDLCConnInfo.communicationTimeout = strToInt(buffer);
				if (PPPConnInfo->HDLCConnInfo.communicationTimeout >= 0 ||
					PPPConnInfo->HDLCConnInfo.communicationTimeout <= 180)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionCommunicationTimeoutDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "tcpPort", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 5);

			if (checkStringNumeric(buffer, 5, STRING_NUMBER))
			{
				PPPConnInfo->tcpPort = strToInt(buffer);
				if (PPPConnInfo->tcpPort >= 1 || PPPConnInfo->tcpPort <= 99999)
				{
					dataIsCorrect = TRUE;
				}
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionTcpPortDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "ipAddress", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);

			strToToken(buffer, token);
			dataIsCorrect = TRUE;
			i = 0;
			while (token[0] != 0 && i < 4)
			{
				if (strToInt(token) >= 0 && strToInt(token) <= 255)
					PPPConnInfo->ipAddress[(int)i] = (uint8)strToInt(token);
				else
					dataIsCorrect = FALSE;

				strToToken(buffer, token);
				i++;
			}
			PPPConnInfo->ipAddress[4] = 0;
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionIpAddressDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "username", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 17);
			if (strlen(buffer) > 0)
			{
				strcpy(PPPConnInfo->PPPConfig.user, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionUserDefaults(PPPConnInfo);

	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "password", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 17);
			if (strlen(buffer) > 0)
			{
				strcpy(PPPConnInfo->PPPConfig.password, buffer);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (!dataIsCorrect)
		initPPPConnectionPasswordDefaults(PPPConnInfo);

	return TRUE;
}

/*
* Initialize connection information from XML, for example: connection type, general, etc.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   serverSpecST [input]: the number of servers
* @see     showLog().
* @see     mxmlFindElement().
* @see     initGeneralConnectionFromXml().
* @see     initGeneralConnectionDefaults().
* @see     mxmlIndexNew().
* @see     mxmlIndexEnum().
* @see     readString().
* @see     initGeneralConnectionTypeDefaults().
* @see     initHDLCConnectionFromXml().
* @see     updateFileInfo().
* @see     addSystemErrorReport().
* @see     initLanConnectionFromXml().
* @see     initPPPConnectionFromXml().
* @see     initGPRSConnectionFromXml().
* @see     initHDLCConnectionDefaults().
* @return  TRUE or FALSE.
*/
uint8 initConnectionFromXml(serverSpecST* serverSpec, mxml_node_t* serverXmlHead)
{
	generalConnInfoST       generalConnInfo = { 0 };
	LANConnInfoST           LANConnInfo = { 0 };
	PPPConnInfoST           PPPConnInfo = { 0 };
	HDLCConnInfoST          HDLCConnInfo = { 0 };
	GPRSConnInfoST          GPRSConnInfo = { 0 };
	mxml_node_t*            data = NULL;
	mxml_index_t*           choiceIndex = NULL;
	mxml_node_t*            choicecNode = NULL;

	uint16                  returnVal = 0;
	uint8                   i = 0;
	uint8                   buffer[512] = { 0 };
	uint8                   dataIsCorrect = FALSE;
	terminalSpecST          terminalCapability = getTerminalCapability(); //MRF_NEW2

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "initConnectionFromXml", "********STARTED***********");
	memset(&generalConnInfo, 0, sizeof(generalConnInfoST));
	memset(&LANConnInfo, 0, sizeof(LANConnInfoST));
	memset(&PPPConnInfo, 0, sizeof(PPPConnInfoST));
	memset(&HDLCConnInfo, 0, sizeof(HDLCConnInfoST));
	memset(&GPRSConnInfo, 0, sizeof(GPRSConnInfoST));

	data = mxmlFindElement(serverXmlHead, serverXmlHead, "connection", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		data = mxmlFindElement(serverXmlHead, serverXmlHead, "general", NULL, NULL, MXML_DESCEND);
		if (data != NULL)
		{
			initGeneralConnectionFromXml(data, &generalConnInfo);
		}
		else
			initGeneralConnectionDefaults(&generalConnInfo);

		choiceIndex = mxmlIndexNew(serverXmlHead, "choice", NULL); // index for choice
		for (i = 0; i < generalConnInfo.connectionCount; i++)
		{
			choicecNode = mxmlIndexEnum(choiceIndex);
			dataIsCorrect = FALSE;
			if (choicecNode != NULL)
			{
				data = mxmlFindElement(choicecNode, choicecNode, "connectiontype", NULL, NULL, MXML_DESCEND);

				if (terminalCapability.GPRSCapability)//MRF_NEW2
				{
					generalConnInfo.connectionsType[(int)i] = CONNECTION_GPRS;
					dataIsCorrect = TRUE;
				}

				else if (data != NULL)
				{
					if (data->child != NULL)
					{
						readString(buffer, data->child, 32);

						if (!strcmp((char*)buffer, "hdlc"))
						{
							generalConnInfo.connectionsType[(int)i] = CONNECTION_HDLC;
						}
						else if (!strcmp((char*)buffer, "lan") || !strcmp((char*)buffer, "ethernet"))
						{
							generalConnInfo.connectionsType[(int)i] = CONNECTION_LAN;
						}
						else if (!strcmp((char*)buffer, "ppp"))
						{
							generalConnInfo.connectionsType[(int)i] = CONNECTION_PPP;
						}
						//      --MRF_GPRS                  else if (!strcmp((char*)buffer, "gprs"))
						//                        {
						//	                            generalConnInfo.connectionsType[(int)i] = CONNECTION_GPRS;
						//                        }
						else
							initGeneralConnectionTypeDefaults(&(generalConnInfo.connectionsType[i])); // get from defaults;
						dataIsCorrect = TRUE;
					}
				}
				//                #endif
			}

			if (!dataIsCorrect)
				initGeneralConnectionTypeDefaults(&(generalConnInfo.connectionsType[i])); // get from defaults;


			//************************   get each connection *****************************************
			dataIsCorrect = FALSE;
			if (choicecNode != NULL)
			{
				dataIsCorrect = TRUE;
				switch (generalConnInfo.connectionsType[i])
				{
				case CONNECTION_HDLC:
					initHDLCConnectionFromXml(choicecNode, &HDLCConnInfo);
					showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "initHDLCConnectionFromXml");
					returnVal = updateFileInfo(serverSpec->files.connFiles[i], &HDLCConnInfo, sizeof(HDLCConnInfoST));
					if (returnVal != SUCCESS)
					{
						addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
						return FALSE;
					}
					break;
				case CONNECTION_LAN:
					initLanConnectionFromXml(choicecNode, &LANConnInfo);
					returnVal = updateFileInfo(serverSpec->files.connFiles[i], &LANConnInfo, sizeof(LANConnInfoST));
					if (returnVal != SUCCESS)
					{
						addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
						return FALSE;
					}
					break;
				case CONNECTION_PPP:
					initPPPConnectionFromXml(choicecNode, &PPPConnInfo);
					returnVal = updateFileInfo(serverSpec->files.connFiles[i], &PPPConnInfo, sizeof(PPPConnInfoST));
					if (returnVal != SUCCESS)
					{
						addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
						return FALSE;
					}
					break;
				case CONNECTION_GPRS:
					initGPRSConnectionFromXml(choicecNode, &GPRSConnInfo);
					returnVal = updateFileInfo(serverSpec->files.connFiles[i], &GPRSConnInfo, sizeof(GPRSConnInfoST));
					if (returnVal != SUCCESS)
					{
						addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
						return FALSE;
					}
					break;
				default:
					initGeneralConnectionTypeDefaults(&(generalConnInfo.connectionsType[i])); // get from defaults;
					initHDLCConnectionDefaults(&HDLCConnInfo); // default type is hdlc
					returnVal = updateFileInfo(serverSpec->files.connFiles[i], &HDLCConnInfo, sizeof(HDLCConnInfoST));
					if (returnVal != SUCCESS)
					{
						addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
						return FALSE;
					}
					break;
				}
				//********************************************************************************************
			}
			if (!dataIsCorrect)
			{
				initGeneralConnectionTypeDefaults(&(generalConnInfo.connectionsType[i])); // get from defaults;
				//HNO_ADD
#ifdef GPRS_IWL
				initGPRSConnectionDefaults(&GPRSConnInfo);  // default type is hdlc
				returnVal = updateFileInfo(serverSpec->files.connFiles[0], &GPRSConnInfo, sizeof(GPRSConnInfoST));
				if (returnVal != SUCCESS)
				{
					addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
					return FALSE;
				}
#else
				initHDLCConnectionDefaults(&HDLCConnInfo); // default type is hdlc
				returnVal = updateFileInfo(serverSpec->files.connFiles[i], &HDLCConnInfo, sizeof(HDLCConnInfoST));
				if (returnVal != SUCCESS)
				{
					addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
					return FALSE;
				}
#endif
			}
		}// for loop
		mxmlIndexDelete(choiceIndex);
	}
	else // connection tag doesn't exist
	{
		// init all connection from defaults
		initGeneralConnectionDefaults(&generalConnInfo);
		initGeneralConnectionTypeDefaults(&(generalConnInfo.connectionsType[1])); // get type hdlc from defaults;
		//HNO_ADD
#ifdef GPRS_IWL
		initGPRSConnectionDefaults(&GPRSConnInfo);  // default type is hdlc
		returnVal = updateFileInfo(serverSpec->files.connFiles[0], &GPRSConnInfo, sizeof(GPRSConnInfoST));
		if (returnVal != SUCCESS)
		{
			addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
			return FALSE;
		}
#else
		initHDLCConnectionDefaults(&HDLCConnInfo);  // default type is hdlc
		returnVal = updateFileInfo(serverSpec->files.connFiles[1], &HDLCConnInfo, sizeof(HDLCConnInfoST));
		if (returnVal != SUCCESS)
		{
			addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
			return FALSE;
		}
#endif
	}

	// save general config to file 
	returnVal = updateFileInfo(serverSpec->files.generalConnInfoFile, &generalConnInfo, sizeof(generalConnInfoST));
	if (returnVal != SUCCESS)
	{
		addSystemErrorReport(returnVal, ERR_TYPE_FILE_SYSTEM);
		return FALSE;
	}
	setGeneralConnInfo(serverSpec->files.id, &generalConnInfo);

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "initConnectionFromXml", "********Finised***********");
	return TRUE;
}

/*
* Initialize merchant information from XML, for example: helpPhone number.
* @param   serverXmlHead [input]: tag of XML configuration
* @param   serverSpecST [input]: the number of servers
* @see     showLog().
* @see     readMerchantSpec().
* @see     mxmlFindElement().
* @see     readString().
* @see     checkStringNumeric().
* @see     writeMerchantSpec().
* @return  None.
*/
uint8 initMerchantSpecFromXml(serverSpecST* serverSpec, mxml_node_t* serverXmlHead)
{
	mxml_node_t* data = NULL;
	uint8        dataIsCorrect = FALSE;
	uint8        buffer[512] = { 0 };
	merchantSpecST merchantSpec;

	memset(&merchantSpec, 0, sizeof(merchantSpecST));

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "initMerchantSpecFromXml", "********STARTED***********");

	readMerchantSpec(&serverSpec->files, &merchantSpec);
	dataIsCorrect = FALSE;
	data = mxmlFindElement(serverXmlHead, serverXmlHead, "helpPhone", NULL, NULL, MXML_DESCEND);
	if (data != NULL)
	{
		if (data->child != NULL && data->child->value.text.string != NULL)
		{
			readString(buffer, data->child, 16);
			if (checkStringNumeric(buffer, 16, STRING_PHONE))
			{
				strncpy(merchantSpec.helpPhone, buffer, 16);
				dataIsCorrect = TRUE;
			}
		}
	}
	if (dataIsCorrect)
		writeMerchantSpec(&serverSpec->files, merchantSpec);

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "initMerchantSpecFromXml", "********FINISHED***********");

}

/*
* XMl  type of node.
* @param   node [input]: Node type like:integer, real or etc
* @see     mxmlElementGetAttr().
* @return  XML type.
*/
mxml_type_t xmlTypeCB(mxml_node_t* node)
{
	const char* type;

	type = mxmlElementGetAttr(node, "type");
	if (type == NULL)
		type = node->value.element.name;

	if (!strcmp(type, "integer"))
		return MXML_INTEGER;
	else if (!strcmp(type, "opaque"))
		return MXML_OPAQUE;
	else if (!strcmp(type, "real"))
		return MXML_REAL;
	else
		return MXML_TEXT;
}

//MRF_NEW2
void setPOSCapability(void)
{
	uint8               check = 0;
	terminalSpecST      terminalCapapility;
	serviceSpecST       POSServices;


	memset(&terminalCapapility, 0, sizeof(terminalSpecST));

	check = checkAppVersion();//+MRF_971225
	if (fileExist(TERMINAL_SPEC_FILE) != SUCCESS)
		initTerminalSpec(TRUE);
	else if (check)//+MRF_971225
		initTerminalSpec(FALSE);

	readPOSCapability();
	terminalCapapility = getTerminalCapability();

	if (fileExist(POS_SERVICE_FILE) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "terminalInitiation", "Checking terminal");
		initPOSServices(&POSServices);
	}

	readPOSService();
	POSServices = getPOSService();
}

/*
* load initialization data from XML file to whole application.
* @param   returnedApplicationSpec [output]: returned application information
* @see     showLog().
* @see     displayMessage().
* @see     readFileInfo().
* @see     mxmlLoadString().
* @see     mxmlIndexNew().
* @see     mxmlIndexEnum().
* @see     fillFileInfo().
* @see     setServiceSchedule().
* @see     mxmlFindElement().
* @see     readString().
* @see     readInteger().
* @see     fileExist().
* @see     initConnectionFromXml().
* @see     initMerchantSpecFromXml().
* @see     mxmlIndexDelete().
* @see     mxmlDelete().
* @see     defineMenuItems().
* @see     checkServersMenusVisibility().
* @return  TRUE or FALSE.
*/
uint8 loadInitializationData(applicationSpecST** returnedApplicationSpec)
{
	int32               fileId = 0;
	mxml_node_t*        node = NULL;
	mxml_node_t*        tree = NULL;
	mxml_node_t*        data = NULL;
	mxml_index_t*       switchIndex = NULL;
	applicationSpecST*	applicationSpec = NULL;
	serverSpecST*       serverSpec = NULL;
	uint8               i = 0;
	int16               retValue = 0;
	uint8               buffer[8192] = { 0 };
	uint32              sizeOfFile = 0;
	uint8               dataIsCorrect = FALSE;
	cardTracksST        tempCardTrack;
	cardSpecST          cardSpec;
	versionKeyST        versionKeySpec;

	memset(&tempCardTrack, 0, sizeof(cardTracksST));
	memset(&cardSpec, 0, sizeof(cardSpecST));
	memset(&versionKeySpec, 0, sizeof(versionKeyST));

	//reader("MENU_CARD_IRANCELL_20000");
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*****load Initialization Data*****");

	setPOSCapability();

	displayMessage("ÏÑ ÍÇá ÈÇÑÐÇÑí ÝÇíá...", DISPLAY_START_LINE + 1, ALL_LINES);
#if !defined (ICT250) && !defined(IWL220)	//HNO_ADD

	if (retValue = fileSize(CONFIG_XML, &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		return FALSE;
	}

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fileSize");
	if (retValue = readFileInfo(CONFIG_XML, buffer, &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		return FALSE;
	}
#else
	readConfigFile(buffer);//HNO_ADD
#endif

	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "strlen(buffer)= %d", strlen(buffer));

	tree = mxmlLoadString(NULL, buffer, xmlTypeCB);

	closeFile(fileId);

	if (tree == NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "NULL tree");
		return FALSE;
	}

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "XML OK");

	//HNO_IDENT
#ifndef INGENICO //IDENT2
	applicationSpec = (applicationSpecST*)malloc(sizeof(applicationSpecST)); // alocate memory
#else
	applicationSpec = (applicationSpecST*)umalloc(sizeof(applicationSpecST));//HNO_change malloc to umalloc for ict
#endif
	*returnedApplicationSpec = applicationSpec;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Parsing xml start");

	switchIndex = mxmlIndexNew(tree, "switch", NULL);
	node = mxmlIndexEnum(switchIndex);

	do
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "memory allocation");

		if (i == 0)
		{
#ifndef INGENICO //IDENT2
			applicationSpec->serverSpec = (serverSpecST*)malloc(sizeof(serverSpecST));
#else
			applicationSpec->serverSpec = (serverSpecST*)umalloc(sizeof(serverSpecST));
#endif
			serverSpec = applicationSpec->serverSpec;
			serverSpec->next = NULL;
		}
		else
		{
#ifndef INGENICO //IDENT2
			serverSpec->next = (serverSpecST*)malloc(sizeof(serverSpecST));
#else
			serverSpec->next = (serverSpecST*)umalloc(sizeof(serverSpecST));
#endif
			serverSpec = serverSpec->next;
			serverSpec->next = NULL;
		}

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "filling schedules and file id");
		serverSpec->files.id = i;
		fillFileInfo(serverSpec, i);

		setServiceSchedule(serverSpec);
		if (i == 0)
			strcpy(serverSpec->files.generalKey, MASKAN_TEST_GENERAL_KEY);
		else
			strcpy(serverSpec->files.generalKey, MASKAN_GENERAL_KEY);

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Display tag");

		dataIsCorrect = FALSE;
		data = mxmlFindElement(node, node, "display", NULL, NULL, MXML_DESCEND);
		if (data != NULL)
		{
			if (data->child != NULL)
			{
				readString(serverSpec->files.displayLogoFile, data->child, 32);
				dataIsCorrect = TRUE;
				showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", " Display logo is %s ", serverSpec->files.displayLogoFile);
			}
		}
		if (!dataIsCorrect)
			strcpy(serverSpec->files.displayLogoFile, "");

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "printer TAG");

		dataIsCorrect = FALSE;
		data = mxmlFindElement(node, node, "printer", NULL, NULL, MXML_DESCEND);
		if (data != NULL)
		{
			if (data->child != NULL)
			{
				readString(serverSpec->files.printerLogoFile, data->child, 32);
				dataIsCorrect = TRUE;
				showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", " printer logo is %s ", serverSpec->files.printerLogoFile);
			}
		}
		if (!dataIsCorrect)
			strcpy(serverSpec->files.printerLogoFile, "");

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "visible tag");

		dataIsCorrect = FALSE;
		data = mxmlFindElement(node, node, "setvisible", NULL, NULL, MXML_DESCEND);
		if (data != NULL)
		{
			if (data->child != NULL)
			{
				readInteger(&(serverSpec->isMenuVisible), data->child);
				dataIsCorrect = TRUE;
			}
		}
		if (!dataIsCorrect)
			serverSpec->isMenuVisible = TRUE;

		if (fileExist(serverSpec->files.generalConnInfoFile) != SUCCESS)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Connection files doesn't Exist");
			initConnectionFromXml(serverSpec, node);
		}
		else
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "Connection files Exist");

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "merchantFile");

		if (fileExist(serverSpec->files.merchantSpecFile) != SUCCESS)
		{
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "Merchant Spec file does'nt Exist");
			initMerchantSpecFromXml(serverSpec, node);
		}
		else
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "MerchantSpec files Exist");

		if (fileExist(serverSpec->files.versionKeyFile) != SUCCESS)
		{
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "version key file Not Exist");
			//if Not exist version key file message can be create
			initVersionKeySpec(&serverSpec->files, &versionKeySpec);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "versionKeyFile2: %s ", serverSpec->files.versionKeyFile);

		}
		else
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "version key  files Exist");
		i++;

	} while ((node = mxmlIndexEnum(switchIndex)) != NULL);

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "loadInitializationData", "Parsing xml finised");
	mxmlIndexDelete(switchIndex);
	mxmlDelete(tree);

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "define menu items");
	defineMenuItems(applicationSpec->serverSpec);
	applicationSpec->menuItems = NULL;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fill menu structs");

	checkServersMenusVisibility(applicationSpec->serverSpec);

	//Calculate and save KCV of master key
	getKCV(MASTER_INDEX, MASKAN_TEST_GENERAL_KEY);

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "end of load Initialization Data");

	return TRUE;
}


void reader2(uint8 title[20])
{

	int32               fileId = 0;
	mxml_node_t*        node = NULL;
	mxml_node_t*        tree = NULL;
	mxml_node_t*        data = NULL;
	mxml_node_t*        data1 = NULL;
	mxml_index_t*       switchIndex = NULL;
	applicationSpecST*	applicationSpec = NULL;
	serverSpecST*       serverSpec = NULL;
	uint8               i = 0;
	int16               retValue = 0;
	uint8               buffer[80000] = { 0 };
	uint32              sizeOfFile = 0;
	uint8               dataIsCorrect = FALSE;
	cardTracksST        tempCardTrack;
	cardSpecST          cardSpec;
	versionKeyST        versionKeySpec;
	uint8 var[100] = { 0 };                 /*!< Display Logo File*/
	const char* var1;
	const char* var2;
	uint8* var3;
	mxml_attr_t  aa;
	FILE *fp = NULL;
	uint8 value[100] = { 0 };
	int num = 0;
	memset(var, 0, 100);


	if (retValue = fileSize("f:mesagges.xml", &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		//return FALSE;
	}

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "fileSize");
	if (retValue = readFileInfo("f:mesagges.xml", buffer, &sizeOfFile) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "ret= %d", retValue);
		//return FALSE;
	}


	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "strlen(buffer)= %d", strlen(buffer));
	//convertCp1256ToIransystem(buffer);
	tree = mxmlLoadString(NULL, buffer, NULL);

	closeFile(fileId);

	if (tree == NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "NULL tree");
		//return FALSE;
	}
	showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "111111111111");
	//showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "bufff=%s", buffer);



	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "XML OK");


	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Parsing xml start");

	//switchIndex = mxmlIndexNew(tree, "iso", NULL);
	//showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "xxxxxxxxxxxxxxxxxxxxxxxxxxx=%d", switchIndex->num_nodes);

	switchIndex = mxmlIndexNew(tree, "iso", NULL);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "xxxxxxxxxxxxxxxxxxxxxxxxxxx=%d", switchIndex->num_nodes);

	//node = mxmlIndexEnum(switchIndex);

//	while (node != NULL)
	for (num = 0 ; num < switchIndex->num_nodes ; num++)
	{
		node = mxmlIndexEnum(switchIndex);
		//showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "xxxxxxxxxxxxxxxxxxxxxxxxxxx=%s", (node->value.element.name));
		
		strcpy(value,"");
		//showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "value=%d ---> mesg=%s", (node->value.element.attrs[0].value), (node->value.element.attrs[1].value));
		strcpy(value, convert_PersianUtf8_To_Cp1256(node->value.element.attrs[1].value));
		//showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "value=%s", value);
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "value=%s ---> msg=%s", (node->value.element.attrs[0].value), value);


	}
	
}

