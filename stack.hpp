// Stack class of IPoints used for the battleship game
//
#ifndef __STACK_H__
#define __STACK_H__

#include <IPoint.hpp>
#include <assert.h>

#define MAX_STACK_SIZE 100
const int BOS = -1;
const int stack_size = MAX_STACK_SIZE;

class stack
{
   public:
      stack (int sz = stack_size);
      ~stack();
      int isEmpty()  { return st_top == BOS; }
      int isFull()   { return (st_top == st_size-1);       }
      void push(IPoint x);
      IPoint top();
      void clear();
      IPoint pop_top();
      IPoint getCurrent(int x);  //get the value in the stack at x
      int NumberOfItemsOnStack()  { return st_top+1; }
      Boolean AlreadyGuessed(stack* pstack, IPoint IPoint);     //dsb

   private:
      int    st_top;
      int    st_size;
      IPoint *st_array;
};
#endif
