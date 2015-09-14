#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include <string>

class Classifier {

public:

  Classifier() {
  }
  virtual ~Classifier() {
  }

  void add(bool realPositive, bool evaluatedPositive);
  std::string getReport();

private:

  int truePositives_ = 0;
  int falsePositives_ = 0;
  int trueNegatives_ = 0;
  int falseNegatives_ = 0;

};

#endif /* СLASSIFIER_H_ */
