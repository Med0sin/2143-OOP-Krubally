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
       int

    }
    
    void pushRear(const MedVector& other) {
        Node* otherPtr = other.head;         // get copy of other lists head

        while (otherPtr) {      // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;}
    }