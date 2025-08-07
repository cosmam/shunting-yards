#include "freebird/freebird.h"

#include <string.h>

int main(int argc, char const* argv[])
{
  (void)argc;
  (void)argv;

  return strcmp(exported_function(), "freebird") == 0 ? 0 : 1;
}
