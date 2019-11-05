
/* 
 * A simple implementation for a Big Integer library.
 * This library has no exception-handling capability and
 * four binary arithmetic operations are provided:
 * addition, subtraction, multiplication and integer division.
 * Note: Integer division is implemented using
 * addition, subtraction and multiplication.
 * @author Duncan
 * @since 99/99/9999
 * @see BigInt.h
 */
#include "BigInt.h"
#include <stdexcept>
using namespace std;

/**
 * Removes leading and trailing whitespace characters from the specified string
 * @param text a string
 * @return the specified string without leading and trailing whitespace characters
 */
string trim(string text)
{
    const auto startIndex = text.find_first_not_of(" \t");
    if (startIndex == string::npos) text = "";
    const auto endIndex = text.find_last_not_of(" \t");
    text = text.substr(startIndex, endIndex - startIndex + 1);
    return text;
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
    if (lhs.number[0] == '-' && rhs.number[0] != '-')
        return true;
    if (lhs.number[0] != '-' && rhs.number[0] == '-')
        return false;
    if (lhs.number[0] == '-' && rhs.number[0] == '-')
    {
        if (lhs.number.length() < rhs.number.length())
            return false;
        if (lhs.number.length() > rhs.number.length())
            return true;
        return lhs.number.substr(1) > rhs.number.substr(1);
        
    }
    else
    {
        if (lhs.number.length() < rhs.number.length())
            return true;
        if (lhs.number.length() > rhs.number.length())
            return false;
        return lhs.number < rhs.number;
    }
    
}

bool operator==(const BigInt& lhs, const BigInt& rhs)
{    
    return lhs.number == rhs.number;
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{  
    if (lhs.number[0] == '-' && rhs.number[0] != '-')
        return false;
    if (lhs.number[0] != '-' && rhs.number[0] == '-')
        return true;
    if (lhs.number[0] == '-' && rhs.number[0] == '-')
    {
        if (lhs.number.length() < rhs.number.length())
            return true;
        if (lhs.number.length() > rhs.number.length())
            return false;
        return lhs.number.substr(1) < rhs.number.substr(1);
        
    }
    else
    {
        if (lhs.number.length() < rhs.number.length())
            return false;
        if (lhs.number.length() > rhs.number.length())
            return true;  
        return lhs.number > rhs.number;
    }    
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
    return !(lhs > rhs);
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
    return !(lhs == rhs);
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
    return !(lhs < rhs);
}

BigInt::BigInt()
{
    number = "0";
}

BigInt::~BigInt()
{
    //Compiler-generated
}

BigInt::BigInt(string s)
{
    s = trim(s);
    if (!(s[0] == '+' || s[0] == '-' || (s[0] >= '0' && s[0] <= '9')))
       throw invalid_argument("Illegal Argument");  
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            throw invalid_argument("Illegal Argument");
    }
    if (s[0] == '+')
        s = s.substr(1);
    number = s;

}

BigInt::BigInt(const BigInt& i)
{
    number = i.number;
}

string BigInt::str() const
{
    return number;
}

ostream &operator<<(ostream& os, const BigInt& bigInt)
{
    os << bigInt.number;
    return os;
}

istream &operator>>( istream  &is, BigInt& bigInt) 
{ 
    is >> bigInt.number;
    if (bigInt.number[0] == '+')
        bigInt.number = bigInt.number.substr(1);
    return is;            
}

BigInt& BigInt::operator =(const BigInt& rhs)
{
    if (this != &rhs) 
        number = rhs.number;
    return *this;
}

BigInt operator+(BigInt lhs, const BigInt& rhs)
{
    if (rhs < BigInt("0"))
        return lhs - BigInt(rhs.number.substr(1));
    if (lhs < BigInt("0"))
        return rhs - BigInt(lhs.number.substr(1));
    if (lhs.number == "0")
        return rhs;
    if (rhs.number == "0")
        return lhs;
    return BigInt(add(lhs.number,rhs.number));
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
    BigInt u,v;
    if (rhs < BigInt("0"))
        return lhs + BigInt(rhs.number.substr(1));

    if (rhs == BigInt("0"))
        return lhs;
    if (lhs.number == BigInt("0"))
        return BigInt('-'+rhs.number);
  
    if (lhs < BigInt("0"))
    {
        u = BigInt(lhs.number.substr(1));
        return BigInt('-' + (u+rhs).number);
    }
    
    if (lhs < rhs)
        return BigInt('-'+(rhs - lhs).number);
    if (lhs == rhs)
        return BigInt("0");

    return BigInt(subtract(lhs.number,rhs.number));
}

BigInt operator*(BigInt lhs, const BigInt& rhs)
{
    string sum = "",lhss = lhs.number, rhss = rhs.number;
    /* Deals with products that are negative */
    char sign = '+';
    if (lhs < BigInt("0"))
    {
        lhss = lhs.number.substr(1,lhs.number.length()-1);            
        if (rhs > BigInt("0"))
        {
            sign = '-';
            
        }
        else if (rhs < BigInt("0"))
        {
            rhss = rhs.number.substr(1,rhs.number.length()-1);            
        }
    }
    else if (rhs < BigInt("0"))
    {
        rhss = rhs.number.substr(1,rhs.number.length()-1);            
        if (lhs > BigInt("0"))
            sign = '-';
    }
    /* end dealing with negative products */
    if (sign == '-')
        return BigInt('-'+multiply(lhss,rhss));
    return BigInt(multiply(lhss,rhss));
}

BigInt operator/(BigInt lhs, const BigInt& rhs)
{
    string quotient,lhss = lhs.number, rhss = rhs.number;
    /* Deals with signs */
    char sign = '+';
    if (lhs < BigInt("0"))
    {
        lhss = lhs.number.substr(1,lhs.number.length()-1);            
        if (rhs > BigInt("0"))
        {
            sign = '-';
            
        }
        else if (rhs < BigInt("0"))
        {
            rhss = rhs.number.substr(1,rhs.number.length()-1);            
        }
    }
    else if (rhs < BigInt("0"))
    {
        rhss = rhs.number.substr(1,rhs.number.length()-1);            
        if (lhs > BigInt("0"))
            sign = '-';
    }    
    if (lhss.length() < rhss.length())
        return BigInt("0");
    if (lhss.length() == rhss.length())
    {
        if (lhss == rhss)
        {
            if (sign == '-')
                return BigInt(sign+"1");
            return BigInt("1");
        }
        else if (lhss < rhss)
            return BigInt("0");
        else
        {
            quotient = div(lhss,rhss);
            if (sign == '-')
                return BigInt(sign+quotient);
            return BigInt(quotient);
        }            
    }
    quotient = div(lhss,rhss);
    if (sign == '-')
        return BigInt(sign+quotient);
    return BigInt(quotient);
}

string add(string augend, string addend)
{
    string sum = (augend.length() > addend.length()) ?  augend : addend;
    char carry = '0';
    int differenceInLength = abs((int)(augend.size() - addend.size()));
    if(augend.length() > addend.length())
        addend.insert(0, differenceInLength, '0');
    else
        augend.insert(0, differenceInLength, '0');
    int i;
    for(i = augend.length() - 1; i >= 0; i--)
    {
        sum[i] = ((carry-'0')+(augend[i]-'0')+(addend[i]-'0')) + '0';
        if(i != 0)
        {	
            if(sum[i] > '9')
            {
                sum[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    if(sum[0] > '9')
    {
        sum[0]-= 10;
        sum.insert(0,1,'1');
    }
    return sum;
}

string subtract(string minuend, string subtrahend)
{
    string difference = (minuend.length() > subtrahend.length())? minuend : subtrahend;
    int differenceInLength = abs((int)(minuend.size() - subtrahend.size()));
    if(minuend.length() > subtrahend.length())	
        subtrahend.insert(0, differenceInLength, '0');
    else
        minuend.insert(0, differenceInLength, '0');
    int i;
    for(i = minuend.length() - 1; i >= 0; i--)
    {
        if(minuend[i] < subtrahend[i])
        {
            minuend[i] += 10;
            minuend[i-1]--;
        }
        difference[i] = ((minuend[i]-'0')-(subtrahend[i]-'0')) + '0';
    }
    while(difference[0]=='0' && difference.length()!=1)
        difference.erase(0,1);
    return difference;
}

string multiply(string multiplicand, string multiplier)
{
    if(multiplicand.length() > multiplier.length()) 
        multiplicand.swap(multiplier);
    string product = "0", temp;
    string table[10] = {"0"};  // added for memoization
    int i,j, currentDigit, carry;
    for(i = multiplicand.length() - 1; i >= 0; i--)
    {
        temp = multiplier;
        currentDigit = multiplicand[i]-'0';
        if (table[currentDigit] == "") //checking if this product is memoized
        {
            carry = 0;
            for(j = temp.length() - 1; j >= 0; j--)
            {
                temp[j] = ((temp[j]-'0') * currentDigit) + carry;
                if(temp[j] > 9)
                {
                    carry = (temp[j] / 10);
                    temp[j] -= (carry * 10);
                }
                else
                    carry = 0;
                temp[j] += '0';
            }
            if(carry > 0)
                temp.insert(0, 1, (carry+'0'));
            table[currentDigit] = temp;//memorized product
        }
        else
            temp = table[currentDigit]; //lookup
        temp.append((multiplicand.length()-i-1), '0');
        product = add(product, temp); 
    }
    while(product[0] == '0' && product.length()!=1)
        product.erase(0,1);
    return product;
}

string div(string dividend, string divisor)
{
    if (divisor == "0")
        throw invalid_argument("Divide-by-zero exception");
    BigInt n = BigInt(dividend);
    BigInt d = BigInt(divisor);
    BigInt quot, rem;
    if (n < d)
    {
        return "0";
    }
    else if (n == d)
    {
        return "1";        
    }
    BigInt one = BigInt("1");
    BigInt ten = BigInt("10");    
    BigInt q = BigInt(ten);
    while (q * d < n) q = q * ten;
    string numStr = q.str();
    numStr = numStr.substr(0,numStr.length()-1);
    q = BigInt(numStr);
    while (q * d < n) q = q + one;
    q = q - one;
    return q.str();
}
