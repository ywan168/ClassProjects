/**
 *
 * @author Duncan <br>
 * file: Date.java<br>
 * Purpose: models a Gregorian Date<br>
 * Date: October 13, 2013<br>
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <exception>


using namespace std;

#ifndef DATE_H
#define	DATE_H


class Date
{
private:
   /**
    * the month 
    */
   int month;
   /**
    * the day
    */
   int day;
   /**
    * the year
    */
   int year;
   
public:
   /**
    * creates an object representing January 1, 1970
    */
   Date();
   /**
    * creates a valid Gregorian Date
    * @param mm the month
    * @param dd the day
    * @param yyyy the year
    * @throws invalid_argument exception when <br>
    * <pre>
    * 1. year is before 1583
    * 2. month not in the range 1-12
    * 3. day not in the range 1-31
    * 4. month is September, April, June or November and day is 31
    * 5. month is February, the year is a leap year and day is greater
    *    than 29
    * 6. month is February, the year is not a leap year and the day is
    *    greater than 28
    * </pre>
    */
   Date(int mm, int dd, int yyyy) throw (invalid_argument);

   /**
    * returns the name of the current month
    * @return the name of the current month
    */
   string getMonthName() const;
   
   /**
    * gives an integer representing the month
    * @return a number representing the month of this date
    */
   int getMonth() const;

   
   /**
    * gives an integer representing the day
    * @return the day of this date 
    */
   int getDay() const;
   
   /**
    * gives an integer representing the year
    * @return the year of this date
    */
   int getYear() const;
   
   /**
    * determines the name of the day of the week of this date
    * @return the name of the day of the week of this date
    */
   string getDayOfWeek() const;
   
   /**
    * gives the date in the format mm/dd/yyyy
    * @return a string representation of this date in the format mm/dd/yyyy
    */
    string str() const;
    
  /**
    * Determines whether two dates are equal.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the specified dates are equal; otherwise, false.
   */
   friend bool operator==(const Date& d1, const Date& d2);
   
  /**
    * Determines whether two dates are not equal.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the specified dates are not equal; otherwise, false.
   */
   friend bool operator!=(const Date& d1, const Date& d2);
   
  /**
    * Determines whether the first date comes after the second date.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the first date comes after the second; otherwise, false.
   */
   friend bool operator>(const Date& d1, const Date& d2);
   
  /**
    * Determines whether the first date comes before the second date.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the first date comes before the second; otherwise, false.
   */
   friend bool operator<(const Date& d1, const Date& d2);
   
  /**
    * Determines whether the first date is the same as or comes after the second date.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the first date is the same as or comes after the second; otherwise, false.
   */
   friend bool operator>=(const Date& d1, const Date& d2);
   
  /**
    * Determines whether the first date is the same as or comes before the second date.
   *  @param d1 a date
   * @param d2 a date
   * @return true when the first date is the same as or comes before the second; otherwise, false.
   */
   friend bool operator<=(const Date& d1, const Date& d2);
};
#endif	/* DATE_H */

