#include "private_parse.h"
#include "ota-client-policy-config.h"

#define PRIVE_ZUBAO 0


#if PRIVE_ZUBAO

typedef struct {
//  uint8_t  cmd;
  uint8_t   enable;        // Command serial number
  int      seq;        // Command serial number
  uint8_t  all_pack;   // Total package quantity
  uint8_t  pack_seq;   // Received packet serial number
  uint8_t  pack_num;   // Number of packages received
  uint8_t  pack_dat[10][75];   //Subcontract storage
  uint8_t  pack_len[10];       //Packet data length
  uint8_t  all_dat[750];       //Turnkey storage
  uint16_t offset;             //Total package offset bit
} G_PARSE_T; // Parse structure


#define  BUFF_PARSE   3
G_PARSE_T parse_data[BUFF_PARSE] ={0};
int findDataBySeq(int seq);
int findEmptyData(void);
#endif





uint8_t  send_out[EMBER_AF_PLUGIN_FRAGMENTATION_BUFFER_SIZE]={0};
uint16_t out_idx =0;
static uint8_t seq=0;

void report_hearbeat(void)
{
  uint8_t  out[6] ={0xff,0x99,0x01,0x01,0x00,0x00};
  uint8_t  idx =0;
  out[idx++] = 0xff;
  out[idx++] = 0x99;//
  out[idx++] = seq++;
  out[idx++] = 0x01; // Total number of packages
  out[idx++] = 0x00; // Packet serial number
  out[idx++] = EMBER_AF_PLUGIN_OTA_CLIENT_POLICY_FIRMWARE_VERSION;  //version number

  report_agreement(out,idx);
}

//Fill in the data packet header, pass in the packet body, and throw the data packet out.
void make_gateway_frame(uint8_t cmd,uint8_t num,void *val,uint16_t len)
{
  uint8_t  out[EMBER_AF_PLUGIN_FRAGMENTATION_BUFFER_SIZE]={0};

  uint16_t idx =0;
//  uint16_t  i;
  out[idx++] = 0xff;
  out[idx++] = cmd;
  out[idx++] = seq++;
  out[idx++] = 0x01; // Total number of packages
  out[idx++] = 0x00; // Packet serial number
  out[idx++] = num;  //DP quantity

  uint8_t *val_ptr = (uint8_t*)val;

  if ((len > 0) && val_ptr) {
      memcpy(out+idx, val_ptr, len);
  }

  len += idx;

   report_agreement(out,len);
}


void report_power_memory(uint8_t num,uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;

  if(num ==1){
     send_out[(*idx)++] = DP_1_POWER_MEMORY;
  }else if(num ==2){
     send_out[(*idx)++] = DP_2_POWER_MEMORY;
  }else if(num ==3){
     send_out[(*idx)++] = DP_3_POWER_MEMORY;
  }
  send_out[(*idx)++] = PROP_ENUM;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  if(num ==1){
     send_out[(*idx)++] = tpUserControl->power_memory_1;
  }else if(num ==2){
     send_out[(*idx)++] = tpUserControl->power_memory_2;
  }else if(num ==3){
     send_out[(*idx)++] = tpUserControl->power_memory_3;
  }
}

void report_countdown(uint8_t num,uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =4;
  uint8_t dat[4]={0};
  if(num ==1){
     send_out[(*idx)++] = DP_1_COUNTDOWN;
  }else if(num ==2){
     send_out[(*idx)++] = DP_2_COUNTDOWN;
  }else if(num ==3){
     send_out[(*idx)++] = DP_3_COUNTDOWN;
  }
  send_out[(*idx)++] = PROP_INT;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;

  if(num ==1){
    INT32_TO_LE_BYTES(tpUserControl->Count_Down_1,dat);
  }else if(num ==2){
    INT32_TO_LE_BYTES(tpUserControl->Count_Down_2,dat);
  }else if(num ==3){
    INT32_TO_LE_BYTES(tpUserControl->Count_Down_3,dat);
  }


  memcpy(send_out+(*idx), dat, 4);
  (*idx)+=4;


  printf("report Count_Down%d %ld \n",num,tpUserControl->Count_Down_1);
}




void report_cmd_countdown(uint8_t num)
{
  uint8_t  send_out[15]={0};
  uint16_t idx =0;

  report_countdown(num,send_out,&idx);
  make_gateway_frame(CMD_DEVICE_REPORT_STATUS,1,send_out,idx);
}


void report_switch1(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_1_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Onoff_1;

  printf("report Onoff_1 %d \n",tpUserControl->Onoff_1);
}
void report_switch2(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_2_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Onoff_2;

  printf("report Onoff_2 %d \n",tpUserControl->Onoff_2);
}
void report_switch3(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_3_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Onoff_3;

  printf("report Onoff_3 %d \n",tpUserControl->Onoff_3);
}
void report_switch4(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_4_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Onoff_4;

  printf("report Onoff_4 %d \n",tpUserControl->Onoff_4);
}
void report_switch16(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_BACK_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->backlight_16;

  printf("report backlight_16 %d \n",tpUserControl->backlight_16);
}

#if 0
void report_switch(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_1_SWTICH;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;   //little endian
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Onoff;

  printf("report Onoff %d \n",tpUserControl->Onoff);
}


void report_work_mode(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  //uint8_t dat[4]={0};
  send_out[(*idx)++] = DP_2_Work_Mode;
  send_out[(*idx)++] = PROP_ENUM;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = 0x30;	//only one page
 // INT32_TO_LE_BYTES(0x30,dat);

 // printf("report work_mode %d \n",tpUserControl->work_mode);
 // memcpy(send_out+(*idx), dat, 4);
 // (*idx)+=4;
}

void report_lihgt(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =4;
  uint8_t dat[4]={0};
  send_out[(*idx)++] = DP_3_Bright;
  send_out[(*idx)++] = PROP_INT;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  INT32_TO_LE_BYTES((tpUserControl->Brightness*10),dat);
  printf("report light %d \n",tpUserControl->Brightness*10);
  memcpy(send_out+(*idx), dat, 4);
  (*idx)+=4;
}


void report_temp(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =4;
  uint8_t dat[4]={0};
  send_out[(*idx)++] = DP_4_TEMP;
  send_out[(*idx)++] = PROP_INT;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  INT32_TO_LE_BYTES(tpUserControl->Color_Temp,dat);
  printf("report Color_Temp %d \n",tpUserControl->Color_Temp);

  memcpy(send_out+(*idx), dat, 4);
  (*idx)+=4;
}


void report_hsv(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =6;
  send_out[(*idx)++] = DP_5_COLOUR;
  send_out[(*idx)++] = PROP_RAW;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->Color_H >>8;
  send_out[(*idx)++] = tpUserControl->Color_H;

  send_out[(*idx)++] = tpUserControl->Color_S >>8;
  send_out[(*idx)++] = tpUserControl->Color_S;

  send_out[(*idx)++] = tpUserControl->Color_V >>8;
  send_out[(*idx)++] = tpUserControl->Color_V;

  printf("report hsv %d  %d  %d  \n",tpUserControl->Color_H,tpUserControl->Color_S,tpUserControl->Color_V);
}



void report_countdown(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =4;
  uint8_t dat[4]={0};
  send_out[(*idx)++] = DP_7_COUNTDOWN;
  send_out[(*idx)++] = PROP_INT;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;

  INT32_TO_LE_BYTES(tpUserControl->Count_Down,dat);

  memcpy(send_out+(*idx), dat, 4);
  (*idx)+=4;


  printf("report Count_Down %ld \n",tpUserControl->Count_Down);
}




void report_not_disturb(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =1;
  send_out[(*idx)++] = DP_34_DO_NOT_DISTURB;
  send_out[(*idx)++] = PROP_BOOL;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;
  send_out[(*idx)++] = tpUserControl->not_disturb;

  printf("report not_disturb %d \n",tpUserControl->not_disturb);

}

void report_menmory(uint8_t *send_out,uint16_t* idx)
{
  uint8_t len =12;
  send_out[(*idx)++] = DP_33_POWER_MEMORY;
  send_out[(*idx)++] = PROP_RAW;
  send_out[(*idx)++] = len;
  send_out[(*idx)++] = len>>8;

  send_out[(*idx)++] = 0;   //version number
  send_out[(*idx)++] = tpUserControl->memory.mode;  //model

  //hsv
  send_out[(*idx)++] = tpUserControl->memory.Color_H >>8;
  send_out[(*idx)++] = tpUserControl->memory.Color_H;

  send_out[(*idx)++] = tpUserControl->memory.Color_S >>8;
  send_out[(*idx)++] = tpUserControl->memory.Color_S;

  send_out[(*idx)++] = tpUserControl->memory.Color_V >>8;
  send_out[(*idx)++] = tpUserControl->memory.Color_V;

  uint16_t  Brightness = tpUserControl->memory.Brightness*10;
  send_out[(*idx)++] = Brightness >>8;
  send_out[(*idx)++] = Brightness;


  uint16_t  Color_Temp = ((tpUserControl->memory.Color_Temp -2700)*10) /38;
  send_out[(*idx)++] = Color_Temp >>8;
  send_out[(*idx)++] = Color_Temp;


  printf("report menmory %d  HSV  %d  %d  %d  light %d  temp %d  \n",tpUserControl->memory.mode,tpUserControl->memory.Color_H,
         tpUserControl->memory.Color_S,tpUserControl->memory.Color_V,tpUserControl->memory.Brightness,tpUserControl->memory.Color_Temp);

}

void report_cmd_countdown(void)
{
  uint8_t  send_out[15]={0};
  uint16_t idx =0;

  report_countdown(send_out,&idx);
  make_gateway_frame(CMD_DEVICE_REPORT_STATUS,1,send_out,idx);
}
#endif

void report_all_data(void)
{
  if(emberAfNetworkState() != EMBER_JOINED_NETWORK){
      sl_zigbee_app_debug_println("report_all_data no network return report:%d\r\n");
      return;
  }
  uint8_t  send_out[EMBER_AF_PLUGIN_FRAGMENTATION_BUFFER_SIZE]={0};
  uint16_t idx =0;
  uint8_t  dp_num =0;
  //报开关
#if(SWITCH_NUM >=1)
    report_switch1(send_out,&idx);
    dp_num ++;
    report_countdown(1,send_out,&idx);
    dp_num ++;
    report_power_memory(1,send_out,&idx);
    dp_num ++;
#endif
#if(SWITCH_NUM >=2)
    report_switch2(send_out,&idx);
    dp_num ++;
    report_countdown(2,send_out,&idx);
    dp_num ++;
    report_power_memory(2,send_out,&idx);
    dp_num ++;
#endif
#if(SWITCH_NUM >=3)
    report_switch3(send_out,&idx);
    dp_num ++;
    report_countdown(3,send_out,&idx);
    dp_num ++;
    report_power_memory(3,send_out,&idx);
    dp_num ++;
#endif
#if(SWITCH_NUM >=4)
    report_switch4(send_out,&idx);
    dp_num ++;
#endif
    report_switch16(send_out,&idx);
    dp_num ++;


//  report_switch(send_out,&idx);
//  dp_num ++;
//  report_work_mode(send_out,&idx);
//  dp_num ++;
//  report_lihgt(send_out,&idx);
//  dp_num ++;
 // report_temp(send_out,&idx);
//  dp_num ++;
//  report_hsv(send_out,&idx);
//  dp_num ++;
//  report_countdown(send_out,&idx);
//  dp_num ++;
//  report_menmory(send_out,&idx);
//  dp_num ++;
//  report_not_disturb(send_out,&idx);
//  dp_num ++;

  sl_zigbee_app_debug_println("report_all_data start: len %d %d \r\n",idx,dp_num);
  make_gateway_frame(CMD_DEVICE_REPORT_STATUS,dp_num,send_out,idx);
#if 0
  switch()
  {
    case PROP_BOOL:    //1 byte
      break;
    case PROP_INT:
    break;
    case PROP_FLOAT:
      break;
    case PROP_ENUM:
      break;
    case PROP_FAULT:
      break;
    case PROP_TEXT:
      break;
    case PROP_RAW:
      break;
    case PROP_STRUCT:
      break;
    case PROP_ARRAY:
      break;
    default:break;
  }
#endif
}



void make_rec_report(uint8_t cmd, void *val,uint16_t len)
{
#if 1
  uint8_t  send_out[EMBER_AF_PLUGIN_FRAGMENTATION_BUFFER_SIZE]={0};
  uint16_t idx =0;
  uint16_t  i,j;
  send_out[idx++] = 0xff;
  send_out[idx++] = cmd;
  send_out[idx++] = seq++;
  //  val_ptr[idx++] = 0x01; // Total number of packages
  //  val_ptr[idx++] = 0x01; // Packet serial number   //Only modify this part of the package, and find the original data for the rest and send it out.
    idx++;
    idx++;
  j=idx;
  uint8_t *val_ptr = (uint8_t*)val;
  for (i = j; i < (len); i++) {
      send_out[idx++] = val_ptr[i]; // Dereference pointer to obtain data
    //  sl_zigbee_app_debug_println(" rport val_ptr[i]: 0x%02X\n",val_ptr[i]);
  }

  report_agreement(send_out,idx);
#else
  uint8_t *val_ptr = (uint8_t*)val;
  uint16_t idx =0;

  val_ptr[idx++] = 0xff;
  val_ptr[idx++] = cmd;
  val_ptr[idx++] = seq++;
//  val_ptr[idx++] = 0x01; // Total number of packages
//  val_ptr[idx++] = 0x01; // Packet serial number   //Only modify this part of the package, and find the original data for the rest and send it out.
  idx++;
  idx++;


  sl_zigbee_app_debug_println("recv report :\n");
  for (int i = 0; i < (len); i++) {
     //  send_out[idx++] = val_ptr[i]; // Dereference pointer to obtain data
    sl_zigbee_app_debug_print(" 0x%02X",val_ptr[i]);
  }
  sl_zigbee_app_debug_println("\n");
  report_agreement(send_out,len);
#endif
}


//Set random number seed
void set_rand_source(void)
{
  uint16_t SHORT_ID =  emberAfGetNodeId();
  srand(SHORT_ID);
  sl_zigbee_app_debug_println("SHORT_ID =0x%2x   \n",SHORT_ID);
//  EmberEUI64 eui;
//  emberAfGetEui64(eui);
//  emberAfPrintBigEndianEui64(eui);
}


// Analytic Functions
uint16_t HeartbeatTime =0;
uint32_t Save_HbTime =0;
void parseProtocol(uint8_t *data, uint16_t length) {
    // Check the header
    static uint8_t init_srand =0;
    // Get command word

    uint8_t  send_out[512]={0};
    uint8_t  dp_count =0;
    uint16_t idx =0;

    uint8_t cmd = data[1];

    uint8_t i = 0;
  //  uint8_t x=0, j = 0;
    uint8_t dpNum = 0;
    uint8_t dpid_dp = 0;
    uint16_t dpid_len = 0;
    uint8_t type = 0;
    uint8_t dataIndex = 0;
    uint32_t utc_temp   =0;

 //   uint8_t switch_num = 0; //Number of nodes
   // uint8_t rhythm_onoff =0;  //Rhythm switch
  //  uint16_t temp = 0; //
    switch (cmd) {
     //   case CMD_HEARTBEAT:
        case CMD_DEVICE_PING:
            printf("Received Heartbeat\n");
            dataIndex =5; //Header information is not required
            //little endian
            if(!init_srand){
                init_srand =1;
                set_rand_source();
                report_all_data();    //The first ping reports device status
            }
          //  uint32_t utc_temp = (uint32_t)((data[dataIndex]) | (data[dataIndex + 1] << 8) | (data[dataIndex + 2] << 16) | (data[dataIndex + 3] << 24));
            utc_temp = LE_BYTES_TO_INT32(&data[dataIndex]);
            dataIndex+=4;
            uint8_t Divisor = data[dataIndex++];
            uint8_t Remainder = data[dataIndex++];
            uint8_t Max = data[dataIndex++];
            uint8_t BaseTime = data[dataIndex++];
            uint16_t SHORT_ID =  emberAfGetNodeId();  //Device short address
            sl_zigbee_app_debug_println("Divisor %d SHORT_ID =0x%2x  BaseTime %d Max %d\n",Divisor,SHORT_ID,BaseTime,Max);

            sl_zigbee_app_debug_println("(SHORT_ID '%' Divisor) =%d  Remainder %d \n",(SHORT_ID % Divisor),Remainder);
            if((SHORT_ID % Divisor) == Remainder){
                HeartbeatTime =BaseTime * (rand()%(Max+1));
                if(!HeartbeatTime){
                    report_hearbeat();
                }else{
                    Save_HbTime  = halCommonGetInt32uMillisecondTick();
                    sl_zigbee_app_debug_println(" ===  HeartbeatTime %d  Save_HbTime =%d \n",HeartbeatTime,Save_HbTime);
                }
            }

            break;


        case CMD_GATEWAY_COMMAND:
            printf("Received CMD_GATEWAY_COMMAND\n");
            // Get DP quantity
            dataIndex = 5;
            dpNum = data[dataIndex++];
            // Parse DP data starting from the 7th byte
            for (i = 0; i < dpNum; i++) {

                dpid_dp = data[dataIndex++];
                type    = data[dataIndex++];
                dpid_len = ((data[dataIndex+1] << 8) | data[dataIndex]);
                dataIndex += 2;

                printf("DPID: %d, type %d Len: %d,i %d  daNum %d  Data: \n", dpid_dp,type, dpid_len,i,dpNum);

                // Process dp data
             //   for (j = 0; j < dpid_len; j++) {
                    switch(dpid_dp)
                    {
                      case DP_1_SWTICH:
                       tpUserControl->Onoff_1 = data[dataIndex++];

                       printf("SWTICH:  %d\n",tpUserControl->Onoff_1);
                        break;
                      case DP_2_SWTICH:
                       tpUserControl->Onoff_2 = data[dataIndex++];

                       printf("SWTICH2:  %d\n",tpUserControl->Onoff_2);
                        break;
                      case DP_3_SWTICH:
                       tpUserControl->Onoff_3 = data[dataIndex++];

                       printf("SWTICH3:  %d\n",tpUserControl->Onoff_3);
                        break;
                      case DP_4_SWTICH:
                       tpUserControl->Onoff_4 = data[dataIndex++];

                       printf("SWTICH4:  %d\n",tpUserControl->Onoff_4);
                        break;
                      case DP_BACK_SWTICH:
                       tpUserControl->backlight_16 = data[dataIndex++];

                       printf("SWTICH16:  %d\n",tpUserControl->backlight_16);
                      case DP_1_COUNTDOWN:
                        tpUserControl->Count_Down_1 = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24));
                        dataIndex+=4;
                        printf("Count_Down1:  %ld\n",tpUserControl->Count_Down_1);
                        break;
                      case DP_2_COUNTDOWN:
                        tpUserControl->Count_Down_2 = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24));
                        dataIndex+=4;
                        printf("Count_Down2:  %ld\n",tpUserControl->Count_Down_2);
                        break;
                      case DP_3_COUNTDOWN:
                        tpUserControl->Count_Down_3 = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24));
                        dataIndex+=4;
                        printf("Count_Down3:  %ld\n",tpUserControl->Count_Down_3);
                        break;
                      case DP_1_POWER_MEMORY:
                        tpUserControl->power_memory_1 = data[dataIndex++];  //model
                        printf("memory1:  %x\n",tpUserControl->power_memory_1);
                        break;
                      case DP_2_POWER_MEMORY:
                        tpUserControl->power_memory_2 = data[dataIndex++];  //model
                        printf("memory1:  %x\n",tpUserControl->power_memory_1);
                        break;
                      case DP_3_POWER_MEMORY:
                        tpUserControl->power_memory_3 = data[dataIndex++];  //model
                        printf("memory1:  %x\n",tpUserControl->power_memory_1);
                        break;
                      case DP_37_LED_STATE:
                        tpUserControl->backlight_mode = data[dataIndex++];  //model
                        printf("backlight_mode:  %x\n",tpUserControl->backlight_mode);
                        break;
#if 0
                      case DP_2_Work_Mode:
                        tpUserControl->work_mode= data[dataIndex++];

                       printf("Work_Mode:  %d\n",tpUserControl->work_mode);
                        break;

                      case DP_3_Bright:
                   //     tpUserControl->led_mode  =0;
                        //小端
                        tpUserControl->Brightness = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24))/10;
                        dataIndex+=4;
                        execute_led_change_cal(300);
                        printf("Brightness:    %d, \n",tpUserControl->Brightness);
                        break;
                      case DP_4_TEMP:
               //         tpUserControl->led_mode  =0;
                        //小端
                        tpUserControl->Color_Temp = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24));
                        dataIndex+=4;
               //         printf("TEMP:    %d, LED %d \n",  tpUserControl->Color_Temp , tpUserControl->led_mode);

                        execute_led_change_cal(300);

                        break;

                      case DP_5_COLOUR:

                        tpUserControl->led_mode  =1;
                        tpUserControl->Color_H = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                        dataIndex += 2;
                        tpUserControl->Color_S = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                        dataIndex += 2;
                        tpUserControl->Color_V = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                        dataIndex += 2;

                        printf("COLOR:   H %d, S %d V: %d \n",  tpUserControl->Color_H , tpUserControl->Color_S ,  tpUserControl->Color_V);
                        execute_led_change_cal(500);
                        break;
                      case DP_6_SCENE:
                        switch(data[dataIndex++]){
                          case 0x00: //Good night
                            tpUserControl->scen_mode = 1;
                            break;
                          case 0x01: //read
                            tpUserControl->scen_mode = 2;
                            break;
                          case 0x02: //Work
                            tpUserControl->scen_mode = 3;
                            break;
                          case 0x03: //Leisure
                            tpUserControl->scen_mode = 4;
                            break;
                          case 0x18: //sunflower
                            tpUserControl->scen_mode = 6;
                            break;
                          case 0x04: //grassland
                            tpUserControl->scen_mode = 7;
                            break;
                          case 0x06: //Colorful
                            tpUserControl->scen_mode = 8;
                            break;
                          case 0x17: //ocean
                            tpUserControl->scen_mode = 5;
                            break;
                          default:
                            break;
                        }
                        count_100ms =40;
                        set_scen_hsv_led_mode(tpUserControl->scen_mode);
                        set_scen_cw_led_mode(tpUserControl->scen_mode);
                        dataIndex += 26;

                        printf("scen_mode:  %d\n",tpUserControl->scen_mode);
                        break;
                      case DP_7_COUNTDOWN:

                        tpUserControl->Count_Down = ((uint32_t)(data[dataIndex] | (data[dataIndex+1] << 8) | (data[dataIndex+2] << 16)) | (data[dataIndex+3] << 24));

                        dataIndex+=4;
                        printf("Count_Down:  %ld\n",tpUserControl->Count_Down);
                        break;
                      case DP_9_CONTROL:
                      dataIndex+=21;
                        break;
                #if  0
                      case DP_30_RHYTHM:
                        dataIndex++;    //Throw away the version number

                        dataIndex++;  //task switch  8
                        dataIndex++;  //changing pattern 9
                        dataIndex++;  //date setting  10
                        switch_num = data[dataIndex++];   //Number of nodes

                        for(x=0;x<switch_num;x++){
                            tpUserControl->bio_rhythm.onoff[x] = data[8];   //Node task switch
                            tpUserControl->bio_rhythm.week[x][0] = data[10]; //Task date setting
                            dataIndex++;  //节点开关  扔掉
                         //   tpUserControl->bio_rhythm.execution_time[x] = 300000 * data[dataIndex++]; //Gradient time setting 1=5 minutes, 2=ten minutes ...
                            tpUserControl->bio_rhythm.hours[x] = data[dataIndex++];   //Execution hour time point
                            tpUserControl->bio_rhythm.minutes[x] = data[dataIndex++]; //Minutes of execution Time point
                            if(data[dataIndex + 3] ==0){                          //Brightness V =0, represents non-colored light data
                                dataIndex += 4; //Jump to the brightness percentage position
                                tpUserControl->bio_rhythm.led_mode[x]  =0;
                                tpUserControl->bio_rhythm.mode_data[x][2] = data[dataIndex++];  //brightness
                                temp = 2700 + (38* data[dataIndex++]);   //Color temperature value
                                tpUserControl->bio_rhythm.mode_data[x][0] = temp >>8;  //High color temperature
                                tpUserControl->bio_rhythm.mode_data[x][1] = temp;  //Low color temperature
                            }else{
                                tpUserControl->bio_rhythm.led_mode[x]  =1;
                                temp = (data[dataIndex]*100 +  data[dataIndex +1]);   //Hue hundreds and tens ones
                                tpUserControl->bio_rhythm.mode_data[x][0] = temp >>8;  //h_H
                                tpUserControl->bio_rhythm.mode_data[x][1] = temp;      //h_L
                                dataIndex+=2;

                                tpUserControl->bio_rhythm.mode_data[x][2] = data[dataIndex++];  //s
                                tpUserControl->bio_rhythm.mode_data[x][3] = data[dataIndex++];  //v
                                dataIndex+=2;   //Add the data location of color temperature and brightness
                            }
                        }

                        break;
            #endif

            #if  0
                      case DP_31_ASLEEP:
                        dataIndex++;    //Throw away the version number
                        switch_num = data[dataIndex++]; //Number of nodes
                        for(x=0;x<switch_num;x++){
                            tpUserControl->asleep.onoff[x] = data[dataIndex++]; //Node task switch
                            tpUserControl->asleep.week[x][0] = data[dataIndex++]; //Task date setting
                            tpUserControl->asleep.execution_time[x] = 300000 * data[dataIndex++]; //Gradient time setting 1=5 minutes, 2=ten minutes ...
                            tpUserControl->asleep.hours[x] = data[dataIndex++]; //Execution hour time point
                            tpUserControl->asleep.minutes[x] = data[dataIndex++]; //Minutes of execution Time point
                            if(data[dataIndex + 3] ==0){                          //Brightness V =0, represents non-colored light data
                                dataIndex += 4; //Jump to the brightness percentage position
                                tpUserControl->asleep.led_mode[x]  =0;
                                tpUserControl->asleep.mode_data[x][2] = data[dataIndex++];  //brightness
                                temp = 2700 + (38* data[dataIndex++]);   //Color temperature value
                                tpUserControl->asleep.mode_data[x][0] = temp >>8;  //High color temperature
                                tpUserControl->asleep.mode_data[x][1] = temp;  //Low color temperature
                            }else{
                                tpUserControl->asleep.led_mode[x]  =1;
                                temp = (data[dataIndex]*100 +  data[dataIndex +1]);   //Hue hundreds and tens ones
                                tpUserControl->asleep.mode_data[x][0] = temp >>8;  //h_H
                                tpUserControl->asleep.mode_data[x][1] = temp;      //h_L
                                dataIndex+=2;

                                tpUserControl->asleep.mode_data[x][2] = data[dataIndex++];  //s
                                tpUserControl->asleep.mode_data[x][3] = data[dataIndex++];  //v
                                dataIndex+=2;   //Hue hundreds and tens ones
                            }
                        }
                        break;
                      case DP_32_WAKEUP:
                        dataIndex++;    //Throw away the version number
                        switch_num = data[dataIndex++]; //Number of nodes
                        for(x=0;x<switch_num;x++){
                            tpUserControl->awaken.onoff[x] = data[dataIndex++]; //Node task switch
                            tpUserControl->awaken.week[x][0] = data[dataIndex++]; //Task date setting
                            tpUserControl->awaken.execution_time[x] = 300000 * data[dataIndex++]; //Gradient time setting 1=5 minutes, 2=ten minutes ...
                            tpUserControl->awaken.hours[x] = data[dataIndex++]; //Execution hour time point
                            tpUserControl->awaken.minutes[x] = data[dataIndex++]; //Minutes of execution Time point
                            if(data[dataIndex + 3] ==0){                          //Brightness V =0, represents non-colored light data
                                dataIndex += 4; //Jump to the brightness percentage position
                                tpUserControl->awaken.led_mode[x]  =0;
                                tpUserControl->awaken.mode_data[x][2] = data[dataIndex++];  //brightness
                                temp = 2700 + (38* data[dataIndex++]);   //Color temperature value
                                tpUserControl->awaken.mode_data[x][0] = temp >>8;  //High color temperature
                                tpUserControl->awaken.mode_data[x][1] = temp;  //Low color temperature
                            }else{
                                tpUserControl->awaken.led_mode[x]  =1;
                                temp = (data[dataIndex]*100 +  data[dataIndex +1]);   //Hue hundreds and tens ones
                                tpUserControl->awaken.mode_data[x][0] = temp >>8;  //h_H
                                tpUserControl->awaken.mode_data[x][1] = temp;      //h_L
                                dataIndex+=2;

                                tpUserControl->awaken.mode_data[x][2] = data[dataIndex++];  //s
                                tpUserControl->awaken.mode_data[x][3] = data[dataIndex++];  //v
                                dataIndex+=2;   //Add the data location of color temperature and brightness
                            }
                            tpUserControl->awaken.continue_time[x] =  data[dataIndex++]*5;  //Status maintenance time: 5 minutes in steps

                        }

                        break;
            #endif
                      case DP_33_POWER_MEMORY:
                        dataIndex++;    //Throw away the version number
                        tpUserControl->memory.mode = data[dataIndex++];  //model


                        if(tpUserControl->memory.mode == 2){
                            tpUserControl->memory.Color_H = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                            dataIndex += 2;
                            tpUserControl->memory.Color_S = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                            dataIndex += 2;
                            tpUserControl->memory.Color_V = ((data[dataIndex] << 8) | data[dataIndex + 1]);
                            dataIndex += 2;



                            tpUserControl->memory.Brightness = ((data[dataIndex] << 8) | data[dataIndex + 1])/10;
                            dataIndex += 2;
                            tpUserControl->memory.Color_Temp = 2700 + (38*((data[dataIndex] << 8) | data[dataIndex + 1])/10);
                            dataIndex += 2;
                            if((tpUserControl->memory.Color_Temp ==0) && (tpUserControl->memory.Brightness==0)){   //hsv data
                                tpUserControl->memory.led_mode = 1;
                            }else{      //Color temperature data
                                tpUserControl->memory.led_mode = 0;
                            }
                            if(tpUserControl->memory.Brightness == 0){
                                tpUserControl->memory.Brightness =50;
                            }
                        }

                        printf("POWER_MEMORY: mode %d led_mode %d  hsv %d %d %d liht %d  temp %d\n",tpUserControl->memory.mode,tpUserControl->memory.led_mode,  tpUserControl->memory.Color_H,
                               tpUserControl->memory.Color_S,tpUserControl->memory.Color_V,tpUserControl->memory.Brightness,tpUserControl->memory.Color_Temp);
                        break;
                      case DP_34_DO_NOT_DISTURB:
                        tpUserControl->not_disturb = data[dataIndex++];
                        printf("DP_34_DO_NOT_DISTURB:  %d\n",tpUserControl->not_disturb);
                        break;
                      case DP_35_SWTICH_GRADIENT:

                        dataIndex++;    //Throw away the version number

                        tpUserControl->On_buff =data[dataIndex++];
                        tpUserControl->Off_buff =data[dataIndex++];
                        break;
#endif
                      default:break;
                    }
          //      }


            }

            //Change the received data into a command word and send it back directly
            make_rec_report(CMD_DEVICE_REPORT_STATUS,data,length);
            set_write_flag(1);
            break;


        case CMD_DEVICE_STATUS_QUERY:
                      // Parse DP data starting from the 7th byte
          dataIndex = 5;
          dpNum = data[dataIndex++];
          if(dpNum == 0){ //Report all status
              //Report all DP points
              report_all_data();
              return;
          }
          for (i = 0; i < dpNum; i++) {
              dpid_dp = data[dataIndex++];
              printf("DPID: %d \n", dpid_dp);
              // Process dp data
              switch(dpid_dp)
              {
                case DP_1_SWTICH:
                  report_switch1(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH1:  %d\n",tpUserControl->Onoff_1);
                  break;
                case DP_2_SWTICH:
                  report_switch2(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH2:  %d\n",tpUserControl->Onoff_2);
                  break;
                case DP_3_SWTICH:
                  report_switch3(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH3:  %d\n",tpUserControl->Onoff_3);
                  break;
                case DP_4_SWTICH:
                  report_switch4(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH4:  %d\n",tpUserControl->Onoff_4);
                  break;
                case DP_BACK_SWTICH:
                  report_switch16(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH16:  %d\n",tpUserControl->backlight_16);
                case DP_1_COUNTDOWN:
                  report_countdown(1,send_out,&idx);
                  dp_count ++;
                  break;
                case DP_2_COUNTDOWN:
                  report_countdown(2,send_out,&idx);
                  dp_count ++;
                  break;
                case DP_3_COUNTDOWN:
                  report_countdown(3,send_out,&idx);
                  dp_count ++;
                  break;

                case DP_1_POWER_MEMORY:
                  report_power_memory(1,send_out,&idx);
                  dp_count ++;
                  break;
                case DP_2_POWER_MEMORY:
                  report_power_memory(2,send_out,&idx);
                  dp_count ++;
                  break;
                case DP_3_POWER_MEMORY:
                  report_power_memory(3,send_out,&idx);
                  dp_count ++;
                  break;
#if 0
                case DP_1_SWTICH:
                  report_switch(send_out,&idx);
                  dp_count ++;
                  printf("SWTICH:  %d\n",tpUserControl->Onoff);
                  break;
                case DP_2_Work_Mode:
                  report_work_mode(send_out,&idx);
                  dp_count ++;
             //    printf("Work_Mode:  %d\n",tpUserControl->work_mode);
                  break;
                case DP_3_Bright:
                  report_lihgt(send_out,&idx);
                  dp_count ++;
                  printf("Brightness:    %d, \n",tpUserControl->Brightness);
                  break;
                case DP_4_TEMP:
               //   report_temp(send_out,&idx);
               //   dp_count ++;
               //   printf("TEMP:    %d, LED %d \n",  tpUserControl->Color_Temp , tpUserControl->led_mode);
                  break;
                case DP_5_COLOUR:
               //   report_hsv(send_out,&idx);
               //   dp_count ++;
               //   printf("COLOR:   H %d, S %d V: %d \n",  tpUserControl->Color_H , tpUserControl->Color_S ,  tpUserControl->Color_V);
                  break;
                case DP_6_SCENE:
               //   printf("scen_mode:  %d\n",tpUserControl->scen_mode);
                  break;
                case DP_7_COUNTDOWN:
               //   report_countdown(send_out,&idx);
               //   dp_count ++;
               //   printf("Count_Down:  %ld\n",tpUserControl->Count_Down);
                  break;
                case DP_9_CONTROL:
                  break;
                case DP_30_RHYTHM:
                  break;
                case DP_31_ASLEEP:
                  break;
                case DP_32_WAKEUP:
                  break;
                case DP_33_POWER_MEMORY:
                //  report_menmory(send_out,&idx);
                  dp_count ++;
                  break;
                case DP_34_DO_NOT_DISTURB:
                //  report_not_disturb(send_out,&idx);
                  dp_count ++;
                  break;
                case DP_35_SWTICH_GRADIENT:
                  break;
#endif
                case 0xff:  //Report all DP points
                  report_all_data();
                  return;
                  break;
                default: break;
              }
           }

          sl_zigbee_app_debug_println("report_all_data start: len %d\r\n",idx);
          make_gateway_frame(CMD_DEVICE_REPORT_STATUS,dp_count,send_out,idx);
            break;
        // Process other commands
        default:

            printf("Unknown command: 0x%02X\n", cmd);
            break;
    }
}





//Private protocol analysis entry
void zigbee_Private_Trasmit_Parse(uint8_t endpoint,
                                  EmberAfClusterId cluster,
                                  EmberAfAttributeId attributeID,
                                  uint8_t *dataPtr,
                                  uint16_t readLength)
{

 // uint8_t *data =  dataPtr;
 // uint8_t all_pack=0,pack_seq=0,cmd_seq=0;
//
//  sl_zigbee_app_debug_println("endpoint=%x  cluster=%x  attributeID=%x  readLength =%d \n",endpoint,cluster,attributeID,readLength);

 //   cmd_seq = data[3];    //The first digit in the data is the total length, all starting from 3,
 //   all_pack = data[4];
  //  pack_seq = data[5];

//    printf("cmd_seq = %d all_pack = %d  pack_seq = %d  ", cmd_seq, all_pack, pack_seq);

    parseProtocol(dataPtr, readLength); //Directly analyze the obtained data
    //The byte-defined reassembly packet protocol does not need to be used
#if PRIVE_ZUBAO
    if(all_pack == 0){ //No subcontracting
        parseProtocol(dataPtr, readLength); //Directly analyze the obtained data
 //       printf("no pack\n");
    } else {
        int seq=-1;
        seq = findDataBySeq(cmd_seq);
        if (seq == -1) {//The new seq does not match any records
            seq = findEmptyData();
            if (seq == -1) {
                printf("store full\n");
                return;
            }
            parse_data[seq].seq = cmd_seq;
            parse_data[seq].enable = 1;
        }
        //If there is a matching or empty storage space available, save the data.

   //     printf("start fenbao seq = %d \n", seq);
        memset(parse_data[seq].pack_dat[pack_seq], 0, 75);
        if (pack_seq) {//If it is not the first package, remove the 6-digit header number.
            readLength -= 6;                           //Remove the header code from the data and place it into the subpackage array
            memcpy(parse_data[seq].pack_dat[pack_seq], (uint8_t*) &dataPtr[6], (readLength));
        } else {                                       //Place all data into packed array
            memcpy(parse_data[seq].pack_dat[pack_seq], dataPtr, readLength);
        }

        //Memorize the length of each package
        parse_data[seq].pack_len[pack_seq] = readLength;

    //    printf("pack_num = %d  pack_len = %d \n", parse_data[seq].pack_num, parse_data[seq].pack_len[pack_seq]);

        //After all packets have been received, start grouping the packets and send them for analysis.。
        if (parse_data[seq].pack_num == all_pack) {
            parse_data[seq].offset = 0;                 //Guaranteed to start the package from scratch

            for (uint8_t i = 0; i <= all_pack; i++) {
                //Put the sub-packages into the general package in order and by location
                memcpy((uint8_t*) parse_data[seq].all_dat + parse_data[seq].offset,
                       (uint8_t*) parse_data[seq].pack_dat[i],
                       parse_data[seq].pack_len[i]);

                parse_data[seq].offset += (parse_data[seq].pack_len[i]);
             //   printf("offset = %d \n", parse_data[seq].offset);
            }

            //The package is completed and sent for analysis.
            printf("seq :%d  pack_num: %d  offset: %d \n",seq, parse_data[seq].pack_num, parse_data[seq].offset);
            parseProtocol(parse_data[seq].all_dat, parse_data[seq].offset); //Directly analyze the obtained data
            //Clear the relevant parameters of the data packet so that it can be used normally next time
            parse_data[seq].pack_num = 0;
            parse_data[seq].offset = 0;
            parse_data[seq].enable = 0;
            parse_data[seq].seq = -1;
        }else{
            //Count the number of packets received and processed
            parse_data[seq].pack_num++;
        }
    }
#endif
}



#if PRIVE_ZUBAO
//Find if there is a matching array that already contains serial numbers
int findDataBySeq(int seq) {
    for (int i = 0; i < BUFF_PARSE; i++) {
        if (parse_data[i].enable && parse_data[i].seq == seq) {
            return i;
        }
    }
    return -1; // No matching array found
}


//Find unused serial numbers
int findEmptyData(void) {
    for (int i = 0; i < BUFF_PARSE; i++) {
        if (!parse_data[i].enable) {
            return i;
        }
    }
    return -1; // All arrays are allocated
}
#endif





































