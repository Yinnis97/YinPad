
#include "YinPad.h"

int main()
{
    YinPad YinPad;


    while (YinPad.Running())
    {
        YinPad.Update();
        YinPad.Render();
    }

    return 0;
}

