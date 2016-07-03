/*
 * ov5645.h - header for YUV camera sensor OV5645 driver.
 *
 * Copyright (C) 2012 NVIDIA Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#ifndef __OV5645_H__
#define __OV5645_H__

#include <linux/ioctl.h>  /* For IOCTL macros */

#define OV5645_IOCTL_SET_SENSOR_MODE	_IOW('o', 1, struct ov5645_mode)
#define OV5645_IOCTL_GET_SENSOR_STATUS	_IOR('o', 2, __u8)
#define OV5645_IOCTL_GET_CONFIG		_IOR('o', 3, struct ov5645_config)
#define OV5645_IOCTL_SET_FPOSITION	_IOW('o', 4, __u32)
#define OV5645_IOCTL_POWER_LEVEL	_IOW('o', 5, __u32)
#define OV5645_IOCTL_GET_AF_STATUS	_IOR('o', 6, __u8)
#define OV5645_IOCTL_SET_AF_MODE	_IOR('o', 7, __u8)
#define OV5645_IOCTL_SET_WB		_IOR('o', 9, __u8)

#define OV5645_POWER_LEVEL_OFF		0
#define OV5645_POWER_LEVEL_ON		1
#define OV5645_POWER_LEVEL_SUS		2

struct ov5645_mode {
	int xres;
	int yres;
};

struct ov5645_config {
	__u32 settle_time;
	__u32 pos_low;
	__u32 pos_high;
	float focal_length;
	float fnumber;
};

enum{
	OV5645_GPIO_REST,
	OV5645_GPIO_PWD
};

enum {
	OV5645_AF_INIFINITY,
	OV5645_AF_TRIGGER,
};

enum {
	OV5645_WB_AUTO,
	OV5645_WB_INCANDESCENT,
	OV5645_WB_DAYLIGHT,
	OV5645_WB_FLUORESCENT,
	OV5645_WB_CLOUDY,
};

#ifdef __KERNEL__

struct ov5645_power_rail {
	struct regulator *vdd_osc;
	struct regulator *vdd_cam_1v8;
	struct regulator *vdd;
	struct regulator *avdd;
};

struct ov5645_platform_data {
	unsigned cfg;
	unsigned num;
	unsigned sync;
	const char *dev_name;
	unsigned gpio_count;
	struct nvc_gpio_pdata *gpio; /* see nvc.h GPIO notes */
	struct nvc_imager_cap *cap;
	unsigned lens_focal_length; /* / _INT2FLOAT_DIVISOR */
	unsigned lens_max_aperture; /* / _INT2FLOAT_DIVISOR */
	unsigned lens_fnumber; /* / _INT2FLOAT_DIVISOR */
	unsigned lens_view_angle_h; /* / _INT2FLOAT_DIVISOR */
	unsigned lens_view_angle_v; /* / _INT2FLOAT_DIVISOR */
	int (*probe_clock)(unsigned long);
	int (*power_on)(struct ov5645_power_rail *);
	int (*power_off)(struct ov5645_power_rail *);
};
#endif /* __KERNEL__ */

#endif  /* __OV5645_H__ */
