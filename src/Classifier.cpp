#include "Classifier.h"
#include <sstream>

void Classifier::add(bool realPositive, bool evaluatedPositive) {
  if (realPositive && evaluatedPositive)
    truePositives_++;
  if (!realPositive && !evaluatedPositive)
    trueNegatives_++;
  if (realPositive && !evaluatedPositive)
    falseNegatives_++;
  if (!realPositive && evaluatedPositive)
    falsePositives_++;
}

std::string Classifier::getReport() {
  double precision = static_cast<double>(truePositives_) / static_cast<double>(truePositives_ + falsePositives_);
  double recall = static_cast<double>(truePositives_) / static_cast<double>(truePositives_ + falseNegatives_);
  double f = 2 * precision * recall / (precision + recall);
  std::stringstream ss;
  ss << "                       Экспертная оценка\n"
      << "                        \tПолож.\tОтриц.\n"
      << "Оценка системы  Полож.  "
      << "\t" << truePositives_
      << "\t" << falsePositives_
      << "\n                Отриц.  "
      << "\t" << falseNegatives_
      << "\t" << trueNegatives_
      << "\nF-мера " << f
      << std::endl;
  return ss.str();
}
