#ifndef CHARSET_H
#define CHARSET_H

static const int CHARSET_SIZE = 512;

static uint8_t charset[CHARSET_SIZE] = {
    0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00,
    0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
    0x3c, 0x66, 0x0c, 0x18, 0x30, 0x60, 0x7e, 0x00,
    0x7c, 0xc6, 0x06, 0x3c, 0x06, 0xc6, 0x7c, 0x00,
    0xcc, 0xcc, 0xcc, 0xfe, 0x0c, 0x0c, 0x0c, 0x00,
    0xfe, 0xc0, 0xc0, 0x7c, 0x06, 0xc6, 0x7c, 0x00,
    0x7c, 0xc6, 0xc0, 0xfc, 0xc6, 0xc6, 0x7c, 0x00,
    0xfe, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x00,
    0x7c, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0x7c, 0x00,
    0x7c, 0xc6, 0xc6, 0x7e, 0x06, 0xc6, 0x7c, 0x00,
    0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00,
    0x18, 0x7e, 0x58, 0x7e, 0x1a, 0x7e, 0x18, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3c, 0x66, 0x0c, 0x18, 0x18, 0x00, 0x18, 0x00,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0x00,
    0xfc, 0xc6, 0xc6, 0xfc, 0xc0, 0xc0, 0xc0, 0x00,
    0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00,
    0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00,
    0xfe, 0xc0, 0xc0, 0xf8, 0xc0, 0xc0, 0xfe, 0x00,
    0xfc, 0xc6, 0xc6, 0xfc, 0xd8, 0xcc, 0xc6, 0x00,
    0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00,
    0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
    0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00,
    0x7c, 0xc6, 0xc6, 0xc6, 0xde, 0xcc, 0x76, 0x00,
    0x7c, 0xc6, 0xc0, 0x7c, 0x06, 0xc6, 0x7c, 0x00,
    0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00,
    0xfe, 0xc0, 0xc0, 0xf8, 0xc0, 0xc0, 0xc0, 0x00,
    0x7c, 0xc6, 0xc0, 0xc0, 0xce, 0xc6, 0x7e, 0x00,
    0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00,
    0x06, 0x06, 0x06, 0x06, 0x06, 0xc6, 0x7c, 0x00,
    0xc6, 0xcc, 0xd8, 0xf0, 0xd8, 0xcc, 0xc6, 0x00,
    0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x00,
    0x7e, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x7e, 0x00,
    0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6, 0x00,
    0x7c, 0xc6, 0xc0, 0xc0, 0xc0, 0xc6, 0x7c, 0x00,
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00,
    0xfc, 0xc6, 0xc6, 0xfc, 0xc6, 0xc6, 0xfc, 0x00,
    0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x00,
    0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x00, 0x00,
    0x00, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x00, 0x00,
    0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x00,
    0xc6, 0xe6, 0xf6, 0xfe, 0xde, 0xce, 0xc6, 0x00,
    0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0xce, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xce, 0x00,
    0x00, 0x00, 0x3c, 0x7e, 0x7e, 0x7e, 0x3c, 0x00,
    0x1c, 0x1c, 0x18, 0x1e, 0x18, 0x18, 0x1c, 0x00,
    0x1c, 0x1c, 0x18, 0x1e, 0x18, 0x34, 0x26, 0x00,
    0x38, 0x38, 0x18, 0x78, 0x18, 0x2c, 0x64, 0x00,
    0x38, 0x38, 0x18, 0x78, 0x18, 0x18, 0x38, 0x00,
    0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00, 0x00,
    0x18, 0x3c, 0x7e, 0xff, 0xff, 0x18, 0x18, 0x00,
    0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0x00,
    0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0x00,
    0x38, 0x38, 0x12, 0xfe, 0xb8, 0x28, 0x6c, 0x00,
    0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x00,
    0x00, 0x00, 0x0c, 0x08, 0x08, 0xff, 0x7e, 0x00,
    0x00, 0x03, 0x63, 0xff, 0xff, 0x18, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x38, 0xff, 0x7e, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x6e, 0xff, 0x7e, 0x00
};

#endif