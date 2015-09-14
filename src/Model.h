/* Элементы модели:
 * N = 3 - общее количество состояний
 * S = {St1, St2, E} - совокупность состояний
 * M = 3 - размер алфавита наблюдаемой последовательности
 * Y = {a, b, c} - алфавит наблюдаемой последовательности
 * A = | 0.969 0.029 0.002 | - матрица вероятностей переходов
 *     | 0.063 0.935 0.002 |
 *     | 0.000 0.000 1.000 |
 * B = | 0.005 0.775 0.220 | - распределение вероятностей появления символов
 *     | 0.604 0.277 0.119 |
 *     | 0.000 0.000 0.000 |
 * pi = | 0.526 0.474 0.000 | - распределение вероятностей начального состояния
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <string>

class Model {

public:

  class Exception : public std::exception {
  public:
    Exception(const std::string &message);
    virtual ~Exception() throw ();
    virtual const char *what() const throw();
  private:
    std::string message_;
  };

  static const int N = 3;
  static const char *S[N];
  static const int M = 3;
  static const char Y[M];
  static const double A[N][N];
  static const double B[N][M];
  static const double pi[N];
  static int indexOfS(const std::string &s);
  static int indexOfY(const char y);

};

#endif /* MODEL_H_ */
