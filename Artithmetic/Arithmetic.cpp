/*
-Antonio Hernandez Ruiz
-ahern336
-Arithmetic.cpp
-this file makes use of the biginteger adt and prints out operations
*/

//headers
#include <string>
#include <fstream>
#include <iostream>
#include "BigInteger.h"
//using the namespace
using namespace std;

//main part of the file
int main(int argc, char* argv[]){
    //making sure the correct amount of arguements are called
    if(argc!=3){
        cerr<<"using: "<<argv[0]<< "<input file> <output file>"<<endl;
        return(EXIT_FAILURE);
    }
    //getting the in and the out files
    ifstream IN;
    ofstream OUT;

    //opening and trying to read/write to files
    IN.open(argv[1]);
    OUT.open(argv[2]);

    //checking to see if the files are opened correctly 
    if(!IN.is_open()){
        cerr<<"not able to open file"<<argv[1]<<"for reading"<<endl;
        return(EXIT_FAILURE);
    }  
    //checking both
    if(!OUT.is_open()){
        cerr<<"not able to open file"<<argv[2]<<"for writing"<<endl;
        return(EXIT_FAILURE);
    }
    //make strings to read in 
    string strA;
    string strB;

    //reading in 
    IN >> strA;
    IN >> strB;

    //making the bigint parts
    BigInteger A = BigInteger(strA);
    BigInteger B = BigInteger(strB);
    //making the number parts
    BigInteger dos = BigInteger("2");
    BigInteger tres = BigInteger("3");
    BigInteger nueve = BigInteger("9");
    BigInteger dseis = BigInteger("16");

    //printing out the arithmatic in the out file
    //printing out A
    OUT << A << endl << endl;
    //printing out B
    OUT<< B << endl << endl;
    // A + B
    OUT << A+B << endl << endl;
    // A - B
    OUT << A-B << endl << endl;
    // A - A
    OUT << A-A << endl << endl;
    // 3A - 2B
    OUT << tres * A - dos*B <<endl << endl;
    // A*B
    OUT<< A*B << endl << endl;
    // A*A
    OUT<< A*A << endl <<endl;
    // B*B
    OUT << B*B << endl << endl;
    // 9A^4 + 16B^5
    OUT << nueve * A * A * A * A + dseis * B * B * B * B * B << endl << endl;

    //close the files
    IN.close();
    OUT.close();

    //return zero to know it finishes
    return 0;
}

