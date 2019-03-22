/**************************************************************
* Stack Class member functions.
**************************************************************/
#include "stack.hpp"
#define FALSE 0
#define TRUE  1

//this has a default sz specified in the constructor in the header file
stack::stack(int sz)
{
   st_array = new IPoint[sz];
   st_top = BOS;
   st_size = sz;
}

stack::~stack()
{
   delete [] st_array;
}

/****************************************************************
* Function:    push
*
* Purpose      Checks to make sure the stack is not full.  If not,
*              it will add the passed in item to the top of the
*              stack.
*
* Returns      Nothing
****************************************************************/
void stack::push(IPoint x)
{
   if ( isFull() )
      return;
      
   ++st_top;
   st_array[st_top] = x;
}

/****************************************************************
* Function:    pop_top
*
* Purpose      If the stack is empty,  return a marker (-1, -1) to
*              indicate this.  Otherwise,  decrement the stack pointer
*              and return the element at the top.
*
* Returns      A stack element.
****************************************************************/
IPoint stack::pop_top()
{
    if ( isEmpty() )
      return IPoint(-1, -1);
      
   st_top--;
   return st_array[st_top];
}

/****************************************************************
* Function:    clear
*
* Purpose      remove all items from the stack.
*
* Returns      nothing
****************************************************************/
void stack::clear()
{
   while (!isEmpty())
      pop_top();
}

/****************************************************************
* Function:    top
*
* Purpose      If the stack is empty,  return a marker (-1, -1) to
*              indicate this.  Otherwise, return the element at the 
*              top without decrementing the stack pointer.
*
* Returns      A stack element.
****************************************************************/
IPoint stack::top()
{
   if ( isEmpty() )
      return IPoint(-1, -1);
   return st_array[st_top];
}

/****************************************************************
* Function:    getCurrent
*
* Purpose      return the element at the desired stack position.
*
* Returns      A stack element.
****************************************************************/
IPoint stack::getCurrent(int x)
{
   return st_array[x];
}

/*****************************************************
* Function:    AlreadyGuessed()
* Parms:       IPoint
* Purpose:     Will loop the GuessArray looking to see if the
*              IPoint passed already exists in the array.
* Returns:     TRUE - point has already been guessed (exists in the obarray)
*              FALSE - point has not been guessed yet
*****************************************************/
Boolean stack::AlreadyGuessed(stack *pstack, IPoint iPoint)      //dsb
{  
   IPoint obarray_point = IPoint(-1, -1);
   Boolean rc = FALSE;
   int i=0, j;

// How many items are on the stack now 
   j = pstack->NumberOfItemsOnStack();  
   assert(j >= 0);

   while(i<j) // look through all the items on the stack
   {
      obarray_point = pstack->getCurrent(i);  //get the current guess
      if (obarray_point == iPoint)            // do we have a match?
      {
         rc = TRUE;  // must have already guessed it since the IPoint is
         break;      //   already in the array
      }
      i += 1;
   }
   return rc;  
}
