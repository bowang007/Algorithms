#include <iostream>
#include <vector>

#include "Blob.h"
#include "SmallVec.h"
#include "time.h"
#include "Linked_list_stack.h"
#include "Resizing_array_stack.h"
#include "Linked_list_queue.h"

using std::vector;
using std::cout;
using std::endl;

int evaluate(const std::string &str) {
    VectorStack<char> ops;
    VectorStack<int> val;
    for (auto &i : str) {
        if (i == '(' || i == ' ') {}
        else if (i == '+') ops.push(i);
        else if (i == '*') ops.push(i);
        else if (i == ')') {
            char op = ops.pop();
            if (op == '+') val.push(val.pop() + val.pop());
            else if (op == '*') val.push(val.pop() * val.pop());
        } else {
            val.push(atoi(&i));
        }
    }
    return val.pop();
}


int main() {
    Blob<int> ia = {0, 1, 2, 3, 4};
    printf("ia : %d\n", ia[0]);

    SmallVec<int> smlvec;
    clock_t start = clock();
    for (int i = 0; i < 1000000; ++i) {
        smlvec.push_back(2 * i);
    }
    clock_t ends = clock();
    cout <<"Small Vec Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;

    vector<int> vec;
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        vec.push_back(2 * i);
    }
    ends = clock();
    cout <<"Standard Vec Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;

//    LinkedStack<std::string> lkstack;
//    lkstack.push("my");
//    lkstack.push("name");
//    lkstack.push("is");
//    lkstack.push("who?");
//    while (!lkstack.isEmpty()) {
//        cout << lkstack.pop() << " ";
//    }
//    cout << "\n";
//
    VectorStack<std::string> vecstack;
    vecstack.push("my");
    vecstack.push("name");
    vecstack.push("who");
    while (!vecstack.IsEmpty()) {
        cout << vecstack.pop() << " ";
    }
    cout << "\n";
//
//
//    LinkedQueue<std::string> lkqueue;
//    lkqueue.enqueue("my");
//    lkqueue.enqueue("name");
//    lkqueue.enqueue("who");
//    while (!lkqueue.isEmpty()) {
//        cout << lkqueue.dequeue() << " ";
//    }
//    cout << "\n";

    cout << "res: " << evaluate("(1 + ((2 + 3) * (4 * 5)))") << endl;



    return 0;
}