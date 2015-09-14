#ifndef FORWARDBACKWARD_H_
#define FORWARDBACKWARD_H_

#include "Types.h"
#include <list>
#include <array>

template<class Model>
class ForwardBackward {

public:

  ForwardBackward() {
  }

  virtual ~ForwardBackward() {
  }

  void run(const IntList &observations, IntList &guess) {
    backward(observations);
    merge(forward(observations), guess);
  }

private:

  typedef std::array<double, Model::N> Item;
  typedef std::list<Item> ItemList;

  double forward(const IntList &observations) {
    double forwardSum = 0.0;
    for (IntList::const_iterator it = observations.begin(); it != observations.end(); ++it) {
      Item forwardCurrent;
      for (int i = 0; Model::N > i; ++i) {
        if (observations.begin() == it) {
          forwardSum = Model::pi[i];
        } else {
          forwardSum = 0.0;
          for (int j = 0; Model::N > j; ++j)
            forwardSum += (*forward_.rbegin())[j] * Model::A[j][i];
        }
        forwardCurrent[i] = Model::B[i][*it] * forwardSum;
      }
      forward_.push_back(forwardCurrent);
    }
    double forwardProbability = 0.0;
    for (int i = 0; Model::N > i; ++i)
      forwardProbability += (*forward_.rbegin())[i] * Model::A[i][Model::N - 1];
    return forwardProbability;
  }

  void backward(const IntList &observations) {
    Item backwardCurrent;
    for (int i = 0; Model::N > i; ++i)
      backwardCurrent[i] = Model::A[i][Model::N - 1];
    backward_.push_front(backwardCurrent);

    double backwardSum = 0.0;
    for (IntList::const_reverse_iterator it = observations.rbegin(); it != observations.rend(); ++it) {
      Item backwardCurrent;
      for (int i = 0; Model::N > i; ++i) {
        backwardSum = 0.0;
        for (int j = 0; Model::N > j; ++j)
          backwardSum += Model::A[i][j] * Model::B[j][*it] * (*backward_.begin())[j];
        backwardCurrent[i] = backwardSum;
      }
      backward_.push_front(backwardCurrent);
    }
    backward_.pop_front();
  }

  void merge(double forwardProbability, IntList &guess){
    double probability;
    double maxProbability;
    int guessStateIndes;
    for (typename ItemList::const_iterator fIt = forward_.begin(), bIt = backward_.begin();
        fIt != forward_.end() and bIt != backward_.end(); ++fIt, ++bIt) {
      maxProbability = 0.0;
      guessStateIndes = 0;
      for (int i = 0; Model::N > i; ++i) {
        probability = (*fIt)[i] * (*bIt)[i] / forwardProbability;
        if (maxProbability < probability) {
          guessStateIndes = i;
          maxProbability = probability;
        }
      }
      guess.push_back(guessStateIndes);
    }
  }

  ItemList forward_;
  ItemList backward_;

};

#endif /* FORWARDBACKWARD_H_ */
