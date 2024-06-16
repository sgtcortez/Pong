#include "object/Pause.hpp"
#include <raylib.h>

using namespace ramboindustries;
using namespace component;
using namespace object;

Pause::Pause()
:
    paused(false)
{}

bool Pause::is_paused() const
{
    return paused;
}

void Pause::input()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        paused = !paused;
    }
}