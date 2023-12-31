/***************************************************************************//**
 * @file app.c
 * @brief Callbacks implementation and application specific code.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "app.h"
#include "app/framework/include/af.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_NETWORK_TEST_PRESENT
#include "network_test_config.h"
#endif //SL_CATALOG_ZIGBEE_NETWORK_TEST_PRESENT

#if (LARGE_NETWORK_TESTING == 0)
#ifndef EZSP_HOST

#include "zigbee_sleep_config.h"
#endif

#include "network-creator.h"
#include "network-creator-security.h"
#include "network-steering.h"
#include "find-and-bind-target.h"
#include "zll-commissioning.h"

#include "sl_simple_button_instances.h"
#if defined(SL_CATALOG_LED0_PRESENT)
#include "sl_led.h"
#include "sl_simple_led_instances.h"
#define led_turn_on(led) sl_led_turn_on(led)
#define led_turn_off(led) sl_led_turn_off(led)
#define led_toggle(led) sl_led_toggle(led)

#define COMMISSIONING_STATUS_LED_0     (&sl_led_led0)
#define COMMISSIONING_STATUS_LED_1     (&sl_led_led1)
#define COMMISSIONING_STATUS_LED_2     (&sl_led_led2)
#define COMMISSIONING_STATUS_LED_3     (&sl_led_led3)
#define COMMISSIONING_STATUS_LED_4     (&sl_led_led4)
#define COMMISSIONING_STATUS_LED_16    (&sl_led_led16)

#else // !SL_CATALOG_LED0_PRESENT
#define led_turn_on(led)
#define led_turn_off(led)
#define led_toggle(led)
#endif // SL_CATALOG_LED0_PRESENT

#define LED_BLINK_PERIOD_MS          2000
#define TRANSITION_TIME_DS           20
#define FINDING_AND_BINDING_DELAY_MS 3000
#define BUTTON1                      0
#define BUTTON2                      1
#define BUTTON3                      2
#define BUTTON4                      3
#define SWITCH_ENDPOINT              1

static sl_zigbee_event_t commissioning_led_event;
static sl_zigbee_event_t finding_and_binding_event;
static sl_zigbee_event_t com_delay_join;

void report_endpoint_onoff(uint8_t endpoint,uint8_t value);
void report_agreement(void *value,uint16_t len);
//---------------
// Event handlers


//---------------
// Event handlers
#include "nvm3.h"
#include "nvm3_hal_flash.h"

#include "app_timer.h"

#include "attribute-table.h"

#include "zap-command.h"
#include "em_device.h"
#include "af.h"
#include "af-main.h"
#include "zap-id.h"
#include "hal.h"

// Create a NVM area of 24kB (size must equal N * FLASH_PAGE_SIZE, N is integer). Create a cache of 10 entries.
//NVM3_DEFINE_SECTION_STATIC_DATA(nvm3Data1, 24576, 10);
// This macro creates the following:
// 1. An array to hold NVM data named nvm3Data1_nvm
// 2. A section called nvm3Data1_section containing nvm3Data1_nvm. The application linker script must place this section correctly in memory.
// 3. A cache array: nvm3Data1_cache

void report_all_data(void);
void join_net_work(uint8_t join_v);
void set_write_flag(uint8_t flag);

G_USER_CTRL_T tUserCtrl ={0,};
G_USER_CTRL_T *tpUserControl =&tUserCtrl;


#define   User_Dat_ID   1   //存储对象标识

#define   Mark_Head     0x55
#define   Mark_End      0xa4

void emberAfMainTickCallback(void)
{
 // led_toggle(&sl_led_led0);
}
uint8_t nvm_init_ok =0;
void nvm3_user_init(void)
{

//  nvm3_Handle_t handle;
  // Declare a nvm3_Init_t struct of name nvm3Data1 with initialization data. This is passed to nvm3_open() below.
 // NVM3_DEFINE_SECTION_INIT_DATA(nvm3Data1, &nvm3_halFlashHandle);

  G_USER_CTRL_T tUserInit ={0,};
  G_USER_CTRL_T *tpUserInit =&tUserInit;
  Ecode_t status;

  //status = nvm3_open(&handle, &nvm3Data1);  //打开 nvm3存储器
  status = nvm3_initDefault();
  sl_zigbee_app_debug_println("oPen status: 0x%x \n",status);
  if (status != ECODE_NVM3_OK) {
    // Handle error
      sl_zigbee_app_debug_println("oPen nvm3 error \n");
  }


#if 0
    size_t dataLen1;
    //读取对应句柄中的存储数量，如果没有对象写入初始值，
    // Get the number of valid keys already in NVM3
    dataLen1 = nvm3_countObjects(nvm3_defaultHandle);

    sl_zigbee_app_debug_println("object dataLen1 %d\n",dataLen1);
      //想要添加新的对象标识符时可以先查一下总共定义了多少个标识nvm3_countObjects(nvm3_defaultHandle);
         //然后使用下面的nvm3_enumObjects   跑遍所有的标识，将标识名打印出来，这样可以确保新添加的标识符不会与旧的重复
    nvm3_ObjectKey_t keyList[dataLen1];
    size_t numKeys = nvm3_enumObjects(nvm3_defaultHandle, keyList, dataLen1, NVM3_KEY_MIN, NVM3_KEY_MAX);
    for (size_t i = 0; i < numKeys; i++) {
        nvm3_ObjectKey_t key = keyList[i];
        // 打印对象标识
         sl_zigbee_app_debug_println("Object Key: %u\n", key);
    }
#endif
    // Skip if we have initial keys. If not, generate objects and store
    // persistently in NVM3 before proceeding.
  // nvm3_getObjectInfo(nvm3_defaultHandle, User_Dat_ID, &objectType, &dataLen1);
  // sl_zigbee_app_debug_println("objectType: %d dataLen1 %d\n",objectType,dataLen1);
   status = nvm3_readData(nvm3_defaultHandle, User_Dat_ID, tpUserInit, sizeof(G_USER_CTRL_T));
  // sl_zigbee_app_debug_println("INIT  MarkHead: %d MarkEnd %d\n",tpUserInit->MarkHead,tpUserInit->MarkEnd);
   if(status != 0){
      tpUserInit->MarkHead       = Mark_Head;
      tpUserInit->MarkEnd        = Mark_End;
      tpUserInit->Brightness     = 100;            //
      tpUserInit->Color_Temp     = 250;            //
      tpUserInit->Onoff_1        = 0;              //
      tpUserInit->Onoff_2        = 0;              //
      tpUserInit->Onoff_3        = 0;              //
      tpUserInit->Onoff_4        = 0;              //
      tpUserInit->Mode_1         = '0';            //
      tpUserInit->Mode_2         = '0';              //
      tpUserInit->Mode_3         = '0';             //
      tpUserInit->power_memory_1 = '2';
      tpUserInit->power_memory_2 = '2';
      tpUserInit->power_memory_3 = '2';
      tpUserInit->backlight_mode = '0';

      tpUserInit->Count_Down_1   = 0;
      tpUserInit->Count_Down_2   = 0;
      tpUserInit->Count_Down_3   = 0;
      tpUserInit->backlight_16   = 1;
      tpUserInit->Power_On_Times = 0;
      memcpy(tpUserControl, tpUserInit, sizeof(G_USER_CTRL_T)); //写入应用
      status = nvm3_writeData(nvm3_defaultHandle, User_Dat_ID, &tUserInit, sizeof(G_USER_CTRL_T)); //写入flash
      sl_zigbee_app_debug_println("INIT write status: 0x%x \n",status);

   }else{
     if((tpUserInit->MarkHead != Mark_Head) || (tpUserInit->MarkEnd != Mark_End))
     {
         sl_zigbee_app_debug_println("chage  MarkHead: %d MarkEnd %d\n",tpUserInit->MarkHead,tpUserInit->MarkEnd);
         tpUserInit->MarkHead       = Mark_Head;
         tpUserInit->MarkEnd        = Mark_End;
         tpUserInit->Brightness     = 100;            //
         tpUserInit->Color_Temp     = 250;            //
         tpUserInit->Onoff_1        = 0;              //
         tpUserInit->Onoff_2        = 0;              //
         tpUserInit->Onoff_3        = 0;              //
         tpUserInit->Onoff_4        = 0;              //
         tpUserInit->Mode_1         = '0';            //
         tpUserInit->Mode_2         = '0';              //
         tpUserInit->Mode_3         = '0';             //
         tpUserInit->power_memory_1 = '2';
         tpUserInit->power_memory_2 = '2';
         tpUserInit->power_memory_3 = '2';
         tpUserInit->backlight_mode = '0';
         tpUserInit->Count_Down_1   = 0;
         tpUserInit->Count_Down_2   = 0;
         tpUserInit->Count_Down_3   = 0;
         tpUserInit->backlight_16   = 1;
         tpUserInit->Power_On_Times = 0;
     }
     sl_zigbee_app_debug_println("tpUserInit->Power_On_Times: %d\n",tpUserInit->Power_On_Times);
     if(++tpUserInit->Power_On_Times >=6){
         tpUserInit->Power_On_Times =0;    //短时间连续上电3次，执行重置配网
      //   join_net_work(1);

      //   sl_zigbee_app_debug_println("join_net-work \n");
     }
     memcpy(tpUserControl, tpUserInit, sizeof(G_USER_CTRL_T)); //写入应用
     nvm3_writeData(nvm3_defaultHandle, User_Dat_ID, tpUserInit, sizeof(G_USER_CTRL_T)); //写入flash

     sl_zigbee_app_debug_println("tpUserControl->light: %d   color =%d\n",tpUserControl->Brightness,tpUserControl->Color_Temp);
   }
   if(tpUserControl->power_memory_1   == '0'){        //灭
       tpUserControl->Onoff_1        = 0;
   }else  if(tpUserControl->power_memory_1   == '1'){ //亮
       tpUserControl->Onoff_1        = 1;
   }else  if(tpUserControl->power_memory_1   == '2'){ //恢复记忆
   }
   if(tpUserControl->power_memory_2   == '0'){        //灭
       tpUserControl->Onoff_2        = 0;
   }else  if(tpUserControl->power_memory_2   == '1'){ //亮
       tpUserControl->Onoff_2        = 1;
   }else  if(tpUserControl->power_memory_2   == '2'){ //恢复记忆
   }
   if(tpUserControl->power_memory_3   == '0'){        //灭
       tpUserControl->Onoff_3        = 0;
   }else  if(tpUserControl->power_memory_3   == '1'){ //亮
       tpUserControl->Onoff_3        = 1;
   }else  if(tpUserControl->power_memory_3   == '2'){ //恢复记忆
   }


   emberAfWriteServerAttribute(1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)&tpUserControl->Onoff_1, ZCL_BOOLEAN_ATTRIBUTE_TYPE);
   emberAfWriteServerAttribute(2, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)&tpUserControl->Onoff_2, ZCL_BOOLEAN_ATTRIBUTE_TYPE);
   emberAfWriteServerAttribute(3, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)&tpUserControl->Onoff_3, ZCL_BOOLEAN_ATTRIBUTE_TYPE);
   emberAfWriteServerAttribute(4, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)&tpUserControl->Onoff_4, ZCL_BOOLEAN_ATTRIBUTE_TYPE);



   nvm_init_ok =1;    //初始化完成
   // 关闭 NVM3 控制器
 //  nvm3_deinitDefault();
 //  nvm3_close(nvm3_defaultHandle);
}


uint8_t  r_write_flag =0;
static uint8_t delay_write =0;
void set_write_flag(uint8_t flag)
{
  r_write_flag =flag;
  delay_write  =0;
  sl_zigbee_app_debug_println("set write flash\n");

}

void clean_flash(void)
{
  G_USER_CTRL_T tUserInit ={0,};
  G_USER_CTRL_T *tpUserInit =&tUserInit;
  tpUserInit->MarkHead       = Mark_Head;
  tpUserInit->MarkEnd        = Mark_End;
  tpUserInit->Brightness     = 100;            //
	tpUserInit->Color_Temp     = 250;            //
	tpUserInit->Onoff_1        = 0;              //
	tpUserInit->Onoff_2        = 0;              //
	tpUserInit->Onoff_3        = 0;              //
  tpUserInit->Onoff_4        = 0;              //
  tpUserInit->Mode_1         = '0';            //
  tpUserInit->Mode_2         = '0';              //
  tpUserInit->Mode_3         = '0';             //
  tpUserInit->power_memory_1 = '2';
  tpUserInit->power_memory_2 = '2';
  tpUserInit->power_memory_3 = '2';
  tpUserInit->backlight_mode = '0';
  tpUserInit->Count_Down_1   = 0;
  tpUserInit->Count_Down_2   = 0;
  tpUserInit->Count_Down_3   = 0;
	tpUserInit->Power_On_Times = 0;
  memcpy(tpUserControl, tpUserInit, sizeof(G_USER_CTRL_T)); //写入应用
  nvm3_writeData(nvm3_defaultHandle, User_Dat_ID, &tUserInit, sizeof(G_USER_CTRL_T)); //写入flash
  sl_zigbee_app_debug_println("clean_flash :  \n");
}

void write_flash(void)
{
  if(++delay_write >=20){
      delay_write =0;     //250MS写入flash    主循环时间不稳定

   //   led_toggle(&sl_led_led1);
   //   sl_zigbee_app_debug_println("start write flash\n");
    if(r_write_flag){
      r_write_flag =0;
      G_USER_CTRL_T tUserInit ={0,};
      G_USER_CTRL_T *tpUserInit =&tUserInit;
      nvm3_readData(nvm3_defaultHandle, User_Dat_ID, tpUserInit, sizeof(G_USER_CTRL_T));
    //  sl_zigbee_app_debug_println("read00 ->light: %d   color =%d\n",tpUserInit->Brightness,tpUserInit->Color_Temp);

      if((tpUserInit->MarkHead == Mark_Head) && (tpUserInit->MarkEnd == Mark_End)){
          EmberStatus status = nvm3_writeData(nvm3_defaultHandle, User_Dat_ID, tpUserControl, sizeof(G_USER_CTRL_T)); //写入flash
          sl_zigbee_app_debug_println("write status: 0x%x \n",status);
          nvm3_readData(nvm3_defaultHandle, User_Dat_ID, tpUserInit, sizeof(G_USER_CTRL_T));
          sl_zigbee_app_debug_println("read ->Power_On_Times: %d   Onoff =%d  Onoff2 =%d  Onoff3 =%d\n",tpUserInit->Power_On_Times,tpUserInit->Onoff_1,tpUserInit->Onoff_2,tpUserInit->Onoff_3);

      }
    }
  }
}

static app_timer_t app_opened_timer;
EmberStatus r_cancel_network =0;  //定时器调用重复配网标志
EmberStatus get_network_state(void)
{
  return r_cancel_network;
}

void join_net_work(uint8_t join_v)
{
  EmberStatus status =0;
  status  = emberAfNetworkState();
  sl_zigbee_app_debug_println("ember work status: 0x%02X\n",status);

  switch (status) {
      case EMBER_NO_NETWORK:
          // 如果当前没有加入任何 Zigbee 网络，则启动网络加入流程。
          status = emberAfPluginNetworkSteeringStart();
          sl_zigbee_app_debug_println("EMBER_NO_NETWORK state: 0x%02X",status);
          if(join_v){
              r_cancel_network =1;   //定时调用加网
              emberAfZllResetToFactoryNew();
          }
          break;
      case EMBER_JOINING_NETWORK:
          // 如果当前正在尝试加入 Zigbee 网络，则不进行任何操作。
          break;
      case EMBER_JOINED_NETWORK:
          // 如果当前已经加入了 Zigbee 网络，则不进行任何操作。
          if(join_v){
              emberAfZllResetToFactoryNew();
          //    clean_flash();    //清除flash内容
          //  status = emberLeaveNetwork();  //先离开网络
         //   status = emberAfPluginNetworkSteeringStart();
            sl_zigbee_app_debug_println("EMBER_JOINED_NETWORK state: 0x%02X",status);
            r_cancel_network =1;
          }else{
              r_cancel_network =0;
              led_turn_off(COMMISSIONING_STATUS_LED_0);   //连上网络 熄灭
          }
          break;
      case EMBER_JOINED_NETWORK_NO_PARENT:
          // 如果当前已经加入了 Zigbee 网络，但是没有找到合适的父节点，则重新启动网络加入流程。
          emberAfPluginNetworkSteeringStop();
        //  emberAfPluginNetworkSteeringStart();
          r_cancel_network =1;
          break;
      default:
          // 对于其他的状态值，可以进行相应的错误处理。
          break;
  }

}

static bool  key1_flag =0;
static bool  key2_flag =0;
static bool  key3_flag =0;
static bool  key4_flag =0;

#define  NET_Count    20    //20*250 =5S
void  key_enter_net(void)
{
#if(SWITCH_NUM >=1)
  static uint8_t  key1_count =0;
  if(key1_flag){
      if(++key1_count >=NET_Count){  //长按3S配网
          key1_count =0;
          join_net_work(1);
          key1_flag =0;
      }

  }else{
      key1_count =0;
  }
#endif

#if(SWITCH_NUM >=2)    //key 2
  static uint8_t  key2_count =0;

  if(key2_flag){
      if(++key2_count >=NET_Count){  //长按3S配网
          key2_count =0;
          join_net_work(1);
          key2_flag =0;
      }

  }else{
      key2_count =0;
  }
#endif

#if(SWITCH_NUM >=3)   //key 3
  static uint8_t  key3_count =0;

  if(key3_flag){
      if(++key3_count >=NET_Count){  //长按3S配网
          key3_count =0;
          join_net_work(1);
          key3_flag =0;
      }

  }else{
      key3_count =0;
  }
#endif
#if(SWITCH_NUM >=4)   //key 3
  static uint8_t  key4_count =0;

  if(key4_flag){
      if(++key4_count >=NET_Count){  //长按3S配网
          key4_count =0;
          join_net_work(1);
          key4_flag =0;
      }

  }else{
      key4_count =0;
  }
#endif

}



static uint8_t  one_sec_flg =0;
void rep_join(void)
{
  static bool init_power_flag =0;
  static uint8_t  times_count =0;
  static uint8_t  times_count2 =0;

        if(r_cancel_network){
           if(times_count <178){
               join_net_work(0);       //3分钟内才会允许调用beacon加入网络
           }
           if(++times_count >=186){    // 186S 配网提示时长
               times_count = 0;
               r_cancel_network =0;
               led_turn_on(COMMISSIONING_STATUS_LED_0);   //超时未连上网络 点亮
           }
       }else{
           times_count =0;
       }
       if(!init_power_flag){
           if(++times_count2 >=3){  //通电3S后清除上电数据。
               times_count2 =0;
               init_power_flag =1;
               tpUserControl->Power_On_Times = 0;
               set_write_flag(1);  //写入flash
			   if(emberAfNetworkState() == EMBER_JOINED_NETWORK){
                 led_turn_off(COMMISSIONING_STATUS_LED_0);   //连上网络 熄灭
              //   GPIO_PinModeSet(gpioPortD,4,gpioModeInputPull,1);
              //   GPIO_PinModeSet(gpioPortA,0,gpioModePushPull,0);
              //   sl_zigbee_app_debug_println("COMMISSIONING_STATUS_LED_0 set off\n");
			  }
           }
       }
}



uint8_t init_ok =0;
uint8_t get_init_state(void)
{
  return init_ok;
}



//倒计时功能  1S执行调用程序
void f_countdown1_off(uint32_t* times)
{
  static uint8_t count =0,rand_c =60;
   if(*times){
       (*times)--;
       if((*times) ==0){
           tpUserControl->Onoff_1 ^=1;  //执行取反
           report_endpoint_onoff(1,tpUserControl->Onoff_1);
           report_cmd_countdown(1);
           sl_zigbee_app_debug_println(" times %d onoff %d",*times,tpUserControl->Onoff_1);
       }else{
         if(++count >=rand_c){
             count =0;
             rand_c =60+ (rand()%5);
             sl_zigbee_app_debug_println(" rand_c %d",rand_c);
             report_cmd_countdown(1);
         }
       }
   }else{
       count  =0;
       rand_c =60;
   }
}
void f_countdown2_off(uint32_t* times)
{
  static uint8_t count =0,rand_c =60;
   if(*times){
       (*times)--;
       if((*times) ==0){
           tpUserControl->Onoff_2 ^=1;  //执行取反
           report_endpoint_onoff(2,tpUserControl->Onoff_2);
           report_cmd_countdown(2);
           sl_zigbee_app_debug_println(" times2 %d onoff %d",*times,tpUserControl->Onoff_2);
       }else{
         if(++count >=rand_c){
             count =0;
             rand_c =60+ (rand()%5);
             sl_zigbee_app_debug_println(" rand_c %d",rand_c);
             report_cmd_countdown(2);
         }
       }
   }else{
       count  =0;
       rand_c =60;
   }
}
void f_countdown3_off(uint32_t* times)
{
  static uint8_t count =0,rand_c =60;
   if(*times){
       (*times)--;
       if((*times) ==0){
           tpUserControl->Onoff_3 ^=1;  //执行取反
           report_endpoint_onoff(3,tpUserControl->Onoff_3);
           report_cmd_countdown(3);
           sl_zigbee_app_debug_println(" times3 %d onoff %d",*times,tpUserControl->Onoff_3);
       }else{
         if(++count >=rand_c){
             count =0;
             rand_c =60+ (rand()%5);
             sl_zigbee_app_debug_println(" rand_c %d",rand_c);
             report_cmd_countdown(3);
         }
       }
   }else{
       count  =0;
       rand_c =60;
   }
}




static uint8_t r_Abnormal_recovery =0;  //异常计时恢复
static uint8_t r_30second =0;
static uint16_t delay_report =0;
void app_opened_timer_cbbbx(app_timer_t *timer, void *data)
{
  static uint8_t  sec_count =0;
  static uint8_t  m250_count =0;
  static uint8_t  c_100ms =0;
  (void)data;
  (void)timer;
 //  EmberStatus status  = emberAfNetworkState();
 //  sl_zigbee_app_debug_println("ember work status: 0x%02X\n",status);


  if(++m250_count >=25){
      m250_count =0;
      key_enter_net();
      if(r_cancel_network == 1){
          led_toggle(COMMISSIONING_STATUS_LED_0);
        //    led_toggle(COMMISSIONING_STATUS_LED_16);
      }
   //   led_toggle(COMMISSIONING_STATUS_LED_0);
  }
  if(++c_100ms >=10){ //100MS
      c_100ms =0;
      r_Abnormal_recovery =0;
      if(++sec_count >=10){  //1S时间到
         sec_count =0;
         one_sec_flg =1;
         r_30second ++;
         init_ok =1;      //初始化化后过1S
      }
   }
  if(delay_report > 1){
    delay_report --;
  }
//  sl_simple_button_poll_instances();
}


//定时上报开关状态用于心跳
void time_report_hearbeat(void)
{
//  static uint8_t rand_tims=30;

  uint32_t tickCount  = halCommonGetInt32uMillisecondTick();
  if(HeartbeatTime){  //有查询协议信息来就不执行定时上报，没有就执行随机定时上报
    if((tickCount - Save_HbTime) >=HeartbeatTime)
    {
        sl_zigbee_app_debug_println(" ===  tickCount %d  Save_HbTime =%d \n",tickCount,Save_HbTime);
        printf("hearbeat %d\n",HeartbeatTime);
        HeartbeatTime =0;
        report_hearbeat();
        r_30second =0;
    }
  }
#if 0
  else{
      if(r_30second >=rand_tims){
           rand_tims = 20+ (rand()%20);
           printf("hearbeat %d\n",rand_tims);
           r_30second =0;
           report_hearbeat();
       }
  }
#endif
}


void app_init(void)
{
  app_timer_start(&app_opened_timer,
      Time_Count,
      app_opened_timer_cbbbx,
      NULL,
      true);
    nvm3_user_init();
    set_rand_source();

    emberSetRadioPower(EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER);  //设置最大功率输出
 //   emberSetLogicalAndRadioChannel(11);
}



//修复定时

void  Repair_timer(void)
{
  if(++r_Abnormal_recovery >=25){  //0.25S 异常恢复定时器
      r_Abnormal_recovery =0;
      app_timer_start(&app_opened_timer,
          Time_Count,
          app_opened_timer_cbbbx,
          NULL,
          true);
      sl_zigbee_app_debug_println("Repair_timer \n");
  }
}


//1秒执行调用
void f_one_sec_run(void)
{
  if(one_sec_flg){
      one_sec_flg =0;
      rep_join();            //重复入网操作
      f_countdown1_off(&tpUserControl->Count_Down_1);
      f_countdown2_off(&tpUserControl->Count_Down_2);
      f_countdown3_off(&tpUserControl->Count_Down_3);
  //    sl_zigbee_app_debug_println("switch 3 1.0.2 \n");

  }
}
uint8_t report_state =0;
uint8_t switch_state =0;
void app_process_action(void)
{
  static uint32_t save_tick =0;
//  static uint8_t Brightness;  //亮度
//  static uint16_t Color_Temp;  //色温

  uint32_t tickCount  = halCommonGetInt32uMillisecondTick();




  time_report_hearbeat();  //定时上报
  if(tickCount - save_tick >=10){ //10ms执行函数
      save_tick = tickCount;

      write_flash();

      f_one_sec_run();
      if(delay_report == 1){
         delay_report = 0;
        // report_all_data();

      }
      Repair_timer();
        if(report_state){
            report_state =0;
            report_all_data();
        }
      //  led_turn_off(COMMISSIONING_STATUS_LED_0); //配网指示灯灭
      //  if(r_cancel_network == 0){
#if(SWITCH_NUM >=1)
         if(tpUserControl->Onoff_1){
             led_turn_on(COMMISSIONING_STATUS_LED_1);
         }else{
             led_turn_off(COMMISSIONING_STATUS_LED_1);
         }
#endif
#if(SWITCH_NUM >=2)
         if(tpUserControl->Onoff_2){
             led_turn_on(COMMISSIONING_STATUS_LED_2);
         }else{
             led_turn_off(COMMISSIONING_STATUS_LED_2);
         }
#endif
#if(SWITCH_NUM >=3)
         if(tpUserControl->Onoff_3){
             led_turn_on(COMMISSIONING_STATUS_LED_3);
         }else{
             led_turn_off(COMMISSIONING_STATUS_LED_3);
         }
#endif
#if(SWITCH_NUM >=4)
         if(tpUserControl->Onoff_4){
             led_turn_on(COMMISSIONING_STATUS_LED_4);
         }else{
             led_turn_off(COMMISSIONING_STATUS_LED_4);
         }
#endif

         if(tpUserControl->backlight_16){
             led_turn_on(COMMISSIONING_STATUS_LED_16);
         }else{
             led_turn_off(COMMISSIONING_STATUS_LED_16);
         }

     // }
  }

 // sl_zigbee_app_debug_println("tickCount %d\n",tickCount);

}




void report_agreement(void *value,uint16_t len)
{
    if(emberAfNetworkState() != EMBER_JOINED_NETWORK){
        sl_zigbee_app_debug_println("no network return report_hearbeat:%d\r\n");
        return;
    }
    uint8_t  type=emberAfCurrentCommand()->type;


    //   sl_zigbee_app_debug_println("groupId :%d  option %x  destinationEndpoint %d   type =%x\r\n",emberAfCurrentCommand()->apsFrame->groupId,
     //                              emberAfCurrentCommand()->apsFrame->options,emberAfCurrentCommand()->apsFrame->destinationEndpoint,emberAfCurrentCommand()->type);





    if((type == EMBER_INCOMING_MULTICAST) || (recevi_type == EMBER_INCOMING_MULTICAST)){ //群组消息不回复  report
        return;
    }

   uint16_t  idx =0,i;
   uint8_t  status =0;
   uint8_t  attribute_record3[EMBER_AF_PLUGIN_FRAGMENTATION_BUFFER_SIZE] ={0};



    //报开关状态
    idx =0;
    attribute_record3[idx++] = LOW_BYTE(0x0068);
    attribute_record3[idx++] = HIGH_BYTE(0x0068);//私有协议定义属性
    attribute_record3[idx++] = ZCL_OCTET_STRING_ATTRIBUTE_TYPE;
  //  attribute_record3[idx++] = len;
    sl_zigbee_app_debug_print(" len 0x%02X ",len);
    uint8_t *val_ptr = (uint8_t*)value;

     for (i = 0; i < len; i++) {
        attribute_record3[idx++] = val_ptr[i]; // 解引用指针取得数据
        sl_zigbee_app_debug_print(" 0x%02X ",val_ptr[i]);
     }



     //将属性报告填充进入缓冲区   CLUSTER值   数据内容  数据长度      //Fill a ZCL global report attributes command buffer  ZCL_BASIC_CLUSTER_ID  ZCL_GENERIC_TUNNEL_CLUSTER_ID
     status = emberAfFillCommandGlobalServerToClientReportAttributes_no_response(ZCL_BASIC_CLUSTER_ID,attribute_record3,idx);
    sl_zigbee_app_debug_println("ReportAttributes_no_response: 0x%02X\n",status);
    //写入 sourceEndpoint  和 destinationEndpoint    //Specify endpoints for command sending
    emberAfSetCommandEndpoints(0x01, 0x01);

    //调用发送数据接口将缓存好的数据发出           发生选项  和  单播目标地址
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, 0x0000);
   // sl_zigbee_app_debug_println("emberAfSendCommandUnicast: 0x%02X\n",status);
    //status2 = emberAfSendCommandUnicastToBindings();
}


void report_endpoint_onoff(uint8_t endpoint,uint8_t value)
{
  uint8_t  idx =0;
   uint8_t  status =0;
   uint8_t attribute_record3[5] ={0};

   if(emberAfNetworkState() != EMBER_JOINED_NETWORK){
      sl_zigbee_app_debug_println("no network return report_endpoint_onoff:%d\r\n");
      return;
   }
#if 0
     emberAfGetCommandApsFrame()->sourceEndpoint = endpoint;
     if (value) {
         emberAfFillCommandOnOffClusterOn();
     } else{
         emberAfFillCommandOnOffClusterOff();
     }
 //    sl_zigbee_app_debug_println("%s: 0x%02X", "3 Send to bindings", status);
#endif
     uint8_t  type=emberAfCurrentCommand()->type;


   //   sl_zigbee_app_debug_println("groupId :%d  option %x  destinationEndpoint %d   type =%x\r\n",emberAfCurrentCommand()->apsFrame->groupId,
    //                              emberAfCurrentCommand()->apsFrame->options,emberAfCurrentCommand()->apsFrame->destinationEndpoint,emberAfCurrentCommand()->type);

     if((type == EMBER_INCOMING_MULTICAST) || (recevi_type == EMBER_INCOMING_MULTICAST)){ //群组消息不回复  report
         return;
     }

    //报开关状态
    idx =0;
    attribute_record3[idx++] = LOW_BYTE(ZCL_ON_OFF_ATTRIBUTE_ID);
    attribute_record3[idx++] = HIGH_BYTE(ZCL_ON_OFF_ATTRIBUTE_ID);
    attribute_record3[idx++] = ZCL_BOOLEAN_ATTRIBUTE_TYPE;
    attribute_record3[idx++] = value;


    //将属性报告填充进入缓冲区   CLUSTER值   数据内容  数据长度      //Fill a ZCL global report attributes command buffer
    status = emberAfFillCommandGlobalServerToClientReportAttributes_no_response(ZCL_ON_OFF_CLUSTER_ID,attribute_record3,idx);
    sl_zigbee_app_debug_println("emberAfFillCommandGlobalServerToClientReportAttributes: 0x%02X\n",status);
    //写入 sourceEndpoint  和 destinationEndpoint    //Specify endpoints for command sending
    emberAfSetCommandEndpoints(endpoint, 0x01);

    //调用发送数据接口将缓存好的数据发出           发生选项  和  单播目标地址
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, 0x0000);
    sl_zigbee_app_debug_println("emberAfSendCommandUnicast: 0x%02X\n",status);
    //status2 = emberAfSendCommandUnicastToBindings();
}

static void commissioning_led_event_handler(sl_zigbee_event_t *event)
{
  sl_zigbee_app_debug_println("get work %d\n",emberAfNetworkState());
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
    uint16_t identifyTime;
    emberAfReadServerAttribute(SWITCH_ENDPOINT,
                               ZCL_IDENTIFY_CLUSTER_ID,
                               ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                               (uint8_t *)&identifyTime,
                               sizeof(identifyTime));
#if 0
    if (identifyTime > 0) {
      led_toggle(COMMISSIONING_STATUS_LED);
      sl_zigbee_event_set_delay_ms(&commissioning_led_event,
                                   LED_BLINK_PERIOD_MS << 1);
    } else {
      led_turn_on(COMMISSIONING_STATUS_LED);
    }
#endif
  } else {
  //  EmberStatus status = emberAfPluginNetworkSteeringStart();
   // r_cancel_network =1;
    sl_zigbee_app_debug_println("Up Not Join NetWork");
    sl_zigbee_event_set_delay_ms(&com_delay_join,500);  //上电后检查到没有加入任何网络延迟500ms后进入配网状态，500MS串口留给产测信标检查时间。
  }
}

static void finding_and_binding_event_handler(sl_zigbee_event_t *event)
{
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
    sl_zigbee_event_set_inactive(&finding_and_binding_event);

    sl_zigbee_app_debug_println("Find and bind target start: 0x%02X",
                                emberAfPluginFindAndBindTargetStart(SWITCH_ENDPOINT));
  }
}

static void com_delay_join_handler(sl_zigbee_event_t *event)
{
    sl_zigbee_app_debug_println("com_delay_join_handler");
    r_cancel_network =1;
}




//----------------------
// Implemented Callbacks

/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be notified
 * of changes to the stack status and take appropriate action. The framework
 * will always process the stack status after the callback returns.
 */
void emberAfStackStatusCallback(EmberStatus status)
{
  // Note, the ZLL state is automatically updated by the stack and the plugin.
  uint8_t rand_c =0;
  sl_zigbee_app_debug_println("emberAfStackStatusCallback =0x%02x\n\n",status);
  if (status == EMBER_NETWORK_DOWN) {
      sl_zigbee_app_debug_println("emberAfStackStatusCallback status = EMBER_NETWORK_DOWN\n\n");
      join_net_work(1);
   // led_turn_off(COMMISSIONING_STATUS_LED);
      led_turn_on(COMMISSIONING_STATUS_LED_0);    //断网 点亮
  } else if (status == EMBER_NETWORK_UP) {
   // led_turn_on(COMMISSIONING_STATUS_LED);
  	  led_turn_off(COMMISSIONING_STATUS_LED_0);   //连上网络 熄灭
      sl_zigbee_event_set_active(&finding_and_binding_event);
   //   report_all_data();
      set_rand_source();
      rand_c = (rand()%500);
   //   rand_c = (rand()%250);
      delay_report = 4+rand_c; //延迟上报所有状态，保证读到flash中的内容
      sl_zigbee_app_debug_println("emberAfStackStatusCallback status %d = EMBER_NETWORK_UP\n\n",delay_report);

  }
}

// 定义回调函数


/** @brief Init
 * Application init function
 */
void emberAfMainInitCallback(void)
{
  sl_zigbee_event_init(&commissioning_led_event, commissioning_led_event_handler);
  sl_zigbee_event_init(&finding_and_binding_event, finding_and_binding_event_handler);


  sl_zigbee_event_init(&com_delay_join, com_delay_join_handler);

 sl_zigbee_event_set_active(&commissioning_led_event);
}

/** @brief Complete network steering.
 *
 * This callback is fired when the Network Steering plugin is complete.
 *
 * @param status On success this will be set to EMBER_SUCCESS to indicate a
 * network was joined successfully. On failure this will be the status code of
 * the last join or scan attempt.
 *
 * @param totalBeacons The total number of 802.15.4 beacons that were heard,
 * including beacons from different devices with the same PAN ID.
 *
 * @param joinAttempts The number of join attempts that were made to get onto
 * an open Zigbee network.
 *
 * @param finalState The finishing state of the network steering process. From
 * this, one is able to tell on which channel mask and with which key the
 * process was complete.
 */
void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState)
{
  sl_zigbee_app_debug_println("Join network complete: 0x%02X", status);

  if (status != EMBER_SUCCESS) {
    // Initialize our ZLL security now so that we are ready to be a touchlink
    // target at any point.

    #if 0
        //尝试自己组件网络 边缘设备不需要
        status = emberAfZllSetInitialSecurityState();
        if (status != EMBER_SUCCESS) {
          sl_zigbee_app_debug_println("Error: cannot initialize ZLL security: 0x%02X", status);
        }

        status = emberAfPluginNetworkCreatorStart(false); // distributed
        sl_zigbee_app_debug_println("Form network start: 0x%02X", status);
    #endif
  }
}

/** @brief Complete the network creation process.
 *
 * This callback notifies the user that the network creation process has
 * completed successfully.
 *
 * @param network The network that the network creator plugin successfully
 * formed.
 *
 * @param usedSecondaryChannels Whether or not the network creator wants to
 * form a network on the secondary channels.
 */
void emberAfPluginNetworkCreatorCompleteCallback(const EmberNetworkParameters *network,
                                                 bool usedSecondaryChannels)
{
  sl_zigbee_app_debug_println("Form Network Complete: 0x%02X",
                              EMBER_SUCCESS);
}

/** @brief Post Attribute Change
 *
 * This function is called by the application framework after it changes an
 * attribute value. The value passed into this callback is the value to which
 * the attribute was set by the framework.
 */

void report_fuction(uint8_t ATTRIBUTE_ID, uint8_t TYPE, uint16_t CLUSTER,void *value,uint8_t len)
{
    if(emberAfNetworkState() != EMBER_JOINED_NETWORK){
        sl_zigbee_app_debug_println("no network return report_hearbeat:%d\r\n");
        return;
    }
   uint8_t  idx =0,i;
   uint8_t  attribute_record3[20] ={0};
   uint8_t  type=emberAfCurrentCommand()->type;


  // sl_zigbee_app_debug_println("groupId :%d  option %x  destinationEndpoint %d   type =%x\r\n",emberAfCurrentCommand()->apsFrame->groupId,
  //                             emberAfCurrentCommand()->apsFrame->options,emberAfCurrentCommand()->apsFrame->destinationEndpoint,emberAfCurrentCommand()->type);

//   sl_zigbee_app_debug_println("type =%d recevi_tyep %d ",sli_zigbee_af_current_command->type,recevi_type);


    if((type == EMBER_INCOMING_MULTICAST) || (recevi_type == EMBER_INCOMING_MULTICAST)){ //群组消息不回复  report
        sl_zigbee_app_debug_println("type =%d report_fuction ",type);
        return;
    }

    //报开关状态f
    idx =0;
    attribute_record3[idx++] = LOW_BYTE(ATTRIBUTE_ID);
    attribute_record3[idx++] = HIGH_BYTE(ATTRIBUTE_ID);
    attribute_record3[idx++] = TYPE;
  //  attribute_record3[idx++] = len;

  //  sl_zigbee_app_debug_println("len[i]: 0x%02X\n",len);
    uint8_t *val_ptr = (uint8_t*)value;


     for (i = 0; i < len; i++) {
        attribute_record3[idx++] = val_ptr[i]; // 解引用指针取得数据
     //   sl_zigbee_app_debug_println("val_ptr[i]: 0x%02X\n",val_ptr[i]);
     }




    //将属性报告填充进入缓冲区   CLUSTER值   数据内容  数据长度      //Fill a ZCL global report attributes command buffer

    uint8_t status = emberAfFillCommandGlobalServerToClientReportAttributes_no_response(CLUSTER,attribute_record3,idx);
    sl_zigbee_app_debug_println("ReportAttributes_no_response: 0x%02X\n",status);
    //写入 sourceEndpoint  和 destinationEndpoint    //Specify endpoints for command sending
    emberAfSetCommandEndpoints(0x01, 0x01);

    //调用发送数据接口将缓存好的数据发出           发生选项  和  单播目标地址
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, 0x0000);
  //  sl_zigbee_app_debug_println("emberAfSendCommandUnicast: 0x%02X  CLUSTER 0x%02X\n",status,CLUSTER);
    //status2 = emberAfSendCommandUnicastToBindings();
}



uint8_t g_endpoint =0;

uint8_t r_temp_onoff =0;
uint8_t r_temp_light =0;
uint16_t r_temp_color =0;
void emberAfPostAttributeChangeCallback(uint8_t endpoint,
                                        EmberAfClusterId clusterId,
                                        EmberAfAttributeId attributeId,
                                        uint8_t mask,
                                        uint16_t manufacturerCode,
                                        uint8_t type,
                                        uint8_t size,
                                        uint8_t* value)
{
  g_endpoint = endpoint;
  if(!nvm_init_ok) return;    //nvm初始化未完成不可操作
 // sl_zigbee_app_debug_println("clusterId 0x%02x attributeId 0x%02x:  mask 0x%02X  value =%d\n",clusterId, attributeId, mask,*value);
  if (clusterId == ZCL_ON_OFF_CLUSTER_ID
      && attributeId == ZCL_ON_OFF_ATTRIBUTE_ID
      && mask == CLUSTER_MASK_SERVER) {
      if (emberAfReadServerAttribute(endpoint,
                                     ZCL_ON_OFF_CLUSTER_ID,
                                     ZCL_ON_OFF_ATTRIBUTE_ID,
                                     (uint8_t *)&r_temp_onoff,
                                     sizeof(r_temp_onoff))
          == EMBER_ZCL_STATUS_SUCCESS)
      {
          //回复状态值
          sl_zigbee_app_debug_println("recv attribute onoff =%d , endpoint:%d\r\n",r_temp_onoff, endpoint);
          if(g_endpoint == 0x01){
              if(r_temp_onoff !=tpUserControl->Onoff_1){
                  set_write_flag(1);
              }
              tpUserControl->Onoff_1 = r_temp_onoff ;
              report_endpoint_onoff(g_endpoint,tpUserControl->Onoff_1);
          }else  if(g_endpoint == 0x02){
              if(r_temp_onoff !=tpUserControl->Onoff_2){
                  set_write_flag(1);
              }
              tpUserControl->Onoff_2 = r_temp_onoff ;
              report_endpoint_onoff(g_endpoint,tpUserControl->Onoff_2);
          }else  if(g_endpoint == 0x03){
              if(r_temp_onoff !=tpUserControl->Onoff_3){
                  set_write_flag(1);
              }
              tpUserControl->Onoff_3 = r_temp_onoff ;
              report_endpoint_onoff(g_endpoint,tpUserControl->Onoff_3);
          }else  if(g_endpoint == 0x04){
              if(r_temp_onoff !=tpUserControl->Onoff_4){
                  set_write_flag(1);
              }
              tpUserControl->Onoff_4 = r_temp_onoff ;
              report_endpoint_onoff(g_endpoint,tpUserControl->Onoff_4);
          }

      }
  }

}

/** @brief On/off Cluster Server Post Init
 *
 * Following resolution of the On/Off state at startup for this endpoint, perform any
 * additional initialization needed; e.g., synchronize hardware state.
 *
 * @param endpoint Endpoint that is being initialized
 */
void emberAfPluginOnOffClusterServerPostInitCallback(uint8_t endpoint)
{
  // At startup, trigger a read of the attribute and possibly a toggle of the
  // LED to make sure they are always in sync.


  sl_zigbee_app_debug_println("emberAfPluginOnOffClusterServerPostInitCallback 0x=%02x\n\n",endpoint);
  emberAfPostAttributeChangeCallback(endpoint,
                                     ZCL_ON_OFF_CLUSTER_ID,
                                     ZCL_ON_OFF_ATTRIBUTE_ID,
                                     CLUSTER_MASK_SERVER,
                                     0,
                                     0,
                                     0,
                                     NULL);
}

/** @brief
 *
 * Application framework equivalent of ::emberRadioNeedsCalibratingHandler
 */
void emberAfRadioNeedsCalibratingCallback(void)
{
  #ifndef EZSP_HOST

  sl_zigbee_app_debug_println("emberAfRadioNeedsCalibratingCallback\n\n");
  sl_mac_calibrate_current_channel();
  #endif
}

#if defined(SL_CATALOG_SIMPLE_BUTTON_PRESENT) && (SL_ZIGBEE_APP_FRAMEWORK_USE_BUTTON_TO_STAY_AWAKE == 0)
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"
#ifdef SL_CATALOG_ZIGBEE_FORCE_SLEEP_AND_WAKEUP_PRESENT
#include "force-sleep-wakeup.h"
#endif //SL_CATALOG_ZIGBEE_FORCE_SLEEP_AND_WAKEUP_PRESENT
/***************************************************************************//**
 * A callback called in interrupt context whenever a button changes its state.
 *
 * @remark Can be implemented by the application if required. This function
 * can contain the functionality to be executed in response to changes of state
 * in each of the buttons, or callbacks to appropriate functionality.
 *
 * @note The button state should not be updated in this function, it is updated
 * by specific button driver prior to arriving here
 *
   @param[out] handle             Pointer to button instance
 ******************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  if (SL_SIMPLE_BUTTON_INSTANCE(BUTTON1) == handle) {       //switch  1
    if ( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
       if(key1_flag){
          key1_flag =0;
          tpUserControl->Onoff_1 ^= 1;
          sl_zigbee_app_debug_println("BUTTON1 onoff 0x%02X", tpUserControl->Onoff_1);
          report_endpoint_onoff(1,tpUserControl->Onoff_1);
          set_write_flag(1);
       }

    }else if( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
#if(SWITCH_NUM>=1)
        key1_flag =1;
#endif
    }
  } else if (SL_SIMPLE_BUTTON_INSTANCE(BUTTON2) == handle) {  //switch 2
    if ( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
        if(key2_flag){
          key2_flag =0;
          tpUserControl->Onoff_2 ^= 1;
          sl_zigbee_app_debug_println("BUTTON2 onoff 0x%02X", tpUserControl->Onoff_2);
          report_endpoint_onoff(2,tpUserControl->Onoff_2);
          set_write_flag(1);
        }
    }else if( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
#if(SWITCH_NUM>=2)
        key2_flag =1;
#endif
    }
  }else if (SL_SIMPLE_BUTTON_INSTANCE(BUTTON3) == handle) {
      if ( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
          if(key3_flag){
            key3_flag =0;
            tpUserControl->Onoff_3 ^= 1;
            sl_zigbee_app_debug_println("BUTTON3 onoff  0x%02X", tpUserControl->Onoff_3);
            report_endpoint_onoff(3,tpUserControl->Onoff_3);
            set_write_flag(1);
          }
      }else if( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
#if(SWITCH_NUM>=3)
          key3_flag =1;
#endif
      }
   }else if (SL_SIMPLE_BUTTON_INSTANCE(BUTTON4) == handle) {
       if ( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
           if(key4_flag){
             key4_flag =0;
             tpUserControl->Onoff_4 ^= 1;
             sl_zigbee_app_debug_println("BUTTON4 onoff  0x%02X", tpUserControl->Onoff_4);
             report_endpoint_onoff(4,tpUserControl->Onoff_4);
             set_write_flag(1);
           }
       }else if( sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
 #if(SWITCH_NUM>=4)
           key4_flag =1;
 #endif
       }
     }
}
#endif // SL_CATALOG_SIMPLE_BUTTON_PRESENT && SL_ZIGBEE_APP_FRAMEWORK_USE_BUTTON_TO_STAY_AWAKE == 0

//Internal testing stuff
#if defined(EMBER_TEST)
void emberAfHalButtonIsrCallback(uint8_t button, uint8_t state)
{
  if (state == BUTTON_RELEASED) {

    sl_zigbee_event_set_active(&finding_and_binding_event);
  }
}
#endif // EMBER_TEST

#ifdef SL_CATALOG_ZIGBEE_FORCE_SLEEP_AND_WAKEUP_PRESENT
void sli_zigbee_app_framework_force_sleep_callback(void)
{
  // Do other things like turn off LEDs etc
  sl_led_turn_off(&sl_led_led0);
  sl_zigbee_app_debug_println("sli_zigbee_app_framework_force_sleep_callback\n\n");
}
#endif // SL_CATALOG_ZIGBEE_FORCE_SLEEP_AND_WAKEUP_PRESENT
#endif //#if (LARGE_NETWORK_TESTING == 0)












/*
 * 产测部分
 */


uint8_t    Production_Test =0;
uint8_t get_Test_State(void)
{
  return Production_Test;
}

void Set_Test_State(uint8_t val)
{
  Production_Test =val;
}

void emberEnter_Test(uint8_t clust,uint8_t comm)
{
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
      printf("retrun emberAfNetworkState");
      return; //已入网 退出   不会进入产测
  }
  if(get_network_state()){  //
    printf("retrun r_cancel_network");
    return;   //处于配网状态，也不会进入产测。
  }

    if(get_init_state()){ //初始化超过时间不再进入产测
      printf("retrun Test_Enter");
      return;   //处于配网状态，也不会进入产测。
    }
  //网络情况下和没有配网情况下， 收到产测信号开始进入产测
  if((clust == 0) &&(comm == 0x55)){
    /*  if(!tpUserControl->test_mode){
          Production_Test =1;   //第一次产测
      }else{
          Production_Test =2;   //重复产测
      }
     */
      sl_zigbee_app_debug_println("Enter TestMode =%d \n",Production_Test);
  }
}






