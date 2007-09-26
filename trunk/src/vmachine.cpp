#include "globals.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "vmachine.h"

#include "options.h"
#include "speedlimit.h"

using namespace std;

VirtualMachine::VirtualMachine(const char *romfile, const char *biosfile)
    : vdc_(video_),
      extstorage_(vdc_),
      cpu_(rom_, extstorage_, keyboard_, joysticks_)
{
    rom_.load(romfile, biosfile);

    {
        const SDL_version *version = SDL_Linked_Version();
        cout << "Initializing SDL version " << (int)version->major
             << '.' << (int)version->minor << '.' << (int)version->patch << endl;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw(runtime_error(SDL_GetError()));
    }
    SDL_EnableKeyRepeat(0, 0);

    video_.init();
    vdc_.init(&cpu_);
    reset();
}

VirtualMachine::~VirtualMachine()
{
    SDL_Quit();
    cout << "Virtual machine quit" << endl;
}

inline void VirtualMachine::reset()
{
    g_p1 = g_p2 = 0xff;
    rom_.calculate_current_bank();

    g_t1 = true;

    cpu_.reset();
    vdc_.reset();
}

void VirtualMachine::run()
{
    int cpu_ticks = 0, vdc_ticks = 0;
    int breakpoint = -1;

    int cpu_units, vdc_units;
    if (g_options.pal_emulation) {
        // PAL system, each VDC tick is 5/3 (1.666...) 8048 ticks
        vdc_units = 5;
        cpu_units = 3;
    }
    else {
        // NTSC system, each VDC tick is 3/2 (1.5) 8048 ticks
        vdc_units = 3;
        cpu_units = 2;
    }

    while (true) {
        if (g_options.debug) {
            cout << "> ";
            cout.flush();
            string command;
            cin >> command;

            if (command == "b" || command == "breakpoint") {
                int addr;
                cin >> hex >> addr;
                if (cin.fail()) {
                    cout << "Invalid address" << endl;
                }
                else {
                    breakpoint = addr;
                    cout << "Breakpoint set at 0x" << hex << setw(2) << setfill('0') << addr << endl;
                }
            }
            else if (command == "c" || command == "continue") {
                g_options.debug = false;
            }
            else if (command == "e" || command == "extram") {
                extstorage_.debug_dump_extram(cout);
            }
            else if (command == "h" || command == "help") {
                cout << "The following commands are recognized:\n" \
                        "c/continue Return to emulation\n" \
                        "i/intram   Dump the contents of the internal RAM\n" \
                        "p/print    Print the contents of some CPU structures\n" \
                        "q/quit     Quit " PACKAGE_NAME "\n" \
                        "r/reset    Reset the virtual machine\n" \
                        "s/step     Execute a single CPU step\n" \
                        "v/vdc      Dump the contents of the VDC memory\n";
                cout.flush();
            }
            else if (command == "i" || command == "intram") {
                cpu_.debug_dump_intram(cout);
            }
            else if (command == "p" || command == "print") {
                cpu_.debug_print(cout);
            }
            else if (command == "q" || command == "quit" || cin.eof()) {
                if (cin.eof())
                    cout << endl;
                return;
            }
            else if (command == "r" || command == "reset") {
                reset();
                cout << "Reset the virtual machine" << endl;
            }
            else if (command == "s" || command == "step") {
                while (vdc_ticks < cpu_ticks) {
                    vdc_.step();
                    vdc_ticks += vdc_units;
                }
                cpu_ticks += cpu_.step() * cpu_units;

                if (vdc_ticks == cpu_ticks)
                    cpu_ticks = vdc_ticks = 0;

                cpu_.debug_print(cout);
            }
            else if (command == "v" || command == "vdc") {
                vdc_.debug_dump(cout);
            }
            else {
                cout << "Unknown command, use \"help\" or \"h\" for help" << endl;
            }
        }
        else {
            bool paused = false;
            SpeedLimit limit;

            while (!g_options.debug) {
                if (cpu_.debug_get_pc() == breakpoint) {
                    cpu_.debug_print(cout);
                    g_options.debug = true;
                    break;
                }

                // Check for SDL events
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            return;
                            break;
                        case SDL_KEYDOWN:
                            if (!joysticks_.handle_key_down(event.key.keysym))
                                keyboard_.handle_key_down(event.key.keysym);
                            break;
                        case SDL_KEYUP:
                            switch (event.key.keysym.sym) {
                                case SDLK_ESCAPE:
                                    return;
                                    break;
                                case SDLK_F1:
                                    if (paused)
                                        cout << "Returning to emulation" << endl;
                                    else
                                        cout << "-- PAUSED (press F1 to return to emulation) --" << endl;
                                    paused = !paused;
                                    break;
                                case SDLK_F4:
                                    g_options.debug = true;
                                    break;
                                case SDLK_F5:
                                    reset();
                                    cout << "Reset the virtual machine" << endl;
                                    break;
                                default:
                                    if (!joysticks_.handle_key_up(event.key.keysym))
                                        keyboard_.handle_key_up(event.key.keysym);
                                    break;
                            }
                            break;
                    }
                }

                for (int i = 0; i < UNPOLLED_FRAMES; ++i) {
                    while (!vdc_.entered_vblank() && !paused) {
                        if (vdc_ticks < cpu_ticks) {
                            vdc_.step();
                            vdc_ticks += vdc_units;
                        }
                        else {
                            cpu_ticks += cpu_.step() * cpu_units;
                        }

                        if (vdc_ticks == cpu_ticks)
                            cpu_ticks = vdc_ticks = 0;
                    }

                    // Speed limiter
                    if (g_options.speed_limit)
                        limit.limit_on_frame_end();
                }
            }

            // Just entered debug mode
            SDL_WM_IconifyWindow();
        }
    }
}