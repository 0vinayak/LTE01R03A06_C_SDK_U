
/*================================================================
  Copyright (c) 2021 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/
                
/*=================================================================

						EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN			  WHO		  WHAT, WHERE, WHY
------------	 -------	 -------------------------------------------------------------------------------

=================================================================*/


#ifndef QL_PWM_H
#define QL_PWM_H

#include "ql_api_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define QL_PWM_ERRCODE_BASE (QL_COMPONENT_BSP_PWM<<16)

/*===========================================================================
 * Enum
 ===========================================================================*/
/**
 * PWM errcode
 */
typedef enum
{
    QL_PWM_SUCCESS = QL_SUCCESS,

    QL_PWM_EXECUTE_ERR                  = 1|QL_PWM_ERRCODE_BASE,
    QL_PWM_INVALID_PARAM_ERR,
    QL_PWM_FUNC_SET_ERR,
    QL_PWM_ACQUIRE_ERR,
    QL_PWM_START_ERR,
    QL_PWM_STOP_ERR,
    QL_PWM_REPEAT_OPEN_ERR,
    QL_PWM_REPEAT_CLOSE_ERR,

    QL_PWM_CREATE_MUTEX_ERR,
    QL_PWM_MUTEX_TIMEOUT_ERR
}ql_errcode_pwm;

/**
 * PWM function select
 */
typedef enum
{
    PWM_PWT,
    PWM_LPG,
    PWM_PWL0,
    PWM_PWL1,
    PWM_MAX
}ql_PwmSel;

/**
 * PWM LPG Period and high-level time
 */
typedef enum
{
    LPG_PER_125MS,
    LPG_PER_250MS,
    LPG_PER_500MS,
    LPG_PER_1000MS,
    LPG_PER_1500MS,
    LPG_PER_2000MS,
    LPG_PER_2500MS,
    LPG_PER_3000MS
}ql_LpgPer;

typedef enum
{
    LPG_ONTIME_UNDEFINE,
    LPG_ONTIME_15_6MS,
    LPG_ONTIME_31_2MS,
    LPG_ONTIME_46_8MS,
    LPG_ONTIME_62MS,
    LPG_ONTIME_78MS,
    LPG_ONTIME_94MS,
    LPG_ONTIME_110MS,
    LPG_ONTIME_125MS,
    LPG_ONTIME_140MS,
    LPG_ONTIME_156MS,
    LPG_ONTIME_172MS,
    LPG_ONTIME_188MS,
    LPG_ONTIME_200MS,
    LPG_ONTIME_218MS,
    LPG_ONTIME_234MS
}ql_LpgOntime;

typedef enum
{
    IND_SIM_NOT_INSERT      = 0,
    IND_SIM_INITIALIZING,
    IND_SIM_PIN_LOCK,
    IND_SIM_CPIN_READY,
    IND_SEARCHING,
    IND_CAMP_ON_CELL        = 5,
    IND_REGISTERING,
    IND_STANDBY,
    IND_PDP_ACTIVING,
    IND_PDP_ACTIVED,
    IND_SOCKET_SET_UP       = 10,
    IND_DATA_TRANSMIT,
    IND_PDP_DEACTIVING,
    IND_DIALING,
    IND_NET_LED_STATUS_MAX
}ql_module_status; 

typedef enum
{
    IND_NET_TYPE_NOT_REGISTERED,
    IND_NET_TYPE_2G,
    IND_NET_TYPE_3G,
    IND_NET_TYPE_4G,
    IND_NET_TYPE_USER_DEF,
    IND_NET_TYPE_MAX
}ql_net_type;

/*===========================================================================
 * Struct
 ===========================================================================*/

/*===========================================================================
 * Functions declaration
 ===========================================================================*/
/**
 * @brief PWM open function
 * @param pwm_sel       :pwm type
 * @return
 *       QL_PWM_FUNC_SET_ERR
 *       QL_PWM_ACQUIRE_ERR
 *       QL_PWM_REPEAT_OPEN_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_open(ql_PwmSel pwm_sel);

/**
 * @brief PWM close function
 * @param pwm_sel       :pwm type
 * @return
 *       QL_PWM_INVALID_PARAM_ERR
 *       QL_PWM_REPEAT_CLOSE_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_close(ql_PwmSel pwm_sel);

/**
 * @brief PWM LPG function enable
 * @param lpg_period     : LPG period
 * @param highlvl_time   : LPG high-level time
 * @return
 *       QL_PWM_INVALID_PARAM_ERR
 *       QL_PWM_START_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_lpg_enable(ql_LpgPer lpg_period, ql_LpgOntime highlvl_time);

/**
 * @brief PWM PWT function enable
 * @param pwm_divider    : pwm divider,value range[0-255]
 * @param pwt_period     : pwt period,value range[0-2047]
 * @param pwt_duty       : pwt duty,value range[0-1023]
 * pwt_clk = SysFreq/(pwm_divider+1)
 * frequency output = pwt_clk/(pwt_period*8+1)  
 * @return
 *       QL_PWM_INVALID_PARAM_ERR
 *       QL_PWM_START_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_pwt_enable(uint8_t pwm_divider, uint32_t pwt_period, uint32_t pwt_duty);

/**
 * @brief PWM PWL function enable
 * @param pwm_sel        : pwm type, only support pwl0 and pwl1
 * @param pwl_duty       : pw1 duty,value range[0-255]
 * @return
 *       QL_PWM_INVALID_PARAM_ERR
 *       QL_PWM_START_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_pwl_enable(ql_PwmSel pwm_sel, uint32_t pwl_duty);

/**
 * @brief PWM function disable
 * @param pwm_sel        :pwm type
 * @return
 *       QL_PWM_INVALID_PARAM_ERR
 *       QL_PWM_STOP_ERR
 *       QL_PWM_SUCCESS
 */
ql_errcode_pwm ql_pwm_disable(ql_PwmSel pwm_sel);


#ifdef __cplusplus
} /*"C" */
#endif

#endif /* QL_PWM_H */


