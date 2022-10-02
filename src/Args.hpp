#ifndef ARGS_H
#define ARGS_H

namespace OGLSample 
{

struct Arguments {
   int argc;
   const char* const *argv;
};

Arguments GetArguments();
void SetArguments(Arguments args);
int GetArgc();
const char* const* GetArgv();

}

#endif
