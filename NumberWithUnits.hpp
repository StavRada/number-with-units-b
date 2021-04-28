#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

namespace ariel{
  class NumberWithUnits{
    private:
      double num;
      string str;
      static double convert_NU(NumberWithUnits const & left, NumberWithUnits const & right );
      static void check_inside(string const &  str);
      
    public:
      NumberWithUnits(double num,string const & str);
      static void read_units(ifstream& units_file);
      // + - += -= (+) (-)
      NumberWithUnits operator+( NumberWithUnits const & right );
      NumberWithUnits operator+( ) const;

      NumberWithUnits operator-( NumberWithUnits const & right );
      NumberWithUnits operator-( ) const;

      NumberWithUnits & operator-=( NumberWithUnits const & right );
      NumberWithUnits & operator+=( NumberWithUnits const & right );


      // > >= < <= == !=
      friend bool operator==( NumberWithUnits const & left, NumberWithUnits const & right );
      friend bool operator!=( NumberWithUnits const & left, NumberWithUnits const & right );
      friend bool operator<( NumberWithUnits const & left, NumberWithUnits const & right );
      friend bool operator<=( NumberWithUnits const & left, NumberWithUnits const & right );
      friend bool operator>( NumberWithUnits const & left, NumberWithUnits const & right );
      friend bool operator>=( NumberWithUnits const & left, NumberWithUnits const & right );

      // ++ --
      // prefix ++v
      friend NumberWithUnits & operator++( NumberWithUnits & value );
      //postfix v++
      friend NumberWithUnits operator++( NumberWithUnits & value, int );
      // prefix --v
      friend NumberWithUnits & operator--( NumberWithUnits & value );
      //postfix v--
      friend NumberWithUnits operator--( NumberWithUnits & value, int );

      // *
      friend NumberWithUnits operator*( NumberWithUnits const & left, double const right );
      friend NumberWithUnits operator*( double const left, NumberWithUnits const & right);

      // << >>
      friend ostream& operator<<(ostream & os, NumberWithUnits const & value);
      friend istream& operator>>(istream& in, NumberWithUnits& value );
    };
}
