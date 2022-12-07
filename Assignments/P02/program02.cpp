/*****************************************************************************
*
*  Author:          Ahmed krubally
*  Title:            Singly linked list vector implementation
*  Course:           2143
*  Semester:         Fall 2021
*
*  Description:
*        Uses a singly linked list program and overload additional operators
*
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF = 1000000000

using namespace std;

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


/*
 
    ,                                                                                                                                                                                                                                                                                            
  ,'                                                                                                                                                                                                                                                                                             
 '                                                                                                                                                                                                                                                                                               
                                                                                                                                                                                                                                                                                                 
          ,      ,      ,    ,          ,      ,        ,    ,       .    .       ,        ,      ,    ,       .    .       ,    ,       .    .                   ,    ,       .    .         ,      ,                    ,    ,                  ,    ,       .    .       ,    ,       .    .  
        ,'     ,'     ,'   ,'         ,'     ,'       ,'   ,'         )    )    ,'       ,'     ,'   ,'         )    )    ,'   ,'         )    )                ,'   ,'         )    )      ,'     ,'                   ,'   ,'                 ,'   ,'         )    )    ,'   ,'         )    ) 
       '      '      '    '          '      '        '    '          '    '    '        '      '    '          '    '    '    '          '    '                '    '          '    '      '      '                    '    '                  '    '          '    '    '    '          '    '  
                                                                                                                                                                                                                                                                                                 
        ,      ,      ,    ,            ,    ,                        ,      ,            ,    ,          ,      ,      ,    ,    ,      ,                  ,    ,                    ,      ,                    ,    ,            .  .                .  .                                     
      ,'     ,'     ,'   ,'           ,'   ,'                       ,'     ,'           ,'   ,'         ,'     ,'     ,'   ,'   ,'     ,'                 ,'   ,'                   ,'     ,'                   ,'   ,'            (  (                (  (                                      
     '      '      '    '            '    '                        '      '            '    '          '      '      '    '    '      '                  '    '                    '      '                    '    '               `  `                `  `                                     
                                                                                                                                                                                                                                                                                                 
      ,      ,      ,              ,    ,                        ,      ,            ,    ,          ,      ,      ,      .                    ,    ,                    ,      ,                    ,                   ,    ,                  ,    ,                                          
    ,'     ,'     ,'             ,'   ,'                       ,'     ,'           ,'   ,'         ,'     ,'     ,'      (                   ,'   ,'                   ,'     ,'                   ,'                     `,   `,                 `,   `,                                        
   '      '      '              '    '                        '      '            '    '          '      '      '         `                 '    '                    '      '                    '                         `    `                  `    `                                       
                                                                                                                                                                                                                                                                                                 
    ,      ,      ,    ,                    ,    ,                        ,      ,            ,    ,          ,      ,      ,    ,                          ,    ,                    ,      ,                    ,    ,                           .    .              .    .                    
  ,'     ,'     ,'   ,'                   ,'   ,'                       ,'     ,'           ,'   ,'         ,'     ,'     ,'   ,'                         ,'   ,'                   ,'     ,'                   ,'   ,'                             )    )              )    )                   
 '      '      '    '                    '    '                        '      '            '    '          '      '      '    '                          '    '                    '      '                    '    '                              '    '              '    '                    
                                                                                                                                                                                                                                                                                                 
        ,      ,    ,    ,      ,    .  .    ,      ,          ,      ,          .  .    ,      ,      ,    ,                        .  .    ,      ,      ,      ,    ,      ,      ,    ,                .  .      ,      ,  .  .      ,      ,                                                
      ,'     ,'   ,'   ,'     ,'    (  (   ,'     ,'         ,'     ,'          (  (   ,'     ,'     ,'   ,'                        (  (   ,'     ,'     ,'     ,'   ,'     ,'     ,'   ,'                (  (     ,'     ,'  (  (     ,'     ,'                                                 
     '      '    '    '      '       `  ` '      '          '      '             `  ` '      '      '    '                           `  ` '      '      '      '    '      '      '    '                   `  `   '      '     `  `   '      '                                                   
                                                                                                                                                                                                                                                                                                 
    ,                                                                                                                                                                                                                                                                                            
  ,'                                                                                                                                                                                                                                                                                             
 '                                                                                                                                                                                                                                                                                               
                                                                                                                                                                                                                                                                                                 
 
*/

class Medvector {
private:
    Node* head;  // base pointer of list
    Node* tail;
    int size;
    static ofstream fout;
    string infileName;
    bool sorted;

    /**
     *  function Private version of inOrder push.
     *
     *  parameters x
     */
    void _ Pushinorder(int x) {
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
    }

public:
    /**
     *  function Default constructor
     *
     */
    Medvector() {
        init();
    }

    /**
     *  function: Overloaded Constructor
     *
     *  parameters int *A  pointer to array ,int aSize  size of array
     */
    Medvector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    /**
     *  function: Overloaded Constructor
     *
     *  parameters :string infileName file to open and read
     */
    Medvector(string infileName) {
        init();

        ifstream infile;
        int x = 0;

        infile.open(infileName);
        while (!infile.eof()) {
            infile >> x;
            pushRear(x);
        }
    }

    /**
     *  function Copy Constructor
     *
     *  parameters Medvector &other
     */
    Medvector(const Medvector& other) {
        init();

        Node* traverse = other.head;
        while (traverse) {		//while loop that traverses the whole list and pushes the data from the V2 to V1
            pushRear(traverse->data);
            traverse = traverse->next;
        }
    }

    /**
     *  function - Initialize the data members 
     * parameters: none
     *   return: void
     */ 
    void init() {
        head = tail = NULL;
        infileName = " "; 
        size = 0;
        sorted = 0;
    }


    /**
     *  function Public version of inOrder push.
     *  parameters :int x
     * returns : none
     */
    void  Pushinorder(int x) {
        if (!sorted) {
            sortList();
        }

        if (!head) {
            pushFront(x);  // call push front for empty list (or pushRear would work)
        }
        else if (x < head->data) {
            pushFront(x);  // call push front if x is less than head
        }
        else if (x > tail->data) {
            pushRear(x);  // call push rear if x > tail
        }
        else {
            _ Pushinorder(x);  // call private version of push in order
        }
    }

    /**
     *  function Sort the current values in the linked list.
     *
     *  returns None
     */
    void sortList() {
        Node* newFront = head;

        while (newFront->next) {
            Node* smallest = newFront;
            Node* current = newFront;
            int   minimum = 1000000000;

            while (current) {
                if (current->data < minimum) {
                    smallest = current;
                    minimum = current->data;
                }
                current = current->next;
            }

            smallest->data = newFront->data;
            newFront->data = minimum;
            newFront = newFront->next;
        }

        sorted = true;
    }

    /**
     *  function Add value to front of list.
     *
     *  parameters x
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr; 
            // otherwise adjust head pointer
        }
        else {
            tempPtr->next = head; 
            head = tempPtr; 
        }

        size++;
    }

    /**
     *  function :this loads in the other vector to the front of the vector
     *  parameters: Medvector& other
     *  return: None
     */
    void pushFront(const Medvector& other) {
        Node* otherPtr = other.head;           // get copy of other lists head
        int* tempData = new int[other.size];  // allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i; 
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]); 
        }
    }

    /**
     *  function:  Add first list values to the end of another list
     *  parameters: Medvector& other
     *  return: None
     */
    void pushRear(const Medvector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     *  function :Push value onto list at soecified position, if it exists.
     *
     *  parameters: int i - location index  inr x - value to add
     *  return : true add successful / false add failed
     */
    bool pushAt(int i, int x) {
        if (i >= size) {
            return false;
        }

        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i > 0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
        return true;
    }

    /**
     *  function: Add value to rear of list
     *
     *  parameters: int x - value to be added
     *  return: None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        }
        else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

    friend ostream& operator<<(ostream& os, const Medvector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
            // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << "->";
            }
            temp = temp->next;  // move to next Node
        }
        os << endl;
        return os;
    }

    /**
     *  function Destroy the My Vector object
     *
     */
    ~Medvector() {
        Node* curr = head;
        Node* prev = head;

        while (curr) {
            prev = curr;
            curr = curr->next;
            cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }

    
    //Overloaded operators for the objective of program 2
    

    //Overload << (ostream) so that printing to std out is easy
    friend ofstream& operator<<(ofstream&, const Medvector&);

    //Overload << (ofstream) so that printing to out-file is easy.
    friend ofstream& operator>>(ofstream&, const Medvector&);

    //Overload [] so that your Medvector can be treated as an array
    //friend Medvector& operator[](const Medvector&, const Medvector&);

    //Overload + (addition)
    friend Medvector& operator+(const Medvector&, const Medvector&);

    //Overload - (subtraction)
    friend Medvector& operator-(const Medvector&, const Medvector&);

    //Overload * (multiplication)
    friend Medvector& operator*(const Medvector&, const Medvector&);

    //Overload / (division)
    friend Medvector& operator/(const Medvector&, const Medvector&);

    //Overload == (equality)
    friend bool operator==(const Medvector&, const Medvector&);

    //Overload = (assignment)
    //friend ofstream& opearator=(ofstream&, const Medvector&);
    
};

//Overload << (ostream) so that printing to std out is easy
ofstream& operator<<(ofstream& outfile, const Medvector& M) {
    Node* traverse = M.head;

    while (traverse != NULL) {					//goes through entire list and dispalays as it traverses
        outfile << traverse->data << " ";
        traverse = traverse->next;
    }

    return outfile;
}

//Overload >> (ofstream) so that printing to out-file is easy.
ofstream& operator>>(ofstream& os, const Medvector& M) {
    Node* traverse = M.head;

    while (traverse != NULL) {					//goes through entire list and dispalays as it traverses
        os << traverse->data << " ";
        traverse = traverse->next;
    }

    return os;
}

//Overload + (addition)
Medvector& operator+(const Medvector& a, const Medvector& b) {
        Medvector M;

        Node*  travel1 = a.head;
        Node*  travel2 = b.head;

        int aSize = 0;
        int bSize = 0;

        //  getting the sizes of the vectors that will be added 
        while ( travel1) {
            aSize++;
             travel1 =  travel1->next;
        }
        while ( travel2) {
            bSize++;
             travel2 =  travel2->next;
        }

        // repointing traverse to heads
         travel1 = a.head;
         travel2 = b.head;
        // checks if the first vector is larger that the other 
        if (aSize > bSize) {
            // adds the elements of both vectors and pushes to the rear 
            for (int i = 0; i != bSize; i++) {
                M.pushRear( travel1->data +  travel2->data);
                 travel1 =  travel1->next;
                 travel2 =  travel2->next;
            }
            // pushes the remaining elements of the first vector
            while ( travel1) {
                M.pushRear( travel1->data);
                 travel1 =  travel1->next;
            }
            delete  travel1;
            delete  travel2;
            return M;
        }

        // checks if the second vector is larger than the other 
        else if (bSize > aSize) {
            // adds the elements and pushes to new vector
            for (int i = 0; i != aSize; i++) {
                M.pushRear( travel1->data +  travel2->data);
                 travel1 =  travel1->next;
                 travel2 =  travel2->next;
            }
            //pushes the remaining elements in the second vector 
            while ( travel2) {
                M.pushRear( travel2->data);
                 travel2 =  travel2->next;
            }
            delete  travel1;
            delete  travel2;
            return M;
        }

        else {
            // adds the elements and pushes them to the new vector
            while ( travel1) {
                M.pushRear( travel1->data +  travel2->data);
                 travel1 =  travel1->next;
                 travel2 =  travel2->next;
            }
            delete  travel1;
            delete  travel2;
            return M;
        }

}

//Overload - (subtraction)
Medvector& operator-(const Medvector& a, const Medvector& b) {
    Medvector M;

    Node*  travel1 = a.head;
    Node*  travel2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while ( travel1) {
        aSize++;
         travel1 =  travel1->next;
    }
    while ( travel2) {
        bSize++;
         travel2 =  travel2->next;
    }

    // repointing traverse to heads
     travel1 = a.head;
     travel2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear( travel1->data -  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        // pushes the remaining elements of the first vector
        while ( travel1) {
            M.pushRear( travel1->data);
             travel1 =  travel1->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear( travel1->data -  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        //pushes the remaining elements in the second vector 
        while ( travel2) {
            M.pushRear( travel2->data);
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while ( travel1) {
            M.pushRear( travel1->data -  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }
}

//Overload * (multiplication)
Medvector& operator*(const Medvector& a, const Medvector& b) {
    Medvector M;

    Node*  travel1 = a.head;
    Node*  travel2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while ( travel1) {
        aSize++;
         travel1 =  travel1->next;
    }
    while ( travel2) {
        bSize++;
         travel2 =  travel2->next;
    }

    // repointing traverse to heads
     travel1 = a.head;
     travel2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear( travel1->data *  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        // pushes the remaining elements of the first vector
        while ( travel1) {
            M.pushRear( travel1->data);
             travel1 =  travel1->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear( travel1->data *  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        //pushes the remaining elements in the second vector 
        while ( travel2) {
            M.pushRear( travel2->data);
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while ( travel1) {
            M.pushRear( travel1->data *  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }
}

//Overload / (division)
Medvector& operator/(const Medvector& a, const Medvector& b) {
    Medvector M;

    Node*  travel1 = a.head;
    Node*  travel2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while ( travel1) {
        aSize++;
         travel1 =  travel1->next;
    }
    while ( travel2) {
        bSize++;
         travel2 =  travel2->next;
    }

    // repointing traverse to heads
     travel1 = a.head;
     travel2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear( travel1->data /  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        // pushes the remaining elements of the first vector
        while ( travel1) {
            M.pushRear( travel1->data);
             travel1 =  travel1->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear( travel1->data /  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        //pushes the remaining elements in the second vector 
        while ( travel2) {
            M.pushRear( travel2->data);
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while ( travel1) {
            M.pushRear( travel1->data /  travel2->data);
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;
        return M;
    }
}

//Overload == (equality)
bool operator==(const Medvector& a, const Medvector& b) {
    Node*  travel1 = a.head;
    Node*  travel2 = b.head;

    int aSize = 0;
    int bSize = 0;
    int total = 0;

    //  getting the sizes of the vectors that will be added 
    while ( travel1) {
        aSize++;
         travel1 =  travel1->next;
    }
    while ( travel2) {
        bSize++;
         travel2 =  travel2->next;
    }

    // repointing traverse to heads
     travel1 = a.head;
     travel2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        return false;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        return false;
    }

    else {
        // adds the elements and pushes them to the new vector
        while ( travel1) {
            if ( travel1->data ==  travel2->data) {
                // increment count every time the elements are equal
                total++;
            }
             travel1 =  travel1->next;
             travel2 =  travel2->next;
        }
        delete  travel1;
        delete  travel2;

        if (total == aSize) {
            return true;
        }
        else {
            return false;
        }
    }
}

ofstream Medvector::fout;


int main() {
    Medvector V1;

    V1.pushFront(76);
    V1.pushFront(22);
    V1.pushFront(94);
    V1.pushFront(54);

    V1.pushFront(V1);

    cout << V1 << endl;
    //print out the vector 1

    V1.sortList();
    cout << V1 << endl;

    V1.pushAt(3, 15);
    cout << V1 << endl;
    V1.sortList();
    cout << V1 << endl;

    //main for program 2

    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    Medvector V3(a1, 5);
    Medvector V4(a2, 3);
    

    ofstream outfile;
    outfile.open("output.txt");
     
  

    cout << V3 << endl;
    // writes out [1,2,3,4,9] to console.

    outfile << V3 << endl;
    // writes out [1,2,3,4,9] to your output file.

    Medvector V5 = V3 + V4;
    cout << V5 << endl;
    //adds the vector 3 and 4 to create 5

    V5 = V3 - V4;
    cout << V5 << endl;
    // subtracts vectors 3 and 4 to make vector 5


    V5 = V3 * V4;
    cout << V5 << endl;
    // multiples vectos 3 and 4 to make 5


    V5 = V3 / V4;
    cout << V5 << endl;
    // divides vector 3 and 4 to make a new 5 vector

    V5 = V4 / V3;
    cout << V5 << endl;
    // reverses the divions from above

    cout << (V4 == V3) << endl;
    // checks to see if the two vectors are the same 

    Medvector V6 = V3;
    cout << (V6 == V3) << endl;
    // checks to see if the new vectors are the same. 
    
    outfile.close();
}