/**
 * A testbed for a binary heap implementation and the heap sort algorithm using various comparators
 * @since 02-12-2019
 * @see Date, HeapAPI, Hea.cppp
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "Heap.h"
#include "Heap.cpp"
#include "Date.h"

using namespace std;

int main(int argc, char** argv) 
{
  //  //implement this function
  /********** This is the Test case mentioned in Email **************
   //vector<int> tree = [9, 7, 8, 9, 4, 5, 7, 9, 2, 12];
   Heap<int> h;   // This is for max-heap
   //Heap<int> h([](int a, int b) -> bool {return (a > b? true : false);}); // This is for Min-heap
   printf("the size of heap is %d\n",h.size());
   h.insert(9);
   h.insert(7);
   h.insert(8);
   h.insert(9);
   h.insert(4);
   h.insert(5);
   h.insert(7);
   h.insert(9);
   h.insert(2);
   h.insert(12);
   printf("the size of heap is %d\n",h.size());
   while(h.isEmpty()==0){
       printf("remove and return %d\n", h.remove());
   }
   printf("the size of heap is %d\n", h.size());
   return 0;
  */
   Heap<Date> Des_Heap;   // Max heap, descending order
   Heap<Date> Asc_Heap([](Date a, Date b) -> bool {return (a > b? true : false);}); // Min heap,ascending order
   Heap<Date> Asc_Heap_2019([](Date a, Date b) -> bool {return (a > b? true : false);}); // Min heap, ascending order
   char Dash;
   int year,month,day;

   std::ifstream infile;
   infile.open("BundesHolidays.txt");
   if(!infile.fail()){
        while(true)
        {
	   infile>> month >> Dash >> day >> Dash >> year;  
	   if (Dash != '/')
           {
	         cout << "Wrong format" << endl;
           }
           if (infile.eof()) break;
           Date date(month, day, year);  // Here is the date read from the file
	   Des_Heap.insert(date);
	   Asc_Heap.insert(date);

	   year=2019;
           Date date_2019(month,day,year); //Here is the date in 2019
	   Asc_Heap_2019.insert(date_2019);
       }
   }   
   else
	   //cout << "before print" <<endl;
      {
       cerr<< "Error opening" <<endl;
       exit(1); 
       }
   infile.close();

   //cout << "-------------------------------------------------------" << endl;
   cout << "      Listing 1: Dates in +year+month+day Order" << endl;
   cout << "-------------------------------------------------------" << endl;
   cout << "Dates from <BundesHolidays.txt> in Ascending Order: " << endl;
   cout << "<Day of the week>, <Month name>  <day>,  <year> " << endl;
   while(Asc_Heap.isEmpty()==0)
   {
	   Date date = Asc_Heap.remove();
             cout << std::internal
		  << std::setw(15)
		  << date.getDayOfWeek()
		  << "  , "
		  << std::internal
		  << std::setw(12)
		  << date.getMonthName()
		  << std::internal
		  << std::setw(6)
		  << date.getDay()
		  << " ,  "
		  << std::internal
		  << std::setw(6)
		  << date.getYear()
		  << endl;
   }
   cout << "-------------------------------------------------------" << endl;

   cout << "      Listing 2: Dates in -year-month-day Order" << endl;
   cout << "-------------------------------------------------------" << endl;
   cout << "Dates from <BundesHolidays.txt> in Descending Order: " << endl;
   cout << "<Day of the week>, <Month name>  <day>,  <year> " << endl;
   while(Des_Heap.isEmpty()==0)
   {
	   Date date = Des_Heap.remove();
             cout << std::internal
		  << std::setw(15)
		  << date.getDayOfWeek()
		  << "  , "
		  << std::internal
		  << std::setw(12)
		  << date.getMonthName()
		  << std::internal
		  << std::setw(6)
		  << date.getDay()
		  << " ,  "
		  << std::internal
		  << std::setw(6)
		  << date.getYear()
		  << endl;
   }
   cout << "--------------------------------------------------------" << endl;

   cout << "         Listing 3: Dates in +month+day Order" << endl;
   cout << "----------------------------------------------------------------" << endl;
   cout << "Dates from <BundesHolidays.txt> in Ascending Order and Weekday" << endl;
   cout << "  in this Year: " << endl;
   cout << "<Day of the week>, <Month name>  <day> " << endl;
   while(Asc_Heap_2019.isEmpty()==0)
   {
	   Date date = Asc_Heap_2019.remove();
             cout << std::internal
		  << std::setw(15)
		  << date.getDayOfWeek()
		  << "  , "
		  << std::internal
		  << std::setw(12)
		  << date.getMonthName()
		  << std::internal
		  << std::setw(6)
		  << date.getDay()
		  << endl;
   }
   cout << "----------------------------------------------------------------" << endl;

   return 0;
}


