/*************************************************************************************************\
*                                                                                                 *
* "titleRecord.cpp" -                                                                             *
*                                                                                                 *
*            Author - Tom McDonnell 2005                                                          *
*                                                                                                 *
\*************************************************************************************************/

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "titleRecord.h"
#include "misc.h"

// STATIC MEMBER CONSTANT DEFINITIONS /////////////////////////////////////////////////////////////

const int titleRecord::titleMaxLength = 32;

// MEMBER FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

/*
 * Set firstName once data is checked according to rules defined in printValidNameRules().
 */
void titleRecord::setTitle(const std::string &t)
{
   // test length
   if (!(1 <= t.length() && t.length() <= titleMaxLength))
     throw titleRecordErr();

   // test each word
   bool newWord = true;
   for (int i = 0; i < t.length(); ++i)
   {
      // test first letter (should be uppercase or digit or apostrophe)
      if (newWord)
      {
         if (!(isupper(t[i]) || isdigit(t[i]) || t[i] == char(39)))
           throw titleRecordErr();

         newWord = false;
      }

      // test for end of word
      else if (t[i] == ' ')
        newWord = true;

      // test other characters (should be lowercase or punctuation)
      else if (!(islower(t[i]) || ispunct(t[i])))
        throw titleRecordErr();

   }

   // t meets requirements for title
   title = t;
}

/*
 * Get title from user (cin).  Prints prompts and
 * error messages to cout until name is correctly read.
 * Validation rules are defined in printValidTitleRules().
 */
void titleRecord::getFromUser(const std::string &prompt)
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
      catch (titleRecordErr)
      {
         printValidTitleRules(cout);
         cout << "Retry." << endl;
         success = false;
      }
   }
}

/*
 * Same purpose as getTitleFromUser(), but supports automatic completion
 * of input line by pressing tab key where input can only be one of the
 * strings in list.
 */
//void titleRecord::getTitleFromUser(titleRecord &t, const std::list<std::string> &l)
//{
//}

// FUNCTION DEFINITIONS ///////////////////////////////////////////////////////////////////////////

/*
 * Input function for nameRecord class.
 */
std::istream &operator>>(std::istream &in, titleRecord &t)
{
   std::string title;

   eatwhite(in);

   char c;
   while (in.get(c))
   {
      if (c == '\n') break;
      else           title += c; 
   }

   t.setTitle(title);

   return in;
}

/*****************************************END*OF*FILE*********************************************/
