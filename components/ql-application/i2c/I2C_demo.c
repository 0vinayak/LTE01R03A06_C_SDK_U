/**  @file
  I2C_demo.c

  @brief
  This file is demo of I2C.

*/

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

/*===========================================================================
 * include files
 ===========================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ql_api_osi.h"
#include "ql_log.h"
#include "ql_api_camera.h"
#include "ql_i2c.h"
#include "I2C_demo.h"

/*===========================================================================
 * Macro Definition
 ===========================================================================*/

#define QL_APP_I2C_LOG_LEVEL QL_LOG_LEVEL_INFO
#define QL_APP_I2C_LOG(msg, ...) QL_LOG(QL_APP_I2C_LOG_LEVEL, "QL_APP_I2C", msg, ##__VA_ARGS__)
#define QL_APP_I2C_LOG_PUSH(msg, ...) QL_LOG_PUSH("QL_APP_I2C", msg, ##__VA_ARGS__)

#define QL_I2C_TASK_STACK_SIZE 1024
#define QL_I2C_TASK_PRIO APP_PRIORITY_NORMAL
#define QL_I2C_TASK_EVENT_CNT 5

#define SalveAddr_w_8bit (0xD6 >> 1)
#define SalveAddr_r_8bit (0xD7 >> 1)

// #define SalveAddr_w_8bit (0xD6 >> 1)
// #define SalveAddr_r_8bit (0xD7 >> 1)

/*reserved*/
#define SalveAddr_w_16bit (0xff >> 1)
#define SalveAddr_r_16bit (0xff >> 1)

#define demo_for_8bit_or_16bit (1) // 1:test 8bit register address     0:test 16bit register address
/*===========================================================================
 * Struct
 ===========================================================================*/

/*===========================================================================
 * Enum
 ===========================================================================*/

/*===========================================================================
 * Variate
 ===========================================================================*/

/*===========================================================================
 * Functions
 ===========================================================================*/

void ql_i2c_demo_thread(void *param)
{
#if demo_for_8bit_or_16bit
    /*test 8bit register address*/
    uint8_t read_data = 0;
    QlI2CStatus ql_errcode_i2c = QL_I2C_INIT_ERR;
    // uint8_t data = 0xaa;

    /*operate the camera for the example*/
    ql_CamInit(320, 240);
    ql_CamPowerOn();

    ql_errcode_i2c = ql_I2cInit(i2c_1, STANDARD_MODE);
    if (ql_errcode_i2c != QL_OSI_SUCCESS)
    {
        QL_APP_I2C_LOG("i2c init failed");
    }
    while (1)
    {
        QL_APP_I2C_LOG("I2C read_data = 0x%x", read_data);
        ql_I2cWrite(i2c_1, (uint8_t)SalveAddr_r_8bit, (uint8_t)0x0F, &read_data, 1);
        QL_APP_I2C_LOG("I2C read_data = 0x%x", read_data);
        // ql_I2cWrite(i2c_1, SalveAddr_w_8bit, 0x55, &data, 1);
        read_data = 0;
        ql_rtos_task_sleep_ms(2000);
        // nwy_test_cli_i2c_imu_startup();
    }

#else

    /*test 16bit register address*/
    uint8_t read_data = 0;
    uint8_t data = 0xff;

    /*set i2c pin function*/
    ql_pin_set_func(41, 0);
    ql_pin_set_func(42, 0);

    ql_I2cInit(i2c_1, STANDARD_MODE);
    while (1)
    {
        QL_APP_I2C_LOG("I2C read_data = 0x%x", read_data);
        ql_I2cRead_16bit_addr(i2c_1, SalveAddr_r_16bit, 0xffff, &read_data, 1);
        QL_APP_I2C_LOG("I2C read_data = 0x%x", read_data);
        ql_I2cWrite_16bit_addr(i2c_1, SalveAddr_w_16bit, 0xffff, &data, 1);
        read_data = 0;
        ql_rtos_task_sleep_ms(200);
    }

#endif
}

void nwy_test_cli_i2c_imu_startup(void)
{

    uint8_t accEnable = 0x01;
    uint8_t *intEn = &accEnable;

    uint8_t accFreq = 0x60;
    uint8_t *freqEn = &accFreq;

    /**start accelerometer */
    while (1)
    {
        ql_I2cWrite(i2c_1, SalveAddr_w_8bit, 0x0D, intEn, 1); // enable accel interrupt

        ql_rtos_task_sleep_ms(1000);

        ql_I2cWrite(i2c_1, SalveAddr_w_8bit, 0x10, freqEn, 1); // select accel at 416 Hz
    }
    // nwy_test_cli_echo("\r\nI2c Error is not in imu initialization\r\n");
}

void ql_i2c_demo_init(void)
{
    QlI2CStatus err = QL_OSI_SUCCESS;
    ql_task_t i2c_task = NULL;

    err = ql_rtos_task_create(&i2c_task, QL_I2C_TASK_STACK_SIZE, QL_I2C_TASK_PRIO, "I2C DEMO", ql_i2c_demo_thread, NULL, QL_I2C_TASK_EVENT_CNT);
    if (err != QL_OSI_SUCCESS)
    {
        QL_APP_I2C_LOG("i2ctest1 demo task created failed");
    }
}
