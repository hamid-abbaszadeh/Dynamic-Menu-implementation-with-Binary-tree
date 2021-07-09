

uint8* getUnicode(int index);

struct k_farsi
    {
        uint8   chr;
        uint8   to_prev;// : 1;
        uint8   to_next;// : 1;
        uint8   mid;
        int     last   ;// : 3;
        int     first  ;// : 3;
    };
struct k_farsi f_chr[128]={0,0,0,0,0};

/**
 * This function assign Farsi charachter in windows1256 unicode to TTF unicode.
 * and Structure filds is position of other type of char than main char in TTF Table.
 * first Farsi char in Widows1256 unicode table have 1 Position in ttf table.
 * @return None.
 */
void initTTFFont(void)
{   
    f_chr[ 1].chr = 122; 	
    f_chr[ 1].to_prev = 1;
    f_chr[ 1].to_next = 1;
    f_chr[ 1].last = -1;
    f_chr[ 1].first = 1;
    
    f_chr[ 2].chr = 140; 
       
    f_chr[ 13].chr = 126; 	
    f_chr[ 13].to_prev = 1;
    f_chr[ 13].to_next = 1;
    f_chr[ 13].last = -1;
    f_chr[ 13].first = 1;

    f_chr[ 14].chr = 129; 	
    f_chr[ 14].to_prev = 1;
    f_chr[ 14].first = -1;

    f_chr[ 16].chr = 132; 	
    f_chr[ 16].to_prev = 1;
    f_chr[ 16].to_next = 1;
    f_chr[ 16].last = -1;
    f_chr[ 16].first = 1;

    f_chr[ 24].chr = 96; 	
    f_chr[ 24].to_prev = 1;
    f_chr[ 24].to_next = 1;
    f_chr[ 24].last = -1;
    f_chr[ 24].first = 1;

    f_chr[ 42].chr = 112; 	
    f_chr[ 42].to_next = 1;
    f_chr[ 42].to_prev = 1;
    f_chr[ 42].last = -1;
    f_chr[ 42].first = 1;

    f_chr[ 63].chr = 14; 	

    f_chr[ 64].chr = 112; 	
    f_chr[ 64].to_next = 1;
    f_chr[ 64].to_prev = 1;
    f_chr[ 64].first = 1;
    f_chr[ 64].last = -1;

    f_chr[ 65].chr = 137; 	

    f_chr[ 66].chr = 17; 	
    
    //MRF_NEW3
    f_chr[ 67].chr = 145;
    f_chr[ 67].to_prev = 1;
    f_chr[ 67].first = -1;
    
    //MRF_NEW3
    f_chr[ 68].chr = 143;
    f_chr[ 68].to_prev = 1;
    f_chr[ 68].first = -1;

    f_chr[ 70].chr = 18; 	
    f_chr[ 70].to_prev = -1;
    f_chr[ 70].to_next = 1; //MRF_TTF
    f_chr[ 70].last = -1;//MRF_TTF
    f_chr[ 70].first = 1;//MRF_TTF

    f_chr[ 71].chr = 21; 	
    f_chr[ 71].to_prev = 1;
    f_chr[ 71].first = -1;

    f_chr[ 72].chr = 24; 	
    f_chr[ 72].to_prev = 1;
    f_chr[ 72].to_next = 1;
    f_chr[ 72].last = -1;
    f_chr[ 72].first = 1;

    f_chr[ 74].chr = 28; 	
    f_chr[ 74].to_prev = 1;
    f_chr[ 74].to_next = 1;
    f_chr[ 74].last = -1;
    f_chr[ 74].first = 1;

    f_chr[ 75].chr = 32; 	
    f_chr[ 75].to_prev = 1;
    f_chr[ 75].to_next = 1;
    f_chr[ 75].last = -1;
    f_chr[ 75].first = 1;

    f_chr[ 76].chr = 36; 	
    f_chr[ 76].to_prev = 1;
    f_chr[ 76].to_next = 1;
    f_chr[ 76].last = -1;
    f_chr[ 76].first = 1;

    f_chr[ 77].chr = 40; 	
    f_chr[ 77].to_prev = 1;
    f_chr[ 77].to_next = 1;
    f_chr[ 77].last = -1;
    f_chr[ 77].first = 1;

    f_chr[ 78].chr = 44; 	
    f_chr[ 78].to_prev = 1;
    f_chr[ 78].to_next = 1;
    f_chr[ 78].last = -1;
    f_chr[ 78].first = 1;

    f_chr[ 79].chr = 47; 	
    f_chr[ 79].to_prev = 1;
    f_chr[ 79].first = -1;

    f_chr[ 80].chr = 49; 	
    f_chr[ 80].to_prev = 1;
    f_chr[ 80].first = -1;

    f_chr[ 81].chr = 51; 	
    f_chr[ 81].to_prev = 1;
    f_chr[ 81].first = -1;
    
    f_chr[ 82].chr = 53; 	
    f_chr[ 82].to_prev = 1;
    f_chr[ 82].first = -1;

    f_chr[ 83].chr = 56; 	
    f_chr[ 83].to_prev = 1;
    f_chr[ 83].to_next = 1;
    f_chr[ 83].last = -1;
    f_chr[ 83].first = 1;

    f_chr[ 84].chr = 60; 	
    f_chr[ 84].to_prev = 1;
    f_chr[ 84].to_next = 1;
    f_chr[ 84].last = -1;
    f_chr[ 84].first = 1;

    f_chr[ 85].chr = 64; 	
    f_chr[ 85].to_prev = 1;
    f_chr[ 85].to_next = 1;
    f_chr[ 85].last = -1;
    f_chr[ 85].first = 1;

    f_chr[ 86].chr = 68; 	
    f_chr[ 86].to_prev = 1;
    f_chr[ 86].to_next = 1;
    f_chr[ 86].last = -1;
    f_chr[ 86].first = 1;

    f_chr[ 88].chr = 72; 	
    f_chr[ 88].to_prev = 1;
    f_chr[ 88].to_next = 1;
    f_chr[ 88].last = -1;
    f_chr[ 88].first = 1;

    f_chr[ 89].chr = 76; 	
    f_chr[ 89].to_prev = 1;
    f_chr[ 89].to_next = 1;
    f_chr[ 89].last = -1;
    f_chr[ 89].first = 1;

    f_chr[ 90].chr = 80; 	
    f_chr[ 90].to_prev = 1;
    f_chr[ 90].to_next = 1;
    f_chr[ 90].first = 1;
    f_chr[ 90].last = -1;

    f_chr[ 91].chr = 84; 	
    f_chr[ 91].to_prev = 1;
    f_chr[ 91].to_next = 1;
    f_chr[ 91].last = -1;
    f_chr[ 91].first = 1;
    

    f_chr[ 92].chr = 14; 	
    f_chr[ 92].to_prev = 1;
    f_chr[ 92].to_next = 1;

    f_chr[ 93].chr = 88; 	
    f_chr[ 93].to_prev = 1;
    f_chr[ 93].to_next = 1;
    f_chr[ 93].last = -1;
    f_chr[ 93].first = 1;

    f_chr[ 94].chr = 92; 	
    f_chr[ 94].to_prev = 1;
    f_chr[ 94].to_next = 1;
    f_chr[ 94].last = -1;
    f_chr[ 94].first = 1;

    f_chr[ 95].chr = 96;
    f_chr[ 95].to_prev = 1;
    f_chr[ 95].to_next = 1;
    f_chr[ 95].last = -1;
    f_chr[ 95].first = 1;

    f_chr[ 97].chr = 100; 	
    f_chr[ 97].to_prev = 1;
    f_chr[ 97].to_next = 1;
    f_chr[ 97].last = -1;
    f_chr[ 97].first = 1;

    f_chr[ 99].chr = 104; 	
    f_chr[ 99].to_prev = 1;
    f_chr[ 99].to_next = 1;
    f_chr[ 99].last = -1;
    f_chr[ 99].first = 1;

    f_chr[ 100].chr = 108; 	
    f_chr[ 100].to_prev = 1;
    f_chr[ 100].to_next = 1;
    f_chr[ 100].last = -1;
    f_chr[ 100].first = 1;

    f_chr[ 101].chr = 112; 	
    f_chr[ 101].to_next = 1;
    f_chr[ 101].to_prev = 1;
    f_chr[ 101].first = 1;
    f_chr[ 101].last = -1;

    f_chr[ 102].chr = 115; 	
    f_chr[ 102].to_prev = 1;
    f_chr[ 102].first = -1;

    f_chr[ 108].chr = 118; 	
    f_chr[ 108].to_prev = 1;
    f_chr[ 108].to_next = 1;
    f_chr[ 108].last = -1;
    f_chr[ 108].first = 1;

    f_chr[ 109].chr = 118; 	
    f_chr[ 109].to_prev = 1;
    f_chr[ 109].to_next = 1;
    f_chr[ 109].last = -1;
    f_chr[ 109].first = 1;
    
}



/**
 * Convert IP to string.
 * @param   IP [input]: IP in IP format
 * @param   strIP [output]: string format
 * @return  None.
 */
void ipToString(uint8* IP, uint8* strIP)
{
    int   ipPartNum             = 0;        /* IP part number, 0-3 */
    int   ipPartDigitNum        = 0;        /* IP part digits number, 0-2 */
    uint8 ipPatVal              = 0;        /* IP part value */
    uint8 quotient              = 0;        /* quotient of divison */
    uint8 divisionRes           = 0;        /* division result */
    int   strIpLen              = 0;        /* string IP lenght */
    int   isFirstInPart         = 1;        /* set if this digit is first in part */
    
    for (ipPartNum = 0; ipPartNum < 4; ipPartNum++) 
    {
        if (ipPartNum) 
            strIP[strIpLen++] = '.';
        
        ipPatVal = IP[ipPartNum];
        isFirstInPart = 1;
        quotient = 100;
        
        for (ipPartDigitNum = 0; ipPartDigitNum < 3; ipPartDigitNum++) 
        {
            divisionRes = ipPatVal / quotient;
            
            if (divisionRes != 0 || !isFirstInPart || ipPartDigitNum == 2) 
            {
                strIP[strIpLen++] = divisionRes + (uint8)'0';
                
                if (divisionRes != 0) 
                    isFirstInPart=0;
            }
            
            ipPatVal %= quotient;
            quotient /= 10;
        }
    }
    strIP[strIpLen] = 0;
}

/**
 * Convert string input to string with comma.
 * @param  input [input]:  input value without comma
 * @param  output [output]: output value with comma
 * @return FAILURE.
 */
void makeValueWithCommaStr(uint8* input, uint8* output)
{
    int counter		= 0;                            /* loop counter */
    int outputLen	= 0;                            /* output string lenght */
    int commaPart	= 0;                            /* comma index in output */
    int index		= 0;                            /* index in output */
    int inputLen	= strlen((const char*)input);   /* input value lenght */
    
    if (inputLen == 0)
    {
        output[0] = '0';
        return;
    }
    
    outputLen = (inputLen % 3 == 0) ? (inputLen + (inputLen / 3) - 1) : 
                                      (inputLen + (inputLen / 3));
    commaPart = inputLen % 3;
    if (commaPart == 0) 
        commaPart += 3;
    
    for (counter = 0, index = 0; index < outputLen, counter < inputLen; counter++, index++)
    {
        if (counter == commaPart)
        {
            output[index] = ',';
            index++;
            commaPart += 3;
        }
        
        output[index] =  input[counter];
    }
    
    output[outputLen] = 0;
}

/**
 * Convert input INT to string with comma.
 * @param   value [input]: input value without comma in uint32 form
 * @param   valueWithCommaStr [input]: output value with comma
 * @see     makeValueWithCommaStr().
 * @return  None.
 */
void makeValueWithCommaInt(uint32 value, uint8* valueWithCommaStr)
{
    uint8 valueStr[50] = {0};              /* input value in string form */

    sprintf(valueStr, "%lu", value);
    
    if (strlen((const char*)valueStr) == 0)
    {
        valueWithCommaStr[0] = '0';
        valueWithCommaStr[1] = 0;
    }
    else
        makeValueWithCommaStr(valueStr, valueWithCommaStr);
}

/**
 * Mask card ID for display on LCD.
 * @param   cardIdStr [input]: card Id
 * @param   result [output]: card Id masked for display on LCD
 * @return  None.
 */
void maskCardId(uint8* cardIdStr, uint8* result)
{
	//int   counter = 0;            /* loop counter */
	//uint8 cardID[17] = { 0 };

	//strncpy(cardID, cardIdStr, 16);
	//cardID[16] = 0;

	//for (counter = 6; counter < 12; counter++)//ABS
	//	cardID[counter] = '*';    //Star    

	//strcpy((char*)result, cardID);



	int   counter = 0;            /* loop counter *///ABS:CHANGE
	uint8 cardID[17] = { 0 };

	strncpy(cardID, cardIdStr, 6);
	strcat(cardID, "**");
	strncat(cardID, &cardIdStr[12], 4);
	cardID[12] = 0;

    strcpy((char*)result, cardID);
}


/**
 * Convert number string to int.
 * @param   inputStr [output]: input string
 * @param   size [output]: size of input string
 * @return  number.
 */
int zeroPadStrToInt(uint8* inputStr, int size)
{
    int   counter	= 0;                /* loop counter */
    int   value		= 0;                /* number, return value */
    int   sign		= 1;                /* number sign */
    uint8 nonZero	= FALSE;            /* set if escape all zeros */
    
    for (counter = 0; counter < size; counter++) 
    {
        if (inputStr[counter] == '-') 
        {
            if (!nonZero) 
            {
                nonZero = TRUE;
                sign = -1;
                continue;
            }
            else 
                return 0;
        }
        else if (inputStr[counter] > '0' && inputStr[counter] <='9') 
            nonZero = TRUE;
        
        if (inputStr[counter] >= '0' && inputStr[counter] <='9') 
            value = value * 10 + (inputStr[counter] - '0');
    }
    return (sign * value);
}


/**
 * Compact string, in input chars have 8 bit but in output chars will have 4 bit.
 * @param   input [input]: input string
 * @param   output [output]: output string
 * @param   inputLen [input]: input string lenght
 * @param   padElement [input]: pad element         
 * @param   padDir [input]: pad direction
 * @return  None.
 */
void asciiToBCD(uint8* input, uint8* output, int inputLen, uint8 padElement, uint8 padDir) 
{
    int		counter         = 0;	/* loop counter */
    int		index           = 0;
    uint8	secondMid       = 0;    /* second mid */ 
    uint8   firstMid        = 0;    /* first mid */
        
    for (counter = 0; counter < inputLen; counter++, index++) 
    {
        if ((input[counter] == '='))
            firstMid = 13;
        else if (input[counter] >= '0' && input[counter] <= '9')
            firstMid = input[counter] - '0';
        else if (input[counter] >= 'A' && input[counter] <= 'F')
            firstMid = input[counter] - 'A' + 10;
        else
            firstMid = input[counter] - 'a' + 10;
                                         
        if (inputLen % 2 != 0)
        {
            if (padDir == 0 && counter == 0) 
            {
                output[index] = padElement * 16 + firstMid;
                continue;
            }
            else if (padDir == 1 && counter == inputLen - 1) 
            {
                output[index] = firstMid * 16 + padElement;
                continue;
            }
        }
                 
        counter++;
        
        if ((input[counter] == '='))
            secondMid = 13;
        else if (input[counter] >= '0' && input[counter] <= '9')
            secondMid = input[counter] - '0';
        else if (input[counter] >= 'A' && input[counter] <= 'F')
            secondMid = input[counter] - 'A' + 10;
        else
            secondMid = input[counter] - 'a' + 10;
                                                    
        output[index] = firstMid * 16 + secondMid;
    }
}


/**
 * Convert HEX character to binary.
 * @param   input [input]: Hex character
 * @return  binary value or 0.
 */
uint8 hexCharToBin(uint8 input) 
{
    if (input >= '0' && input <= '9') 
        return input - '0';
    else if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    else if (input >= 'A' && input <= 'F') 
        return input - 'A' + 10;
    else 
        return 0;
}



/**
 * Convert bin character to HEX.
 * @param   input [input]: Binary character
 * @return  HEX value.
 */
uint8 binCharToHex(uint8 input) 
{
    if (input < 10)
        return input + '0';
    else
        return input - 10 + 'A';
}

/**
 * Convert String to UInt64.
 * @param   inputStr [input]: String
 * @param   size [input]: length of string 
 * @return  value. 
 */
uint32 StrToUInt64(uint8* inputStr, int size)
{
    int		counter = 0;            /* loop counter */
    uint32	value	= 0;            /* number, return value */
    
    for (counter = 0; counter < size; counter++) 
    {
        if (inputStr[counter] >= '0' && inputStr[counter] <= '9') 
            value = value * 10 + (inputStr[counter] - '0');
    }
    return value;
}


/**
 * Convert binary string to HEX string.
 * @param   binStr [input]: Input array in binary form
 * @param   hexStr [output]: Output array in hex form
 * @param   binLen [input]: Lenght of binary
 * @see     binCharToHex().
 * @return  None. 
 */
void binStrToHex(uint8* binStr, uint8* hexStr, int binLen) 
{
    uint8 HexChar = 0;               /* HEX character */
    
    while (binLen)
    {
        HexChar = binStr[--binLen];
        hexStr[2 * binLen + 1] = binCharToHex(HexChar % 16);
        hexStr[2 * binLen] = binCharToHex(HexChar / 16);
    }
    
}

/**
 * Check each bit set or not in uint8 type variable.
 * @param   index [input]: index in byte bits
 * @param   input [input]: input byte
 * @return  input in uint8 form.
 */
uint8 isBitSet(int index, uint8 input)
{
    input = input << (7 - index);
    input = input >> 7;
    return (uint8)input;
}

/**
 * Print data exist on comport in Hex form.
 * @param   ucDataToPrint [input]: data will print
 * @param   iLen [input]: length of data
 * @return  None.
 */
void comportHexShow(uint8* ucDataToPrint, uint16 iLen)
{
    int		i           = 0;
    int		k           = 0;
    char	szTemp[4]   = {0};
    char	szLine[51]  = {0};
    
    
    memset(szLine, 0x00, sizeof(szLine));
    
    for (i = 0; i < iLen; i++)
    {
        sprintf(szTemp, "%02X ", ucDataToPrint[i]);
        strcat(szLine, szTemp);
        k++;
        if (k == HEX_COUNT_SHOW)
        {
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", szLine);
            memset(szLine, 0x00, sizeof(szLine));
            k = 0;
			//ABS		delay(50, JUST_VERIFONE);
        }
    }
    if (k)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "%s", szLine);
    }
}

/**
 * Wrap farsi sentence that dependent max char in line and continuation of 
 * sentence placed in next line.
 * @param   str [input]: string
 * @param   separatedStr [output]: separated sentence
 * @param   maxInLine [input]: max char in line
 * @param   len [input]: length of string
 * @return  loop is number of separated sentence.
 */
int wordWrapFarsi(uint8* str, uint8 separatedStr[10][250], uint8 maxInLine,int len) 
{
    int     loop           = 0;
    uint8   cpyStr[250]    = {0};
    int     length         = 0;
    
//HNO_ADD
#if	defined(ICT250) || defined(IWL220)
	return wordWrapEnglish(str, separatedStr, maxInLine);
#else
    strcpy(cpyStr, str);
    length = strlen(cpyStr);
   
    while (length > maxInLine)
    {
        length -= maxInLine;  
        if ((cpyStr[length] == ' ') || (cpyStr[length - 1] == ' '))
        {
            strcpy(separatedStr[loop], &cpyStr[length]);
            loop++;
            if (cpyStr[length] == ' ')
                cpyStr[length] = '\0';
            else
                cpyStr[length - 1] = '\0';              
        }
        else 
        {
            while (TRUE)
            {
                length++;
                if (cpyStr[length] == '\0')
                { 
                    length -= maxInLine;
                    break;
                }
                if (cpyStr[length] == ' ')
                    break;
            }
            strcpy(separatedStr[loop], &cpyStr[length]);
            loop++;
            cpyStr[length] = '\0';

        }
    }
    strcpy(separatedStr[loop], &cpyStr[0]);
    return loop;
#endif
}

/**
 * Wrap English sentence that dependent max char in line and continuation of 
 * sentence placed in next line.
 * @param   str [input]: string
 * @param   separatedStr [output]: separated sentence
 * @param   maxInLine [input]: max char in line
 * @return  loop is number of separated sentence.
 */
 int wordWrapEnglish(uint8 str[250], uint8 separatedStr[10][250], uint8 maxInLine)  
{
    int     length          = 0;  
    int     currentIndex    = 0; 
    int     preIndex	    = 0;
    int     loop            = 0;
    uint8   cpyStr[250]     = {0};
    uint8 	fixedLen		= maxInLine;//HNO_ADD
    
    //HNO_ADD
    memset(separatedStr, 0, sizeof(separatedStr));

#if	defined(IWL220) || defined(ICT250)
    if (fixedLen == TRUE) //wordwrap for display
    	maxInLine = 27;
#endif
    strcpy(cpyStr, str);
    length = strlen(cpyStr);
    
    while ((length - currentIndex) > maxInLine)
    {
#if	defined(IWL220) || defined(ICT250) //HNO
			if (fixedLen != TRUE)
				maxInLine = setPrinterCharacterCount(&cpyStr[preIndex]); // add for Telium 2 POS
#else
        maxInLine--;//MRF_NEW4
#endif
        currentIndex = preIndex + maxInLine;
        
        if ((cpyStr[currentIndex] == ' ') || (cpyStr[currentIndex + 1] == ' '))
        {
            if (cpyStr[currentIndex] == ' ')
                cpyStr[currentIndex] = '\0';
            else
                cpyStr[++currentIndex] = '\0';
            
            strcpy(separatedStr[loop++], &cpyStr[preIndex]);
            preIndex = currentIndex + 1;
         }
        else
        {
            while (TRUE)
            {
                currentIndex--;
                if ((cpyStr[currentIndex] == '\0') || (currentIndex == 0))
                { 
                    currentIndex = preIndex + maxInLine;
                    break;
                }
                if (cpyStr[currentIndex] == ' ')
                {
                    break;
                }
            }
            if (cpyStr[currentIndex] == ' ')
            {
                cpyStr[currentIndex] = '\0';
                strcpy(separatedStr[loop++], &cpyStr[preIndex]);
                preIndex = currentIndex + 1;
            }
            else
            {
                memmove(cpyStr + currentIndex + 1, cpyStr + currentIndex, (length - currentIndex));
                cpyStr[currentIndex] = '\0';
                strcpy(separatedStr[loop++], &cpyStr[preIndex]);
                preIndex = currentIndex + 1;
            }
        }
    }

//    strcpy(separatedStr[loop], &cpyStr[preIndex]);
#if	defined(IWL220) || defined(ICT250)//HNO
    strcpy(separatedStr[loop], &cpyStr[preIndex]);
#else
    memcpy(separatedStr[loop], &cpyStr[preIndex],strlen(&cpyStr[preIndex]));
#endif

    return loop;
}

/**
 * Convert Long value to BCD form.
 * @param   src [input]: value will convert
 * @param   dst [output]: output
 * @param   len [input]: length of src
 * @return  None.
 */
void longToBCD(uint32 src, uint8* dst, int32 len)
{
	int32	i       = 0;
	int32	high    = 0;
	int32	low     = 0;

	for (i = len - 1; i >= 0; i--)
	{
		low  = (int)(src % 10);
		src /= 10;
		high = (int)(src % 10);
		src /= 10;
		dst[i] = (unsigned char)((high << 4) | low); // MRF??
	}
}

/**
 * Convert string to integer.
 * @param  inputStr [output]: string will convert
 * @see    removePadLeft().
 * @return Number or 0.
 */
int32 strToInt(uint8* inputStr) 
{
    uint8 buffer[50]	= {0};
    uint8 counter       = 0;                /* loop counter */
    int32 value         = 0;                /* number, return value */
    int8  sign          = 1;                /* number sign */
    
    strcpy(buffer, inputStr);
    removePadLeft(buffer, '0');
    

    if (buffer[0] == '-') 
    {
        sign = -1;
        counter++;
    }
    
    for (counter; counter < strlen(buffer); counter++) 
    {
        if (buffer[(int)counter] >= '0' && buffer[(int)counter] <= '9')//HNO_CHANGE casting
            value = value * 10 + (buffer[(int)counter] - '0');
        else
            return 0;
    }

    return (sign * value);
}


/**
 * Convert HEX string to binary string.
 * @param   hexStr [input]: input string in hex form
 * @param   binStr [output]: output strng in binary form
 * @param   hexLen [input]: lenght of hexstr
 * @see     hexCharToBin().
 * @return  None.
 */
void hex2bin(uint8* hexStr, uint8* binStr, int hexLen) 
{
    int counter = 0;                    /* loop counter */
    
    if (hexLen % 2 != 0) 
        return;
    
    for (counter = 0; counter < hexLen / 2; counter++) 
        binStr[counter] = hexCharToBin(hexStr[counter * 2]) * 
                          16 + hexCharToBin(hexStr[counter * 2 + 1]);
}


/**
 * Remove specified charcter from left side of string.
 * @param   buffer [input]: string
 * @param   buffer [output]: string of result
 * @param   pad [input]: one charchter that we want remove
 * @return  None.
 */
void removePadLeft(uint8* buffer, uint8 pad)
{
    int index		= 0;								/* index in buffer */
    int bufferLen	= strlen((const char*)buffer);      /* buffer lenght */
    
    while (buffer[index] == pad)
        index++;
    
    if (index == 0)
    	return;
    
    memmove(buffer, &buffer[index], bufferLen - index);
    buffer[bufferLen - index] = 0;
}


/**
 * Pad buffer string with '0'.
 * @param   buffer [input]: string
 * @param   buffer [output]: string
 * @param   finalLength [input]: length
 * @see     comportHexShow().    
 * @return  None.
 */
void padLeft(uint8* buffer, const uint8 finalLength)
{
    int 	bufferLen		= strlen((const char*)buffer);      /* buffer lenght */
    uint8	finalBuf[20]    = "00000000000000000000";
    
    finalBuf[finalLength] = 0;
    memmove(&finalBuf[finalLength - bufferLen], buffer, bufferLen);
    memcpy(buffer, finalBuf, finalLength);
    comportHexShow(buffer, finalLength);
}


/**
 * Remove specified charcter from right side of string.
 * @param   buffer [input]: string
 * @param   buffer [output]: string of result
 * @param   pad [input]: one charchter that we want remove
 * @return  None.
 */
void removePadRight(uint8* buffer, uint8 pad)
{
    int index = strlen((const char*)buffer) - 1;         /* index in buffer */
    
    while (buffer[index] == pad)  
        index--;
    buffer[index+1] = 0;
}

/**
 * Remove All of Pads. both rigth and left.
 * @param   buffer [input]: string
 * @param   buffer [output]: string of result
 * @param   pad [input]: one charchter that we want remove
 * @return  None.
 */
void removePad(uint8* buffer, uint8 pad)
{
    removePadLeft(buffer, pad);
    removePadRight(buffer, pad);
}

/**
 * For each bit position they will set.
 * @param    bit0 [input]: bit0
 * @param    bit1 [input]: bit1
 * @param    bit2 [input]: bit2
 * @param    bit3 [input]: bit3
 * @param    bit4 [input]: bit4
 * @param    bit5 [input]: bit5
 * @param    bit6 [input]: bit6
 * @param    bit7 [input]: bit7
 * @return   bitmap.
 */
uint8 setBits(uint8 bit0, uint8 bit1, uint8 bit2, uint8 bit3, uint8 bit4, 
              uint8 bit5, uint8 bit6, uint8 bit7) 
{
    uint8 bitmap = 0;                       /* result byte */
    
    if (bit7) 
        bitmap = bitmap + 128;
    
    if (bit6) 
        bitmap = bitmap + 64;
    
    if (bit5) 
        bitmap = bitmap + 32;
    
    if (bit4) 
        bitmap = bitmap + 16;
    
    if (bit3) 
        bitmap = bitmap + 8; 
    
    if (bit2) 
        bitmap = bitmap + 4;
    
    if (bit1) 
        bitmap = bitmap + 2; 
    
    if (bit0) 
        bitmap = bitmap + 1;

    return bitmap;
}


/**
 * Converts windows codepage 1256 to Iran System font codepage.
 * @param   strBuff [input]: input string to convert it cannot to exeed 256 bytes
 * @param   strBuff [output]: converted string
 * @return  length of converted string.
 */ 
uint16 convertCp1256ToIransystem(uint8* strBuff) //MRF_NEW9
{
    uint8   buff[256]   = {0};
    int     len         = strlen(strBuff);
    int     curpos      = 0;
    int     i           = 0;
    int     c           = 0;
    int     prev        = 0;
    int     prev1       = 0;
    int     k           = 0;

    struct k_farsi
    {
        uint8   chr;
        uint8   to_prev;// : 1;
        uint8   to_next;// : 1;
        int     last   ;// : 3;
        int     first  ;// : 3;
    }f_chr[128]={0,0,0,0,0};

    f_chr[ 1].chr = 149; 	
    f_chr[ 1].last = -1;
    f_chr[ 1].to_prev = 1;
    f_chr[ 1].to_next = 1;

    f_chr[ 13].chr = 157; 	
    f_chr[ 13].to_prev = 1;
    f_chr[ 13].to_next = 1;
    f_chr[ 13].last = -1;

    f_chr[ 14].chr = 166; 	
    f_chr[ 14].to_prev = 1;

    f_chr[ 16].chr = 240; 	
    f_chr[ 16].to_prev = 1;
    f_chr[ 16].to_next = 1;
    f_chr[ 16].last = -1;

    f_chr[ 24].chr = 238; 	
    f_chr[ 24].to_prev = 1;
    f_chr[ 24].to_next = 1;
    f_chr[ 24].last = -1;

    f_chr[ 42].chr = 249; 	
    f_chr[ 42].to_next = 1;
    f_chr[ 42].to_prev = 1;
    f_chr[ 42].first = 1;
    f_chr[ 42].last = -1;

    f_chr[ 63].chr = 140; 	

    f_chr[ 64].chr = 249; 	
    f_chr[ 64].to_next = 1;
    f_chr[ 64].to_prev = 1;
    f_chr[ 64].first = 1;
    f_chr[ 64].last = -1;

    f_chr[ 65].chr = 143; 	

    f_chr[ 66].chr = 141; 	

    f_chr[ 70].chr = 142; 	
    f_chr[ 70].to_next = 1;
    f_chr[ 70].to_prev = 1;
    f_chr[ 70].last = 1;

    f_chr[ 71].chr = 145; 	
    f_chr[ 71].to_prev = 1;
    f_chr[ 71].first = -1;

    f_chr[ 72].chr = 147; 	
    f_chr[ 72].to_prev = 1;
    f_chr[ 72].to_next = 1;
    f_chr[ 72].last = -1;

    f_chr[ 74].chr = 151; 	
    f_chr[ 74].to_prev = 1;
    f_chr[ 74].to_next = 1;
    f_chr[ 74].last = -1;

    f_chr[ 75].chr = 153; 	
    f_chr[ 75].to_prev = 1;
    f_chr[ 75].to_next = 1;
    f_chr[ 75].last = -1;

    f_chr[ 76].chr = 155; 	
    f_chr[ 76].to_prev = 1;
    f_chr[ 76].to_next = 1;
    f_chr[ 76].last = -1;

    f_chr[ 77].chr = 159; 	
    f_chr[ 77].to_prev = 1;
    f_chr[ 77].to_next = 1;
    f_chr[ 77].last = -1;

    f_chr[ 78].chr = 161; 	
    f_chr[ 78].to_prev = 1;
    f_chr[ 78].to_next = 1;
    f_chr[ 78].last = -1;

    f_chr[ 79].chr = 162; 	
    f_chr[ 79].to_prev = 1;

    f_chr[ 80].chr = 163; 	
    f_chr[ 80].to_prev = 1;

    f_chr[ 81].chr = 164; 	
    f_chr[ 81].to_prev = 1;

    f_chr[ 82].chr = 165; 	
    f_chr[ 82].to_prev = 1;

    f_chr[ 83].chr = 168; 	
    f_chr[ 83].to_prev = 1;
    f_chr[ 83].to_next = 1;
    f_chr[ 83].last = -1;

    f_chr[ 84].chr = 170; 	
    f_chr[ 84].to_prev = 1;
    f_chr[ 84].to_next = 1;
    f_chr[ 84].last = -1;

    f_chr[ 85].chr = 172; 	
    f_chr[ 85].to_prev = 1;
    f_chr[ 85].to_next = 1;
    f_chr[ 85].last = -1;

    f_chr[ 86].chr = 174; 	
    f_chr[ 86].to_prev = 1;
    f_chr[ 86].to_next = 1;
    f_chr[ 86].last = -1;

    f_chr[ 88].chr = 175; 	
    f_chr[ 88].to_prev = 1;
    f_chr[ 88].to_next = 1;

    f_chr[ 89].chr = 224; 	
    f_chr[ 89].to_prev = 1;
    f_chr[ 89].to_next = 1;

    f_chr[ 90].chr = 227; 	
    f_chr[ 90].to_prev = 1;
    f_chr[ 90].to_next = 1;
    f_chr[ 90].first = 1;
    f_chr[ 90].last = -1;

    f_chr[ 91].chr = 231; 	
    f_chr[ 91].to_prev = 1;
    f_chr[ 91].to_next = 1;
    f_chr[ 91].last = -1;
    f_chr[ 91].first = 1;

    f_chr[ 92].chr = 139; 	
    f_chr[ 92].to_prev = 1;
    f_chr[ 92].to_next = 1;

    f_chr[ 93].chr = 234; 	
    f_chr[ 93].to_prev = 1;
    f_chr[ 93].to_next = 1;
    f_chr[ 93].last = -1;

    f_chr[ 94].chr = 236; 	
    f_chr[ 94].to_prev = 1;
    f_chr[ 94].to_next = 1;
    f_chr[ 94].last = -1;

    f_chr[ 95].chr = 238; 	
    f_chr[ 95].to_prev = 1;
    f_chr[ 95].to_next = 1;
    f_chr[ 95].last = -1;

    f_chr[ 97].chr = 243; 	
    f_chr[ 97].to_prev = 1;
    f_chr[ 97].to_next = 1;
    f_chr[ 97].last = -2;

    f_chr[ 99].chr = 245; 	
    f_chr[ 99].to_prev = 1;
    f_chr[ 99].to_next = 1;
    f_chr[ 99].last = -1;

    f_chr[ 100].chr = 247; 	
    f_chr[ 100].to_prev = 1;
    f_chr[ 100].to_next = 1;
    f_chr[ 100].last = -1;

    f_chr[ 101].chr = 250; 	
    f_chr[ 101].to_next = 1;
    f_chr[ 101].to_prev = 1;
    f_chr[ 101].first = 1;
    f_chr[ 101].last = -1;

    f_chr[ 102].chr = 248; 	
    f_chr[ 102].to_prev = 1;

    f_chr[ 108].chr = 254; 	
    f_chr[ 108].to_prev = 1;
    f_chr[ 108].to_next = 1;
    f_chr[ 108].last = -2;

    f_chr[ 109].chr = 254; 	
    f_chr[ 109].to_prev = 1;
    f_chr[ 109].to_next = 1;
    f_chr[ 109].last = -2;

    for (curpos = 0, i = 0; i <= len; i++)
    {
		if ( strBuff[i] >= 128 && f_chr[strBuff[i] - 128].chr == 0 )
            continue; 
        prev1 = prev;
        prev = c;
        c = (strBuff[i] > 127) ? strBuff[i] - 128 : 0;
        if (!f_chr[c].to_prev)
        {
            if (f_chr[prev].to_next)
            {
	          	if (buff[curpos - 1] != f_chr[prev].chr && f_chr[prev].chr <= 0xE8) 
	            	buff[curpos - 1] = f_chr[prev].chr + f_chr[prev].last - f_chr[prev].first;
                else
                    if (f_chr[prev].chr == 0xFE && !f_chr[prev1].to_next) 
	              		buff[curpos - 1] = f_chr[prev].chr - 1;
                    else
	              		buff[curpos - 1] = f_chr[prev].chr + f_chr[prev].last;
            }
            buff[curpos] = (f_chr[c].chr) ? f_chr[c].chr : strBuff[i];
         }
         else
         {
            if (!f_chr[prev].to_next)
	          	buff[curpos]= (f_chr[c].chr) ? f_chr[c].chr + f_chr[c].first : strBuff[i];
            else 
                if (f_chr[prev].chr != 0xF3 || f_chr[c].chr != 0x91)
                    buff[curpos] = (f_chr[c].chr) ? f_chr[c].chr : strBuff[i];
                else
                {
                    buff[--curpos] = 0xF2; 
                }
         }
         curpos++;
    }
    
	curpos -= 2;
    for (i = 0, k = 0; i <= curpos; i++)
    {
            if ((buff[curpos-i] < 128 && buff[curpos-i] != ' ') || (buff[curpos-i] == ' ' && k > 0))
            {
                if (k == 0)
                    c = i;
                k++;
                if (buff[curpos - i] >= '0' && buff[curpos - i] <= '9')
                    buff[curpos - i] += 0x50;
            }
            else
            {
                if (k > 0)
                {
                    strncpy(strBuff + c, buff + curpos - i + 1, k);
                    k = 0;
                }
                strBuff[i] = buff[curpos - i];
            }
    }
    if (k > 0)
        strncpy(strBuff + c, buff + curpos - i + 1, k);
    
    strBuff[curpos + 1] = 0;	 
    return (curpos + 1);
}

 /** 
 * Convert windows codepage windows1256 to TTF font codepage.
 * @param   strBuff [input]: one string to convert it cannot to exceed 256 bytes
 * @param   strBuff [output]: string converted
 * @see     getUnicode().
 * @return  length of converted string.
 * @return  strBuff converted string.
 */ 
uint8* convertCp1256ToTTFFont(uint8* strBuff , uint8 support)
{
    uint8   buff[256]       = {0};
    int     len             = strlen(strBuff);
    int     curpos          = 0;
    int     i               = 0;
    int     j               = 0;
    int     c               = 0;
    int     prev            = 0;
    int     prev1           = 0;
    int     a               = 0;
    int     statecounter    = 0;
    int     lenStr          = 0;
    uint8   align           = 0;
    uint8   state           = LA_NONE;//HNO_CHANGE because in ingenico it crash
#ifndef VX520 //MRF_NEW9
    uint8   string[len*6];
    uint8   array[len][7];
#else
    uint8   string[30 * 6];//ABS:CHANGE:960807
	uint8   array[30][7];//ABS:CHANGE:960807
#endif
    
    struct state_st
    {
        int pos;
        enum languageEN language;
    }s[60];
    
	memset(string, 0, sizeof(string));//ABS:CHANGE:960807
    for (curpos = 0, i = 0; i <= len; i++)
    {
        if ( strBuff[i] >= 128 && f_chr[strBuff[i] - 128].chr == 0 )
            continue; 
        prev1 = prev;                          
        prev = c;
        c = (strBuff[i] > 127) ? strBuff[i] - 128 : 0;

        if (!f_chr[c].to_prev)
        {
            if (f_chr[prev].to_next)
            {
                state = LA_FA;
                if (buff[curpos - 1] != f_chr[prev].chr )
                {
                    buff[curpos - 1] = f_chr[prev].chr + f_chr[prev].last - f_chr[prev].first;
                    a = f_chr[prev].chr + f_chr[prev].last - f_chr[prev].first;
                    strcpy(&array[curpos-1][0], getUnicode(a));
                }
                else                
                {
                    buff[curpos - 1] = f_chr[prev].chr + f_chr[prev].last;
                    a = f_chr[prev].chr + f_chr[prev].last;
                    strcpy(&array[curpos-1][0], getUnicode(a));
                 }
            }

            buff[curpos] = (f_chr[c].chr) ? f_chr[c].chr : strBuff[i];

            if (f_chr[c].chr)
            {
                a = (f_chr[c].chr);
                state = LA_FA;
                strcpy(&array[curpos][0], getUnicode(a));
            }
            else
            {
                 if (buff[curpos] >= '0' && buff[curpos] <= '9') 
                 {
                     strcpy(&array[curpos][0], getUnicode(buff[curpos]-48 + 1)); 
                     state = LA_NUM;
                 }
                 else if (buff[curpos ]== ',')
                 {
                     strcpy(&array[curpos][0],& buff[curpos]); 
                     state = LA_NUM;
                 }
                 else if (buff[curpos ]== '#')
                 {
                     strcpy(&array[curpos][0],& buff[curpos]); 
                     state = LA_FA;
                 }
                 else 
                 {
                    strcpy(&array[curpos][0], &buff[curpos]);  
                     state = LA_EN;
                 }
                 
                 if ((s[statecounter].language != LA_FA) && (array[curpos][0] == NULL))
                 {
                     statecounter++;
                     state = LA_EMPTY;
                     s[statecounter].pos = curpos;
                 }     
            }       
         }
         else
         {
            if (!f_chr[prev].to_next)
            {
                buff[curpos] = (f_chr[c].chr) ? f_chr[c].chr + f_chr[c].first : strBuff[i];

                if (f_chr[c].chr)
                {
                    a = f_chr[c].chr + f_chr[c].first;
                    state = LA_FA;
                }
                else  
                {
                    a = strBuff[i];
                    state = LA_EN;
                    if ((s[statecounter].language != LA_FA) && (array[curpos][0] == NULL))
                    {
                         statecounter++;
                         state = LA_EMPTY;
                         s[statecounter].pos = curpos;
                    }
                }

                strcpy(&array[curpos][0],getUnicode(a));         
            }
            else if ((f_chr[prev].chr != 100 || f_chr[c].chr != 21) || (support == FALSE)) //MRF_TTF
            {
                 buff[curpos] = (f_chr[c].chr) ? f_chr[c].chr : strBuff[i];

                 if (f_chr[c].chr)
                 {
                     a = f_chr[c].chr;
                     state = LA_FA;
                 }
                 else
                 {
                     a = strBuff[i];
                     state = LA_EN;
                     if ((s[statecounter].language != LA_FA) && (array[curpos][0] == NULL))
                     {
                         statecounter++;
                         state = LA_EMPTY;
                         s[statecounter].pos = curpos;
                     }
                 }
                  strcpy(&array[curpos][0], getUnicode(a));
            }  
            else
            {  
                if ((a == 100) && (support)) //MRF_TTF
                    strcpy(array[--curpos], "\uFEFC");
                else
                   strcpy(array[--curpos], "\uFEFB");
            }
         }

        if(curpos == 0)
        {
            s[statecounter].language = state;
            s[statecounter].pos = curpos;
        }
         else if ((state != s[statecounter].language) && (state != LA_EMPTY))
        {
            statecounter++;
            s[statecounter].language = state;
            s[statecounter].pos = curpos;
        }

        curpos++;
    
    }
    
    for (i = 0; i < statecounter ; i++)
    {
       if (s[i].language == LA_FA)
       {    
             align = RIGHT;
             break;
       }
       else
             align = LEFT;
    }

    if (align == LEFT)   
    {
        for (i = 0 ; i < statecounter; i++)
        { 
                lenStr = s[i+1].pos-s[i].pos;

           if (s[i].language == LA_FA)
           {     
               for ( j = lenStr-1; j >= 0; j--)    
               {
                   if(!string)
                   {  
                       strcpy(string,array[s[i].pos+j]);
                   }
                   else
                   {
                       strcat(string,array[s[i].pos+j]);
                   }
               }
           }
           else if ((s[i].language == LA_EN) || (s[i].language == LA_NUM))
           {
                for ( j = 0; j < lenStr; j++)
                {
                    if(!string)
                    {  
                     strcpy(string,array[s[i].pos+j]);
                    }
                    else
                    {
                        strcat(string,array[s[i].pos+j]);
                    }
                }
           }
       }
    }
    
    if (align == RIGHT)   
    {
        for (i = statecounter-1 ; i >=0 ; i--)
        { 
            lenStr = s[i+1].pos-s[i].pos;

            if (s[i].language == LA_FA)
            {  
                for ( j = lenStr-1; j >= 0; j--)    
                {
                    if(!string)
                    {
                        strcpy(string,array[s[i].pos+j]);
                    }
                    else
                    {
                        strcat(string,array[s[i].pos+j]);
                    }
                 }
            }
            else if ((s[i].language == LA_EN) || (s[i].language == LA_NUM))
            {
                 for ( j = 0; j < lenStr; j++)
                {
                   if(!string)
                   {
                       strcpy(string,array[s[i].pos+j]);
                   }
                   else
                   {
                       strcat(string,array[s[i].pos+j]);
                   }
                }
             }
        }
     }
    
    strcpy(strBuff,string);
    return (string);  
}

//Added by MRF
/**
 * This Function Get index of char in TTF table and return Unicode of that.
 * @param   index [input]: index
 * @return  unicode of index.
 */
uint8* getUnicode(int index)
{
    switch(index)
    {
        case 1:
            return "\u06F0";
            
        case 2:
            return "\u06F1";
            
        case 3:
            return "\u06F2";
            
        case 4:
            return "\u06F3";
            
        case 5:
            return "\u06F4";
            
        case 6:
            return "\u06F5";
            
        case 7:
            return "\u06F6";
            
        case 8:
            return "\u06F7";
        
        case 9:
            return "\u06F8";
            
        case 10:
            return "\u06F9";
            
        case 11:
            return "\u066A";
            
        case 12:
            return "\u066B";
            
        case 13:
            return "\u060C";
            
        case 14:
            return "\u061F";
            
        case 15:
            return "\uFD3E";
            
        case 16:
            return "\uFD3F";
            
        case 17:
            return "\u0622";
            
        case 18:
            return "\uFE8C";    //"\uFE8B"; MRF_TTF
            
        case 19:
            return "\uFE8B";    //"\uFE8C"; MRF_TTF
        
        case 20:
            return "\uFE8D";
            
        case 21:
            return "\uFE8E";
            
        case 22:
            return "\u0628";
            
        case 23:
            return "\uFE90";
            
        case 24:
            return "\uFE92";   
            
        case 25:
            return "\uFE91";
            
        case 26:
            return "\u062A";
            
        case 27:
            return "\uFE96";
            
        case 28:
            return "\uFE98";
            
        case 29:
            return "\uFE97";
            
        case 30:
            return "\u062B";
            
        case 31:
            return "\uFE9A";
        
        case 32:
            return "\uFE9C";
            
        case 33:
            return "\uFE9B";
            
        case 34:
            return "\u062C";
            
        case 35:
            return "\uFE9E";
            
        case 36:
            return "\uFEA0";
            
        case 37:
            return "\uFE9F";
            
        case 38:
            return "\u062D";
            
        case 39:
            return "\uFEA2";
            
        case 40:
            return "\uFEA4";
            
        case 41:
            return "\uFEA3";
            
        case 42:
            return "\u062E";
        
        case 43:
            return "\uFEA6";
            
        case 44:
            return "\uFEA8";
            
        case 45:
            return "\uFEA7";
            
        case 46:
            return "\u062F";
            
        case 47:
            return "\uFEAA";
            
        case 48:
            return "\u0630";
            
        case 49:
            return "\uFEAC";
            
        case 50:
            return "\u0631";
            
        case 51:
            return "\uFEAE";
            
        case 52:
            return "\u0632";
            
        case 53:
            return "\uFEB0";
        
        case 54:
            return "\u0633";
            
        case 55:
            return "\uFEB2";
            
        case 56:
            return "\uFEB4";
            
        case 57:
            return "\uFEB3";
            
        case 58:
            return "\u0634";
            
        case 59:
            return "\uFEB6";
            
        case 60:
            return "\uFEB8";
            
        case 61:
            return "\uFEB7";
            
        case 62:
            return "\u0635";
            
        case 63:
            return "\uFEBA";
            
        case 64:
            return "\uFEBC";
        
        case 65:
            return "\uFEBB";
            
        case 66:
            return "\u0636";
            
        case 67:
            return "\uFEBE";
            
        case 68:
            return "\uFEC0";
            
        case 69:
            return "\uFEBF";
            
        case 70:
            return "\u0637";
            
        case 71:
            return "\uFEC2";
            
        case 72:
            return "\uFEC4";
            
        case 73:
            return "\uFEC3";
            
        case 74:
            return "\u0638";
            
        case 75:
            return "\uFEC6";
        
        case 76:
            return "\uFEC8";
            
        case 77:
            return "\uFEC7";
            
        case 78:
            return "\u0639";

       case 79:
            return "\uFECA";
            
        case 80:
            return "\uFECC";
            
        case 81:
            return "\uFECB";
            
        case 82:
            return "\u063A";
            
        case 83:
            return "\uFECE";
            
        case 84:
            return "\uFED0";
            
        case 85:
            return "\uFECF";
            
        case 86:
            return "\u0641";
            
        case 87:
            return "\uFED2";
        
        case 88:
            return "\uFED4";
            
        case 89:
            return "\uFED3";
            
        case 90:
            return "\u0642";
            
        case 91:
            return "\uFED6";
            
        case 92:
            return "\uFED8";
            
        case 93:
            return "\uFED7";
            
        case 94:
            return "\u06A9";//"\uFB8E";//"\uFED9"; //"\u0643";
            
        case 95:
            return  "\uFB8F";//"\uFEDA";
            
        case 96:
            return "\uFEDC";
            
        case 97:
            return "\uFEDB";
            
        case 98:
            return "\u0644";
        
        case 99:
            return "\uFEDE";
            
        case 100:
            return "\uFEE0";
            
        case 101:
            return "\uFEDF";
            
        case 102:
            return "\u0645";
            
        case 103:
            return "\uFEE2";
            
        case 104:
            return "\uFEE4";
            
        case 105:
            return "\uFEE3";
            
        case 106:
            return "\u0646";
            
        case 107:
            return "\uFEE6";
            
        case 108:
            return "\uFEE8";
            
        case 109:
            return "\uFEE7";
        
        case 110:
            return "\u0647";
            
        case 111:
            return "\uFEEA";
            
        case 112:
//            return "\uFBAB"; //MRF_TTF
            return "\uFEEC";
            
        case 113:
//            return "\u06BE"; //MRF_TTF
            return "\uFEEB";
            
        case 114:
            return "\u0648";
            
        case 115:
            return "\uFEEE";
            
        case 116:
            return "\u0649";
            
        case 117:
            return "\uFEF0";
            
        case 118:
            return "\uFBFF";
            
        case 119:
            return "\uFBFE";
            
        case 120:
            return "\u067E";
        
        case 121:
            return "\uFB57";
            
        case 122:
            return "\uFB59";
            
        case 123:
            return "\uFB58";
            
        case 124:
            return "\u0686";
            
        case 125:
            return "\uFB7B";
            
        case 126:
            return "\uFB7D";
            
        case 127:
            return "\uFB7C";
            
        case 128:
            return "\u0698";
            
        case 129:
            return "\uFB8B";
            
        case 130:
            return "\u06AF";
            
        case 131:
            return "\uFB93";
        
        case 132:
            return "\uFB95";
            
        case 133:
            return "\uFB94";
            
        case 134:
            return "\uFEFB";
            
        case 135:
            return "\uFEFC";
            
        case 136:
            return "\uFDF2";
            
        case 137:
            return "\uFE80";
            
        case 138:
            return "\u066D";
            
        case 139:
            return "\u061B";
         
        case 140:
            return "\u201A";
            
//        case 141: //MRF_TTF MRF_NEW2 MRF_DEBUG
//            return "#";
            
        case 142:                   //MRF_NEW3
            return "\uFE85"; 
            
        case 143:
            return "\uFE86";        //MRF_NEW3
            
        case 144:
            return "\uFE83";        //MRF_NEW3
            
        case 145:
            return "\uFE84";        //MRF_NEW3
         
        default:
//            displayMessageBox("ÑÏÇÒÔ ãÊä Çã˜Çä ÐíÑ äãí ÈÇÔÏ",MSG_ERROR);
            break;
    }
}

//MRF
/**
 * If Defined Terminal is Castles V5 We use TTF Font Else use Iransystem Unicode. 
 * @param   strBuff [input]: Is one string will be convert
 * @return  None.
 */
uint8* convertFont(uint8* strBuff)
{
#ifdef  CASTLES_V5S
    convertCp1256ToTTFFont(strBuff, TRUE); //MRF_TTF TRUE FOR 
#else
        convertCp1256ToIransystem(strBuff);
#endif
} 

/**
 * Convert one String from Windows1256 codepage to UTF8.
 * @param   OutBuffer [output]: String converted
 * @param   inBuffer [input]: String will be convert
 * @return  length of string converted.
 */
uint16 convertCp1256ToUtf8(uint8* OutBuffer, uint8* inBuffer)
{
    uint16 len = 0;
    uint16  i  = 0;
    typedef struct
    {    
        uint8   cp1256Char;
        uint8   utf8[10];
    }convertTableST;

    convertTableST cp1265Table[128] = 
    {
        {128	,{226,     130,    172}},
        {129	,{217,     190        }},            
        {130	,{226,     128,    154}},
        {131	,{198,     146        }}, 
        {132	,{226,     128,    158}},
        {133	,{226,     128,    166}},
        {134	,{226,     128,    160}},
        {135	,{226,     128,    161}},
        {136	,{203,     134        }},
        {137	,{226,     128,    176}},
        {138	,{217,     185        }},
        {139	,{226,     128,    185}},
        {140	,{197,     146        }},
        {141	,{218,     134        }},
        {142	,{218,     152        }},
        {143	,{218,     136        }},
        {144	,{218,     175        }},
        {145	,{226,     128,    152}},
        {146	,{226,     128,    153}},
        {147	,{226,     128,    156}},
        {148	,{226,     128,    157}},
        {149	,{226,     128,    162}},
        {150	,{226,     128,    147}},
        {151	,{226,     128,    148}},
        {152	,{218,     169        }},
        {153	,{226,     132,    162}},
        {154	,{218,     145        }},
        {155	,{226,     128,    186}},
        {156	,{197,     147        }},
        {157	,{226,     128,    140}},
        {158	,{226,     128,    141}},
        {159	,{218,     186        }},
        {160	,{194,     160        }},
        {161	,{216,     140        }}, 
        {162	,{194,     162        }},
        {163	,{194,     163        }}, 
        {164	,{194,     164        }},
        {165	,{194,     165        }},
        {166	,{194,     166        }},
        {167	,{194,     167        }},
        {168	,{194,     168        }},
        {169	,{194,     169        }},
        {170	,{218,     190        }},
        {171	,{194,     171        }},
        {172	,{194,     172        }},
        {173	,{194,     173        }},
        {174	,{194,     174        }},
        {175	,{194,     175        }},
        {176	,{194,     176        }},
        {177	,{194,     177        }},
        {178	,{194,     178        }},
        {179	,{194,     179        }},
        {180	,{194,     180        }},
        {181	,{194,     181        }},
        {182	,{194,     182        }},
        {183	,{194,     183        }},
        {184	,{194,     184        }},
        {185	,{194,     185        }},
        {186	,{216,     155        }},
        {187	,{194,     187        }},
        {188	,{194,     188        }},
        {189	,{194,     189        }},
        {190	,{194,     190        }},
        {191	,{216,     159        }},
        {192	,{219,     129        }},
        {193	,{216,     161        }}, 
        {194	,{216,     162        }},
        {195	,{216,     163        }}, 
        {196	,{216,     164        }},
        {197	,{216,     165        }},
        {198	,{216,     166        }},
        {199	,{216,     167        }},
        {200	,{216,     168        }},
        {201	,{216,     169        }},
        {202	,{216,     170        }},
        {203	,{216,     171        }},
        {204	,{216,     172        }},
        {205	,{216,     173        }},
        {206	,{216,     174        }},
        {207	,{216,     175        }},
        {208	,{216,     176        }},
        {209	,{216,     177        }},
        {210	,{216,     178        }},
        {211	,{216,     179        }},
        {212	,{216,     180        }},
        {213	,{216,     181        }},
        {214	,{216,     182        }},
        {215	,{195,     151        }},
        {216	,{216,     183        }},
        {217	,{216,     184        }},
        {218	,{216,     185        }},
        {219	,{216,     186        }},
        {220	,{217,     128        }},
        {221	,{217,     129        }},
        {222	,{217,     130        }},
        {223	,{217,     131        }},
        {224	,{195,     160        }},
        {225	,{217,     132        }}, 
        {226	,{195,     162        }},
        {227	,{217,     133        }}, 
        {228	,{217,     134        }},
        {229	,{217,     135        }},
        {230	,{217,     136        }},
        {231	,{195,     167        }},
        {232	,{195,     168        }},
        {233	,{195,     169        }},
        {234	,{195,     170        }},
        {235	,{195,     171        }},
        {236	,{217,     137        }},
        {237	,{217,     138        }},
        {238	,{195,     174        }},
        {239	,{195,     175        }},
        {240	,{217,     139        }},
        {241	,{217,     140        }},
        {242	,{217,     141        }},
        {243	,{217,     142        }},
        {244	,{195,     180        }},
        {245	,{217,     143        }},
        {246	,{217,     144        }},
        {247	,{195,     183        }},
        {248	,{217,     145        }},
        {249	,{195,     185        }},
        {250	,{217,     146        }},
        {251	,{195,     187        }},
        {252	,{195,     188        }},
        {253	,{226,     128,    142}},
        {254	,{226,     128,    143}},
        {255	,{219,     146        }}  
    };

    memset(OutBuffer, 0, strlen(inBuffer));
    for (i = 0; i < strlen(inBuffer); i++)
    {
        if (inBuffer[i] >= 128 /*&& inBuffer[i] <= 255 --> check for larger than uint8*/)
        {
            strncat(&OutBuffer[len], cp1265Table[inBuffer[i] - 128].utf8, strlen(cp1265Table[inBuffer[i] - 128].utf8));
            len += strlen(cp1265Table[inBuffer[i] - 128].utf8);
        }
        else
        {
            OutBuffer[len] = inBuffer[i];
            len++;
        }   
    }
    return len;
}

/**
 * X to the power of Y.
 * @param   x [input]: Is base number
 * @param   y [input]: Power number
 * @return  X to be Powered.
 */
int power(int x, int y) 
{
	if (y == 0) 
        return 1;
	if (y < 0) 
        return 0;
    
	return x * power(x, y - 1);
}

/**
 * One string will be reverse.
 * @param   str [input]: String
 * @return  None.
 */
void reverseString(uint8* str)
{
    int     i       = 0;
    int     j       = 0;
    uint8   temp    = 0;
    
    for (i = 0, j = strlen(str) - 1; i <= j; i++, j--)
	{
		temp    = str[i];
		str[i]  = str[j];
		str[j]  = temp;
	}
}

/**
 * Get two string include number and sum values them.
 * @param   X [input]: first string include number
 * @param   Y [input]: second string include number
 * @param   result [output]: result string from sum of x and y
 * @see     reverseString().
 * @return  None.
 */
void sumStringNumbers(uint8* X, uint8* Y, uint8* result)
{
    int     maxLen                  = 0;
    int     i                       = 0;
    int     R                       = 0;
    int     tempResult[15 + 1]      = {0};
    uint8   reverseX[15 + 1]        = {0};
    uint8   reverseY[15 + 1]        = {0};
    uint8   tempX[2]                = {0};
    uint8   tempY[2]                = {0};
        
    maxLen = strlen(X) > strlen(Y) ? strlen(X) : strlen(Y);
  
    strcpy(reverseX, X);
    reverseString(reverseX);
    strcpy(reverseY, Y);
    reverseString(reverseY);
    
    for (i = 0; i < maxLen; i++)
    {
        tempX[0] = reverseX[i];
        tempY[0] = reverseY[i];
        tempResult[i] = atoi(tempX) + atoi(tempY) + R;

        if (tempResult[i] > 9) 
            R = 1;                                      /* We keep the surplus in mind :)*/
        else
            R = 0;
        tempResult[i] %= 10;                            /* if the number is bigger than 10 we keep only the last digit */
        result[i] = (char)(tempResult[i] + '0');
    }

    if (R != 0) 
    {
        tempResult[maxLen] = R;
        result[maxLen] = (char)(tempResult[maxLen] + '0');
    }
    
    reverseString(result);
}

//HNO
uint16 convertCp1256ToUnicde(uint8* OutBuffer, uint8* inBuffer)
{
	convertCp1256ToIransystem(inBuffer);
	return convertIransystemToUnicde(OutBuffer, inBuffer);

}


/**
 * Compare two string. which one is equal or less or elder.
 * @param   X  [input]: first string
 * @param   Y [input]: second string
 * @return  -1 : if X < Y.
 *           1 : if X > Y.
 *           0 : if X = Y.
 */
int compareStringNumbers(uint8* X, uint8* Y)
{
    int i = 0;

    if (strlen(X) < strlen(Y)) 
        return -1;          // if Y has more digits than X then it is bigger than X
    else if (strlen(X) > strlen(Y)) 
        return 1; 
    else
    {

        for (i = 0; i < strlen(Y); i++)
        {
            if (Y[i] > X[i]) 
                return -1;
            else if (Y[i] < X[i]) 
                return 1;
        }
        return 0;
    }
}

/**
 * Get two string include number and sub values them.
 * We assume that X is bigger than Y.
 * @param   X [input]: first string include number
 * @param   X [output]: result of sub
 * @param   Y [input]: second string include number
 * @return  None.
 */
void sub(uint8* X, uint8* Y)
{
	/* We assume that X is bigger than Y */
	int i   = 0;
    int j   = 0;
    int len = 0;

	for (i = 0; i < strlen(Y); i++)
    {
        if (atoi(&Y[i]) > atoi(&X[i]))
		{
            j = i; 
            while (X[++j] == 0);
            
            X[j]--; 
            j--;
            
            while (j > i)
            {
                X[j] = 9;
                j--;
            }
            X[i] += 10;   
            X[i] -= Y[i]; 
		}
        else
		{
            X[i] -= Y[i]; 
		} 
    }

    len = strlen(X);
	while ((X[len] == 0) && (len > 0))
        len--;
}

/**
 * Get two string include number and sub values them.
 * @param   X [input]: first string include number
 * @param   Y [input]: second string include number
 * @param   result [output]: result string from sub of x and y
 * @see     compareStringNumbers().
 * @see     sub().
 * @return  None.
 */
void SubStringNumbers(uint8* X, uint8* Y, uint8* result)
{ 
    int a = compareStringNumbers(X, Y);
    int i = 0;
    
    if ((a == 1) || (a == 0)) /// if X >= Y 
    {
        for (i = 0; i <= strlen(X); i++) 
            result[i] = X[i]; 
        sub(result, Y);
    }
    else /// if X < Y 
    { 
        for (i = 0; i <= strlen(Y); i++) 
            result[i] = Y[i]; 
        sub(result, X);
    }
}

/**
 * Get one string and to Upper charachters.
 * @param    str [input]: string will upper
 * @param    str [output]: string to upper  
 * @return   None.
 */
void strToUpper(uint8* str)
{
	if (str != NULL)
	{
		while (*str++ != ASCII_NULL)
		{
			*str = (uint8)toupper((int)*str);
		}
	}
}

//HNO
int16 convertCp1256ToLCD(uint8* strBuff)
{
	uint8 outBuff[100] = {0};

#if defined(IWL220) || defined(ICT250)
	convertCp1256ToUnicde(outBuff, strBuff);
	memcpy(strBuff, outBuff, 100);
#else
	return convertCp1256ToIransystem(strBuff);
#endif
}
/**
 * Get one string and to Lower charachters.
 * @param    str [input]: string will Lower
 * @param    str [output]: string to Lower  
 * @return   None.
 */
void strToLower(uint8* str)
{
	if (str != NULL)
	{
		while (*str++ != ASCII_NULL)
		{
			*str = (uint8)tolower((int)*str);
		}
	}
}

//MRF_NEW
void maskMobileNumbers(uint8* mobileNo, uint8* result)
{
    int   counter       = 0;            /* loop counter */
    uint8 phoneNo[17]	= {0};          /* card ID */

    strncpy(phoneNo, mobileNo, 11);
    phoneNo[11] = 0;
    
    for (counter = 3; counter < 7; counter++) 
        phoneNo[counter] = '*';    //Star    

    strcpy((char*)result, phoneNo);
}

//MRF_TTF
void reversPartString(uint8* string)
{
    uint8   sign[50]= {0};
    uint8   start[50]   = {0};
    uint8   end[50]     = {0};
    uint8   temp[100]   = {0};
    int     len         = 0;
    int     lenSign     = 0;
    int     i           = 0;
    int     j           = 0;
    int     n           = 0;
    int     lenStart    = 0;
    int     lenEnd      = 0;
    int     endOfStart  = 0;
    int     firstOfEnd  = 0;
    
    len = strlen(string);
    
    for (i = 0; i <= len; i++)
    {
        if (string[i] == '*' )
        {
            sign[j] = '*';
            j++;
            n = i;
        }
        else if (string[i] == '-')
        {
            sign[j] = '-';
            j++;
            n = i;
        }
    }
    
    lenSign = strlen(sign);
    endOfStart = n - lenSign;
    
    strncpy(start, string, endOfStart + 1);
    lenStart = strlen(start);
    firstOfEnd = lenStart + lenSign;
    lenEnd = len - (lenStart + lenSign);
    strncpy(end, &string[firstOfEnd], lenEnd);
    memset(temp, 0, sizeof(uint8));
    
    strcpy(temp, end);
    strcat(temp, sign);
    strcat(temp, start);
    strcpy(string, temp);
}

//HNO
uint16 convertIransystemToUnicde(uint8* OutBuffer, uint8* inBuffer)
{
//	showLog(JUST_INGENICO, __FILE__, __LINE__, DEBUG, "","first of convert");
    uint16 len = 0;
    int	  i  = 0;
    typedef struct
    {
        uint8   cp1256Char;
        uint8   utf8[10];
    }convertTableST;
    convertTableST cp1265Table[128] =
    {
        {128	,"\x06\x60"},
        {129	,"\x06\x61"},
        {130	,"\x06\x62"},
        {131	,"\x06\x63"},
        {132	,"\x06\x64"},
        {133	,"\x06\x65"},
        {134	,"\x06\x66"},
        {135	,"\x06\x67"},
        {136	,"\x06\x68"},
        {137	,"\x06\x69"},
        {138	,"\x06\x0c"},
        {139	,"\x06\x40"},
        {140	,"\x06\x1f"},
        {141	,"\xfe\x81"},
        {142	,"\xfe\x8b"},
        {143	,"\x06\x21"},
        {144	,"\xfe\x8d"},
        {145	,"\xfe\x8e"},
        {146	,"\xfe\x8f"},
        {147	,"\xfe\x91"},
        {148	,"\xfb\x56"},
        {149	,"\xfb\x58"},
        {150	,"\xfe\x95"},
        {151	,"\xfe\x97"},
        {152	,"\xfe\x99"},
        {153	,"\xfe\x9B"},
        {154	,"\xfe\x9D"},
        {155	,"\xfe\x9F"},
        {156	,"\xfB\x7A"},
        {157	,"\xfb\x7c"},
        {158	,"\xfe\xA1"},
        {159	,"\xfe\xA3"},
        {160	,"\xfe\xA5"},
        {161	,"\xfe\xA7"},
        {162	,"\x06\x2f"},
        {163	,"\x06\x30"},
        {164	,"\x06\x31"},
        {165	,"\x06\x32"},
        {166	,"\x06\x98"},
        {167	,"\xfe\xb1"},
        {168	,"\xfe\xb3"},
        {169	,"\xfe\xb5"},
        {170	,"\xfe\xb7"},
        {171	,"\xfe\xb9"},
        {172	,"\xfe\xbb"},
        {173	,"\xfe\xbD"},
        {174	,"\xfe\xbF"},
        {175	,"\x06\x37"},
        {176	,"\x25\x91"},
        {177	,"\x25\x92"},
        {178	,"\x25\x93"},
        {179	,"\x25\x02"},
        {180	,"\x25\x24"},
        {181	,"\x25\x61"},
        {182	,"\x25\x62"},
        {183	,"\x25\x56"},
        {184	,"\x25\x55"},
        {185	,"\x25\x63"},
        {186	,"\x25\x51"},
        {187	,"\x25\x57"},
        {188	,"\x25\x5d"},
        {189	,"\x25\x5c"},
        {190	,"\x25\x5b"},
        {191	,"\x25\x10"},
        {192	,"\x25\x14"},
        {193	,"\x25\x34"},
        {194	,"\x25\x2c"},
        {195	,"\x25\x1c"},
        {196	,"\x25\x00"},
        {197	,"\x25\x3c"},
        {198	,"\x25\x5e"},
        {199	,"\x25\x5f"},
        {200	,"\x25\x5a"},
        {201	,"\x25\x54"},
        {202	,"\x25\x69"},
        {203	,"\x25\x66"},
        {204	,"\x25\x60"},
        {205	,"\x25\x50"},
        {206	,"\x25\x6c"},
        {207	,"\x25\x67"},
        {208	,"\x25\x68"},
        {209	,"\x25\x64"},
        {210	,"\x25\x65"},
        {211	,"\x25\x59"},
        {212	,"\x25\x58"},
        {213	,"\x25\x52"},
        {214	,"\x25\x53"},
        {215	,"\x25\x6B"},
        {216	,"\x25\x6A"},
        {217	,"\x25\x18"},
        {218	,"\x25\x0c"},
        {219	,"\x25\x88"},
        {220	,"\x25\x84"},
        {221	,"\x25\x8c"},
        {222	,"\x25\x90"},
        {223	,"\x25\x80"},
        {224	,"\x06\x38"},
        {225	,"\xfe\xc9"},
        {226	,"\xfe\xca"},
        {227	,"\xfe\xcc"},
        {228	,"\xfe\xcb"},
        {229	,"\xfe\xcd"},
        {230	,"\xfe\xce"},
        {231	,"\xfe\xd0"},
        {232	,"\xfe\xcf"},
        {233	,"\xfe\xd1"},
        {234	,"\xfe\xd3"},
        {235	,"\xfe\xd5"},
        {236	,"\xfe\xd7"},
        {237	,"\xfb\x8e"},
        {238	,"\xfb\x90"},
        {239	,"\xfb\x92"},
        {240	,"\xfb\x94"},
        {241	,"\xfe\xDD"},
        {242	,"\xfe\xfb"},
        {243	,"\xfe\xdf"},
        {244	,"\xfe\xe1"},
        {245	,"\xfe\xe3"},
        {246	,"\xfe\xe5"},
        {247	,"\xfe\xe7"},
        {248	,"\x06\x48"},
        {249	,"\xfe\xe9"},
        {250	,"\xfe\xec"},
        {251	,"\xfe\xeb"},
        {252	,"\xfe\xf0"},
        {253	,"\xfe\xf1"},
        {254	,"\xfe\xf3"},
        {255	,"\x00\xA0"}
    };

    memset(OutBuffer, 0, strlen(inBuffer));
    for (i = strlen(inBuffer) - 1; i >= 0 ; i--)
    {
//    	showLog(JUST_INGENICO, __FILE__, __LINE__, DEBUG, "","inBuffer[i]: %d", inBuffer[i]);
    	if (inBuffer[i] >= 128 /*&& inBuffer[i] <= 255 --> check for larger than uint8*/)
        {
//            strncat(&OutBuffer[len], cp1265Table[inBuffer[i] - 128].utf8, strlen(cp1265Table[inBuffer[i] - 128].utf8));
//    		strcat(OutBuffer, cp1265Table[inBuffer[i] - 128].utf8);
    		memcpy(&OutBuffer[len], cp1265Table[inBuffer[i] - 128].utf8, 2);
            len += 2;//strlen(cp1265Table[inBuffer[i] - 128].utf8);
        }
        else
        {
        	OutBuffer[len] = '\x00';
        	switch(inBuffer[i])
        	{
				case 0:
					OutBuffer[len + 1] = '\x00';
					break;
				case 1:
					OutBuffer[len + 1] = '\x01';
					break;
				case 2:
					OutBuffer[len + 1] = '\x02';
					break;
				case 3:
					OutBuffer[len + 1] = '\x03';
					break;
				case 4:
					OutBuffer[len + 1] = '\x04';
					break;
				case 5:
					OutBuffer[len + 1] = '\x05';
					break;
				case 6:
					OutBuffer[len + 1] = '\x06';
					break;
				case 7:
					OutBuffer[len + 1] = '\x07';
					break;
				case 8:
					OutBuffer[len + 1] = '\x08';
					break;
				case 9:
					OutBuffer[len + 1] = '\x09';
					break;
				case 10:
					OutBuffer[len + 1] = '\x0a';
					break;
				case 11:
					OutBuffer[len + 1] = '\x0b';
					break;
				case 12:
					OutBuffer[len + 1] = '\x0c';
					break;
				case 13:
					OutBuffer[len + 1] = '\x0d';
					break;
				case 14:
					OutBuffer[len + 1] = '\x0e';
					break;
				case 15:
					OutBuffer[len + 1] = '\x0f';
					break;
				case 16:
					OutBuffer[len + 1] = '\x10';
					break;
				case 17:
					OutBuffer[len + 1] = '\x11';
					break;
				case 18:
					OutBuffer[len + 1] = '\x12';
					break;
				case 19:
					OutBuffer[len + 1] = '\x13';
					break;
				case 20:
					OutBuffer[len + 1] = '\x14';
					break;
				case 21:
					OutBuffer[len + 1] = '\x15';
					break;
				case 22:
					OutBuffer[len + 1] = '\x16';
					break;
				case 23:
					OutBuffer[len + 1] = '\x17';
					break;
				case 24:
					OutBuffer[len + 1] = '\x18';
					break;
				case 25:
					OutBuffer[len + 1] = '\x19';
					break;
				case 26:
					OutBuffer[len + 1] = '\x1a';
					break;
				case 27:
					OutBuffer[len + 1] = '\x1b';
					break;
				case 28:
					OutBuffer[len + 1] = '\x1c';
					break;
				case 29:
					OutBuffer[len + 1] = '\x1d';
					break;
				case 30:
					OutBuffer[len + 1] = '\x1e';
					break;
				case 31:
					OutBuffer[len + 1] = '\x1f';
					break;
				case 32:
					OutBuffer[len + 1] = '\x20';
					break;
				case 33:
					OutBuffer[len + 1] = '\x21';
					break;
				case 34:
					OutBuffer[len + 1] = '\x22';
					break;
				case 35:
					OutBuffer[len + 1] = '\x23';
					break;
				case 36:
					OutBuffer[len + 1] = '\x24';
					break;
				case 37:
					OutBuffer[len + 1] = '\x25';
					break;
				case 38:
					OutBuffer[len + 1] = '\x26';
					break;
				case 39:
					OutBuffer[len + 1] = '\x27';
					break;
				case 40:
					OutBuffer[len + 1] = '\x28';
					break;
				case 41:
					OutBuffer[len + 1] = '\x29';
					break;
				case 42:
					OutBuffer[len + 1] = '\x2a';
					break;
				case 43:
					OutBuffer[len + 1] = '\x2b';
					break;
				case 44:
					OutBuffer[len + 1] = '\x2c';
					break;
				case 45:
					OutBuffer[len + 1] = '\x2d';
					break;
				case 46:
					OutBuffer[len + 1] = '\x2e';
					break;
				case 47:
					OutBuffer[len + 1] = '\x2f';
					break;
				case 48:
					OutBuffer[len + 1] = '\x30';
					break;
				case 49:
					OutBuffer[len + 1] = '\x31';
					break;
				case 50:
					OutBuffer[len + 1] = '\x32';
					break;
				case 51:
					OutBuffer[len + 1] = '\x33';
					break;
				case 52:
					OutBuffer[len + 1] = '\x34';
					break;
				case 53:
					OutBuffer[len + 1] = '\x35';
					break;
				case 54:
					OutBuffer[len + 1] = '\x36';
					break;
				case 55:
					OutBuffer[len + 1] = '\x37';
					break;
				case 56:
					OutBuffer[len + 1] = '\x38';
					break;
				case 57:
					OutBuffer[len + 1] = '\x39';
					break;
				case 58:
					OutBuffer[len + 1] = '\x3a';
					break;
				case 59:
					OutBuffer[len + 1] = '\x3b';
					break;
				case 60:
					OutBuffer[len + 1] = '\x3c';
					break;
				case 61:
					OutBuffer[len + 1] = '\x3d';
					break;
				case 62:
					OutBuffer[len + 1] = '\x3e';
					break;
				case 63:
					OutBuffer[len + 1] = '\x3f';
					break;
				case 64:
					OutBuffer[len + 1] = '\x40';
					break;
				case 65:
					OutBuffer[len + 1] = '\x41';
					break;
				case 66:
					OutBuffer[len + 1] = '\x42';
					break;
				case 67:
					OutBuffer[len + 1] = '\x43';
					break;
				case 68:
					OutBuffer[len + 1] = '\x44';
					break;
				case 69:
					OutBuffer[len + 1] = '\x45';
					break;
				case 70:
					OutBuffer[len + 1] = '\x46';
					break;
				case 71:
					OutBuffer[len + 1] = '\x47';
					break;
				case 72:
					OutBuffer[len + 1] = '\x48';
					break;
				case 73:
					OutBuffer[len + 1] = '\x49';
					break;
				case 74:
					OutBuffer[len + 1] = '\x4a';
					break;
				case 75:
					OutBuffer[len + 1] = '\x4b';
					break;
				case 76:
					OutBuffer[len + 1] = '\x4c';
					break;
				case 77:
					OutBuffer[len + 1] = '\x4d';
					break;
				case 78:
					OutBuffer[len + 1] = '\x4e';
					break;
				case 79:
					OutBuffer[len + 1] = '\x4f';
					break;
				case 80:
					OutBuffer[len + 1] = '\x50';
					break;
				case 81:
					OutBuffer[len + 1] = '\x51';
					break;
				case 82:
					OutBuffer[len + 1] = '\x52';
					break;
				case 83:
					OutBuffer[len + 1] = '\x53';
					break;
				case 84:
					OutBuffer[len + 1] = '\x54';
					break;
				case 85:
					OutBuffer[len + 1] = '\x55';
					break;
				case 86:
					OutBuffer[len + 1] = '\x56';
					break;
				case 87:
					OutBuffer[len + 1] = '\x57';
					break;
				case 88:
					OutBuffer[len + 1] = '\x58';
					break;
				case 89:
					OutBuffer[len + 1] = '\x59';
					break;
				case 90:
					OutBuffer[len + 1] = '\x5a';
					break;
				case 91:
					OutBuffer[len + 1] = '\x5b';
					break;
				case 92:
					OutBuffer[len + 1] = '\x5c';
					break;
				case 93:
					OutBuffer[len + 1] = '\x5d';
					break;
				case 94:
					OutBuffer[len + 1] = '\x5e';
					break;
				case 95:
					OutBuffer[len + 1] = '\x5f';
					break;
				case 96:
					OutBuffer[len + 1] = '\x60';
					break;
				case 97:
					OutBuffer[len + 1] = '\x61';
					break;
				case 98:
					OutBuffer[len + 1] = '\x62';
					break;
				case 99:
					OutBuffer[len + 1] = '\x63';
					break;
				case 100:
					OutBuffer[len + 1] = '\x64';
					break;
				case 101:
					OutBuffer[len + 1] = '\x65';
					break;
				case 102:
					OutBuffer[len + 1] = '\x66';
					break;
				case 103:
					OutBuffer[len + 1] = '\x67';
					break;
				case 104:
					OutBuffer[len + 1] = '\x68';
					break;
				case 105:
					OutBuffer[len + 1] = '\x69';
					break;
				case 106:
					OutBuffer[len + 1] = '\x6a';
					break;
				case 107:
					OutBuffer[len + 1] = '\x6b';
					break;
				case 108:
					OutBuffer[len + 1] = '\x6c';
					break;
				case 109:
					OutBuffer[len + 1] = '\x6d';
					break;
				case 110:
					OutBuffer[len + 1] = '\x6e';
					break;
				case 111:
					OutBuffer[len + 1] = '\x6f';
					break;
				case 112:
					OutBuffer[len + 1] = '\x70';
					break;
				case 113:
					OutBuffer[len + 1] = '\x71';
					break;
				case 114:
					OutBuffer[len + 1] = '\x72';
					break;
				case 115:
					OutBuffer[len + 1] = '\x73';
					break;
				case 116:
					OutBuffer[len + 1] = '\x74';
					break;
				case 117:
					OutBuffer[len + 1] = '\x75';
					break;
				case 118:
					OutBuffer[len + 1] = '\x76';
					break;
				case 119:
					OutBuffer[len + 1] = '\x77';
					break;
				case 120:
					OutBuffer[len + 1] = '\x78';
					break;
				case 121:
					OutBuffer[len + 1] = '\x79';
					break;
				case 122:
					OutBuffer[len + 1] = '\x7a';
					break;
				case 123:
					OutBuffer[len + 1] = '\x7b';
					break;
				case 124:
					OutBuffer[len + 1] = '\x7c';
					break;
				case 125:
					OutBuffer[len + 1] = '\x7d';
					break;
				case 126:
					OutBuffer[len + 1] = '\x7e';
					break;
				case 127:
					OutBuffer[len + 1] = '\x7f';
					break;
        	}
            len += 2;
        }
    }
//    strcat(OutBuffer, "\x00\x0A"); // add \n
//    OutBuffer[len] = '\x00';
//    OutBuffer[len +  1] = '\x0A';
//    showLog(JUST_INGENICO, __FILE__, __LINE__, DEBUG, "", "outBuffer Len: %d", len);
//    len += 2;
    return len;
}

//MRF_NEW8
//HNO_IDENT5
#ifndef INGENICO
/*
* '_cups_strlcat()' - Safely concatenate two strings.
*/
unsigned int strlcat(char *dst, const char *src, unsigned int size) 
{
	unsigned int    srclen;         /* Length of source string */
	unsigned int    dstlen;         /* Length of destination string */

	/* Figure out how much room is left...*/

	dstlen = strlen(dst);
	size -= dstlen + 1;

	if (!size)
		return (dstlen);        /* No room, return immediately... */

	/* Figure out how much room is needed...*/
	srclen = strlen(src);

	/*Copy the appropriate amount...*/
	if (srclen > size)
		srclen = size;

	memcpy(dst + dstlen, src, srclen);
	dst[dstlen + srclen] = '\0';

	return (dstlen + srclen);
}
#endif /* !HAVE_STRLCAT */


//HNO_IDENT5
#ifndef INGENICO
/*
* '_cups_strlcpy()' - Safely copy two strings.
*/
unsigned int strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int    srclen;

	/* Figure out how much room is needed...*/
	size--;
	srclen = strlen(src);

	/*  Copy the appropriate amount...*/
	if (srclen > size)
		srclen = size;

	memcpy(dst, src, srclen);
	dst[srclen] = '\0';

	return (srclen);
}
#endif /* !HAVE_STRLCPY */

//+MRF_970820
void stringToIP(uint8* input, uint8* output)
{
    int         i           = 0;
    int         j           = 0;
    int         k           = 0;
    int         len         = strlen(input);
    uint8       string[5]   = {0};//ABS:CHANGE
    uint8       split[5][4] = {0,0};
    
    for (i = 0; i <= len; i++)
    {
        if ((input[i] == '.') || (i == len))
        {
            string[j] = atoi(split[j]);
            strcpy(&output[j],&string[j]);
            j++;
            k = 0;
        }
        else
        {
            split[j][k] = input[i];
            k++;
        }
    }
    
    output[4] = 0;
}

//+ HNO_980224
int32 sumTwoNumericStr(uint8* inputStr1, uint8* inputStr2, uint8* result)
{
	int			i = 0;                /* loop counter */
	int			sum = 0;
	uint8		sumStr[10] = { 0 };
	int			temp = 0;
	int			len = 0;
	uint8		str1[20] = { 0 };
	uint8		str2[20] = { 0 };
	uint8		charNum1 = 0;
	int			numericNum1 = 0;
	uint8		charNum2 = 0;
	int			numericNum2 = 0;

	strcpy(str1, inputStr1);
	strcpy(str2, inputStr2);

	if (strlen(inputStr1) >= strlen(inputStr2))
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "str1 bigger");
		padLeft(str2, strlen(inputStr1));
		len = strlen(inputStr1);
	}
	else
	{
		showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "str2 bigger");
		padLeft(str1, strlen(inputStr2));
		len = strlen(inputStr2);
	}

	for (i; i < len; i++)
	{
		//        if (inputStr1[i] >= '0' && inputStr1[i] <= '9'
		//        		&& inputStr2[i] >= '0' && inputStr2[i] >= '9')
		{
			memcpy(&charNum1, &str1[len - 1 - i], 1);
			memcpy(&charNum2, &str2[len - 1 - i], 1);

			numericNum1 = charNum1 - '0';//char '0' is 48: so deduct it from every numeric char
			numericNum2 = charNum2 - '0';//char '0' is 48: so deduct it from every numeric char
			sum = numericNum1 + numericNum2 + temp;

			if (sum > 9)
				temp = 1;
			else
				temp = 0;
			sprintf(sumStr, "%d", sum % 10);

			memcpy(&result[len - i], sumStr, 1);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "result 00: %c", result[0]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "result 11: %c", result[1]);

			if ((i == (len - 1)) && (temp == 1))
			{
				showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "last of number & temp is 1");
				sprintf(sumStr, "%d", sum);
				memcpy(&result[0], &sumStr[0], 2);
			}
			else
				memcpy(&result[0], "0", 1);

			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "result: %c", result[len - 1 - i]);
		}

	}
	removePadLeft(result, '0');
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "result of num: %s", result);

	return TRUE;
}


/**
* Extracts a selection of string and return a new string or NULL.
* It supports both negative and positive indexes.
*/
char *
str_slice(char str[], int slice_from, int slice_to)
{
	char *buffer;
	size_t str_len, buffer_len;

	// if a string is empty, returns nothing
	if (str[0] == '\0')
		return NULL;

	

	// for negative indexes "slice_from" must be less "slice_to"
	if (slice_to < 0 && slice_from < slice_to) {
		str_len = strlen(str);

		// if "slice_to" goes beyond permissible limits
		if (abs(slice_to) > str_len - 1)
			return NULL;

		// if "slice_from" goes beyond permissible limits
		if (abs(slice_from) > str_len)
			slice_from = (-1) * str_len;

		buffer_len = slice_to - slice_from;
		str += (str_len + slice_from);

		// for positive indexes "slice_from" must be more "slice_to"
	}
	else if (slice_from >= 0 && slice_to > slice_from) {
		str_len = strlen(str);

		// if "slice_from" goes beyond permissible limits
		if (slice_from > str_len - 1)
			return NULL;

		buffer_len = slice_to - slice_from;
		str += slice_from;

		// otherwise, returns NULL
	}
	else
		return NULL;

	buffer = calloc(buffer_len, sizeof(char));
	strncpy(buffer, str, buffer_len);
	return buffer;
}

/**
* Convert one String from Windows1256 codepage to UTF8.
* @param   OutBuffer [output]: String converted
* @param   inBuffer [input]: String will be convert
* @return  length of string converted.
*/
uint8* convert_PersianUtf8_To_Cp1256(uint8* inBuffer)
{
	uint16 len = 0;
	uint16  i, j, k = 0;
	uint8           	Cp1256[100] = { 0 };//+HNO,ABS_971128
	//uint8           	activeUserName1[16] = { 0 };//+HNO,ABS_971128
	//uint8           	activeUserName2[16] = { 0 };//+HNO,ABS_971128
	//uint8           	ptr[3] = { 0 };//+HNO,ABS_971128
	int i1 = 0;
	int i2 = 0;
	float loop = 0;
	//long ret = 0;
	//uint8 str[2] = "";



	typedef struct
	{
		uint8   cp1256Char;
		uint8   utf8[10];
	}convertTableST;

	convertTableST cp1265Table[128] =
	{
		{ 128, { 226, 130, 172 } },
		{ 129, { 217, 190 } },//
		{ 130, { 226, 128, 154 } },//
		{ 131, { 198, 146 } },
		{ 132, { 226, 128, 158 } },//
		{ 133, { 226, 128, 166 } },//
		{ 134, { 226, 128, 160 } },//
		{ 135, { 226, 128, 161 } },//
		{ 136, { 203, 134 } },
		{ 137, { 226, 128, 176 } },//
		{ 138, { 217, 185 } },//
		{ 139, { 226, 128, 185 } },//
		{ 140, { 197, 146 } },
		{ 141, { 218, 134 } },
		{ 142, { 218, 152 } },
		{ 143, { 218, 136 } },
		{ 144, { 218, 175 } },
		{ 145, { 226, 128, 152 } },//
		{ 146, { 226, 128, 153 } },//
		{ 147, { 226, 128, 156 } },//
		{ 148, { 226, 128, 157 } },//
		{ 149, { 226, 128, 162 } },//
		{ 150, { 226, 128, 147 } },//
		{ 151, { 226, 128, 148 } },//
		{ 152, { 218, 169 } },
		{ 153, { 226, 132, 162 } },//
		{ 154, { 218, 145 } },
		{ 155, { 226, 128, 186 } },//
		{ 156, { 197, 147 } },
		{ 157, { 226, 128, 140 } },//
		{ 158, { 226, 128, 141 } },//
		{ 159, { 218, 186 } },
		{ 160, { 194, 160 } },//
		{ 161, { 216, 140 } },
		{ 162, { 194, 162 } },//
		{ 163, { 194, 163 } },//
		{ 164, { 194, 164 } },//
		{ 165, { 194, 165 } },//
		{ 166, { 194, 166 } },//
		{ 167, { 194, 167 } },//
		{ 168, { 194, 168 } },//
		{ 169, { 194, 169 } },//
		{ 170, { 218, 190 } },
		{ 171, { 194, 171 } },//
		{ 172, { 194, 172 } },//
		{ 173, { 194, 173 } },//
		{ 174, { 194, 174 } },//
		{ 175, { 194, 175 } },//
		{ 176, { 194, 176 } },//
		{ 177, { 194, 177 } },//
		{ 178, { 194, 178 } },//
		{ 179, { 194, 179 } },//
		{ 180, { 194, 180 } },//
		{ 181, { 194, 181 } },//
		{ 182, { 194, 182 } },//
		{ 183, { 194, 183 } },//
		{ 184, { 194, 184 } },//
		{ 185, { 194, 185 } },//
		{ 186, { 216, 155 } },
		{ 187, { 194, 187 } },//
		{ 188, { 194, 188 } },//
		{ 189, { 194, 189 } },//
		{ 190, { 194, 190 } },//
		{ 191, { 216, 159 } },
		{ 192, { 219, 129 } },
		{ 193, { 216, 161 } },
		{ 194, { 216, 162 } },
		{ 195, { 216, 163 } },
		{ 196, { 216, 164 } },
		{ 197, { 216, 165 } },
		{ 198, { 216, 166 } },
		{ 199, { 216, 167 } },
		{ 200, { 216, 168 } },
		{ 201, { 216, 169 } },
		{ 202, { 216, 170 } },
		{ 203, { 216, 171 } },
		{ 204, { 216, 172 } },
		{ 205, { 216, 173 } },
		{ 206, { 216, 174 } },
		{ 207, { 216, 175 } },
		{ 208, { 216, 176 } },
		{ 209, { 216, 177 } },
		{ 210, { 216, 178 } },
		{ 211, { 216, 179 } },
		{ 212, { 216, 180 } },
		{ 213, { 216, 181 } },
		{ 214, { 216, 182 } },
		{ 215, { 195, 151 } },//
		{ 216, { 216, 183 } },
		{ 217, { 216, 184 } },
		{ 218, { 216, 185 } },
		{ 219, { 216, 186 } },
		{ 220, { 217, 128 } },//
		{ 221, { 217, 129 } },//
		{ 222, { 217, 130 } },//
		{ 223, { 217, 131 } },//
		{ 224, { 195, 160 } },
		{ 225, { 217, 132 } },//
		{ 226, { 195, 162 } },
		{ 227, { 217, 133 } },//
		{ 228, { 217, 134 } },//
		{ 229, { 217, 135 } },//
		{ 230, { 217, 136 } },//
		{ 231, { 195, 167 } },//
		{ 232, { 195, 168 } },//
		{ 233, { 195, 169 } },//
		{ 234, { 195, 170 } },//
		{ 235, { 195, 171 } },//
		{ 236, { 217, 137 } },//
		{ 237, { 217, 138 } },//
		{ 238, { 195, 174 } },//
		{ 239, { 195, 175 } },//
		{ 240, { 217, 139 } },//
		{ 241, { 217, 140 } },//
		{ 242, { 217, 141 } },//
		{ 243, { 217, 142 } },//
		{ 244, { 195, 180 } },//
		{ 245, { 217, 143 } },//
		{ 246, { 217, 144 } },//
		{ 247, { 195, 183 } },//
		{ 248, { 217, 145 } },//
		{ 249, { 195, 185 } },//
		{ 250, { 217, 146 } },//
		{ 251, { 195, 187 } },//
		{ 252, { 195, 188 } },//
		{ 253, { 226, 128, 142 } },//
		{ 254, { 226, 128, 143 } },//
		{ 255, { 219, 146 } }
	};
	
	//memset(OutBuffer, 0, strlen(inBuffer));
	memset(Cp1256, 0, strlen(Cp1256));
	//memset(activeUserName1, 0, strlen(activeUserName1));
	//memset(activeUserName2, 0, strlen(activeUserName2));


	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "cp1256Char=%d", cp1265Table[0].cp1256Char);
	/*showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[0]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[1]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[2]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[3]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[4]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[5]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[6]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[7]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[8]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[9]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[10]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[11]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[12]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[13]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[14]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[15]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[16]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[17]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[18]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[19]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[20]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[21]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[22]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[23]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[24]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[25]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[26]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[27]);
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer=%d", inBuffer[28]);*/

	/*showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "sizeof=%d", sizeof(inBuffer));
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "strlen=%d", strlen(inBuffer));
	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "strlen=%d", stringlen(inBuffer));*/

	

	{
	
	//strcpy(activeUserName1, str_slice(inBuffer, 0, 2));
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName1=%d", activeUserName1[0]);
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName1=%d", activeUserName1[1]);
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName1=%d", activeUserName1[2]);

	//strcpy(activeUserName2, str_slice(inBuffer, 2, 4));
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName2=%d", activeUserName2[0]);
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName2=%d", activeUserName2[1]);
	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName2=%d", activeUserName2[2]);
	

	i1 = 0;
	i2 = 2;


	if (!strlen(inBuffer) % 2)
	{
		//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "loop1=%f", loop);
		loop = strlen(inBuffer);
		//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "loop1=%f", loop);
	}
	else
	{
		//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "loop2=%f", loop);
		loop = (strlen(inBuffer)) + 1;
		//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "loop2=%f", loop);
	}

	//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "loop=%f", loop);

	for (k = 0; k < loop; k++)
	{
		/*showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "k=%d", k);
		showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "i1=%d", i1);
		showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "i2=%d", i2);
		showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "inBuffer[k]=%d", inBuffer[k]);
		showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "[k]=%d", k);*/


		if (inBuffer[k] >= 128 /*&& inBuffer[i] <= 255 --> check for larger than uint8*/)
		{
			k++;

			//for (j = 0; j < 2; j++)
			{
				//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "j=%d", j);
				/*showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "[k]=%d", k);
				showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "str_slice=%d", str_slice(inBuffer, i1, i2)[0]);
				showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "str_slice=%d", str_slice(inBuffer, i1, i2)[1]);
				showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "str_slice=%d", str_slice(inBuffer, i1, i2)[2]);
*/
				for (i = 0; i < 128; i++)
				{
					

					if (!strcmp(cp1265Table[i].utf8, str_slice(inBuffer, i1, i2)))
					{
						//showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "cp1256Char1=%s", &cp1265Table[i].cp1256Char);
						strncat(Cp1256, &cp1265Table[i].cp1256Char, 1);
					/*	showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[0]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[1]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[2]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[3]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[4]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[5]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[6]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[7]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[8]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[9]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[10]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[11]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[12]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[13]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[14]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[15]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[16]);
						showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "activeUserName=%d", activeUserName[17]);*/

					}
				}

				i1 = i1 + 2;
				i2 = i2 + 2;
			}
		}
		else
		{
			switch (inBuffer[k])
			{
			case 32:
				strncat(Cp1256, " ", 1);
				break;
			case 48:
				strncat(Cp1256, "0", 1);
				break;
			case 49:
				strncat(Cp1256, "1", 1);
				break;
			case 50:
				strncat(Cp1256, "2", 1);
				break;
			case 51:
				strncat(Cp1256, "3", 1);
				break;
			case 52:
				strncat(Cp1256, "4", 1);
				break;
			case 53:
				strncat(Cp1256, "5", 1);
				break;
			case 54:
				strncat(Cp1256, "6", 1);
				break;
			case 55:
				strncat(Cp1256, "7", 1);
				break;
			case 56:
				strncat(Cp1256, "8", 1);
				break;
			case 57:
				strncat(Cp1256, "9", 1);
				break;
			default:
				break;
			}
				
			i1 = i1 + 1;
			i2 = i2 + 1;
			/*showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "k=%d", k);
			showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "i1=%d", i1);
			showLog(JUST_VERIFONE, __FILE__, __LINE__, DEBUG, "", "i2=%d", i2);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[0]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[1]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[2]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[3]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[4]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[5]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[6]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[7]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[8]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[9]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[10]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[11]);

			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[12]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[13]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[14]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[15]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[16]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[17]);
			showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[18]);*/

		}

	}

	/*showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[0]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[1]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[2]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[3]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[4]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[5]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[6]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[7]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[8]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[9]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[10]);
	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "var is %d ", activeUserName[11]);*/
	//clearDisplay();
	//displayStringFarsi(activeUserName, 2, PRN_NORM, ALIGN_CENTER);
}
	
return Cp1256;
}

//
//int stringlen(uint8 *str)
//{
//	int num,i = 0;
//	for (str; *str; str++)
//{
//		num++;
//	// ... work with *p
//}
//
//	//while (str[i] != '\0')
//	//{
//	//	++i;
//	//}
//
//		
//	return num;
//}