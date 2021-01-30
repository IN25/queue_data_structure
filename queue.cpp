#include <iostream>
#include <string>
#include <cstdlib> //needed for exit(1);

using namespace std;

/*
This program implements the data structure called Queue.
*/

// struct containing a string (element_name) and an bool (priority), 
//as well as a node pointer (Node* next)
struct Node {
    string element_name;
    bool priority; //bool to keep track of the priority queue
    Node *next; //points to the next node in the Queue
};

// Queue class;
class Queue {
    // --- public members ---
    public:
    //Constructor (with no parameters) - Creates an empty queue.
    Queue();

    //Deconstructor - Deletes the queue.
    ~Queue();

    //Checks if the queue is empty.
    bool isEmpty() {return (front == NULL);};

    //Adds a new Node to the back of the Queue. 
    void Enqueue(string d);

    //Priority Enqueue - Adds a new Node to the front of the Queue,if there are 
    //already priority nodes in the Queue, the new Node
    // is added at the back of the priority nodes
    void PriorityEnqueue(string d);
    
    //Deletes a Node from the front of the Queue and return a string
    string Dequeue();

    //Returns a string containing the contents of the queue 
    string toString();


    // --- private members ---
    private:

    //a pointer to the front of the Queue
    Node* front;

    //a pointer to the back of the Queue
    Node* back;

    //a pointer to the back of the PriorityQueue
    Node* priorityback;
};

//Constructor (with no parameters) - Creates an empty queue.
Queue::Queue() {
    front = NULL;
    back = NULL;
    priorityback = NULL;
}

//Deconstructor - Deletes the queue.
Queue::~Queue() {
    while(!isEmpty()) {
        cout << "deleting node..." << endl;
        Dequeue();
    }
}

//Adds a new Node to the back of the Queue. 
void Queue::Enqueue(string d) {
    Node *newback = new Node; //create a new Node
    newback->element_name = d; //assign data
    newback->next = back; //make newback's next point to whatever the back points to
    back = newback; //make back point to whatever newback points to
    if (front == NULL) {
        front = back;
        front->next = NULL;
    }
}

//Priority Enqueue - Adds a new Node to the front of the Queue,if there are 
//already priority nodes in the Queue, the new Node
// is added at the back of the priority nodes
void Queue::PriorityEnqueue(string d) {
    if (isEmpty()) {
        Enqueue(d);
        front->priority = true;
        priorityback = front;
    } else {
        if (front->priority == false) {
        Node *newfront = new Node; //create a new Node
        newfront->element_name = d; //assign data
        newfront->next = front->next; //make newfront point to NULL
        front->next = newfront; //make front point to whatever newfront points to
        front = newfront; //new front
        front->priority = true;
        priorityback = front; //this pointer is needed to keep track of 
                              //priority queue
        //if there is already priority element, it is placed to the back
        //of that element and this code gets exected
    } else { 
        Node* newpriorityback = new Node; //create a new node
        newpriorityback->element_name = d; //assign name
        newpriorityback->next = priorityback; //make newpriorityback point 
                                              //to priorityback
                                          
        Node *temp = back; //create a new node and point to back
        //search for the element before priority back
        while(temp->next != priorityback) {
            temp = temp->next;
        }
        temp->next = newpriorityback;
        priorityback = newpriorityback;
    }

    }
      
}

//Deletes a Node from the front of the Queue and return a string
string Queue::Dequeue() {
    if (isEmpty()) {
        cout << "ERROR: You can't dequeue from an empty queue" << endl;
        exit(-1);
    } else {
        string value = front->element_name; //set aside element_name to return it later
        if (back->next != NULL) {
        Node *oldfront = back; //ponint new node to back
        oldfront = front;

        Node *current = back;
        //search for the element before front
        while(current->next != front) {
            current = current->next;
        }
        current->next = NULL;

        front = current;

        delete oldfront;        
        return value; 

        } else {
            Node *oldfront = front;
            front = NULL;
            back = NULL;
            delete oldfront;
            return value;
        }
    }
}

//Returns a string containing the contents of the queue 
string Queue::toString() {
    string result = "";
    Node *current = back;
    while (current != NULL) {
        result += current->element_name + " -> ";
        current = current->next;
    }
    result += "NULL";
    return result;
}


int main() {

    Queue* q = new Queue();

    q->Enqueue("Solo");
    q->Enqueue("R2D2");
    q->Enqueue("Yoda");
    q->PriorityEnqueue("BB8");

    cout << q->toString() << endl;

    q->PriorityEnqueue("IN25");

    cout << q->toString() << endl;

    q->Dequeue();

    cout << q->toString() << endl;

    delete q;

    return 0;
}