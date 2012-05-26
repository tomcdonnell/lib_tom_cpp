/*************************************************************************************************\
*                                                                                                 *
* "date.h" -                                                                                      *
*                                                                                                 *
*   Author - Tom McDonnell 2005                                                                   *
*                                                                                                 *
\*************************************************************************************************/

#ifndef TOMS_LIB_DATE_RECORD_H
#define TOMS_LIB_DATE_RECORD_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>

#include <cstdlib>
#include <cassert>

// TYPE DEFINITIONS ///////////////////////////////////////////////////////////////////////////////

/*
 * Date class.
 */
class dateRecord
{
 public:
   // static constant declarations
   static const int maxYear,
                    minYear;

   // exception classes
   struct dateRecordErr {};
   struct dateFormatErr:  public dateRecordErr {};
   struct dateInvalidErr: public dateRecordErr
   {
      int d, m, y;

      dateInvalidErr(int dd, int mm, int yy) {d = dd; m = mm; y = yy;}
   };

   // month enumeration
   static enum monthAbbrev {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

   // constructors
   dateRecord(void): day(1), month(JAN), year(minYear) {}
   dateRecord(const int &d, const int &m, const int &y) {setDate(d, m, y);}

   // get functions
   int getDay(void)   const {return day;}
   int getMonth(void) const {return month;}
   int getYear(void)  const {return year;}

   // set functions
   void setDate(const int &d, const int &m, const int &y);

   // user input function
   void getFromUser(const std::string &prompt);

   // operators

   bool operator==(const dateRecord &d) const;
   bool operator!=(const dateRecord &d) const {return !(*this == d);}

   bool operator<(const dateRecord &d) const;
   bool operator>(const dateRecord &d) const {return !(*this < d) && *this != d;} 

   bool operator<=(const dateRecord &d) const {return *this < d || *this == d;}
   bool operator>=(const dateRecord &d) const {return *this > d || *this == d;}

   dateRecord operator++(void);
   dateRecord operator--(void);
   dateRecord operator++(int) {dateRecord temp = *this; ++(*this); return temp;} // postfix ++
   dateRecord operator--(int) {dateRecord temp = *this; --(*this); return temp;} // postfix --


   // static member funtions

   static bool leapYear(const int &y);
   static bool dateValid(const int &d, const int &m, const int &y);

   static int daysInMonthFeb(const int &y)    {if (leapYear(y)) return 29; else return 28;}
   static int daysInMonthNotFeb(const int &m);
   static int daysInMonth(const int &m, const int &y);

   static void printDateFormat(std::ostream &out) {out << "dd/mm/yyyy";}
   static void printValidDateRules(std::ostream &);


 private:
   // private variables (need integrity protection mechanisms)
   int year,  // range [minYear, maxYear]
       month, // range [JAN, DEC]
       day;   // range depends on year and month
};

/*
 * Often used pair.
 */
class dateBeginEnd
{
 public:
   dateRecord begin, end;

   // user input function
   void getFromUser(void);
};

// INLINE MEMBER FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

/*
 * Constructor.  invalidDateErr() exception thrown from here.
 */
inline void dateRecord::setDate(const int &d, const int &m, const int &y)
{
   if (dateValid(d, m, y))
   {
      day   = d;
      month = m;
      year  = y;
   }
   else
     throw dateInvalidErr(d, m, y);
}

inline bool dateRecord::operator==(const dateRecord &d) const
{
   assert(minYear <= year  && year  <= maxYear                 );
   assert(JAN     <= month && month <= DEC                     );
   assert(1       <= day   && day   <= daysInMonth(month, year));

   return    day   == d.day
          && month == d.month
          && year  == d.year;
}

/*
 * Test whether year 'y' is a leap year.
 */
inline bool dateRecord::leapYear(const int &y)
{
   assert(minYear <= y && y <= maxYear);

   if (y % 4 == 0 && !((y % 100 == 0) && (y % 400 != 0))) return true;
   else                                                   return false;
}

/*
 * Test whether date ('d'/'m'/'y') is a valid date.
 */
inline bool dateRecord::dateValid(const int &d, const int &m, const int &y)
{
   // static member function (so no assert()s for member variables)

   if (   (minYear <= y && y <= maxYear          )
       && (JAN     <= m && m <= DEC              )
       && (1       <= d && d <= daysInMonth(m, y)))
     return true;
   else
     return false;
}

/*
 * Return the number of days in month m that is not February.
 * (for February need year also as depends on whether year is leap year)
 */
inline int dateRecord::daysInMonthNotFeb(const int &m)
{
   // static member function (so no assert()s for member variables)

   assert(JAN <= m && m <= DEC);

   switch (m)
   {
    case JAN: case MAR: case MAY: case JUL: case AUG: case OCT: case DEC: return 31;
    case APR: case JUN: case SEP: case NOV:                               return 30;
    case FEB: std::cerr << "daysInMonthNotFeb(m) called with m = FEB.";
    default: return 0; // to avoid compiler warning (program flow should never reach here)
   }
}

/*
 * Return the number of days in month 'm' in year 'y'.
 * (need year because might be leap year and month might be February)
 */
inline int dateRecord::daysInMonth(const int &m, const int &y)
{
   // static member function (so no assert()s for member variables)

   assert(JAN     <= m && m <= DEC    );
   assert(minYear <= y && y <= maxYear);

   if (m == FEB) return daysInMonthFeb(y);
   else          return daysInMonthNotFeb(m);
}

/*
 *
 */
inline void dateRecord::printValidDateRules(std::ostream &out)
{
   // static member function (so no assert()s for member variables)

   using std::endl;

   out << "-------------------------------------------------------------" << endl
       << "Expecting a calendar date."                                    << endl
       << "Format: "; printDateFormat(std::cout); out << "."              << endl
       << "yyyy must be between " << minYear << " and " << maxYear << "." << endl
       << "mm   must be between 1 and 12."                                << endl
       << "dd   must be between 1 and no. days in month mm in year yyyy." << endl
       << "-------------------------------------------------------------" << endl;
}

// FUNCTION DECLARATIONS //////////////////////////////////////////////////////////////////////////

std::istream &operator>>(std::istream &, dateRecord &);

// INLINE FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

inline std::ostream &operator<<(std::ostream &out, const dateRecord &d)
{
   out << std::setfill('0')

              << std::setw(2) << d.getDay()
       << "/" << std::setw(2) << d.getMonth()
       << "/" << std::setw(4) << d.getYear()

       << std::setfill(' ');

   return out;
}

inline std::ostream &operator<<(std::ostream &out, const dateBeginEnd &period)
{
   out << "[" << period.begin << ", " << period.end << "]";

   return out;
}

#endif

/*****************************************END*OF*FILE*********************************************/
