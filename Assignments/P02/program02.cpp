/*****************************************************************************
 *
 *  Author:           ahmed krubally
 *  Title:            vectors 
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *  create a linked list based Vector class that will include the functionality listed below. 
 * You will achieve this by writing additional methods to add values, remove values, and maintain 
 * sorted values if needed.This class also needs the ability to be initialized with different
 *  data sources (files, other vectors, and arrays). then overload a set of operators such as the the <<,>>,+,-
 * ,/,==,=, operators.
 * 
 *  
 *        
 *
 *  Usage:
 *   allows the user to create a war simulation for two sides
 *

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


// Node for our linked list
struct Node {
  int data;
  Node *previous;
  Node *next;

  Node(int x) {
    data = x;
    next = NULL;
    previous = NULL;
  }
};
/*

        #       #  #####
       #       #  #     # #        ##    ####   ####
      #       #   #       #       #  #  #      #
     #       #    #       #      #    #  ####   ####
    #       #     #       #      ######      #      #
   #       #      #     # #      #    # #    # #    #
  #       #        #####  ###### #    #  ####   ####


*/
class MedVector {
private:
  Node *head; // head pointer
  Node *tail; // tail pointer
  int size;
  ofstream fout;
  string fileName;
public:
  /*
      #       # #     # ####### ####### #     # ####### ######   #####
     #       #  ##   ## #          #    #     # #     # #     # #     #
    #       #   # # # # #          #    #     # #     # #     # #
   #       #    #  #  # #####      #    ####### #     # #     #  #####
  #       #     #     # #          #    #     # #     # #     #       #
 #       #      #     # #          #    #     # #     # #     # #     #
#       #       #     # #######    #    #     # ####### ######   #####
*/
int A[];
  // class constructor
  MedVector() {
    head = tail = NULL;
    fileName = "";
    size = 0;
  }
  // overloaded class constructor for the array
  MedVector(int A[], int aSize) {

    head = tail = NULL;
    fileName = "";
    size = aSize;

    for (int i = 0; i < aSize; i++) {
      pushRear(A[i]);
    }
  }
  // function to open a file and run the values of the file on to the rear emd
  // of the list
  MedVector(string FileName) {

    head = tail = NULL;
    fileName = "";

    ifstream fin;
    int x = 0;
    int i = 0;

    fin.open(FileName);
    while (fin >> x) {
      pushRear(x);
      i++;
    }
    size = i;
  }
  // function to push the "other data"
  MedVector(const MedVector &other) {
    init(other.size);

    Node *temp = other.head;

    while (temp) {
      pushRear(temp->data);
      temp = temp->next;
    }
  }

  void init(int s) {}
  // seting the a newfile name
  void setFileName(string fname) { fileName = fname; }

  // prints to file
  void print(bool printFile = 0) {
    if (printFile) {
      fout.open(fileName, ofstream::out | ofstream::trunc);
    }

    cout << "[";
    if (printFile) {
      fout << "[";
    }

    Node *temp = head;

    while (temp) {
      cout << temp->data;

      if (printFile) {
        fout << temp->data;
      }

      if (temp->next) {
        cout << ",";
        if (printFile) {
          fout << ",";
        }
      }

      temp = temp->next;
    }
    cout << "]";
    if (printFile) {
      fout << "]";
    }
    cout << endl;
    if (printFile) {
      fout << endl;
    }
  }

  // pushes new number to the front of the list

  void pushFront(int x) {
    Node *tempPtr = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
      head = tail = tempPtr;

      // otherwise adjust head pointer
    } else {
      tempPtr->next = head;
      head = tempPtr;
    }
    size++;
  }

  // pushes value of another list into this current list
  // the values are loaded in reverse to they come our in order
  void pushFront(const MedVector &other) {
    Node *otherPtr = other.head;
    int *tempData = new int[other.size];

    // load other list into array
    int i = 0;
    while (otherPtr) {
      tempData[i] = otherPtr->data;
      otherPtr = otherPtr->next;
      ++i;
    }

    for (int i = other.size - 1; i >= 0; i--) {
      pushFront(tempData[i]);
    }
    
  }

  // funciton to add a value to the end of the vector
  void pushRear(int x) {
    Node *tempptr = new Node(x);

    if (!head) {
      head = tail = tempptr;
    } else {
      
      tail->next = tempptr;
      tail = tempptr;
    
      }
    size++;
  }


  int popRear() {
    Node *travel = head;
    while (travel->next != tail) {
      travel = travel->next;
    }
    int tempData = tail->data;
    delete tail;
    tail = travel;
    travel->next = nullptr;
    size--;
    return tempData;
    
  }

  // funciton to push values from the intial list
  void pushRear(const MedVector &other) {
    Node *otherPtr = other.head; // get copy of other lists head

    while (otherPtr) { // traverse and add
      pushRear(otherPtr->data);
      otherPtr = otherPtr->next;
   
    }
  }


  // friend ostream &operator<<(ostream &os, const MedVector &rhs) {
  //   Node *temp = rhs.head;

  //   while (temp) {
  //     os << temp->data;
  //     if (temp->next) {
  //       os << "->";
  //     }
  //     temp = temp->next;
  //   }
  //   os << endl;
  //   return os;
  // }


  int popFront() {

    if (head) {

      Node *temp = head;

      head = head->next;
      delete temp;
      head->previous = NULL;
      temp = NULL;
        size--;
    }
    return head->data;
  }


  void inOrderPush(int val) {
    {
      // Create new node
      Node *temp = new Node(val);

      // Check if empty list
      if (head == NULL) {
        head = temp;
        tail = temp;
      } else {

        if (temp->data < head->data)
          pushFront(val);
        else {

          Node *traverse = head;
          Node *trailing = NULL;

          while (traverse && temp->data > traverse->data) {

            trailing = traverse;
            // Traverse moves on to the next node
            traverse = traverse->next;
          }

          if (traverse == NULL)
            pushRear(val);

          else {
            temp->next = traverse;
            traverse->previous = temp;
            trailing->next = temp;
            temp->previous = trailing;
          }
        }
      }
    }

    // allowing access to the Medvector
  }


  int popAt(int d) {
    Node *travel;
    Node *traveling;
    travel = head;
    int count=0;
    
  for( count=0; count < d;){
    traveling = travel;
      travel = travel-> next;
    count++;
  }
       if (count == d){
         traveling-> next= travel->next;
       }
    return travel->data ;
   }
    
  
  int find(int d) {
    int count=0;
    
    Node* travel;
    Node* traveling;
    travel =head;
    
    while( d !=travel->data ){
      traveling = travel;
      travel = travel-> next;
      count++;

      if(travel== NULL){
        return -1;
      }
      }
  
    return count;
    }


/* Start of program 2: overloading operators and implimenting them 
******************************************************************
*In this section of this program we will overloading more operators 
* in order to increase the functionality of our individual vecter 
* classes.
*
******************************************************************
*/

friend ofstream& operator<<(ofstream&, const MedVector&); 
	
friend ostream& operator<<(ostream&, const MedVector&); 

friend bool operator==(const MedVector&, const MedVector&);

friend MedVector& operator/(const MedVector&, const MedVector&);

friend MedVector& operator*(const MedVector&, const MedVector&);

friend MedVector& operator-(const MedVector&, const MedVector&);

friend MedVector& operator+(const MedVector&, const MedVector&);

};

/* function: Overload the << operator
purpose: This function is used to overload the << operator so it has the ability to print out the entire list of number.

Parameters: ofstream & , const MedVector

Returns: ofstream.

*/
 ofstream& operator<<(ofstream& outfile, const MedVector& V){
  Node* travel = V.head;
    while( travel != NULL){
      outfile << travel->data << " ";
		travel = travel->next;
	}
	return outfile;
    
}

/* function : this function overloads the << aswell 
* purpose: prints out the list all at once with a cout call
* 
* Parameters: ostream& const MedVector
*/

ostream& operator<<(ostream& os, const MedVector& V) {
	Node* travel = V.head;
	while (travel != NULL) {					
		os << travel->data << " ";
		travel = travel->next;
	}
	return os;
  }

/* function : This function is used to overload the == operator
* purpose: This function is used to check if the two vectors being 
*compared are the same.
*
*Parameters: const MedVector& f=first const MedVector& s=second
*
*
*/
bool operator==(const MedVector& f, const MedVector& s){
  Node * travelf= f.head;
  Node * travels= s.head;
  int sizef=0;
  int sizes=0;
  //travel the vectors to check the size
  while( travelf != NULL){
    sizef++;
    travelf = travelf -> next;
  }
//travel the second vector to check the size of the second vector
  while( travels != NULL){
    sizes++;
    travels = travels -> next;
  }
//if they arent the same size then return false
  if( sizes> sizef){
    return false;
  }
    //if they arent the same size then return false
  else if( sizef>sizes){
    return false;
  }
    // if they are the same size check the data if they are the same.
  else{
    while( travelf){
      if( travelf-> data == travels->data){
        travelf= travelf-> next;
        travels = travels-> next;
      }
      else{
        return false;
      }
    }
  }
  }
/*function:overloads the operator "/" 
*purpose: this function overloads the / operator so that we will be 
*able to divide two vectors of the same size
*
*Parameters: const MedVector & , const MedVector &
*
*Returns N= New Vector once the vectors are divided
*/
 MedVector& operator/(const MedVector& f, const MedVector&s){
  MedVector N;
  Node * travelf= f.head;
  Node * travels= s.head;
  int sizef=0;
  int sizes=0;
  //travel the vectors to check the size
  while( travelf != NULL){
    sizef++;
    travelf = travelf -> next;
  }
//travel the second vector to check the size of the second vector
  while( travels != NULL){
    sizes++;
    travels = travels -> next;
  }
//if the first vector is larger than the second vector 
  if(sizef> sizes){
    for( int i= 0; i <= sizes;i++){
      N.pushRear ( travelf-> data/ travels-> data);
        travelf= travelf-> next;
        travels= travels ->next;
    }
    //push the rest of the larger vector
    while(travelf){
      N.pushRear(travelf->data);
        travelf= travelf-> next;
    }
    return N;
  }
    //if the second vector is larger than the first vector 
  else if( sizes>sizef){
    for(int i=0; i <= sizef; i++){
      N.pushRear(travels->data/ travelf->data);
      travels= travels->next;
      travelf= travelf->next;  
    }
    //Push the rest of the bigger vector
    while(travels){
      N.pushRear(travels->data);
      travels= travels-> next;
    }
    return N;
  
  }
    // if they are the same size divide the data within the vectors
  else{
    while(travelf){
      N.pushRear(travelf->data/ travels->data);
      travelf= travelf->next;
      travels= travels-> next;
    }
      return N;

      }
   }
  
/* function: overload the "*" operator
*
*Purpose:This function allows the ablity to mulitply the values in *two vectors
*
*Parameters: const MedVector& , const Medvecotor &
*
*Return: N= new vector; the result of the multiplying of two vector
*/
  
   MedVector& operator*(const MedVector& f, const MedVector& s){
MedVector N;
  Node * travelf= f.head;
  Node * travels= s.head;
  int sizef=0;
  int sizes=0;
  //travel the vectors to check the size
  while( travelf != NULL){
    sizef++;
    travelf = travelf -> next;
  }
//travel the second vector to check the size of the second vector
  while( travels != NULL){
    sizes++;
    travels = travels -> next;
  }
//if the first vector is larger than the second vector 
  if(sizef> sizes){
    for( int i= 0; i <= sizes;i++){
      N.pushRear ( travelf-> data* travels-> data);
        travelf= travelf-> next;
        travels= travels ->next;
    }
    //push the rest of the larger vector
    while(travelf){
      N.pushRear(travelf->data);
        travelf= travelf-> next;
    }
    return N;
  }
    //if the second vector is larger than the first vector 
  else if( sizes>sizef){
    for(int i=0; i <= sizef; i++){
      N.pushRear(travels->data * travelf->data);
      travels= travels->next;
      travelf= travelf->next;  
    }
    //Push the rest of the bigger vector
    while(travels){
      N.pushRear(travels->data);
      travels= travels-> next;
    }
    return N;
  
  }
    // if they are the same size multiply the data within the vectors
  else{
    while(travelf){
      N.pushRear(travelf->data * travels->data);
      travelf= travelf->next;
      travels= travels-> next;
    }
      return N;

      }

  }
  
  
  
  /* Function: this function overload the  
* Purpose: this function provide the functionality to subtract the 
*values of two different vectors
*
*parameters: const MedVector& , Const MedVector&
*
*Returns: N= new vecotor; the quotient vector of the two subtracted *vectors
*
**/

 MedVector& operator-(const MedVector&f, const MedVector&s){

  MedVector N;
  Node * travelf= f.head;
  Node * travels= s.head;
  int sizef=0;
  int sizes=0;
  //travel the vectors to check the size
  while( travelf != NULL){
    sizef++;
    travelf = travelf -> next;
  }
//travel the second vector to check the size of the second vector
  while( travels != NULL){
    sizes++;
    travels = travels -> next;
  }
//if the first vector is larger than the second vector 
  if(sizef> sizes){
    for( int i= 0; i <= sizes;i++){
      N.pushRear ( travelf-> data - travels-> data);
        travelf= travelf-> next;
        travels= travels ->next;
    }
    //push the rest of the larger vector
    while(travelf){
      N.pushRear(travelf->data);
        travelf= travelf-> next;
    }
    return N;
  }
    //if the second vector is larger than the first vector 
  else if( sizes>sizef){
    for(int i=0; i <= sizef; i++){
      N.pushRear(travels->data - travelf->data);
      travels= travels->next;
      travelf= travelf->next;  
    }
    //Push the rest of the bigger vector
    while(travels){
      N.pushRear(travels->data);
      travels= travels-> next;
    }
    return N;
  
  }
    // if they are the same size divide the data within the vectors
  else{
    while(travelf){
      N.pushRear(travelf->data - travels->data);
      travelf= travelf->next;
      travels= travels-> next;
    }
      return N;

    }
  }

  /* Function: overload the "+" operator
*
*purpose: This function allows the two vectors to be added together
*
*Parameters: const MedVector& , Const MedVector&
*
*Return: N = newvector; the sum vector of the two vectors
*/

   MedVector& operator+(const MedVector&f, const MedVector&s)
  {
     MedVector N;
  Node * travelf= f.head;
  Node * travels= s.head;
  int sizef=0;
  int sizes=0;
  //travel the vectors to check the size
  while( travelf != NULL){
    sizef++;
    travelf = travelf -> next;
  }
//travel the second vector to check the size of the second vector
  while( travels != NULL){
    sizes++;
    travels = travels -> next;
  }
//if the first vector is larger than the second vector 
  if(sizef> sizes){
    for( int i= 0; i <= sizes;i++){
      N.pushRear ( travelf-> data + travels-> data);
        travelf= travelf-> next;
        travels= travels ->next;
    }
    //push the rest of the larger vector
    while(travelf){
      N.pushRear(travelf->data);
        travelf= travelf-> next;
    }
    return N;
  }
    //if the second vector is larger than the first vector 
  else if( sizes>sizef){
    for(int i=0; i <= sizef; i++){
      N.pushRear(travels->data + travelf->data);
      travels= travels->next;
      travelf= travelf->next;  
    }
    //Push the rest of the bigger vector
    while(travels){
      N.pushRear(travels->data);
      travels= travels-> next;
    }
    return N;
  
  }
    // if they are the same size divide the data within the vectors
  else{
    while(travelf){
      N.pushRear(travelf->data + travels->data);
      travelf= travelf->next;
      travels= travels-> next;
    }
      return N;
    
  }

    }
  





 //ofstream MedVector::fout;

//overloading the + operator


int main() {
  ofstream fout;
  
   
  
  MedVector V1("input.dat");
  V1.setFileName("newfile1.out");

  MedVector V2("input2.dat");
  V2.setFileName("newfile2.out");

  MedVector V3("input2.dat");
  V3.setFileName("newfile3.out");

  // Ahmed krubally
  // 09-16-22
  // fall 2143


  
  int x = 0;

  MedVector v1;
  v1.pushFront(18);
  v1.pushFront(20);
  v1.pushFront(25);
  v1.pushRear(18);
  v1.pushRear(20);
  v1.pushRear(25);
  v1.print();
  // [25, 20, 18, 18, 20, 25]

  int A[] = {11, 25, 33, 47, 51};
  MedVector v2(A, 5);
  v2.print();
  // [11, 25, 33, 47, 51]

  v2.pushFront(9);
  v2.inOrderPush(27);
  v2.pushRear(63);
  v2.print();
  // [9, 11, 25, 33, 47, 51, 63]

  v1.pushRear(v2);
  v1.print();
  // [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

  x = v1.popFront();
  x = v1.popFront();
  x = v1.popFront();
  v1.print();
  // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
  cout << x << endl;
  // 18

  x = v1.popRear();
  x = v1.popRear();
  x = v1.popRear();
  v1.print();
  // [18, 20, 25, 9, 11, 25, 27, 33]
  cout << x << endl;
  // 47

   x = v2.popAt(3);
   v2.print();
  // [9, 11, 25, 33, 47, 51, 63]
  cout<<x<<endl;
  // 27


  
  x = v2.find(51);
  cout<<x<<endl;
  // 5

  x = v2.find(99);
  cout<<x<<endl;
  // -1

   V3.pushFront(v1);
 V3.print();
  //[18, 20, 25, 9, 11, 25, 27, 33]

   V3.pushRear(v2);
   V3.print();
  // //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

   MedVector v4("input.dat");
   v4.pushRear(v1);
   v4.print();

  fout<< v1;
  fout<< v2;
  fout<< V3;
  fout<< v4;

  
  // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23,
  // 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25,
  // 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]


  cout<<"======================================================="<<endl;

  int a1[] = { 1, 2, 3, 4, 5 };
int a2[] = { 10, 20, 30 };

MedVector v7(a1,5);
MedVector v8(a2,3);

// ofstream fout;
// ofile.open("output.txt");

//cout << v7[2] << endl;
// writes out 3

//v7[4] = 9;
// v1 now = [1,2,3,4,9]

cout << v7 << endl;
// writes out [1,2,3,4,9] to console.

fout << v7 << endl;
// writes out [1,2,3,4,9] to your output file.

MedVector v9 = v7 + v8;
cout << v9 << endl;
// writes out [11,22,33,4,9] to console.

v9 = v7 - v8;
cout << v9 << endl;
// writes out [-9,-18,-27,4,9] to console.

v9 = v8 - v7;
cout << v9 << endl;
// writes out [9,18,27,4,9] to console.

v9 = v8 * v7;
cout << v9 << endl;
// writes out [10,40,90,4,9] to console.

v9 = v7 * v8;
cout << v9 << endl;
// writes out [10,40,90,4,9] to console.

v9 = v7 / v8;
cout << v9 << endl;
// writes out [0,0,0,4,9] to console.

v9 = v8 / v7;
cout << v9 << endl;
// writes out [10,10,10,4,9] to console.

cout << (v8 == v7) << endl;
// writes 0 to console (false) .

MedVector v40 = v7;
cout << (v40 == v7) << endl;
// writes 1 to console (true) .
}
   
  