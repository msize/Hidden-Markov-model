#include "Process.h"
#include "Model.h"
#include "Viterbi.h"
#include "ForwardBackward.h"
#include "Classifier.h"
#include <sstream>
#include <iostream>

Process::Process(const char *file) :
    inFile_(file) {
}

Process::~Process() {
}

void Process::run() {
  try {
    readFile();
    IntList viterbiResult;
    runViterbi(viterbiResult);
    IntList forwardBackwardResult;
    runForwardBackward(forwardBackwardResult);
    printBothReports(viterbiResult, forwardBackwardResult);
  } catch (Model::Exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void Process::readFile() {
  int step;
  std::string state;
  char symbol;
  std::string line;
  while (std::getline(inFile_, line)) {
    std::istringstream iss(line);
    if (!(iss >> step))
      continue;
    if (!(iss >> state))
      continue;
    if (!(iss >> symbol))
      continue;
    states_.push_back(Model::indexOfS(state));
    observations_.push_back(Model::indexOfY(symbol));
  }
}

void Process::runViterbi(IntList &viterbiResult) {
  Viterbi<Model> viterbi;
  viterbi.run(observations_, viterbiResult);
}

void Process::runForwardBackward(IntList &forwardBackwardResult) {
  ForwardBackward<Model> forwardBackward;
  forwardBackward.run(observations_, forwardBackwardResult);
}

void Process::printBothReports(const IntList &viterbiResult, const IntList &forwardBackwardResult) {
  std::cout << "Шаг     Сост.   Эмиссия Витерби Вперёд-Назад\n"
               "------- ------- ------- ------- ------------\n";
  int step = 0;
  Classifier viterbiClassifier;
  Classifier forwardBackwardClassifier;
  int indexOfSt1 = Model::indexOfS("St1");
  for (IntList::const_iterator sIt = states_.begin(), oIt = observations_.begin(), vIt =
      viterbiResult.begin(), fbIt = forwardBackwardResult.begin();
      sIt != states_.end() && oIt != observations_.end() && vIt != viterbiResult.end()
          && fbIt != forwardBackwardResult.end(); ++sIt, ++oIt, ++vIt, ++fbIt) {
    viterbiClassifier.add(indexOfSt1 == *sIt, indexOfSt1 == *vIt);
    forwardBackwardClassifier.add(indexOfSt1 == *sIt, indexOfSt1 == *fbIt);
    std::cout << step++ << "\t"
        << Model::S[*sIt] << "\t"
        << Model::Y[*oIt] << "\t"
        << Model::S[*vIt] << "\t"
        << Model::S[*fbIt] << "\n";
  }
  std::cout << "----------------------------------------------\n"
               "Оценка алгоритма Витерби:\n" << viterbiClassifier.getReport()
            << "----------------------------------------------\n"
               "Оценка алгоритма Вперёд-Назад:\n" << forwardBackwardClassifier.getReport();
}
