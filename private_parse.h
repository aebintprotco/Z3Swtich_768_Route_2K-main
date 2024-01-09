/*
 * led_user.h
 *
 *  Created on: August 29, 2023
 *      Author: YWJ
 */

#ifndef PRIVATE_PARSE_H_
#define PRIVATE_PARSE_H_



#include "app.h"




// Convert 16-bit integer to byte array (little endian)
#define INT16_TO_LE_BYTES(val, bytes)  { (bytes)[0] = (uint8_t)((val) & 0xFF); (bytes)[1] = (uint8_t)(((val) >> 8) & 0xFF); }


// Convert val to 32-bit integer to byte array (little endian)
#define INT16_TO_LE_BYTES(val, bytes)  { (bytes)[0] = (uint8_t)((val) & 0xFF); (bytes)[1] = (uint8_t)(((val) >> 8) & 0xFF); }

// Convert little-endian byte array to 16-bit integer
#define LE_BYTES_TO_INT16(bytes)       ((uint16_t)((bytes)[0] | ((bytes)[1] << 8)))

// Convert 32-bit integer to byte array (little endian)
#define INT32_TO_LE_BYTES(val, bytes)  { (bytes)[0] = (uint8_t)((val) & 0xFF); \
                                         (bytes)[1] = (uint8_t)(((val) >> 8) & 0xFF); \
                                         (bytes)[2] = (uint8_t)(((val) >> 16) & 0xFF); \
                                         (bytes)[3] = (uint8_t)(((val) >> 24) & 0xFF); }
// Convert little-endian byte array to 32-bit integer
#define LE_BYTES_TO_INT32(bytes)       ((uint32_t)((bytes)[0] | ((bytes)[1] << 8) | ((bytes)[2] << 16)) | ((bytes)[3] << 24))




// Define command word index
#define CMD_HEARTBEAT               0x99
#define CMD_DEVICE_PING             0x01
#define CMD_DEVICE_STATUS_QUERY     0x02
#define CMD_GATEWAY_COMMAND         0x04
#define CMD_DEVICE_REPORT_STATUS    0x06



#define DP_1_SWTICH               1
#define DP_2_SWTICH               2
#define DP_3_SWTICH               3
#define DP_4_SWTICH               4
#define DP_BACK_SWTICH              16


#define DP_1_COUNTDOWN         30
#define DP_2_COUNTDOWN         31
#define DP_3_COUNTDOWN         32



#define DP_37_LED_STATE         37
#define DP_38_POWER_MEMORY      38
#define DP_1_POWER_MEMORY       39
#define DP_2_POWER_MEMORY       40
#define DP_3_POWER_MEMORY       41
#define DP_2_Work_Mode            2
#define DP_3_Bright               3
#define DP_4_TEMP                 4
#define DP_5_COLOUR               5
#define DP_6_SCENE                6
#define DP_7_COUNTDOWN            7
#define DP_9_CONTROL              9
#define DP_30_RHYTHM              30
#define DP_31_ASLEEP              31
#define DP_32_WAKEUP              32
#define DP_33_POWER_MEMORY        33
#define DP_34_DO_NOT_DISTURB      34
#define DP_35_SWTICH_GRADIENT     35


typedef enum {
  PROP_UNKNOWN,
    PROP_BOOL,    //4 bytes
    PROP_INT,     //4 bytes
    PROP_FLOAT,   //4 bytes
    PROP_ENUM,    //4 bytes  //little endian transfer
    PROP_FAULT,
    PROP_TEXT,
    PROP_RAW,
    PROP_STRUCT,
    PROP_ARRAY,
} DP_PROP_TP_E;




extern void zigbee_Private_Trasmit_Parse(uint8_t endpoint,
                                  EmberAfClusterId cluster,
                                  EmberAfAttributeId attributeID,
                                  uint8_t *dataPtr,
                                  uint16_t readLength);






#endif /* PRIVATE_PARSE_H_ */
