/*************************************************************************************************\
*                                                                                                 *
* "stack.h" - Class "stack" definition.                                                           *
*                                                                                                 *
*   Author  - Tom McDonnell                                                                       *
*                                                                                                 *
\*************************************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <fstream.h>
#include <assert.h>

template<class T>
class stack {
   friend ostream &operator<<(ostream &, const stack &);
 public:
   stack(int = 10);
   ~stack(void) {delete []stackPtr;}
   bool push(const T &);
   bool pop(T &);
   bool empty(void) const {return top == -1;}
   bool full(void) const {return top == size - 1;}
   int  getCount(void) {return top + 1;}
 private:
   int size,
       top;
   T  *stackPtr;
};

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

/*
 * Constructor with default size 10.
 */
template<class T>
stack<T>::stack(int s) {
   size  =  s;
   top   = -1;
   stackPtr = new T[size];
}

/*
 * Push an item on to stack.
 */
template<class T>
bool stack<T>::push(const T &item) {
   if (!full()) {
      stackPtr[++top] = item;
      return true;
   }
   return false;
}

/*
 * Pop an item from stack.
 * Returns true if successful, false otherwise.
 */
template<class T>
bool stack<T>::pop(T &poppedItem) {
   if (!empty()) {
      poppedItem = stackPtr[top--];
      return true;
   }
   return false;
}

// FRIEND FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

/*
 * Print stack to output on one line
 * with items separated by a two spaces.
 */
template<class T>
ostream &operator<<(ostream &output, const stack<T> &S) {
   for (int i = 0; i < S.top + 1; ++i)
     output << S.stackPtr[i] << "  ";
   output << endl;
   return output;
}

#endif