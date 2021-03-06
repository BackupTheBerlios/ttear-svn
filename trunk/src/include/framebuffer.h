#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "common.h"

class Framebuffer
{
    protected:
        struct {
            unsigned int x, y;
            unsigned int x_end, y_end;
            float x_scale, y_scale;
        } window_size_;

        static const int COLORTABLE_SIZE = 16;
        static const uint8_t colortable_[COLORTABLE_SIZE][3];

    public:
        static const int SCREEN_WIDTH_MULTIPLIER = 5;
        static const int SCREEN_WIDTH = 170 * SCREEN_WIDTH_MULTIPLIER;
        static const int SCREEN_HEIGHT = 242;

        Framebuffer();
        virtual ~Framebuffer() {}

        virtual void init() = 0;

        virtual void set_clip_rect(SDL_Rect &r) = 0;
        virtual void clear_clip_rect() = 0;
        virtual void fill_rect(SDL_Rect &r, int color) = 0;

        virtual void paste_surface(int x, int y, SDL_Surface *surface) = 0;
        virtual void paste_surface(int x, int y, SDL_Surface *surface, SDL_Rect &src_r) = 0;

        virtual void blit() = 0;

        void take_snapshot();
        virtual void take_snapshot(const string &str) = 0;
};

extern Framebuffer *g_framebuffer;

#endif
