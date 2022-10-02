#include "Application.hpp"
#include "Args.hpp"

int main(int argc, char** argv)
{
    OGLSample::SetArguments({argc, argv});

    OGLSample::Application app;
    app.run();

    return 0;
}
