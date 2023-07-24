/*
-Antonio Hernandez Ruiz
-ahern336
-List.cpp
-Implementation of the List ADT functions
*/

//headers
#include "List.h"
#include <stdexcept>

//making a consructor for the nodes
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}
// Class Constructors & Destructors ----------------------------------------
   
// Creates new List in the empty state.
List::List(){
    //adding placeholder values for the front and back dummy
    frontDummy = new Node(-20);
    backDummy = new Node(20);
    //placing the next and previous for the new list
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    //fixing the cursors for the new list
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    //setting everything else to zero
    pos_cursor = 0;
    num_elements = 0;

}

// Copy constructor.
// this basically has everything the same as the new list function but
// it also adds values to the list
List::List(const List& L){
    //adding the placeholder values here to 
    frontDummy = new Node(-20);
    backDummy = new Node(20);
    //placing the next and prev
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    //setting the cursors
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    //setting everything else to zero
    pos_cursor = 0;
    num_elements = 0;
    //going through the list input and appending all thev values
    // in it into the new one
    Node *A = L.frontDummy->next;
    while (A!=L.backDummy)
    {
        //inserting the data from the pointer
        this->insertBefore(A->data);
        //moving so cursor so the loop breaks
        A = A->next;
    }
    //starting at the beginning of the list
    this->moveFront();
}

// Destructor
List::~List(){
    //cleating everything stored
    this->clear();
    //deleting everything else
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    //returning the number of elements
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    //raising an error for an empty list
    if(length() == 0){
        throw std::length_error("calling List: front() on an emtpy list");
    }
    //returns the data from the front
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    //checking for preconditions
    if(length() == 0){
        throw std::length_error("calling List: back() on an empty list");
    }
    //returns the data from the back 
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    //checking to see if the cursor is in the correct position
    // for both the upper range of numbers as well as the lower range
    if(pos_cursor < 0){
        throw std::range_error("cursor out of lower range");
    }
    if(pos_cursor > num_elements){
        throw std::range_error("cursor out of higher range");
    }
    //returning the cursor
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    //checking for the precondition
    if(position()> length()){
        throw std::range_error("calling List: peekNext() out of range");
    }else{
        //then just returning the data after the cursor
        return afterCursor->data;
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    //checking for the precondition
    if(position()< 0){
        throw std::range_error("calling List: peekPrev() out of range");
    }else{
        //then just returning the data before the cursor
        return beforeCursor->data;
    }
}
// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    //starting at the beginning of the list
    this->moveFront();
    //looping through the length of the list and erasing
    while(length()>0){
        this->eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    //setting everything to be at the front
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    //setting everyhing up to be at the back
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    //checking for preconditions
    if(position() > length()){
        throw std::range_error("calling List: moveNext() out of range");
    }else{
        //changing where the cursor position is 
        beforeCursor = afterCursor;
        //moving it to the next one
        afterCursor = afterCursor->next;
        //adding to the cursor value
        pos_cursor++;
        //returning the data
        return beforeCursor->data;
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(position()<0){
        throw std::range_error("calling List: movePrev() out of range");
    }
    //changing where the cursor position is 
    afterCursor = beforeCursor;
    //moving it to the previous one
    beforeCursor = beforeCursor->prev;
    //subtrating from the cursor value
    pos_cursor--;
    //returning the data
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    //checking to see if their is no place to even insert
    if(position()<0){
        exit(EXIT_FAILURE);
    }
    //making a pointer to hold the value for x
    Node *A = new Node(x);
    //setting up all the values for the next and 
    // previous nodes
    beforeCursor->next = A;
    afterCursor->prev = A;
    //pointing to the correct values
    A->prev = beforeCursor;
    A->next = afterCursor;
    //change this
    afterCursor = A;
    //adding to the number of elements
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    //checking to see if their is no place to insert
    if(position() <0){
        exit(EXIT_FAILURE);
    }
    //making apointer to hold the value for x
    Node *A = new Node(x);
    //stting up all the values for the other nodes
    beforeCursor->next = A;
    afterCursor->prev = A;
    //pointing to the next values
    A->prev = beforeCursor;
    A->next = afterCursor;
    //changing the other values
    beforeCursor = A;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    //checking precondtions s
    if(position()>length()){
        throw std::range_error("calling List: setAfter() out of range");
    }else{
        afterCursor->data = x;
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    //checking preconditions
    if(position()<0){
        throw std::range_error("calling List: setBefore() out of range");
    }else{
        beforeCursor->data = x;
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    //checking preconditions
    if(position()> length()){
        throw std::range_error("calling List: eraseAfter() out of range");
    }
    //making a node pointer
    Node *A = afterCursor;
    //changing where the cursors point
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    //deleting the place after the cursor
    delete A;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(position()<0){
        throw std::range_error("calling List: eraseBefore() out of range");
    }
    //making a node pointer
    Node *A = beforeCursor;
    //changing where the cursor now points
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    //deleting the element before the cursor
    delete A;
    //accounting for the less elements and changin cursor
    num_elements--;
    pos_cursor--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    //starting at where the cursor is and having the limit
    // be the number of elements in the list
    while(pos_cursor<num_elements){
        //getting the elements inside of the list
        int get = moveNext();
        //checking to see if it is equal to x
        // if it is return the position of that element
        if(get == x){
            return position();
        }
    }
    //if the element does not exist just return -1
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    //iterating while the cursor is greater than zero 
    // if it is zero then you are at the front
    while(pos_cursor>0){
        //getting the elements of the list here
        int get = movePrev();
        //if the element is x return the position of it
        if(get == x){
            return position();
        }
    }
    //else just return -1
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    //making variables for later
    Node *pointer;
    Node *pointer2;
    Node *pointer3;
    int x;
    int y;
    //setting the first pointer to be the next item after the cursor
    pointer = frontDummy->next;
    x = 0;
    y = 0;
    //iterating through the list using the pointer and not
    // the actual cursor or front dummy so the cursor will not be affected
    while(pointer!= backDummy && pointer->next != backDummy){
        //making the next pointer equal to the first one in order to compare
        pointer2 = pointer;
        y = x;
        //iterating now using the second pointer
        while(pointer2->next!= backDummy){
            //checking to see if the data is the same for the next
            // items in one pointer to the other
            if(pointer->data == pointer2->next->data){
                //checking to see if the data after the second pointer
                //is after the cursor
                if(pointer2->next == afterCursor){
                    //using the other pointer here
                    pointer3 = pointer2->next;
                    //modifying the value of the second pointer
                    pointer2->next->next->prev = pointer2;
                    pointer2->next = pointer2->next->next;
                    afterCursor = pointer2->next;
                    //removing the elements
                    num_elements-=1;
                    delete pointer3;
                //now accounting for the element being before the cursor
                }else if(pointer2->next == beforeCursor){
                    //using the third pointer to be the next value
                    pointer3 = pointer2->next;
                    pointer2->next->next->prev= pointer2;
                    pointer2->next = pointer2->next->next;
                    //changing the value of the element before the cursor
                    beforeCursor = beforeCursor->prev;
                    //removing elements
                    num_elements-=1;
                    delete pointer3;
                }else{
                    //acounting for all other values that can happen
                    pointer3 = pointer2->next;
                    //changing the values of the pointers
                    pointer2->next->next->prev = pointer2;
                    pointer2->next = pointer2->next->next;
                    //removing elements
                    num_elements-=1;
                    delete pointer3;
                }
                //accounting for cursors 
                if(y+1<pos_cursor){
                    pos_cursor-=1;
                }
            //if the next elements in the pointers do not match
            // just iterate to the next one and add to the counters
            }else{
                pointer2 = pointer2->next;
                y+=1;
            }
        }
        //iterating to the next pointer element
        pointer = pointer->next;
        x+=1;
    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    //making node pointers that will hold what is in the list being passed
    // as well as what is in the "this"
    Node *A = this->frontDummy->next;
    Node *B = L.frontDummy->next;
    //new list to hold the concatanated values
    List newL;
    //iterating through the list and checking to see that it is 
    // not at the back 
    while(A!= this->backDummy){
        //inserting everything into the new list
        newL.insertBefore(A->data);
        //moving to the next element
        A = A->next;
    }
    //iterating though the other list here and adding it to the same new list
    while(B!= L.backDummy){
        //inserting the data into the new list
        newL.insertBefore(B->data);
        //moving to the next element
        B = B->next;
    }
    //starting at the front of the new list
    newL.moveFront();
    return newL;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    //acounting for strings of length zero 
    if(length() == 0){
        return("()");
    }
    //making a null pointer that will be changed later
    Node *A = nullptr;
    //calling the funciton within itself to format the answer
    //the actual information goes later
    std::string str = "(";
    //iterating through using the pointer
    // and setting it equal to the front element
    //as long as it istn at the back
    for(A=frontDummy->next;A!=backDummy->prev;A=A->next){
        //then just adding the data using the function itself
        //adding the ", " for format
        str += std::to_string(A->data)+", ";
    }
    //adding the closing parenthasis 
    str += std::to_string(A->data)+")";
    return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    //making two List variables that will hold 
    // the "this" list and the "R" list
    List pointer = *this;
    List pointer2 = R;
    //other variables
    int x;
    int y;
    //making a variable to check if true or false
    bool answer = true;
    //first checking to see if the lists have the same number of elements
    if(R.num_elements != num_elements){
        return false;
    }
    //starting at the front of the lists
    pointer.moveFront();
    pointer2.moveFront();
    // then using those to iterate through 
    // and compare the values
    //this works since they are the same size
    while(pointer.position()<num_elements){
        //getting the data from the pointers
        x = pointer.moveNext();
        y = pointer2.moveNext();
        //then comparing here
        if(x!=y){
            answer = false;
        }
    }
    //clearing the lists
    pointer.clear();
    pointer2.clear();
    //returning the answer
    return answer;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    //just returning the string representation into the stream
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    //just using the equals function here
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    //first checking to see if they are not equal
    if(this != &L){
        //making a new list that is exactly the same as L
        List newL = L;
        //then just using swap to change the state of the copy
        // to the state of the "this" list
        std::swap(this->frontDummy,newL.frontDummy);
        std::swap(this->backDummy,newL.backDummy);
        std::swap(this->num_elements,newL.num_elements);
        std::swap(this->pos_cursor,newL.pos_cursor);
        std::swap(this->afterCursor,newL.afterCursor);
        std::swap(this->beforeCursor,newL.beforeCursor);
    }
    //return the this list with the new data
    return *this;
}
