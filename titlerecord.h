/*************************************************************************************************\
*                                                                                                 *
* "titleRecord.h" -                                                                               *
*                                                                                                 *
*          Author - Tom McDonnell 2005                                                            *
*                                                                                                 *
\*************************************************************************************************/

#ifndef TOMS_LIB_TITLE_RECORD_H
#define TOMS_LIB_TITLE_RECORD_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <list>

// TYPE DEFINITIONS ///////////////////////////////////////////////////////////////////////////////

/*
 *
 */
class titleRecord
{
 public:
   // static constant declarations
   static const int titleMaxLength;

   // exception
   struct titleRecordErr {titleRecordErr(void) {}};

   // constructors
   titleRecord(void): title("<title>") {}
   titleRecord(const std::string &t)   {setTitle(t);}

   // get functions
   std::string get(void) const {return title;}
 
   // set functions
   void setTitle(const std::string &t);

   // user input function
   void getFromUser(const std::string &prompt);

   // operators
   bool operator==(const titleRecord &t) const {return title == t.title;}
   bool operator!=(const titleRecord &t) const {return title != t.title;}

   // static member functions
   static void printValidTitleRules(std::ostream &);

 private:
   std::string title; // validation rules defined in printValidTitleRules()
};

// INLINE MEMBER FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

inline void titleRecord::printValidTitleRules(std::ostream &out)
{
   using std::endl;

   out << "---------------------------------------------------------------------" << endl
       << "Expecting title."                                                      << endl
       << "Format: String of words separated by spaces."                          << endl
       << "Maximum string length " << titleMaxLength << " characters."            << endl
       << "First character of each word must be uppercase, digit, or apostrophe." << endl
       << "Other characters must be alphabet or punctuation symbol."              << endl
       << "---------------------------------------------------------------------" << endl;
}

// FUNCTION DECLARATIONS //////////////////////////////////////////////////////////////////////////

std::istream &operator>>(std::istream &, titleRecord &);

// INLINE FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

inline std::ostream &operator<<(std::ostream &out, const titleRecord &t)
{
   std::ios_base::fmtflags newFlags = std::ios_base::left,
                           oldFlags = out.flags(newFlags); // save old flags and set new ones

   // NOTE: changing of alignment has no effect if a
   //       width > title.length() has not been specified

   out << t.get();

   out.flags(oldFlags); // reset flags

   return out;
}

#endif

/*****************************************END*OF*FILE*********************************************/
