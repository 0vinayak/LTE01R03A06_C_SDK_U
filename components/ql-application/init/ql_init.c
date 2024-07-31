/*================================================================
  Copyright (c) 2020 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ql_app_feature_config.h"
#include "ql_api_osi.h"
#include "ql_log.h"
#include "ql_pin_cfg.h"
#include "nw_demo.h"
#include "gpio_demo.h"
#include "gpio_int_demo.h"
#include "datacall_demo.h"
#include "osi_demo.h"
#include "ql_dev_demo.h"
#include "adc_demo.h"
#include "led_cfg_demo.h"
#include "ql_sim_demo.h"
#include "power_demo.h"
#include "ql_api_dev.h"

// #define QL_APP_FEATURE_BLE_GATT 1

#ifdef QL_APP_FEATURE_USB
#include "usb_demo.h"
#endif

#ifdef QL_APP_FEATURE_MMS
#include "mms_demo.h"
#endif

#ifdef QL_APP_FEATURE_UART
#include "uart_demo.h"
#endif
#ifdef QL_APP_FEATURE_RS485
#include "rs485_demo.h"
#endif
#ifdef QL_APP_FEATURE_AUDIO
#include "audio_demo.h"
#endif
#ifdef QL_APP_FEATURE_LCD
#include "lcd_demo.h"
#endif
#ifdef QL_APP_FEATURE_LVGL
#include "lvgl_demo.h"
#endif
#ifdef QL_APP_FEATURE_HTTP
#include "http_demo.h"
#endif
#ifdef QL_APP_FEATURE_FTP
#include "ftp_demo.h"
#endif
#ifdef QL_APP_FEATURE_MQTT
#include "mqtt_demo.h"
#endif
#ifdef QL_APP_FEATURE_SSL
#include "ssl_demo.h"
#endif
#ifdef QL_APP_FEATURE_PING
#include "ping_demo.h"
#endif
#ifdef QL_APP_FEATURE_NTP
#include "ntp_demo.h"
#endif
#ifdef QL_APP_FEATURE_LBS
#include "lbs_demo.h"
#endif
#ifdef QL_APP_FEATURE_QTHSDK
#include "qthsdk_demo.h"
#endif
#ifdef QL_APP_FEATURE_SOCKET
#include "socket_demo.h"
#endif

#ifdef QL_APP_FEATURE_FILE_ZIP
#include "zip_demo.h"
#endif

#ifdef QL_APP_FEATURE_BT

#ifdef QL_APP_FEATURE_BT_SPP
#include "bt_spp_demo.h"
#endif
#ifdef QL_APP_FEATURE_BT_HFP
#include "bt_hfp_demo.h"
#endif
#ifdef QL_APP_FEATURE_BT_A2DP_AVRCP
#include "bt_a2dp_avrcp_demo.h"
#endif
#ifdef QL_APP_FEATURE_BLE_GATT
#include "ble_gatt_demo.h"
#include "ble_hid_demo.h"
#endif

#endif

#ifdef QL_APP_FEATURE_FILE
#include "ql_fs_demo.h"
#endif
#ifdef QL_APP_FEATURE_SMS
#include "sms_demo.h"
#endif
#ifdef QL_APP_FEATURE_VOICE_CALL
#include "voice_call_demo.h"
#endif
#ifdef QL_APP_FEATURE_GNSS
#include "gnss_demo.h"
#endif

#ifdef QL_APP_FEATURE_SPI
#include "spi_demo.h"
#endif

#ifdef QL_APP_FEATURE_SPI_NOR_FLASH
#include "spi_nor_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_SPI4_EXT_NOR_SFFS
#include "spi4_ext_nor_sffs_demo.h"
#endif

#ifdef QL_APP_FEATURE_SPI6_EXT_NOR
#include "spi6_ext_nor_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_SPI_NAND_FLASH
#include "spi_nand_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_CAMERA
#include "camera_demo.h"
#endif

#ifdef QL_APP_FEATURE_WIFISCAN
#include "wifi_scan_demo.h"
#endif

#ifdef QL_APP_FEATURE_HTTP_FOTA
#include "fota_http_demo.h"
#endif

#ifdef QL_APP_FEATURE_FTP_FOTA
#include "fota_ftp_demo.h"
#endif

#ifdef QL_APP_FEATURE_DECODER
#include "decoder_demo.h"
#endif

#ifdef QL_APP_FEATURE_APP_IMG_AT
#include "app_img_at_demo.h"
#endif

#ifdef QL_APP_FEATURE_VOLTE
#include "volte_demo.h"
#endif

#ifdef QL_APP_FEATURE_VSIM_ADAPT
#include "vsim_adapt_demo.h"
#endif

#ifdef QL_APP_FEATURE_KEYPAD
#include "keypad_demo.h"
#endif

#ifdef QL_APP_FEATURE_RTC
#include "ql_rtc_demo.h"
#endif

#ifdef QL_APP_FEATURE_SECURE_BOOT
#include "ql_api_dev.h"
#endif

#ifdef QL_APP_FEATURE_USB_CHARGE
#include "charge_demo.h"
#endif

#ifdef QL_APP_FEATURE_QCLOUD_IOT
#include "qcloud_demo.h"
#endif

#ifdef QL_APP_FEATURE_VIRT_AT
#include "ql_virt_at_demo.h"
#endif

#ifdef QL_APP_FEATURE_TTS
#include "tts_demo.h"
#endif

#ifdef QL_APP_FEATURE_I2C
#include "I2C_demo.h"
#endif

#ifdef QL_APP_FEATURE_PBK
#include "ql_pbk_demo.h"
#endif

#ifdef QL_APP_FEATURE_SDMMC
#include "ql_sdmmc_demo.h"
#endif

#ifdef QL_APP_FEATURE_ALI_LINKSDK
#include "ali_demo.h"
#endif

#ifdef QL_APP_FEATURE_USBNET
#include "usbnet_demo.h"
#endif

#ifdef QL_APP_FEATURE_FS_NAND_FLASH
#include "fs_nand_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_FS_NOR_FLASH
#include "fs_nor_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_SFTP
#include "sftp_demo.h"
#endif

#ifdef QL_APP_FEATURE_MXML
#include "mxml_demo.h"
#endif

#ifdef QL_APP_FEATURE_CLOUDOTA
#include "cloudota_demo.h"
#endif

#ifdef QL_APP_FEATURE_EMBED_NOR_FLASH
#include "embed_nor_flash_demo.h"
#endif

#ifdef QL_APP_FEATURE_HILINK
#include "hilink.h"
#endif

#ifdef QL_APP_FEATURE_PSM
#include "psm_demo.h"
#endif

#ifdef QL_APP_FEATURE_STK
#include "stk_demo.h"
#endif

#ifdef QL_APP_FEATURE_GPRS_DATA_TRANSFER
#include "gprs_data_transfer_demo.h"
#endif

#ifdef QL_APP_FEATURE_TP
#include "tp_demo.h"
#endif

#ifdef QL_APP_FEATURE_ALIOTSMARTCARD
#include "aliotsmartcard_demo.h"
#endif
#ifdef QL_APP_FEATURE_MIPI_LCD
#include "mipi_lcd_demo.h"
#endif

#ifdef QL_APP_FEATURE_ALIPAY_IOT_SDK
extern void ql_alipay_iot_sdk_app_init(void);
#endif

#ifdef QL_APP_FEATURE_NTRIP_RTK
#include "ntrip_rtk_demo.h"
#endif
#ifdef QL_APP_FEATURE_LWM2M
#include "lwm2m_client_demo.h"
#endif

#ifdef QL_APP_FEATURE_SS
#include "ussd_demo.h"
#endif

#ifdef QL_APP_FEATURE_ETHERNET
#include "ethernet_demo.h"
#endif
#ifdef QL_APP_FEATURE_WEBSOCKET
#include "websocket_demo.h"
#endif

#ifdef QL_APP_FEATURE_WIFI
#include "wifi_demo.h"
#endif

#ifdef QL_APP_FEATURE_L2TP
#include "l2tp_demo.h"
#endif

#ifdef QL_APP_FEATURE_CNKTD
#include "cnktd_demo.h"
#include "cnktd_nw_demo.h"
#include "cnktd_sms_demo.h"
#include "cnktd_socket_demo.h"
#include "cnktd_http_demo.h"
#endif

#ifdef QL_APP_FEATURE_XLAT
#include "xlat_demo.h"
#endif

#define QL_INIT_LOG_LEVEL QL_LOG_LEVEL_INFO
#define QL_INIT_LOG(msg, ...) QL_LOG(QL_INIT_LOG_LEVEL, "ql_INIT", msg, ##__VA_ARGS__)
#define QL_INIT_LOG_PUSH(msg, ...) QL_LOG_PUSH("ql_INIT", msg, ##__VA_ARGS__)

static void prvInvokeGlobalCtors(void)
{
    extern void (*__init_array_start[])();
    extern void (*__init_array_end[])();

    size_t count = __init_array_end - __init_array_start;
    for (size_t i = 0; i < count; ++i)
        __init_array_start[i]();
}

const uint8_t ql_mipi_lcd_pin[] =
    {
        QUEC_PIN_MIPI_LCD_DSI_CKP,
        QUEC_PIN_MIPI_LCD_DSI_CKN,
        QUEC_PIN_MIPI_LCD_DSI_D0P,
        QUEC_PIN_MIPI_LCD_DSI_D0N,
        QUEC_PIN_MIPI_LCD_DSI_D1P,
        QUEC_PIN_MIPI_LCD_DSI_D1N,
};

bool ql_is_mipi_lcd_pin(uint8_t pin_num)
{
    for (int i = 0; i < sizeof(ql_mipi_lcd_pin) / sizeof(ql_mipi_lcd_pin[0]); i++)
    {
        if (pin_num == ql_mipi_lcd_pin[i])
        {
            return true;
        }
    }
    return false;
}

void ql_pin_cfg_init(void)
{
    uint8_t index = 0;
    uint8_t pin_num = 0;
    uint8_t default_func = 0;
    uint8_t gpio_func = 0;
    ql_GpioNum gpio_num = 0;
    ql_GpioDir gpio_dir = 0;
    ql_PullMode gpio_pull = 0;
    ql_LvlMode gpio_lvl = 0;

    for (index = 0; index < QL_GPIO_PIN_MAX; index++)
    {
        // QL_INIT_LOG("pin%d=%d", index, ql_pin_cfg_map[index].pin_num);
        if (QUEC_PIN_NONE == ql_pin_cfg_map[index].pin_num)
        {
            QL_INIT_LOG("init exit %d!", index);
            break;
        }
// 从boot到APP一直显示MIPI图像，不能将MIPI的引脚配置为其他功能
#if 0
        if (true == ql_is_mipi_lcd_pin(ql_pin_cfg_map[index].pin_num))
        {
            continue;
        }
#endif

        pin_num = ql_pin_cfg_map[index].pin_num;
        default_func = ql_pin_cfg_map[index].default_func;
        gpio_func = ql_pin_cfg_map[index].gpio_func;
        gpio_num = ql_pin_cfg_map[index].gpio_num;
        gpio_dir = ql_pin_cfg_map[index].gpio_dir;
        gpio_pull = ql_pin_cfg_map[index].gpio_pull;
        gpio_lvl = ql_pin_cfg_map[index].gpio_lvl;

        ql_pin_set_func(pin_num, default_func);
        if (default_func == gpio_func)
        {
            ql_gpio_init(gpio_num, gpio_dir, gpio_pull, gpio_lvl);
        }
    }
}

static void ql_init_demo_thread(void *param)
{
    QL_INIT_LOG("init demo thread enter, param 0x%x", param);

/*Caution:If the macro of secure boot and the function are opened, download firmware and restart will enable secure boot.
          the secret key cannot be changed forever*/
#if 1
    ql_gpio_app_init();
    //  ql_gpioint_app_init();
#endif

#ifdef QL_APP_FEATURE_UART
    ql_uart_app_init();
    //  ql_uart_rb_app_init();
#endif

#ifdef QL_APP_FEATURE_BLE_GATT
    ql_ble_gatt_server_demo_init();
#endif

#ifdef QL_APP_FEATURE_MQTT
    ql_mqtt_app_init();
#endif

#ifdef QL_APP_FEATURE_GNSS
    ql_gnss_app_init();
#endif

    ql_rtos_task_sleep_ms(1000); /*Chaos change: set to 1000 for the camera power on*/

    /*To save logs to sdcard/nandflash, you must call this function after initializing sdcard/nandflash file system;*/
    /*Logs before this point can be output via USB or debug port, which can be configured in prvTraceInit of app_start*/
    // ql_fs_trace_init();

    ql_rtos_task_delete(NULL);
}

int appimg_enter(void *param)
{
    QlOSStatus err = QL_OSI_SUCCESS;
    // QlOSStatus blerr = QL_OSI_SUCCESS;

    ql_task_t ql_init_task = NULL;
    // ql_task_t ble_init_task = NULL;

    QL_INIT_LOG("init demo enter: %s @ %s", QL_APP_VERSION, QL_APP_BUILD_RELEASE_TYPE);
    prvInvokeGlobalCtors();
    if (0 == strcasecmp(QL_APP_BUILD_RELEASE_TYPE, "release"))
    {
        ql_dev_cfg_wdt(1);
        // open the kernel log
        // ql_quec_trace_enable(1);
    }
    else
    {
        ql_dev_cfg_wdt(0);
        // close the kernel log
        // ql_quec_trace_enable(0);
    }

    /*Caution: GPIO pin must be initialized here, otherwise the pin status cannot be determined*/
    ql_pin_cfg_init();

    err = ql_rtos_task_create(&ql_init_task, 1024 * 4, APP_PRIORITY_NORMAL, "ql_init", ql_init_demo_thread, NULL, 5);
    //

    // blerr = ql_rtos_task_create(&ble_init_task, 1024*4, APP_PRIORITY_NORMAL, "ble_init", ql_ble_gatt_client_demo_init, NULL, 1);

    if (err != QL_OSI_SUCCESS)
    {
        QL_INIT_LOG("init failed");
    }

    return err;

    // if(blerr != QL_OSI_SUCCESS)
    // {
    // 	QL_INIT_LOG("ble init failed");
    // }

    // return err;
}

void appimg_exit(void)
{
    QL_INIT_LOG("init demo exit");
}
