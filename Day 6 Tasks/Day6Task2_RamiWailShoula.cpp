//Day6Task2_RamiWailShoula.cpp
// Implement all operator overloading in Class Complex;
//Full implementation without using <complex> header

//includes
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;
using std::string;


// Complex class definition
class Complex {
public:
	// Default + Overloaded constructor.
	Complex(double = 0.0, double = 0.0);

	// Type conversion constructor (string ==> Complex).
	Complex(const string&);

	// Use compiler-generated copy constructor, assignment, and destructor.
	// Complex(const Complex&);
	// Complex& operator=(const Complex&);
	// ~Complex();

	friend std::ostream& operator <<(std::ostream& rOs, const Complex& rFrom);

	friend std::istream& operator >>(std::istream& rIs, Complex& rTo);

	Complex operator +(const Complex& rhs);

	Complex operator +(const double rhs);

	friend Complex operator +(const double lhs, const Complex& rhs);

	Complex& operator +=(const Complex& rhs);

	Complex& operator +=(const double rhs);

	Complex operator -(const Complex& rhs);

	Complex operator -(const double rhs);

	friend Complex operator -(const double lhs, const Complex& rhs);

	Complex& operator -=(const Complex& rhs);

	Complex& operator -=(const double rhs);

	Complex operator *(const Complex& rhs);

	Complex operator *(const double rhs);

	friend Complex operator *(const double lhs, const Complex& rhs);

	Complex& operator *=(const Complex& rhs);

	Complex& operator *=(const double rhs);

	Complex operator /(const Complex& rhs);

	Complex operator /(const double rhs);

	friend Complex operator /(const double lhs, const Complex& rhs);

	Complex& operator /=(const Complex& rhs);

	Complex& operator /=(const double rhs);

	bool operator ==(const Complex& rhs);

	bool operator !=(const Complex& rhs);

	Complex operator -();

	Complex operator *();

	Complex& operator ++();

	Complex operator ++(int);

	Complex& operator --();

	Complex operator --(int);

	operator double();

	void SetReal(double = 0.0);
	void SetImaginary(double = 0.0);
	void SetComplex(double = 0.0, double = 0.0);

	//overload void SetComplex(const Complex&);

	void SetComplex(const Complex&);

	// getters
	double GetReal()const;
	double GetImaginary()const;
	const Complex& GetComplex()const;

private:

	bool Is_Number(const string& testNumber);

	// DATA MEMBERS
	double mReal;
	double mImaginary;
};
// end class Complex

// Complex Default + Overloaded Constructor
Complex::Complex(double aReal, double aImaginary) : mReal(aReal), mImaginary(aImaginary) {
	this->SetComplex(aReal, aImaginary);
}
// end Complex constructor

// String Conversion Constructor
Complex::Complex(const string& aString) {
	int posPlus = aString.find("+");
	int posMinus = aString.find("-");
	int posSymbol = max(posPlus, posMinus);
	int posI = aString.find("i");
	int posJ = aString.find("j");
	int posImSymbol = max(posI, posJ);
	if (posSymbol == -1 || posImSymbol == -1) {
		if (this->Is_Number(aString) && posImSymbol == -1)
			this->SetComplex(stod(aString));
		else if (this->Is_Number(aString) && posImSymbol != -1)
			this->SetComplex(0, stod(aString));
		else {
			cout << "Provided string cannot be converted to complex number. Setting string to zero." << endl;
			this->SetComplex();
		}

		return;
	}
	double realDouble = 1.0;
	double imaginaryDouble = 1.0;
	int posStart = -1;
	// for negative symbols
	if (posPlus == -1) {
		imaginaryDouble = -1.0;
		if (count(aString.begin(), aString.end(), '-') == 2) {
			realDouble = -1.0;
			posSymbol = aString.find_last_of("-");
			posStart = aString.find_first_of("-");
		}
	}
	else {
		if (posMinus != -1) {
			realDouble = -1.0;
			posStart = aString.find_first_of("-");
		}
	}
	string realString = aString.substr(posStart + 1, posSymbol);
	string gap = aString.substr(posSymbol + 1, posImSymbol - posSymbol + 1);
	string imaginaryString;
	if (this->Is_Number(gap))	// a + bi case
		imaginaryString = aString.substr(posSymbol + 1);
	else			// a + ib case
		imaginaryString = aString.substr(posImSymbol + 1);
	if (this->Is_Number(realString))
		realDouble *= stod(realString);
	else
		realDouble = 0.0;
	imaginaryDouble *= stod(imaginaryString);

	this->SetComplex(realDouble, imaginaryDouble);
}
// end Complex constructor

// Stream Insertion
ostream& operator <<(ostream& rOs, const Complex& rFrom) {
	rOs << "(" << rFrom.GetReal() << ") + (" << rFrom.GetImaginary() << ")i";
	return rOs;
}
// end stream insertion

// Stream Extraction
istream& operator >>(istream& rIs, Complex& rTo) {
	int aReal, aImaginary;
	cout << "Enter real part: ";
	rIs >> aReal;
	cout << "Enter imaganiary part: ";
	rIs >> aImaginary;

	rTo.SetComplex(aReal, aImaginary);

	return rIs;
}
// end stream extraction

// Addition operator
Complex Complex::operator +(const Complex& rhs) {
	Complex t = *this;
	return t += rhs;
}
// end Addition operator

// Overloaded addition operator
Complex Complex::operator +(const double rhs) {
	Complex t = *this;
	return t += rhs;
}
// end Addition operator

// Friend function to overloaded addition operator
Complex operator +(const double lhs, const Complex& rhs) {
	Complex t = rhs;
	return t += lhs;
}
// end Addition operator

// Addition assignment operator
Complex& Complex::operator +=(const Complex& rhs) {
	*this += rhs.GetReal();
	this->SetImaginary(this->GetImaginary() + rhs.GetImaginary());
	return *this;
}
// end addition assignment operator 

// Overloaded Addition assignment operator
Complex& Complex::operator +=(const double rhs) {
	this->SetReal(this->GetReal() + rhs);

	return *this;
}
// end addition assignment operator 

// Subtraction operator
Complex Complex::operator -(const Complex& rhs) {
	Complex t = *this;
	return t -= rhs;
}
// end Subtraction operator

// Overloaded subtraction operator
Complex Complex::operator -(const double rhs) {
	Complex t = *this;
	return t -= rhs;
}
// end subtraction operator

// Friend function to overloaded subtraction operator
Complex operator -(const double lhs, const Complex& rhs) {
	Complex t = rhs;
	t = -t;
	return t += lhs;
}
// end subtraction operator

// Subtraction assignment operator
Complex& Complex::operator -=(const Complex& rhs) {
	*this -= rhs.GetReal();
	this->SetImaginary(this->GetImaginary() - rhs.GetImaginary());
	return *this;
}
// end subtraction assignment operator 

// Overloaded subtraction assignment operator
Complex& Complex::operator -=(const double rhs) {
	this->SetReal(this->GetReal() - rhs);

	return *this;
}
// end subtraction assignment operator

// Multiplication operator
Complex Complex::operator *(const Complex& rhs) {
	Complex t(this->GetComplex());
	return (t *= rhs);
}
// end multiplication operator

// Overloaded multiplication operator
Complex Complex::operator *(const double rhs) {
	Complex t(this->GetComplex());
	return (t *= rhs);
}
// end multiplication operator

// Friend function to overloaded multiplication operator
Complex operator *(const double lhs, const Complex& rhs) {
	Complex t = rhs;
	return t *= lhs;
}
// end multiplication operator

// Multiplication assignment operator
Complex& Complex::operator *=(const Complex& rhs) {
	this->SetComplex(this->GetReal() * rhs.GetReal() - this->GetImaginary() * rhs.GetImaginary(), this->GetReal() * rhs.GetImaginary() + this->GetImaginary() * rhs.GetReal());
	return *this;
}
// end multiplication assignment operator 

// Overloaded multiplication assignment operator
Complex& Complex::operator *=(const double rhs) {
	this->SetComplex(this->GetReal() * rhs, this->GetImaginary() * rhs);

	return *this;
}
// end multiplication assignment operator

// Division operator
Complex Complex::operator /(const Complex& rhs) {
	Complex t(this->GetComplex());

	return (t /= rhs);
}
// end division operator

// Overloaded division operator
Complex Complex::operator /(const double rhs) {
	Complex t(this->GetComplex());

	return (t /= rhs);
}
// end division operator

// Friend function to overloaded division operator
Complex operator /(const double lhs, const Complex& rhs) {
	Complex t;
	t = (Complex)lhs;

	return (t /= rhs);
}
// end division operator

// Division assignment operator
Complex& Complex::operator /=(const Complex& rhs) {
	Complex nmrtr, dnmntr, cnjgt = rhs;
	cnjgt = *cnjgt;
	double dDenom;
	nmrtr = this->GetComplex();
	nmrtr *= cnjgt;
	dnmntr = cnjgt * rhs;
	dDenom = (double)dnmntr;
	this->SetComplex(nmrtr / dDenom);
	return *this;
}
// end division assignment operator 

// Overloaded division assignment operator
Complex& Complex::operator /=(const double rhs) {
	this->SetComplex(this->GetReal() / rhs, this->GetImaginary() / rhs);

	return *this;
}

// end division assignment operator

// Equality operator
bool Complex::operator == (const Complex& rhs) {
	if ((this->GetReal() == rhs.GetReal()) && (this->GetImaginary() == rhs.GetImaginary())) {
		return true;
	}
	else
		return false;
}
// end equality operator

// Non-Equality operator
bool Complex::operator != (const Complex& rhs)
{
	if (*this == rhs)
		return false;
	else
		return true;
}
// end non-Equality operator

// Negation operator
Complex Complex::operator -() {
	Complex temp(-this->GetReal(), -this->GetImaginary());
	return temp;
}
//end negation operator

// Conjugate operator
Complex Complex::operator *() {
	Complex t(this->GetReal(), -this->GetImaginary());
	return t;
}
//end conjugate operator

// pre-increment operator
Complex& Complex::operator++() {
	*this += 1;
	return *this;
}
// end pre-increment operator

// post-increment operator
Complex Complex::operator ++(int) {
	Complex t = *this;
	*this += 1;
	return t;
}
// end post-increment operator

// pre-decrement operator
Complex& Complex::operator --() {
	*this -= 1;
	return *this;
}
// end pre-decrement operator

// post-decrement operator
Complex Complex::operator --(int) {
	Complex t = *this;
	*this -= 1;
	return t;
}
// end post-decrement operator

// Function operator to overload float
Complex::operator double() {
	return this->GetReal();
}
// end function operator

// function that sets real part of complex number
void Complex::SetReal(double aReal) {
	this->mReal = aReal;
}
// end function SetReal

// function that sets imaginary part of complex number
void Complex::SetImaginary(double aImaginary) {
	this->mImaginary = aImaginary;
}
// end function SetImaginary

// function that sets the Complex number
void Complex::SetComplex(double aReal, double aImaginary) {
	this->SetReal(aReal);
	this->SetImaginary(aImaginary);
}
// end function SetComplex

// overloaded function that sets the Complex number
void Complex::SetComplex(const Complex& rComplex) {
	this->SetComplex(rComplex.GetReal(), rComplex.GetImaginary());
}
// end function SetComplex

// function that gets real part of complex number
double Complex::GetReal()const {
	return this->mReal;
}
// end function GetReal

// function that gets imaginary part of complex number
double Complex::GetImaginary()const {
	return this->mImaginary;
}
// end function GetImaginary

// function that gets the Complex number
const Complex& Complex::GetComplex()const {
	return *this;
}
// end function GetComplex

bool Complex::Is_Number(const string& testNumber) {

	try {
		std::stod(testNumber);
	}
	catch (...) {
		return false;
	}

	return true;
}

//driving shit
void main()
{
	cout << "Q2: Implement all operator overloading in Class Complex";
	Complex c1(23, 8), c2 = (string)"5+4i", c3("-5 + 0 j");

	Complex t0 = (c1 + 8. - c2 * c3);
	Complex t1 = 8. * (c1 + c3) - c2;
	Complex t2 = c2 * 8. / (c1 + c3);
	Complex t3 = c2 - 8. * (c3) / c1;
	Complex t4 = (c3)+(c1)-8. * (c2);
	Complex t5 = (c3)*c2 + (c1)-8.;
	cout << t0 << endl;
	cout << t1 << endl;
	cout << t2 << endl;
	cout << t3 << endl;
	cout << t4 << endl;
	cout << t5 << endl;

	Complex c4;
	c4 = (Complex)"23 + 8j";
	if (c4 != c2)
		cout << "Not Equal" << endl;
	else
		cout << "Equal" << endl;
	c4 = *c2;
	cout << "Conjugate of " << c2 << " is: " << c4 << endl;

	c1 /= c2;
	cout << c1 << endl;
	(c2 /= 2.325) = c3;
	cout << c2 << endl;

	double ab = c4;
	cout << ab << endl;

	system("pause");
}
// end main


