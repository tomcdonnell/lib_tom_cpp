/*************************************************************************************************\
*                                                                                                 *
* "queue.h" - Class "queue" definition.                                                           *
*                                                                                                 *
*   Author  - Tom McDonnell                                                                       *
*                                                                                                 *
\*************************************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream.h>
#include <assert.h>

template <class T>
class queue {
   friend ostream &operator<<(ostream &output, const queue &Q);
 public:
   queue(int = 10);
   ~queue(void) {delete[] queuePtr;}
   bool append(const T &);
   bool serve(T &);
   bool full(void) const {return (rear == front - 1) || (rear == size - 1 && front == 0);}
   bool empty(void) const {return front == -1;}
   int getCount(void) const;
 private:
   int size, front, rear;
   T *queuePtr;
};

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

template <class T>
queue<T>::queue(int s) {
   size = s;
   front = rear = -1;
   queuePtr = new T[size];
}

template <class T>
bool queue<T>::append(const T &item) {
   if (!full()) {
      if (empty())
        front = rear = 0;
      else
        rear = (rear + 1) % size;
      queuePtr[rear] = item;
      return true;
   }
   return false;
}

template <class T>
bool queue<T>::serve(T &servedItem) {
   if (!empty()) {
      servedItem = queuePtr[front];
      front = (front + 1) % size;
      if (front == (rear + 1) % size)
        front = rear = -1; // queue is empty
      return true;
   }
   return false;
}

template <class T>
int queue<T>::getCount(void) const {
   if (front == -1)
     return 0;
   if (front == rear)
     return 1;
   if (rear > front)
     return rear - front + 1;
   else
     return size - front + rear + 1;
}

// FRIEND FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

template <class T>
ostream &operator<<(ostream &output, const queue<T> &Q) {
   if (!Q.empty())
     for (int i = 0; i < Q.getCount(); ++i)
       output << Q.queuePtr[(Q.front + i) % Q.size] << "  ";
   output << endl;
   return output;
}

#endif