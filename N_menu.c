


static menuST   menuItemList[MENU_ITEM_COUNT];
static menuST*  selectedItem; 
static uint8    preMenuName[20];
static uint8	maxLineInScreen		= MAX_LINE_IN_SCREEN;
static uint8	maxAssistInScreen	= MAX_LINE_IN_SCREEN; 

#define d_BUFF_SIZE 32	      //Buffer Size

//Declare Global Variable 
uint32 babuff[d_BUFF_SIZE];
int  menuindex = 0;

/**
 * Get preMenu Name.
 * @return preMenuName.
 */
uint8 getPreMenuName(void)
{
    return *preMenuName;
}

/**
 * Clean preMenuName var.
 * @return None.
 */
void clearPreMenuName(void)
{
    memset(preMenuName,0,sizeof(preMenuName));
}


/**
 * Get Max Line In Screen.
 * @return maxLineInScreen.
 */
uint8 getMaxLineInScreen(void)
{
	return maxLineInScreen;
}

/**
 * Execute A Function.
 * @see     clearDisplay().
 * @return  retVal.
 */
uint8 doFunction(void)
{
    if (selectedItem->data.function != NULL)
    {
        uint8 retVal = 0;

        retVal = (selectedItem->data.function(selectedItem->data.arguments));
        clearDisplay();
        return retVal;
    }
    //TODO: this function must return a value for else if.
    // no return value at end
}


/**
 * With Press One Key Running TimeOut.
 * @param  key [input]: One Key pressed
 * @param  timeOut [input]: Timeout per m/s
 * @see    getKey().
 * @return True Or False.
 */
uint8 checkTimeOut(uint8* key, uint8 timeOut) 
{
    uint8 retValue          = FALSE;
    uint8 validKeys[21 + 1] = {KBD_CANCEL, KBD_ENTER, KBD_CLEAR, KBD_UP, KBD_DOWN, KBD_PAGE_DOWN, KBD_PAGE_UP,
                               KBD_0, KBD_1, KBD_2, KBD_3, KBD_4, KBD_5, KBD_6, KBD_7, KBD_8, KBD_9,
                               KBD_ATM_F1, KBD_ATM_F2, KBD_ATM_F3, KBD_ATM_F4};
    uint8 pressedKey	    = 0;
   
    getKey(&pressedKey, &retValue, validKeys, timeOut);

    if (retValue)
    {
        *key = pressedKey;
        return TRUE;
    }
    return FALSE;
}

/**
 * Get parent a node.
 * @param  currentMenu [input]: current menu node
 * @param  rootMenu [input]: root menu node
 * @see    getParentNode().
 * @return parent node.
 */
menuST* getParent(menuST* currentMenu, uint8 rootMenu)
{
    return getParentNode(&menuItemList[rootMenu], currentMenu);	
}

/**
 * Get child a node.
 * @param  currentMenu [input]: is structure
 * @return child node.
 */
menuST* getChild(menuST* currentMenu)
{
    return getChildNode(currentMenu);	
}

/**
 * Get next child node.
 * @param  currentMenu [input]: is structure
 * @return next node.
 */
menuST* getNextChild(menuST* currentMenu)
{
    return getNextNode(currentMenu);
}

/**
 * Get previous node.
 * @param  rootMenu [input]: root menu
 * @param  currentMenu [input]: current menu node is structure
 * @return previous node.
 */
menuST* getPrevious(uint8 rootMenu, menuST* currentMenu)
{
    return getPreviousNode(&menuItemList[(int)rootMenu], currentMenu); //HNO_ADD casting
}

/**
 * Ability of quick Selection menu Items by short key.
 * @param  key [input]: keyboard pressed
 * @param  rootMenu [input]: root menu
 * @see    getNextNode().
 * @see    getPrevious().
 * @return openMenu() or FALSE.
 */
uint8 quickSelection(uint8 key, uint8 rootMenu)
{
    uint8   currentIndex    = (selectedItem->data.index + maxLineInScreen - 1) % maxLineInScreen;
    uint8   pressedIndex    = 0;
    int     diffIndex       = 0;
    menuST* tempSelected    = selectedItem;

    if (maxLineInScreen == MAX_LINE_IN_SCREEN + 1) 
    {
        if (key == KBD_ATM_F1)
            pressedIndex = 0;
        else if (key == KBD_ATM_F2)
            pressedIndex = 1;
        else if (key == KBD_ATM_F3)
            pressedIndex = 2;
        else if (key == KBD_ATM_F4)
            pressedIndex = 3;
    }
    else
    {
        if (key == KBD_ATM_F2)
            pressedIndex = 0;
        else if (key == KBD_ATM_F3)
            pressedIndex = 1;
        else if (key == KBD_ATM_F4)
            pressedIndex = 2;
    }

    if (pressedIndex == currentIndex)
    {
        return openMenu(rootMenu);
    }
    else
    {
        diffIndex = pressedIndex - currentIndex;

        //go forward
        if (diffIndex > 0)
            while (diffIndex > 0 && selectedItem)
            {
                selectedItem = getNextNode(selectedItem);
                diffIndex--;
            }

        //go backward
        else if (diffIndex < 0)
            while (diffIndex < 0 && selectedItem)
            {
                selectedItem = getPrevious(rootMenu, selectedItem);
                diffIndex++;
            }

        if (selectedItem)
        {
            return openMenu(rootMenu);
        }
        //key pressed do not effect on menus
        else 
        {
            selectedItem = tempSelected;
            return FALSE;
        }
    }
}

/**
 * Creation menu with ability to shows .
 * @param  selectedMenu [input]: One structure of type Structure of Node
 * @param  rootMenu [input]: Root menu node
 * @see    clearMenu().
 * @see    isMenuCleared().
 * @see    displayHeaderMenu().
 * @see    displayforeColor().  
 * @see    displayBackColor(). 
 * @see    displayStringFarsi().  
 * @see    oneLineClear().  
 * @see    displayInvertStringFarsi().
 * @see    displayPic().
 * @see    getPrevious().
 * @see    getChildNode().
 * @see    setMenuCleared().
 * @see    cleanfinger().
 * @see    displayButtonMenu().
 * @see    displayfinger().
 * @see    getParent().
 * @see    getNextChild().  
 * @return None.
 */
void displayMenu(menuST* selectedMenu, uint8 rootMenu)
{
	uint8               displayStartLine	= DISPLAY_START_LINE;	
    uint8               line            	= displayStartLine; //+ EMPTY_LINE;
    uint8               menuName[50] 		= {0};
    menuST*             currentMenu     	= NULL;
    menuST*             parent          	= getPrevious(rootMenu, selectedMenu);
    uint8               predecessorNum 		= 0;
    menuST*             titleMenu           = getParent(selectedMenu, rootMenu);
    uint8               assist              = 2;
    terminalSpecST      terminalSpec        = getTerminalCapability();
    menuST* 			invertedMenu 		= NULL; //HNO
    uint8				invertedLine 		= 0;	//HNO
    
    initY(70); // initialize y as coordinate shapes
    cleanMenuInTrace(selectedMenu); // This function clean menu when trace page up or trace page down.
   
	if (rootMenu == MENU_KEY_ROOT)
	{
		if (getPreDialCheck() == TRUE)//MRF_NEW5
		{
			disconnectModem(); //MRF_NEW6
		}
	}

    //parent Menu is base title  
    if (rootMenu == MENU_CARD_ROOT && titleMenu == &menuItemList[(int)rootMenu])  //do not show title for card menu else V5S
    {
    	//HNO_ADD
#if  defined(ICT250) || defined(IWL220)
    	maxLineInScreen = MAX_LINE_IN_SCREEN + 1;
#else
        line++;
        assist++;
       	maxLineInScreen = MAX_LINE_IN_SCREEN + EMPTY_LINE;
#endif
        if (terminalSpec.graphicCapability)
            maxAssistInScreen = MAX_ASSIST_IN_SCREEN;

        //title menu 
#ifndef INGENICO //HNO_ADD
        if (isMenuCleared())
        {
            if (!terminalSpec.graphicCapability)//MRF_IDENT
            {
                displayInvertStringFarsi("áíÓÊ ÊÑÇ˜äÔ åÇ", DISPLAY_START_LINE, BIG_STRING, ALIGN_CENTER);                  
                //border title  
                displayPic(borderPic); //display white line (two Pixels)
            }
            else
            {
                settingMenu("áíÓÊ ÊÑÇ˜äÔ åÇ"); //Set color and title for menu
            }
        }
#endif
    }
    else
    {
    	//first line is reserved for title
    	displayStartLine++;
    	line++;
        assist++;
       	maxLineInScreen = MAX_LINE_IN_SCREEN + EMPTY_LINE;
       
        if (terminalSpec.graphicCapability)
            maxAssistInScreen = MAX_ASSIST_IN_SCREEN;
        
        //compare Titles.
        strcpy(menuName, titleMenu->data.title);
        if ((strcmp(preMenuName, menuName) != 0) || isMenuCleared())
        {
            //title menu 
            if (!terminalSpec.graphicCapability)//MRF_IDEN
            {
                displayInvertStringFarsi(menuName, DISPLAY_START_LINE, BIG_STRING, ALIGN_CENTER);                  
                //border title  
                displayPic(borderPic); //display white line (two Pixels)
            }
            else
            	settingMenu(menuName); //Set color and title for menu

#if !defined(ICT250) && !defined(IWL220)//HNO_ADD
            strcpy(preMenuName, menuName);
#endif
        }
    }
    currentMenu = selectedMenu;	
    
    if (!terminalSpec.graphicCapability)
    {
        predecessorNum = (currentMenu->data.index - 1) % maxLineInScreen; 
        maxAssistInScreen = maxLineInScreen + 1 - EMPTY_LINE; //mgh_940713(change): and add 1 to maxAssistInScreen
    }
    else
        predecessorNum = (currentMenu->data.index - 1) % maxAssistInScreen;  

    while (predecessorNum > 0)
    {
        currentMenu = parent;
        parent = getPrevious(rootMenu, currentMenu);
        predecessorNum--;
    }

    if (currentMenu == &menuItemList[rootMenu])
        currentMenu = getChildNode(currentMenu);
        
	if (!terminalSpec.graphicCapability)    //here must call clearMenu that clean 3lines.
        cleanMenuLines();
   
    setMenuCleared(FALSE);
    
    //mgh_940713(change): replace maxLineInScreen with maxAssistInScreen
    while (currentMenu != NULL && line < ( maxAssistInScreen + EMPTY_LINE + EMPTY_LINE)+ displayStartLine)
    {
        strcpy(menuName, currentMenu->data.title);
        cleanfinger(getY());
        if (currentMenu == selectedMenu)
        {
            if (terminalSpec.graphicCapability)
                displaySelectedItemMenu(menuName,assist, currentMenu->data.size, currentMenu->data.align, BOLD_BLUE, WHITE );
            else
			{
				#if defined(IWL220) || defined(ICT250)//HNO_ADD
					invertedMenu     	= currentMenu;
					invertedLine		= line;
				#else
                	displayInvertStringFarsi(menuName, line, currentMenu->data.size, currentMenu->data.align);
				#endif
			}
        }		
        else 
        {
            if (terminalSpec.graphicCapability) 
                displayItemMenu(menuName,assist, currentMenu->data.size, currentMenu->data.align,GREEN_LIGHT,WHITE ); 
            else
                displayStringFarsi(menuName, line, currentMenu->data.size, currentMenu->data.align);
        }
        
        currentMenu = getNextChild(currentMenu);
        line++;
        assist = assist + 2; 
        yPlus(64);
    }
    setColor(WHITE,BLUE);

#if defined(IWL220) || defined(ICT250)//HNO_ADD
    displayInvertStringFarsi(invertedMenu->data.title, invertedLine, invertedMenu->data.size, invertedMenu->data.align);
#endif
}

/**
 * Ability scroll down on menu.
 * @param  loop [input]: TRUE or FALSE
 * @param  rootMenu [input]: Root menu node
 * @see    getNextNode(). 
 * @see    getNextChild().
 * @see    getFirstNode().
 * @return None. 
 */
void traceDown(uint8 loop, uint8 rootMenu)
{
    if (getNextNode(selectedItem) != NULL)
    {
        selectedItem = getNextChild(selectedItem);
    }
    else if (loop)
    {
        selectedItem = getFirstNode(&menuItemList[(int)rootMenu], selectedItem);
    }
}

/**
 * Ability scroll up on menu.
 * @param  loop [input]: TRUE or FALSE
 * @param  rootMenu [input]: Root menu node
 * @see    getPrevious(). 
 * @see    getNextChild().
 * @see    getLastNode().
 * @return None. 
 */
void traceUp(uint8 loop, uint8 rootMenu)
{
    menuST* backMenu = getPrevious(rootMenu, selectedItem);

    //only loop in current level menu
    if (getNextChild(backMenu) == selectedItem)
    {
        selectedItem = backMenu;
    }
    else if (loop)
    {
        selectedItem = getLastNode(selectedItem);
    }
}

/**
 * Open menu & do function.
 * @param  rootMenu [input]: Root menu node
 * @see    clearDisplay().
 * @see    getChildNode().
 * @see    doFunction().
 * @see    getSuccessorNode().
 * @see    getNextChild().
 * @return TRUE or FALSE.
 */
uint8 openMenu(uint8 rootMenu)
{
    menuST* tempMenu = selectedItem; 
    
    menuindex = 0; //MRF for trace menu
    clearDisplay(); 
    
    //if menu has no submenu, it is a transaction
    if (getChildNode(selectedItem) == NULL)
    {
        doFunction();
        if (rootMenu == MENU_KEY_ROOT)
        	return FALSE; //remain in menu
        else
            return TRUE; //go to main page
    } 
    //else go to submenu
    else
    {
        if (selectedItem->data.function != NULL)
            if (!doFunction())
            {
                return FALSE;
            } 
        
        selectedItem = getSuccessorNode(&menuItemList[(int)rootMenu], selectedItem);//HNO_CHANGE casting
        
        while (selectedItem && selectedItem->data.visible == FALSE)
        {
            selectedItem = getNextChild(selectedItem);
        }
        if (selectedItem == NULL)
            selectedItem = tempMenu;
        return FALSE;
    }
}

/**
 * Close Menu.
 * @param  rootMenu [input]: Root menu node
 * @see    getPrevious().     
 * @see    clearDisplay().
 * @see    getNextChild().
 * @see    clearPreMenuName().
 * @return TRUE or FALSE.
 */
uint8 closeMenu(uint8 rootMenu)
{   
    menuST* parent = getPrevious(rootMenu, selectedItem);
    
    clearDisplay();

    //go backward untill reach top level
    while (getNextChild(parent) == selectedItem)
    {
        selectedItem = parent;
        parent = getPrevious(rootMenu, selectedItem);
    }
    
    selectedItem = parent;
    clearPreMenuName(); 
    resetPrePrintFlags();//MGH 941106
    
    if (selectedItem->data.index == 5)//#MRF_971003: CHANGE 4 TO 5 BECAUSE MULTI CHARG INDEX IS 5 NOW
    {
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "** resetBuyChargeInfo **");
        resetBuyChargeInfo();
    }
    
    if (selectedItem == &menuItemList[(int)rootMenu])//HNO_CHANGE casting
    {
        return TRUE; //go to main page
    }
    return FALSE; //remain in menu
}

/**
 * Scroll menu items with short key.
 * @param  key [input]: Key pressed keyboard
 * @param  enterMenu [input]: TRUE or FALSE
 * @param  rootMenu [input]: Root menu node
 * @see    traceDown().
 * @see    traceUp().
 * @see    open Menu().
 * @return Open menu or FALSE.
 */
uint8 traceShortKeys(uint8 key, uint8 enterMenu, uint8 rootMenu)
{
    uint8       i               = 0;
    uint8       downDistance 	= key - (selectedItem->data.index);
    uint8       upDistance      = (selectedItem->data.index) - key;
    menuST*     oldSelectedItem = selectedItem;

    if (key > (selectedItem->data.index))
		for (i; i< downDistance; i++)   // i = 0
            traceDown(FALSE, rootMenu);
    else
		for (i; i< upDistance; i++)    // i = 0
            traceUp(FALSE, rootMenu);

    //short key is valid
    if ((selectedItem->data.index) == key)
    {
        if (enterMenu)
            return openMenu(rootMenu);
    }
    else
    {
        selectedItem = oldSelectedItem;
        return FALSE;
    }
//    return TRUE; //HNO_ADD we have it in ict
}

/**
 * Trace Page Down. 
 * @param  rootMenu [input]: Root menu node
 * @see    clearDisplay().
 * @see    traceShortKeys().
 * @return traceShortKeys() or FALSE.
 */
uint8 tracePageDown(uint8 rootMenu)
{
    uint8 pageNumber    = 0;
    uint8 maxLine       = 0;
    
    menuindex           = 0; // MRF for trace menu
    
    
    #ifdef CASTLES_V5S
        maxLine = maxAssistInScreen;
    #else
        maxLine = maxLineInScreen;
    #endif
    
    clearMenu();
    
    pageNumber = (selectedItem->data.index - 1) / maxLine;
    pageNumber = (pageNumber + 1)* maxLine;
    pageNumber++;
    
    //go to next page
    if (pageNumber < 10)
        return traceShortKeys(pageNumber, FALSE, rootMenu);
    else 
        return FALSE;
}

/**
 * Trace Page Up.
 * @param  rootMenu [input]: Root menu node
 * @see    clearDisplay().
 * @see    traceShortKeys(). 
 * @return traceShortKeys() or FALSE.
 */
uint8 tracePageUp(uint8 rootMenu)
{
    uint8 pageNumber    = 0;
    uint8 maxLine       = 0;
    
    menuindex           = 0; //MRF for trace menu
    
    
    #ifdef CASTLES_V5S
        maxLine = maxAssistInScreen;
    #else
        maxLine = maxLineInScreen;
    #endif
    
    clearMenu();
    
    pageNumber = (selectedItem->data.index - 1) / maxLine ;
    pageNumber = (pageNumber - 1) * maxLine;
    pageNumber++;
    
    //go to next page
    if (pageNumber < 10)
        return traceShortKeys((pageNumber), FALSE, rootMenu);
    else 
        return FALSE;
}

/**
 * Set Menu Visible.
 * @param   parentMenu [input]: Is structre for Parent node
 * @param   currentMenu [input]: Is structure for current node
 * @see     insertNode().
 * @see     increaseIndex().
 * @return  None.
 */
void setMenuVisible(menuST* parentMenu, menuST* currentMenu)
{
	//menu is already visible
    if (currentMenu->data.visible == TRUE)
    {
        return;
    }

    currentMenu->data.visible = TRUE;
    insertNode(parentMenu, currentMenu);
    increaseIndex(currentMenu);
}

/**
 * Set Menu Invisible.
 * @param  currentMenu [input]: Is structure for current menu node
 * @param  rootMenu [input]: Is structure for root menu node
 * @see    decreaseIndex().
 * @see    deleteNode().
 * @see    getPrevious().
 * @return None.
 */
void setMenuInvisible(menuST* currentMenu, uint8 rootMenu)
{
    //menu is already invisible
    if (currentMenu->data.visible == FALSE)
    {
        return;
    }
    currentMenu->data.visible = FALSE;
    decreaseIndex(currentMenu);
    deleteNode(getPrevious(rootMenu, currentMenu), currentMenu);
}

/**
 * Set Menu Items.
 * @param   menuIndex [input]: index of Item
 * @param   parentMenuIndex [input]: index of parent
 * @param   language [input]: ENGLISH or FARSI
 * @param   timeOut [input]: Time out is m/s
 * @param   align [input]: Align of Menu Item
 * @param   color [input]: Color of Text Menu Item
 * @param   visible [input]: TRUE or FALSE
 * @param   checkPass [input]: TRUE or FALSE
 * @param   title [input]: Title of item
 * @param   size [input]: Size text of item
 * @param   index [input]: Item index
 * @param   function [input]: do a function on item
 * @param   argumentCount [input]: argument of function
 * @param   ...
 * @see     insertAtEnd().
 * @see     getMenuItem().
 * @return  None.
 */
void setMenuItem(enum menuItemNameEN menuIndex, enum menuItemNameEN parentMenuIndex, uint8 language, uint16 timeOut, uint8 align, uint8 color, uint8 visible,
                 uint8 checkPass, uint8 title[20], uint8 size, uint8 index, uint8 (*function)(argumentListST* arguments), 
                 int argumentCount, ...)
{
    va_list         args;
    argumentListST* argList = NULL;
    int             i       = 0;

    menuItemList[menuIndex].data.align = align;
    menuItemList[menuIndex].data.checkPass = checkPass;
    menuItemList[menuIndex].data.color = color;
    menuItemList[menuIndex].data.function = function;
    menuItemList[menuIndex].data.index = index;
    menuItemList[menuIndex].data.language = language;
    menuItemList[menuIndex].data.size = size;
    menuItemList[menuIndex].data.timeOut = timeOut;
    strcpy(menuItemList[menuIndex].data.title, title);
    menuItemList[menuIndex].data.visible = visible;
    menuItemList[menuIndex].leftChild = NULL;
    menuItemList[menuIndex].sibling = NULL;
    menuItemList[menuIndex].data.arguments = NULL;
  
    va_start(args, argumentCount);
    for (i = 0; i < argumentCount; i++)
    {
        if (i == 0)
        {
            menuItemList[menuIndex].data.arguments = (argumentListST*) malloc(sizeof(argumentListST));
            argList = menuItemList[menuIndex].data.arguments;
        }
        else
        {
            argList->next = (argumentListST*) malloc(sizeof(argumentListST));
            argList = argList->next;
        }

        argList->argumentName = va_arg(args, void*);

        argList->next = NULL;
    }
    
    va_end(args);
    if ((parentMenuIndex != 0) && (visible == TRUE))
    	insertAtEnd(getMenuItem(parentMenuIndex), getMenuItem(menuIndex));
}

/**
 * Get Menu Item.
 * @param   menuIndex [input]: Index of menu
 * @return  menuItemList;
 */
menuST* getMenuItem(enum menuItemNameEN menuIndex)
{
    return &menuItemList[menuIndex];
}

/**
 * Show Menu.
 * @param   rootMenu [input]: Root Menu Node
 * @see     clearDisplay().     
 * @see     getChildNode().
 * @see     displayMenu().
 * @see     checkTimeOut().
 * @see     traceDown().
 * @see     traceUp().
 * @see     openMenu().
 * @see     closeMenu().
 * @see     tracePageUp().
 * @see     tracePageDown().
 * @see     quickSelection().
 * @see     traceShortKeys().
 * @return  None.
 */
void showMenu(uint8 rootMenu)
{
    uint8	check               = 0;
    uint8	key                 = 0;
    uint8	stop                = FALSE;
    uint8   predecessorNum 		= 0;
    uint8   pageNumber          = 0;
    uint8   maxLine             = 0;
    int 	DisplayHeaderStatus = changeDisplayHeader(0);//HNO_CHANGE

    showLog(JUST_INGENICO, __FILE__, __LINE__, DEBUG, "", "showMenu");
    
    clearDisplay();
    
    selectedItem = &menuItemList[(int)rootMenu];//HNO_CHANGE casting
    selectedItem = getChildNode(selectedItem);
   
    while (!stop)	
    {	
        displayMenu(selectedItem, rootMenu);
        predecessorNum =(selectedItem->data.index - 1) % maxAssistInScreen;
        check = checkTimeOut(&key, DISPLAY_TIMEOUT);
        
        #ifdef CASTLES_V5S
             maxLine = maxAssistInScreen;
        #else
             maxLine = maxLineInScreen;
        #endif
        
        if (check != FALSE)
        {
            pageNumber = (selectedItem->data.index - 1) / maxLine ;
    //        pageNumber = (pageNumber - 1) * maxLine;
            pageNumber++;

            if (key == KBD_DOWN)
            {
               traceDown(TRUE, rootMenu);
            }
            else if (key == KBD_UP)
            {
              traceUp(TRUE, rootMenu);
            }
            
            else if (key == KBD_ENTER)
                stop = openMenu(rootMenu);
            else if (key == KBD_CANCEL)
                stop = closeMenu(rootMenu);
            else if (key == KBD_PAGE_UP)
                tracePageUp(rootMenu);
            else if (key == KBD_PAGE_DOWN)
                tracePageDown(rootMenu);
            else if (key == KBD_ATM_F1 || key == KBD_ATM_F2 || key == KBD_ATM_F3 || key == KBD_ATM_F4)
                stop = quickSelection(key, rootMenu);
            else if (key > KBD_0 &&  key <= KBD_9)      
                    if(key != KBD_6) //+MRF_971015: This is a condition for charity: INDEX IS 7 NOW ,It may change
                        stop = traceShortKeys(key - KBD_0, TRUE, rootMenu);
        }
        else	//timeout
            stop = closeMenu(rootMenu);
    }	
#if defined(ICT250) || defined(IWL220)//HNO_ADD
    changeDisplayHeader(DisplayHeaderStatus);
#endif
}

/**
 * Check bank connection number visibility.
 * @param  args [input]: Args is Variable
 * @see    checkConnectionNumber().
 * @return TRUE.
 */
uint8 checkBankConnNumberVisibility(argumentListST* args)
{
    uint8	connectionNumbers[6] = {MENU_CONNECTION1, MENU_CONNECTION2, MENU_CONNECTION3, MENU_CONNECTION4,
                                                                                    MENU_CONNECTION5, MENU_CONNECTION6};
    checkConnectionNumber(args, MENU_SETTING_CONNECTION, connectionNumbers);

    return TRUE;
}

/**
 * Check charge connection number visibility.
 * @param  args [input]: Args is Variable
 * @see    checkConnectionNumber().
 * @return TRUE.
 */
uint8 checkChargeConnNumberVisibility(argumentListST* args)
{
//    uint8	connectionNumbers[6] = {MENU_CONNECTION1_CHARGE, MENU_CONNECTION2_CHARGE, MENU_CONNECTION3_CHARGE, MENU_CONNECTION4_CHARGE,
//                                                                                    MENU_CONNECTION5_CHARGE, MENU_CONNECTION6_CHARGE};
//    checkConnectionNumber(args, MENU_CONNECTION_SETTING_CHARGE, connectionNumbers);
//
//    return TRUE;
}

/**
 * Check bill connection number visibility.
 * @param  args [input]: Args is Variable
 * @see    checkConnectionNumber().
 * @return TRUE.
 */
uint8 checkBillConnNumberVisibility(argumentListST* args)
{
//    uint8	connectionNumbers[6] = {MENU_CONNECTION1_BILL, MENU_CONNECTION2_BILL, MENU_CONNECTION3_BILL, MENU_CONNECTION4_BILL,
//                                                                                    MENU_CONNECTION5_BILL, MENU_CONNECTION6_BILL};
//    checkConnectionNumber(args, MENU_CONNECTION_SETTING_BILL, connectionNumbers);
//
//    return TRUE;
}

/**
 * Check mizan connection number visibility.
 * @param  args [input]: Args is Variable
 * @see    checkConnectionNumber().
 * @return TRUE.
 */
uint8 checkMizanConnNumberVisibility(argumentListST* args)
{
//    uint8	connectionNumbers[] = {MENU_CONNECTION1_MIZAN, MENU_CONNECTION2_MIZAN, MENU_CONNECTION3_MIZAN, MENU_CONNECTION4_MIZAN,
//                                                                                    MENU_CONNECTION5_MIZAN, MENU_CONNECTION6_MIZAN};
//    checkConnectionNumber(args, MENU_CONNECTION_SETTING_MIZAN, connectionNumbers);
//
//    return TRUE;
}

/**
 * Check connection number.
 * @param   args [input]: Args is variable
 * @param   parentMenuIndex [input]: Parent menu index
 * @param   connectionNumbers [input]: Connection Number
 * @see     getChild().
 * @see     setMenuVisible().
 * @see     getMenuItem().
 * @see     getGeneralConnInfo().
 * @return  None.
 */
void checkConnectionNumber(argumentListST* args, enum menuItemNameEN parentMenuIndex, uint8* connectionNumbers)
{    
    filesST*            files               = (filesST*) (args->argumentName);
	menuST*             parentMenu          = getMenuItem(parentMenuIndex);
	menuST*             childMenu			= 0;  // never used
    int                 counter             = 0;
    generalConnInfoST	generalConnInfo;    /* general configuration information */

    memset(&generalConnInfo, 0, sizeof(generalConnInfoST));
	childMenu = getChild(parentMenu);  // never used

    
    generalConnInfo = getGeneralConnInfo(files->id); 
    
//	for (counter = 0; counter < 6; counter++)
//		showLog(JUST_CASTLES, __FILE__, __LINE__, DEBUG, "", "conn Num %d ", connectionNumbers[counter]);
    
	// set menu visible
	for (counter = 0; counter < generalConnInfo.connectionCount; counter++)
	{
        setMenuVisible(parentMenu, getMenuItem(connectionNumbers[counter]));
    }

    // set menu InVisible
    for (counter = generalConnInfo.connectionCount; counter < MAX_CONNECTION_NUMBER; counter++)
    {
        setMenuInvisible(getMenuItem(connectionNumbers[counter]), MENU_KEY_ROOT);
    }
}

/**
 * Set Menu Visiblity.
 * @param   server [input]: Is structure
 * @param   cardDependantMenus [input]: Card dependant menus
 * @param   cardLen [input]: Card Length
 * @param   KeyDependantMenus [input]: Key dependant menus
 * @param   Keylen [input]: Key length
 * @see     searchMenuItem().
 * @see     setMenuVisible().
 * @see     getMenuItem().
 * @return  None.   
 */
void setMenuVisibility(serverSpecST* server, uint8* cardDependantMenus, uint8 cardLen, 
                       uint8* KeyDependantMenus, uint8 Keylen)
{    
    int	counter = 0;

    if (server->isMenuVisible) 
    {
        for (counter = 0; counter < cardLen; counter++)
        {
        	if (searchMenuItem(MENU_CARD_ROOT, cardDependantMenus[counter]))
        		setMenuVisible(getMenuItem(MENU_CARD_ROOT), getMenuItem(cardDependantMenus[counter]));	
        }
        
        for (counter = 0; counter < Keylen; counter++)
        {
        	//if menu exist
        	if (searchMenuItem(MENU_KEY_ROOT, KeyDependantMenus[counter]))
            {
                    setMenuVisible(getMenuItem(MENU_KEY_ROOT), getMenuItem(KeyDependantMenus[counter]));	
            }
        }
    }
    else
    {
        for (counter = 0; counter < cardLen; counter++)
        {            
        	if (searchMenuItem(MENU_CARD_ROOT, cardDependantMenus[counter]))
        		setMenuInvisible(getMenuItem(cardDependantMenus[counter]), MENU_CARD_ROOT);
        }
        
        for (counter = 0; counter < Keylen; counter++)
        {
        	if (searchMenuItem(MENU_KEY_ROOT, KeyDependantMenus[counter]))
        		setMenuInvisible(getMenuItem(KeyDependantMenus[counter]), MENU_KEY_ROOT);            
        }        
    }
}


/**
 * Search Menu Item.
 * @param   root [input]: Root node 
 * @param   menuItem [input]: Menu item
 * @see     searchNode().
 * @see     getMenuItem().
 * @return TRUE or FALSE.
 */
uint8 searchMenuItem(uint8 root, uint8 menuItem)
{
	if (searchNode(getMenuItem(root), getMenuItem(menuItem)) != NULL)
    {
		return TRUE;
    }
	else
    {
		return FALSE;
    }
}

/**
 * Get Menu Item List.
 * @param   id [input]: Menu Item id
 * @return  menuItemList.
 */
menuST* getMenuItemList(uint8 id)
{
    return &menuItemList[id];
}

/**
 * Free Menu Memory.
 * @see free().
 * @return TRUE.
 */
uint8 freeMenuMemory(void)
{
	int i = 0;

	for (i; i < MENU_ITEM_COUNT; i++)
		free(menuItemList[i].data.arguments);
	return TRUE;
}

/**
 * Get Max Assist Line In Screen this used for Help to show menu.
 * @return maxAssistInScreen.
 */
uint8 getMaxAssistInScreen(void)
{
    return maxAssistInScreen;
}

/**
 * Check Maskan PAN.
 * @param   PAN [input]: PAN
 * @see     setMizanMenuVisibility().
 * @see     checkMaskanMenusVisibility().
 * @return  None.
 */
void checkMaskanMenus(int8* PAN)
{
//    if (strncmp(PAN, "628023", 6) == 0)
//    {
//        setMizanMenuVisibility(TRUE);
//    }
//    else
//    {
//        checkMaskanMenusVisibility(FALSE);
//    }
}

/**
 * Set Bill menu visibility.
 * @param   server [input]: Is structure
 * @see     searchMenuItem().
 * @see     setMenuVisibility().
 * @return  TRUE.
 */
uint8 setBillMenuVisibility(serverSpecST* server)
{    
//    uint8   cardDependantMenus[] = {MENU_ITEM_BILL_PAY};
//    uint8   keyDependantMenus[]  = {MENU_TRANSACTION_BILL_LIST, MENU_REPRINT_BILL_TRANSACTION,
//    				   MENU_BILL_SETTING, MENU_SETTLEMENT_BILL};
//	
//	if (searchMenuItem(MENU_KEY_ROOT, MENU_CONFIGURATION_BILL))
//	{			
//        setMenuVisibility(server, cardDependantMenus, 1, keyDependantMenus, 4);
//	}
//
//    return TRUE;
}


/**
 * Set charge menu visibility.
 * @param   server [input]: Is structutre
 * @see     searchMenuItem().
 * @see     setMenuVisibility().
 * @return  TRUE.
 */
uint8 setChargeMenuVisibility(serverSpecST* server)
{   
//    uint8   cardDependantMenus[] = {/*MENU_ITEM_BUY_CHARGE,*/ MENU_ITEM_BUY_MULTI_CHARGE};
//    uint8   keyDependantMenus[] = {MENU_CHARGE_SETTING, MENU_TRANSACTION_CHARGE_LIST, 
//    								MENU_SETTLEMENT_CHARGE, MENU_UNSUCCESS_CHARGE_TRANSACTION};
//
//    if (searchMenuItem(MENU_KEY_ROOT, MENU_CONFIGURATION_CHARGE))
//    {			
//        setMenuVisibility(server, cardDependantMenus, 2, keyDependantMenus, 4);
//    }
//
//    return TRUE;
}

/**
 * Check Server Menu Visibility.
 * @param   serverSpec [input]: Is structutre
 * @see     setBillMenuVisibility().
 * @see     setMizanMenuVisibility().
 * @see     setChargeMenuVisibility().
 * @return  TRUE.
 */
uint8 checkServersMenusVisibility(serverSpecST* serverSpec)
{    
//    serverSpecST* servers;
//
//    servers = serverSpec;
//    while (servers != NULL)
//    {
//        switch (servers->files.id)
//        {
//            case 0:
//                break;
//            case 1:
//                setBillMenuVisibility(servers);
//                break;
//            case 2:
//                setMizanMenuVisibility(servers);
//                break;
//            case 3:
//                setChargeMenuVisibility(servers);
//                break;
//        }
//
//        servers = servers->next;     
//    }   
//    
//    return TRUE;
}

/**
 * Check Maskan Menus Visibility.
 * @param   visible [input]: TRUE or FALSE
 * @see     setMenuVisible().
 * @see     getMenuItem().
 * @return  TRUE.
 */
uint8 checkMaskanMenusVisibility(uint8 visible)
{    
//    uint8   dependantMenus[]    = {MENU_ITEM_LOAN_PAYMENT, MENU_ITEM_BILL_CARD};
//    int     counter             = 0;
//    
//    for (counter = 0; counter < 2; counter++)
//    {
//        if (visible)
//        {
//            setMenuVisible(getMenuItem(MENU_CARD_ROOT), getMenuItem(dependantMenus[counter]));	
//        }
//        else
//        {
//            setMenuInvisible(getMenuItem(dependantMenus[counter]), MENU_CARD_ROOT);
//        }
//    }
//    
//    return TRUE;
}
