#ifndef PROCESS_H_
#define PROCESS_H_

#include "Types.h"
#include <fstream>

class Process {

public:

  Process(const char *file);
  virtual ~Process();

  void run();

private:

  void readFile();
  void runViterbi(IntList &viterbiResult);
  void runForwardBackward(IntList &forwardBackwardResult);
  void printBothReports(const IntList &viterbiResult, const IntList &forwardBackwardResult);

  std::ifstream inFile_;
  IntList states_;
  IntList observations_;

};

#endif /* PROCESS_H_ */
