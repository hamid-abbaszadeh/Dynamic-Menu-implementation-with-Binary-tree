


#ifdef  PROGRAMMER
static 	uint8  	logType	= FATAL;
static 	uint8  	logPort	= USB;
#else
static 	uint8  	logType	= RELEASE;
static 	uint8  	logPort	= USB;
#endif



uint8 readLogType(void);
uint8 readLogPort(void);
uint8 writeLogPort(void);
uint8 writeLogType(void);

/**
 * Get log type.
 * @return  logType.
 */
uint8 getLogType(void)
{
    return logType;
}


/**
 * Set log type.
 * @see     clearDisplay().
 * @see     checkLogMenuPassword().
 * @see     selectItemPage().
 * @see     writeLogType().
 * @see     closeSerialPort().
 * @see     displayforeColor().
 * @return  None.
 */
void setLogType(void)
{
   uint8   selectionItems[][20]    = {"RELEASE", "TRACE", "DEBUG", "FATAL", "TEST"}; //MRF_954
   uint8   selectedItemIndex       = getLogType();
    
    clearDisplay();
    //comment by HNO
//    if (checkLogMenuPassword())
//    {
    //HNO_IDENT9
        if (selectItemPage("Log Type ?", selectionItems, ENGLISH, 5, &selectedItemIndex, DISPLAY_TIMEOUT))
        {
            logType = selectedItemIndex; 
            writeLogType();
            if (logType == RELEASE || logType == TEST) //MRF_954
            	closeSerialPort(LOG_PORT);
            //HNO_IDENT
#ifndef INGENICO
            else
                openSerialPort(LOG_PORT, BAUD_RATE_115200, PARITY, DATA_SIZE, STOP_BITS);
#endif
        }
//    }
    displayforeColor(BLUE);
    clearDisplay(); 
}

/**
 * Initialize log type.
 * @see     readLogType().
 * @return  None.
 */
void initLogType(void)
{
   readLogType();
   readLogPort();
}

/**
 * Read log type.
 * @see     fileExist().
 * @see     readFileInfo().
 * @return  TRUE or FALSE.
 */
uint8 readLogType(void)  
{
    int16   retValue = FAILURE;                      /* file functions return value */
    uint32  sizeOfFile = sizeof(uint8);                /* size of settlement file */

    if (fileExist(LOG_TYPE_FILE) == SUCCESS)
    {
        retValue = readFileInfo(LOG_TYPE_FILE, &logType, &sizeOfFile);

        if (retValue != SUCCESS)
        {
            logType = RELEASE;
        }
    }
        
    return (retValue == SUCCESS) ? TRUE : FALSE;
}

/**
 * Write log type.
 * @see     showLog().
 * @see     updateFileInfo().
 * @see     addSystemErrorReport().
 * @return  TRUE or FALSE.
 */
uint8 writeLogType(void)  
{
    int16 retValue = FAILURE;                   /* file functions return value */

    //showLog(JUST_INGENICO, __FILE__, __LINE__, DEBUG, "", "**UPDATE: LOG_TYPE_FILE");
    retValue = updateFileInfo(LOG_TYPE_FILE, &logType, sizeof(uint8));
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
    
    return (retValue == SUCCESS) ? TRUE : FALSE;
}

/**
 * Show log.
 * @param   posType [input]: the type of pos
 * @param   file [input]: file
 * @param   line [input]: line to show message log
 * @param   level [input]: log type(release,trace,...)
 * @param   title [input]: used for grouping logs 
 * @param   message [input]:  text message to show
 * @see     getDateTime().
 * @see     getHour().
 * @see     getMinute().
 * @see     gregorianToJalali().
 * @see     getYear().
 * @see     getMonth().
 * @see     getDay().
 * @see     logPrintf().
 * @return  None.
 */
void showLog(uint8 posType, uint8* file, uint32 line, uint8 level, uint8* title, uint8* message, ...)
{
	va_list		args;
	uint8 		output[512]		= {0};
	dateTimeST	dateTime		= {0, 0};
	int			hour			= 0;
	int			minute			= 0;
    int			second			= 0;	
	int			year			= 0;
	int			month			= 0;
	int			day				= 0;
	uint8 		str[512]		= {0};	
	uint8 		fileInfo[100]	= {0};		
    uint32		jalaliDate		= 0;

#ifdef CASTLES          
	if ((posType & JUST_CASTLES) || (posType & ALL_POS))
#elif defined (ICT250) || defined(IWL220)
	if ((posType & JUST_INGENICO) || (posType & ALL_POS))
#elif defined (VX520)											//ABS:ADD
	if ((posType & JUST_VERIFONE) || (posType & ALL_POS))
#endif   
        
        if ((level == getLogType()) || (level == TRACE && DEBUG == getLogType())
             || ((level == TRACE || level == DEBUG) && FATAL == getLogType()))
		{
			va_start(args, message);
#ifdef INGENICO //HNO_IDENT
			vsprintf(output, message, &args);
#else
			vsprintf(output, message, args);
#endif
			va_end(args);
	
			dateTime = getDateTime();
			hour = getHour(dateTime.time);
			minute = getMinute(dateTime.time);
            second = getSecond(dateTime.time);
	
			gregorianToJalali(&jalaliDate , dateTime.date);
			year = getYear(jalaliDate);
			month = getMonth(jalaliDate);
			day = getDay(jalaliDate);
			
            sprintf(str, "%d/%d/%d, %d:%d:%d | ", year, month, day, hour, minute, second);
            sprintf(fileInfo, "File: %-30s Line: %-5ld | ", file, line);

			strcat(str, fileInfo);
			strcat(str, title);
			strcat(str, output);
            
			logPrintf(str, getLogPort()); //MRF_NEW14
		}
}

//MRF_NEW14
void setLogPort(void)
{
    uint8   selectionItems[][20]    = {"USB", "COM2","NONE"};
    uint8   selectedItemIndex       = getLogType();
    
    clearDisplay();

    if (selectItemPage("Log Port ?", selectionItems, ENGLISH, 3, &selectedItemIndex, DISPLAY_TIMEOUT))
    {
        logPort = selectedItemIndex; 
        writeLogPort();
    }
    displayforeColor(BLUE);
    clearDisplay(); 
}

//MRF_NEW14
uint8 writeLogPort(void)  
{
    int16 retValue = FAILURE;                   /* file functions return value */

    retValue = updateFileInfo(LOG_PORT_FILE, &logPort, sizeof(uint8));
    if (retValue != SUCCESS)
    {
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    }
    
    return (retValue == SUCCESS) ? TRUE : FALSE;
}

uint8 getLogPort(void)
{
    return logPort;
}

//MRF_NEW16
uint8 readLogPort(void)  
{
    int16   retValue = FAILURE;                      /* file functions return value */
    uint32  sizeOfFile = sizeof(uint8);                /* size of settlement file */

    if (fileExist(LOG_PORT_FILE) == SUCCESS)
    {
        retValue = readFileInfo(LOG_PORT_FILE, &logPort, &sizeOfFile);

        if (retValue != SUCCESS)
        {
            logPort = NO_PORT;
        }
    }
        
    return (retValue == SUCCESS) ? TRUE : FALSE;
}

