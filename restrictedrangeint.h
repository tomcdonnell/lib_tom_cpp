/*************************************************************************************************\
*                                                                                                 *
* "restrictedRangeInt.h" -                                                                        *
*                                                                                                 *
*                 Author - Tom McDonnell 2005                                                     *
*                                                                                                 *
\*************************************************************************************************/

#ifndef TOMS_LIB_RESTRICTED_RANGE_INT_H
#define TOMS_LIB_RESTRICTED_RANGE_INT_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <limits>

#include <cstdlib>

// TYPE DEFINITIONS ///////////////////////////////////////////////////////////////////////////////

/*
 *
 */
class restrictedRangeInt
{
 public:

   // constructor
   restrictedRangeInt(const int &min, const int &max);
   restrictedRangeInt(const int &min, const int &max, const int &value);

   // exception classes
   struct restrictedRangeIntErr {restrictedRangeIntErr(void) {}};

   // conversion function
   operator int(void) const {return val;}

   // get function
   int get(void)    const {return val;}
   int getMin(void) const {return min;}
   int getMax(void) const {return max;}

   // set function
   void set(const int &i);

   // user input function
   void getFromUser(const std::string &prompt);
   void printValidUserInputRules(std::ostream &);

   // operators

   restrictedRangeInt operator=(const int i);

   restrictedRangeInt operator++(void);
   restrictedRangeInt operator++(int);  // postfix increment
   restrictedRangeInt operator--(void);
   restrictedRangeInt operator--(int);  // postfix decrement

   restrictedRangeInt operator+=(const int &i);
   restrictedRangeInt operator-=(const int &i);
   restrictedRangeInt operator*=(const int &i);
   restrictedRangeInt operator/=(const int &i);

   restrictedRangeInt operator+=(const restrictedRangeInt &i) {return *this += i.val;}
   restrictedRangeInt operator-=(const restrictedRangeInt &i) {return *this -= i.val;}
   restrictedRangeInt operator*=(const restrictedRangeInt &i) {return *this *= i.val;}
   restrictedRangeInt operator/=(const restrictedRangeInt &i) {return *this /= i.val;}


 private:
   setRange(const int &min, const int &max);

   int min,
       max,
       val;
};

// INLINE MEMBER FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

/*
 * Set function.
 */
inline void restrictedRangeInt::set(const int &i)
{
   if (min <= i && i <= max)
     val = i;
   else
   {
      if (min < i) val = min;
      else         val = max;

      throw restrictedRangeIntErr();
   }
}

/*
 *
 */
inline void restrictedRangeInt::printValidUserInputRules(std::ostream &out)
{
   using std::endl;

   out << "-------------------------------------------------------------" << endl
       << "Expecting an integer in range [" << min << ", " << max << "]." << endl
       << "-------------------------------------------------------------" << endl;
}

/*
 * Assignment operator.
 */
inline restrictedRangeInt restrictedRangeInt::operator=(const int i)
{
   if (min <= i && i <= max) val = i;
   else                      throw restrictedRangeIntErr();

   return *this;
}

/*
 * Increment operator.
 */
inline restrictedRangeInt restrictedRangeInt::operator++(void)
{
   if (val < max) ++val;
   else           throw restrictedRangeIntErr();

   return *this;
}

/*
 * Increment operator (postfix version).
 */
inline restrictedRangeInt restrictedRangeInt::operator++(int)
{
   restrictedRangeInt temp = *this; ++(*this); return temp;
}

/*
 * Decrement operator.
 */
inline restrictedRangeInt restrictedRangeInt::operator--(void)
{
   if (val > min) --val;
   else           throw restrictedRangeIntErr();

   return *this;
}

/*
 * Decrement operator (postfix version).
 */
inline restrictedRangeInt restrictedRangeInt::operator--(int)
{
   restrictedRangeInt temp = *this; --(*this); return temp;
}

/*
 * += operator (mixed-mode).
 */
inline restrictedRangeInt restrictedRangeInt::operator+=(const int &i)
{
   if (val + i <= max) val = val + i;
   else                throw restrictedRangeIntErr();

   return *this;
}

/*
 * -= operator (mixed-mode).
 */
inline restrictedRangeInt restrictedRangeInt::operator-=(const int &i)
{
   if (min <= val - i) val = val - i;
   else                throw restrictedRangeIntErr();

   return *this;
}

/*
 * *= operator (mixed-mode).
 */
inline restrictedRangeInt restrictedRangeInt::operator*=(const int &i)
{
   int temp = val * i;

   if (min <= temp && temp <= max) val = temp;
   else                            throw restrictedRangeIntErr();

   return *this;
}

/*
 * /= operator (mixed-mode).
 */
inline restrictedRangeInt restrictedRangeInt::operator/=(const int &i)
{
   int temp = val / i;

   if (min <= temp && temp <= max) val = temp;
   else                            throw restrictedRangeIntErr();

   return *this;
}

// INLINE FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

// comparison operators
inline bool operator==(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return a.get() == b.get();}

inline bool operator!=(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return !(a == b);}

inline bool operator<(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return a.get() < b.get();}

inline bool operator>(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return a.get() > b.get();}

inline bool operator<=(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return a < b || a == b;}

inline bool operator>=(const restrictedRangeInt &a, const restrictedRangeInt &b)
{return a > b || a == b;}

inline std::ostream &operator<<(std::ostream &out, const restrictedRangeInt &i)
{out << i.get(); return out;}

// FUNCTION DECLARATIONS //////////////////////////////////////////////////////////////////////////

inline std::istream &operator>>(std::istream &, restrictedRangeInt &);

#endif

/*****************************************END*OF*FILE*********************************************/
