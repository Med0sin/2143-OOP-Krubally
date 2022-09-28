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

  // prints t file
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


  friend ostream &operator<<(ostream &os, const MedVector &rhs) {
    Node *temp = rhs.head;

    while (temp) {
      os << temp->data;
      if (temp->next) {
        os << "->";
      }
      temp = temp->next;
    }
    os << endl;
    return os;
  }


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
    
  for( count; count < d;){
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
};

// ofstream MedVector::fout;

int main() {
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
  // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23,
  // 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25,
  // 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
}