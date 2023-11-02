int CAN_rx_wait_time=1000;

String receive_CAN_String()
{
    String received = "";

    unsigned long startTime = millis();

    while (received.indexOf('#') == -1 && (millis() - startTime < CAN_rx_wait_time))
    {
        received = received + receive_CAN();
    }
    if (received.indexOf('#') != -1)
    {
        received.remove(received.indexOf('#'));
        return received;
    }
    else if (millis() - startTime >= CAN_rx_wait_time)
    {
        received = "ERROR:TIMEOUT";
    }
    else if (received.indexOf('#') == -1)
    {
        received = "ERROR:NO_HASH";
    }
    else
    {
        received = "ERROR:UNKNOWN";
    }
    return received;
}

// receive a CAN frame
String receive_CAN()
{
    String msgString = "";
    unsigned char datalength;
    unsigned char receiveBuffer[8];
    long unsigned int transmitterID;

    if (!digitalRead(CAN0_INT))
    {
        if (CAN0.checkError())
        {
            // if the error is receiver full clear it
            // CAN0.clearRcvBufFullError();
            Serial.println("CAN receive error");
            error_counter++;

            if (error_counter > 100)
            {
//                ESP.restart();
                  can_init();
                  Serial.println("resetting");
                // resetFunc();  //call reset
            }
        }
        else
        {
            CAN0.readMsgBuf(&transmitterID, &datalength, receiveBuffer);
            can_data_from_id=transmitterID;
            for (int i = 0; i < datalength; i++)
            {
                msgString = msgString + char(receiveBuffer[i]);
            }
        }
    }

    return msgString;
}

void listen_to_only_id_100()
{
	CAN0.init_Mask(0, 0, 0x000F0000); // Init first mask...
	CAN0.init_Filt(0, 0, 0x00040000); // Init first filter...
	CAN0.init_Filt(1, 0, 0x00040000); // Init second filter...

	CAN0.init_Mask(1, 0, 0x000F0000); // Init second mask...
	CAN0.init_Filt(2, 0, 0x00040000); // Init third filter...
	CAN0.init_Filt(3, 0, 0x00040000); // Init fouth filter...
	CAN0.init_Filt(4, 0, 0x00040000); // Init fifth filter...
	CAN0.init_Filt(5, 0, 0x00040000); // Init sixth filter...
}

void listen_to_only_id(int _id_)
{
	uint32_t mask = 0x000F0000;

	uint32_t filter = mask;
	filter  = filter >> 16;
	filter = filter & _id_;
	filter = filter << 16;

	CAN0.init_Mask(0, 0, mask); // Init first mask...
	CAN0.init_Filt(0, 0, filter); // Init first filter...
	CAN0.init_Filt(1, 0, filter); // Init second filter...

	CAN0.init_Mask(1, 0, mask); // Init second mask...
	CAN0.init_Filt(2, 0, filter); // Init third filter...
	CAN0.init_Filt(3, 0, filter); // Init fouth filter...
	CAN0.init_Filt(4, 0, filter); // Init fifth filter...
	CAN0.init_Filt(5, 0, filter); // Init sixth filter...
}

void listen_to_all_id()
{
	CAN0.init_Mask(0, 0, 0); // Init first mask...
	CAN0.init_Filt(0, 0, 0); // Init first filter...
	CAN0.init_Filt(1, 0, 0); // Init second filter...

	CAN0.init_Mask(1, 0, 0); // Init second mask...
	CAN0.init_Filt(2, 0, 0); // Init third filter...
	CAN0.init_Filt(3, 0, 0); // Init fouth filter...
	CAN0.init_Filt(4, 0, 0); // Init fifth filter...
	CAN0.init_Filt(5, 0, 0); // Init sixth filter...
}

void listen_to_only_id_104()
{
	CAN0.init_Mask(0, 0, 0x00000111); // Init first mask...
	CAN0.init_Filt(0, 0, 0x00000104); // Init first filter...
}
