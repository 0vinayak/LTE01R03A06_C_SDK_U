
/**  @file
  quec_pin_cfg.h

  @brief
  TODO

*/

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


#ifndef QUEC_PIN_CFG_H
#define QUEC_PIN_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "quec_pin_index.h"
#include "ql_gpio.h"

/*===========================================================================
 * Macro
 ===========================================================================*/

/*===========================================================================
 * Struct
 ===========================================================================*/
typedef struct
{
    uint8_t             pin_num;
    uint8_t             default_func;
    uint8_t             gpio_func;
    ql_GpioNum          gpio_num;
    ql_GpioDir          gpio_dir;
    ql_PullMode         gpio_pull;
    ql_LvlMode          gpio_lvl;
    volatile uint32_t   *reg;
} quec_pin_cfg_t;

/*===========================================================================
 * Extern
 ===========================================================================*/
extern const quec_pin_cfg_t quec_pin_cfg_map[];


#ifdef __cplusplus
} /*"C" */
#endif

#endif /* QUEC_PIN_CFG_H */


