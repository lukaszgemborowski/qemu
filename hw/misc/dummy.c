/*
 * This code is licensed under the GNU GPL v2.
 *
 * Contributions after 2012-01-13 are licensed under the terms of the
 * GNU GPL, version 2 or (at your option) any later version.
 */

#include "hw/i2c/i2c.h"

#define TYPE_DUMMY "dummy"
#define DUMMY(obj) OBJECT_CHECK(DUMMYState, (obj), TYPE_DUMMY)

#define REGS_CNT 64

typedef struct DUMMYState {
	I2CSlave parent_obj;

	uint8_t reg_ptr;
	uint8_t regs[REGS_CNT];
} DUMMYState;

static const VMStateDescription dummy_state = {
	.name = "dummy",
	.version_id = 2,
	.minimum_version_id = 1,
	.fields = (VMStateField[]) {
		VMSTATE_I2C_SLAVE(parent_obj, DUMMYState),
		VMSTATE_UINT8_V(reg_ptr, DUMMYState, 2),
		VMSTATE_UINT8_ARRAY(regs, DUMMYState, REGS_CNT),
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
	DUMMYState *s = DUMMY(i2c);
	return s->regs[s->reg_ptr];
}

static int dummy_send(I2CSlave *i2c, uint8_t data)
{
	DUMMYState *s = DUMMY(i2c);
	s->reg_ptr = data;
	return 0;
}

static int dummy_init(I2CSlave *i2c)
{
	DUMMYState *s = DUMMY(i2c);
	int i;

	s->reg_ptr = 0;
	for (i = 0; i < REGS_CNT; i ++)
		s->regs[i] = i * 2;

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
