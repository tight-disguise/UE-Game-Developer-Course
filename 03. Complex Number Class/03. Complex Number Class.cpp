/* 03. Complex Number Class.cpp
 *
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 3:
 * - write a class to represent complex numbers
 * - class should contain:
 *   - default, parametric & copying constructor
 *   - destructor
 *   - overloaded operators: +, -, *, /, =
 *   - Print() method to display complex number
 * - main() function should implement a set of tests of implemented complex number class & operations.
 * 
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <cmath>	// pow()

using namespace std;

class ComplexNumber
{
private:
    double m_real;
    double m_imaginary;

public:
    // Default constructor
    ComplexNumber(): m_real(0), m_imaginary(0)
    {
    }

    // Parametric constructor
    ComplexNumber(double real, double imaginary): m_real(real), m_imaginary(imaginary)
    {
    }

    // Copy constructor
    ComplexNumber(const ComplexNumber& complexNumber)
    {
        m_real = complexNumber.m_real;
        m_imaginary = complexNumber.m_imaginary;
    }

    // Destructor (not much to do here really, but we'll see when objects are destructed)
    ~ComplexNumber()
    {
        cout << "BOOM! Complex Number object destroyed!\n";
    }

    // Setters
    void setReal(double real)
    {
        m_real = real;
    }

    void setImaginary(double imaginary)
    {
        m_imaginary = imaginary;
    }

    // Getters
    double GetReal() const
    {
        return m_real;
    }

    double GetImaginary() const
    {
        return m_imaginary;
    }

    // Print() method
    void Print() const
    {
        m_imaginary >= 0
            ? cout << m_real << "+" << m_imaginary << "i" << endl
            : cout << m_real << m_imaginary << "i" << endl;
    }

    // Overloaded operators
    ComplexNumber operator+(const ComplexNumber& complexNumber) const
    {
        return {m_real + complexNumber.m_real, m_imaginary + complexNumber.m_imaginary};
    }

    ComplexNumber operator-(const ComplexNumber& complexNumber) const
    {
        return {m_real - complexNumber.m_real, m_imaginary - complexNumber.m_imaginary};
    }

    ComplexNumber operator*(const ComplexNumber& complexNumber) const
    {
        return {
            m_real * complexNumber.m_real - m_imaginary * complexNumber.m_imaginary,
            m_real * complexNumber.m_imaginary + m_imaginary * complexNumber.m_real
        };
    }

    ComplexNumber operator/(const ComplexNumber& complexNumber) const
    {
        return {
            (m_real * complexNumber.m_real + m_imaginary * complexNumber.m_imaginary) /
            (pow(complexNumber.m_real, 2) + pow(complexNumber.m_imaginary, 2)),
            (m_imaginary * complexNumber.m_real - m_real * complexNumber.m_imaginary) /
            (pow(complexNumber.m_real, 2) + pow(complexNumber.m_imaginary, 2))
        };
    }

    ComplexNumber& operator=(const ComplexNumber& complexNumber)
    {
        if (this != &complexNumber)
        {
            m_real = complexNumber.m_real;
            m_imaginary = complexNumber.m_imaginary;
        }
        return *this;
    }

    // We're friends with << operator :)
    friend ostream& operator<<(ostream& os, const ComplexNumber& complexNumber);
};

// Bonus: overloaded << operator for easy printing to output stream
ostream& operator<<(ostream& os, const ComplexNumber& complexNumber)
{
    complexNumber.m_imaginary >= 0
        ? os << complexNumber.m_real << "+" << complexNumber.m_imaginary << "i"
        : os << complexNumber.m_real << complexNumber.m_imaginary << "i";

    return os;
}

// Show host
constexpr char showHost[] = "~(*_*)~";

/* MAIN PROGRAM CODE */
int main()
{
    cout << showHost << ": Welcome to complex numbers math 101 show!\n\n";

    // Default constructor is used to create these two complex numbers...
    ComplexNumber complexNumber1, complexNumber2;
    // ...and for those, parametric constructor is used.
    ComplexNumber complexNumber3{1.1, -2.2}, complexNumber4{-1.3, 4.2};

    cout << showHost << ": A few complex numbers created with default (1 & 2) and parametric constructors (3 & 4):\n";
    // Printing numbers using overloaded << operator
    cout << "complexNumber1 = " << complexNumber1 << '\n';
    cout << "complexNumber2 = " << complexNumber2 << '\n';
    cout << "complexNumber3 = " << complexNumber3 << '\n';
    cout << "complexNumber4 = " << complexNumber4 << '\n' << endl;

    cout << showHost << ": Let's assign new values to complex numbers 1 & 2 using overloaded = operator:\n";
    complexNumber1 = complexNumber3;
    complexNumber2 = ComplexNumber{-8.7, 4.6};
    cout << "complexNumber1 = " << complexNumber1 << '\n';
    cout << "complexNumber2 = " << complexNumber2 << '\n' << endl;

    // Copy constructor in action
    ComplexNumber complexNumber5{complexNumber3}, complexNumber6{complexNumber4};

    // Let's use Print() this time
    cout << showHost << ": Two new complex numbers initialized using copy constructor:\n";
    cout << "complexNumber5 = ";
    complexNumber5.Print();
    cout << "complexNumber6 = ";
    complexNumber6.Print();
    cout << endl;
    
    cout << showHost << ": Now let's perform basic math operations using our fancy overloaded operators!\n";

    cout << showHost << ": ComplexNumber1 + ComplexNumber2 = " << complexNumber1 + complexNumber2 << '\n';
    cout << showHost << ": ComplexNumber3 - ComplexNumber4 = " << complexNumber3 - complexNumber4 << '\n';
    cout << showHost << ": ComplexNumber5 * ComplexNumber6 = " << complexNumber5 * complexNumber6 << '\n';
    cout << showHost << ": ComplexNumber1 / ComplexNumber6 = " << complexNumber1 / complexNumber6 << '\n';

    cout << '\n' << showHost << ": That's all folks! See you next time!\n";
    cout << showHost << ": (BTW, have you noticed destructor in action? BOOM!)\n" << endl;
    
    // MS Windows trick to keep terminal window open after program finishes.
    //system("pause");

    return 0;
}
