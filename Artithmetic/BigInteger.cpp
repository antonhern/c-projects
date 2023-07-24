/*
-Antonio Hernandez Ruiz
-ahern336
-BigInteger.cpp
-This file implements the functions for the BigInteger ADT
*/
//headers
#include "BigInteger.h"
#include "List.h"
#include <stdexcept>
#include <ctype.h>
#include <iostream>
#include <fstream>

//making the base and the power
long base = 1000000000;
int power = 9;
//declaring helper functions here
void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    //variables for later
    int i;
    bool flag = false;
    //turning the long variable into a string
    std::string s = std::to_string(x);
    //now checking the lenght
    if(s.length() == 0){
        throw std::length_error("BigInteger: trying to create a long of lenght zero");
    }
        //first checking to see if it is a plus
    if(s[0] == '+'){
        //if it is signum is 1 and subtract form the length
        signum  = 1;
        s = s.substr(1,s.length());
    }
    //checking for other signs
    else if(s[0] == '-'){
        signum = -1;
        s = s.substr(1,s.length());
    //else signum is 1
    }else{
        signum = 1;
    }
    //checking for non digit entries in the string
    for(char const &c: s){
        if(!isdigit(c)){
            throw std::invalid_argument("non number entry");
        }
    }
    //looping through the string to check for zeros and negatives
    for(i = s.length()-power;;i-=power){
        if(i < 0){
            //if the character is less than zero the postiion is zero but
            // the legth is i+power
            digits.insertAfter(std::stol(s.substr(0,i+power)));
            flag = true;
        //if the character is a zero then you just have position i and length power
        }else if(i == 0){
            digits.insertAfter(std::stol(s.substr(i,power)));
            flag = true;
        }else{
           digits.insertAfter(std::stol(s.substr(i,power))); 
        }
        //break out of the loop if the flag is true
        if(flag){
            break;
        }
    }
    //now to account for the zero values before the first loop executes
    digits.moveFront();
    //looping through 
    while(digits.position()<digits.length() && digits.peekNext() == 0){
        //erasing and moving foward
        digits.eraseAfter();
        digits.moveNext();
    }
    //if the lenght of the digits list is zero just
    // make the signum zero
    if(digits.length() == 0){
        signum = 0;
    }


}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    //variable for later
    bool flag = false;
    int i;
    //first checking to see that the lenght of the string is correct
    if(s.length() == 0){
        throw std::length_error("BigInteger: trying to create a string of length zero");
    }
    //first checking to see if it is a plus
    else if(s[0] == '+'){
        //if it is signum is 1 and subtract form the length
        signum  = 1;
        s = s.substr(1,s.length());
    }
    //checking for other signs
    else if(s[0] == '-'){
        signum = -1;
        s = s.substr(1,s.length());
    //else signum is 1
    }else{
        signum = 1;
    }
    //checking for non digit entries in the string
    for(char const &c: s){
        if(!isdigit(c)){
            throw std::invalid_argument("non number entry");
        }
    }
    //looping through the string to check for zeros and negatives
    for(i = s.length()-power;;i-=power){
        if(i < 0){
            //if the character is less than zero the postiion is zero but
            // the legth is i+power
            digits.insertAfter(std::stol(s.substr(0,i+power)));
            flag = true;
        //if the character is a zero then you just have position i and length power
        }else if(i == 0){
            digits.insertAfter(std::stol(s.substr(i,power)));
            flag = true;
        }else{
           digits.insertAfter(std::stol(s.substr(i,power))); 
        }
        //break out of the loop if the flag is true
        if(flag){
            break;
        }
    }
    //now to account for the zero values before the first loop executes
    digits.moveFront();
    //looping through 
    while(digits.position()<digits.length() && digits.peekNext() == 0){
        //erasing and moving foward
        digits.eraseAfter();
        digits.moveNext();
    }
    //if the lenght of the digits list is zero just
    // make the signum zero
    if(digits.length() == 0){
        signum = 0;
    }


}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    //taking the things from "this" and putting them into N
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return this->signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    //making variables for later
    int i;
    long num1;
    long num2;
    //pointer to this
    BigInteger temp = *this;
    BigInteger temp2 = N;
    //start at the begining
    temp.digits.moveFront();
    temp2.digits.moveFront();
    //using simple if statements to compare
    // the signs of both this and N
    //checking if both are zero or equal 
    if(temp.sign() ==0 && temp2.sign() ==0){
        return 0;
    }
    //checking to see if temp is greater than n
    if(temp.sign() >=0 && temp2.sign() == -1){
        return 1;   
    }
    //checking to see if temp is less than n
    if(temp.sign() == -1 && temp2.sign() >=0){
        return -1;
    //now checking to see their length and compare like that
    }else{
        //if the lengh of this is less than n and the sign is 1 return -1
        if(temp.digits.length() < temp2.digits.length() && temp.sign() == 1){
            return -1;
        }
        //if teh length of this greater than n and the sign is -1 return -1
        if(temp.digits.length() > temp2.digits.length() && temp.sign() == -1){
            return -1;
        }
        //if the lenght of this is greater than n and the sign is 1 return 1
        if(temp.digits.length() > temp2.digits.length() && temp.sign() == 1){
            return 1;
        }
        //if the lenght of this is less than n and the sign is -1 return 1
        if(temp.digits.length() < temp2.digits.length() && temp.sign() == -1){
            return 1;
        }else{
            //comparing the individual digits inside of the lists
            //iterating through the list of digits
            for(i = 0;i<temp.digits.length();i++){
                //holding all the digits inside of the this digits list a variable
                num1 = temp.digits.moveNext();
                //holding all the digits inside of the N digits list in a variable
                num2 = temp2.digits.moveNext();
                //comparing the digits
                // and returning the appropiate value
                if(num1 > num2 && temp.sign() == 1){
                    return 1;
                }
                if(num1 < num2 && temp.sign() == -1){
                    return 1;
                }
                if(num1 > num2 && temp.sign() == -1){
                    return -1;
                }
                if(num1 < num2 && temp.sign() == 1){
                    return -1;
                }
            }
        }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    //checking to see if signum is not zero
    //if it is not just times it * -1
    if(signum != 0){
        signum *= -1;
    }
}
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    //starting at the front of the list
    L.moveFront();
    //iterating through the list
    while (L.position()<L.length())
    {
        //multiplying everything by -1
        L.setAfter(-1*L.peekNext());
        L.moveNext();
    }
    
}
// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    //first clearing the list S
    S.clear();
    //starting at the beginning of the list B
    B.moveFront();
    //iterating through and multiplying everything in 
    // B by sgn
    while(B.position()<B.length()){
        B.setAfter(sgn*B.peekNext());
        B.moveNext();
    }
    //starting at the back of both lists now
    A.moveBack();
    B.moveBack();
    //if the position of both is greater than zero 
    // add both and inert then into S
    while(A.position()>0&&B.position()>0){
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }
    //now making a loop to add A to list S
    while(A.position()>0){
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    //now making a loop to add B to list S
    while(B.position()>0){
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }
    //now iterating through the list S to check for a zero upfront
    while(S.front() == 0 && S.length()>1){
        S.eraseAfter();
    }

}
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    //variables for later
    int i = 1;
    int j;
    ListElement k;
    //first checking to see if the front of the list is zero
    if(L.front() == 0){
        //if it is return 0
        return 0;
    }
    //checking to see if the front of the list is negative
    if(L.front()<0){
        //negate the list so it becomes positive
        negateList(L);
        //change the value of the sign
        i = -1;
    }
    //starting at the back of the list
    L.moveBack();
    j = 0;
    k = 0;
    //iterating through the L list
    while(L.position()>0){
        //holding a value of the list here
        k = L.peekPrev();
        //now accounting for the value of that value
        if(k<0){
            //adding the base here
            k+= base+j;
            L.setBefore(k);
            j = -1;
        }else{
            //just adding a to carry over
            k+=j;
            j=0;
            //accounting for values being too big
            if(k>=base){
                j = k/base;
                k = k%base;
            }
            L.setBefore(k);
        }
        L.movePrev();
    }
    //acouting for the number carried over not being zero
    if(j!= 0){
        L.moveFront();
        L.insertAfter(j);
    }
    return i;

}
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    //variable for later
    int i;
    //starting at the back of the list
    L.moveBack();
    //iterating through the size/amount of int p
    for(i=0;i<p;i++){
        //inserting that many zeros
        L.insertAfter(0);
    }
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    //starting at the front of the list
    L.moveFront();
    //iterating through the list
    while(L.position() < L.length()){
        //setting in the multiplied value of the list value * m
        L.setAfter(L.peekNext()*m);
        L.moveNext();
    }
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    //making variables for later
    BigInteger answer;
    //making a list to hold values
    List asnwer_list;
    //making a copy of the this list
    List this_copy = this->digits;
    List N_copy = N.digits;
    //checking to see what the signs are of the lists
    // if they are equal or less than one another
    if (this->signum == 1 && N.signum == 1) {
        //adding them into the empty list of answers
        sumList(asnwer_list, this_copy, N_copy, 1);
        //modifying the sign of them and putting the answers in
        answer.signum = normalizeList(asnwer_list);
        answer.digits = asnwer_list;
    }
    else if (this->signum == -1 && N.signum== -1) {
        negateList(this_copy);
        negateList(N_copy);
        //then add them 
        sumList(asnwer_list,this_copy,N_copy,1);
        //modifying the holder for the values to hold the 
        // new signum and digits
        answer.signum = normalizeList(asnwer_list);
        answer.digits = asnwer_list;
        //now checking for other conditions
    }else{
        //if this is negative
        if(this->signum < 0){
            //negate it
            negateList(this_copy);
        }
        //doing the same for N
        if(N.signum < 0){
            //negate is 
            negateList(N_copy);
        }
        //then just do the same as the other options
        //adding them together
        sumList(asnwer_list,this_copy,N_copy,1);
        //then putting them into the other holder
        answer.signum = normalizeList(asnwer_list);
        answer.digits = asnwer_list;
    }
    return answer;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    //making a copy of what is in the this pointer
    BigInteger A = *this;
    //making a copy of N
    BigInteger B = N;
    //negating everything
    negateList(B.digits);
    // just add them together
    return B.add(A);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    //variables for later
    BigInteger answer;
    List answer_list;
    List this_copy;
    int i;
    //making a copy of the inserted list
    List N_copy = N.digits;
    //checking to see if the sginum is zero for either
    //return the blank answer
    if(this->signum == 0 || N.signum == 0){
        return answer;
    }  
    //inserting a zero 
    answer_list.insertAfter(0);
    N_copy.moveBack();
    i = 0;
    //iterating through the copy of the inswerted list
    while(N_copy.position() > 0){
        //holding the digits her
        this_copy = this->digits;
        //using the helper to multiply the list
        // that holds the this values and the individual values
        // of the N copy
        scalarMultList(this_copy,N_copy.peekPrev());
        //now just shiftint the list over
        shiftList(this_copy,i);
        //making a copy of the answer list
        List answer_list_copy = answer_list;
        //now adding those together with 1
        sumList(answer_list,answer_list_copy,this_copy,1);
        //now normalizing the list
        normalizeList(answer_list);
        //making it so its not an infinite loop 
        N_copy.movePrev();
        i++;
    }
    //now using the answer 
    answer.digits = answer_list;
    //checing for equal numbers in the lists
    if(this->signum == N.signum){
        answer.signum = 1;
    }else{
        answer.signum = -1;
    }
    return answer;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    //checking to see if we should return zero
    if(this->signum == 0){
        return "0";
    }
    //making a holder varible that will hold the string
    //version of what we want to return 
    std::string A = "";
    //if the signum is -1 then add the - sign
    if(this->signum == -1){
        A+="-";
    }
    //starting at the front of the digit list
    digits.moveFront();
    //iterating through the digits list in this
    //and erasing if they are too small
    while(digits.front() == 0 && digits.length() > 1){
        digits.eraseAfter();
    }
    //iterating again but this time converting into strings
    for(digits.moveFront();digits.position()<digits.length();digits.moveNext()){
        //making a string variable to hold the integers inside of the digits list
        std::string x = std::to_string(digits.peekNext());
        std::string y = "";
        //iterating through again to insert the numbers into the string variables
        while((int)(y.length()+x.length())<power && digits.position()!= 0){
            //addt the zeros to the empty string
            y+= '0';
        }
        //then just add the two srings together
        A+=(y+x);
    }
    return A;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    //checking if A is equal to B
    if(A.compare(B)==0){
        return true;
    }else{
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    //checking to see if A is less than B
    if(A.compare(B) == -1){
        return true;
    }else{
        return false;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    //checking to see if A is less than B but also equal
    if(A.compare(B) == -1 || A.compare(B) == 0){
        return true;
    }else{
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    //checking to see if A is greater than B
    if(A.compare(B) == 1){
        return true;
    }else{
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    //checking to see if A is greater than B but also equal
    if(A.compare(B) == 1 || A.compare(B) == 0){
        return true;
    }else{
        return false;
    }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

   // operator+=()
   // Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}