/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;



int main() {
  //name file units
  cout << "Write name of file" << endl;
  string file;
  cin>> file;

  //print list units
  ifstream units_file{file};
  cout<< endl;
  cout << "List Units: " << endl;
  if (units_file.is_open())
          cout << units_file.rdbuf();

  //set list units
  ifstream f{file};
  NumberWithUnits::read_units(f);

  //input 2 NumberWithUnits
  NumberWithUnits a{0, "km"};
  NumberWithUnits b{0, "km"};
  cout<< endl;
  cout << "Input 2 NumberWithUnits example: 1 [km]" << endl;
  cin>>a;
  cin>>b;

  //ALL OPERATOR + (+) - (-) = += < > .........

  string o;
  while (o!="finish") {
    cout<< endl;
    cout << "Input operator example: + = * < > ..... " << endl;
    cout << "write finish to finish" << endl;
    cin>>o;
    
    if(o=="="){
      if(a==b){
        cout <<"answer:" << "true" << endl;
      }
      else{
      cout <<"answer:"<<"false" << endl;
      }
    }


    if(o=="+"){
      cout <<"answer:"<< (a+b) << endl;
    }


    if(o=="(+)"){
     cout << "choose a or b" << endl;
      string temp;
      cin >> temp;
      if(temp == "a")
     cout <<"answer:"<< (+a) << endl;
     else{
       cout <<"answer:"<< (+b) << endl;
     }
    }


    if(o=="-"){
      cout <<"answer:"<< (a-b) << endl;
    }


    if(o=="(-)"){
     cout << "choose a or b" << endl;
     string temp;
     cin >> temp;
      if(temp == "a")
     cout <<"answer:"<< (-a) << endl;
     else{
       cout <<"answer:"<< (-b) << endl;
     }
      

    
    }
    if(o=="<"){
      cout << boolalpha;
      cout <<"answer:"<< (a<b) << endl;
    }
  

    if(o==">"){
      cout << boolalpha;
      cout <<"answer:"<< (a>b) << endl;
    }


    if(o=="<="){
      cout << boolalpha;
      cout <<"answer:"<< (a<=b) << endl;
    }


    if(o==">="){
      cout << boolalpha;
      cout <<"answer:"<< (a>=b) << endl;
    }


   if(o=="*"){
      cout << "choose a or b: "<< endl;
      string str;
      cin >> str;
      cout<< endl;
      cout << "choose some number: "<< endl;
      double num;
      cin >> num;
      if(str == "a"){
        cout <<"answer:"<< (a*num) << endl;
      }
      else{
        cout <<"answer:"<< (b*num) << endl;
      }


    
    }





  }


  return 0;
}
