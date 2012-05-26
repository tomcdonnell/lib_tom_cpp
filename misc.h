/*************************************************************************************************\
*                                                                                                 *
* "misc.h" -                                                                                      *
*                                                                                                 *
*   Author - Tom McDonnell 2003                                                                   *
*                                                                                                 *
\*************************************************************************************************/

#ifndef TOMS_LIB_MISC_H
#define TOMS_LIB_MISC_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cassert>
#include <cstdlib>
#include <cmath>

// GLOBAL FUNCTION DECLARATIONS ///////////////////////////////////////////////////////////////////

namespace TomsLibMisc
{
 int getWordFromLine(char *word, int wordBufSize, char *line, int lineBufSize, int startPos);

 void printASCIIcharSet(std::ostream &);

 std::istream &eatwhite(std::istream &);

 void reportCaughtException(const std::string &exception,
                            const std::string &function,
                            const std::string &file);

 bool userHappy(const std::string &prompt, const int &width = 0);

 /*
  * Prompt should be a (y/n) question.
  * 'y' response from user will cause b = true, n will cause b = false.
  */
 void getBoolFromUser(bool &b, const std::string &prompt);

 int digits(int);

} // end namespace TomsLibMisc

// GLOBAL INLINE FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

namespace TomsLibMisc
{

 /*
  * Find solutions s1 & s2 of equation 0 = ax^2 + bx + c.
  * If    solutions found, returns  true.
  * If no solutions found, returns false.
  */
 inline bool solvePolynomial(const double &a, const double &b, const double &c,
                             double &s1, double &s2                            )
 {
    double det = pow(b, 2) - 4.0 * a * c;

    if (det < 0.0)
      return false;
    else
    {
       s1 = (-b + sqrt(det)) / (2.0 * a);
       s2 = (-b - sqrt(det)) / (2.0 * a);

       return true;
    }
 }

 // PROBLEM: unnessesary.  there should be a std::max() defined in <algorithm>
 template<class T>
 inline T max(const T &a, const T &b) {return (a > b)? a: b;}

 /*
  * Print an error message than exit with code EXIT_FAILURE.
  */
 inline void error(char *msg) {std::cerr << "ERROR: " << msg << std::endl; exit(EXIT_FAILURE);}

 /*
  * Return a random integer in the range [l, h].
  */
 inline int random(int l, int h) {assert(l < h); return (rand() / RAND_MAX) * (h - l) + l;}

 /*
  * Return a random floating-point number in the range [l, h].
  */
 inline double random(double l, double h)
 {
    assert(l <= h); return ((double)rand() / (double)RAND_MAX) * (h - l) + l;
 }

 /*
  *
  */
 inline bool readChar(std::istream &in, const char &c)
 {
    if (in.get() == c) return true;
    else               return false;
 }

} // end namespace TomsLibMisc

#endif

/*****************************************END*OF*FILE*********************************************/
