/*
 * app.h
 *
 *  Created on: 2023年6月27日
 *      Author: YWJ
 */

#ifndef APP_H_
#define APP_H_


#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#include "sl_simple_rgb_pwm_led.h"

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

#define SWITCH_NUM                   2
#define SCENE_NUM                    0


typedef struct {
  uint8_t MarkHead;
  uint8_t Power_On_Times;//Power-on times
  uint8_t Onoff_1;    //switch
  uint8_t Onoff_2;    //switch
  uint8_t Onoff_3;    //switch
  uint8_t Onoff_4;    //switch
  uint8_t Mode_1;    //switch mode
  uint8_t Mode_2;    //switch mode
  uint8_t Mode_3;    //switch mode

  uint8_t power_memory_1;
  uint8_t power_memory_2;
  uint8_t power_memory_3;
  uint8_t backlight_mode;
  uint8_t backlight_16;    //backlight switch
  uint8_t Brightness;  //brightness
  uint8_t resever;     //reserve
  uint16_t Color_Temp;  //color temperature
  uint32_t Count_Down_1;
  uint32_t Count_Down_2;
  uint32_t Count_Down_3;
  uint8_t MarkEnd;

} G_USER_CTRL_T;

typedef enum {
  SIGLE_CLICK  = 0,
  DOUBLE_CLIKC = 1,
  LONG_PRESS   = 2,

  SECEN_DP     = 0x10,
}ZCL_PRIVATE_SECEN_VUALE;

extern G_USER_CTRL_T *tpUserControl;

extern uint16_t HeartbeatTime;
extern uint32_t Save_HbTime;
#define  Time_Count    10     //Timer setting 10ms
void report_hearbeat(void);
void app_init(void);
void app_process_action(void);
void report_cmd_countdown(uint8_t num);

void report_agreement(void *value,uint16_t len);
void set_write_flag(uint8_t flag);
void set_rand_source(void);

#endif /* APP_H_ */
