/* 
 * The purpose of this file is to provide The interface
 * for a naive and a fast power functions for BigInt types with
 * integer exponents
 * CSC 3102 Programming Project # 0
 * @since 01/20/2019
 * @see BigInt.h
 */

#include "BigInt.h"
#include <stdexcept>
using namespace std;



#ifndef BIGMATH_H
#define	BIGMATH_H

/**
 * This function computes the non-negative power of a positive "BigInt"
 * for a given non-negative integer exponent using repeated multiplication;
 * given a base, b, and the exponent n, the function uses n-1 multiplications
 * to compute b * b * b * ..... * b, where b is used as a factor n times.
 * @param base a positive object of the BigInt class
 * @param n a non-negative integer
 * @return the power of a big integer to the specified non-negative exponent
 * @throw invalid_argument exception when n is negative or base is not positive.
 */
BigInt naivePow(const BigInt& base, int n) throw (invalid_argument)
{ 
    if (n == 0  || base == BigInt(std::to_string(1)))
        return BigInt(std::to_string(1));
    BigInt  y = BigInt(std::to_string(1));
    BigInt  bigint_base = base;
    for (int i = 1; i <= n; ++i) {
        y = y*bigint_base;
    }
    return y;
}

/**
 * This function computes the non-negative power of a positive "BigInt"
 * using the fast power algorithm that uses successive squaring
 * @param base a positive object of the BigInt class
 * @param n a non-negative integer
 * @return the power of a big integer to the specified non-negative exponent
 * @throw invalid_argument exception when n is negative or base is not positive.
 */
BigInt fastPow(const BigInt& base, int n) throw (invalid_argument)
{
   if (n == 0  || base == BigInt(std::to_string(1)))
       return BigInt(std::to_string(1));

    BigInt y = BigInt(std::to_string(1));
    BigInt bigint_base = base;
    while (n>1){
	if (n%2==1)
        {
            y = y*bigint_base;
        } 
        n = n/2;
        bigint_base =bigint_base*bigint_base;
    } 
    return y*bigint_base;
}        
        
#endif	/* BIGMATH_H */

