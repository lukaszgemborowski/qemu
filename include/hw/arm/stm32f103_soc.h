/*
 * STM32F103 SoC
 *
 * Copyright (c) 2016 Lukasz Gemborowski <lukasz.gemborowski@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HW_ARM_STM32F103_SOC_H
#define HW_ARM_STM32F103_SOC_H

#include "hw/sysbus.h"

#define TYPE_STM32F103_SOC "stm32f103-soc"
#define STM32F103_SOC(obj) \
    OBJECT_CHECK(STM32F103State, (obj), TYPE_STM32F103_SOC)

typedef struct STM32F103State {
    /*< private >*/
    SysBusDevice parent_obj;
    /*< public >*/

    char *kernel_filename;
    char *cpu_model;
} STM32F103State;

#endif
