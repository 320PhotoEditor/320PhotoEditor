#include "Application.h"

int main()
{
    Application application;

    if (!application.init("Test"))
    {
        return EXIT_FAILURE;
    }

    application.run();

    return EXIT_SUCCESS;
}