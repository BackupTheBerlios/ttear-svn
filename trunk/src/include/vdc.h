#ifndef VDC_H
#define VDC_H

#include "common.h"

#include <vector>

#include "framebuffer.h"
#include "options.h"

class Vdc
{
    private:
        static const int MEMORY_SIZE = 256;

        static const int CONTROL_REGISTER = 0xa0;
        static const int STATUS_REGISTER = 0xa1;
        static const int COLLISION_REGISTER = 0xa2;
        static const int COLOR_REGISTER = 0xa3;
        static const int Y_REGISTER = 0xa4;
        static const int X_REGISTER = 0xa5;

        static const int HORIZONTAL_GRID_START = 0xc0;
        static const int HORIZONTAL_GRID9_START = 0xd0;
        static const int VERTICAL_GRID_START = 0xe0;

        static const int COLLISION_SPRITE0 = 0;
        static const int COLLISION_SPRITE1 = 1;
        static const int COLLISION_SPRITE2 = 2;
        static const int COLLISION_SPRITE3 = 3;
        static const int COLLISION_VGRID = 4;
        static const int COLLISION_HGRID = 5;
        static const int COLLISION_EXTERNAL = 6;
        static const int COLLISION_CHAR = 7;

        static const int CYCLES_PER_SCANLINE = 228;
        static const int HBLANK_START = 178;
        static const int HBLANK_END = 222;

        vector<uint8_t> mem_;

        int cycles_, scanlines_, cur_frame_;
        const int first_drawing_scanline_;

        static bool entered_vblank_;

        bool grid_enabled() { return mem_[CONTROL_REGISTER] & 1 << 3; }
        bool foreground_enabled() { return mem_[CONTROL_REGISTER] & 1 << 5; }

        void draw_background(SDL_Rect &clip_r);
        void draw_grid(SDL_Rect &clip_r);
        void draw_rect(SDL_Rect &clip_r);

        bool screen_drawn_;
        void draw_screen();
        void update_screen();

        uint8_t latched_x_, latched_y_;

    public:
        Vdc();

        void init();

        void reset();
        void step();

        uint8_t read(uint8_t offset);
        void write(uint8_t offset, uint8_t value);

        bool entered_vblank();

        void debug_dump(ostream &out) const { dump_memory(out, mem_, MEMORY_SIZE); }
        void debug_print_timing(ostream &out);
};

extern Vdc g_vdc;

inline bool Vdc::entered_vblank()
{
    if (entered_vblank_) {
        entered_vblank_ = false;
        return true;
    }
    else {
        return false;
    }
}

#endif
