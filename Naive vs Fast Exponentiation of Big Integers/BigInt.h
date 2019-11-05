/* 
 * The interface for a Big Integer library.
 * This is a basic big integer library. Four 
 * binary arithmetic operations are provided:
 * addition, subtraction and multiplication.
 * @author Duncan
 * @since 99/99/9999
 */
#include <string>
#include <cstdlib>
#include <iostream>
#include <exception>


using namespace std;

#ifndef BIGINT_H
#define	BIGINT_H
class BigInt
{
private:
    string number;
public:
    /**
     * Creates 0
     */
    BigInt();
    /**
     * Deallocates the memory for this big integer
     */
    ~BigInt();
    /**
     * Creates the specified integer
     * @param s the string representation of an integer
     * @throws an exception is the specified parameter
     * cannot be parsed into an integer
     */    
    BigInt(string s);
    /**
     * Creates a big integer equivalent to the specified
     * big integer
     * @param i a big integer
     */    
    BigInt(const BigInt& i);
    /**
     * Gives a string representation of this object
     * @return a string representation of this number
     */
    string str() const;
    /**
     * put the specified big integer into an output stream
     * @param rhs a big integer
     * @return a reference to an output stream
     */
    friend ostream& operator<<(ostream& os, const BigInt& bigInt);
    /**
     * extracts a big integer from an input stream.
     * @param rhs a big integer
     * @return a reference to an input stream
     */
    friend istream& operator>>(istream& os, BigInt& bigInt);
    
    /**
     * Assigns the specified big integer to the specified big integer
     * @param rhs a big integer
     * @return a big integer equivalent to the specified big integer
     */
    BigInt& operator=(const BigInt& rhs);
    /**
     * Computes the sum of the specified big integers
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return the sum of the specified big integers
     */
    friend BigInt operator+(BigInt lhs, const BigInt& rhs);
    /**
     * Computes the difference of the specified big integers
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return the difference of the specified big integers
     */    
    friend BigInt operator-(BigInt lhs, const BigInt& rhs);
    /**
     * Computes the product of the specified big integers
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return the product of the specified big integers
     */    
    friend BigInt operator*(BigInt lhs, const BigInt& rhs);    
    /**
     * Computes the quotient of the specified big integers
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return the quotient of the specified big integers
     */   
    friend BigInt operator/(BigInt lhs, const BigInt& rhs);             
    /**
     * Removes leading and trailing whitespace characters from the specified string
     * @param text a string
     * @return the specified string without leading and trailing whitespace characters
     */
    friend string trim(string text);
    /**
     * Determines whether one big integer is less than another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is less than the right operand;
     * otherwise, false
     */    
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
    /**
     * Determines whether one big integer is equal to another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is equal to the right operand;
     * otherwise, false
     */    
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    /**
     * Determines whether one big integer is greater than another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is greater than the right operand;
     * otherwise, false
     */        
    friend bool operator>(const BigInt& lhs, const BigInt& rhs);    
    /**
     * Determines whether one big integer is less than or equal to another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is less than or equal to the right
     * operand; otherwise, false
     */        
    friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
    /**
     * Determines whether one big integer is not equal to another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is not equal to the right operand;
     * otherwise, false
     */        
    friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
    /**
     * Determines whether one big integer is greater than or equal to another
     * @param lhs the left operand, a big integer
     * @param rhs the right operand a big integer
     * @return true when the left operand is greater than or equal to
     * the right operand; otherwise, false
     */        
    friend bool operator>=(const BigInt& lhs, const BigInt& rhs);   
};
/**
 * An auxiliary function to support the overloaded + operator.
 * This function does the heavy lifting for the operator; i.e.
 * the + operator is a wrapper for this function
 * @param augend a string representation of the unsigned left operand
 * @param addend a string representation of the unsigned right operand
 * @return a unsigned representation of the sum of the augend and 
 * addend
 */
string add(string augend, string addend);
/**
 * An auxiliary function to support the overloaded - operator.
 * This function does the heavy lifting for the operator; i.e.
 * the - operator is a wrapper for this function
 * @param minuend a string representation of the unsigned left operand
 * @param subtrahend a string representation of the unsigned right operand
 * @return a unsigned representation of the difference of the minuend and 
 * subtrahend
 */
string subtract(string minuend, string subtrahend);
/**
 * An auxiliary function to support the overloaded * operator.
 * This function does the heavy lifting for the operator; i.e.
 * the * operator is a wrapper for this function; it does basic
 * grade school multiplication but has dynamic programming 
 * (memoization) to lookup previous products involving a digit
 * that has already been used as the multiplier.
 * @param multiplicand a string representation of the unsigned left operand
 * @param multiplier a string representation of the unsigned right operand
 * @return a unsigned representation of the product of the augend and 
 * addend
 */
string multiply(string multiplicand, string multiplier);    
/**
 * An auxiliary function to support the overloaded / operator.
 * This function does the heavy lifting for the operator; i.e.
 * the / operator is a wrapper for this function
 * @param dividend a string representation of the unsigned left operand
 * @param divisor a string representation of the unsigned right operand
 * @return a unsigned representation of the quotient of the dividend and 
 * divisor
 */
string div(string dividend, string divisor);  
#endif	/* BIGINT_H */
