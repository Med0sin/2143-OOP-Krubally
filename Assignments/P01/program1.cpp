#include <fstream>
#include <iostream>
#include <string>

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

class MedVector {
private:
    Node*           head;  // head pointer
    Node*           tail;  // tail pointer
    int             size;  
    static ofstream fout;
    string          fileName;

public:
    MedVector() {
        init();
    }

    MedVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    int Medvector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

    MedVector(const MedVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
    }

    void setFileName(string fname) {
        fileName = fname;
    }

    void print(bool printFile = 0) {
        if (printFile) {
            if (!fout.is_open()) {
                fout.open(fileName, std::ofstream::out | std::ofstream::trunc);
            }
        }

        bool flag = (printFile && fout.is_open());

        cout << "[";
        if (flag) {
            fout << "[";
        }

        Node* temp = head;

        while (temp) {
            cout << temp->data;

            if (flag) {
                fout << temp->data;
                ;
            }

            if (temp->next) {
                cout << ",";
                if (flag) {
                    fout << ",";
                }
            }

            temp = temp->next;
        }
        cout << "]";
        if (flag) {
            fout << "]";
        }
        cout << endl;
        if (flag) {
            fout << endl;
        }
    };


    void pushfront( const Medvector& other){
       Node*other= other.head;
       int* tempdata = new int[other.size];

       int i =0;
       while (otherptr){
        tempData[i]= otherptr-> data;
        otherptr = otherptr-> next;
        ++i;
       }      

                //push list in reverse to keep it in order
            for( int i = other.size -1; i>= 0;i--){
                pushfront(tmepdata[i]);
            }
    }

    
    
    void pushRear(const MedVector& other) {
        Node* otherPtr = other.head;         // get copy of other lists head

        while (otherPtr) {      // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;}
    }
    void pushRear( int x){
        Node* tempptr= new Node(x);

        if (!head){
            head = tail =temp;
        }
        else { 
            tail -> next = tempptr;
            tail -> tempptr;
        }
        size++;
    }
     
    friend ostream& operator << (ostream& os , const Medvector& rhs){
        Node* temp= rhs.head;


      while (temp){
        os<< temp -> data;
        if(temp-> next){
            os<< "->"
        }
        temp = temp->next;
      }
      os<< endl;
      return os;
    }

    ofstream Medvector::fout;


int main( ) {
    MedVector V1("input.dat");
    V1.setFilename("newfile1.out");

    MedVector V2("input2.dat");
    V2.setFilename("newfile2.out");

    MedVector V3("input2.dat");
    V3.setFilename("newfile3.out")

    V2.pushFront(100);
    V2.pushFront(200);
    V2.pushFront(300);
    V2.pushFront(400);

    V2.pushFront(V1);

    cout << V1 << endl;
    cout << V2 << endl;
    cout << V3 << endl;  

    V1.print(true);
    V2.print(true);
    V3.print(true);






    }