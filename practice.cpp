#include "lab.hpp"


int main() {  
    setlocale(LC_ALL, "Ru");
    while (true) {
       outputMenu();
       Processing[inputNumber()-1]();
    }
  
}

/*

Moscow    12000000  Russia    899       42
Piter     10000000  Russia    1200      15
Ufa       20000000  Russia    900       9
Vor       10000000  Russia    400       8
Tor       90000000  Russia    700       7

*/
