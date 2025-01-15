#include "core/Application.h"

int main(int argc, char* argv[])
{
    Application app;
    if (app.init())
        app.loop();

    return 0;
}
