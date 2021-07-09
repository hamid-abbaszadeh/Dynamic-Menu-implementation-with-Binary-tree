


#define START_LOGON_TIME    0
#define END_LOGON_TIME      8



 static scheduleST   schedules[SCHEDULES_NUMBER] = {0};

scheduleST readOneSchedule(filesST* files, int scheduleType);
uint16 writeSchedules(filesST* files);
void setSchedule(filesST* files, int scheduleType, uint8 setMember, scheduleST schedule);

/**
 * Get schedule.
 * @param   scheduleIndex [output]: index of schedule
 * @return  schedules index.
 */
scheduleST getSchedule(uint8 scheduleIndex)
{
      return schedules[scheduleIndex];
}

/**
 * Get max count of schedule.
 * @param   baseScheduleTime [input]: base of schedule time
 * @see     showLog().
 * @see     power().
 * @return  maxScheduleCount.
 */
uint8 getMaxScheduleCount(uint8 baseScheduleTime)
{
    uint8   maxTime             = 0;
    uint8   maxScheduleCount    = 0;
    
    maxTime = (MAX_SCHEDULE_TIME) / baseScheduleTime;  // 5 month
    
    while (TRUE) 
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "MaxScheduleCount: %d", maxScheduleCount);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "maxTime: %d", maxTime);
        if (power(2, maxScheduleCount) > maxTime && maxTime < power(2, maxScheduleCount + 1))
            break;
        maxScheduleCount++;
    }
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "return MaxScheduleCount: %d", maxScheduleCount);

    return maxScheduleCount;
}

/**
 * Read schedules from file.
 * @param   files [input]: file which have schedule
 * @see     showLog().
 * @see     readFileInfo().
 * @see     power().
 * @return  retValue (schedules).
 */
int16 readSchedules(filesST* files)  
{
    int16   retValue = FAILURE;                                 /* write in file function return value */
    uint32  len      = sizeof(scheduleST) * SCHEDULES_NUMBER;  

    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "***readSchedules***");
    
    memset(&schedules, 0, sizeof(scheduleST) * SCHEDULES_NUMBER);    

	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "readSchedules", "schedule file = %s", files->scheduleFile);
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "readSchedules", "file = %s", files->scheduleFile);
    
    retValue = readFileInfo(files->scheduleFile, schedules, &len);    
    
    return retValue;
}

/**
 * Read one schedule from file.
 * @param   files [input]: file which have schedule
 * @param   scheduleType [input]: type of schedule
 * @return  emptySchedule or schedules.
 */
scheduleST readOneSchedule(filesST* files, int scheduleType) 
{
    uint16 			readScheduleRes = FAILURE;
    scheduleST   	emptySchedule;

    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "***readOneSchedule***");
     
	memset(&emptySchedule, 0, sizeof(scheduleST));

    emptySchedule.set = FALSE;
    emptySchedule.datetime.date = 0;
    emptySchedule.datetime.time = 0;
    emptySchedule.orginDatetime.date = 0;
    emptySchedule.orginDatetime.time = 0;
    emptySchedule.scheduleCount = 0; 
    readScheduleRes = readSchedules(files);  
    
    if (readScheduleRes == SUCCESS)
        return schedules[scheduleType];

    return emptySchedule;
}

/**
 * Write schedules to file.
 * @param   files [input]: file which have schedule
 * @see     showLog().
 * @see     updateFileInfo().
 * @see     addSystemErrorReport().
 * @return  retValue(SUCCESS or FAILURE).
 */
uint16 writeSchedules(filesST* files)  
{
    int16  retValue     = FAILURE;                                  /* write in file function return value */
    uint32 len          = sizeof(scheduleST) * SCHEDULES_NUMBER;      
    
    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**UPDATE: scheduleFile");
    retValue = updateFileInfo(files->scheduleFile, schedules, len);    
    if (retValue != SUCCESS)
        addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
    
    return retValue;
}

/**
 * Set schedules to file.
 * @param   files [output]: file which have schedule
 * @param   scheduleType [input]: type of schedule
 * @param   setMember [input]: set member
 * @param   schedule [input]: schedule
 * @see     isBitSet().
 * @see     writeSchedules().
 * @return  retValue(SUCCESS or FAILURE).
 */
void setSchedule(filesST* files, int scheduleType, uint8 setMember, scheduleST schedule)  
{
    
    uint8 temp = 0;                   /** temp bit array */
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***setSchedule***");
    
    temp = setMember;
    if (isBitSet(0, temp))    
        schedules[scheduleType].set = schedule.set;
    temp = setMember;
    if (isBitSet(1, temp))    
        schedules[scheduleType].datetime = schedule.datetime;
    temp = setMember;
    if (isBitSet(2, temp)) 
    {
//        memset(schedules[scheduleType].phone, 0, sizeof(schedules[scheduleType].phone));
 //       strncpy(schedules[scheduleType].phone, schedule.phone, strlen(schedule.phone));
    }
    temp = setMember;
    if (isBitSet(3, temp))    
        schedules[scheduleType].lastDatetime = schedule.lastDatetime;
    temp = setMember;
    if (isBitSet(4, temp))    
        schedules[scheduleType].orginDatetime = schedule.orginDatetime;
    temp = setMember;
 /*   if (isBitSet(5, temp))    
        schedules[scheduleType].phoneCode = schedule.phoneCode;*/
    
    // TODO: mgh: correct with "isBitSet"
    schedules[scheduleType].scheduleCount = schedule.scheduleCount;
    
    writeSchedules(files);
}

/**
 * Set periodic TMS schedule.
 * @param   files [output]: file which have schedule
 * @param   day [input]: day of TMS 
 * @see     showLog().
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     getDateTime().
 * @see     getSecond().
 * @see     randomTime().
 * @see     displayMessageBox().
 * @see     setNextDate().
 * @see     setTime().
 * @see     setSchedule().
 * @return  None.
 */
void setPeriodicTMSSchedule(filesST* files, uint8 day)  
{
   scheduleST   tempSchedule;             /* temp command structure */
   dateTimeST   nowDateTime = {0, 0};     /* current date and time */
   int          hour        = 0;
   int          minute      = 0;
   int          second      = 0;
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "***setPeriodicTMSSchedule***");
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   tempSchedule = readOneSchedule(files, SCHEDULES_TMS_CONFIG);
   
   nowDateTime = getDateTime();
   
/*
 * //mgh: random time for TMS
   int s = 0;
   int e = 0;
   srand(getSecond(systemDateTimeToTime()));
   s = rand() % 23;
   e = rand() % 23;
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Start: %d  End: %d", s, e);
*/
   
   if (!randomTime(START_PERIODIC_TMS_TIME, END_PERIODIC_TMS_TIME, &hour, &minute))
   {
       displayMessageBox("ÈÇÒå ÊÚÑíöÝ ÔÏå ÇÔÊÈÇå ÇÓÊ", MSG_ERROR);
       showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "FAILED! --> set Periodic TMS Schedule");
       return;
   }
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "Set setPeriodicTMSSchedule", "hour: %d  minute: %d", hour, minute);
   
   tempSchedule.set = TRUE;
   tempSchedule.datetime.date = setNextDate(nowDateTime.date, 0, 0, day);
   tempSchedule.datetime.time = setTime(hour, minute, second);

   setSchedule(files, SCHEDULES_PERIODIC_TMS, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Set TMS run schedule.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     resetTMSRunSchedule().
 * @see     setSchedule().
 * @details this function is not use currently.
 * @return  None.
 */
void setTMSRunSchedule(filesST* files)  
{
   scheduleST   tempSchedule;                       /* temp command structure */
   dateTimeST   nowDateTime         = {0, 0};       /* current date and time */
   int          nextTime            = 0; 
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   tempSchedule = readOneSchedule(files, SCHEDULES_TMS);
   
   nowDateTime = getDateTime();
   
   tempSchedule.scheduleCount = schedules[SCHEDULES_TMS].scheduleCount;
   nextTime = (SCHEDULES_TMS_RUN_NEXT_TIME * power(2, tempSchedule.scheduleCount));
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
   tempSchedule.scheduleCount++;
   if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_TMS_RUN_NEXT_TIME))
   {
       resetTMSRunSchedule(files);
   }
   else
   {
       tempSchedule.set = TRUE;
       tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0);

       setSchedule(files, SCHEDULES_TMS, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
   }
}

/**
 * Set TMS update schedule.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     getDateTime().
 * @see     resetTMSUpdateSchedule().
 * @see     setSchedule().
 * @see     setNextTime().
 * @details this function is not use currently.
 * @return  None.
 */
void setTMSUpdateSchedule(filesST* files)  
{
   scheduleST   tempSchedule;             /* temp command structure */
   dateTimeST   nowDateTime = {0, 0};     /* current date and time */
   uint8        nextTime    = 0;
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   tempSchedule = readOneSchedule(files, SCHEDULES_TMS_UPDATE);
   
   nowDateTime = getDateTime();
   
   tempSchedule.scheduleCount = schedules[SCHEDULES_TMS_UPDATE].scheduleCount;
   nextTime = (SCHEDULES_TMS_UPDATE_NEXT_TIME * power(2, tempSchedule.scheduleCount));
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
   tempSchedule.scheduleCount++;
   if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_TMS_UPDATE_NEXT_TIME))
   {
       resetTMSUpdateSchedule(files);
   }
   else
   {
       tempSchedule.set = TRUE;
       tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0);

       setSchedule(files, SCHEDULES_TMS_UPDATE, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
   }
}

/**
 * Set TMS configuration schedule.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     getDateTime().
 * @see     resetTMSUpdateSchedule().
 * @see     setSchedule().
 * @see     setNextTime().
 * @details this function is not use currently.
 * @return  None.
 */
void setTMSConfigSchedule(filesST* files)  
{
   scheduleST   tempSchedule;             /* temp command structure */
   dateTimeST   nowDateTime = {0, 0};     /* current date and time */
   uint8        nextTime    = 0;
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   tempSchedule = readOneSchedule(files, SCHEDULES_TMS_CONFIG);
   
   nowDateTime = getDateTime();
   
   tempSchedule.scheduleCount = schedules[SCHEDULES_TMS_CONFIG].scheduleCount;
   nextTime = (SCHEDULES_TMS_CONFIG_NEXT_TIME * power(2, tempSchedule.scheduleCount));
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
   tempSchedule.scheduleCount++;
   if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_TMS_CONFIG_NEXT_TIME))
   {
       resetTMSConfigSchedule(files);
   }
   else
   {
       tempSchedule.set = TRUE;
       tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0);

       setSchedule(files, SCHEDULES_TMS_CONFIG, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
   }
}

/**
 * Reset periodic TMS schedule.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     getDateTime().
 * @see     setSchedule().
 * @return  None.
 */
void resetPeriodicTMSSchedule(filesST* files)  
{
   scheduleST tempSchedule;             /* temp command structure */
   dateTimeST nowDateTime = {0, 0};     /* current date and time */
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "resetPeriodicTMSSchedule");
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   
   nowDateTime = getDateTime();

   tempSchedule.set = FALSE;
   tempSchedule.datetime.date = 0;
   tempSchedule.datetime.time = 0;

   setSchedule(files, SCHEDULES_PERIODIC_TMS, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Reset TMS run schedule.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     getDateTime().
 * @see     setSchedule().
 * @return  None.
 */
void resetTMSRunSchedule(filesST* files)  
{
   scheduleST tempSchedule;             /* temp command structure */
   dateTimeST nowDateTime = {0, 0};     /* current date and time */
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   
   nowDateTime = getDateTime();

   tempSchedule.set = FALSE;
   tempSchedule.datetime.date = 0;
   tempSchedule.datetime.time = 0;
   tempSchedule.scheduleCount = 0;

   setSchedule(files, SCHEDULES_TMS, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Reset TMS update schedule.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     getDateTime().
 * @see     setSchedule().
 * @return  None.
 */
void resetTMSUpdateSchedule(filesST* files)  
{
   scheduleST tempSchedule;             /* temp command structure */
   dateTimeST nowDateTime = {0, 0};     /* current date and time */
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   
   nowDateTime = getDateTime();

   tempSchedule.set = FALSE;
   tempSchedule.datetime.date = 0;
   tempSchedule.datetime.time = 0;
   tempSchedule.scheduleCount = 0;

   setSchedule(files, SCHEDULES_TMS_UPDATE, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Reset TMS configuration schedule.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     getDateTime().
 * @see     setSchedule().
 * @return  None.
 */
void resetTMSConfigSchedule(filesST* files)  
{
   scheduleST tempSchedule;             /* temp command structure */
   dateTimeST nowDateTime = {0, 0};     /* current date and time */
   
   memset(&tempSchedule, 0, sizeof(scheduleST));
   readSchedules(files);
   
   nowDateTime = getDateTime();

   tempSchedule.set = FALSE;
   tempSchedule.datetime.date = 0;
   tempSchedule.datetime.time = 0;
   tempSchedule.scheduleCount = 0;

   setSchedule(files, SCHEDULES_TMS_CONFIG, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Set log on schedule for tomorrow.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     getDateTime().
 * @see     randomTime().
 * @see     displayMessageBox().
 * @see     setNextDate().
 * @see     setSchedule().
 * @return  None.
 */
void setLogonScheduleForTomorrow(filesST* files)  
{
    scheduleST  tempSchedule;            /* temp command structure */
    dateTimeST  nowDateTime;             /* current date and time */
    int         hour        = 0;
    int         minute      = 0;
    int         second      = 0;
    
    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "set Logon Schedule For Tomorrow");
    
    readSchedules(files);
    tempSchedule = readOneSchedule(files, SCHEDULES_LOGON);
    
    nowDateTime = getDateTime();  
    
/*
    //mgh: random time for LogOn
    int s = 0;
    int e = 0;
    srand(getSecond(systemDateTimeToTime()));
    s = rand() % 23;
    e = rand() % 23;
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Start: %d  End: %d", s, e);
    if (!randomTime(s, e, &hour, &minute))
*/
 
    if (!randomTime(START_LOGON_TIME, END_LOGON_TIME, &hour, &minute))
    {
       displayMessageBox("ÈÇÒå ÊÚÑíöÝ ÔÏå ÇÔÊÈÇå ÇÓÊ", MSG_ERROR);
       showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "FAILED! --> set Logon Schedule For Tomorrow");
       return;
    }
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "hour: %d  minute: %d", hour, minute);
   
    tempSchedule.set = TRUE;
    
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "preLogOnDate:");
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "year: %d", getYear(nowDateTime.date));
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "month: %d", getMonth(nowDateTime.date));
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "day: %d", getDay(nowDateTime.date));
    
    tempSchedule.datetime.date = setNextDate(nowDateTime.date, 0, 0, 1);
    
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "nextLogOnDate:");
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "year: %d", getYear(tempSchedule.datetime.date));
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "month: %d", getMonth(tempSchedule.datetime.date));
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "day: %d", getDay(tempSchedule.datetime.date));
    
        
    tempSchedule.datetime.time = setTime(hour, minute, second);

    setSchedule(files, SCHEDULES_LOGON, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * set reversal schedule after initiate schedules.
 * @param   files [output]: file which have schedule
 * @see     getDateTime().
 * @see     readSchedules().
 * @see     setSchedule().
 * @details this function is not use currently.
 * @return  None.
 */
void setReversalScheduleAfterInitSchedule(filesST* files)  
{
    scheduleST tempSchedule;            /* temp command structure */
    dateTimeST nowDateTime;             /* current date and time */

    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));

    readSchedules(files);
    nowDateTime = getDateTime();
    
    tempSchedule.set = TRUE;
    tempSchedule.datetime = nowDateTime; 

    setSchedule(files, SCHEDULES_REVERSAL, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}


/**
 * Set reversal schedule after unsuccess reversal.
 * @param   files [output]: file which have schedule
 * @see     getDateTime().
 * @see     readSchedules().
 * @see     showLog().
 * @see     resetReversalSchedule().
 * @see     setNextTime().
 * @see     setSchedule().
 * @details this function is not use currently.
 * @return  None.
 */
void setReversalScheduleAfterUnsuccessReversal(filesST* files)  
{
    scheduleST  tempSchedule;            /* temp command structure */
    dateTimeST  nowDateTime;             /* current date and time */
    uint8       nextTime = 0;

    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));
    
   readSchedules(files);
   nowDateTime = getDateTime();
   
   tempSchedule.scheduleCount = schedules[SCHEDULES_REVERSAL].scheduleCount;
   nextTime = (SCHEDULES_REVERSAL_TIME * power(2, tempSchedule.scheduleCount));
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
   tempSchedule.scheduleCount++;
   if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_REVERSAL_TIME))
   {
       resetReversalSchedule(files);
       //mgh fileRemove(files->reversalReceiptFile);
       //mgh fileRemove(files->reversalTransFile);
   }
   else
   {
        tempSchedule.set = TRUE;
        tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0); 

        setSchedule(files, SCHEDULES_REVERSAL, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
   }
}

/**
 * specify that specific schedule is set or not.
 * @param   files [output]: file which have schedule
 * @param   scheduleType [output]: type of schedule
 * @see     readSchedules().
 * @details this function is not use currently.
 * @return  TRUE or FALSE.
 */
uint8 isScheduleSet(filesST* files, int scheduleType)  
{
    uint16 readScheduleRes = FAILURE;

    readScheduleRes = readSchedules(files);  
    if (readScheduleRes == SUCCESS)
    {
        if (schedules[scheduleType].set)    
            return TRUE;
        else    
            return FALSE;
    }
    return FALSE;
}

/**
 * specify that settlement Schedule after unsuccess settlement is set or not.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     showLog().
 * @see     getDateTime().
 * @see     power().
 * @see     resetSettlementSchedule().
 * @see     setNextTime().
 * @see     setSchedule().
 * @return  None.
 */
void setSettlementScheduleAfterUnsuccessSettlement(filesST* files)  
{
    scheduleST          tempSchedule;                     
    dateTimeST          nowDateTime;        
    uint8               nextTime = 0;
    
    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));

    readSchedules(files);

    tempSchedule = readOneSchedule(files, SCHEDULES_SETTLEMENT);

    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "setSettlementScheduleAfterUnsuccessSettlement");

    nowDateTime = getDateTime();
    
    tempSchedule.scheduleCount = schedules[SCHEDULES_SETTLEMENT].scheduleCount;
    nextTime = (SCHEDULES_SETTLEMENT_TIME * power(2, tempSchedule.scheduleCount));

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
    tempSchedule.scheduleCount++;
    if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_SETTLEMENT_TIME))
    {
        resetSettlementSchedule(files);
        //mgh fileRemove(files->settelmentInfoFile);
    }
    else
    {
         tempSchedule.set = TRUE;
         tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0); 

         setSchedule(files, SCHEDULES_SETTLEMENT, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
    }
}

/**
 * specify that settlement Schedule after Initiate schedule is set or not.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     readOneSchedule().
 * @see     setSchedule().
 * @details this function is not use currently.
 * @return  None.
 */
void setSettlementScheduleAfterInitSchedule(filesST* files)   
{
    scheduleST          tempSchedule;               /* temp command structure */
    dateTimeST          nowDateTime;                /* current date and time */
 
    
    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));
    
    readSchedules(files);
    nowDateTime = getDateTime();

    tempSchedule.set = TRUE;
    tempSchedule.datetime = nowDateTime;
  
    setSchedule(files, SCHEDULES_SETTLEMENT, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Initiate schedules.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     writeSchedules().
 * @details this function is not use currently.
 * @return  None.
 */
void initSchedules(filesST* files)  
{          
    uint16 readScheduleRes	= FAILURE;                /* read from file return value */
    int    counter          = 0;                      /* loop counter */
  
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "init schedules");
    readScheduleRes = readSchedules(files);
    
    if (readScheduleRes != SUCCESS) 
    {   
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "read failed");
        for (counter = 0; counter < SCHEDULES_NUMBER; counter++) 
        {
            schedules[counter].set = FALSE;
            schedules[counter].datetime.date = 0;
            schedules[counter].datetime.time = 0;
            schedules[counter].lastDatetime.date = 0;
            schedules[counter].lastDatetime.time = 0;
            schedules[counter].orginDatetime.date = 0;
            schedules[counter].orginDatetime.time = 0;
        }
        writeSchedules(files);
    }
    
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "finished  schedules");
}

/**
 * Next schedule.
 * @param   serverSpec [input]: the number of servers
 * @param   schedule [output]: schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     compareDateTime().
 * @see     getHour().
 * @see     getMinute().
 * @return  None.
 */
void nextSchedule(serverSpecST* serverSpec, nextScheduleST* schedule)
{
    uint8           i       = 0;
    uint8           counter = 0;
    serverSpecST*	server  = NULL;

    schedule->group = 0;
    schedule->existance = FALSE;
    schedule->type = -1;
    schedule->dateTime.date = 0;
    schedule->dateTime.time = 0;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*************** check existing schedules**************");
//    server = serverSpec;
//    while (server != NULL)
//    {
//        readSchedules(&(server->files));  /// read schedules to static variable
//
//        for (counter = 0; counter < SCHEDULES_NUMBER; counter++) 
//        {
//            if (schedules[counter].set)
//            {
//                schedule->group = i; // mgh
//                schedule->existance = TRUE;
//                schedule->type = counter;
//                schedule->dateTime = schedules[counter].datetime;
//                //showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "set = %d, type = %d , dateTime = %d, time = %d", schedules[counter].set, counter, 
//                //showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "set = %d, type = %d , dateTime = %d, time = %d", schedules[counter].set, counter, 
//				//showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "set = %d, type = %d , dateTime = %d, time = %d", schedules[counter].set, counter, 
//                //schedules[counter].datetime.date, schedules[counter].datetime.time ));
//                showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "P_TMS enable");
//                break;
//            }
//            
//        }
//        server = server->next;
//        i++; // mgh & eli
//    }
//
//    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "nextSchedule()", "*****************");    
//    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "nextSchedule()", "server = %d, type = %d , HH = %d, MM = %d", schedule->group, schedule->type,
//    		getHour( schedule->dateTime.time), getMinute( schedule->dateTime.time) );
//    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "nextSchedule()", "Finding MIN EXISTANCE=%d", schedule->existance);
//    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "nextSchedule()", " Finding minimum check existing schedules");
//    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "nextSchedule()", "*****************");
//
//    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*****************");    
//    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "server = %d, type = %d , HH = %d, MM = %d", schedule->group, schedule->type, 
//        getHour( schedule->dateTime.time), getMinute( schedule->dateTime.time) );
//    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*****************");
//    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", " Finding minimum check existing schedules");
//    if (!schedule->existance)
//    {
//        showLog(JUST_VERIFONE, __FILE__, __LINE__, TRACE, "", "____________NOT___EXIST_____RETURN________");
//        return;
//    }

    server = serverSpec;
    i = 0;
    while (server != NULL)
    {
       readSchedules(&(server->files));  /// read schedules to static variable

       for (counter = 0; counter < SCHEDULES_NUMBER; counter++) 
       {
           if (schedules[counter].set)
           {
               showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "server  = %d, schedule type = %d HH = %d, MM = %d", i, counter, 
               getHour( schedules[counter].datetime.time), getMinute( schedules[counter].datetime.time));
			   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Current minimum is server = %d, type = %d " , schedule->group, schedule->type);

               if (schedule->existance == FALSE || 
            		   compareDateTime(&(schedules[counter].datetime), &(schedule->dateTime), TRUE) < 0)
               {
                   schedule->group = i;
                   schedule->existance = TRUE;
                   schedule->type = counter;
                   schedule->dateTime = schedules[counter].datetime;
				   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "less than !!!");
               }
           }
       }
       server = server->next;
       i++; 
    }

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*******MINIMUM IS **********");    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "server = %d, type = %d , HH = %d, MM = %d", schedule->group, schedule->type, 
    getHour(schedule->dateTime.time), getMinute(schedule->dateTime.time));
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "*****************");
}

/**
 * Reset reversal schedule.
 * @param   files [output]: file which have schedule
 * @see     showLog().
 * @see     readSchedules().
 * @see     setSchedule().
 * @return  None.
 */
void resetReversalSchedule(filesST* files)  
{
    scheduleST tempSchedule;        /* temp command structure */

    memset(&tempSchedule, 0, sizeof(scheduleST));

    readSchedules(files);
    tempSchedule.set = FALSE;
    tempSchedule.datetime.date = 0;
    tempSchedule.datetime.time = 0;
    tempSchedule.scheduleCount = 0;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ reset reversal");
    setSchedule(files, SCHEDULES_REVERSAL, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}


/* //mgh
void resetActiveTestSchedule(filesST* files)  
{
    scheduleST tempSchedule;        // temp command structure

    memset(&tempSchedule, 0, sizeof(scheduleST));

#ifndef MASKAN
    readSchedules(files);
    tempSchedule.set = FALSE;
    tempSchedule.datetime.date = 0;
    tempSchedule.datetime.time = 0;

    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "$$ reset activeTest");
    setSchedule(files, SCHEDULES_ACTIVE_TEST, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
#endif    
}
*/

/**
 * Reset settlement schedule.
 * @param   files [output]: file which have schedule
 * @see     setSchedule().
 * @see     showLog().
 * @return  None.
 */
void resetSettlementSchedule(filesST* files)  
{
    scheduleST tempSchedule;                      /* temp command structure */

    memset(&tempSchedule, 0, sizeof(scheduleST));
    
    readSchedules(files);
    tempSchedule.set = FALSE;
    tempSchedule.datetime.date = 0;
    tempSchedule.datetime.time = 0;
    tempSchedule.orginDatetime.date = 0;
    tempSchedule.orginDatetime.time = 0;
    tempSchedule.scheduleCount = 0;

    setSchedule(files, SCHEDULES_SETTLEMENT, setBits(1, 1, 0, 0, 1, 0, 0, 0), tempSchedule);
    showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "$$ reset settlement");
}

/**
 * Reset Log on schedule.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     showLog().
 * @see     setSchedule().
 * @return  None.
 */
void resetLogonSchedule(filesST* files)  
{
    scheduleST tempSchedule;        /* temp command structure */

    memset(&tempSchedule, 0, sizeof(scheduleST));
 
    readSchedules(files);
    //schedules[SCHEDULES_LOGON].set = FALSE;
    tempSchedule.set = FALSE;
    tempSchedule.datetime.date = 0;
    tempSchedule.datetime.time = 0;
    tempSchedule.scheduleCount = 0;

    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "$$ reset logon");
    setSchedule(files, SCHEDULES_LOGON, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
}

/**
 * Do schedules one by one.
 * @param   serverSpec [input]: the number of server
 * @param   currentSchedule [output]: the current schedule
 * @see     showLog().
 * @see     doConnect().
 * @see     disconnectAndClose().
 * @see     setReversalScheduleAfterUnsuccessReversal().
 * @see     resetReversalSchedule().
 * @see     setSettlementScheduleAfterUnsuccessSettlement().
 * @see     resetSettlementSchedule().
 * @see     setLogonScheduleForTomorrow().
 * @see     resetLogonSchedule().
 * @see     resetPeriodicTMSSchedule().
 * @see     resetTMSRunSchedule().
 * @see     resetTMSUpdateSchedule().
 * @see     resetTMSConfigSchedule().
 * @return  None.
 */
void doSchedules(serverSpecST* serverSpec, nextScheduleST* currentSchedule)
{
    int             i       = 0;
    serverSpecST*	server  = NULL;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Schedules for server %d, type %d", currentSchedule->group, currentSchedule->type);
    server = serverSpec;

    while (server != NULL)
    {
        if (currentSchedule->group == i)
        {
            switch (currentSchedule->type) 
            {
                case SCHEDULES_REVERSAL:
                	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ reversal schedule");
                    if (server->schedules[SERVICE_REVERSAL_INDEX])
                    {
                        if (doConnect(&(server->files)))
                        {
                            reversalTrans(&(server->files));                            
                            disconnectAndClose(0);
                        }
                        else
                            setReversalScheduleAfterUnsuccessReversal(&(server->files));
                    }
                    else
                    {
                        resetReversalSchedule(&(server->files));
                    }
                    break;
                case SCHEDULES_SETTLEMENT:
                	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ sett schedule");
                    
                    if (server->schedules[SERVICE_SETTLEMENT_INDEX])
                    {
                        if (doConnect(&(server->files)))
                        {
                            settlementTrans(&(server->files));
                            disconnectAndClose(0);
                        }
                        else
                            setSettlementScheduleAfterUnsuccessSettlement(&(server->files));
                    }
                    else
                    {
                        resetSettlementSchedule(&(server->files));
                    }
                    break;
/* //mgh
                case SCHEDULES_ACTIVE_TEST:
                    showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "doSchedules()", "SCHEDULES_ACTIVE_TEST");
                	showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "$$ activeTest schedule");
                    #ifndef MASKAN
                    if (server->schedules[SERVICE_ACTIVE_TEST_INDEX])
                    {
                        activeTestTrans(&(server->files));
                        disconnectAndClose(0);
                    }
                    else
                    {
                        resetActiveTestSchedule(&(server->files));
                    }
                    #endif
                    break;
*/
                case SCHEDULES_LOGON:
                    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "doSchedules()", "SCHEDULES_LOGON");
                	if (server->schedules[SERVICE_LOGON_INDEX] && server->isMenuVisible)
                    {
                        if (doConnect(&(server->files)))
                        {
                            //MRF
                            logonTrans(&(server->files));
                            disconnectAndClose(0);
                        }
                        else
                        {
//                          setLogonScheduleForTomorrow(&(server->files)); //mgh CM BY MRF
                            //MRF
                            setLogonScheduleAfterUnsuccessLogon(&(server->files));
                        }
                    }
                    else
                    {
                        resetLogonSchedule(&(server->files));
                    }
                    break;
                case SCHEDULES_PERIODIC_TMS: //MRF_TMS
                    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ periodic TMS schedule");
                    if (server->schedules[SERVICE_PERIODIC_TMS_INDEX])
                    {
                        //mgh_93
//						  showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "server= %d", server->files.id);
//                        resetTMSRunSchedule(&(server->files));
//                        setPeriodicTMSSchedule(&(server->files), getPeriodicTMSTime());
//                        periodicTMSRun(&(server->files));
                        
                        //MRF_TMS
                        TMSPeriodicTask(&(server->files));
                    }
                    else
                    {
                        resetPeriodicTMSSchedule(&(server->files));
                    }
                    break;
                case SCHEDULES_TMS:
//        --MRF_TMS            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ TMS schedule");
//                    if (server->schedules[SERVICE_TMS_INDEX])
//                    {
//                        //mgh_93 TMSRun(&(server->files), FALSE);
//                    }
//                    else
//                    {
//                        resetTMSRunSchedule(&(server->files));
//                    }
                    break;
                case SCHEDULES_TMS_UPDATE: 
//       --MRF_TMS             showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ TMS Update schedule");
//                    if (server->schedules[SERVICE_TMS_UPDATE_INDEX])
//                    {
//                        //mgh_93 TMSUpdate(server);
//                    }
//                    else
//                    {
//                        resetTMSUpdateSchedule(&(server->files));
//                    }
                    break;
                case SCHEDULES_TMS_CONFIG:
//      --MRF_TMS              showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "$$ TMS CONFIG schedule");
//                    if (server->schedules[SERVICE_TMS_CONFIG_INDEX])
//                    {        
//                        //mgh_93 TMSConfig(&(server->files));
//                    }
//                    else
//                    {
//                        resetTMSConfigSchedule(&(server->files));
//                    }
                    break;
                default:
                    break;
            }
        }
        server = server->next;
        i++; 
    }
}

/**
 * Read active test period.
 * @param   files [output]: file which have schedule
 * @param   activeTestPeriodSec [output]: active test period second
 * @param   testActivity [output]: activity test
 * @see     readFileInfo().
 * @see     showLog().
 * @see     addSystemErrorReport().
 * @see     updateFileInfo().
 * @return  None.
 */
//mgh 
//void readActiveTestPeriod(filesST* files, uint32* activeTestPeriodSec, uint8* testActivity) 
//{    
//    int16  retValue     = FAILURE;              // read file return value
//    uint32 len          = sizeof(uint32);       // file len
//    uint32 periodSec	= 0;                    // period ic second form
//
//#ifndef MASKAN    
//    retValue = readFileInfo(files->activeTestPeriodFile, &periodSec, &len);    
//    if (retValue == SUCCESS) 
//    {
//        if (periodSec > 0) 
//        { 
//            *activeTestPeriodSec = periodSec;
//            *testActivity = TRUE;
//        } 
//        else 
//        {
//            *activeTestPeriodSec = 0;
//            *testActivity = FALSE;
//        }
//    }
//    else
//    {
////        if (retValue != ERR_FILE_NOT_FOUND)
////        {
////        		showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "#err 8");
////        		addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
////        }
//
//        if (isInitialized(files))
//        {
//            periodSec = SCHEDULES_ACTIVE_TEST_TIME; // 5 days
//
//            showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "**UPDATE: activeTestPeriodFile");
//            retValue = updateFileInfo(files->activeTestPeriodFile, &periodSec, sizeof(uint32));            
//            if (retValue == SUCCESS) 
//            {
//                *activeTestPeriodSec = periodSec;
//                *testActivity = TRUE;
//            }
//            else 
//            {
//            	showLog(JUST_INGENICO, __FILE__, __LINE__, TRACE, "", "#err 9");
//                addSystemErrorReport(retValue, ERR_TYPE_FILE_SYSTEM);
//                *activeTestPeriodSec = 0;
//                *testActivity = FALSE;
//            }
//        }
//        else 
//        {
//            *activeTestPeriodSec = 0;
//            *testActivity = FALSE;
//        }
//    }
//#endif    
//}

/**
 * Set active test command after transaction.
 * @param   [output] files: file which have schedule
 * @see     secondToStandardTime().
 * @see     setNextDate().
 * @see     setNextTime().
 * @see     setSchedule().
 * @return  None.
 */
//void setActiveTestCommandAfterTransaction(filesST* files)
//{
//    scheduleST  schedule;
//    dateTimeST  nowDateTime				= getDateTime();
//    int         day                     = 0;
//    int         hour					= 0;
//    int         minute					= 0;
//    int         second					= 0;
//    uint32      activeTestPeriodSecond  = SCHEDULES_ACTIVE_TEST_TIME;//mgh 0;
//
//    memset(&schedule, 0, sizeof(scheduleST));
//
//#ifndef MASKAN    
//    readSchedules(files);
//
//    secondToStandardTime(activeTestPeriodSecond, &day, &hour, &minute, &second);
//    schedule.datetime = nowDateTime;
//    schedule.datetime.date = setNextDate(schedule.datetime.date, 0, 0, day);
//    schedule.datetime = setNextTime(&(schedule.datetime), hour, minute, second);
//
//    schedule.set = TRUE;
//    schedule.lastDatetime = nowDateTime;
//
//    setSchedule(files, SCHEDULES_ACTIVE_TEST, setBits(1, 1, 0, 1, 0, 0, 0, 0), schedule);
//#endif    
//}

/**
 * Set active test command after unsuccess send.
 * @param   files [output]: file which have schedule
 * @see     readSchedules().
 * @see     secondToStandardTime().
 * @see     setNextDate().
 * @see     setNextTime().
 * @see     setSchedule().
 * @return  None.
 */
//void setActiveTestCommandAfterUnsuccessSend(filesST* files)
//{
//    scheduleST  schedule;
//    dateTimeST  nowDateTime             = getDateTime();
//    uint32      activeTestPeriodSecond	= SCHEDULES_ACTIVE_TEST_TIME;//0;
//    int         day                     = 0;
//    int         hour					= 0;
//    int         minute					= 0;
//    int         second					= 0;
//
//    memset(&schedule, 0, sizeof(scheduleST));
//
//#ifndef MASKAN    
//    readSchedules(files);
//
//    secondToStandardTime(activeTestPeriodSecond, &day, &hour, &minute, &second);
//    schedule.datetime = nowDateTime;
//    schedule.datetime.date = setNextDate(schedule.datetime.date, 0, 0, day);
//    schedule.datetime = setNextTime(&(schedule.datetime), hour, minute, second);
//
//    schedule.set = TRUE;
//    schedule.lastDatetime = nowDateTime;
//    
//    setSchedule(files, SCHEDULES_ACTIVE_TEST, setBits(1, 1, 0, 0, 0, 0, 0, 0), schedule);
//#endif    
//}

//MRF
void setLogonScheduleAfterUnsuccessLogon(filesST* files)  
{
    scheduleST          tempSchedule;                     
    dateTimeST          nowDateTime;        
    uint8               nextTime = 0;
    
    memset(&tempSchedule, 0, sizeof(scheduleST));
    memset(&nowDateTime, 0, sizeof(dateTimeST));

    readSchedules(files);

    tempSchedule = readOneSchedule(files, SCHEDULES_LOGON);

    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "setLogonScheduleAfterUnsuccessLogon");

    nowDateTime = getDateTime();
    
    tempSchedule.scheduleCount = schedules[SCHEDULES_LOGON].scheduleCount;
    nextTime = (SCHEDULES_LOGON_TIME * power(2, tempSchedule.scheduleCount));

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
    tempSchedule.scheduleCount++;
    if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_LOGON_TIME))
    {
        resetLogonSchedule(files);
    }
    else
    {
        tempSchedule.set = TRUE;
        tempSchedule.datetime = setNextTime(&nowDateTime, 0, nextTime, 0); 

        setSchedule(files, SCHEDULES_LOGON, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
    }
}


//MRF_TMS
void setTMSScheduleAfterUnsuccessTMS(filesST* files)  
{
   scheduleST  tempSchedule;            /* temp command structure */
   dateTimeST  nowDateTime;             /* current date and time */
   uint8       nextTime = 0;

   memset(&tempSchedule, 0, sizeof(scheduleST));
   memset(&nowDateTime, 0, sizeof(dateTimeST));
    
   showLog(JUST_CASTLES, __FILE__, __LINE__, DEBUG, "", "setTMSScheduleAfterUnsuccessTMS");
   readSchedules(files);
   
   nowDateTime = getDateTime();
   
   tempSchedule.scheduleCount = schedules[SCHEDULES_PERIODIC_TMS].scheduleCount;
   
   showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "scheduleCount: %d", tempSchedule.scheduleCount);
   tempSchedule.scheduleCount++;
   if (tempSchedule.scheduleCount > getMaxScheduleCount(SCHEDULES_PERIODIC_TMS_TIME))
   {
       resetPeriodicTMSSchedule(files);
   }
   else
   {
       tempSchedule.set = TRUE;
       tempSchedule.datetime = setNextTime(&nowDateTime, 0, SCHEDULES_PERIODIC_TMS_TIME, 0); //AFTER 8 HOURE

       setSchedule(files, SCHEDULES_PERIODIC_TMS, setBits(1, 1, 0, 0, 0, 0, 0, 0), tempSchedule);
   }
}

