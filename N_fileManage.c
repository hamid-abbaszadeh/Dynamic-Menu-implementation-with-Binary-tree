
#include <string.h> 
//MRF #include <stdio.h>
#include "N_common.h"
#include "N_utility.h"
#include "N_dateTime.h" 
#include "N_fileManageWrapper.h"
#include "N_fileManage.h"
#include "N_binaryTree.h"
#include "N_menu.h" 
#include "N_cardSpec.h" 
//#include "N_dateTime.h" 
#include "N_scheduling.h"
#include "N_error.h" 
#include "N_terminalSpec.h"
#include "N_POSSpecific.h" 
#include "N_initialize.h" 
#include "N_log.h"
#include "N_printer.h"
#include "N_printerWrapper.h"

#include "N_userManagement.h"
#include "N_TMS.h"
#include "N_passManager.h"

uint8   flag  = FALSE; //MRF_ETC 

//MRF_ETC
void setflag(uint8 init)
{
    flag = init;
}

//MRF_ETC
uint8 getflag(void)
{
    return flag;
}

/**
 * Read a line from file (line to CRLF).
 * @param   fileId [input] : file identification variable
 * @param   buffer [input] : bytes read from file
 * @param   endChar [input] : end character
 * @see     fileRead().
 * @return  retValue (SUCCESS or Error code).
 */
int16 fileReadTo(uint32 fileId, int8* buffer, int8 endChar)
{
    int8    ch[1]       = {0};                  /* control character */
    int16   retValue    = FAILURE;              /* function return value */
    uint16  offset      = 0;                    /** buffer index */
    uint32  len         = 1;                    /* read length */
    uint16   counter     = 0;                    /** loop counter */
    
    retValue = fileRead(fileId, ch, &len);
    if (retValue != SUCCESS)
        return retValue;
    
    while ((int)endChar != (int)ch[0])
    {
        buffer[offset++] = ch[0];
        retValue = fileRead(fileId, ch, &len);
        if (retValue != SUCCESS)
        {
            for (counter = 0; counter < offset; counter++)
                buffer[counter] = 0;
            
            return retValue;
        }
    }
    
    buffer[offset] = 0;	
    
    return retValue;
} 

/**
 * Check file emptiness.
 * @param   fileName [input]: file name.
 * @see     fileSize().
 * @return  SUCCESS or FAILURE.
 */
int16 fileEmpty(uint8* fileName)
{
    int16  retValue = FAILURE;      /* function return value */
    uint32 size     = 0;            /* size of file */
    
    retValue = fileSize(fileName, &size);
    if (retValue != SUCCESS)
        return retValue;
    
    if (size == 0)
        return SUCCESS;
    
    return FAILURE;
}


/**
 * Update structure and file information of file.
 * @param   fileName [input]: file name 
 * @param   stInfo [input]: structure should be read 
 * @param   structLen [input]: structure length 
 * @see     fileExist().
 * @see     fileCreate().
 * @see     fileRemove().
 * @see     openFile().
 * @see     fileWrite(). 
 * @see     closeFile().
 * @return  retValue (SUCCESS or Error code).
 */
int16 updateFileInfo(uint8* fileName, void* stInfo, uint32 structLen)
{
    int16  retValue         = FAILURE;          /* function return value */
    int8   fileNameTemp[32] = {0};              /* temp file name */
    uint32 fileId           =  0;               /* file handler */
    uint32 len              = structLen;        /* requested data length */
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "Into UpdateFile!");
    
    strcpy(fileNameTemp, fileName);
    
    while(strcspn(fileNameTemp, " ") < strlen(fileNameTemp))//while space exist to filename
    	strcpy(strchr(fileNameTemp, ' '), strchr(fileNameTemp, ' ') + 1);

//    uint16 a =strcpy(strchr(fileNameTemp, ' '), strchr(fileNameTemp, ' ') + 1);
//    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "strchr = %s",a);
    
    if (fileExist(fileNameTemp) != SUCCESS)
    {
    	retValue = fileCreate(fileNameTemp);
        if(retValue != SUCCESS)
        {
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "file Not Create: %d",retValue);
            return retValue;
        }
    }
    else
    {
    	retValue = fileRemove(fileNameTemp);
        if(retValue != SUCCESS)
        {
            return retValue;
        }

        retValue = fileCreate(fileNameTemp);
        if (retValue != SUCCESS)
        {
            return retValue;
        }
    }
        
    retValue = openFile(fileNameTemp, &fileId);
    if (retValue != SUCCESS)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "file not open"); 
        return retValue;
    }  
    
    retValue = fileWrite(fileId, stInfo, len);        
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    if (closeFile(fileId) == SUCCESS)
    	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "file closed");
    
    return SUCCESS;
}


/**
 * Append structure of file.
 * @param   fileName [input] : file name
 * @param   stInfo [input] : structure should be read
 * @param   structLen [input] : structure length
 * @see     fileExist().
 * @see     fileCreate().
 * @see     openFile().
 * @see     seekFile().
 * @see     fileWrite().
 * @see     closeFile().
 * @return  SUCCESS or FAILURE.
 */
int16 appendFileInfo(uint8* fileName, void* stInfo, uint32 structLen)
{
    int16  retValue         = FAILURE;          /* function return value */
    int8   fileNameTemp[32] = {0};              /* temp file name */
    uint32 fileId           = 0;                /* file handler */
    uint32 len              = structLen;        /* requested data length */
    uint32 newpos           = 0;                /* write position */
    
    strcpy(fileNameTemp,fileName);
    while (strcspn(fileNameTemp," ") < strlen(fileNameTemp))
        strcpy(strchr(fileNameTemp,' '), strchr(fileNameTemp,' ') + 1);
    
    if (fileExist(fileNameTemp) != SUCCESS)
    {
        retValue = fileCreate(fileNameTemp);
        if (retValue != SUCCESS)
            return retValue;
    }
    
    retValue = openFile(fileNameTemp, &fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = seekFile(fileId, 0, FILE_SEEK_END, &newpos);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, stInfo, len);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    closeFile(fileId);
    
    return SUCCESS;
}


/**
 * Append structure to fixed file.
 * @param   fileName [input] : file name
 * @param   stInfo [input] : structure should be read 
 * @param   structLen [input] : structure length 
 * @param   maxRecord [input] : maximum record in file 
 * @see     fileExist().
 * @see     fileCreate().
 * @see     fileSize().
 * @see     openFile().
 * @see     fileWrite().
 * @see     seekFileBegin().
 * @see     fileRead().
 * @see     closeFile().
 * @return  SUCCESS or FAILURE.
 */
int16 appendFixedFileInfo(uint8* fileName, void* stInfo, uint32 structLen, int16 maxRecord)
{
    int16  retValue		= FAILURE;	    /* function return value */
    uint32 fileId		= 0;            /* file handler */
    uint32 len			= structLen;    /* requested data length */
    uint32 currentPos   = 0;            /* last record position */
    uint32 size			= 4;            /* last record position size */
    uint32 newPos		= 0;            /*write position */
   
    if (fileExist(fileName) != SUCCESS)
    {
        retValue = fileCreate(fileName);
        if (retValue != SUCCESS)
            return retValue;
    }
    
    retValue = fileSize(fileName, &currentPos); 
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    if (currentPos == 0)
    { 
        currentPos = 4;
        
        retValue = fileWrite(fileId, &currentPos, size);
        if (retValue != SUCCESS)
        {
            closeFile(fileId);
            return retValue;
        }

        retValue = seekFileBegin(fileId);
        if (retValue != SUCCESS)
        {
            closeFile(fileId);
            return retValue;
        }
    }

    retValue = fileRead(fileId, &currentPos, &size);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = seekFile(fileId, currentPos, FILE_SEEK_BEGINNING, &newPos);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, stInfo, len);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    currentPos += len;
    if ((currentPos - 4) / len == maxRecord)
        currentPos = 4;
    
    retValue = seekFileBegin(fileId);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, &currentPos, size);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    closeFile(fileId);
    
    return SUCCESS;
}

/**
 * Append structure end of file without opening file.
 * @param   fileId [input] : file id
 * @param   stInfo [input] : structure should be read
 * @param   structLen [input] : structure length
 * @see     seekFile().
 * @see     closeFile().
 * @see     fileWrite().
 * @return  SUCCESS or FAILURE..
 */
int16 appendOpenedFile(uint32 fileId, void* stInfo, uint32 structLen)
{
    int16  retValue		= FAILURE;	    /* function return value */
    uint32 len			= structLen;    /* requested data length */
    uint32 newpos		= 0;            /* write position */
    
    retValue = seekFile(fileId, 0, FILE_SEEK_END, &newpos);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, stInfo, len);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    return SUCCESS;
}

/**
 * Read last record from fixed file.
 * @param   fileName [input] : file name.
 * @param   stInfo [input] : structure should be read .
 * @param   structLen [input] : structure length .
 * @param   maxRecord [input] : maximum record in file .
 * @see     openFile().
 * @see     seekFile().
 * @see     closeFile().
 * @see     readFixedFileInfo().
 * @return  SUCCESS or FAILURE..
 */
int16 readFixedFileLastRecord(uint8* fileName, void* stInfo, uint32 structLen, int16 maxRecord)
{
    int16  retValue     = FAILURE;          /* function return value */
    uint32 fileId       = 0;                /* file handler */
    uint32 len          = structLen;        /* requested data length */
    uint32 size         = 0;                /* file length */
    int16  lastRecord   = 0;                /* last record number */
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = seekFile(fileId, 0, FILE_SEEK_END,&size);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }

    lastRecord = (int) ((size - 4) / len) - 1;

    retValue = readFixedFileInfo(fileId, stInfo, structLen, lastRecord, maxRecord);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = closeFile(fileId);
    if (retValue != SUCCESS)
    	return retValue;
    
    return SUCCESS ;
}

/**
 * Update last record of file.
 * @param   fileName [input] : file name
 * @param   stInfo [input] : structure should be read 
 * @param   structLen [input] : structure length
 * @see     fileExist().
 * @see     fileCreate().
 * @see     fileSize().
 * @see     openFile().
 * @see     seekFile().
 * @see     closeFile().
 * @see     fileWrite().
 * @return  SUCCESS or FAILURE.
 */
int16 updateFileLastRecord(uint8* fileName, void* stInfo, int16 structLen)
{
    int16  retValue         = FAILURE;              /* function return value */
    uint8  fileNameTemp[32] = {0};                  /** temp file name */
    uint32 fileId           = 0;                    /* file handler */
    uint32 len              = structLen;            /* requested data length */
    uint32 newPos           = 0;                    /* write position */
    uint32 size             = 0;                    /* file length */
    
    strcpy(fileNameTemp, fileName);
    while (strcspn(fileNameTemp, " ") < strlen(fileNameTemp))
        strcpy(strchr(fileNameTemp, ' '), strchr(fileNameTemp, ' ') + 1);//vaghti be space miresad kalameh bad ra yeki be chap mibarad.

    if (fileExist(fileNameTemp) != SUCCESS)
    {
        retValue = fileCreate(fileNameTemp);
        if (retValue != SUCCESS)
            return retValue;
    }
    
    retValue = fileSize(fileNameTemp, &size);
    if (retValue != SUCCESS) 
        return retValue;
    
    if (size < (uint32) structLen)
        return FAILURE;

    retValue = openFile(fileNameTemp, &fileId);
    if (retValue != SUCCESS)
        return retValue;

    retValue = seekFile(fileId, size - structLen, FILE_SEEK_BEGINNING, &newPos);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, stInfo, len);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    closeFile(fileId);
    
    return SUCCESS;
}


/**
 * Update last record of fixed file.
 * @param   fileName [input] : file name.
 * @param   stInfo [input] : structure should be read 
 * @param   structLen [input] : structure length 
 * @param   maxRecord [input] : maximum record in file 
 * @see     openFile().
 * @see     fileRead().
 * @see     closeFile().
 * @see     seekFile().
 * @see     fileWrite().
 * @return  SUCCESS or FAILURE.
 */
int16 updateFixedFileLastRecord(uint8* fileName,void* stInfo, uint32 structLen, uint32 maxRecord)
{
    int16  retValue     = FAILURE;              /* function return value */
    uint32 fileId       = 0;                    /* file handler */
    uint32 fileSize     = 0;                    /* file length */
    uint32 currentPos   = 0;                    /* last record position */
    uint32 totalRecord  = 0;                    /* files records number */
    uint32 len          = structLen;            /* requested data length */
    uint32 size         = 4;                    /* last record position size */
    uint32 newPos       = 0;                    /* write position */
	
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = fileRead(fileId, &currentPos, &size);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = seekFile(fileId, 0, FILE_SEEK_END, &fileSize);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    totalRecord = (fileSize - 4) / len;
    if (totalRecord == maxRecord && currentPos == 4)
        currentPos = fileSize - len;
    else
        currentPos -= len;
    
    retValue = seekFile(fileId, currentPos, FILE_SEEK_BEGINNING, &newPos);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    retValue = fileWrite(fileId, stInfo, len);
    if (retValue != SUCCESS)
    {
        closeFile(fileId);
        return retValue;
    }
    
    closeFile(fileId);
    
    return SUCCESS;
}


/**
 * delete last record of fixed file.
 * @param   fileName [input] : file name
 * @param   structLen [input] : structure length
 * @see     fileEmpty().
 * @see     fileSize().
 * @see     fileFreeze().
 * @return  SUCCESS or FAILURE.
 */
int16 deleteFileLastRecord(int8* fileName, uint32 structLen)
{
    int16  retValue         = FAILURE;          /* function return value */
    int8   fileNameTemp[32] = {0};              /* temp file name */
    uint32 size             = 0;                /* file length */
    
    strcpy(fileNameTemp, fileName);
    while (strcspn(fileNameTemp, " ") < strlen(fileNameTemp))
        strcpy(strchr(fileNameTemp, ' '), strchr(fileNameTemp, ' ') + 1);
    
    if (fileEmpty(fileNameTemp) == SUCCESS)
        return FAILURE;
    
    retValue = fileSize(fileNameTemp, &size);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = fileFreeze(fileNameTemp, size - structLen);
    if (retValue != SUCCESS)
        return retValue;

    return SUCCESS;
}


/**
 * Read a line from file(line to CRLF).
 * @param   fileId [input] : file identification
 * @param   buff [input] : bytes read from file
 * @param   readLen [output] : buffer length
 * @see     fileRead().
 * @return  SUCCESS or FAILURE.
 */
int16 fileReadLine(uint32 fileId, void* buff, uint32* readLen)
{
    int8    ch[1]    = {0};                          /* control character */
    int8*   buffer   = (int8*) buff;                  /* read buffer */
    int16   retValue = FAILURE;                      /* function return value */
    int16   offset   = 0;                            /** index in read buffer */
    uint32  len      = 1;                            /* file read length */
    int16   counter  = 0;
            
    retValue = fileRead(fileId, ch, &len);
    if (retValue != SUCCESS)
        return retValue;
    
    while ((int)';' != (int)ch[0])
    {
        buffer[offset] = ch[0];
        ++offset;
        
        retValue = fileRead(fileId, ch, &len);
        if (retValue != SUCCESS)
        {
            for (counter = 0 ; counter<offset ; counter++)
                buffer[counter]=0;
            
            return retValue;
        }
    }
    
    buffer[offset] = 0;	
    *readLen = offset + 1;
    
    return SUCCESS;
}


/**
 * Read all data from file.
 * @param   fileName [input] : File name
 * @param   data [output] : Data should be read 
 * @param   len [input] : inputs maximum length and returns actual read length
 * @see     fileExist().
 * @see     openFile().
 * @see     fileRead().
 * @see     closeFile().
 * @return  SUCCESS or FAILURE.
 */
int16 readFileInfo(uint8* fileName, void* data, uint32* len)
{
    int16  retValue = FAILURE;                  /* function return value */
    uint32 fileId   = 0;                        /* file handler */
    uint32 preLen   = 0;                        /* copy of requested length */
    uint32 newLen   = 0;
    preLen          = *len;
    newLen          = preLen;

   
    if (fileExist(fileName) != SUCCESS)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "File Not Exist!");
        return ERR_FILE_NOT_FOUND;
    }

    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
    {  
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "File Not Open!");
        return retValue;
    }
    
    retValue = fileRead(fileId, data, &preLen);
    if (retValue != SUCCESS)
    {
        showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "fileRead old");
        closeFile(fileId);
        return retValue;
    }

//    retValue = fileRead(fileId, data, &newLen); 
//    //TODO: TEST THIS PART
//    showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "newLen: %d", newLen);
//    if (retValue != SUCCESS)
//    {
//    	showLog(ALL_POS, __FILE__, __LINE__, DEBUG, "", "Can not read new file");
//        closeFile(fileId);
//        return retValue;
//    }
       
    closeFile(fileId);

//    //TODO: TEST THIS PART
//    if (newLen != preLen) 
//    {
//    	showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "READ ERR4");
//        return FAILURE;
//    }
    
    return SUCCESS;
}

/**
 * Read record from fixed file with record number.
 * @param   fileId [input] : file handler 
 * @param   stInfo [input] : structure should be read 
 * @param   structLen [input] : structure length 
 * @param   recordNum [input] : record number 
 * @param   maxRecord [output] : maximum record in file 
 * @see     seekFile().
 * @see     seekFileBegin().
 * @see     fileRead().
 * @return  SUCCESS or FAILURE.
 */
int16 readFixedFileInfo(uint32 fileId, void* stInfo, uint32 structLen, 
                           uint16 recordNum, uint32 maxRecord)
{
    int16  retValue     = FAILURE;          /* function return value */
    uint32 fileSize     = 0;                /* size of file */
    uint32 len          = structLen;        /* file structure length */
    uint32 currentPos   = 0;                /* last record position */
    uint32 totalRecord  = 0;                /* file records number */
    uint32 size         = 4;                /* position size */
    uint32 newPos       = 0;                /* current record position */

    retValue = seekFile(fileId, 0, FILE_SEEK_END, &fileSize);
    if (retValue != SUCCESS)
        return retValue;
    
    totalRecord = (fileSize - 4) / len;
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**recordNum**:%d",recordNum);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**totalRecord**:%d",totalRecord);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**fileSize**:%d",fileSize);
    
    if (recordNum > totalRecord)
        return FAILURE;
    
    retValue = seekFileBegin(fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = fileRead(fileId, &currentPos, &size);
    if (retValue != SUCCESS)
        return retValue;
    
    if (totalRecord == maxRecord)
        currentPos += recordNum * len;
    else
        currentPos = (recordNum * len) + 4;
    
    if (currentPos >= (maxRecord * len + 4)) //return to begin position , over write
        currentPos -= maxRecord * len;
    
    retValue = seekFile(fileId, currentPos, FILE_SEEK_BEGINNING, &newPos);
    if (retValue != SUCCESS)
        return retValue;
    
    retValue = fileRead(fileId, stInfo, &len);
    if (retValue != SUCCESS)
        return retValue;
    
    return retValue;
}

/**
 * Read array of record from fixed file, from identified beginning record to specified end record by number of needed record.
 * @param   fileName [input] : file name 
 * @param   buffer [output] :info 
 * @param   structLen [input] : structure length 
 * @param   startRecord [input] : first record number to read
 * @param   neededNum [input] : number of needed record
 * @param   maxRecord [output] : maximum record in file 
 * @see     openFile().
 * @see     readFixedFileInfo().
 * @see     closeFile().
 * @return  SUCCESS or FAILURE.
 */
int16 readFixedFileInfoArray(uint8* fileName,/*MRF_ETC uint8**/void* buffer, uint32 structLen, int startRecord,
                             uint16 neededNum, uint32 maxRecord)
{
    int16   retValue = FAILURE;          /* read file return value */
    uint32  fileId   = 0;                /* file handler */
    uint16  counter  = 0;                /* loop counter */
	uint8 * buff_cast = buffer; 												//ABS:ADD

    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
        return retValue;

    for (counter = 0; counter < neededNum; counter++, startRecord++) 
    {
		retValue = readFixedFileInfo(fileId, &buff_cast[counter * structLen],
                                       structLen, startRecord, maxRecord);
        if (retValue != SUCCESS)
            return retValue;
    }
    
    closeFile(fileId);
    
    return SUCCESS;
}

/** 
 * Unpack File Information.
 * @param   fileName [input] : file name
 * @param   data [input] : data
 * @param   outDataBuff [output] : outDataBuff
 * @param   lineNum [input] : number of needed line
 * @see     openFile().
 * @see     fileReadLine().
 * @see     closeFile().
 * @return  SUCCESS or FAILURE.
 */
int16 unpackFileInfo(uint8* fileName, int8* data, int8* outDataBuff[56],
                        uint16 lineNum)
{
    int8*   temp     = 0;                        /* temp copy of data */
    int16   i        = 0;                        /* loop counter */
    int16   retValue = FAILURE;                  /* function return value */
    uint32  fileId   = 0;                        /* file handler */
    uint32  len      = 0;                        /* read length */
    
    if (data == NULL)
        return FAILURE;
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
        return retValue;
    
    for (i = 0; i < lineNum; i++) 
    {
    	retValue = fileReadLine(fileId, data, &len);
        if (retValue == FAILURE)
        {
            closeFile(fileId);
            return retValue;
        }
    }
    
    if (len == 0)
        return FAILURE;
    
    temp = data;
    len = strcspn((uint8*)temp, ",");
    temp[len] = 0;
    
    for (i = 0; i < 32; i++)
    {
        outDataBuff[i] = temp;
        temp = temp + len + 1;
        
        if (strchr((uint8*)temp, ',') == NULL)
            break;
        
        len = strcspn((uint8*)temp, ",");
        temp[len] = 0;
    }
    
    i++;
    outDataBuff[i] = temp;
    closeFile(fileId);
    
    return SUCCESS;
}


/**
 * Search (binary search) first occur of date range in file and return record number that contain that date.
 * @param   fileId [input] : file handler
 * @param   structLen [input] : structure length
 * @param   dateOffset [input] : date offset in structure
 * @param   startDate [input] : beginning of date range
 * @param   endDate [input] : end of date range
 * @param   maxRecord [input] : maximum record in file
 * @param   low [input] : beginning of records number range
 * @param   high [input] : beginning of records number range
 * @see     readFixedFileInfo()
 * @see     searchFirstOccurDateInFixedFile().
 * @return  record number or error code.
 */
int searchFirstOccurDateInFixedFile(uint32 fileId, uint32 structLen, 
                                    uint32 dateOffset, uint32 startDate, 
                                    uint32 endDate, uint32 maxRecord, 
                                    uint32 low, uint32 high) 
{
    int    mid                          = 0;                /* middle record between low and high */ 
    uint8  buffer[RECORD_BUFFER_LEN]    = {0};              /* record buffer */    // MGH 050411 : define size of array
    int16  retValue                     = FAILURE;          /* read file return value */
    uint32 date1                        = 0;                /* date of low record */
    uint32 date2                        = 0;                /* data of light record */
    uint32 date3                        = 0;                /* data of middle record */
    
    if (high < low)
        return -1;
    
    retValue = readFixedFileInfo(fileId, buffer, structLen, low, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date1, &buffer[dateOffset], sizeof(uint32));
    retValue = readFixedFileInfo(fileId, buffer, structLen, high, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date2, &buffer[dateOffset], sizeof(uint32));
    if (!((date1 <= endDate) && (date2 >= startDate)))
        return -1;
    
    if ((startDate <= date1) && (date1 <= endDate))
        return low;
    
    mid = low + ((((high - low) / 2) * 100) - ((((high - low) / 2) * 100) % 100)) / 100 ;
    if ((mid == low) && ((startDate <= date2) || (date2 <= endDate)))
        return high;
    
    retValue = readFixedFileInfo(fileId,buffer,structLen, mid, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date3, &buffer[dateOffset] , sizeof(uint32));
    if ((startDate <= date3) && (date3 <= endDate))
        return searchFirstOccurDateInFixedFile(fileId, structLen, dateOffset, 
                                               startDate, endDate, maxRecord, low, mid);  
    else if (date3 < startDate)
        return searchFirstOccurDateInFixedFile(fileId, structLen, dateOffset, 
                                               startDate, endDate, maxRecord, mid+1, high);  
    else if (date3 > endDate)
        return searchFirstOccurDateInFixedFile(fileId, structLen, dateOffset, 
                                               startDate, endDate, maxRecord, low, mid-1);  
    
}

/**
 * Search (binary search) last occur of date range in file and return record number that contain that date.
 * @param   fileId [input] : file handler 
 * @param   structLen [input] : structure length 
 * @param   dateOffset [input] :t date offset in structure 
 * @param   startDate [input] : beginning of date range 
 * @param   endDate [input] : end of date range 
 * @param   maxRecord [input] : maximum record in file 
 * @param   low [output] : beginning of records number range 
 * @param   high  [output] : end of records number range 
 * @see     readFixedFileInfo().
 * @see     searchLastOccurDateInFixedFile().
 * @return 
 *  error code.
 */
int searchLastOccurDateInFixedFile(uint32 fileId, uint32 structLen, 
                                   uint32 dateOffset, uint32 startDate, 
                                   uint32 endDate, uint32 maxRecord, 
                                   uint32 low, uint32 high)
{
    int    mid                          = 0;                /* middle record between low and high */ 
    uint8  buffer[RECORD_BUFFER_LEN]    = {0};              /* record buffer */    // MGH 050411 : define size of array
    int16  retValue                     = FAILURE;          /* read file return value */
    uint32 date1                        = 0;                /* date of low record */
    uint32 date2                        = 0;                /* data of light record */
    uint32 date3                        = 0;                /* data of middle record */

    if (high < low)
        return -1;
    
    retValue = readFixedFileInfo(fileId,buffer,structLen, low, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date1, &buffer[dateOffset], sizeof(uint32));
    retValue = readFixedFileInfo(fileId,buffer,structLen, high, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date2, &buffer[dateOffset], sizeof(uint32));
    if (!((date1 <= endDate) && (date2 >= startDate)))
        return -1;
    
    if ((startDate <= date2) && (date2 <= endDate))
        return high;

    mid = low + ((((high - low) / 2) * 100) - ((((high - low) / 2) * 100) % 100)) / 100 ;
    if ((mid == low) && ( (startDate <= date1) || (date1 <= endDate)))
        return low;
    
    retValue = readFixedFileInfo(fileId,buffer,structLen, mid, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date3, &buffer[dateOffset] , sizeof(uint32));
    if ((startDate <= date3) && (date3 <= endDate))
        return searchLastOccurDateInFixedFile(fileId, structLen, dateOffset, startDate, endDate, maxRecord, mid, high);  
    else if (date3 < startDate)
        return searchLastOccurDateInFixedFile(fileId, structLen, dateOffset, startDate, endDate, maxRecord, mid+1, high);  
    else if (date3 > endDate)
        return searchLastOccurDateInFixedFile(fileId, structLen, dateOffset, startDate, endDate, maxRecord, low, mid-1);   
}

/**
 * Search(binary search) date range in file.
 * @param   fileName [input] : file name 
 * @param   structLen [input] : structure length 
 * @param   dateOffset [input] : date offset in structure 
 * @param   startDate [input] : beginning of date range 
 * @param   endDate [input] : end of date range 
 * @param   maxRecord [input] : maximum record in file 
 * @param   startRecordNum [output] : first record number of date range in file 
 * @param   endRecordNum [output] : last record number of date range in file 
 * @see     fileSize().
 * @see     openFile().
 * @see     searchFirstOccurDateInFixedFile().
 * @see     searchLastOccurDateInFixedFile().
 * @return  error code.
 */
int searchDateRangeInFixedFile(uint8* fileName, uint32 structLen, uint32 dateOffset, uint32 startDate,
                               uint32 endDate, uint32 maxRecord, int* startRecordNum, int* endRecordNum)
{
    int16   retValue    = FAILURE;         /* read file return value */
    uint32  fileId      = 0;               /* file handler */
    uint32  length      = 0;               /* file size */
    int     totalnumber = 0;
    
    retValue = fileSize(fileName, &length);
    if (retValue != SUCCESS)
       return -2;
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
       return -2;
    
    totalnumber = (length - 4) / structLen;
    *startRecordNum = searchFirstOccurDateInFixedFile(fileId, structLen, dateOffset, startDate, 
                                                      endDate, maxRecord, 0, totalnumber - 1);
    
    totalnumber = (length - 4) / structLen;
    *endRecordNum = searchLastOccurDateInFixedFile(fileId, structLen, dateOffset, startDate, 
                                                   endDate, maxRecord, 0, totalnumber - 1); 

    closeFile(fileId);
    
    return 0;
}

/**
 * Search(binary search) first date and time in file.
 * @param fileId [input] : file identification variable
 * @param structLen [input] : structure length
 * @param dateOffset [input] : date offset in structure
 * @param startDateTime [input] : beginning of date range
 * @param endDateTime [input] : end of date range
 * @param maxRecord [input] : maximum record in file
 * @param low [output] : beginning of records number range
 * @param high [output] : end of records number range
 * @see   readFixedFileInfo().
 * @see   searchFirstOccurDateTimeInFixedFile().
 * @return error code.
 */
int searchFirstOccurDateTimeInFixedFile(uint32 fileId, uint32 structLen, uint32 dateOffset, 
						dateTimeST* startDateTime, dateTimeST* endDateTime, uint32 maxRecord, 
                             uint32 low, uint32 high) 
{
    int    mid                          = 0;                /* middle record between low and high */ 
    uint8  buffer[RECORD_BUFFER_LEN]    = {0};              /* record buffer */    // MGH 050411 : define size of array
    int16  retValue                     = FAILURE;          /* read file return value */
    uint32 date1                        = 0;                /* date of low record */
    uint32 date2                        = 0;                /* data of lighh record */
    uint32 date3                        = 0;                /* data of middle record */
    uint32 time1                        = 0;                /* Time of low record */
    uint32 time2                        = 0;                /* Time of lighh record */
    uint32 time3                        = 0;                /* Time of middle record */
    uint8 startDateTimeStr[20]          = {0};
    uint8 endDateTimeStr[20]            = {0};
    uint8 dateTime1[20]                 = {0};
    uint8 dateTime2[20]                 = {0};
    uint8 dateTime3[20]                 = {0};
 
    if (high < low)
        return -1;
    
    sprintf(startDateTimeStr, "%ld%07ld", startDateTime->date, startDateTime->time);
    sprintf(endDateTimeStr, "%ld%07ld", endDateTime->date, endDateTime->time);

    retValue = readFixedFileInfo(fileId, buffer, structLen, low, maxRecord);
    if (retValue != SUCCESS)
        return -2;

    memcpy(&date1, &buffer[dateOffset], sizeof(uint32));
    memcpy(&time1, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));

    sprintf(dateTime1, "%ld%07ld", date1, time1);
   
    retValue = readFixedFileInfo(fileId, buffer, structLen, high, maxRecord);
    if (retValue != SUCCESS)
        return -2;

    memcpy(&date2, &buffer[dateOffset], sizeof(uint32));
    memcpy(&time2, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));
    
    sprintf(dateTime2, "%ld%07ld", date2, time2);
    if (!((date1 <= endDateTime->date) && (date2 >= startDateTime->date)))
        return -1;

    if ((strcmp(startDateTimeStr, dateTime1) <= 0) && (strcmp(dateTime1, endDateTimeStr) <= 0))
        return low;
    
    mid = low + ((((high - low) / 2) * 100) - ((((high - low) / 2) * 100) % 100)) / 100 ;
    
/*
    if ((mid == low) && ((strcmp(startDateTimeStr, dateTime2) <= 0) || 
            (strcmp(dateTime2, endDateTimeStr) <= 0)))
        return high;
*/
    if ((mid == low) && ((strcmp(startDateTimeStr, dateTime2) <= 0) && 
            (strcmp(dateTime2, endDateTimeStr) <= 0)))
        return high;
    
    retValue = readFixedFileInfo(fileId, buffer, structLen, mid, maxRecord);
    if (retValue != SUCCESS)
        return -2;

    memcpy(&date3, &buffer[dateOffset] , sizeof(uint32));
    memcpy(&time3, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));
    
    sprintf(dateTime3, "%ld%07ld", date3, time3);

    if ((strcmp(startDateTimeStr, dateTime3) <= 0) && (strcmp(dateTime3, endDateTimeStr) <= 0))
        return searchFirstOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, low, mid);  
    else if (strcmp(dateTime3, startDateTimeStr) < 0)
        return searchFirstOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, mid + 1, high);  
    else if (strcmp(dateTime3, endDateTimeStr) > 0)
        return searchFirstOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, low, mid - 1);
}


/**
 * Search (binary search) last date and time in file.
 * @param fileId [input] : file identification variable
 * @param structLen [input] : structure length
 * @param dateOffset [input] : date offset in structure
 * @param startDateTime [input] : beginning of date range 
 * @param endDateTime [input] : end of date range
 * @param maxRecord [input] : maximum record in file
 * @param low [output] : beginning of records number range
 * @param high [output] : end of records number range
 * @see   readFixedFileInfo().
 * @see   searchLastOccurDateTimeInFixedFile().
 * @return Error Code.
 */
int searchLastOccurDateTimeInFixedFile(uint32 fileId, uint32 structLen, 
                                   uint32 dateOffset, dateTimeST* startDateTime, dateTimeST* endDateTime,
                                   uint32 maxRecord, uint32 low, uint32 high)
{
    int    mid                          = 0;                /* middle record between low and high */ 
    uint8  buffer[RECORD_BUFFER_LEN]    = {0};              /* record buffer */    // MGH 050411 : define size of array
    int16  retValue                     = FAILURE;          /* read file return value */
    uint32 date1                        = 0;                /* date of low record */
    uint32 date2                        = 0;                /* data of lighh record */
    uint32 date3                        = 0;                /* data of middle record */
    uint32 time1                        = 0;                /* Time of low record */
    uint32 time2                        = 0;                /* Time of lighh record */
    uint32 time3                        = 0;                /* Time of middle record */
    uint8 startDateTimeStr[20]          = {0};
    uint8 endDateTimeStr[20]            = {0};
    uint8 dateTime1[20]                 = {0};
    uint8 dateTime2[20]                 = {0};
    uint8 dateTime3[20]                 = {0};
 
    if (high < low)
        return -1;
    
    sprintf(startDateTimeStr, "%ld%07ld", startDateTime->date, startDateTime->time);
    sprintf(endDateTimeStr, "%ld%07ld", endDateTime->date, endDateTime->time);

    retValue = readFixedFileInfo(fileId, buffer, structLen, low, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date1, &buffer[dateOffset], sizeof(uint32));
    memcpy(&time1, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));
    
    sprintf(dateTime1, "%ld%07ld", date1, time1);
//    sprintf(dateTime1, "%ld%ld", date1, time1);

    retValue = readFixedFileInfo(fileId, buffer, structLen, high, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date2, &buffer[dateOffset], sizeof(uint32));
    memcpy(&time2, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));
    
    sprintf(dateTime2, "%ld%07ld", date2, time2);
    if (!((date1 <= endDateTime->date) && (date2 >= startDateTime->date)))
        return -1;

    if ((strcmp(startDateTimeStr, dateTime2) <= 0) && (strcmp(dateTime2, endDateTimeStr) <=0))
        return high;

    mid = low + ((((high - low) / 2) * 100) - ((((high - low) / 2) * 100) % 100)) / 100 ;
   
/*
    if ((mid == low) && ((strcmp(startDateTimeStr, dateTime1) <= 0) || 
            (strcmp(dateTime1, endDateTimeStr) <= 0)))
        return low;
*/
    if ((mid == low) && ((strcmp(startDateTimeStr, dateTime1) <= 0) && 
            (strcmp(dateTime1, endDateTimeStr) <= 0)))
        return low;
    
    retValue = readFixedFileInfo(fileId, buffer, structLen, mid, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&date3, &buffer[dateOffset] , sizeof(uint32));
    memcpy(&time3, &buffer[dateOffset + sizeof(uint32)], sizeof(uint32));
    
    sprintf(dateTime3, "%ld%07ld", date3, time3);
       
    if ((strcmp(startDateTimeStr, dateTime3) <= 0) && (strcmp(dateTime3, endDateTimeStr) <= 0))
        return searchLastOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, mid, high);  
    else if (strcmp(dateTime3, startDateTimeStr) < 0)
        return searchLastOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, mid + 1, high);  
    else if (strcmp(dateTime3, endDateTimeStr) > 0)
        return searchLastOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
                                               startDateTime, endDateTime, maxRecord, low, mid - 1);
}

/**
 * Search (binary search) date and time range in file.
 * @param fileName [input] : file name
 * @param structLen [input] : structure length
 * @param dateOffset [input] : date offset in structure
 * @param startDateTime [input] : beginning of date range
 * @param endDateTime [input] : end of date range
 * @param maxRecord [input] : maximum record in file
 * @param startRecordNum [output] : beginning of records number range
 * @param endRecordNum [output] : end of records number range
 * @see   fileSize().
 * @see   openFile().
 * @see   searchFirstOccurDateTimeInFixedFile().
 * @return Error Code.
 */
int searchDateTimeRangeInFixedFile(uint8* fileName, uint32 structLen, uint32 dateOffset, dateTimeST* startDateTime,
						dateTimeST* endDateTime, uint32 maxRecord, int* startRecordNum, int* endRecordNum)
{
    int16   retValue    = FAILURE;         /** read file return value */
    uint32  fileId      = 0;               /** file handler */
    uint32  length      = 0;               /** file size */
    int     totalnumber = 0;
    
    retValue = fileSize(fileName, &length);
    if (retValue != SUCCESS)
       return -2;
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
       return -2;
    
    totalnumber = (length - 4) / structLen;
    *startRecordNum = searchFirstOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
    										startDateTime, endDateTime, maxRecord, 0, totalnumber - 1);
    
    totalnumber = (length - 4) / structLen;
    *endRecordNum = searchLastOccurDateTimeInFixedFile(fileId, structLen, dateOffset, 
    										startDateTime, endDateTime, maxRecord, 0, totalnumber - 1); 
    closeFile(fileId);
    
    return 0;
}

//MRF_ETC
int searchSTANInFixedFile(uint8* fileName, uint32 structLen, uint32 dateOffset, uint32 STAN,
						uint32 maxRecord, int* recordNum)
{
    int16   retValue    = FAILURE;         /** read file return value */
    uint32  fileId      = 0;               /** file handler */
    uint32  length      = 0;               /** file size */
    uint32  totalnumber = 0;
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**searchSTANInFixedFile**");
    
    retValue = fileSize(fileName, &length);
    if (retValue != SUCCESS)
       return -2;
    
    retValue = openFile(fileName, &fileId);
    if (retValue != SUCCESS)
       return -2;
    
    totalnumber = (length - 4) / structLen;
    
    *recordNum = searchFirstOccurSTANInFixedFile(fileId, structLen, STAN, dateOffset, maxRecord,
            0, totalnumber - 1);

    closeFile(fileId);
    
    return 0;
}


 int searchFirstOccurSTANInFixedFile(uint32 fileId, uint32 structLen, uint32 STAN, 
        uint32 dateOffset, uint32 maxRecord, uint32 low, uint32 high) 
{
    int     mid                              = 0;                /* middle record between low and high */ 
//    uint8   buffer[2 * RECORD_BUFFER_LEN]    = {0};
#ifdef INGENICO/* record buffer */    // MGH 050411 : define size of array
    uint8   buffer[10 * RECORD_BUFFER_LEN]    = {0};//..HNO_971008
#else
    uint8   buffer[2 * RECORD_BUFFER_LEN]    = {0};
#endif

    int16   retValue                         = FAILURE;          /* read file return value */
    uint32  stan1                            = 0;
    uint32  stan2                            = 0;
    uint32  stan3                            = 0;
 
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "**searchFirstOccurSTANInFixedFile**");
    
    if (high < low)
        return -1;
    
    retValue = readFixedFileInfo(fileId, buffer, structLen, low, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&stan1, &buffer[dateOffset], sizeof(uint32));
    
    if (stan1 == STAN)
    {
        return low;
    }
    retValue = readFixedFileInfo(fileId, buffer, structLen, high, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&stan2, &buffer[dateOffset], sizeof(uint32));
    if (stan2 == STAN)
        return high;
    
    mid = low + ((((high - low) / 2) * 100) - ((((high - low) / 2) * 100) % 100)) / 100;
    if (low == mid && (STAN != stan1 && STAN != stan2))
        return -2;
    
    retValue = readFixedFileInfo(fileId, buffer, structLen, mid, maxRecord);
    if (retValue != SUCCESS)
        return -2;
    
    memcpy(&stan3, &buffer[dateOffset] , sizeof(uint32));
    if (STAN == stan3)
    {
        return mid; 
    }
    else if (STAN < stan3)
    {
        return searchFirstOccurSTANInFixedFile(fileId, structLen, STAN, dateOffset, 
                                                maxRecord, low, mid); 
    }
    else if (STAN > stan3)
    {
        return searchFirstOccurSTANInFixedFile(fileId, structLen, STAN, dateOffset, 
                                                maxRecord, mid + 1, high);  
    }
}


 struct {
	 uint8     val[100];
	 uint8 *str;
 } file_name_convert[] = {
	
	 { MASTER_KEY_FILE, "MASTER_KEY_FILE" },
	 { BIN_FILE, "BIN_FILE" },
	 { PREFIX_FILE, "PREFIX_FILE" },
	 { MERCHANT_SPEC_FILE, "MERCHANT_SPEC_FILE" },
	 { VERSIONS_FILE, "VERSIONS_FILE" },
	 { SCHEDULE_FILE, "SCHEDULE_FILE" },
	 { EXIST_UNSUCCESS_SETTLEMENT_FILE, "EXIST_UNSUCCESS_SETTLEMENT_FILE" },
	 { REVERSAL_TRANS_FILE, "REVERSAL_TRANS_FILE" },
	 { TRANSACTIONS_BATCH_FILE, "TRANSACTIONS_BATCH_FILE" },
	 { SETTLEMENT_INFO_FILE, "SETTLEMENT_INFO_FILE" },
	 { REVERSAL_RECEIPT_FILE, "REVERSAL_RECEIPT_FILE" },
	 { GENERAL_CONN_INFO_FILE, "GENERAL_CONN_INFO_FILE" },
	 { CONN_FILE1, "CONN_FILE1" },
	 { CONN_FILE2, "CONN_FILE2" },
	 { CONN_FILE3, "CONN_FILE3" },
	 { CONN_FILE4, "CONN_FILE4" },
	 { CONN_FILE5, "CONN_FILE5" },
	 { CONN_FILE6, "CONN_FILE6" },
	 { SW_VERSION_NUMBER_FILE, "SW_VERSION_NUMBER_FILE" },
	 { SETTING_FILE, "SETTING_FILE" },
	 { CUSTOMER_RECEIPT_FILE, "CUSTOMER_RECEIPT_FILE" },
	// { POS_PARAM, "POS_PARAM" },
	// { PPP_USER_PASS, "PPP_USER_PASS" },
	 { LOGON_INFO_FILE, "LOGON_INFO_FILE" },
	 { PIN_KEY_FILE, "PIN_KEY_FILE" },
	 { GENERAL_KEY_FILE, "GENERAL_KEY_FILE" },
	 { VERSION_KEY_FILE, "VERSION_KEY_FILE" },
	 { KCV_FILE, "KCV_FILE" },
	 { VOUCHER_KEY_FILE, "VOUCHER_KEY_FILE" },
	 { SUPERVISOR_FILE, "SUPERVISOR_FILE" },
	 { MAC_KEY_FILE, "MAC_KEY_FILE" },
	 { ETC_INFO_FILE, "ETC_INFO_FILE" },
	 { UNKNOWN_ETC_INFO_FILE, "UNKNOWN_ETC_INFO_FILE" },
	 { LOAN_INFO_FILE, "LOAN_INFO_FILE" },
	 { UNKNOWN_LOAN_INFO_FILE, "UNKNOWN_LOAN_INFO_FILE" },
	 { ROLL_INFO_FILE, "ROLL_INFO_FILE" },
	 { CHARGE_INFO_FILE, "CHARGE_INFO_FILE" },
	 { PCPOS_INFO_FILE, "PCPOS_INFO_FILE" },
	 { USER_MANAGEMENT_FILE, "USER_MANAGEMENT_FILE" },
	 { ACTIVATED_USER_FILE, "ACTIVATED_USER_FILE" },
	 { LOG_TYPE_PASSWORDS_FILE, "LOG_TYPE_PASSWORDS_FILE" },
	 { TERMINAL_SPEC_FILE, "TERMINAL_SPEC_FILE" },
	 { POS_SERVICE_FILE, "POS_SERVICE_FILE" },
	 { POS_TIME_FILE, "POS_TIME_FILE" },
	 { TMS_INFO_FILE, "TMS_INFO_FILE" },
	 { TMS_UPDATED_FILE, "TMS_UPDATED_FILE" },
	 { TMS_SCHEDULE_FILE, "TMS_SCHEDULE_FILE" },
	 { LOG_TYPE_FILE, "LOG_TYPE_FILE" },
	 { LOG_PORT_FILE, "LOG_PORT_FILE" },
	 { GLOBAL_MENU_PASSWORDS_FILE, "GLOBAL_MENU_PASSWORDS_FILE" },
	 { MERCHANT_MENU_PASSWORDS_FILE, "MERCHANT_MENU_PASSWORDS_FILE" },
	 { USER_MANAGER_MENU_PASSWORDS_FILE, "USER_MANAGER_MENU_PASSWORDS_FILE" },
	 { SUPERVISOR_MENU_PASSWORDS_FILE, "SUPERVISOR_MENU_PASSWORDS_FILE" },
	 { SUPERVISOR_PASS_FLAG_FILE, "SUPERVISOR_PASS_FLAG_FILE" },

 };
 
uint8* str2filename(const char *str)
 {
		 int j;
		 for (j = 0; j < strlen(file_name_convert->str); ++j)
		 if (!strcmp(str, file_name_convert[j].str))
			 return file_name_convert[j].val;
	 }



 uint8 readFilenameListAndCreate_XML()
 {
	 mxml_node_t*        tree = NULL;
	 mxml_node_t*        node = NULL;
	 mxml_index_t*       switchIndex = NULL;
	 int num = 0;
	 uint8 value[100] = { 0 };
	 uint16 retValue = FAILURE;


	 tree = read_message_xml("f:filelist.xml");
	 switchIndex = mxmlIndexNew(tree, "file", NULL);
	 for (num = 0; num < switchIndex->num_nodes; num++)
	 {
		 node = mxmlIndexEnum(switchIndex);		
		 showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "filename=%s", str2filename(node->value.element.attrs[0].value));

		 retValue = fileCreate(str2filename(node->value.element.attrs[0].value));
		 if (retValue != SUCCESS)
		 {
			 showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "file %s Not Create: %d", node->value.element.attrs[0].value, retValue);
			 return retValue;
		 }
				
	 }

	 return retValue;	
 }