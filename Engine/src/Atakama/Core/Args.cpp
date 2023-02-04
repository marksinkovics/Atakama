#include "Args.hpp"

namespace Atakama
{

static Arguments __arguments;

Arguments GetArguments()
{
  return __arguments;
}

void SetArguments(Arguments args)
{
  __arguments = args;
}

int GetArgc()
{
  return __arguments.argc;
}

const char* const* GetArgv()
{
  return __arguments.argv;
}

}
