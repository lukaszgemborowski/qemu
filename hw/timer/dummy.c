/*
 * MAXIM DUMMY I2C RTC+NVRAM
 *
 * Copyright (c) 2009 CodeSourcery.
 * Written by Paul Brook
 *
 * This code is licensed under the GNU GPL v2.
 *
 * Contributions after 2012-01-13 are licensed under the terms of the
 * GNU GPL, version 2 or (at your option) any later version.
 */

#include "hw/i2c/i2c.h"

#define TYPE_DUMMY "dummy"
#define DUMMY(obj) OBJECT_CHECK(DUMMYState, (obj), TYPE_DUMMY)

#define NVRAM_SIZE 64

typedef struct DUMMYState {
    I2CSlave parent_obj;

    int64_t offset;
    uint8_t wday_offset;
    uint8_t nvram[NVRAM_SIZE];
    int32_t ptr;
    bool addr_byte;
} DUMMYState;

static const VMStateDescription dummy_state = {
    .name = "dummy",
    .version_id = 2,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_I2C_SLAVE(parent_obj, DUMMYState),
        VMSTATE_INT64(offset, DUMMYState),
        VMSTATE_UINT8_V(wday_offset, DUMMYState, 2),
        VMSTATE_UINT8_ARRAY(nvram, DUMMYState, NVRAM_SIZE),
        VMSTATE_INT32(ptr, DUMMYState),
        VMSTATE_BOOL(addr_byte, DUMMYState),
        VMSTATE_END_OF_LIST()
    }
};


static void dummy_event(I2CSlave *i2c, enum i2c_event event)
{
    switch (event) {
    case I2C_START_RECV:
        break;
    case I2C_START_SEND:
        break;
    default:
        break;
    }
}

static int dummy_recv(I2CSlave *i2c)
{
    return 0;
}

static int dummy_send(I2CSlave *i2c, uint8_t data)
{
    return 0;
}

static int dummy_init(I2CSlave *i2c)
{
    return 0;
}

static void dummy_reset(DeviceState *dev)
{
}

static void dummy_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    I2CSlaveClass *k = I2C_SLAVE_CLASS(klass);

    k->init = dummy_init;
    k->event = dummy_event;
    k->recv = dummy_recv;
    k->send = dummy_send;
    dc->reset = dummy_reset;
    dc->vmsd = &dummy_state;
}

static const TypeInfo dummy_info = {
    .name          = TYPE_DUMMY,
    .parent        = TYPE_I2C_SLAVE,
    .instance_size = sizeof(DUMMYState),
    .class_init    = dummy_class_init,
};

static void dummy_register_types(void)
{
    type_register_static(&dummy_info);
}

type_init(dummy_register_types)
