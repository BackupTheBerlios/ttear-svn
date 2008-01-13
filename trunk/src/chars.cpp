#include "common.h"

#include <iostream>
#include <stdexcept>

#include "chars.h"

#include "colors.h"
#include "framebuffer.h"

Chars g_chars;

const uint8_t Chars::charset_[Chars::NUM_CHARS * 8] = {
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

void Chars::init()
{
    // Create the surfaces
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    static const uint32_t rmask = 0xff000000;
    static const uint32_t gmask = 0x00ff0000;
    static const uint32_t bmask = 0x0000ff00;
    static const uint32_t amask = 0x000000ff;
#else
    static const uint32_t rmask = 0x000000ff;
    static const uint32_t gmask = 0x0000ff00;
    static const uint32_t bmask = 0x00ff0000;
    static const uint32_t amask = 0xff000000;
#endif
    for (int i = 0; i < 8; ++i) {
        surfaces_[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
                16 * Framebuffer::SCREEN_WIDTH_MULTIPLIER,
                NUM_CHARS * 16, 32, rmask, gmask, bmask, amask);
        if (!surfaces_[i])
            throw runtime_error(SDL_GetError());
        else if (surfaces_[i]->format->BitsPerPixel != 32)
            throw runtime_error("Unable to create a 32bpp surface");
    }

    // Initialize the colormap
    uint32_t colormap[8];
    for (int i = 0; i < 8; ++i)
        colormap[i] = SDL_MapRGB(surfaces_[i]->format, colortable[i + COLORTABLE_CHAR_OFFSET][0],
                colortable[i + COLORTABLE_CHAR_OFFSET][1], colortable[i + COLORTABLE_CHAR_OFFSET][2]);

    // Draw the chars
    for (int clr_idx = 0; clr_idx < 8; ++clr_idx) {
        if (SDL_MUSTLOCK(surfaces_[clr_idx])) {
            if (SDL_LockSurface(surfaces_[clr_idx]))
                throw runtime_error(SDL_GetError());
        }
        create_chars(surfaces_[clr_idx], colormap[clr_idx]);
        if (SDL_MUSTLOCK(surfaces_[clr_idx]))
            SDL_UnlockSurface(surfaces_[clr_idx]);
    }
}

void Chars::create_chars(SDL_Surface *surface, uint32_t color)
{
    static int surface_idx = 0;
    cout << "Initializing chars for color " << surface_idx++ << ": ";
    cout.flush();

    memset(surface->pixels, SDL_ALPHA_TRANSPARENT, surface->pitch * 16);

    for (int chr_idx = 0; chr_idx < NUM_CHARS; ++chr_idx) {
        for (int byte_idx = 0; byte_idx < 8; ++byte_idx) {
            const uint8_t &bitfield = charset_[chr_idx * 8 + byte_idx];
            for (int bit_idx = 0; bit_idx < 8; ++bit_idx) {
                if (bitfield & 1 << 7 - bit_idx) {
                    SDL_Rect r = {bit_idx * Framebuffer::SCREEN_WIDTH_MULTIPLIER,
                        chr_idx * 16 + byte_idx * 2, Framebuffer::SCREEN_WIDTH_MULTIPLIER, 2};
                    SDL_FillRect(surface, &r, color);
                }
            }
        }
        cout << '|';
        cout.flush();
    }
    cout << endl;
}

inline SDL_Rect Chars::get_rect(int index, int cut_top, int cut_bottom)
{
    index &= ~(1 << 0 | 1 << 1 | 1 << 2);
    SDL_Rect r = {0, (index + cut_top) * 2,
        8 * Framebuffer::SCREEN_WIDTH_MULTIPLIER,
        (cut_bottom == -1 ? 8 - cut_top : cut_bottom) * 2};
    return r;
}

inline void Chars::draw_char(int x, int y, uint8_t *ptr, SDL_Rect &clip_r, int cut_bottom)
{
    if (x < 4 || x > 228 || y + 16 < clip_r.y || y > clip_r.y + clip_r.h)
        return;
 
    x = x % 228 + 4;
    uint8_t &control = ptr[3];

    int charset_index = (ptr[2] + ((control & 1 << 0) << 8) + y / 2) % (NUM_CHARS * 8);
    SDL_Rect r = get_rect(charset_index, charset_index % 8, cut_bottom);

    // Note that chars are 1/Framebuffer::SCREEN_WIDTH_MULTIPLIER pixels shifted to the left
    g_framebuffer->paste_surface(x * Framebuffer::SCREEN_WIDTH_MULTIPLIER - 1, y,
            surfaces_[(control & (1 << 1 | 1 << 2 | 1 << 3)) >> 1], r);
}

void Chars::draw(uint8_t *mem, SDL_Rect &clip_r)
{
    for (uint8_t *ptr = &mem[CHARS_START]; ptr != &mem[CHARS_START + 48]; ptr += 4)
        draw_char(ptr[1], ptr[0], ptr, clip_r);

    for (uint8_t *ptr = &mem[QUADS_START]; ptr != &mem[QUADS_START + 64]; ptr += 16) {
        int y = ptr[0];
        int x = ptr[1];
        int cut_bottom = 8 - (ptr[14] + (ptr[15] & 1 << 0) + y / 2) % 8;
        for (int i = 0; i < 16; i += 4) {
            draw_char(x, y, &ptr[i], clip_r, cut_bottom);
            x += 16;
        }
    }
}
