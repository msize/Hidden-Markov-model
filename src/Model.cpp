#include "Model.h"

Model::Exception::Exception (const std::string &message) : message_(message) {
}

Model::Exception::~Exception() throw () {
}

const char *Model::Exception::what() const throw() {
  return message_.c_str();
}

const char *Model::S[N] = {"St1", "St2", "E"};
const char Model::Y[M] = {'a', 'b', 'c'};
const double Model::A[N][N] = {{0.969, 0.029, 0.002},
                               {0.063, 0.935, 0.002},
                               {0.000, 0.000, 1.000}};
const double Model::B[N][M] = {{0.005, 0.775, 0.220},
                               {0.604, 0.277, 0.119},
                               {0.000, 0.000, 0.000}};
const double Model::pi[N] = {0.526, 0.474, 0};

static std::string StringState = "St1";
static int IndexState = 0;

int Model::indexOfS(const std::string &s) {
  if (StringState == s)
    return IndexState;
  for (int i = 0; M > i; ++i)
    if (IndexState != i && S[i] == s) {
      IndexState = i;
      StringState = s;
      return i;
    }
  throw Exception("Unknown state: " + s);
}

int Model::indexOfY(char y) {
  if (Y[0] > y || y > Y[M-1])
    throw Exception("Unknown observation: " + y);
  return y - Y[0];
}
