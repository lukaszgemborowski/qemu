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

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "hw/arm/arm.h"
#include "exec/address-spaces.h"
#include "hw/arm/stm32f103_soc.h"

static void stm32f103_soc_initfn(Object *obj)
{
}

static void stm32f103_soc_realize(DeviceState *dev_soc, Error **errp)
{
}

static Property stm32f103_soc_properties[] = {
    DEFINE_PROP_STRING("kernel-filename", STM32F103State, kernel_filename),
    DEFINE_PROP_STRING("cpu-model", STM32F103State, cpu_model),
    DEFINE_PROP_END_OF_LIST(),
};

static void stm32f103_soc_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->realize = stm32f103_soc_realize;
    dc->props = stm32f103_soc_properties;
}

static const TypeInfo stm32f103_soc_info = {
    .name          = TYPE_STM32F103_SOC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32F103State),
    .instance_init = stm32f103_soc_initfn,
    .class_init    = stm32f103_soc_class_init,
};

static void stm32f103_soc_types(void)
{
    type_register_static(&stm32f103_soc_info);
}

type_init(stm32f103_soc_types)
