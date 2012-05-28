/*************************************************************************************************\
*                                                                                                 *
* "date.cpp" -                                                                                    *
*                                                                                                 *
*     Author - Tom McDonnell 2005                                                                 *
*                                                                                                 *
\*************************************************************************************************/

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "dateRecord.h"
#include "misc.h"

// STATIC MEMBER CONSTANT DEFINITIONS /////////////////////////////////////////////////////////////

const int dateRecord::maxYear = 2020,
          dateRecord::minYear = 1980;

// MEMBER FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

/*
 *
 */
bool dateRecord::operator<(const dateRecord &d) const
{
   assert(minYear <= year  && year  <= maxYear                 );
   assert(JAN     <= month && month <= DEC                     );
   assert(1       <= day   && day   <= daysInMonth(month, year));

        if (year < d.year) return true;
   else if (year > d.year) return false;
   else
   {
      // years equal
           if (month < d.month) return true;
      else if (month > d.month) return false;
      else
      {
         // years and months equal
              if (day < d.day) return true;
         else if (day > d.day) return false;
         else
           // dates are equal
           return false;
      }
   }
}

/*
 * Increment date by one day.
 */
dateRecord dateRecord::operator++(void)
{
   assert(minYear <= year  && year  <= maxYear                 );
   assert(JAN     <= month && month <= DEC                     );
   assert(1       <= day   && day   <= daysInMonth(month, year));

   if (day < daysInMonth(month, year))
     day++;
   else
   {
      // last day of month
      day = 1;
      if (month == DEC) {month = JAN; year++;}
      else               month++;
   }

   return *this;
}

/*
 * Decrement date by one day.
 */
dateRecord dateRecord::operator--(void)
{
   assert(minYear <= year  && year  <= maxYear                 );
   assert(JAN     <= month && month <= DEC                     );
   assert(1       <= day   && day   <= daysInMonth(month, year));

   if (day >= 2)
     day--;
   else
   {
      // first day of month

      // update month (and year if necessary)
      if (month == JAN) {month = DEC, year--;}
      else               month--;

      // update day
      if (month == FEB) day = daysInMonthFeb(year);
      else              day = daysInMonthNotFeb(month);
   }

   return *this;
}

/*
 * Get date from user (cin).  Prints prompts and
 * error messages to cout until date is correctly read.
 * Validation rules are defined in printValidDateRules().
 */
void dateRecord::getFromUser(const std::string &prompt)
{
   // static member function (so no assert()s for member variables)

   using std::cin;
   using std::cout;
   using std::endl;

   bool success = false;
   while (!success)
   {
      try
      {
         cout << prompt;

         printDateFormat(cout);
         cout << ": ";
         cin.sync();
         cin >> *this;
         success = true;
      }
      catch (dateRecordErr)
      {
         printValidDateRules(cout);
         cout << "Retry." << endl;
         success = false;
      }
   }
}

// FUNCTION DEFINITIONS ///////////////////////////////////////////////////////////////////////////

/*
 * Read date from input.
 */
std::istream &operator>>(std::istream &in, dateRecord &date)
{
   using std::cout;
   using std::endl;

   using dateRecord::dateFormatErr;

   int  d, m, y;
   char c;

   eatwhite(in);

   // read dd
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else d  = (c - '0') * 10;
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else d += (c - '0');

   // read separator '/'
   in.get(c); if (c != '/')    throw dateFormatErr();
               
   // read mm
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else m  = (c - '0') * 10;
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else m += (c - '0');

   // read separator '/'
   in.get(c); if (c != '/')    throw dateFormatErr();

   // read yyyy
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else y  = (c - '0') * 1000;
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else y += (c - '0') * 100;
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else y += (c - '0') * 10;
   in.get(c); if (!isdigit(c)) throw dateFormatErr(); else y += (c - '0');

   // read terminating whitespace character
   in.get(c); if (!isspace(c)) throw dateFormatErr();

   date = dateRecord(d, m, y);

   return in;
}

/*
 *
 */
void dateBeginEnd::getFromUser(void)
{
   using std::cout;
   using std::endl;

   bool happyWithDates = false;
   while (!happyWithDates)
   {
      begin.getFromUser("Begin date? ");
        end.getFromUser("End date?   ");

      if (begin <= end)
        happyWithDates = true;
      else
        cout << "---------------------------------------------------" << endl
             << "End date must be later than or equal to begin date." << endl
             << "---------------------------------------------------" << endl
             << "Retry."                                              << endl;
   }
}

/*****************************************END*OF*FILE*********************************************/
