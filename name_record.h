/*************************************************************************************************\
*                                                                                                 *
* "nameRecord.h" -                                                                                *
*                                                                                                 *
*         Author - Tom McDonnell 2005                                                             *
*                                                                                                 *
\*************************************************************************************************/

#ifndef TOMS_LIB_NAME_RECORD_H
#define TOMS_LIB_NAME_RECORD_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <list>

// TYPE DEFINITIONS ///////////////////////////////////////////////////////////////////////////////

/*
 *
 */
class nameRecord
{
 public:
   // static constant declarations
   static const int         firstNameMaxLength,
                            lastNameMaxLength;
   static const std::string defaultFirstName,
                            defaultLastName;

   // exception classes
   struct nameRecordErr {nameRecordErr(void) {}};

   // constructors
   nameRecord(void)                                       {initFirstName(); initLastName();}
   nameRecord(const std::string &f)                       {setFirstName(f); initLastName();}
   nameRecord(const std::string &f, const std::string &l) {setFirstName(f); setLastName(l);}

   // get functions
   std::string getFirstName(void) const {return firstName;}
   std::string getLastName(void)  const {return lastName;}

   // set functions
   void setFirstName(const std::string &);
   void setLastName(const std::string &);
   void setName(const nameRecord &n) {setFirstName(n.firstName); setLastName(n.lastName);}

   // user input function
   void getFromUser(const std::string &prompt);

   // operators
   bool operator==(const nameRecord &n) const;
   bool operator!=(const nameRecord &n) const {return !(*this == n);}

   // other functions
   void initFirstName(void) {firstName = defaultFirstName;}
   void initLastName(void)  {lastName  = defaultLastName;}
   void init(void)          {initFirstName(); initLastName();}
   void printFormatted(std::ostream &, const int &wf = 0, const int &wl = 0) const;

   // static member functions
   static void printValidNameRules(std::ostream &);

 private:
   // private variables
   std::string firstName, // validation rules defined in printValidNameRules()
               lastName;  // validation rules defined in printValidNameRules()
};

// INLINE MEMBER FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

inline bool nameRecord::operator==(const nameRecord &n) const
{
   return firstName == n.firstName && lastName == n.lastName;
}

inline void nameRecord::printValidNameRules(std::ostream &out)
{
   using std::endl;

   out << "-------------------------------------------------------------------" << endl
       << "Expecting persons name."                                             << endl
       << "Format:    One word (firstName) or two words (firstName lastName)"   << endl
       << "firstName: Maximum length " << firstNameMaxLength << " characters."  << endl
       << "           First character must be uppercase."                       << endl
       << "           Other characters must be lowercase."                      << endl
       << "lastName:  Maximum length " << lastNameMaxLength << " characters."   << endl
       << "           First character must be uppercase."                       << endl
       << "           Other characters must be alphabet, hyphen or apostrophe." << endl
       << "-------------------------------------------------------------------" << endl;
}

// FUNCTION DECLARATIONS //////////////////////////////////////////////////////////////////////////

std::istream &operator>>(std::istream &input, nameRecord &n);

// INLINE FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

inline std::ostream &operator<<(std::ostream &out, const nameRecord &n)
{
   out << n.getFirstName() << " " << n.getLastName();

   return out;
}

#endif

/*****************************************END*OF*FILE*********************************************/
