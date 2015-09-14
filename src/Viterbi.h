#ifndef VITERBI_H_
#define VITERBI_H_

#include "Types.h"
#include <list>
#include <array>

template<class Model>
class Viterbi {

public:

  Viterbi() {
  }

  virtual ~Viterbi() {
  }

  void run(const IntList &observations, IntList &guess) {
    for (IntList::const_iterator it = observations.begin(); it != observations.end(); ++it) {
      Item stateItem;
      Item indexItem;
      for (int stateIndex = 0; Model::N > stateIndex; ++stateIndex) {
        if (observations.begin() == it) {
          stateItem[stateIndex] = Model::pi[stateIndex] * Model::B[stateIndex][*it];
          indexItem[stateIndex] = 0;
        } else {
          stateItem[stateIndex] = max(*state_.rbegin(), stateIndex, *it);
          indexItem[stateIndex] = argmax(*state_.rbegin(), stateIndex, *it);
        }
      }
      state_.push_back(stateItem);
      index_.push_back(indexItem);
    }
    guess.push_front(argmax(*state_.rbegin()));
    for (typename ItemList::const_reverse_iterator it = index_.rbegin(); it != index_.rend(); ++it)
      guess.push_front((*it)[*guess.begin()]);
    guess.pop_front();
  }

private:

  typedef std::array<double, Model::N> Item;
  typedef std::list<Item> ItemList;

  double max(const Item &state, int stateIndex, int observationIndex) {
    double result = 0.0;
    double tmp;
    for (int i = 0; Model::N > i; ++i) {
      tmp = state[i] * Model::A[i][stateIndex] * Model::B[stateIndex][observationIndex];
      result = result < tmp ? tmp : result;
    }
    return result;
  }

  int argmax(const Item &state, int stateIndex, int observationIndex) {
    int result = 0;
    double max = 0.0;
    double tmp;
    for (int i = 0; Model::N > i; ++i) {
      tmp = state[i] * Model::A[i][stateIndex] * Model::B[stateIndex][observationIndex];
      if (max < tmp) {
        max = tmp;
        result = i;
      }
    }
    return result;
  }

  int argmax(const Item &state) {
    int result = 0;
    double max = 0.0;
    for (int i = 0; Model::N > i; ++i)
      if (max < state[i]) {
        max = state[i];
        result = i;
      }
    return result;
  }

  ItemList state_;
  ItemList index_;

};

#endif /* VITERBI_H_ */
