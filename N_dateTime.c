

/** sale kabiseh va gheire kabise (function) */
#define LEAPYEAR(year)                           (!((year) % 4) && (((year) % 100) || !((year) % 400)))
/** max of time in second */
#define TIME_MAX                                 2147483647L

/** structure of time */
typedef struct
{
  int sec;                           /*!< Seconds after the minute [0, 59] */
  int min;                           /*!< Minutes after the hour [0, 59] */
  int hour;                          /*!< Hours since midnight [0, 23] */
  int mday;                          /*!< Day of the month [1, 31] */
  int mon;                           /*!< Months since January [0, 11] */
  int year;                          /*!< Years since 1900 */
  int wday;                          /*!< Days since Sunday [0, 6] */
  int yday;                          /*!< Days since January 1 [0, 365] */
  int isdst;                         /*!< Daylight Saving Time flag */
}timeST;


const int daysPerMonths[2][12] = 
{
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

uint32 makeTime(timeST* time);

/**
 * Calculate difference between two date and time.
 * @param   beginDateTime [input]: begin date time
 * @param   endDateTime [input]: end date time
 * @see     compareDateTime().
 * @see     getYear().
 * @see     getMonth().
 * @see     getDay().
 * @see     getHour().
 * @see     getMinute().
 * @see     getSecond().
 * @return  difference in seconds.
 */
uint32 dateTimeDiffSecondes(dateTimeST* beginDateTime, dateTimeST* endDateTime) 
{
    uint32                 diffSec     = 0;
    uint16                 diffDay     = 0;
    int16                  beginYear   = 0; 
    int16                  endYear     = 0;
    int16                  year        = 0;
    int16                  beginMonth  = 0; 
    int16                  endMonth    = 0; 
    int16                  month       = 0; 
    int16                  beginDay    = 0;  
    int16                  endDay      = 0; 
    int16                  day         = 0; 
    dateTimeST* dateTime             = NULL;
    
    int cmpRes = compareDateTime(endDateTime, beginDateTime, TRUE);
    if (cmpRes == -1)
    {
        dateTime = endDateTime;
        endDateTime = beginDateTime;
        beginDateTime = dateTime;
    }
    else if (cmpRes == 0)
        return 0;

    if (beginDateTime->date != endDateTime->date)
    {        
		beginYear = getYear(beginDateTime->date);
        endYear = getYear(endDateTime->date);
        year = beginYear;
        for (year = beginYear; year <= endYear; year++)
        {
            beginMonth = (year == beginYear) ? getMonth(beginDateTime->date) : 1;
            endMonth = (year == endYear) ? getMonth(endDateTime->date) : 12;
            month = beginMonth;
            for (month = beginMonth; month <= endMonth; month++)
            {
                beginDay = ((year == beginYear) && (month == getMonth(beginDateTime->date))) ? 
                                 getDay(beginDateTime->date) + 1 : 1;
                
                if (beginDay > daysPerMonths[LEAPYEAR(year)][month - 1])
                    continue;
                
                endDay = ((year == endYear) && (month == getMonth(endDateTime->date))) ? 
                               getDay(endDateTime->date) - 1 : daysPerMonths[LEAPYEAR(year)][month - 1];
                
                if (endDay < 1)
                    break;
                
                day = beginDay;

                for (day = beginDay; day <= endDay; day++)
                    diffDay++;
            }
        }
        
        diffSec = diffDay * 24 * 60 * 60;
    }

    if (endDateTime->date != beginDateTime->date)
    {
        diffSec += (24 * 60 * 60) - ((getHour(beginDateTime->time) * 60 * 60) + 
                   (getMinute(beginDateTime->time) * 60) + getSecond(beginDateTime->time));
        
        diffSec += (getHour(endDateTime->time) * 60 * 60) + 
                   (getMinute(endDateTime->time) * 60) + getSecond(endDateTime->time);
    }
    else
    {
        diffSec += ((getHour(endDateTime->time) * 60 * 60) + 
                    (getMinute(endDateTime->time) * 60) + 
                    getSecond(endDateTime->time)) - 
                   ((getHour(beginDateTime->time) * 60 * 60) + 
                    (getMinute(beginDateTime->time) * 60) + 
                    getSecond(beginDateTime->time));
    }

    return diffSec;
}

/**
 * Make Time.
 * @param   time [input] :input date and time
 * @return  days since day 0 now in structured form.
 */
uint32 makeTime(timeST* time)
{
    int32 returnedDay   = 0;            /* means days since day 0 now */
    int32 offsetYear    = EPOCH_YR;    /* offset year */
    int   year          = 0;            /* now year */
    int   day           = 0;           /* days since beginning this year now */
    int   month         = 0;            /* months since beginning this year now */
    int   overflow      = 0;            /* over flow, not used effective */

    year = time->year + 2000;

    if (TIME_MAX / 365 < year - offsetYear) 
        overflow++;
    
    returnedDay = (year - offsetYear) * 365;
    
    if (TIME_MAX - returnedDay < (year - offsetYear) / 4 + 1) 
        overflow++;
    
    returnedDay += (year - offsetYear) / 4 + ((year % 4) && year % 4 < offsetYear % 4);
    returnedDay -= (year - offsetYear) / 100 + ((year % 100) && year % 100 < offsetYear % 100);
    returnedDay += (year - offsetYear) / 400 + ((year % 400) && year % 400 < offsetYear % 400);

    while (month < time->mon)
    {
        day += daysPerMonths[LEAPYEAR(year)][month];
        month++;
    } 
    
    day += (time->mday - 1);
    
    if (returnedDay + day < 0) 
        overflow++;
    
    returnedDay += day;

    return returnedDay;
}

/**
 * Get day number In Year.
 * @param   dateTime [input]: input date & time
 * @see     getYear().
 * @see     getMonth().
 * @see     getDay().
 * @see     getHour().
 * @see     getMinute().
 * @see     getSecond().
 * @return  makeTime(): days since day 0 now.
 */
uint32 getDayNumInYear(dateTimeST* dateTime) 
{
    timeST time;

    memset(&time, 0, sizeof(timeST));
    
    time.year      = getYear(dateTime->date) % 100;
    time.mon       = getMonth(dateTime->date) - 1;
    time.mday      = getDay(dateTime->date);
    time.hour      = getHour(dateTime->time);
    time.min       = getMinute(dateTime->time);
    time.sec       = getSecond(dateTime->time);
    time.isdst     = 1;
    
    return makeTime(&time);
}

/**
 * Convert gregorian date to jalali date.
 * @param   jalaliDate [input]: date in jalali form
 * @param   gregorianDate [output]: date in gregorian form
 * @see     getYear().
 * @see     getMonth().
 * @see     getDay().
 * @see     setDate().
 * @return  None.
 */
void gregorianToJalali(uint32* jalaliDate, uint32 gregorianDate)
{
    int   gerigorianYear            = 0;            /* year of gerigorian date */
    int   gerigorianMonth           = 0;            /* month of gerigorian date */
    int   gerigorianDay             = 0;            /* day of gerigorian date */
    int   jalaliYear                = 0;            /* year of jalali date */
    int   jalaliMonth               = 0;            /* month of jalali date */
    int   jalaliDay                 = 0;            /* day of jalali date */
    int32 gerigorianDaysNum         = 0;            /* days number gerigorian date */
    int32 jalaliDaysNum             = 0;            /* days number jalali date */
    int   jalali365YearsNum         = 0;            /* mumber of jalali years with 365 day */
    int   counter                   = 0;            /* loop counter */
    int   daysInGrgnMonths[12]      = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int   daysInJalaliMonths[12]    = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

    gerigorianYear = getYear(gregorianDate) - 1600;
    gerigorianMonth = getMonth(gregorianDate) - 1;
    gerigorianDay = getDay(gregorianDate) - 1;
    gerigorianDaysNum = 365 * gerigorianYear + (gerigorianYear + 3) / 4 - (gerigorianYear + 99) / 100 + (gerigorianYear + 399) / 400;
   
    for (counter=0; counter < gerigorianMonth; ++counter)
        gerigorianDaysNum += daysInGrgnMonths[counter];
   
    if (gerigorianMonth > 1 && ((gerigorianYear % 4 == 0 && gerigorianYear % 100 != 0) || (gerigorianYear % 400 == 0)))
        ++gerigorianDaysNum;

    gerigorianDaysNum += gerigorianDay;

    jalaliDaysNum = gerigorianDaysNum - 79;

    jalali365YearsNum = jalaliDaysNum / 12053;

    jalaliDaysNum %= 12053;

    jalaliYear = 979 + 33 * jalali365YearsNum + 4 * (jalaliDaysNum / 1461);

    jalaliDaysNum %= 1461;

    if (jalaliDaysNum >= 366) 
    {
        jalaliYear += (jalaliDaysNum - 1) / 365;
        jalaliDaysNum = (jalaliDaysNum - 1) % 365;
    }

    for (counter = 0; counter < 11 && jalaliDaysNum >= daysInJalaliMonths[counter]; ++counter)
        jalaliDaysNum -= daysInJalaliMonths[counter];
      
    jalaliMonth = counter + 1;

    jalaliDay = jalaliDaysNum + 1;

    *jalaliDate = setDate(jalaliYear, jalaliMonth, jalaliDay);
}

/**
 * Convert jalali date to gregorian date.
 * @param   gregorianDate [output]: date in gregorian form
 * @param   jalaliDate [input]: date in jalali form
 * @see     getYear().
 * @see     getMonth().
 * @see     getDay().
 * @see     setDate().
 * @return  None.
 */
void jalaliToGregorian(uint32* gregorianDate, uint32 jalaliDate)
{
    int       gerigorianYear            = 0;            /* year of gerigorian date */
    int       gerigorianMonth           = 0;            /* month of gerigorian date */
    int       gerigorianDay             = 0;            /* day of gerigorian date */
    int       jalaliYear                = 0;            /* year of jalali date */
    int       jalaliMonth               = 0;            /* month of jalali date */
    int       jalaliDay                 = 0;            /* day of jalali date */
    int32     gerigorianDaysNum         = 0;            /* days number gerigorian date */
    int32     jalaliDaysNum             = 0;            /* days number jalali date */
    int       counter                   = 0;            /* loop counter */
    int       leap                      = 1;
    int       daysInGrgnMonths[12]      = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int       daysInJalaliMonths[12]    = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
   
   jalaliYear = getYear(jalaliDate) - 979;
   jalaliMonth = getMonth(jalaliDate) - 1;
   jalaliDay = getDay(jalaliDate) - 1;
   jalaliDaysNum = 365 * jalaliYear + (jalaliYear / 33) * 8 + (jalaliYear % 33 + 3) / 4;
   
   for (counter = 0; counter < jalaliMonth; ++counter)
      jalaliDaysNum += daysInJalaliMonths[counter];

   jalaliDaysNum += jalaliDay;

   gerigorianDaysNum = jalaliDaysNum + 79;

   /* 146097 = 365 * 400 + 400 / 4 - 400 / 100 + 400 / 400 */
   gerigorianYear = 1600 + 400 * (gerigorianDaysNum / 146097); 

   gerigorianDaysNum = gerigorianDaysNum % 146097;

   if (gerigorianDaysNum >= 36525)       /* 36525 = 365*100 + 100/4 */
   {
      gerigorianDaysNum--;
      /* 36524 = 365 * 100 + 100 / 4 - 100 / 100 */
      gerigorianYear += 100 * (gerigorianDaysNum / 36524); 
      gerigorianDaysNum = gerigorianDaysNum % 36524;

      if (gerigorianDaysNum >= 365)
         gerigorianDaysNum++;
      else
         leap = 0;
   }

   /* 1461 = 365 * 4 + 4 / 4 */
   gerigorianYear += 4 * (gerigorianDaysNum / 1461); 

   gerigorianDaysNum %= 1461;

   if (gerigorianDaysNum >= 366) 
   {
      leap = 0;
      gerigorianDaysNum--;
      gerigorianYear += gerigorianDaysNum / 365;
      gerigorianDaysNum = gerigorianDaysNum % 365;
   }

   for (counter = 0; gerigorianDaysNum >= daysInGrgnMonths[counter] + (counter == 1 && leap); counter++)
      gerigorianDaysNum -= daysInGrgnMonths[counter] + (counter == 1 && leap);
   
   gerigorianMonth = counter + 1;
   
   gerigorianDay = gerigorianDaysNum + 1;

   *gregorianDate = setDate(gerigorianYear, gerigorianMonth, gerigorianDay);
   
}

/**
 * Set terminal date and time with log on transaction response.
 * @param   files [input]: files
 * @param   dateTime [input]: new Date and time
 * @param   dateTimeBoth [input]: date or time or both?
 * @param   jalali [output]: jalali or gregorian
 * @see     jalaliToGregorian().
 * @see     setPOSDateTime().
 * @see     addSystemErrorReport().
 * @return  TRUE or FALSE.
 */
uint8 setSystemDateTime(filesST* files, dateTimeST* dateTime, int dateTimeBoth, int jalali) 
{
    int         changed             = 0;                /* set if terminal date or time will be changed */
    uint32      gregorianDate       = 0;                /* date and time in gregorian form */
    int16       retValue            = 0;
    
    if (dateTimeBoth)
       changed = 1;

    if (dateTimeBoth != 1) 
    {
        if (jalali) 
        {            
            jalaliToGregorian(&gregorianDate ,dateTime->date);
            dateTime->date = gregorianDate;
        }
        
        if (getDateTime().date != dateTime->date)
            changed = 1;
    }

    if (changed) 
    {   
/*
        dateToSystemDateTime(dateTime->date, &year, &month, &day);
        timeToSystemDateTime(dateTime->time, &hour, &minute, &second);
		
        retValue = setPOSDateTime(year, month, day, hour, minute, second); 
*/
        retValue = setPOSDateTime(dateTime->date, dateTime->time); 
        if (retValue != SUCCESS)
        {
            addSystemErrorReport(retValue, ERR_TYPE_RTC);
            return FALSE;
        }
        else
            return TRUE;
    }
    return TRUE;
}

/**
 * Compare two date.
 * @param   first [input]: begin date
 * @param   second [input]: end date
 * @param   Time [input]: compare Time
 * @see     getHour().
 * @see     getMinute().
 * @return  0 if two dates are equal, 1 if first date is greater than second date
            and -1 if second date is greater than first date.
 */
int compareDates(dateTimeST* first, dateTimeST* second, uint8 Time) 
{
    int firstHhour          = 0;        /* first date hour */
    int firstMinute         = 0;        /* first date minute */
    int secondHour          = 0;        /* second date hour */
    int secondMinute        = 0;        /* second date minute */

    firstHhour = getHour(first->time);
    firstMinute = getMinute(first->time);
    secondHour = getHour(second->time);
    secondMinute = getMinute(second->time);
    
    if ((first->date == second->date) && (!Time || (firstHhour == secondHour && firstMinute == secondMinute)))  
        return 0;
    else if (first->date > second->date) 
        return 1;
    else if ((first->date == second->date) && (first->time > second->time)) 
        return 1;
    
    return -1;
}

/**
 * Convert date in uint32 format.
 * @param   inputDate [input]: input Date
 * @param   year [input]: year
 * @param   month [input]: month
 * @param   day [input]: day
 * @see     getYear().  
 * @see     getMonth().
 * @see     getDay().
 * @return  None
 */
void dateToSystemDateTime(uint32 inputDate, int32* year, int32* month, int32* day)
{
    *year   = getYear(inputDate);
    *month  = getMonth(inputDate);
    *day    = getDay(inputDate);
}

/**
 * Convert date time.
 * @see     clockToDate()
 * @return  date in uint32 format.
 */
uint32 systemDateTimeToDate(void) 
{
    uint32	 year      		= 0;
    uint32 	month     		= 0;
    uint32 	day       		= 0;
    uint8	dateStr[8 + 1]	= {0};
    
    clockToDate(&year, &month, &day);
    
#if	defined(ICT250) || defined(IWL220)//HNO_CHANGE
    sprintf(dateStr, "20%02d%02d%02d", (int)year, (int)month, (int)day);
    return strToInt(dateStr);
#else
    sprintf(dateStr, "%04ld%02ld%02ld", year, month, day);
    return SN_DATE(year, month, day);
#endif
}

/**
 * Get Year From date in uint32 format.
 * @param   inputDate [input]: date in uint32 format
 * @return  year.
 */
int getYear(uint32 inputDate) 
{
	//HNO_ADD
#if defined(IWL220) || defined(ICT250)
	return (inputDate / 10000);
#else
    return (int)(inputDate >> 16);
#endif
}

/**
 * Get Month From date in uint32 format.
 * @param   inputDate [input]: date in uint32 format
 * @return  Month.
 */
int getMonth(uint32 inputDate) 
{
	//HNO_ADD
#if defined(IWL220) || defined(ICT250)
	return ((inputDate % 10000) / 100);
#else
    return (int)((inputDate >> 8) & 0xFF);
#endif
}

/**
 * Get Day From date in uint32 format.
 * @param   inputDate [input]: date in uint32 format
 * @return  Day.
 */
int getDay(uint32 inputDate) 
{
	//HNO_ADD
#if defined(IWL220) || defined(ICT250)
	return ((inputDate % 10000) % 100);
#else
    return (int)(inputDate & 0xFF);
#endif
}

/**
 * Insert year, month & day in uint32 type variable.
 * @param   year [input]: year
 * @param   month [input]: month
 * @param   day [input]: day
 * @return  date in uint32 format.
 */
uint32 setDate(int year, int month, int day) 
{
#if defined(IWL220) || defined(ICT250)
	uint8 dateStr[8 + 1] = {0};

	sprintf(dateStr, "%04d%02d%02d", year, month, day);
	return strToInt(dateStr);
#else
    return SN_DATE(year, month, day);
#endif
}

/**
 * Convert date in uint32 format to string.
 * @param   inputDate [input]: date in uint32 format
 * @param   outputDate [output]: string
 * @return  None.
 */
void DateToStr(uint32 inputDate, uint8* outputDate) 
{
    sprintf(outputDate, "%04d%02d%02d", getYear(inputDate), getMonth(inputDate), getDay(inputDate));
}

/**
 * Convert date in string format to date in uint32 format.
 * @param   inputDate [input]: string
 * @return  date in uint32 format.
 */
uint32 strToDate(uint8* inputDate) 
{
    int       month       = 0;            /* month */
    int       day         = 0;            /* day */
    uint32    year        = 0;
    uint8 		dateStr[8 + 1] = {0};
    
    year     = ((inputDate[0] - 48) * 1000) + ((inputDate[1] - 48) * 100) + 
            ((inputDate[2] - 48) * 10) + (inputDate[3] - 48); 
    month    = ((inputDate[4] - 48) * 10) + (inputDate[5] - 48);
    day      = ((inputDate[6] - 48) * 10) + (inputDate[7] - 48);
    
#if defined(IWL220) || defined(ICT250)//HNO_CHANGE
	sprintf(dateStr, "%04ld%02d%02d", year, month, day);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "dateStr: %s", dateStr);
	return strToInt(dateStr);
#else
    return SN_DATE(year, month, day);
#endif
}


/**
 * Convert time in uint32 format.
 * @param   inputTime [input]: input Date
 * @param   hour [input]: hour
 * @param   minute [input]: minute
 * @param   second [input]: second
 * @see     getHour().  
 * @see     getMinute().
 * @see     getSecond().
 * @return  None.
 */
void timeToSystemDateTime(uint32 inputTime, uint32* hour, uint32* minute, uint32* second)    //CTOS_RTC * dateTime) 
{
    *hour   = getHour(inputTime); 
    *minute = getMinute(inputTime);
    *second = getSecond(inputTime);
}

/**
 * Convert date time.
 * @see     clockToTime().
 * @return  time in uint32 format.
 */
uint32 systemDateTimeToTime(void) 
{
    uint32 hour      = 0;
    uint32 minute    = 0;
    uint32 second    = 0;
    uint8	timeStr[6 + 1]	= {0};
    clockToTime(&hour, &minute, &second);

#if defined(ICT250) || defined(IWL220)//HNO_ADD
    sprintf(timeStr, "%02d%02d%02d", (int)hour, (int)minute, (int)second);
    return strToInt(timeStr);
#else
    return SN_TIME(hour, minute, second);
#endif
}

/**
 * Get hour From time in uint32 format.
 * @param   inputTime [input]: time in uint32 format
 * @return  hour.
 */
int getHour(uint32 inputTime) 
{
#if defined(ICT250) || defined(IWL220)//HNO_ADD
	return (inputTime / 10000);
#else
    return (inputTime >> 16);
#endif
}

/**
 * Get minute From time in uint32 format.
 * @param   inputTime [input]: time in uint32 format
 * @return  minute.
 */
int getMinute(uint32 inputTime) 
{
#if defined(ICT250) || defined(IWL220)
	return ((inputTime % 10000) / 100);//HNO_ADD
#else
    return ((inputTime >> 8) & 0xFF);
#endif
}

/**
 * Get second From time in uint32 format.
 * @param   inputTime [input]: time in uint32 format
 * @return  second.
 */
int getSecond(uint32 inputTime) 
{
#if defined(ICT250) || defined(IWL220)//HNO_ADD
	return ((inputTime % 10000) % 100);
#else
    return (inputTime & 0xFF);
#endif
}

/**
 * Insert hour, minute & second in uint32 type variable.
 * @param   hour [input]: hour
 * @param   minute [input]: minute
 * @param   second [input]: second
 * @return  time in uint32 format.
 */
uint32 setTime(int hour, int minute, int second) 
{
#if defined(ICT250) || defined(IWL220)//HNO_ADD
	uint8 timeStr[6 + 1] = {0};

	sprintf(timeStr, "%02d%02d%02d", hour, minute, second);
	return strToInt(timeStr);
#else
    return SN_TIME(hour, minute, second);
#endif
}

/**
 * Convert time in uint32 format to string.
 * @param   inputTime [input]: date in uint32 format
 * @param   outputTime [output]: string
 * @return  None.
 */
void timeToStr(uint32 inputTime, uint8* outputTime) 
{
#if defined(IWL220) || defined(ICT250)//HNO_ADD
	sprintf(outputTime, "%02d%02d%02d", getHour(inputTime), getMinute(inputTime), getSecond(inputTime));

#else
    int    counter   = 0;        /* loop counter */
    uint32 time      = 0;        /* temp time */
    
    for (counter = 1 ; counter < 4 ; counter++) 
    {
        time = inputTime;
        time = time << (counter * 8);
        time = time >> 24;
        outputTime[(counter-1) * 2] = (int)(time / 10) + 48; 
        outputTime[(counter-1) * 2 + 1] = (int)(time % 10) + 48;
    }
    outputTime[6] = 0;
#endif
}


/**
 * Convert time in string format to time in uint32 format.
 * @param   inputTime [input]: string
 * @return  time in uint32 format.
 */
uint32 strToTime(uint8* inputTime) 
{
    int hour         = 0;        /* hour */
    int minute       = 0;        /* minute */
    int second       = 0;        /* second */
    
    hour = ((inputTime[0] - 48) * 10) + (inputTime[1] - 48);
    minute = ((inputTime[2] - 48) * 10) + (inputTime[3] - 48);
    second = ((inputTime[4] - 48) * 10) + (inputTime[5] - 48);
    
#if defined(ICT250) || defined(IWL220)//HNO_ADD
    uint8 timeStr[6 + 1] = {0};
    sprintf(timeStr, "%02d%02d%02d", hour, minute, second);
    return strToInt(timeStr);
#else
    return SN_TIME(hour, minute, second);
#endif
}


/**
 * Convert date time.
 * @see     systemDateTimeToDate().  
 * @see     systemDateTimeToTime().
 * @return  structured date time(date & time have uint32 type).
 */
dateTimeST getDateTime(void)
{
    dateTimeST dateTime;              /* date and time */

    memset(&dateTime, 0, sizeof(dateTimeST));

    dateTime.date = systemDateTimeToDate();
    dateTime.time = systemDateTimeToTime();
    return dateTime;
}


/**
 * Set next date.
 * @param   date [input]: offset date
 * @param   incYear [input]: increment year
 * @param   incMonth [input]: increment month
 * @param   incDay [input]: increment day
 * @see     getYear().  
 * @see     getMonth().
 * @see     getDay().
 * @see     setDate().
 * @return  next date.
 */
uint32 setNextDate(uint32 date, int incYear, int incMonth, int incDay) 
{
    int    year             = 0;        /* offset year */
    int    month            = 0;        /* offset month */
    int    day              = 0;        /* offset day */
    uint32 nextDate         = 0;        /* next date */
    int    daysInGMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /** day number in gregorian months */
    
    year = getYear(date);
    month = getMonth(date);
    day = getDay(date);
    
    if (incDay > 0)
    {
        day = day + incDay;
        while (day > daysInGMonth[month - 1])
        {
            day = day - daysInGMonth[month - 1];
            month = month + 1;
            if (month > 12)
            {
                month = month - 12;
                year = year + 1;
            }
        }
    }
    
    if (incMonth > 0)
    {
        month = month + incMonth;
        while (month > 12)
        {
            month = month - 12;
            year = year + 1;
        }
    }
    
    if (incYear > 0)
        year = year + incYear;
    
    nextDate = setDate(year, month, day);
    
    return nextDate;
}

/**
 * Set next time.
 * @param   dateTime [input]: offset date and time
 * @param   incHour [input]: increment hour
 * @param   incMinute [input]: increment minute
 * @param   incSecond [input]: increment second
 * @see     getHour().  
 * @see     getMinute().
 * @see     getSecond().
 * @see     setNextDate().
 * @see     setTime().
 * @return  next date and time.
 */
dateTimeST setNextTime(dateTimeST* dateTime, int incHour, int incMinute, int incSecond) 
{
    int        hour             = 0;        /* offset hour */
    int        minute           = 0;        /* offset minute */
    int        second           = 0;        /* offset second */
    dateTimeST nextDateTime     = {0};      /* next date and time */
    
    hour = getHour(dateTime->time);
    minute = getMinute(dateTime->time);
    second = getSecond(dateTime->time);
    
    nextDateTime.date = dateTime->date;
    
    if (incSecond > 0)
    {
        second = second + incSecond;
        while (second >= 60)
        {
            second = second - 60;
            minute = minute + 1;
            if (minute >= 60)
            {
                minute = minute - 60;
                hour = hour + 1;
                if (hour >= 24) 
                {
                    hour = hour - 24;
                    nextDateTime.date = setNextDate(dateTime->date, 0, 0, 1);   
                }
            }
        }
    }
    
    if (incMinute > 0)
    {
        minute = minute + incMinute;
        while (minute >= 60)
        {
            minute = minute - 60;
            hour = hour + 1;
            if (hour >= 24)
            {
                hour = hour - 24;
                nextDateTime.date = setNextDate(dateTime->date, 0, 0, 1);     
            }
        }
    }
    
    if (incHour > 0)
    {
        hour = hour + incHour;
        while (hour >= 24)
        {
            hour = hour - 24;
            nextDateTime.date = setNextDate(dateTime->date, 0, 0, 1);     
        }       
    }
    
    nextDateTime.time = setTime(hour, minute, second);
    
    return nextDateTime;
}

/**
 * Convert second to standard time, day, hour, minute and second
 * @param   input [input]: total second
 * @param   day [input]: number of days
 * @param   hour [input]: number of hours
 * @param   minute [input]: number of minuted
 * @param   second [input]: number of seconds
 * @return  None.
 */
void secondToStandardTime(uint32 input, int* day, int* hour, int* minute, int* second) 
{
    uint32 tempInput = 0;                /* copy of input */
    
    tempInput = input % (24 * 60 * 60);
    *day = (input - tempInput) / (24 * 60 * 60);
    input = tempInput;
    tempInput = input % (60 * 60);
    *hour = (input - tempInput) / (60 * 60);
    input = tempInput;
    tempInput = input % (60);
    *minute = (input - tempInput) / (60);
    *second = tempInput;
}

/**
 * Compare Date and Time.
 * @param   first [input]: the first time
 * @param   second [input]: the second time
 * @param   Time [input]: time
 * @see     getHour().  
 * @see     getMinute().
 * @return  if first date and time are equal it returns 0 else if the first date or time are greater than second date and time it returns 1 else it returns -1.
 */
int compareDateTime(dateTimeST* first, dateTimeST* second, uint8 Time)  
{
    int firstHhour          = 0;        /* first date hour */
    int firstMinute         = 0;        /* first date minute */
    int secondHour          = 0;        /* second date hour */
    int secondMinute        = 0;        /* second date minute */

    firstHhour = getHour(first->time);
    firstMinute = getMinute(first->time);
    secondHour = getHour(second->time);
    secondMinute = getMinute(second->time);
    
    if ((first->date == second->date) && (!Time || (firstHhour == secondHour && firstMinute == secondMinute)))
    {
        return 0;
    }
    else if (first->date > second->date) 
    {
        return 1;
    }
    else if ((first->date == second->date) && (firstHhour > secondHour)) 
    {
        return 1;
    }
    else if ((first->date == second->date) && (firstHhour == secondHour) && (firstMinute > secondMinute)) 
    {
        return 1;
    }

    return -1;
}

/**
 * Get date(year,month,day) in string.
 * @param   dateTime [input]: offset date and time
 * @param   buffer [output]: buffer for store date
 * @see     getYear().  
 * @see     getMonth().
 * @see     getDay().
 * @return  None.
 */
void getDateStrYYMMDD(dateTimeST* dateTime, uint8* buffer)
{
    sprintf(buffer, "%02d%02d%02d", getYear(dateTime->date)%100, 
            getMonth(dateTime->date), getDay(dateTime->date));
}

/**
 * Get date(year,month) in string.
 * @param   dateTime [input]: offset date and time
 * @param   buffer [input]: buffer for store date
 * @see     getYear().  
 * @see     getMonth().
 * @return  None.
 */
void getDateStrYYMM(dateTimeST* dateTime, uint8* buffer)
{
    sprintf((char*)buffer, "[%02d][%02d]", 
            getYear(dateTime->date)%100,
            getMonth(dateTime->date));
}

/**
 * Get date(month,day) in string.
 * @param   dateTime [input]: offset date and time
 * @param   buffer [input]: buffer for store date
 * @see     getMonth().  
 * @see     getDay().
 * @return  None.
 */
void getDateStrMMDD(dateTimeST* dateTime, uint8* buffer)
{
    sprintf(buffer, "%02d%02d", 
            getMonth(dateTime->date), 
            getDay(dateTime->date));
}

/**
 * Get date(year,month,day,hour,minute,second) in string.
 * @param   dateTime [input]: offset date and time
 * @param   buffer [input]: buffer for store date
 * @see     getYear().  
 * @see     getMonth().
 * @see     getDay().  
 * @see     getHour().
 * @see     getMinute().  
 * @see     getSecond().
 * @return  None.
 */
void getDateTimeStrYYMMDDhhmmss(dateTimeST* dateTime, uint8* buffer)
{  
    sprintf(buffer, "%02d%02d%02d%02d%02d%02d", 
            getYear(dateTime->date)%100,
            getMonth(dateTime->date), 
            getDay(dateTime->date), 
            getHour(dateTime->time),
            getMinute(dateTime->time), 
            getSecond(dateTime->time));
}

/**
 * Get Greenwich date(year,month,day,hour,minute) in string.
 * @param   dateTime [input]: offset date and time
 * @param   buffer [input]: buffer for store date
 * @see     getYear().  
 * @see     getMonth().
 * @see     getDay().  
 * @see     getHour().
 * @see     getMinute().  
 * @return  None.
 */
void getGMTDateTimeStrYYMMDDhhmm(dateTimeST* dateTime, uint8* buffer)
{
    sprintf((char*)buffer, "%02d%02d%02d%02d%02d", 
            getYear(dateTime->date)%100,
            getMonth(dateTime->date), 
            getDay(dateTime->date), 
            getHour(dateTime->time),
            getMinute(dateTime->time));
}

/**
 * Get random time.
 * @param   startHour [input]: start hour
 * @param   endHour [input]: end hour
 * @param   hour [input]: hour
 * @param   minute [input]: minute  
 * @return  TRUE or FALSE.
 */
uint8 randomTime(int startHour, int endHour, int* hour, int* minute)
{
    int randomNum   = 0;
    int timeLimit   = 0;
    int difHour     = 0;
    int temp        = 0;
    
    if (startHour > 23 || startHour < 0 || endHour > 23 || endHour < 0 || startHour == endHour)
    {
        return FALSE;
    }
    
    if (endHour == 0)
    {
        endHour = 24;
    }
    
    if (endHour < startHour)
    {
        timeLimit = ((24 - startHour) + endHour) * 60;
    }
    else
    {
        timeLimit = (endHour - startHour) * 60;
    }
    
    randomNum = rand() % timeLimit; // random number in 0-timeLimit
    
    difHour = randomNum / 60;
    
    if (endHour < startHour)
    {
        temp = 24 - startHour;
        if (difHour < temp)
        {
            *hour = difHour + startHour;
        }
        else if (difHour == startHour)
        {
            *hour = 0;
        }
        else
        {
            *hour = difHour - temp;
        }
    }
    else
    {
        *hour = difHour + startHour;
    }
        
    *minute = randomNum % 60;
    
    return TRUE;
}


void setUserDateAndTime(void)
{
    uint32           timeStr        = 0;
    uint32           dateStr	    = 0;
    uint32           gregorianDate  = 0; 
    
    clearDisplay();
    getDateFromUser("æÑæÏ ÊÇÑíÎ:", FALSE, &dateStr);
   
    jalaliToGregorian(&gregorianDate ,dateStr);
    dateStr = gregorianDate;
    if (KBD_NEXT)
    {
        clearDisplay();
        getTimeFromUser("æÑæÏ ÓÇÚÊ:", FALSE, &timeStr);
    }
    
    setPOSDateTime(dateStr, timeStr);
}

void setDateTimeStrYYMMDDhhmmss(uint8* buffer, dateTimeST* dateTime)
{
	uint8 dateStr[8 + 1] = {0};
	uint8 timeStr[6 + 1] = {0};

	strncpy(dateStr, buffer, 8);
	strncpy(timeStr, &buffer[8], 6);

	dateTime->date = strToDate(dateStr);
	dateTime->time = strToTime(timeStr);
}

//MRF_NEW
uint8 calculateNextDate(void)
{
//    dateTimeST  currentDate;
//    uint32      nextDate  = 0;
//    
//    memset(&currentDate, 0, sizeof(dateTimeST));
//    
//    currentDate = getDateTime();
//    nextDate = setNextDate(currentDate.date, 0, 0, 1);
//    
//    if (updateFileInfo(NEXT_DATE_FILE, &nextDate, sizeof(uint32)) != SUCCESS)
//        return FALSE;
//    return TRUE;
}

//MRF_NEW
uint8 checkDate(void)
{
    dateTimeST  currentDate;
    uint32      baseDate   = 0;
    uint32      len       = sizeof(baseDate);
    
    memset(&currentDate, 0, sizeof(dateTimeST));

    currentDate = getDateTime();

    if (readFileInfo(POS_TIME_FILE, &baseDate, &len) != SUCCESS)
        return FALSE;
    
    if (currentDate.date > baseDate)
    {
        if (!PasswordGenerator())
            return FALSE;
        
        if (updateFileInfo(POS_TIME_FILE, &currentDate.date, sizeof(uint32)) != SUCCESS)
            return FALSE;
    }
    else if (currentDate.date < baseDate)
    {
        setPOSDateTime(baseDate, currentDate.time);
        return EXPIRE;
    }
    
    return TRUE; 
}

//MRF_OPTIMIZE
void setTimeForPrint(dateTimeST* dateTime, uint8* time)
{
    int32         hour      = 0;
    int32         minute    = 0;
    int32         second    = 0;
    
    hour = getHour(dateTime->time);
    minute = getMinute(dateTime->time);
    second = getSecond(dateTime->time);

#ifdef CASTLES_V5S 
    sprintf(time, "|%02d:%02d:%02d", second, minute, hour);
#else
    sprintf(time, "%2d:%02d:%02d", hour, minute,second);
#endif
}

