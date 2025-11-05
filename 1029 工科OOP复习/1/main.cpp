#include <iostream>
#include "file.h"
using namespace std;

int main() {
    LinkedList<int> * list = new LinkedList<int>;
    LinkedList<int> * stack = new Stack<int>;
    LinkedList<int> * queue = new Queue<int>;

    cout << "LinkedList" << endl;
    list->pushFront(1);
    list->pushBack(2);
    list->pushBack(3);
    list->pushFront(4);
    list->print();
    list->popFront();
    list->popBack();
    list->print();
    cout << list->size() << endl;

    cout << stack->name() << endl;
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);
    cout << stack->peak() << endl;
    stack->pop();
    cout << stack->pop() << endl;
    cout << stack->peak() << endl;

    cout << queue->name() << endl;
    queue->push(1);
    queue->push(2);
    queue->push(3);
    queue->push(4);
    cout << queue->peak() << endl;
    queue->pop();
    cout << queue->pop() << endl;
    cout << queue->peak() << endl;

    delete list;
    delete stack;
    delete queue;

    return 0;
}