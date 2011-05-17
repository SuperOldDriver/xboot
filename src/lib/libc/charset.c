/*
 * lib/libc/charset.c
 */

#include <xboot.h>
#include <types.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <charset.h>

/*
 * non-spacing attribute table.
 */
static const u8_t nonspacing_table_data[26 * 64] = {
	/* 0x0000-0x01ff */
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, /* 0x0000-0x003f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, /* 0x0040-0x007f */
	0xff, 0xff, 0xff, 0xff, 0x00, 0x20, 0x00, 0x00, /* 0x0080-0x00bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00c0-0x00ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0100-0x013f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0140-0x017f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0180-0x01bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x01c0-0x01ff */
	/* 0x0200-0x03ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0200-0x023f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0240-0x027f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0280-0x02bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x02c0-0x02ff */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* 0x0300-0x033f */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, /* 0x0340-0x037f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0380-0x03bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x03c0-0x03ff */
	/* 0x0400-0x05ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0400-0x043f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0440-0x047f */
	0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0480-0x04bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x04c0-0x04ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0500-0x053f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0540-0x057f */
	0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xbf, /* 0x0580-0x05bf */
	0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x05c0-0x05ff */
	/* 0x0600-0x07ff */
	0x0f, 0x00, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, /* 0x0600-0x063f */
	0x00, 0xf8, 0xff, 0x7f, 0x00, 0x00, 0x01, 0x00, /* 0x0640-0x067f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0680-0x06bf */
	0x00, 0x00, 0xc0, 0xff, 0x9f, 0x3d, 0x00, 0x00, /* 0x06c0-0x06ff */
	0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0xff, 0xff, /* 0x0700-0x073f */
	0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0740-0x077f */
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, /* 0x0780-0x07bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f, 0x00, /* 0x07c0-0x07ff */
	/* 0x0800-0x09ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0800-0x083f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0840-0x087f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0880-0x08bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08c0-0x08ff */
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, /* 0x0900-0x093f */
	0xfe, 0x21, 0x1e, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0940-0x097f */
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, /* 0x0980-0x09bf */
	0x1e, 0x20, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x09c0-0x09ff */
	/* 0x0a00-0x0bff */
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, /* 0x0a00-0x0a3f */
	0x86, 0x39, 0x02, 0x00, 0x00, 0x00, 0x23, 0x00, /* 0x0a40-0x0a7f */
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, /* 0x0a80-0x0abf */
	0xbe, 0x21, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0ac0-0x0aff */
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, /* 0x0b00-0x0b3f */
	0x1e, 0x20, 0x40, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0b40-0x0b7f */
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0b80-0x0bbf */
	0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0bc0-0x0bff */
	/* 0x0c00-0x0dff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, /* 0x0c00-0x0c3f */
	0xc1, 0x3d, 0x60, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0c40-0x0c7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, /* 0x0c80-0x0cbf */
	0x00, 0x30, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0cc0-0x0cff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0d00-0x0d3f */
	0x1e, 0x20, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, /* 0x0d40-0x0d7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0d80-0x0dbf */
	0x00, 0x04, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0dc0-0x0dff */
	/* 0x0e00-0x0fff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x07, /* 0x0e00-0x0e3f */
	0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0e40-0x0e7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x1b, /* 0x0e80-0x0ebf */
	0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0ec0-0x0eff */
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xa0, 0x02, /* 0x0f00-0x0f3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, /* 0x0f40-0x0f7f */
	0xdf, 0x00, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x1f, /* 0x0f80-0x0fbf */
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x0fc0-0x0fff */
	/* 0x1000-0x11ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfd, 0x66, /* 0x1000-0x103f */
	0x00, 0x00, 0x00, 0xc3, 0x01, 0x00, 0x1e, 0x00, /* 0x1040-0x107f */
	0x64, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1080-0x10bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10c0-0x10ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1100-0x113f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1140-0x117f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1180-0x11bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x11c0-0x11ff */
	/* 0x1200-0x13ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1200-0x123f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1240-0x127f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1280-0x12bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x12c0-0x12ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1300-0x133f */
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, /* 0x1340-0x137f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1380-0x13bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x13c0-0x13ff */
	/* 0x1600-0x17ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1600-0x163f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1640-0x167f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1680-0x16bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x16c0-0x16ff */
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, /* 0x1700-0x173f */
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, /* 0x1740-0x177f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x3f, /* 0x1780-0x17bf */
	0x40, 0xfe, 0x0f, 0x20, 0x00, 0x00, 0x00, 0x00, /* 0x17c0-0x17ff */
	/* 0x1800-0x19ff */
	0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1800-0x183f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1840-0x187f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, /* 0x1880-0x18bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18c0-0x18ff */
	0x00, 0x00, 0x00, 0x00, 0x87, 0x01, 0x04, 0x0e, /* 0x1900-0x193f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1940-0x197f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1980-0x19bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x19c0-0x19ff */
	/* 0x1a00-0x1bff */
	0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, /* 0x1a00-0x1a3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1a40-0x1a7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1a80-0x1abf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1ac0-0x1aff */
	0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x17, /* 0x1b00-0x1b3f */
	0x04, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f, 0x00, /* 0x1b40-0x1b7f */
	0x03, 0x00, 0x00, 0x00, 0x3c, 0x03, 0x00, 0x00, /* 0x1b80-0x1bbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1bc0-0x1bff */
	/* 0x1c00-0x1dff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xcf, 0x00, /* 0x1c00-0x1c3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1c40-0x1c7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1c80-0x1cbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1cc0-0x1cff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d00-0x1d3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d40-0x1d7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d80-0x1dbf */
	0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xc0, /* 0x1dc0-0x1dff */
	/* 0x2000-0x21ff */
	0x00, 0xf8, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, /* 0x2000-0x203f */
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, /* 0x2040-0x207f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2080-0x20bf */
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, /* 0x20c0-0x20ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2100-0x213f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2140-0x217f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2180-0x21bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x21c0-0x21ff */
	/* 0x2c00-0x2dff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2c00-0x2c3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2c40-0x2c7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2c80-0x2cbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2cc0-0x2cff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2d00-0x2d3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2d40-0x2d7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2d80-0x2dbf */
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, /* 0x2dc0-0x2dff */
	/* 0x3000-0x31ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, /* 0x3000-0x303f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x3040-0x307f */
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, /* 0x3080-0x30bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30c0-0x30ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x3100-0x313f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x3140-0x317f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x3180-0x31bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x31c0-0x31ff */
	/* 0xa600-0xa7ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa600-0xa63f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x30, /* 0xa640-0xa67f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa680-0xa6bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa6c0-0xa6ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa700-0xa73f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa740-0xa77f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa780-0xa7bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa7c0-0xa7ff */
	/* 0xa800-0xa9ff */
	0x44, 0x08, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, /* 0xa800-0xa83f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa840-0xa87f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa880-0xa8bf */
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa8c0-0xa8ff */
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x00, /* 0xa900-0xa93f */
	0x80, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa940-0xa97f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa980-0xa9bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa9c0-0xa9ff */
	/* 0xaa00-0xabff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x66, 0x00, /* 0xaa00-0xaa3f */
	0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xaa40-0xaa7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xaa80-0xaabf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xaac0-0xaaff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xab00-0xab3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xab40-0xab7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xab80-0xabbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xabc0-0xabff */
	/* 0xfa00-0xfbff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfa00-0xfa3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfa40-0xfa7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfa80-0xfabf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfac0-0xfaff */
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, /* 0xfb00-0xfb3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfb40-0xfb7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfb80-0xfbbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfbc0-0xfbff */
	/* 0xfe00-0xffff */
	0xff, 0xff, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, /* 0xfe00-0xfe3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfe40-0xfe7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xfe80-0xfebf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, /* 0xfec0-0xfeff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xff00-0xff3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xff40-0xff7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xff80-0xffbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, /* 0xffc0-0xffff */
	/* 0x10000-0x101ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10000-0x1003f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10040-0x1007f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10080-0x100bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x100c0-0x100ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10100-0x1013f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10140-0x1017f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10180-0x101bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, /* 0x101c0-0x101ff */
	/* 0x10a00-0x10bff */
	0x6e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, /* 0x10a00-0x10a3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10a40-0x10a7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10a80-0x10abf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10ac0-0x10aff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10b00-0x10b3f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10b40-0x10b7f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10b80-0x10bbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10bc0-0x10bff */
	/* 0x1d000-0x1d1ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d000-0x1d03f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d040-0x1d07f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d080-0x1d0bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d0c0-0x1d0ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d100-0x1d13f */
	0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0xf8, /* 0x1d140-0x1d17f */
	0xe7, 0x0f, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, /* 0x1d180-0x1d1bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d1c0-0x1d1ff */
	/* 0x1d200-0x1d3ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d200-0x1d23f */
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d240-0x1d27f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d280-0x1d2bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d2c0-0x1d2ff */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d300-0x1d33f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d340-0x1d37f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x1d380-0x1d3bf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* 0x1d3c0-0x1d3ff */
};

static const s8_t nonspacing_table_ind[240] = {
	0,   1,  2,  3,  4,  5,  6,  7,					/* 0x0000-0x0fff */
	8,   9, -1, 10, 11, 12, 13, -1,					/* 0x1000-0x1fff */
	14, -1, -1, -1, -1, -1, 15, -1,					/* 0x2000-0x2fff */
	16, -1, -1, -1, -1, -1, -1, -1,					/* 0x3000-0x3fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x4000-0x4fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x5000-0x5fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x6000-0x6fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x7000-0x7fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x8000-0x8fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x9000-0x9fff */
	-1, -1, -1, 17, 18, 19, -1, -1,					/* 0xa000-0xafff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0xb000-0xbfff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0xc000-0xcfff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0xd000-0xdfff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0xe000-0xefff */
	-1, -1, -1, -1, -1, 20, -1, 21,					/* 0xf000-0xffff */
	22, -1, -1, -1, -1, 23, -1, -1,					/* 0x10000-0x10fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x11000-0x11fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x12000-0x12fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x13000-0x13fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x14000-0x14fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x15000-0x15fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x16000-0x16fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x17000-0x17fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x18000-0x18fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x19000-0x19fff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x1a000-0x1afff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x1b000-0x1bfff */
	-1, -1, -1, -1, -1, -1, -1, -1,					/* 0x1c000-0x1cfff */
	24, 25, -1, -1, -1, -1, -1, -1					/* 0x1d000-0x1dfff */
};

/*
 * utf8_to_ucs4 - convert a UTF-8 string to UCS-4 string
 */
ssize_t utf8_to_ucs4(u32_t * dst, size_t dst_size, const char * src, size_t src_size, const char ** src_end)
{
	u32_t *p = dst;
	int count = 0;
	u32_t code = 0;
	u32_t c;

	if(src_end)
		*src_end = src;

	while(src_size && dst_size)
	{
		c = *src++;
		if(src_size != (size_t)-1)
			src_size--;
		if(count)
		{
			if((c & 0xc0) != 0x80)
			{
				code = '?';
				/* character c may be valid, don't eat it */
				src--;
				if(src_size != (size_t)-1)
					src_size++;
				count = 0;
			}
			else
			{
				code <<= 6;
				code |= (c & 0x3f);
				count--;
			}
		}
		else
		{
			if(c == 0)
				break;

			if((c & 0x80) == 0x00)
				code = c;
			else if((c & 0xe0) == 0xc0)
			{
				count = 1;
				code = c & 0x1f;
			}
			else if((c & 0xf0) == 0xe0)
			{
				count = 2;
				code = c & 0x0f;
			}
			else if((c & 0xf8) == 0xf0)
			{
				count = 3;
				code = c & 0x07;
			}
			else if((c & 0xfc) == 0xf8)
			{
				count = 4;
				code = c & 0x03;
			}
			else if((c & 0xfe) == 0xfc)
			{
				count = 5;
				code = c & 0x01;
			}
			else
			{
				code = '?';
				count = 0;
			}
		}

		if (count == 0)
		{
			*p++ = code;
			dst_size--;
		}
	}

	if(src_end)
		*src_end = src;

	return p - dst;
}

/*
 * utf4_to_utf8 - convert a UCS-4 to UTF-8
 */
char * ucs4_to_utf8(u32_t * src, size_t src_size, char * dst, size_t dst_size)
{
	char * destend = dst + dst_size - 1;
	char * p = dst;
	u32_t code = 0;

	while(src_size-- && p < destend)
	{
		code = *src++;

		if(code <= 0x007F)
			*p++ = code;
		else if(code <= 0x07FF)
		{
			if(p + 1 >= destend)
				break;
			*p++ = (code >> 6) | 0xC0;
			*p++ = (code & 0x3F) | 0x80;
		}
		else if((code >= 0xDC00 && code <= 0xDFFF) || (code >= 0xD800 && code <= 0xDBFF))
		{
			*p++ = '?';
		}
		else if(code < 0x10000)
		{
			if(p + 2 >= destend)
				break;
			*p++ = (code >> 12) | 0xE0;
			*p++ = ((code >> 6) & 0x3F) | 0x80;
			*p++ = (code & 0x3F) | 0x80;
		}
		else
		{
			if(p + 3 >= destend)
				break;
			*p++ = (code >> 18) | 0xF0;
			*p++ = ((code >> 12) & 0x3F) | 0x80;
			*p++ = ((code >> 6) & 0x3F) | 0x80;
			*p++ = (code & 0x3F) | 0x80;
		}
	}

	*p = 0;
	return dst;
}

/*
 * utf8_to_utf16 - convert a UTF-8 string to UTF-16 string
 */
ssize_t utf8_to_utf16(u16_t * dst, size_t dst_size, const char * src, size_t src_size, const char ** src_end)
{
	u16_t *p = dst;
	int count = 0;
	u32_t code = 0;
	u32_t c;

	if(src_end)
		*src_end = src;

	while(src_size && dst_size)
	{
		c = *src++;
		if(src_size != (size_t)-1)
			src_size--;
		if(count)
		{
			if ((c & 0xc0) != 0x80)
			{
				return -1;
			}
			else
			{
				code <<= 6;
				code |= (c & 0x3f);
				count--;
			}
		}
		else
		{
			if(c == 0)
				break;

			if((c & 0x80) == 0)
				code = c;
			else if((c & 0xe0) == 0xc0)
			{
				count = 1;
				code = c & 0x1f;
			}
			else if((c & 0xf0) == 0xe0)
			{
				count = 2;
				code = c & 0x0f;
			}
			else if((c & 0xf8) == 0xf0)
			{
				count = 3;
				code = c & 0x07;
			}
			else if((c & 0xfc) == 0xf8)
			{
				count = 4;
				code = c & 0x03;
			}
			else if((c & 0xfe) == 0xfc)
			{
				count = 5;
				code = c & 0x01;
			}
			else
				return -1;
		}

		if(count == 0)
		{
			if((dst_size < 2) && (code >= 0x10000))
				break;
			if(code >= 0x10000)
			{
				*p++ = (0xd800 + ((((code) - 0x10000) >> 12) & 0xfff));
				*p++ = (0xdc00 + (((code) - 0x10000) & 0xfff));
				dst_size -= 2;
			}
			else
			{
				*p++ = code;
				dst_size--;
			}
		}
    }

	if(src_end)
		*src_end = src;

	return p - dst;
}

/*
 * utf16_to_utf8 - convert a UTF-16 string to UTF-8 string
 */
char * utf16_to_utf8(char * dst, u16_t * src, size_t size)
{
	u32_t code_high = 0;
	u32_t code;

	while(size--)
	{
		code = *src++;

		if(code_high)
		{
			if(code >= 0xDC00 && code <= 0xDFFF)
			{
				code = ((code_high - 0xD800) << 12) + (code - 0xDC00) + 0x10000;

				*dst++ = (code >> 18) | 0xF0;
				*dst++ = ((code >> 12) & 0x3F) | 0x80;
				*dst++ = ((code >> 6) & 0x3F) | 0x80;
				*dst++ = (code & 0x3F) | 0x80;
			}
			else
			{
				*dst++ = '?';
			}

			code_high = 0;
		}
		else
		{
			if(code <= 0x007F)
				*dst++ = code;
			else if(code <= 0x07FF)
			{
				*dst++ = (code >> 6) | 0xC0;
				*dst++ = (code & 0x3F) | 0x80;
			}
			else if(code >= 0xD800 && code <= 0xDBFF)
			{
				code_high = code;
				continue;
			}
			else if(code >= 0xDC00 && code <= 0xDFFF)
			{
				*dst++ = '?';
			}
			else
			{
				*dst++ = (code >> 12) | 0xE0;
				*dst++ = ((code >> 6) & 0x3F) | 0x80;
				*dst++ = (code & 0x3F) | 0x80;
			}
		}
	}

	return dst;
}

/*
 * utf4_to_utf8_alloc - convert a UCS-4 to UTF-8
 */
char * ucs4_to_utf8_alloc(u32_t * src, size_t size)
{
	size_t remaining;
	u32_t * ptr;
	u32_t code;
	size_t cnt = 0;
	char * ret;

	remaining = size;
	ptr = src;

	while(remaining--)
	{
		code = *ptr++;

		if(code <= 0x007F)
			cnt++;
		else if(code <= 0x07FF)
			cnt += 2;
		else if((code >= 0xDC00 && code <= 0xDFFF) || (code >= 0xD800 && code <= 0xDBFF))
			cnt++;
		else if(code < 0x10000)
			cnt += 3;
		else
			cnt += 4;
	}
	cnt++;

	ret = malloc(cnt);
	if(!ret)
		return 0;

	ucs4_to_utf8(src, size, ret, cnt);
	return ret;
}

/*
 * utf8_to_ucs4_alloc - convert a UTF-8 string to UCS-4 string
 */
ssize_t utf8_to_ucs4_alloc(const char * src, u32_t ** dst, u32_t ** pos)
{
	ssize_t len = strlen((char *)src);

	*dst = malloc(len * sizeof(u32_t));

	if(!*dst)
		return -1;

	len = utf8_to_ucs4(*dst, len, src, -1, 0);

	if(pos)
		*pos = *dst + len;

	return len;
}

/*
 * determine number of column positions required for unicode
  */
int ucs4_width(u32_t uc)
{
	bool_t cjk = FALSE;
	int ind;

	/*
	 * test for non-spacing or control character
	 */
	if((uc >> 9) < 240)
	{
		ind = nonspacing_table_ind[uc >> 9];
		if(ind >= 0)
		{
			if((nonspacing_table_data[64*ind + ((uc >> 3) & 63)] >> (uc & 7)) & 1)
			{
				if(uc > 0 && uc < 0xa0)
					return -1;
				else
					return 0;
			}
		}
	}
	else if((uc >> 9) == (0xe0000 >> 9))
	{
		if(uc >= 0xe0100)
		{
			if(uc <= 0xe01ef)
				return 0;
		}
		else
		{
			if(uc >= 0xe0020 ? uc <= 0xe007f : uc == 0xe0001)
				return 0;
		}
	}

	/*
	 * test for double-width character
	 */
	if( (uc >= 0x1100) && ((uc < 0x1160)
		|| (uc >= 0x2329 && uc < 0x232b)
		|| (uc >= 0x2e80 && uc < 0xa4d0 && !(uc == 0x303f) && !(uc >= 0x4dc0 && uc < 0x4e00))
		|| (uc >= 0xac00 && uc < 0xd7a4)
		|| (uc >= 0xf900 && uc < 0xfb00)
		|| (uc >= 0xfe10 && uc < 0xfe20)
		|| (uc >= 0xfe30 && uc < 0xfe70)
		|| (uc >= 0xff00 && uc < 0xff61)
		|| (uc >= 0xffe0 && uc < 0xffe7)
		|| (uc >= 0x20000 && uc <= 0x2a6d6)
		|| (uc >= 0x2f800 && uc <= 0x2fa1d)) )
		return 2;

	/*
	 * in ancient cjk encodings
	 */
	if(uc >= 0x00A1 && uc < 0xFF61 && uc != 0x20A9 && cjk)
		return 2;

	return 1;
}

/*
 * determine number of column positions required for utf8 string
  */
size_t utf8_width(const char * s)
{
	const char * p;
	u32_t code;
	size_t width;
	int w;

	for(width = 0, p = s; utf8_to_ucs4(&code, 1, p, -1, &p) > 0; )
	{
		w = ucs4_width(code);
		if(w < 0)
			w = 0;
		width += w;
	}

	return width;
}

bool_t utf8_is_valid(const char * src, size_t size)
{
	u32_t code = 0;
	int count = 0;
	u32_t c;

	while(size)
	{
		c = *src++;
		if(size != (size_t)-1)
			size--;

		if(count)
		{
			if((c & 0xc0) != 0x80)
			{
				return FALSE;
			}
			else
			{
				code <<= 6;
				code |= (c & 0x3f);
				count--;
			}
		}
		else
		{
			if(c == 0)
				break;

			if((c & 0x80) == 0x00)
				code = c;
			else if ((c & 0xe0) == 0xc0)
			{
				count = 1;
				code = c & 0x1f;
			}
			else if ((c & 0xf0) == 0xe0)
			{
				count = 2;
				code = c & 0x0f;
			}
			else if ((c & 0xf8) == 0xf0)
			{
				count = 3;
				code = c & 0x07;
			}
			else
				return FALSE;
		}
	}

	return TRUE;
}

size_t utf8_strlen(const char * s)
{
	size_t i = 0, j = 0;

	while(s[i])
	{
		if((s[i] & 0xc0) != 0x80)
			j++;
		i++;
	}

	return j;
}
