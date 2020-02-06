/**
 * Describes a city with a given name and unique integer identifier
 * @since 99-99-9999
 */

#ifndef CITY_H
#define	CITY_H
#include <string>
#include <iostream>

using namespace std;

class City
{
public:
    /**
     * Creates a default city
     */
   City()
   {
      label = " ";
      key = 0;
   }

   /**
    * Creates a city with the specified key (zip code) and label (name)
    * @param aKey key of the city
    * @param aLabel label of the city
    */
   City(int aKey, string aLabel)
   {
      label = aLabel;
      key = aKey;
   }

   /**
    * Creates an anonymous city with the specified key (zip code)
    * @param aKey the key of the city
    */
   City(int aKey)
   {
      label = " ";
      key = aKey;
   }

   /**
    * Gives the label for this city
    * @return the label for this city
    */
   string getLabel() const
   {
      return label;
   }

   /**
    * Gives the key for this city
    * @return the key for this city
    */
   int getKey() const
   {
      return key;
   }
   /**
    * Determines whether the specified cities are identical
    * @param c1 a city
    * @param c2 a city
    * @return true if the specified cities are identical;
    * false, otherwise
    */
   friend bool operator==(const City& c1, const City& c2); 
   /**
    * Determines whether the specified cities are different
    * @param c1 a city
    * @param c2 a city
    * @return true if the specified cities are different;
    * false, otherwise
    */   
   friend bool operator!=(const City& c1, const City& c2); 
   /**
    * Determines whether the key of the first city is greater than
    * the key of the second city.
    * @param c1 a city
    * @param c2 a city
    * @return true if the key of the first city is greater than the key
    * of the second city; false, otherwise
    */      
   friend bool operator>(const City& c1, const City& c2); 
   /**
    * Determines whether the key of the first city is less than
    * the key of the second city.
    * @param c1 a city
    * @param c2 a city
    * @return true if the key of the first city is less than the key
    * of the second city; false, otherwise
    */         
   friend bool operator<(const City& c1, const City& c2); 
   /**
    * Determines whether the key of the first city is greater than
    * or the same as the key of the second city.
    * @param c1 a city
    * @param c2 a city
    * @return true if the key of the first city is greater than or the same
    * as the key of the second city; false, otherwise
    */         
   friend bool operator>=(const City& c1, const City& c2); 
   /**
    * Determines whether the key of the first city is less than
    * or the same as the key of the second city.
    * @param c1 a city
    * @param c2 a city
    * @return true if the key of the first city is less than or the same
    * as the key of the second city; false, otherwise
    */       
   friend bool operator<=(const City& c1, const City& c2); 
private:
    /**
     * The label (name) of this city
     */
   string label;
   /**
    * The key (zip code) of this city    
    */
   int key;
};

bool operator==(const City& c1, const City& c2)
{
   return (c1.key == c2.key);
}

bool operator!=(const City& c1, const City& c2)
{
   return (c1.key != c2.key);
}

bool operator>(const City& c1, const City& c2)
{
   return (c1.key > c2.key);
}

bool operator<(const City& c1, const City& c2)
{
   return (c1.key < c2.key);
}

bool operator>=(const City& c1, const City& c2)
{
   return (c1.key >= c2.key);
}

bool operator<=(const City& c1, const City& c2)
{
   return (c1.key <= c2.key);
}
#endif	/* CITY_H */

