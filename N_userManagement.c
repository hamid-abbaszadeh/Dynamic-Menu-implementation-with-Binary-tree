

static userNodeST*	usersList          = NULL;
static uint8        loginUser[15 + 1]  = {0};   //MRF_SHIFT : FIX IT
static uint8        activeUser[16]     = {0};   //MRF_SHIFT
static uint8        checkShiftChange   = 0;     //MRF_SHIFT

//ABS_SHIFT
/**
* This function categorize userFileIndex of user structure with  its username string
* @param fileName		 [input] : fileName pointer of uint8
* @return TRUE or FALSE.
*/
uint8 strcatUserID(uint8* fileName)
{
	uint32		fileID			= 0;
	int16		retValue		= 0;
	uint32		len				= sizeof(userInfoST);
	uint8		userIndexStr[4]	= {0};
	userInfoST	currentUser;
	
    memset(&currentUser, 0, sizeof(userInfoST)); //mgh
    
	if (fileExist(ACTIVATED_USER_FILE) != SUCCESS) //basic file
		return TRUE;
	
	retValue = openFile(ACTIVATED_USER_FILE, &fileID);
	if (retValue != SUCCESS)
    {
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "ERR OPEN");
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
        return FALSE;
    }
	
	retValue = fileRead(fileID, &currentUser, &len);
	closeFile(fileID);
	
	if (retValue == SUCCESS)
	{
		sprintf(userIndexStr, "%d", currentUser.userFileIndex);
		strcat(fileName, userIndexStr);
		return TRUE;
	}
	else
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
        return FALSE;
    }
		
}

//ABS_SHIFT
/**
* This function read userlist from USER_MANAGEMENT_FILE file
* @return TRUE or FALSE.
*/
uint8 createUsersList(void)		//ABS:CHANGE
{
	int32 		fileID = 0;
	int16		retValue = -1;
	userNodeST* currentNode = NULL;
	userNodeST* parentNode = NULL;
	uint32		len = sizeof(userNodeST);
	uint32      size = 0;
	activateDateST*		logDateTimeSample = NULL;
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "********************createUsersList************************");

	retValue = fileSize(USER_MANAGEMENT_FILE, &size);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "retValue = %d", retValue);

	//read file to a link list
	retValue = openFile(USER_MANAGEMENT_FILE, &fileID);
	if (retValue != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "ERR OPEN");
		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
		return FALSE;
	}

	//create first node in linkList
	currentNode = parentNode = (userNodeST*)malloc(sizeof(userNodeST));
	//mgh retValue = fileRead(fileID, &(currentNode->data), &len);
	retValue = fileRead(fileID, currentNode, &len); //mgh
	if (retValue == SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "NODE FILE:");
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "current=%s", currentNode->data.userName);
		//HNO_SHIFT_LOG
//		if (currentNode->data.logDateTime != NULL)
//		{
//			logDateTimeSample=currentNode->data.logDateTime;
//
//			while (logDateTimeSample)
//			{
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getHour(logDateTimeSample->loginDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getMinute(logDateTimeSample->loginDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getSecond(logDateTimeSample->loginDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getHour(logDateTimeSample->logOffDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getMinute(logDateTimeSample->logOffDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getSecond(logDateTimeSample->logOffDateTime.time));
//				showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");
//				logDateTimeSample = logDateTimeSample->next;
//
//			}
//		}
        
        //fill active username
		if (currentNode->data.active == TRUE)
			setActiveUser(currentNode->data.userName);//MRF_SHIFT

        
		if (currentNode->next == NULL)
		{

			usersList = currentNode; //header of linkList	
			closeFile(fileID);
			return TRUE;
		}

		
		usersList = currentNode; //header of linkList
		currentNode->next = NULL;
		currentNode->previous = NULL;
	}
	else
	{
		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM); //MRF_SHIFT
		closeFile(fileID);
		return FALSE;
	}

	//create whole linkList
	do{
		currentNode = (userNodeST*)malloc(sizeof(userNodeST));
		//mgh retValue = fileRead(fileID, &(currentNode->data), &len);
		retValue = fileRead(fileID, currentNode, &len); //mgh
		if (retValue != SUCCESS)
		{
			addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM); //MRF_SHIFT
			break;
		}

		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "after-admin-node");
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "userName = %s", currentNode->data.userName);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "userName = %d", currentNode->data.userName);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "index = %d", currentNode->data.userFileIndex);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "retValue = %d", retValue);
		//fill active username
		if (currentNode->data.active == TRUE)
			setActiveUser(currentNode->data.userName);//MRF_SHIFT

		parentNode->next = currentNode;
		currentNode->previous = parentNode;
		parentNode = currentNode;

		if (currentNode->next == NULL)
		{
			break;
		}

	} while (retValue == SUCCESS);

	while (TRUE)//ADD:ABS
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "parentNode:");
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "userName = %s", parentNode->data.userName);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "userName = %d", parentNode->data.userName);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "index = %d", parentNode->data.userFileIndex);
		if (parentNode->previous == NULL)
			break;
		parentNode = parentNode->previous;
	}
	usersList = parentNode;
	closeFile(fileID);
	return TRUE;
}

//ABS_SHIFT
/**
* this function update any change in userlist of shift service
* @return TRUE or FALSE.
*/
uint8 updateUsersListFile(void)
{
	userNodeST* currentNode = NULL;
	int16		retValue = -1;
	uint32 		fileId = 0;
	userNodeST* parentNode = NULL;
	uint32		len = sizeof(userNodeST);
	currentNode = usersList;
	
	//rewrite user files; insert linkList nodes in file
	fileRemove(USER_MANAGEMENT_FILE);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "LINK LIST");

	if (usersList == NULL)
		return TRUE;

	retValue = fileCreate(USER_MANAGEMENT_FILE);
	if (retValue != SUCCESS)
	{
		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM); //MRF_SHIFT
		return retValue;
	}

	retValue = openFile(USER_MANAGEMENT_FILE, &fileId);
	if (retValue != SUCCESS)
	{
		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM); //MRF_SHIFT
		return retValue;
	}

	while (currentNode != NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "user %s", currentNode->data.userName);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%d", currentNode->data.userFileIndex);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", currentNode->data.pass);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%d", currentNode->data.permission);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active %d", currentNode->data.active);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%d", currentNode->next);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%d", currentNode->previous);
		if (currentNode->data.logDateTime != NULL)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getHour(currentNode->data.logDateTime->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getMinute(currentNode->data.logDateTime->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getSecond(currentNode->data.logDateTime->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");

			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getHour(currentNode->data.logDateTime->logOffDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getMinute(currentNode->data.logDateTime->logOffDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getSecond(currentNode->data.logDateTime->logOffDateTime.time));
		}
		//mgh retValue = appendOpenedFile(fileId, &(currentNode->data), sizeof(userInfoST));
		retValue = appendOpenedFile(fileId, currentNode, sizeof(userNodeST));//mgh
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "updateUsersListFile = %d", retValue);
		if (retValue != SUCCESS)
		{
			addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
			closeFile(fileId);
			return retValue;
		}
		currentNode = currentNode->next;
	}
	//usersList = NULL;
	//createUsersList();

	closeFile(fileId);
	return SUCCESS;
}

//ABS_SHIFT
/**
* this function showing all user that defined in shift service
* @param allUser		 [input] : allUser type of int
* @param selectedUser	 [output]: selectedUser pointer of uint8
* @return TRUE or FALSE.
*/
uint8 displayUsersList(uint8* selectedUser, int allUser)//HNO_SHIFT
{
	userNodeST*	currentNode				= NULL;
	uint8   	selectionItems[20][20]  = {0, 0};
    uint8   	selectedItemIndex       = 0;
    uint8		index 					= 0;
    uint8		retValue				= FALSE;
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****displayUsersList****");

	//the users linkList should be readed
	if (usersList == NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "NULL list");
		retValue = createUsersList();
		if (!retValue)
			return FALSE;
	}
	
	//display usernames on screen
	currentNode = usersList;
	while(currentNode)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", currentNode->data.userName);
		strcpy(selectionItems[index++], currentNode->data.userName);
		currentNode = currentNode->next;
	}
	if (allUser)//HNO_SHIFT2
		strcpy(selectionItems[index++], "ò·ÌÂ ò«—»—«‰");//HNO_SHIFT9

	//HNO_IDENT9 change title
	retValue = selectItemPage("·Ì”  ò«—»—«‰", selectionItems, FARSI, index, &selectedItemIndex, DISPLAY_TIMEOUT);
    if (!retValue)
    	return FALSE;
	
    strcpy(selectedUser, selectionItems[selectedItemIndex]); 
	return TRUE;
}

/**
 * This function add new user into link list for shift service. if call this 
 * function first time create Admin user Automatically. 
 * @param None
 * @see getPOSService().
 * @see clearDisplay().
 * @see fileExist().
 * @see searchDataNode().
 * @see getLoginUser().
 * @see displayMessageBox().
 * @see getStringValue().
 * @see createUsersList().
 * @see updateUsersListFile().
 * @see removePadLeft().
 * @see removePadRight().
 * @return TRUE or FALSE.
 */
uint8 addUser(void)
{
	int16 		retValue = -1;
	userNodeST* currentNode = NULL;
	userNodeST* searchNode = NULL;
	userNodeST* newUser = NULL;
	uint8		userName[15 + 1] = { 0 };
	uint8		similarUser = FALSE;
	uint8		properUserIndex = FALSE;
	int8        len = 0;
	int8        count = 0;
	uint8		loginUserName[15 + 1] = { 0 }; //ABS:ADD

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****addUser****");

	clearDisplay();
	newUser = (userNodeST*) malloc(sizeof(userNodeST));
	
	//this is the first user
	if (fileExist(USER_MANAGEMENT_FILE) != SUCCESS)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "User File Not Exist!");

		strcpy(newUser->data.userName, "„œÌ—");//HNO_IDENT9
//		strcpy(newUser->data.userName, "Admin");//HNO_IDENT9
		strcpy(newUser->data.pass, MERCHANT_PASS);

		newUser->data.createDateTime        = getDateTime();
		newUser->data.active                = FALSE;  //ABS
		newUser->data.permission            = TRUE;
		newUser->data.logDateTime           = NULL;   //ABS
		newUser->next                       = NULL;
		newUser->previous                   = NULL;
		newUser->data.userFileIndex         = 0;

		usersList = newUser; //add this user to static linkList
    }
	
	//append this user users List
	else
	{
		searchDataNode(" ", USERNAME, &count);  //MRF: calculate number users
		getLoginUser(loginUserName);

		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "Count: %d", count);

		if (count > 5)  //limit for number user IS 5
		{
			displayMessageBox(" ⁄œ«œ ò«—»—«‰ ‘Ì›  »Ì‘ — «“ Õœ „Ã«“!", MSG_ERROR);//HNO_SHIFT
			return FALSE;
		}

			if(!getStringValue("Ê—Êœ ‘„«—Â ‘Ì› :",10, 1, userName, FALSE,  FALSE, FALSE, "0", 0))//HNO_SHIFT
                return FALSE;

			removePadLeft(userName, ' ');
			removePadRight(userName, ' ');
			len = strlen(userName);

			if (len < 1)
				return FALSE;

		strcpy(newUser->data.userName, userName);
		strcpy(newUser->data.pass, MERCHANT_PASS);//HNO_DEBUG

			newUser->data.createDateTime = getDateTime(); 
			newUser->data.active         = FALSE;
			newUser->data.permission     = FALSE;
			newUser->data.logDateTime    = NULL;
			newUser->next                = NULL;
			newUser->previous            = NULL;

            //the users linkList should be readed
            if (usersList == NULL)
            {
                retValue = createUsersList();
                if (!retValue)
                    return FALSE;
            }

            //find the proper fileIndex
            currentNode = usersList; //currnetNode save the proper linkLits node to add new user after that
            searchNode = usersList; //for search on linklist, avoiding similar userName
            
            while(currentNode->next && searchNode->next)
            {
                //gap in linkList, set the deleted index to the new user
                if (!properUserIndex &&
                        currentNode->data.userFileIndex == currentNode->next->data.userFileIndex - 1)
                    currentNode = currentNode->next;
                else
                    properUserIndex = TRUE;

			if (strcmp(searchNode->data.userName, userName) == 0)
			{
				similarUser = TRUE;
				break;
			}
			searchNode = searchNode->next;
		}
		
		//check the last node in link list && similarUser
		if (similarUser || strcmp(searchNode->data.userName, userName) == 0)
		{
			free(newUser);
				displayMessageBox("‘„«—Â ‘Ì›   ò—«—Ì «” !", MSG_ERROR);
				return FALSE;
			}

			newUser->data.userFileIndex = currentNode->data.userFileIndex + 1;
			newUser->next = currentNode->next;

			if (newUser->next)
				newUser->next->previous = newUser;

			currentNode->next = newUser;
			newUser->previous = currentNode;

		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "usersList.next: %d", usersList->next);
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "usersList.previous: %d", usersList->previous);
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "currentNode.next: %d", currentNode->next);
		showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "currentNode.previous: %d", currentNode->previous);
	}

	updateUsersListFile();
    
    if (strcmp("„œÌ—", newUser->data.userName) == 0)
         displayMessageBox("‘Ì›  ›⁄«· ‘œ.", MSG_INFO);
    else
        displayMessageBox("ò«—»— ‘Ì›  »« „Ê›ﬁÌ  «›“ÊœÂ ‘œ.", MSG_INFO);
    
	return TRUE;
}


//ABS_SHIFT
/**
* this function delete selected user of shift service in menu
* @return TRUE or FALSE.
*/
uint8 deleteUser(void)
{
	userNodeST* currentNode             = 0;
	userNodeST* parentNode              = 0;
	uint8   	selectionItems[20][20]  = {0, 0};
	uint8   	selectedItemIndex       = 0;
	uint8		index                   = 0;
	int16		retValue                = -1;
	uint8		userName[15 + 1]        = {0};
	uint8		key                     = KBD_CANCEL;
	int8        count                   = 0;
	uint8		loginUserName[15 + 1]   = {0};
	uint8       activeUser[16] 			= { 0 };//HNO_SHIFT_NEW

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "****deleteUser****");

	getLoginUser(loginUserName);
	//HNO_DEBUG
//
//	if (fileExist(USER_MANAGEMENT_FILE) != SUCCESS)
//	{
//		displayMessageBox("ò«—»—Ì »—«Ì Õ–› ÊÃÊœ ‰œ«—œ.", MSG_INFO);
//		return FALSE;
//	}

		//the users linkList should be readed
		if (usersList == NULL)
		{
			showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "NULL User list");
			retValue = createUsersList();
			if (!retValue)
				return FALSE;
		}

		//display usernames on screen
		currentNode = usersList;
		while (currentNode)
		{
			showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "%s", currentNode->data.userName);
            
			if(strcmp("„œÌ—", currentNode->data.userName) != 0)
				strcpy(selectionItems[index++], currentNode->data.userName);
            
			currentNode = currentNode->next;
		}

		if (index == 0)
		{
			showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "NO USER");
			displayMessageBox("ò«—»—Ì »—«Ì Õ–› ÊÃÊœ ‰œ«—œ!", MSG_INFO);
			return FALSE;
		}
		//HNO_IDENT9 change title
		retValue = selectItemPage("·Ì”  ò«—»—«‰:", selectionItems, FARSI, index, &selectedItemIndex, DISPLAY_TIMEOUT);
		if (!retValue)
			return FALSE;

		strcpy(userName, selectionItems[selectedItemIndex]);

		currentNode = searchDataNode(userName, USERNAME, &count);//MRF_SHIFT
        
		key = displayMessageBox("¬Ì« «“ Õ–› ò«—»— «ÿ„Ì‰«‰ œ«—Ìœø", MSG_CONFIRMATION);
		if (key != KBD_ENTER && key != KBD_CONFIRM)
			return FALSE;

		//only one node is usersList
		if (currentNode->previous == NULL && currentNode->next == NULL)
			usersList = NULL;

		//first node is deleted
		else if (currentNode->previous == NULL)
		{
			usersList = currentNode->next;
			usersList->previous = NULL;
		}
		else
		{
			parentNode = currentNode->previous;
			parentNode->next = currentNode->next;
			if (currentNode->next)
				currentNode->next->previous = parentNode;
		}

		getActiveUser(activeUser);	//HNO_SHIFT_NEW
		if(strcmp(activeUser, userName) == TRUE)
		{
			setActiveUser("");
			checkShiftChange = 0;
		}

		//delete all user dependant files, such as transaction list files
		deleteDependantFiles(currentNode->data.userFileIndex);
        deletUserFiles(currentNode->data.userName); //MRF_NEW15
		free(currentNode);

	// update users file
	updateUsersListFile();
	displayMessageBox("ò«—»— „Ê—œ ‰Ÿ— Õ–› ê—œÌœ.", MSG_INFO);

	return TRUE;
}

/**
 * This function activate exist user & deactivate Probable active user
 * @param args[input]
 * @see getActiveUser().
 * @see getLoginUser().
 * @see checkPrerequisitDisableShift().
 * @see fileExist().
 * @see deactivateUser().
 * @see displayMessageBox().
 * @see searchDataNode().
 * @see createUsersList().
 * @see updateUsersListFile().
 * @see getShiftChange().
 * @see setShiftChange().
 * @see setActiveUser().
 * @see addLoginDateTime().
 * @return TRUE or FALSE.
 */
uint8 activateUser(argumentListST* args)
{
	filesST*    files = (filesST*)(args->argumentName);
	userNodeST* activeUser = 0;
	int16		retValue = -1;
	uint8		currentUser[16] = { 0 };
	uint8       activeUserName[16] = { 0 };//ABS
	uint8		loginUserName[15 + 1] = { 0 }; //ABS:ADD
	int8		userNodeCount = 0;	//HNO_SHIFT

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***************activateUser*************");//ABS:CHANGE

	getActiveUser(activeUserName);   //ABS
	getLoginUser(loginUserName);

	retValue = checkPrerequisitDisableShift(files, FALSE);//MRF_SHIFT
	if (!retValue)
		return FALSE;

	if (fileExist(USER_MANAGEMENT_FILE) != SUCCESS)
	{
		displayMessageBox("ò«—»—Ì ÃÂ  »«“ ò—œ‰ ‘Ì›  ÊÃÊœ ‰œ«—œ!", MSG_INFO);//HNO_SHIFT
		return FALSE;
	}

	if (strcmp(loginUserName, activeUserName) == 0)//MRF_SHIFT
	{
		displayMessageBox("‘Ì›  »«“ «” !", MSG_WARNING);//HNO_SHIFT
		return FALSE;
	}
    
    if (!strcmp(activeUserName, ""))//+MRF_980224
    {
        retValue = deactivateUser(args); //MRF_SHIFT
        if (!retValue)
        {
            displayMessageBox("‘Ì›  ﬁ»·Ì »” Â ‰‘œ!", MSG_ERROR);
            return FALSE;
        }
    }

	//HNO_SHIFT
	activeUser = searchDataNode(loginUserName, USERNAME, &userNodeCount);
	if(activeUser)
		activeUser->data.active = TRUE;

	strcpy(currentUser, activeUser->data.userName);//HNO_SHIFT

    if (getShiftChange() != NO_DISPLAY) //MRF_SHIFT	HNO_SHIFT
    	setShiftChange(TRUE);
    
	setActiveUser(currentUser);//MRF_SHIFT	//HNO_SHIFT

	// update users file
	if (updateUsersListFile() == SUCCESS)
	{
		displayMessageBox("‘Ì›  »«“ ‘œ!", MSG_INFO);
//		addLoginDateTime(currentUser);//HNO_SHIFT_LOG
	}
	else
    {
		displayMessageBox("Œÿ« œ— »«“ ‰„Êœ‰ ‘Ì› !", MSG_ERROR);
        return FALSE;
    }
    
	return TRUE;
}

//ABS_SHIFT
/**
* This function get username that login in menu from static variable
* @param username [output]:username array
* @return NONE.
*/
void getLoginUser(uint8* username) //ABS:ADD
{
	strcpy(username, loginUser);
}

//ABS_SHIFT
/**
* This function set username that login in menu in static variable
* @param username [input]:username array 
* @return NONE.
*/
void setLoginUser(uint8* username) //ABS:ADD
{
	strncpy(loginUser, username, sizeof(loginUser));
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginUser = %s", loginUser);
}

//ABS_SHIFT
/**
* This function show users in screen to choose and enter its password
* @param password [input]: password geting from input
* @return TRUE or FALSE.
*/
uint8 userLogin(uint8* passWord) //ABS:ADD
{
	userNodeST* currentNode = 0;
	uint8   	selectionItems[20][20] = { 0, 0 };
	uint8   	selectedItemIndex = 0;
	uint8		index = 0;
	int16		retValue = -1;
	uint8		userName[15 + 1] = { 0 };
	uint8		loginUserName[15 + 1] = { 0 }; //ABS:ADD
	uint8		selectUser[16] = { 0 };


	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**UserLogin**");

	if (!displayUsersList(selectUser, FALSE))//ABS
	return FALSE;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "selectUser=%s", selectUser);
	
		currentNode = usersList;
		while (currentNode && strcmp(currentNode->data.userName, selectUser) != 0)
			currentNode = currentNode->next;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "USER");
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", currentNode->data.userName);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%d", currentNode->data.userFileIndex);

	setLoginUser(currentNode->data.userName);
	getLoginUser(loginUserName); //ABS:ADD
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "setloginUser = %s", loginUserName);
	strncpy(passWord, currentNode->data.pass, sizeof(passWord));

	return TRUE;
}


/**
 * Print users list and detect active User for Admin.
 * @return TRUE & FALSE.
 */
uint8 printUsersList(void)
{
	userNodeST*	currentNode             = NULL;
	uint8   	userName[50]            = {0};
	uint8		index                   = 0;
	uint8		retValue                = FALSE;
    uint8		loginUserName[15 + 1]   = {0};
	dateTimeST	createDate;
	

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***printUsersList***");

	getLoginUser(loginUserName);

	memset(&createDate, 0, sizeof(dateTimeST));

		//the users linkList should be readed
		if (usersList == NULL)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "NULL list");
			retValue = createUsersList();
			if (!retValue)
				return FALSE;
		}

		//display usernames on screen
		currentNode = usersList;
		printOneStringFarsi("·Ì”  ò«—»—«‰", PRN_BIG, ALIGN_CENTER);
		printStar();

		while (currentNode)
		{
			index++;
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active %s", currentNode->data.userName);
			strcpy(userName, currentNode->data.userName);
			createDate = currentNode->data.createDateTime;
#ifdef VX520		//ABS:ADD

			if (currentNode->data.active)
			{
				if (!strcmp("„œÌ—", userName))
					printTwoStringFarsi(userName, "‘Ì›  ›⁄«·:", PRN_NORM); 
				else
					printTwoStringNumericFarsi(userName, "‘Ì›  ›⁄«·", PRN_NORM); 
			}
			else
			{
				if (!strcmp("„œÌ—", userName))
					printTwoStringFarsi(userName, "‘Ì› :", PRN_NORM);      
				else
					printTwoStringNumericFarsi(userName, "‘Ì› ", PRN_NORM);      
			}

#else
			
			if (currentNode->data.active)
				printTwoStringFarsi(userName, "‘Ì›  ›⁄«·:", PRN_NORM); //MRF_SHIFT
			else
				printTwoStringFarsi(userName, "‘Ì› :", PRN_NORM);      //MRF_SHIFT
#endif

			printReceiptDateTime(&createDate, 2); //MRF_NEW16: FOR CHANGE TITLE IN SHIFT
			printStar();
			currentNode = currentNode->next;
		}

	printBlankLines(BLANK_LINES_COUNT);

	return TRUE;
}

//MRF_SHIFT
/**
 * Print users log of last login and logout per Shifts.
 * Max count of logs is 20 time.
 * @return None.
 */
void logUsersReport(void)//HNO_SHIFT
{
	userNodeST*         currentNode                 = 0;
    userNodeST*         CurrentNodeBk               = 0;
	uint8               userName[15 + 1]            = {0};
	int8                count                       = 0;
    int8                userCount                   = 1;
	int8                i                           = 0;
    int8                j                           = 0;
    int8                k                           = 0;
	uint8               value[3]                    = {0};
    uint8               loginUserName[15 + 1]       = {0};
    uint8               allUser                     = 0;
    uint8               shift[22]                   = {0};
    activateDateST*		loginNode                   = NULL;
	dateTimeST          loginDateTime;
	dateTimeST          logoffDateTime;
	

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***logUsersReport***");

    memset(&loginDateTime, 0, sizeof(dateTimeST));
    memset(&logoffDateTime, 0, sizeof(dateTimeST));
    
	if (getPOSService().shiftService == FALSE)
	{
		displayMessageBox("”—ÊÌ” ‘Ì›  ›⁄«· ‰Ì” !", MSG_ERROR);
		return;
	}
    
	getLoginUser(loginUserName);
	if (strcmp("„œÌ—", loginUserName) == 0)//HNO_IDENT9
	{
        if (!displayUsersList(userName, TRUE)) //MRF_NEW15
            return ; //ABS
        
        if (strcmp("ò·ÌÂ ò«—»—«‰", userName) == 0)
        {
            searchDataNode(" ", USERNAME, &userCount);
            userCount--;
            allUser = TRUE;
        }
    }
    else
    {
        strcpy(userName, loginUserName);
    }

    showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "userCount: %d", userCount);
    showLog(ALL_POS, __FILE__, __LINE__, FATAL, "", "userName: %s", userName);
    
    if (!getNumeric(" ⁄œ«œ œ›⁄«  Ê—Êœ/Œ—ÊÃ:", 2, 1, value, FALSE, FALSE))
        return;
    
    count = atoi(value);
    if (count == 0)
            return;
    
    while (count > 20) 
    {
        displayMessageBox("”ﬁ› œ—ŒÊ«”  20 Ê—Êœ/Œ—ÊÃ „Ì»«‘œ!", MSG_WARNING);//HNO_SHIFT
        memset(value, 0, sizeof(value));
        if (!getNumeric(" ⁄œ«œ œ›⁄«  Ê—Êœ/Œ—ÊÃ:", 2, 1, value, FALSE, FALSE))
            return;
        count = atoi(value);
        if (count == 0)
            return;
    }
    
    CurrentNodeBk = usersList;
    for (j = 1; j <= userCount; j++)
    {
        currentNode = CurrentNodeBk;
        if (!allUser)
            currentNode = searchDataNode(userName, USERNAME, &k);

        strcpy(userName, currentNode->data.userName);
        
        if (currentNode->data.logDateTime != NULL)
        {
            loginNode  = currentNode->data.logDateTime;
        }
        else
        {
            displayMessageBox("»—«Ì ò«—»— „Ê—œ ‰Ÿ— Ê—Êœ/Œ—ÊÃÌ À»  ‰ê—œÌœÂ", MSG_INFO);//HNO_SHIFT
            return;
        }
        
        printOneStringFarsi("·Ì”  Ê—Êœ/Œ—ÊÃ", PRN_BIG, ALIGN_CENTER);
        printStar();
        strcpy(shift, "‘Ì›  ");
        strcat(shift, userName);
        printOneStringFarsi(shift, PRN_BIG, ALIGN_CENTER);
        
        while (&currentNode->data.logDateTime != NULL)
        {
           if (loginNode->next == NULL)
               break;
           
           loginNode  = loginNode->next;
        }
        
        for (i = 1; i <= count; i++)
        {
            if (loginNode != NULL)
            {
                loginDateTime = loginNode->loginDateTime;
                printOneStringFarsi("Ê—Êœ:", PRN_NORM, ALIGN_RIGHT);
                printReceiptDateTime(&loginDateTime, TRUE);
                if (loginNode->logOffDateTime.time != 0)
                {
                    logoffDateTime = loginNode->logOffDateTime;
                    printOneStringFarsi("Œ—ÊÃ:", PRN_NORM, ALIGN_RIGHT);
                    printReceiptDateTime(&logoffDateTime, TRUE);
                }
                else
                {
                    printTwoString("Œ—ÊÃ:", "----", PRN_NORM, ALIGN_RIGHT);
                }
                
                printStar();
            }
            
            if (loginNode->previous != NULL)
                loginNode = loginNode->previous;
            else 
                break;
        }
        
        printBlankLines(BLANK_LINES_COUNT);
        if (allUser)
            if (CurrentNodeBk->next != NULL)
                CurrentNodeBk = CurrentNodeBk->next;
            else 
                break;
	}
    
	return;
}

//MRF_SHIFT
void setActiveUser(uint8* username)
{
    strcpy(activeUser, username);
}

//MRF_SHIFT
void getActiveUser(uint8* user)//ABS:CHANGE
{
	strcpy(user, activeUser);
}

//HNO_SHIFT
/**
 * This function deactivate previous active user
 * @param args[input]
 * @see checkPrerequisitDisableShift().
 * @see searchDataNode().
 * @see setActiveUser().
 * @see addLogOffDateTime().
 * @see updateUsersListFile().
 * @see displayMessageBox().
 * @return TRUE or FALSE.
 */
uint8 deactivateUser(argumentListST* args)
{
    filesST*    files               = (filesST*) (args->argumentName);
   // uint8*      menu                = (uint8*) (args->next->argumentName);
	uint8*                  	menu = (uint8*)malloc(sizeof(uint8));
	userNodeST* activeUser			= 0;
	uint8		retValue			= FAILURE;
	int8		userNodeCount 		= 0;
	uint8       active[16]          = {0};
	*menu = (uint8)(args->next->argumentName);


    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***************deactivateUser*****************");
    
    getActiveUser(active);//MRF_NEW14
    if (strcmp(active, "") == 0)
         if (menu)//MRF_NEW17
         {
            displayMessageBox("‘Ì›  »” Â «” !", MSG_INFO);
            return TRUE;
         }
         else
         {
             return TRUE;
         }
    
    retValue = checkPrerequisitDisableShift(files, FALSE);//MRF_SHIFT
    if (!retValue)
        return FALSE;
    
    //HNO_SHIFT
	activeUser = searchDataNode(active, USERNAME, &userNodeCount);//ABS:CHANGE
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active5");
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active6");

    activeUser->data.active = FALSE;
	setActiveUser("");//Delete variable for current user

    if (menu)//NEW15
    {
        if (updateUsersListFile() == SUCCESS)
            displayMessageBox("‘Ì›  »” Â ‘œ!", MSG_INFO);
        else
            return FALSE;
    }
    
    return TRUE;
}


//ABS_SHIFT
/**
* This function geting userlist from userlist static variable.
* @return userNodeST.
*/
userNodeST* getUserList(void) //ABS:ADD
{
	return usersList;
}


//ABS_SHIFT
/**
* Changing password in static variable of userlist.
* @param user [input]: username array
* @param newpass [input]: new password 
* @return None.
*/
void setPassUserList(uint8* user, uint8* newpass) //ABS:ADD
{
	userNodeST*	currentNode = NULL; //ABS:ADD
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***setPassUserList***");

	currentNode = usersList;
	while (currentNode)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "old pass = %s", user);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "new pass = %s", newpass);

		if (!strcmp(currentNode->data.userName , user))
			strcpy(currentNode->data.pass, newpass);
        
		currentNode = currentNode->next;
	}


}

//ABS_SHIFT
/**
* This function read users from USER_MANAGEMENT_FILE if exist
* @return TRUE or FALSE.
*/
uint8 loadUserListFile(void) //ABS:ADD  
{
	int16		retValue = -1;
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***loadUserListFile***");

	if (fileExist(USER_MANAGEMENT_FILE) != SUCCESS)
	{
		displayMessageBox("ò«—»—Ì ÊÃÊœ ‰œ«—œ.", MSG_INFO);
		return FALSE;
	}

	//the users linkList should be readed
	if (usersList == NULL)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "NULL list");
		retValue = createUsersList();
		if (!retValue)
			return FALSE;
	}

	return TRUE;
}

//MRF_SHIFT
/**
 * set static variable for change shift.
 * @param check [input]: TRUE or FALSE
 * @return None.
 */
void setShiftChange(uint8 check)
{
    checkShiftChange = check;
}

//MRF_SHIFT
/**
 * Get static variable for change shift.
 * @return checkShiftChange (TRUE or FALSE).
 */
uint8 getShiftChange(void)
{
    return checkShiftChange;
            
}

//MRF_SHIFT
/**
 * This function find a node in link list according to all type of variable 
 * in the structure and return count.
 * @param data  [input]: data search item.
 * @param Type  [input]: type of data search item (USERNAME, PERMISION, ACTIVE, INDEX, CREATE_DT, LOGIN_DT, LOGOFF_DT).
 * @param count [output]: count of node while find search item.
 * @return userNodeST : node is find.
 */
userNodeST* searchDataNode(void* data, uint8 Type, uint8* count)
{
    userNodeST* currentNode		= NULL;
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******searchDataNode*******");
    
    currentNode = usersList;
    switch (Type)
    {
        case USERNAME:
            while (currentNode && strcmp(currentNode->data.userName, data) != 0)
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }
            break;
        case PERMISION:
            while (currentNode && (&currentNode->data.permission == data))
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }
            break;
        case ACTIVE:
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active1");
			while (currentNode)//HNO_SHIFT
            {
                if (currentNode->data.active == TRUE)
                {
                   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active2");
                   break;
                }
                else
                {
                    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active3");
                    *count = *count + 1;		
                    currentNode = currentNode->next;
        		}
            }
             showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "active4");

            break;		
        case INDEX:
            while (currentNode && (&currentNode->data.userFileIndex == data))
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }
            break;
        case CREATE_DT:
            while (currentNode && (&currentNode->data.createDateTime == data))
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }
            break;
        case LOGIN_DT:
           /* while (currentNode && (&currentNode->data.loginDateTime == data))
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }
            break;*/
        case LOGOFF_DT:
           /* while (currentNode && (&currentNode->data.logOffDateTime == data))
            {
                *count = *count + 1;
                currentNode = currentNode->next;
            }*/
            break;
        default:
            break;
    }
	
    return currentNode;
}

//ABS_SHIFT
/**
* This function add login date and time for each user with last 20 login
* @param user[input]: username array for search in userlist to find user node
* @return None.
*/
void addLoginDateTime(uint8* user) //ABS:ADD
{
	activateDateST*		parentNode = 0;
	activateDateST*		currentNode = NULL;
	activateDateST*		firstNode = NULL;

	activateDateST*		Node = NULL;
	activateDateST*		newLogin = NULL;
	int8				userNodeCount = 0;
	int8				loginDateTimeCount = 0;
	userNodeST*			userNode = NULL;//HNO_SHIFT
	userNodeST*			userNodeSample = 0;
	activateDateST*		logDateTimeSample = NULL;
	uint8				ret = FAILURE;


	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***********************add(Login)DateTime*******************************");

	newLogin = (activateDateST*)malloc(sizeof(activateDateST));
	userNode = (userNodeST*)malloc(sizeof(userNodeST));//HNO_SHIFT

	userNode = searchDataNode(user, USERNAME, &userNodeCount);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%s", (userNode->data.userName));
	//if (loginList == NULL)
	if (userNode->data.logDateTime == NULL)
	{
		//add first time
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "NO LOGIN FILE");
		newLogin->loginDateTime = getDateTime();
		newLogin->logOffDateTime.time = 0;
		newLogin->logOffDateTime.date = 0;
		newLogin->next = NULL;
		newLogin->previous = NULL;

		userNode->data.logDateTime = newLogin;

	}
	else
	{
		//add 2 to 20 time
		newLogin->loginDateTime = getDateTime();
		newLogin->logOffDateTime.time = 0;
		newLogin->logOffDateTime.date = 0;
		newLogin->next = NULL;
		newLogin->previous = NULL;


		currentNode = userNode->data.logDateTime;
		while (TRUE)
		{
			if (currentNode->next == NULL)
				break;
			currentNode = currentNode->next;
		}

		newLogin->next = currentNode->next;

		if (newLogin->next)
			newLogin->next->previous = newLogin;

		currentNode->next = newLogin;
		newLogin->previous = currentNode;
	}

	//read usersList 
	userNodeSample = usersList;
	while (userNodeSample)
	{
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "username(login)=%s", (userNodeSample->data.userName));
		logDateTimeSample = userNodeSample->data.logDateTime;
		while (logDateTimeSample)
		{
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getHour(logDateTimeSample->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getMinute(logDateTimeSample->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "loginDateTime-node=%d", getSecond(logDateTimeSample->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");
		
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getHour(logDateTimeSample->logOffDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getMinute(logDateTimeSample->logOffDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime-node=%d", getSecond(logDateTimeSample->logOffDateTime.time));


			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "count=%d", loginDateTimeCount);
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******************************");
			logDateTimeSample = logDateTimeSample->next;
			loginDateTimeCount = loginDateTimeCount + 1;
		}

		if (loginDateTimeCount == 6)			//yani 5 ta darim
		{
			//firstNode = userNode->data.loginDateTime1;
			firstNode = userNodeSample->data.logDateTime;
			//find first node for deleting
			while (TRUE)
			{
				if (firstNode->previous == NULL)
					break;
				firstNode = firstNode->previous;
			}
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "firstNode(delete)=%d", getHour(firstNode->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "firstNode(delete)=%d", getMinute(firstNode->loginDateTime.time));
			showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "firstNode(delete)=%d", getSecond(firstNode->loginDateTime.time));


			//only one node is usersList
			if (firstNode->previous == NULL && firstNode->next == NULL)
				userNodeSample->data.logDateTime = NULL;

			//first node is deleted
			else if (firstNode->previous == NULL)
			{
				userNodeSample->data.logDateTime = firstNode->next;
				userNodeSample->data.logDateTime->previous = NULL;
			}
			else
			{
				parentNode = firstNode->previous;
				parentNode->next = firstNode->next;
				if (firstNode->next)
					firstNode->next->previous = parentNode;
			}

		}
		loginDateTimeCount = 0;
		userNodeSample = userNodeSample->next;
	}
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***********************(Finished)*******************************");
	ret = updateUsersListFile();
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "ret=%d",ret);

}

//ABS_SHIFT
/**
* This function add logoff date and time for each user with last 20 logoff
* @param user[input]: username array for search in userlist to find user node
* @return None.
*/
void addLogOffDateTime(uint8* user)		//ABS:ADD
{
//	activateDateST*		currentNode = NULL;
	userNodeST*			userNodeSample = 0;
	activateDateST*		logDateTimeSample = NULL;
	userNodeST*			userNode = 0;
	int8				userNodeCount = 0;

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***********************add(LogOff)DateTime*******************************");

	logDateTimeSample = (activateDateST*)malloc(sizeof(activateDateST));//HNO_SHIFT
		userNode = searchDataNode(user, USERNAME, &userNodeCount);
		showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "username(logoff)=%s", userNode->data.userName);
		logDateTimeSample = userNode->data.logDateTime;
		while (logDateTimeSample)
		{
			if (logDateTimeSample->next == NULL)
				break;
			logDateTimeSample = logDateTimeSample->next;
		}

	logDateTimeSample->logOffDateTime = getDateTime();

	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime=%d", getHour(logDateTimeSample->logOffDateTime.time));
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime=%d", getMinute(logDateTimeSample->logOffDateTime.time));
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "logOffDateTime=%d", getSecond(logDateTimeSample->logOffDateTime.time));
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***********************END**************************************************");
}


//ABS_SHIFT
/**
* this function reset all static variable of shift service
* @return None.
*/
//MRF_SHIFT
void resetAllVariableShift(void)
{
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "","**resetAllVariableShift**");
    
    usersList           = NULL;
    checkShiftChange    = 0;
    memset(loginUser, 0, sizeof(loginUser));
    memset(activeUser, 0, sizeof(activeUser));
}



//ABS_SHIFT
/**
* this function check status of shift service 
* @return TRUE or FALSE.
*/
//HNO_DEBUG
uint8 checkShiftServiceAccessibility(void)
{
	if (getPOSService().shiftService == FALSE)//ABS:ADD:SHIFT
	{
		displayMessageBox("”—ÊÌ” ‘Ì›  ›⁄«· ‰Ì” !", MSG_ERROR);//HNO_SHIFT
		return FALSE;
	}

	else
		return TRUE;

}

//ABS_SHIFT
/**
* this function control permission of user in shift service
* @return TRUE or FALSE.
*/
//HNO_DEBUG
uint8 checkAdminAccessibility(void)
{
	uint8		loginUserName[15 + 1] = { 0 };

	getLoginUser(loginUserName);
	if (strcmp("„œÌ—", loginUserName) == 0)
		return TRUE;
	else
	{
		displayMessageBox("œ” —”Ì €Ì— „Ã«“!", MSG_ERROR);
		return FALSE;
	}
}
