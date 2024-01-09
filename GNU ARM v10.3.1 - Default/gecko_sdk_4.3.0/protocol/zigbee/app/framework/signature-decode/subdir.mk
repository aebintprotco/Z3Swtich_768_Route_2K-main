################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.c 

OBJS += \
./gecko_sdk_4.3.0/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.o 

C_DEPS += \
./gecko_sdk_4.3.0/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.0/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.o: C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.c gecko_sdk_4.3.0/protocol/zigbee/app/framework/signature-decode/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG21A010F768IM32=1' '-DSL_APP_PROPERTIES=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DEMBER_AF_API_BOOTLOADER_INTERFACE=1' '-DCORTEXM3=1' '-DCORTEXM3_EFM32_MICRO=1' '-DCORTEXM3_EFR32=1' '-DPHY_RAIL=1' '-DPLATFORM_HEADER="platform-header.h"' '-DSL_LEGACY_HAL_ENABLE_WATCHDOG=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DCUSTOM_TOKEN_HEADER="sl_token_manager_af_token_header.h"' '-DUSE_NVM3=1' '-DUC_BUILD=1' '-DEMBER_MULTI_NETWORK_STRIPPED=1' '-DSL_ZIGBEE_PHY_SELECT_STACK_SUPPORT=1' '-DCONFIGURATION_HEADER="app/framework/util/config.h"' -I"C:\Users\admin\SimplicityStudio\v5_workspace\Z3Swtich_768_Route_2K-main-aebs7\config" -I"C:\Users\admin\SimplicityStudio\v5_workspace\Z3Swtich_768_Route_2K-main-aebs7\config\zcl" -I"C:\Users\admin\SimplicityStudio\v5_workspace\Z3Swtich_768_Route_2K-main-aebs7\autogen" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG21/Include" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_timer" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader/api" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/driver/button/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/legacy_hal/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/legacy_hal_wdog/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/legacy_printf/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/include" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/library" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/nvm3/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/power_manager/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_psa_driver/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ble" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/wmbus" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/zwave" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_ieee802154" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_pti" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/se_manager/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/se_manager/src" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/silicon_labs/silabs_core/memory_manager" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/service/token_manager/inc" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/plugin/plugin-common/eeprom" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/plugin/plugin-afv6/eeprom" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/address-table" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/basic" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/include" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/em260" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/platform/micro" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/service-function" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/color-control-server" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/counters" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/debug-print" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/find-and-bind-target" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/fragmentation" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/gp" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/green-power-client" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/green-power-common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/groups-server" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/identify" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/interpan" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/level-control" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/network-creator" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/network-creator-security" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/network-steering" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/on-off" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-bootload" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-client" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-client-policy" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-server-policy" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-storage-common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-storage-simple" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/ota-storage-simple-eeprom" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/reporting" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/scan-dispatch" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/scenes" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/security" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/signature-decode" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/zigbee" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/mac/rail_mux" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//platform/radio/mac" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//util/silicon_labs/silabs_core" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/core" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/mac" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/update-tc-link-key" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/include" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/util" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/security" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/util/zigbee-framework" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/util/counters" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/cli" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/util/common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/util/security" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/stack/zll" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/zll-commissioning-common" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/zll-commissioning-server" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/zll-level-control-server" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/zll-on-off-server" -I"C:/Users/admin/SimplicityStudio/SDKs/gecko_sdk//protocol/zigbee/app/framework/plugin/zll-scenes-server" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse -fno-builtin-printf -fno-builtin-sprintf --specs=nano.specs -Wno-unused-parameter -Wno-missing-field-initializers -Wno-missing-braces -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.0/protocol/zigbee/app/framework/signature-decode/sl_signature_decode.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


