#include "NumberWithUnits.hpp"
namespace ariel{

  unordered_map<string,unordered_map<string,double>> read_map;
   NumberWithUnits::NumberWithUnits(double num,string const & str){
    check_inside(str);
    this->num=num;
    this->str=str;
  }
  // check if the str exsist in the map
  void NumberWithUnits::check_inside(string const & str){
    if(read_map.find(str)== read_map.end()) {
      string send = str+string(" do not exsist");
        __throw_invalid_argument(send.c_str());
    }
  }
 // convert the left number to right number
  double NumberWithUnits::convert_NU(NumberWithUnits const & left, NumberWithUnits const & right ){
    if((left.str==right.str) && read_map.find(left.str)!= read_map.end()) {
      return right.num;
    }
    if(read_map.find(left.str)!= read_map.end() &&
    read_map[left.str].find(right.str)!=read_map[left.str].end()){
      // std::cout <<right.num <<" "<< read_map[left.str][right.str]<< '\n';
      return right.num * read_map[right.str][left.str];
    }
    string send = string("Units do not match - [") +right.str+ string("] cannot be converted to [") +left.str+ string("]");
    __throw_invalid_argument(send.c_str());
    return -1;
  }

   void NumberWithUnits::read_units(ifstream& units_file){
     //1 km = 1000 m
     string str1;
     string str2;
     string t;
     double num1=0;
     double num2=0;
     while (units_file>>num1 >> str1 >> t >> num2 >>str2) {
       read_map[str1][str2]=num2;
       read_map[str2][str1]=num1/num2;
       // std::cout << str1<<","<<str2<<"="<<" "<<num2 << '\n';
       // std::cout << str2<<","<<str1<<"="<<" "<<num1/num2 << '\n';

       for (auto& x: read_map[str1]){
         double weight = read_map[str2][str1] * x.second;
         read_map[str2][x.first]=weight;
         read_map[x.first][str2]=1/weight;
       }

      for (auto& x: read_map[str2]){
        double weight = read_map[str1][str2] * x.second;
        read_map[str1][x.first]=weight;
        read_map[x.first][str1]=1/weight;
     }
   }
 }
  // + - += -= (+) (-)
    NumberWithUnits  NumberWithUnits::operator+( NumberWithUnits const & right ){
     return NumberWithUnits(this->num+NumberWithUnits::convert_NU(*this,right),this->str);
   }

   NumberWithUnits NumberWithUnits::operator+( ) const{
     return NumberWithUnits(this->num,this->str);
   }

   NumberWithUnits  NumberWithUnits::operator-( NumberWithUnits const & right ){
     return NumberWithUnits(this->num-NumberWithUnits::convert_NU(*this,right),this->str);
   }

   NumberWithUnits NumberWithUnits::operator-( ) const{
      return NumberWithUnits(-1*this->num,this->str);
   }

    NumberWithUnits & NumberWithUnits::operator+=( NumberWithUnits const & right ){
     this->num+=NumberWithUnits::convert_NU(*this,right);
     return *this;
   }
    NumberWithUnits & NumberWithUnits::operator-=( NumberWithUnits const & right ){
      this->num-=NumberWithUnits::convert_NU(*this,right);
      return *this;
   }

  // > >= < <= == !=
   bool operator==( NumberWithUnits const & left, NumberWithUnits const & right ){
     double weight= NumberWithUnits::convert_NU(left,right);

     const double apsilon = 0.0001;
     if(abs(left.num - weight)<apsilon){
       return true; return false;
     }
     return false;
   }
   bool operator!=( NumberWithUnits const & left, NumberWithUnits const & right ){
     double weight= NumberWithUnits::convert_NU(left,right);
     if(left.num != weight){
       return true; return false;
     }
     return false;
   }
   bool operator<( NumberWithUnits const & left, NumberWithUnits const & right ){
     double weight= NumberWithUnits::convert_NU(left,right);
     if(left.num < weight){
       return true; return false;
     }
     return false;
   }
   bool operator<=( NumberWithUnits const & left, NumberWithUnits const & right ){
     return left<right || left==right;
   }
   bool operator>( NumberWithUnits const & left, NumberWithUnits const & right ){
     double weight= NumberWithUnits::convert_NU(left,right);
     if(left.num > weight){
       return true; return false;
     }
     return false;
   }
   bool operator>=( NumberWithUnits const & left, NumberWithUnits const & right ){
     return left>right || left==right;
   }

  // ++ --
  // prefix ++T
   NumberWithUnits & operator++( NumberWithUnits & value ){
     value.num++;
     return value;
   }
  //postfix T++
   NumberWithUnits operator++( NumberWithUnits & value, int ){
     return NumberWithUnits(value.num++,value.str);
   }
  // prefix --T
   NumberWithUnits & operator--( NumberWithUnits & value ){
     value.num--;
     return value;
   }
  //postfix T--
   NumberWithUnits operator--( NumberWithUnits & value, int ){
    return NumberWithUnits(value.num--,value.str);
   }

  // *
   NumberWithUnits operator*( NumberWithUnits const & left, double const right ){
     return NumberWithUnits(right*left.num,left.str);
   }
   NumberWithUnits operator*( double const left, NumberWithUnits const & right){
     return NumberWithUnits(left*right.num,right.str);
   }

  // << >>
   ostream& operator<<(ostream& os, NumberWithUnits const & value){
     return os<<value.num<<"["<<value.str<<"]";
     //2.3[km]
   }
   istream& operator>>(istream& in, NumberWithUnits& value ){
     string temp;
     getline(in, temp, ']');
     //-700.5555          [        rg_kg    ]"
     string num;
     string str;
     bool flag=false;

     for(char& ch : temp){
       if(ch=='['){
         flag = true;
       }
       if(!flag  && ((isdigit(ch)!=0) || ch=='-' || ch=='.')){
         num+=ch;
       }
       if(flag && ((isalpha(ch)!=0)|| ch=='_')){
         str+=ch;
       }
     }
     NumberWithUnits::check_inside(str);

    value = NumberWithUnits(atof(num.c_str()), str);
    return in;
   }
}
