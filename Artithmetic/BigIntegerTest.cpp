/*
-Antonio Hernadez Ruiz
-ahern336
-BigIntegerTest.cpp
-Tests the implementation of the fucntions for the BigInteger ADT
*/
//headers
#include <string>
#include "BigInteger.h"

using namespace std;

//the main part of the file
int main(void){
    //making different big integers in order to test them
    BigInteger test1 = BigInteger("-1223333");
    BigInteger test2 = BigInteger("1233434");

    //testing to see if the copy works
    BigInteger test3 = test1;

    //now testing the assignment operators
    //testing the addition
    test3 += test2;
    cout<<test3<<endl;

    //testing the subtrraction
    test2 -= test1;
    cout<<test2<<endl;

    //testing the multiplication
    test3 *= test2;
    cout<<test3<<endl;

    //now testing some of the other fucntions
    cout<<"sign of test1: "<<test1.sign()<<endl;
    //testing compare
    cout<<test1.compare(test2)<<endl;
    //printing out 
    cout<<"start: "<<test1<<endl;

    test1.makeZero();
    test2.negate();

    //making a bool variable to test the other operators
    bool i;
    i = (test1 == test2);
    cout<<"equal: "<<i<<endl;
    
    //testing less than 
    i = (test1<test2);
    cout<<"less than: "<< i << endl;

    //testing greater than 
    i = (test1 > test2);
    cout << "greater than: "<< i << endl;

    //testing greater or equal than
    i = (test1 >= test2);
    cout<< "greater or eq: "<< i << endl;

    // testing less or equal than
    i = (test1 <= test2);
    cout << "less than or eq: "<< i <<endl;

    return 0;
}