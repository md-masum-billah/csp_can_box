// CAN Receive Example
//
#define DEBUG_MODE 0
#include <mcp_can.h>
#include <SPI.h>


long unsigned int can_data_from_id;
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

int error_counter=0;
int error_count=0;
String t;


int CAN_NODE = 0x115;

void setup()
{
  Serial.begin(116500);
  can_init();

  // listen_to_only_id(0x115);
  // listen_to_all_id();
}

// char data[6] = "hello";

void loop()
{
  can_com_serial();
  // send_CAN(CAN_NODE,data);
  // delay(1);

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
