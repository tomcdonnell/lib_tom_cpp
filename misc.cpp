/*************************************************************************************************\
*                                                                                                 *
* "misc.cpp" -                                                                                    *
*                                                                                                 *
*     Author - Tom McDonnell 2003                                                                 *
*                                                                                                 *
\*************************************************************************************************/

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <TomsLibrary/misc.h>

#include <string>
#include <iomanip>

#include <cmath>

// GLOBAL FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

namespace TomsLibMisc
{

 /*
  *
  */
 int getWordFromLine(char *word, int wordBufSize, char *line, int lineBufSize, int startPos)
 {
    int i;

    --wordBufSize; // allow for string termination character
    --lineBufSize; // allow for string termination character

    // skip leading spaces
    for (i = startPos;(   line[i] == ' '
                       || line[i] == '\t')
                       && i <  lineBufSize; ++i);

    // if no word in line, return error value
    if (   line[i] == '\n'
        || line[i] == '\0'
        || i       == lineBufSize)
      return -1;

    // copy consecutive non-space characters to 'word'
    int startWordPos = i;
    for (;   line[i] != ' '
          && line[i] != '\t'
          && line[i] != '\n'
          && line[i] != '\0'
          && i                <  lineBufSize
          && i - startWordPos <  wordBufSize; ++i)
      word[i - startWordPos] = line[i];

    // append string termination character to end of word
    word[i - startWordPos] = '\0';

    // return next position after word copied
    return i;
 }

 /*
  * Print the ASCII character set in a table to screen.
  */
 void printASCIIcharSet(std::ostream &out)
 {
    using std::endl;

    const int rows = 25,
              cols = 256 / rows + 1;
    int charNo,
        r, c;

    out << "ASCII Character Set" << endl << endl;

    for (r = 0; r < rows; ++r)
    {
       for (c = 0; c < cols; ++c)
       {
          charNo = c * rows + r;

          if (charNo < 256)
          {
             out.width(3); out << charNo; out << " ";

             switch (charNo)
             {
              case  7: out << "BP "; break; // BEEP
              case  8: out << "BK "; break; // BACKSPACE
              case  9: out << "TB "; break; // TAB
              case 10: out << "NL "; break; // NEWLINE
              case 13: out << "CR "; break; // CARRIAGE RETURN
              default: out << (char)charNo << "  "; break;
             }
          }
       }
       out << endl;
    }
 }

 /*
  *
  */
 std::istream &eatwhite(std::istream &is)
 {
    char c;

    while (is.get(c))
    {
       if (!isspace(c))
       {
          is.putback(c);
          break;
       }
    }

    return is;
 }

 /*
  * Report details of exception caught to cerr then exit program.
  */
 void reportCaughtException(const std::string &exception,
                            const std::string &function,
                            const std::string &file)
 {
    using std::endl;
    using std::cerr;

    cerr << "Exception: " << exception << " caught." << endl
         << " Function: " << function                << endl
         << " File:     " << file                    << endl
                                                     << endl;
    exit(1);
 }

 /*
  *
  */
 bool userHappy(const std::string &prompt, const int &width)
 {
    using std::cin;
    using std::cout;
    using std::endl;

    while (true)
    {
       cout << prompt << std::setw(width) << "Happy? (y/n): ";

       cin.sync();
       switch(cin.get())
       {
        case 'y': case 'Y': return true;
        case 'n': case 'N': return false;
       }

       cout << "----------------------------" << endl
            << "Expecting either 'y' or 'n'." << endl
            << "----------------------------" << endl;
    }
 }

 /*
  * Prompt should be a (y/n) question.
  * 'y' response from user will cause b = true, n will cause b = false.
  */
 void getBoolFromUser(bool &b, const std::string &prompt)
 {
    using std::cin;
    using std::cout;
    using std::endl;

    while (true)
    {
       cout << prompt;

       cin.sync();
       switch(cin.get())
       {
        case 'y': case 'Y': b = true;  return;
        case 'n': case 'N': b = false; return;
       }

       cout << "----------------------------" << endl
            << "Expecting either 'y' or 'n'." << endl
            << "----------------------------" << endl;
    }
 }

 /*
  *
  */
 int digits(int i)
 {
    int d = 0;

    if (i <= 0)
    {
       d = 1; // negative sign couns as digit, 0 is one digit
    }

    while (i != 0)
    {
       i /= 10;
       ++d;
    }

    return d;
 }

} // end namespace TomsLibMisc

/*****************************************END*OF*FILE*********************************************/
