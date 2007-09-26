#ifndef VMACHINE_H
#define VMACHINE_H

#include "globals.h"

#include "cpu.h"
#include "extstorage.h"
#include "joysticks.h"
#include "keyboard.h"
#include "rom.h"
#include "vdc.h"

class VirtualMachine
{
    private:
        static const int UNPOLLED_FRAMES = 6;

        Rom rom_;
        Video video_;
        Vdc vdc_;
        ExternalStorage extstorage_;
        Keyboard keyboard_;
        Joysticks joysticks_;
        Cpu cpu_;

        void reset();

    public:
        VirtualMachine(const char *romfile, const char *biosfile);
        ~VirtualMachine();

        void run();
};

#endif