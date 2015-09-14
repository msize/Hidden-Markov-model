#include <iostream>
#include "Process.h"

static void printUsage(const char *program) {
  std::cout << "Usage: "
      << program
      << " hmmdata"
      << std::endl;
}

int main(int argc, char **argv) {
  if (2 > argc) {
    printUsage(argv[0]);
    return 1;
  }
  Process process(argv[1]);
  process.run();
  return 0;
}
