/*******************************************************************************
 * File Name: cycfg_pins.h
 *
 * Description:
 * Pin configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.20.0
 * device-db 4.16.0.6098
 * mtb-pdl-cat1 3.11.0.34443
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#endif /* defined (CY_USING_HAL) */

#if defined (CY_USING_HAL_LITE)
#include "cyhal_hw_types.h"
#endif /* defined (CY_USING_HAL_LITE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define ioss_0_port_6_pin_6_ENABLED 1U
#define ioss_0_port_6_pin_6_PORT GPIO_PRT6
#define ioss_0_port_6_pin_6_PORT_NUM 6U
#define ioss_0_port_6_pin_6_PIN 6U
#define ioss_0_port_6_pin_6_NUM 6U
#define ioss_0_port_6_pin_6_DRIVEMODE CY_GPIO_DM_PULLUP
#define ioss_0_port_6_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
    #define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_6_IRQ ioss_interrupts_gpio_6_IRQn

#if defined (CY_USING_HAL)
#define ioss_0_port_6_pin_6_HAL_PORT_PIN P6_6
#define ioss_0_port_6_pin_6 P6_6
#define ioss_0_port_6_pin_6_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define ioss_0_port_6_pin_6_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define ioss_0_port_6_pin_6_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#endif /* defined (CY_USING_HAL) */

#define ioss_0_port_6_pin_7_ENABLED 1U
#define ioss_0_port_6_pin_7_PORT GPIO_PRT6
#define ioss_0_port_6_pin_7_PORT_NUM 6U
#define ioss_0_port_6_pin_7_PIN 7U
#define ioss_0_port_6_pin_7_NUM 7U
#define ioss_0_port_6_pin_7_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define ioss_0_port_6_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
    #define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_7_IRQ ioss_interrupts_gpio_6_IRQn

#if defined (CY_USING_HAL)
#define ioss_0_port_6_pin_7_HAL_PORT_PIN P6_7
#define ioss_0_port_6_pin_7 P6_7
#define ioss_0_port_6_pin_7_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define ioss_0_port_6_pin_7_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define ioss_0_port_6_pin_7_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLDOWN
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_6_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t ioss_0_port_6_pin_6_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_7_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t ioss_0_port_6_pin_7_obj;
#endif /* defined (CY_USING_HAL) */

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PINS_H */
