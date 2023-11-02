void can_init(){
   // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.
  CAN0.enOneShotTX();
  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
}



void can_com_serial(){
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
  //   CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
  //   if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
  //     sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
  //   else
  //     sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
  //   Serial.print(msgString);
  
  //   if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
  //     sprintf(msgString, " REMOTE REQUEST FRAME");
  //     Serial.print(msgString);
  //   } else {
  //     for(byte i = 0; i<len; i++){
  //       sprintf(msgString, " 0x%.2X", rxBuf[i]);
  //       Serial.print(msgString);
  //     }
  //   }
    String k=receive_CAN_String();
    char prnt_str[100];
    sprintf(prnt_str, "Data from Node 0x%X :  " , can_data_from_id);

    Serial.print(prnt_str);

    Serial.print(k);
    can_data_from_id=-1;
  }
  if(Serial.available()){
    t=Serial.readString();
  }
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  // byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, t);
  // if(sndStat == CAN_OK){
  //   Serial.println("Message Sent Successfully!");
  // } else {
  //   Serial.println("Error Sending Message...");
  // }
  if(t!=""){
      char prnt_str[100];
      sprintf(prnt_str,"From this Node 0x%x :  " ,CAN_NODE);
      Serial.print(prnt_str);
      Serial.print(t);
      send_CAN(CAN_NODE,t);
      t="";
      delay(1);   // send data per 100ms
  }
}

void check_active_node(){
  send_CAN(CAN_NODE, "send_node_info");
  if(!digitalRead(CAN0_INT)){
    String k=receive_CAN_String();
    if(k=="send_node_info"){
      char prnt_str[100];
      sprintf(prnt_str,"my info From Node 0x%x :  " ,CAN_NODE);
      send_CAN(CAN_NODE, prnt_str);
    }
    else
    {
      String k=receive_CAN_String();
      Serial.println(k);
    }
  }
}