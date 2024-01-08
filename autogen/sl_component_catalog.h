#ifndef SL_COMPONENT_CATALOG_H
#define SL_COMPONENT_CATALOG_H

// APIs present in project
#define SL_CATALOG_APP_TIMER_PRESENT
#define SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT
#define SL_CATALOG_DEVICE_INIT_NVIC_PRESENT
#define SL_CATALOG_EMLIB_CORE_PRESENT
#define SL_CATALOG_EMLIB_CORE_DEBUG_CONFIG_PRESENT
#define SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT
#define SL_CATALOG_IOSTREAM_USART_PRESENT
#define SL_CATALOG_LEGACY_BOOTLOADER_INTERFACE_PRESENT
#define SL_CATALOG_LEGACY_HAL_PRESENT
#define SL_CATALOG_LEGACY_HAL_SOC_PRESENT
#define SL_CATALOG_LEGACY_HAL_WDOG_PRESENT
#define SL_CATALOG_LEGACY_PRINTF_PRESENT
#define SL_CATALOG_NVM3_PRESENT
#define SL_CATALOG_POWER_MANAGER_PRESENT
#define SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT //AEBS
#define SL_CATALOG_PRINTF_PRESENT
#define SL_CATALOG_PSA_CRYPTO_PRESENT
#define SL_CATALOG_RAIL_LIB_PRESENT
#define SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
#define SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
#define SL_CATALOG_RAIL_UTIL_PTI_PRESENT
#define SL_CATALOG_RAIL_UTIL_RF_PATH_PRESENT
#define SL_CATALOG_SE_MANAGER_PRESENT
#define SL_CATALOG_BTN1_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN1_PRESENT
#define SL_CATALOG_BTN2_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN2_PRESENT
#define SL_CATALOG_BTN3_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN3_PRESENT
#define SL_CATALOG_BTN4_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN4_PRESENT
#define SL_CATALOG_LED0_PRESENT
#define SL_CATALOG_SIMPLE_LED_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED0_PRESENT
#define SL_CATALOG_LED1_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED1_PRESENT
#define SL_CATALOG_LED16_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED16_PRESENT
#define SL_CATALOG_LED2_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED2_PRESENT
#define SL_CATALOG_LED3_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED3_PRESENT
#define SL_CATALOG_LED4_PRESENT
#define SL_CATALOG_SIMPLE_LED_LED4_PRESENT
// #define SL_CATALOG_SLEEPTIMER_PRESENT //AEBS
#define SL_CATALOG_TOKEN_MANAGER_PRESENT
#define SL_CATALOG_TOKEN_MANAGER_NVM3_PRESENT
#define SL_CATALOG_UTIL_EEPROM_PRESENT
#define SL_CATALOG_ZIGBEE_ADDRESS_TABLE_PRESENT
#define SL_CATALOG_ZIGBEE_APP_FRAMEWORK_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_APPLICATION_BOOTLOADER_PRESENT
#define SL_CATALOG_ZIGBEE_BASIC_PRESENT
#define SL_CATALOG_ZIGBEE_BINDING_TABLE_PRESENT
#define SL_CATALOG_ZIGBEE_CLASSIC_KEY_STORAGE_PRESENT
#define SL_CATALOG_ZIGBEE_COLOR_CONTROL_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_COUNTERS_PRESENT
#define SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#define SL_CATALOG_ZIGBEE_DEVICE_CONFIG_PRESENT
#define SL_CATALOG_ZIGBEE_ENHANCED_ROUTING_PRESENT
#define SL_CATALOG_ZIGBEE_FIND_AND_BIND_TARGET_PRESENT
#define SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
#define SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT
#define SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_PRESENT
#define SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_CLI_PRESENT
#define SL_CATALOG_ZIGBEE_GREEN_POWER_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_GROUPS_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_IDENTIFY_PRESENT
#define SL_CATALOG_ZIGBEE_INSTALL_CODE_PRESENT
#define SL_CATALOG_ZIGBEE_INTERPAN_PRESENT
#define SL_CATALOG_ZIGBEE_LEVEL_CONTROL_PRESENT
#define SL_CATALOG_ZIGBEE_NETWORK_CREATOR_PRESENT
#define SL_CATALOG_ZIGBEE_NETWORK_CREATOR_SECURITY_PRESENT
#define SL_CATALOG_ZIGBEE_NETWORK_STEERING_PRESENT
#define SL_CATALOG_ZIGBEE_ON_OFF_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_BOOTLOAD_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_CLIENT_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_CLIENT_POLICY_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_STORAGE_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_STORAGE_SIMPLE_PRESENT
#define SL_CATALOG_ZIGBEE_OTA_STORAGE_SIMPLE_EEPROM_PRESENT
#define SL_CATALOG_ZIGBEE_PACKET_HANDOFF_PRESENT
#define SL_CATALOG_ZIGBEE_PHY_2_4_PRESENT
#define SL_CATALOG_ZIGBEE_PRO_STACK_PRESENT
#define SL_CATALOG_ZIGBEE_REPORTING_PRESENT
#define SL_CATALOG_ZIGBEE_SCAN_DISPATCH_PRESENT
#define SL_CATALOG_ZIGBEE_SCENES_PRESENT
#define SL_CATALOG_ZIGBEE_SECURITY_MANAGER_PRESENT
#define SL_CATALOG_ZIGBEE_SIGNATURE_DECODE_PRESENT
#define SL_CATALOG_ZIGBEE_SOURCE_ROUTE_PRESENT
#define SL_CATALOG_ZIGBEE_STACK_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_STACK_DIAGNOSTICS_PRESENT
#define SL_CATALOG_ZIGBEE_STRONG_RANDOM_API_RADIO_PRESENT
#define SL_CATALOG_ZIGBEE_UPDATE_TC_LINK_KEY_PRESENT
#define SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#define SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_COMMON_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_IDENTIFY_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_LEVEL_CONTROL_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_ON_OFF_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_SCENES_SERVER_PRESENT
#define SL_CATALOG_ZIGBEE_ZLL_UTILITY_SERVER_PRESENT

#endif // SL_COMPONENT_CATALOG_H
