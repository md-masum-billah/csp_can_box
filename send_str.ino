
bool send_CAN(int transmitterID, String msgString)
{
	if (CAN0.checkError())
	{
		Serial.println("rcv error");
		error_count++;
		Serial.println(CAN0.getError());
	}
	if (error_count > 100)
	{
		// MCU_restart();
	}
  // Serial.println(sendBuffer);
	msgString = msgString + String('#');
	byte number_of_packets;
	byte packet_count = 0;
	char sendBuffer[255];
	int x = 0;


	if (msgString.length() % 8 == 0)
		number_of_packets = msgString.length() / 8;
	else
		number_of_packets = (msgString.length() / 8) + 1;

	Serial.print("sending ");
	Serial.print(number_of_packets);
	Serial.println(" packets");


	msgString.toCharArray(sendBuffer, msgString.length() + 1);

	// Serial.println(sendBuffer);
	// break the String into number of packets

	while (packet_count < number_of_packets)
	{
  #if DEBUG_MODE
		Serial.print("packet: ");
		Serial.println(packet_count + 1);
  #endif
		byte tempBuff[8];
		byte datapoints = 0;

		for (int i = 0; i < 8; i++)
		{
			if (sendBuffer[x] == '\0')
			{
				break;
			}
			// Serial.println(sendBuffer[x]);
			tempBuff[i] = sendBuffer[x];
			x++;
			datapoints++;
		}
		byte sndStat;
		sndStat = CAN0.sendMsgBuf(transmitterID, 0, datapoints, tempBuff);
    delay(3);
		if (sndStat == CAN_OK)
   { 
     #if DEBUG_MODE
			 Serial.println("sent");
    #endif
    }
		else
		{
			Serial.println("failed");
			error_count++;
			return false;
		}
		packet_count++;

	}

	return true;
}