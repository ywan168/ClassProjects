#include "Date.h"

Date::Date()
{
    month = 1; 
    day = 1;
    year = 1970;
}

Date::Date(int mm, int dd, int yyyy) throw (invalid_argument)
{
    bool leap = (yyyy % 400 == 0)||(yyyy % 4 == 0 && yyyy % 100 != 0);
    if (yyyy < 1583)
        throw invalid_argument("Date(int,int,int): only dates after 1582 are allowed.");
    if (mm < 0 || mm > 12)
        throw invalid_argument("Date(int,int,int): month must be between 1 and 12.");
    if (dd < 0 || dd > 31)
        throw invalid_argument("Date(int,int,int): day must be between 1 and 31.");    
    if ((mm==9 || mm==4 || mm==6 || mm==11) && dd == 31)
        throw invalid_argument("Date(int,int,int): this month has only 30 days.");
    if (mm==2)
    {
        if (leap)
        {
            if (dd >29)
                throw invalid_argument("Date(int,int,int): February has only 29 days in a leap year.");
        }
        else
        {
            if (dd >28)
                throw invalid_argument("Date(int,int,int): February has only 29 days in a leap year.");
        }
    }   
    year = yyyy;
    month = mm;
    day = dd;    
}

string Date::getMonthName() const
{
    string  names[] = {"January", "February", "March", "April",
                        "May", "June", "July", "August",
                        "September", "October", "November", "Decenber"};  
    return names[month-1];
}
   
int Date::getMonth() const
{
    return month;
}

   
int Date::getDay() const
{
    return day;
}
   
int Date::getYear() const
{
    return year;
}
   
string Date::getDayOfWeek() const
{
    int m;
    bool leap = (year % 400 == 0)||(year % 4 == 0 && year % 100 != 0);
    if (month == 1)
    {
        if (leap)
            m = 5;
        else
            m = 0;
    }
    else if (month == 2)
    {
        if (leap)
            m = 2;
        else
            m = 3;
    }
    else if (month == 10)
        m = 0;
    else if (month == 5)
        m = 1;
    else if (month == 8)
        m = 2;
    else if (month == 3 || month == 11)
        m = 3;
    else if (month == 6)
        m = 4;
    else if (month == 9 || month == 12)
        m = 5;
    else
        m = 6;
    int v = year % 100;
    string weekDay[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return weekDay[(2*(3 - (year / 100 % 4)) + v + v/4 + m + day) % 7];    
}
   
string Date::str() const
{
    string dStr="";
    if (month < 10)
        dStr = "0";
    dStr += to_string(month);
    dStr += "/";
    if (day < 10)
        dStr += "0";
    dStr += to_string(day);
    dStr += "/" + to_string(year);
    return dStr;
}
    
bool operator==(const Date& d1, const Date& d2)
{ 
   return d1.month == d2.month && d1.day == d2.day && d1.year == d2.year;
}   

bool operator!=(const Date& d1, const Date& d2)
{   
   return !(d1 == d2);
}   

bool operator>(const Date& d1, const Date& d2)
{   
   if (d1.year > d2.year)
      return true;
   else if (d1.year < d2.year)
       return false;
   else if (d1.month > d2.month)
       return true;
   else if (d1.month < d2.month)
       return false;
   else if (d1.day > d2.day)
       return true;
   else
       return false;
}   

bool operator<(const Date& d1, const Date& d2)
{   
   return (d1 != d2) && !(d1 > d2);
}   

bool operator<=(const Date& d1, const Date& d2)
{   
   return (d1 > d2) || (d1 == d2);
}   

bool operator>=(const Date& d1, const Date& d2)
{   
   return (d1 > d2) || (d1 == d2);
}   
