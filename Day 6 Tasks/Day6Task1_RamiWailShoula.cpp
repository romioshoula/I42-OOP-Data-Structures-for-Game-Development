//Day6Task1_RamiWailShoula.cpp

#include <iostream>
#include <cassert>

using namespace std;

template <class Type>

//function declarations in class

class stackADT
{
public:
    virtual void initializeStack() = 0;
    //Method to initialize the stack to an empty state.
    //Postcondition: Stack is empty

    virtual bool isEmptyStack() const = 0;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty,
    //               otherwise returns false.

    virtual bool isFullStack() const = 0;
    //Function to determine whether the stack is full.
    //Postcondition: Returns true if the stack is full,
    //               otherwise returns false.

    virtual void push(const Type& newItem) = 0;
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem 
    //               is added to the top of the stack.

    virtual Type top() const = 0;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program 
    //               terminates; otherwise, the top element
    //               of the stack is returned.

    virtual void pop() = 0;
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top 
    //               element is removed from the stack.
};

template <class Type>
class stackType : public stackADT<Type>
{
public:
    const stackType<Type>& operator=(const stackType<Type>&);
    //Overload the assignment operator.

//start

    bool operator==(stackType<Type>&);


    //end

    void initializeStack();
    //Function to initialize the stack to an empty state.
    //Postcondition: stackTop = 0

    bool isEmptyStack() const;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty,
    //               otherwise returns false.

    bool isFullStack() const;
    //Function to determine whether the stack is full.
    //Postcondition: Returns true if the stack is full,
    //               otherwise returns false.

    void push(const Type& newItem);
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem 
    //               is added to the top of the stack.

    Type top() const;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program 
    //               terminates; otherwise, the top element
    //               of the stack is returned.

    void pop();
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top 
    //               element is removed from the stack.

    stackType(int stackSize = 100);
    //constructor
    //Create an array of the size stackSize to hold 
    //the stack elements. The default stack size is 100.
    //Postcondition: The variable list contains the base
    //               address of the array, stackTop = 0, and  
    //               maxStackSize = stackSize.

    stackType(const stackType<Type>& otherStack);
    //copy constructor

    ~stackType();
    //destructor
    //Remove all the elements from the stack.
    //Postcondition: The array (list) holding the stack 
    //               elements is deleted.

private:
    int maxStackSize; //variable to store the maximum stack size
    int stackTop;     //variable to point to the top of the stack
    Type* list;       //pointer to the array that holds the
                      //stack elements

    void copyStack(const stackType<Type>& otherStack);
    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and
    //               assigned to this stack.
};

template <class Type>
void stackType<Type>::initializeStack()
{
    stackTop = 0;
}//end initializeStack

template <class Type>
bool stackType<Type>::isEmptyStack() const
{
    return(stackTop == 0);
}//end isEmptyStack

template <class Type>
bool stackType<Type>::isFullStack() const
{
    return(stackTop == maxStackSize);
} //end isFullStack

template <class Type>
void stackType<Type>::push(const Type& newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = newItem;   //add newItem to the 
                                    //top of the stack
        stackTop++; //increment stackTop
    }
    else
        cout << "Cannot add to a full stack." << endl;
}//end push

template <class Type>
Type stackType<Type>::top() const
{
    assert(stackTop != 0);          //if stack is empty, 
                                    //terminate the program
    return list[stackTop - 1];      //return the element of the
                                    //stack indicated by 
                                    //stackTop - 1
}//end top

template <class Type>
void stackType<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--;                 //decrement stackTop 
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
stackType<Type>::stackType(int stackSize)
{
    if (stackSize <= 0)
    {
        cout << "Size of the array to hold the stack must "
            << "be positive." << endl;
        cout << "Creating an array of size 100." << endl;

        maxStackSize = 100;
    }
    else
        maxStackSize = stackSize;   //set the stack size to 
                                    //the value specified by
                                    //the parameter stackSize

    stackTop = 0;                   //set stackTop to 0
    list = new Type[maxStackSize];  //create the array to
                                    //hold the stack elements
}//end constructor

template <class Type>
stackType<Type>::~stackType() //destructor
{
    delete[] list; //deallocate the memory occupied 
                    //by the array
}//end destructor

template <class Type>
void stackType<Type>::copyStack(const stackType<Type>& otherStack)
{
    delete[] list;
    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;

    list = new Type[maxStackSize];

    //copy otherStack into this stack
    for (int j = 0; j < stackTop; j++)
        list[j] = otherStack.list[j];
} //end copyStack


template <class Type>
stackType<Type>::stackType(const stackType<Type>& otherStack)
{
    list = NULL;

    copyStack(otherStack);
}//end copy constructor

template <class Type>
const stackType<Type>& stackType<Type>::operator=
(const stackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this;
} //end operator=         

//start

template <class Type>
bool stackType<Type>::operator==
(stackType<Type>& stacker)
{
    stackType<Type> stackA, stackB;
    bool result = false;
    stackA.copyStack(*this);
    stackB.copyStack(stacker);

    while (!stackA.isEmptyStack() && !stackB.isEmptyStack())
    {
        if (stackA.top() == stackB.top())
        {
            stackA.pop();
            stackB.pop();
            if (stackA.isEmptyStack() && stackB.isEmptyStack())
            {
                result = true;
            }
        }
        else
        {
            result = false;
        }

    }

    return result;

}


//end

void testCopyConstructor(stackType<int> otherStack);

void testCopyConstructor(stackType<int> otherStack)
{
    if (!otherStack.isEmptyStack())
        cout << "otherStack is not empty." << endl
        << "The top element of otherStack: "
        << otherStack.top() << endl;
}

int main()
{
    stackType<int> stack(50);
    stackType<int> copyStack(50);
    stackType<int> dummyStack(100);

    stack.initializeStack();
    stack.push(23);
    stack.push(45);
    stack.push(38);
    copyStack = stack;  //copy stack into copyStack

    cout << "The elements of copyStack: ";
    while (!copyStack.isEmptyStack())  //print copyStack
    {
        cout << copyStack.top() << " ";
        copyStack.pop();
    }
    cout << endl;

    copyStack = stack;
    testCopyConstructor(stack);  //test the copy constructor

    if (!stack.isEmptyStack())
        cout << "The original stack is not empty." << endl
        << "The top element of the original stack: "
        << copyStack.top() << endl;

    dummyStack = stack;  //copy stack into dummyStack

    cout << "The elements of dummyStack: ";
    while (!dummyStack.isEmptyStack())  //print dummyStack
    {
        cout << dummyStack.top() << " ";
        dummyStack.pop();
    }
    cout << endl;

    //start
    cout << endl << "::START OF CODE RUN::" << endl;

    stackType<int> stackOne(20);
    stackType<int> stackTwo(20);
    stackType<int> stackThree(30);

    stackOne.push(4);
    stackOne.push(20);
    stackOne.push(80);
    stackOne.push(100);
    stackOne.push(42);

    stackTwo.push(4);
    stackTwo.push(20);
    stackTwo.push(80);
    stackTwo.push(100);
    stackTwo.push(42);

    stackThree.push(75);
    stackThree.push(60);

    cout << stackOne.top() << " " << stackTwo.top() << endl;

    if (stackOne == stackTwo)
    {
        cout << "stackOne is equal to stackTwo" << endl;
    }
    else
    {
        cout << "stackOne is NOT equal to stackTwo" << endl;
    }

    if (stackOne == stackThree)
    {
        cout << "stackOne is equal to stackThree" << endl;
    }
    else
    {
        cout << "stackOne is NOT equal to stackThree" << endl;
    }

    cout << "20 has been pushed onto stackOne" << endl;
    stackOne.push(20);

    if (stackOne == stackTwo)
    {
        cout << "stackOne is equal to stackTwo" << endl;
    }
    else
    {
        cout << "stackOne is NOT equal to stackTwo" << endl;
    }
    cout << endl << "::END OF CODE RUN::" << endl;
    //end
    return 0;
}
