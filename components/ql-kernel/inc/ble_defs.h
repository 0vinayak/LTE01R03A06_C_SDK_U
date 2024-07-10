#ifndef BLE_DEFS_H
#define BLE_DEFS_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include <rom/ets_sys.h>
// #include "esp_log.h"
// #include "esp_err.h"
// #include "esp_system.h"

#define GATTS_TABLE_TAG "GATTS_SERVER_EM"
#define EEPROM_TAG "ESP_EEPROM"
#define ESP_RTC_TAG "ESP_RTC"
#define ESP_SPIFFS_TAG "ESP_SPIFFS"
#define OTA_TAG "ESP_OTA"

#define LDS_NUMBER_OF_DATA 20
#define TDS_NUMBER_OF_DATA 30
#define TDS_P1_NUMBER_OF_DATA 12
#define TDS_P2_NUMBER_OF_DATA 16
#define ERROR_NUMBER_OF_DATA 10
#define VIS_NUMBER_OF_DATA 25
#define VCS_NUMBER_OF_DATA 7

// extern unsigned char childLockFlag;

#pragma pack(1)
// childLockFlag

typedef enum AppReceive
{
    ODOWRITE = 0,
    HEADLAMP,
    CHILDMODE,
    CONTROL,
    ALTITUDE,
    MCU_OTA_RX
} AppReceive;

extern AppReceive characteristicInd;

struct AppReceiveInfo
{
    uint32_t odo_data;
    bool headLamp;
    uint8_t childMode;
    uint8_t controlVars[7];
    uint16_t Altitude;
    uint8_t McuOta[20];
} AppReceiveInfo;

extern struct AppReceiveInfo AppReceiveInfo;

typedef struct Live_data_st
{
    uint8_t vehicle_speed_value;
    uint8_t motor_speed_value;
    uint16_t battery_voltage_value;
    uint8_t battery_soc_value;
    uint16_t throttle_value;
    uint8_t pas_mode_value : 4;
    uint8_t ride_mode_value : 4;
    uint16_t dte_value;
    uint16_t time_to_charge_value;
    uint8_t current_trip_distance_value;
    uint8_t current_trip_max_speed_value;
    uint8_t side_stand_value : 1;
    uint8_t headlamp_value : 1;
    uint8_t brake_value : 1;
    uint8_t cruise_control_status : 1;
    uint8_t walk_mode_status : 1;
    uint8_t acknowledgement : 1;
    uint8_t reserved : 2;
    uint8_t toast_notification;
    uint32_t vehicle_odo_reading;
} LDS_data;

// Union of LDS_data
union LDSUnion
{
    LDS_data lds_data;
    uint8_t lds[LDS_NUMBER_OF_DATA];
};

extern union LDSUnion Live_Data;

// Define the 1-bit error values as bit fields in a struct
#pragma pack(1)
struct ErrorBits
{
    unsigned int e1 : 1;
    unsigned int e2 : 1;
    unsigned int e3 : 1;
    unsigned int e4 : 1;
    unsigned int e5 : 1;
    unsigned int e6 : 1;
    unsigned int e7 : 1;
    unsigned int e8 : 1;
    unsigned int e9 : 1;
    unsigned int e10 : 1;
};

// Define a union to store the struct as a byte[3] value
union ErrorUnion
{
    struct ErrorBits bits;
    uint8_t error[ERROR_NUMBER_OF_DATA];
};

extern union ErrorUnion error_data;

#pragma pack(1)
typedef struct Trip_data_st_p1
{
    uint8_t max_speed_value;
    uint16_t trip_distance_value;
    uint16_t trip_duration_value;
    uint8_t avg_speed_value;
    uint16_t motor_on_duration_in_trip_value;
    uint16_t trip_whrs_value;
    uint16_t start_trip_soc_value;
    uint8_t end_trip_soc_value;
    // uint16_t pas_distribution_value               ;
} TDS_data_p1;

#pragma pack(1)
typedef struct Trip_data_st_p2
{
    uint32_t eco_activated_duration_value;
    uint32_t normal_activated_duration_value;
    uint32_t user_mode_activated_duration_value;
    uint32_t fitness_activated_duration_value;
} TDS_data_p2;

// Union of TDS_data_P1
union TDSUnionP1
{
    TDS_data_p1 tds_data;
    uint8_t tds[TDS_P1_NUMBER_OF_DATA];
};

// Union of TDS_data_P2
union TDSUnionP2
{
    TDS_data_p2 tds_data;
    uint8_t tds[TDS_P2_NUMBER_OF_DATA];
};

extern union TDSUnionP1 Trip_Data_P1;
extern union TDSUnionP2 Trip_Data_P2;

#pragma pack(1)
typedef struct Vehicle_Info
{
    uint8_t vin_value[17];
    uint8_t battery_number_value[4];
    uint8_t firmware_number_value[4];
} VIS_data;

union VISUnion
{
    VIS_data vis_data;
    uint8_t vis[VIS_NUMBER_OF_DATA];
};

extern union VISUnion Vehicle_Information;

// Define Vehicle control values
#pragma pack(1)
struct VCS_data
{
    uint8_t pas_mode_value : 4;
    uint8_t ride_mode_value : 4;
    uint8_t child_lock_value : 1;
    uint8_t headlamp_value : 1;
    uint8_t reserved : 6;
    uint8_t speed_5;
    uint8_t speed_10;
    uint8_t speed_15;
    uint8_t speed_20;
    uint8_t speed_25;
};

union VCSUnion
{
    struct VCS_data vcs_data;
    uint8_t vcs[VCS_NUMBER_OF_DATA];
};

extern union VCSUnion Vehicle_Control_data;

extern uint32_t odo_big_value;
extern uint32_t odo_start_value;

// extern TaskHandle_t Global_Loop;

#endif // BLE_DEFS_H
