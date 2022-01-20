//Day5Problem_RamiWailShoula.cpp

// C++ program for linked list implementation of stack
#include <iostream>
#include "ITI.h"
//#include <complex> //not needed
using namespace std;

//complex part //done last
//**********COMPLEX CLASS************************
class Complex {
private:
	double real, imag;
public:
	Complex() {
		real = imag = 0;
	}
	///////////////////////////////////////////////////
	Complex(double r) {
		real = r;
		imag = 0;
	}
	///////////////////////////////////////////////////
	Complex(double r, double i) {
		real = r;
		imag = i;
	}
	///////////////////////////////////////////////////
	Complex(Complex& obj) {
		real = obj.real;
		imag = obj.imag;
	}
	///////////////////////////////////////////////////
	Complex add(Complex c) {
		Complex Add;
		Add.real = real + c.real;
		Add.imag = imag + c.imag;
		return Add;
	}
	///////////////////////////////////////////////////
	Complex sub(Complex c) {
		Complex Sub;
		Sub.real = real - c.real;
		Sub.imag = imag - c.imag;
		return Sub;
	}
	///////////////////////////////////////////////////
	Complex mult(Complex c) {
		Complex Mult;
		Mult.real = real * c.real - imag * c.imag;
		Mult.imag = real * c.imag - c.real * imag;
		return Mult;
	}
	///////////////////////////////////////////////////
	Complex multbyNo(Complex c) {
		Complex multbyNo;
		cout << "\nPlease enter No. for multiplication: ";
		int mult = 0;
		cin >> mult;
		multbyNo.real = real * mult;
		multbyNo.imag = imag * mult;
		return multbyNo;
	}
	///////////////////////////////////////////////////
	Complex divbyNo(Complex c) {
		Complex divbyNo;
		cout << "\nPlease enter No. for division: ";
		int div = 0;
		cin >> div;
		divbyNo.real = real / div;
		divbyNo.imag = imag / div;
		return divbyNo;
	}
	///////////////////////////////////////////////////
	Complex div(Complex c) {
		Complex Div;
		Div.real = (real * c.real + imag * c.imag) / (c.real * c.real + c.imag * c.imag);
		Div.imag = (imag * c.real + real * c.imag) / (c.real * c.real + c.imag * c.imag);
		return Div;
	}
	///////////////////////////////////////////////////
	void print() {
		cout << real << "+" << imag << "i" << endl << endl;
	}
	///////////////////////////////////////////////////
	double getReal() const {
		return real;
	}
	///////////////////////////////////////////////////
	double getImag() const {
		return imag;
	}
	///////////////////////////////////////////////////
	void setReal(double re) {
		real = re;

	}
	///////////////////////////////////////////////////
	void setImag(double im) {
		imag = im;
	}
	///////////////////////////////////////////////////
};

// A class to represent a stack // using dynamic allocation (pointers)
class StackNode {
public:
	int data;
	StackNode* next;
	//StackNode(const StackNode& x) {
	//	peek(root)
	//}
};

//copy constructor class

StackNode* newNode(int data)
{
	StackNode* stackNode = new StackNode();
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

int isEmpty(StackNode* root)
{
	return !root;
}

void push(StackNode** root, int data)
{
	StackNode* stackNode = newNode(data);
	stackNode->next = *root;
	*root = stackNode;
	cout << data << " pushed to stack\n";
}

int pop(StackNode** root)
{
	if (isEmpty(*root))
		return INT_MIN;
	StackNode* temp = *root;
	*root = (*root)->next;
	int popped = temp->data;
	free(temp);

	return popped;
}

int peek(StackNode* root)
{
	if (isEmpty(root))
		return INT_MIN;
	return root->data;
}

// Driver code
int main()
{
	//Q1 // Complex operations
	double real1, imag1, real2, imag2;

	cout << "Enter the Real  part of First Number: ";
	cin >> real1;
	cout << "Enter the imaginary  part of First Number: ";
	cin >> imag1;
	Complex obj1(real1, imag1);
	obj1.print();

	cout << "Enter the Real part of Second Number: ";
	cin >> real2;
	cout << "Enter the Imaginary part of second number: ";
	cin >> imag2;
	Complex obj2(real2, imag2);
	obj2.print();

	Complex c;
	c = obj1.add(obj2);
	cout << "Addition is : (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;
	c = obj1.sub(obj2);
	cout << endl << "Subtraction is : (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	c = obj1.mult(obj2);
	cout << endl << "Multiplication is : (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	c = obj1.div(obj2);
	cout << endl << "Division result  is : (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	cout << "Multiplicatiion by No. operation for 1st No.: \n";
	c = obj1.multbyNo(obj1);
	cout<<"Multiplicatiion by No. is: (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	cout << "Division by No. operation for 1st No.: \n";
	c = obj1.divbyNo(obj1);
	cout << "Division by No. is: (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	cout << "Multiplicatiion by No. operation for 2nd No.: \n";
	c = obj2.multbyNo(obj2);
	cout << "Multiplicatiion by No. is: (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	cout << "Division by No. operation for 2nd No.: \n";
	c = obj2.divbyNo(obj2);
	cout << "Division by No. is: (" << c.getReal() << ")+(" << c.getImag() << ")i" << endl;

	//thank you
	//Done complex part
	system("pause");
	clrscr();
	//Q2 // Implement Stack class // using dynamic allocation for the array
	StackNode* root = NULL;
	int stackelemts = 10;
	int stackcount = 0;
	int dummyroot = 0;
	int arrcopy[10];
	cout << "Q2: stack size is " << stackelemts << " elemnts only!\n";
	cout << "Kindly push elements into stack: ";
	while (stackcount < stackelemts) {
		cout << "Do you want to add (push) new element in stack? (1/0)\n";
		int selection = 0;
		cin >> selection;
		while ((selection != 0) && (selection != 1)) {
			cout << "incorrect selection, enter 1 for add or 0 for don't add:\n";
			cin >> selection;
		}
		if (selection == 0)	break;
		else
		{
			cout << "enter int. stack element: ";
			cin >> dummyroot;
			push(&root, dummyroot);
			arrcopy[stackcount] = dummyroot;
			stackcount++;
		}
	}
	//push(&root, 10);
	//push(&root, 20);
	//push(&root, 30);
	int popcount = 0;
	cout << "How many elements to remove (pop)? ";
	cin >> popcount;
	while ((popcount > stackcount) || (popcount < 0))
	{
		cout << "Enter Proper +ve count less than current stack size: " << stackcount<< endl;
		cin >> popcount;
	}
	for (int ii = 0; ii < popcount; ii++) {
		cout << pop(&root) << " popped from stack\n";
		if (ii==(stackcount-1)) {
			cout << "Stack is emptied successfully\n";
		}
		else cout << "Top element is " << peek(root) << endl;
	}
	cout << "Elements present in stack : ";
	//print all elements in stack :
	while (!isEmpty(root))
	{
		// print top element in stack
		cout << peek(root) << " ";
		// remove top element in stack
		pop(&root);
	}
	cout << endl;
	system("pause");
	//clrscr();
	cout << "Q3: Copy constructor to class stack: \n";
	cout << "Q3: Copied stack before deletion is: \n";
	//copying and printing original entered stack
	//Since stack is FILO or LIFO (First in Last out)/(Last in First out) the first element is the last one popped
	//I reversed the for loop to show this behavior as first element is always the lastmost saved (in the array representation)
	for (int i = stackcount-1; i > -1; i--) { // copied string is reversed so count is reversed
		cout << arrcopy[i] << " ";
	}
	cout << endl;
	cout << "Copied stack after deletion (current stack) is: \n";
	//copying and printing current available stack
	for (int i = stackcount - 1 -popcount; i > -1; i--) { // remove popped entries
		cout << arrcopy[i] << " ";
	}
	cout << endl;
	return 0;
}

