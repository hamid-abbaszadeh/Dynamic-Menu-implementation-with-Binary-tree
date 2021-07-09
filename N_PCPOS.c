

#define STATE_START                 0
#define STATE_SEND_ACK              1
#define STATE_SEND_DATA             2
#define STATE_SEND_CONTROL_BYTE     3
#define STATE_RECEIVE_ACK           4
#define STATE_RECEIVE_DATA          5
#define STATE_RECEIVE_CONTROL_BYTE  6
#define STATE_START_OF_OPERATION    7
#define STATE_DO_TRANS              8
#define STATE_ERROR                 9
#define STATE_FINISH                10
#define	STATE_END                   11
#define	STATE_CONNECT_PC                   12

#define ERR_OPEN_PORT				100
#define ERR_SEND_DATA				101
#define	ERR_RECEIVE_DATA			102
#define	ERR_TRANSACTION				103
#define	ERR_PCPOS_CAN				104
#define	ERR_INCORRECT_DATA			105
#define	ERR_UNKNOWN					106
//#define ERR_TRANS                   107

static uint8    serviceName[20] = {0};
static uint8    controlByte     = NUL;
static uint8    checkState[20]  = {0};
static uint8    data[10][30]    = {0, 0};
static uint8    controller      = 0;
static int8     errCode         = 0;
static uint8    preState        = STATE_FINISH;
static uint8    tries           = 0;
//static uint8    pc_trans        = TRUE;//HNO_COMMENT
static uint8    cancel          = FALSE;
static uint8    printer_access  = TRUE;
static int      valAccept       = 0;//HNO_TCP
static int      pcPosPort       = 0;//HNO_TCP
static uint8    PcPosconnType[10]  = {0};//HNO_TCP

//HNO_TCP
int createSocket(void);
uint8 connectSocket(int server_socket);
void readDataFromClient(uint8* recStr);
void sendDataToClient(uint8* sendStr);

//HNO_TCP
/**
 * create a new socket for transmission data to PC.
 * @see     initSocket()
 * @see     socket()
 * @see     showLog
 * @return  number of created socket.
 */
int createSocket(void)
{
    int                 serverSocket;
    uint8               connStatus              = DISCONNECTED;
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "************create socket***********");

    initSocket();
    
//    setConnectionType(CONNECTION_LAN); 
//    connStatus = checkConnectionStatus();
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "create Socket number: %d", serverSocket);
    
    return serverSocket;
}

//HNO_TCP
/**
 * assigns the address specified by address to the socket.
 * @param   socket [input]number of created socket.
 * @see     bind()
 * @see     showLog()
 * @return  NONE.
 */
uint8 bindSocket(int socket) //..ABS_971022
{
    struct sockaddr_in server;			
    struct timeval tv;
   
    int opt = 1;
    int retBind = 0;
    int retset = 0;//..ABS_971022
	tv.tv_sec = 3;  /* 3 Seconds Time-out */
	tv.tv_usec = 0;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(pcPosPort);
    server.sin_addr.s_addr = INADDR_ANY;//inet_addr("192.168.0.139") not useful

//    // Forcefully attaching socket to the port 
	retset = setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));//..ABS_971022
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "retset: %d", retset);

    retBind = bind(socket, (struct sockaddr*)&server, sizeof(server));
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "out bind: %d", retBind);


    if(retBind < 0)
    {
        close(socket);
        return FALSE;
    }
    
    return TRUE;
}

//HNO_TCP
/**
 * listen for data in specific socket number and accept exchange as soon as possible.
 * @param   serverSocket [input] number of created socket.
 * @see     listen()
 * @see     select()
 * @see     accept()
 * @see     FD_ZERO()
 * @see     FD_SET()
 * @see     showlog()
 * @return  TRUE or FALSE.
 */
uint8 connectSocket(int serverSocket)
{
    fd_set readset;
    int maxfd, result;
    int retListen;
    int len = 0;
    struct timeval timeout;

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(pcPosPort);
    server.sin_addr.s_addr = INADDR_ANY;//inet_addr("192.168.0.139") not useful
    
    retListen = listen(serverSocket,1);// 1 means the maximum length of queue
    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "out listen: %d", retListen);
    if(retListen < 0)
        return FALSE;

    FD_ZERO(&readset);//clear the readset
    FD_SET(serverSocket, &readset);//add our file descriptor to the readset
    maxfd = serverSocket;
    
    do{
		delay(50, JUST_VERIFONE);//..ABS_971128

		//printOneStringFarsi("ÊÑÇ˜äÔ ÇäÌÇã äÔÏ!", PRN_NORM, ALIGN_CENTER);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        result = select(maxfd + 1, &readset, NULL, NULL, &timeout);
        if(result == -1)
        {
            showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "select result has error");
            break;
        }
        if(result == 0)
        {
            showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "select timeout");
            break;
        }
        else if(result > 0)
        {
            len = sizeof(struct sockaddr_in);

            valAccept = accept(serverSocket, (struct sockaddr*)&server, (socklen_t*)&len);
            showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "valAccept in accept: %d ", valAccept);


            return TRUE;
        }
    }
	while (1);

    return FALSE;
}

//HNO_TCP
/**
 * read data from socket.
 * @param   recStr [output] received string .
 * @see     read()
 * @see     showlog()
 * @return  NONE.
 */
void readDataFromClient(uint8* recStr)
{
    uint16 readLen = 0;
    
    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "valAccept in read: %d ", valAccept);
    readLen = read(valAccept , recStr, 300);
	delay(200, JUST_VERIFONE);//..ABS_971023


    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "receive Str: %x ", recStr[0]);
    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "data read len: %d ", readLen);
}

//HNO_TCP
/**
 * send data to socket.
 * @param   sendStr [input] the string that should be send to socket.
 * @see     send()
 * @see     showlog()
 * @return  NONE.
 */
void sendDataToClient(uint8* sendStr)
{
    uint16 sendLen = 0;

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "valAccept: %d ", valAccept);
    sendLen = send(valAccept , sendStr , strlen(sendStr) , 0 ); 

	delay(200,JUST_VERIFONE);//..ABS_971022
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "sendStr: %x", sendStr[0]);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "strLen: %d ", sendLen);
}

 uint8 PCPOS(argumentListST* args)		//..ABS_971022
{
    filesST*            files               = (filesST*) (args->argumentName);    
    uint8               state               = STATE_START;
    int16               transactionStatus   = FALSE;
    int                 socket              = 0;//HNO_TCP
	int					ret					= 0;	//..ABS_971022
	int					ret2				= 0;
    uint8               clearLines          = ALL_LINES; //prevent from change screen's message

    messageSpecST       messageSpec;
    terminalSpecST      terminalCapability  = getTerminalCapability();//MRF_NEW9
    serviceSpecST       POSService          = getPOSService();//MRF_NEW12
     
    memset(&messageSpec, 0, sizeof(messageSpecST));
    if ((terminalCapability.pcPosCapability) && (!POSService.PcPOSService))//MRF_NEW9
    {
        displayMessageBox("ÓÑæíÓ ãæÑÏ äÙÑ ÛíÑ ÝÚÇá ÇÓÊ", MSG_INFO);
        return FALSE;
    }
        
    if(!setPcPosConnType())//HNO_TCP  
        return FALSE;

    if (strcmp(PcPosconnType , "TCP") == 0)//HNO_TCP
    {
        socket = createSocket();//HNO_TCP
        if(socket == -1)
        {
            close(socket);
            displayMessageBox("ÎØÇ ÏÑ ÇíÌÇÏ ÇÑÊÈÇØ", MSG_ERROR);
            return FALSE;
        }
        
        if(!bindSocket(socket))
        {
//            close(socket);
            displayMessageBox("ÎØÇ ÏÑ ÇÊÕÇá Èå ÔÈ˜å", MSG_ERROR);
            return FALSE;
        }
            
    }

    else if (strcmp(PcPosconnType, "Serial") == 0)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "open serial");
        if (!openSerialPort(PC_POS_PORT, BAUD_RATE_115200, PARITY, DATA_SIZE, STOP_BITS))
        {
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "can't open serial port");
            closeSerialPort(PC_POS_PORT);
            displayMessageBox("ÎØÇÏÑÈÇÒ˜ÑÏä æÑÊ", MSG_ERROR);
            return FALSE;
        }
    }
    
    else
    {
        displayMessageBox("äæÚ ÇÑÊÈÇØ ÈÇ ÇíÇäå ãÔÎÕ äíÓÊ", MSG_ERROR);
        return FALSE;
    }
        
    while (state != STATE_END)
    {
        switch (state)
        {            
            case STATE_START:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "START");
                disconnectModem(); //MRF_NEW6

                state = receiveENQWait(&clearLines, socket);
                break;

            case STATE_SEND_CONTROL_BYTE:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "STATE_SEND_CONTROL_BYTE");
                state = sendControlBytePCPOS(transactionStatus);
                break;
            case STATE_RECEIVE_DATA:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "STATE_RECEIVE_DATA");
                state = receiveDataPCPOS(&messageSpec);
                break;
            case STATE_DO_TRANS:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "STATE_DO_TRANS");
                state = transPcPos(files, messageSpec);
                break;
            case STATE_ERROR:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "STATE_ERROR");
                switch (errCode)
                {
                    case ERR_OPEN_PORT:
                    displayMessageBox("ÎØÇ ÏÑ ÈÇÒ ˜ÑÏä æÑÊ", MSG_ERROR);
                            break;
                    case ERR_SEND_DATA:
                    displayMessageBox("ÎØÇ ÏÑ ÇÑÓÇá ÇØáÇÚÇÊ", MSG_ERROR);
                            break;
                    case ERR_RECEIVE_DATA:
                    displayMessageBox("ÎØÇ ÏÑ ÏÑíÇÝÊ ÇØáÇÚÇÊ", MSG_ERROR);
                            break;
                    case ERR_TRANSACTION:
                    //						if (messageSpec.responseCode != 0)
                    displayMessageBox("ÊÑÇ˜äÔ äÇãæÝÞ", MSG_ERROR);
                    //						else if (!transactionStatus)
                    //							sendErrorPCPOS(ERR_TRANSACTION,"ÎØÇí ÊÑÇ˜äÔ äÇãæÝÞ");
                    break;
                    case ERR_UNKNOWN:
                    default:
                    displayMessageBox("ÎØÇí äÇ ãÔÎÕ", MSG_ERROR);
                            break;
				}
                state = STATE_FINISH;
//                controlByte = CAN;
                break;
            case STATE_FINISH:
                showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "FINISH!!");
            	flushReceiptionBuffer(PC_POS_PORT);
//            	if (transactionStatus && errCode == 0)
//                    displayMessage("ÇÊãÇã ãæÝÞíÊ ÂãíÒ ÚãáíÇÊ", DISPLAY_START_LINE + 1, ALL_LINES);
            	//load default parameter values
            	state = STATE_START;
            	errCode = 0;
    	    	transactionStatus = 0;
                memset(&messageSpec, 0, sizeof(messageSpecST));
			
#ifdef VX520				
				shutdown(socket, 2);
				ret = socketclose(socket);
				shutdown(valAccept, 2);
				ret2 = socketclose(valAccept);
				socket = -1 ;
				valAccept = -1 ;
				
				if (strcmp(PcPosconnType, "TCP") == 0)//HNO_TCP
				{
					socket = createSocket();//HNO_TCP
					if (socket == -1)
					{
						close(socket);
						displayMessageBox("ÎØÇ ÏÑ ÇíÌÇÏ ÇÑÊÈÇØ", MSG_ERROR);
						return FALSE;
					}

					if (!bindSocket(socket))
					{
						//            close(socket);
						displayMessageBox("ÎØÇ ÏÑ ÇÊÕÇá Èå ÔÈ˜å", MSG_ERROR);
						return FALSE;
					}

				}
#endif



            	break;
            case STATE_END:
                displayMessage("ÞØÚ ÇÑÊÈÇØ ÈÇ ÑÇíÇäå...", DISPLAY_START_LINE + 1, ALL_LINES);
            	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "END");
                break;
            default:
                break;
        }
    }
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "close port PCPOS");
    closeSerialPort(PC_POS_PORT);  
	
	
#ifdef VX520				
	LANDisconnect();
#endif
    ret = close(socket);
    ret2 = close(valAccept);

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "ret2: %d", ret2);
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "ret: %d", ret);
	
    return TRUE;
}

uint8 transPcPos(filesST* files, messageSpecST messageSpec)
{
    uint8		state			= STATE_START;
    uint8               retvalue                = 0;
    
    retvalue = buyPcPOSTrans(files, &messageSpec);
    if(retvalue == TRUE)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "buyPcPOSTrans success");
//        pc_trans = TRUE;
//        sendDataPCPOS(&messageSpec);//HNO_IMPROVE_SPEED
        controlByte = EOT;
        state = STATE_SEND_CONTROL_BYTE;
    }
    else
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "buyPcPOSTrans not success");
        cancel = FALSE;
        
        if(retvalue == PRINTER_FAIL)
            printer_access = FALSE;
        
        else 
        {
            if (messageSpec.merchantSpec.recieveSTAN == 0)
            cancel = TRUE;
        
            printer_access = TRUE;
        }
//        pc_trans = FALSE;
        sendDataPCPOS(&messageSpec, FALSE);
        controlByte = EOT;
        state = STATE_SEND_CONTROL_BYTE;    
    }  
    return state;
}


uint8 receiveENQWait(uint8* clearLines, int socket)
{
    uint16                      resLen                  = 0;
    uint8                       pressedKey              = 0;
    uint8                       state			= STATE_START;
    uint8 			response[200]           = {0}; 				/** response message */
    uint16 			responseLen             = sizeof(response);
    int16                       retValue		= -1;
	

    displayMessage("ãäÊÙÑ ÏÑíÇÝÊ ÇØáÇÚÇÊ ÇÒ ÑÇíÇäå ...", DISPLAY_START_LINE + 1, *clearLines);
    
    *clearLines = NO_LINES;
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "before key press");

    if (isKeyPressed())//HNO
    {
        readPressedKey(&pressedKey);
        if (pressedKey == KBD_CANCEL)
        {  
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "cancel");
            displayMessage("ÞØÚ ÇÑÊÈÇØ ÈÇ ÑÇíÇäå...", DISPLAY_START_LINE + 1, ALL_LINES);
            state = STATE_END;
            return state;
        }
    }
	
    if(strcmp(PcPosconnType, "TCP") == 0)
    {
		
        if(!connectSocket(socket))
        {

            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "not receive data");
            state = STATE_START;
                return state;
        }
        readDataFromClient(response);
    }
    
    else if(strcmp(PcPosconnType, "Serial") == 0)
    {
        resLen = 1; // input, output parameter 
        showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "before receive");

        retValue = receiveData(PC_POS_PORT, response, &resLen, 5000, PC_POS_FLUSH, FALSE);
        showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "retValue:%d", retValue);
    }
    
    if(response[0] == ENQ)
//    if (retValue && (response[0] == ENQ)) //receive ENQ byte
    {
        showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "response[0] == ENQ");
        //initDataParams();
        displayMessage("ÈÑÞÑÇÑí ÇÑÊÈÇØ..", DISPLAY_START_LINE + 1, ALL_LINES);
        *clearLines = ALL_LINES;
        controlByte = ACK;
        state = STATE_SEND_CONTROL_BYTE;    
    }
    return state;
}

uint8 sendDataPCPOS(messageSpecST* messageSpec, uint8 result)//HNO_CHANGE add entrance
{
    uint8       state           = STATE_ERROR;
    uint16      len             = 0;
    uint8       temp[100]       = {0};
    uint8       transInfo[200]  ={0};
    uint8       cardID[17]      = {0};
    uint8       CB = NULL;
    

    //*****************STAN*********************
    sprintf(temp, "%ld", messageSpec->merchantSpec.recieveSTAN);
    strcpy(transInfo, temp);
    strcat(transInfo, ";");
    //*****************reference num*********************
    strcat(transInfo, messageSpec->retrievalReferenceNumber);
    strcat(transInfo, ";");
    //*****************amount*********************
    strcat(transInfo, messageSpec->amount);
    strcat(transInfo, ";");
    //*************terminal number***********
    strcat(transInfo, messageSpec->merchantSpec.terminalID);
    strcat(transInfo, ";");
    //*************merchant number***********
    strcat(transInfo, messageSpec->merchantSpec.merchantID);
    strcat(transInfo, ";");
    //*************PAN*******************
    maskCardId(messageSpec->cardSpec.PAN, cardID);
    removePad(cardID, ' ');
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "cardID = %s", cardID);
    strcat(transInfo, cardID);
    strcat(transInfo, ";");
    //*************date******************
    sprintf(temp,"%04d/%02d/%02d", getYear(messageSpec->dateTime.date), getMonth(messageSpec->dateTime.date), getDay(messageSpec->dateTime.date));
    strcat(transInfo, temp);
    strcat(transInfo, ";");
    //*************time******************
    sprintf(temp, "%02d:%02d:%02d", getHour(messageSpec->dateTime.time), getMinute(messageSpec->dateTime.time), getSecond(messageSpec->dateTime.time));
    strcat(transInfo, temp);
    strcat(transInfo, ";");
    //*************response status******************
    if(!result)
    {
        if(cancel)// cancel transaction & stan =0
        {
            sprintf(temp,"%ld", 300);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "temp = %d %s", temp, temp);
        }
        else if(!printer_access)// roll out or not access printer
        {
            sprintf(temp, "%ld", 500);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "!printer_access");
        }
        else // transaction not success
            sprintf(temp,"%ld", messageSpec->responseStatus);
            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "messageSpec->responseStatus = %d", messageSpec->responseStatus);
    }

    else if(result) //transaction success
        sprintf(temp, "%d", 100);
    
    else if(result && cancel) // power outage pos 
        sprintf(temp, "%d", 400);
    
    strcat(transInfo, temp);
    strcat(transInfo, ";");
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "transInfo = %s", transInfo);
    //printOneStringFarsi(transInfo, PRN_NORM, ALIGN_CENTER);
    
    len = strlen(transInfo);
	showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "len data info = %d", len);
    
    if(strcmp(PcPosconnType, "TCP") == 0)//HNO_TCP
        sendDataToClient(transInfo);//..ABS_971022
    
    else if(strcmp (PcPosconnType, "Serial") == 0)
    {
        if (!sendData(PC_POS_PORT, transInfo, len, PC_POS_FLUSH, TRUE))
        {
            showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "not send data information");
            if (errCode == 0) //dont change previous Err code
                    errCode = ERR_SEND_DATA;
            //return state;
        }
    }
    CB = ETX;
    
    //sendDataToClient(out, &CB);//HNO_TCP
    if(strcmp(PcPosconnType , "Serial") == 0)
        if(!sendData(PC_POS_PORT,&CB,1,PC_POS_FLUSH,FALSE))
                showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "not send cb");
    
    state = STATE_FINISH;
}

 uint8 sendControlBytePCPOS(int16 transactionStatus)
{
    uint8               state               = STATE_ERROR;
    uint8               connType[10]        = {0};//HNO_TCP

    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "send control Byte");
    if(controlByte == ACK)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "send controlByte ACK");
        //HNO_TCP
        if(strcmp(PcPosconnType, "TCP") == 0)//HNO_TCP
            sendDataToClient(&controlByte);
        
        else if (strcmp(PcPosconnType, "Serial") == 0)//HNO_TCP
        {
            if (!sendData(PC_POS_PORT, &controlByte, 1, PC_POS_FLUSH, TRUE))
            {
                showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "not send ACK");
                if (errCode == 0)
                    errCode = ERR_SEND_DATA;
                return state;
            }
        }
        transactionStatus = TRUE;
        state = STATE_RECEIVE_DATA;
    } 
    //HNO_TCP
//    else if(controlByte == CAN)
//    {
//        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "cancel transaction");
//        if (!sendData(PC_POS_PORT, &controlByte, 1, PC_POS_FLUSH, TRUE))
//        {
//            if (errCode == 0)
//                errCode = ERR_SEND_DATA;
//            return state;
//        }
//        state = STATE_FINISH;
//    }   
    else if(controlByte == EOT)
    {
//        //HNO_TCP
//        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "controlByte EOT: %x", controlByte[0]);
//        sendDataToClient(out, &controlByte);
////        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "transaction end");
////        if (!sendData(PC_POS_PORT, &controlByte, 1, PC_POS_FLUSH, TRUE))
////        {
////            showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "not send EOT");
////            if (errCode == 0)
////                errCode = ERR_SEND_DATA;
////            return state;
////        }
        transactionStatus = TRUE;
        state = STATE_FINISH;
    }
    return state;
}

uint8 receiveDataPCPOS(messageSpecST* messageSpec)//HNO_TCP
{
    uint8   response[220]       = {0};
    uint16  resLen              = 70;
    uint8   state               = STATE_ERROR;
    int     amountLen           = 0;
    int     advertise1Len       = 0;
    int     advertise2Len       = 0;
    uint8   amount[20]          = {0};
    uint8   advertise1[101]     = {0};
    uint8   advertise2[101]     = {0};
    //uint8   receiveStr[200]     = {0};//HNO_TCP
    
    showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "before receive");
    
    if(strcmp(PcPosconnType, "TCP") == 0)
        readDataFromClient(response);
    
    else if(strcmp(PcPosconnType, "Serial") == 0)
    {
        if (!receiveData(PC_POS_PORT, response, &resLen, 8000, PC_POS_FLUSH, TRUE))
        {
            showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "not receive");
            if (errCode == 0)
                    errCode = ERR_RECEIVE_DATA;
            return state;
        }
    }
    
    showLog(JUST_CASTLES, __FILE__, __LINE__, TRACE, "", "response: %s", response);
    /////TO DOOOOO:IMPROVEEEEEEEEEEEEEEEEEEEEEEEEE
    if (response[0] == ENQ) //the Pc app still sending ENQ!!
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "the Pc app still sending ENQ");
    	controlByte = ACK;
    	return STATE_SEND_CONTROL_BYTE;
    }
    else if (response == NULL)
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "response == NULL");
        if (errCode == 0)
            errCode = ERR_RECEIVE_DATA;
        state = STATE_ERROR;
    }
    else 
    {
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "response: %s", response);
        amountLen = strcspn(response, ";");
        strncpy(amount,response,amountLen);
        //displayStringFarsi(amount, 2,PRN_NORM, ALIGN_CENTER);
        strcpy(messageSpec->amount , amount);//HNO
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "messageSpec->amount 1: %s", messageSpec->amount);
        
        advertise1Len = strcspn(&response[amountLen + 1], ";");
        strncpy(advertise1,&response[amountLen + 1],advertise1Len);
        strcpy(messageSpec->information.advertise1 , advertise1);//HNO
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "advertise1 %s", advertise1);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "advertise1Len %d", advertise1Len);
        
        advertise2Len = strcspn(&response[amountLen + advertise1Len + 2], ";");
        strncpy(advertise2,&response[amountLen + advertise1Len + 2],advertise2Len);
        strcpy(messageSpec->information.advertise2 , advertise2);//HNO
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "advertise2 %s", advertise2);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "advertise2Len %d", advertise2Len);
        
        state = STATE_DO_TRANS; 
    }
    return state;
}

void initDataParams(void)
{
    uint8 i = 0;
    uint8 j = 0;
    
    for (i = 0; i < 10; i++)
        for (j = 0; j < 30; j++)
            data[i][j] = 0;
    
    for (i = 0; i < 20; i++)
        checkState[i] = 0;
    
    for (i = 0; i < 20; i++)
        serviceName[i] = 0;
    
    controller = 0;
    errCode = 0;
    controlByte = NUL;  
}
//HNO_TCP
/**
 * read PCPOS connection file and set information in structure.
 * @see     readFileInfo()
 * @see     displayMessageBox()
 * @see     showlog()
 * @see     setLANPcPosConfig()
 * @return  TRUE or FALSE.
 */
uint8 setPcPosConnType()
{
    uint16              retValue        = 0;
    uint32              len             = sizeof(PcPosConnInfoST);
    PcPosConnInfoST     pcposSet;
    
    memset(&pcposSet, 0, sizeof(PcPosConnInfoST));
    
    retValue = readFileInfo(PCPOS_INFO_FILE, &pcposSet, &len);
    if (retValue != SUCCESS)  
    {
        displayMessageBox("áØÝÇ ÊäÙíãÇÊ ÇÑÊÈÇØ ÈÇ ÑÇíÇäå ÇäÌÇã ÔæÏ", MSG_ERROR);
        return FALSE;
    }

    strcpy(PcPosconnType, pcposSet.connTypePcPos);
    
    if (strcmp(PcPosconnType , "TCP") == 0)
    {
        pcPosPort = pcposSet.pcposPort;
        
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "localIpAddress:%s", pcposSet.lanPcPos.localIpAddress);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "gateway:%s", pcposSet.lanPcPos.gateway);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "connType: %s", pcposSet.connTypePcPos);
        showLog(ALL_POS, __FILE__, __LINE__, TRACE, "", "porttt: %d", pcposSet.pcposPort);
    
        //setLANPcPosConfig(pcposSet.lanPcPos); 
    }
    
    return TRUE;
}
