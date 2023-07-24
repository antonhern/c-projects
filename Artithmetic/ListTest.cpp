/*
-Antonio Heranandez Ruiz
-ahern336
-this file tests the functions for the list adt
*/
//headers
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
//using std names
using namespace std;

int main(){
    //variables for later
    int i;
    int x = 10;
    List A;
    List B;


    //first testing inserting before and after
    for(i=1;i<=x;i++){
        A.insertAfter(i);
        B.insertBefore(i);
    }

    //printing things out for this
    // first testing position
    cout<<endl;
    cout<< "A= " << A <<endl;
    cout<<"A.position()= "<<A.position()<<endl;
    cout<< "B= "<< B <<endl;
    cout<< "B.position()= "<<B.position()<<endl;


    // testing the cursor 
    A.moveFront();
    cout<<"A.position()= "<<A.position()<<endl;


    //testing to see if the move next and move prev work
    int get = A.moveNext();
    cout<< get<<endl;
    cout<<"A.position()= "<<A.position()<<endl;


    //now starting at the back
    A.moveBack();
    int get2 = A.movePrev();
    cout<<get2<<endl;
    cout<<"A.position()= "<<A.position()<<endl;


    // testing the other access functions
    cout<<"B.length= "<<B.length()<<endl;
    cout<<"B.front()= "<<B.length()<<endl;
    cout<<"B.back()= "<<B.back()<<endl;


    //testing cleanup function
    A.cleanup();
    cout<<"A= "<<A<<endl;


    //testing the peek functions on B
    cout<<"Peek prev = "<<B.peekPrev()<<endl;
    cout<<"Peek next = "<<B.peekNext()<<endl;

    //testing the peek functions on A
    cout<<"Peek prev = "<<A.peekPrev()<<endl;
    cout<<"Peek next = "<<B.peekNext()<<endl;

    //testing set on A
    A.setAfter(13);
    A.setBefore(60);
    cout<<"A = "<<A<<endl;

    //testing set on B
    B.setAfter(33);
    B.setBefore(88);
    cout<<"B = "<<B<<endl;

    //testing find next and prev on A
    A.moveFront();
    cout<<"A.findNext() = "<<A.findNext(5)<<endl;
    A.moveBack();
    cout<<"A.findPrev() = "<<A.findPrev(5)<<endl;

    
    //testing find next and prev on B
    B.moveFront();
    cout<<"B.findNext() = "<<B.findNext(5)<<endl;
    B.moveBack();
    cout<<"B.findPrev() = "<<B.findPrev(5)<<endl;

    //making another list to test concatanate
    List C = B.concat(A);
    cout<<"C = B concat A "<<C<<endl;

    //testing to see if equals workds
    if(C == B){
        cout<<"equals is wrong"<<endl;
    }else{
        cout<<"equals works"<<endl;
    }
    cout<<endl;
    //clear all the lists
    A.clear();
    B.clear();
    C.clear();
}
