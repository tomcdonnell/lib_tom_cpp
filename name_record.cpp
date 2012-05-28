/*************************************************************************************************\
*                                                                                                 *
* "nameRecord.cpp" -                                                                              *
*                                                                                                 *
*           Author - Tom McDonnell 2005                                                           *
*                                                                                                 *
\*************************************************************************************************/

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "name_record.h"
#include "misc.h"

#include <iomanip>

// STATIC MEMBER CONSTANT DEFINITIONS /////////////////////////////////////////////////////////////

const int         nameRecord::firstNameMaxLength = 16,
                  nameRecord::lastNameMaxLength  = 16;

const std::string nameRecord::defaultFirstName("<first_name>"), // must contain no whitespace
                  nameRecord::defaultLastName("<last_name>");   // must contain no whitespace

// MEMBER FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

/*
 * Set firstName once data is checked according to rules defined in printValidNameRules().
 */
void nameRecord::setFirstName(const std::string &n)
{
   if (n == defaultFirstName)
     initFirstName(); // required since defaultFirstName need not meet normal requirements
   else
   {
      // test length
      if (!(1 <= n.length() && n.length() <= firstNameMaxLength))
        throw nameRecordErr();

      // test first letter (should be uppercase)
      if (!isupper(n[0]))
        throw nameRecordErr();

      // test other characters (should be lowercase)
      for (int i = 1; i < n.length(); ++i)
        if (!islower(n[i]))
          throw nameRecordErr();

      // n meets requirements for firstName
      firstName = n;
   }
}

/*
 * Set lastName once data is checked according to rules defined in printValidNameRules().
 */
void nameRecord::setLastName(const std::string &n)
{
   if (n == defaultLastName)
     initLastName(); // required since defaultLastName need not meet normal requirements
   else
   {
      // test length
      if (!(1 <= n.length() && n.length() <= lastNameMaxLength))
        throw nameRecordErr();

      // test first letter (should be uppercase)
      if (!isupper(n[0]))
        throw nameRecordErr();

      // test other characters (should be alphabet, hyphen, or apostrophe)
      for (int i = 1; i < n.length(); ++i)
        if (!(isalpha(n[i]) || n[i] == '-' || n[i] == char(39))) // char(39) = '''
          throw nameRecordErr();

      // n meets requirements for lastName
      lastName = n;
   }
}

/*
 * Get name from user (cin).  Prints prompts and
 * error messages to cout until name is correctly read.
 * Validation rules are defined in printValidNameRules()
 */
void nameRecord::getFromUser(const std::string &prompt)
{
   using std::cin;
   using std::cout;
   using std::endl;

   bool success = false;
   while (!success)
   {
      try
      {
         cout << prompt;

         cin.sync();
         cin >> *this;
         success = true;
      }
      catch (nameRecordErr)
      {
         printValidNameRules(cout);
         cout << "Retry." << endl;
         success = false;
      }
   }
}

/*
 * Same purpose as getNameFromUser(), but supports automatic completion
 * of input line by pressing tab key where input can only be one of the
 * strings in list.
 */
//void nameRecord::getNameFromUser(nameRecord &n, std::list<std::string> &l)
//{
//}

/*
 *
 */
void nameRecord::printFormatted(std::ostream &out, const int &wf, const int &wl) const
{
   std::ios_base::fmtflags newFlags = std::ios_base::left,
                           oldFlags = out.flags(newFlags); // save old flags and set new ones

   out << std::setw(wf) << firstName << " " << std::setw(wl) << lastName;

   out.flags(oldFlags); // reset flags
}

// FUNCTION DEFINITIONS ///////////////////////////////////////////////////////////////////////////

/*
 * Input function for nameRecord class.
 * Tests input according to rules defined in printValidNameRules().
 */
std::istream &operator>>(std::istream &in, nameRecord &n)
{
   std::string name;

   n.init(); // initialise first and last names

   // read firstName
   eatwhite(in);
   in >> name;
   if (name == nameRecord::defaultFirstName) n.initFirstName();
   else                                      n.setFirstName(name);

   // read lastName if supplied
   char c = in.peek();
   if (c == ' ')
   {
      in >> name;
      if (name == nameRecord::defaultLastName) n.initLastName();
      else                                     n.setLastName(name);
   }

   return in;
}

/*****************************************END*OF*FILE*********************************************/
