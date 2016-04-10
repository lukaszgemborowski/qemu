/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "hw/sysbus.h"

#define TYPE_DUMMY_MM "dummy_mm"
#define DUMMY_MM(obj) \
    OBJECT_CHECK(DummyMMState, (obj), TYPE_DUMMY_MM)

typedef struct DummyMMState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
} DummyMMState;

static uint64_t dummy_mm_read(void *opaque, hwaddr offset,
                                   unsigned size)
{
	static int value = 0;

    if (offset == 0) {
		return value++;
    } else {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%x\n", __func__, (int)offset);
        return -1;
    }
}

static void dummy_mm_write(void *opaque, hwaddr offset,
                                uint64_t value, unsigned size)
{
    //DummyMMState *s = (DummyMMState *)opaque;

    switch (offset) {
    case 0:
        break;
    case 4:
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%x\n", __func__, (int)offset);
    }
}

static const MemoryRegionOps dummy_mm_ops = {
    .read = dummy_mm_read,
    .write = dummy_mm_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static int dummy_mm_init(SysBusDevice *sbd)
{
    DeviceState *dev = DEVICE(sbd);
    DummyMMState *s = DUMMY_MM(dev);

    memory_region_init_io(&s->iomem, OBJECT(s), &dummy_mm_ops, s,
                          "dummy_mm", 0x1000);
    sysbus_init_mmio(sbd, &s->iomem);
    return 0;
}

static void dummy_mm_class_init(ObjectClass *klass, void *data)
{
    SysBusDeviceClass *k = SYS_BUS_DEVICE_CLASS(klass);

    k->init = dummy_mm_init;
}

static const TypeInfo dummy_mm_info = {
    .name          = TYPE_DUMMY_MM,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(DummyMMState),
    .class_init    = dummy_mm_class_init,
};

static void dummy_mm_register_types(void)
{
    type_register_static(&dummy_mm_info);
}

type_init(dummy_mm_register_types)
