#ifndef ATAKAMA_ARGS_HPP
#define ATAKAMA_ARGS_HPP

namespace Atakama 
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
