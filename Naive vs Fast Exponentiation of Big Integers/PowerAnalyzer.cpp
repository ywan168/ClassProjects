/**
 * The purpose of this file is to fulfill the requests
 * listed in "The PowerAnalyzer Program" which was
 * written in csc3102proj00cs19.pdf.
 * CSC 3102 Programming Project # 0
 * @author Yanfang Wang
 * @since 01/23/2019
 * @see BigMath.h BigInt.h
 */

#include <iostream>
#include <chrono>
#include "BigMath.h"
#include "BigInt.h"
#include <cstdlib>
#include <iomanip>


int main(int argc, const char * argv[]) {
    
    int base;
    std::cout << "Enter the base of the power\n";
    std::cin >> base;
    
    int power;
    std::cout << "Enter the exponent of the power\n";
    std::cin >> power;
    
    BigInt bigint_base = BigInt(std::to_string(base));
    
    BigInt Nres1 = naivePow(bigint_base,power);
    BigInt Fres1 = fastPow(bigint_base,power);
    
    std::cout << "Using Naive Algorithm: " << base << "^" << power << "=" << Nres1 << "\n";
    std::cout << "Using Fast Algorithm: " << base << "^" << power << "=" << Fres1 << "\n";
    
    std::cout << "Using a random 4-digit base and a random 2-digit exponent: \n";
    srand(time(NULL));
    base = rand() % 10000;
    power = rand() % 100;
    
    bigint_base = BigInt(std::to_string(base));
    
    BigInt Nres2 = naivePow(bigint_base,power);
    BigInt Fres2 = fastPow(bigint_base,power);
    
    std::cout << "Using Naive Algorithm: " << base << "^" << power << "=" << Nres2 << "\n";
    std::cout << "Using Fast Algorithm: " << base << "^" << power << "=" << Fres2 << "\n";
    
    std::cout << "Enter the base of the power for the table \n";
    std::cin >> base;
    std::cout << "b = " << base << "\n";
    std::cout << "============================================================== \n";
    std::cout << std::left << std::setw(15) <<"n" 
	      << std::right << std::setw(20) << "   b^n: Fast Power(ns)" 
	      << std::right << std::setw(20) << "     b^n: Naive Power(ns) \n";
    std::cout << "-------------------------------------------------------------- \n";
    
    bigint_base = BigInt(std::to_string(base));
    
    int powerlist[] = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
    for (int i = 0; i < 10; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        BigInt Fres = fastPow(bigint_base,powerlist[i]);
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long duration_fast = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
         
        start = chrono::high_resolution_clock::now();
        BigInt Nres = naivePow(bigint_base,powerlist[i]);
        elapsed = chrono::high_resolution_clock::now() - start;
        long duration_naive = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

        std::cout << std::left << std::setw(15) <<powerlist[i] 
		  << std::right << std::setw(20) << duration_fast 
		  <<std::right << std::setw(20) << duration_naive 
		  << "\n";
    }
    std::cout << "============================================================== \n";

    return 1;
}
