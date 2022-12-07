
/*****************************************************************************
*                    
*  Author:           Ahmed krubally
*  Email:            ahmedkrubally696@gmail.com
*  Label:            A04
*  Title:            comments
*  Course:           2143
*  Semester:         Fall 2022
* 
*  Description:
*        Use previouslly writen code and the aporiate comments to the program
* 
*  Usage:
*        how to use the program if necessary
* 
*  Files:            (list of all source files used in this program)
*****************************************************************************/




#include <iostream>

using namespace std;

/**
 * CircularArrayQue
 * 
 * Description:
 *      create a queue using a circular array 
 * 
 * Public Methods:
 *       void       circularArrayque()
 *       void       Push()
 *       int        Pop ()
 * 
 * Private Methods:
 *       bool       Full()
 *      
 *      
 * 
 * Usage: 
 * 
 *      Push                 // This adds a number to the que
 *      Pop                  // This removes the number from the que
 *      
 */
class CircularArrayQue {
private:
    int *Container;
    int Front; //variable for the frount
    int Rear;// varible for the rear
    int QueSize; // items in the queue
    int CurrentSize;//varible for the current size of array
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
//construnctor 
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    //overloaded constructor
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }
//funciton: adds a value to the list
// parameters: int item
//return: none
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }
//funciton : removes an iten from the list
//parameters: none
//return : int
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};
//overloaded << operator to impliment the " " with in the printing of the list
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);      //add a 1 to the que
    C1.Push(2);      //adds a 2 to the que
    C1.Push(3);      //adds a 3 to the  que
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;  //Prints the que

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}