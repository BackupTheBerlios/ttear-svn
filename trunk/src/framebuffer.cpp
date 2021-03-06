#include "common.h"

#include <sstream>

#include "framebuffer.h"

#include "options.h"

Framebuffer *g_framebuffer = NULL;

const uint8_t Framebuffer::colortable_[Framebuffer::COLORTABLE_SIZE][3] = {
    // Light background and grid colors
    { 95, 110, 107}, // dark gray
    {106, 161, 255}, // blue
    { 61, 240, 122}, // green
    { 49, 255, 255}, // cyan
    {255,  66,  85}, // red
    {255, 152, 255}, // violet
    {217, 173,  93}, // yellow
    {255, 255, 255}, // white

    // Dark background and grid colors
    {  0,   0,   0}, // black
    { 14,  61, 212}, // dark blue
    {  0, 152,  27}, // dark green
    {  0, 187, 217}, // cyan
    {199,   0,   8}, // red
    {204,  22, 179}, // violet
    {157, 135,  16}, // orange
    {225, 209, 225}  // light gray
};

Framebuffer::Framebuffer()
{
    if (g_options.keep_aspect) {
        window_size_.x_scale = (float)g_options.x_res / 4;
        window_size_.y_scale = (float)g_options.y_res / 3;

        float scale = window_size_.x_scale < window_size_.y_scale ? window_size_.x_scale : window_size_.y_scale;

        window_size_.x = (unsigned int)((g_options.x_res - scale * 4) / 2);
        window_size_.y = (unsigned int)((g_options.y_res - scale * 3) / 2);
        window_size_.x_end = (unsigned int)(window_size_.x + scale * 4);
        window_size_.y_end = (unsigned int)(window_size_.y + scale * 3);

        window_size_.x_scale = scale * 4 / SCREEN_WIDTH;
        window_size_.y_scale = scale * 3 / SCREEN_HEIGHT;
    }
    else {
        window_size_.x_scale = (float)g_options.x_res / SCREEN_WIDTH;
        window_size_.y_scale = (float)g_options.y_res / SCREEN_HEIGHT;

        window_size_.x = 0;
        window_size_.y = 0;
        window_size_.x_end = g_options.x_res;
        window_size_.y_end = g_options.y_res;
    }
}

void Framebuffer::take_snapshot()
{
    static int snapshot_index = 0;

    if (g_options.snapshot_dir.empty())
        return;

    ostringstream oss;
    oss << g_options.snapshot_dir << "/snapshot_" << setfill('0') << setw(4) << snapshot_index++ << ".bmp";
    take_snapshot(oss.str());
}
