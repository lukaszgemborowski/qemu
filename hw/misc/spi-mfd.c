/*
 * Multi functional SPI device.
 *
 * Copyright (c) 2016 Lukasz Gemborowski <lukasz.gemborowski@gmail.com>
 *
 * This code is licensed under the GNU GPLv2.
 *
 * Contributions after 2012-01-13 are licensed under the terms of the
 * GNU GPL, version 2 or (at your option) any later version.
 */

#include "qemu/osdep.h"
#include "hw/ssi/ssi.h"

typedef struct {
    SSISlave parent_obj;
} SPIMFDState;

#define TYPE_SPI_MFD "spi_mfd"

#define SPI_MFD(obj) \
    OBJECT_CHECK(SPIMFDState, (obj), TYPE_SPI_MFD)

static uint32_t spi_mfd_read(SPIMFDState *s)
{
    return 74;
}

/* Interpret a control-byte */
static void spi_mfd_write(SPIMFDState *s, uint32_t value)
{
}

static uint32_t spi_mfd_transfer(SSISlave *dev, uint32_t value)
{
    SPIMFDState *s = SPI_MFD(dev);
    spi_mfd_write(s, value);
    return spi_mfd_read(s);
}

static const VMStateDescription vmstate_spi_mfd = {
    .name = "spi_mfd",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_SSI_SLAVE(parent_obj, SPIMFDState),
        VMSTATE_END_OF_LIST()
    }
};

static void spi_mfd_init(SSISlave *d, Error **errp)
{
    DeviceState *dev = DEVICE(d);
    SPIMFDState *s = SPI_MFD(dev);

    vmstate_register(dev, -1, &vmstate_spi_mfd, s);
}

static void spi_mfd_class_init(ObjectClass *klass, void *data)
{
    SSISlaveClass *k = SSI_SLAVE_CLASS(klass);

    k->transfer = spi_mfd_transfer;
    k->realize = spi_mfd_init;
}

static const TypeInfo spi_mfd_info = {
    .name          = TYPE_SPI_MFD,
    .parent        = TYPE_SSI_SLAVE,
    .instance_size = sizeof(SPIMFDState),
    .class_init    = spi_mfd_class_init,
};


static void spi_mfd_register_types(void)
{
    type_register_static(&spi_mfd_info);
}

type_init(spi_mfd_register_types)
