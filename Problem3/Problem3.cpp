
/*
 * Name : Nourhan Ahmed Hussien
 * ID : 20231194
 * section : s7,8
 * TA : Eng. Mennato Allah youssef
 * Team: Poin(dex)ter
 */
#include <iostream>
using namespace std;

//Node class for linked list
class Node {
    public:
        int data;
        Node* next;
        //Node();
        Node(int val) {
            data = val;
            next = nullptr;
        }

};

//Sorted Linked List Class
class SortedLinkedList {
    private:
        Node* head ;

    public:

        SortedLinkedList() {
            head = nullptr;
        }
        void insert(int value) {
            Node *new_node = new Node(value);
            new_node->next = nullptr;

            //if list is empty
            if(head == nullptr) {
                head = new_node;
            }
            else {
                Node *p = head;
                Node*q = head->next;

                while (true) {

                    //the smallest
                    if(new_node->data <= p->data) {
                        new_node->next = head;
                        head = new_node;
                        break;
                    }

                    //one node and the data is smaller than the item
                    if(p->next == nullptr && p->data <= new_node->data) {
                        p->next = new_node;
                        break;
                    }

                    //one node and the data is greater than the item else
                    if(p->next == nullptr && p->data >= new_node->data) {
                        head = new_node;
                        head->next = p;
                        break;
                    }

                    //between two nodes
                    if(p->data <= new_node->data && q->data >= new_node->data) {
                        p->next = new_node;
                        new_node->next = q;
                        break;
                    }

                    //to end the loop
                    if(p->next == nullptr) {
                        break;
                    }
                    p = p->next;
                    q = q->next;
                }
            }
        }

        
        void remove(int index) {
            int count = 0;
            Node *p = head;

            if(head == nullptr) {
                cout << "List is empty" << endl;
            }

            if(index==0) {
                Node *temp = head;
                head = head->next;
                delete temp;
            }

            else {
                
                while (p->next != nullptr) {
                    Node *temp = p->next;
                    if(count == index) {
                        p->next = p->next->next;
                        delete temp;
                        break;
                    }
                    if(count != 0) {
                        p = p->next;
                    }
                    count++;
                }


            }


        }

        //overloaded operators
        friend ostream& operator<< (ostream& os , const SortedLinkedList &list) {
            Node *current = list.head;

            cout << endl << "L = [";
            while(current != nullptr) {
                os << current->data;
                if(current->next != nullptr) {
                    cout << ",";
                }
                current = current->next;
            }
            cout << "]";
            cout << endl;
            return os;
        }

        int operator[](int index) {
            cout << endl << "L[" << index << "] = " ;
            try{
                int counter = 0;
                Node *current = head;

                while(current != nullptr) {
                    if(counter == index) {
                        return current->data;
                    }
                    current = current->next;
                    counter++;
                }
                throw "out of bounds";
            }
            catch (const char *msg) {
                cout << "Exception: " << msg << " ";
                return 0;
            }
        }

        ~SortedLinkedList() {
            Node *current = head;
            while(current) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }

};

int main() {
    SortedLinkedList L;
    L.insert(3);
    L.insert(1);
    L.insert(5);
    L.insert(2);
    L.insert(4);
    cout << L;

    L.remove(2);
    cout << L;

    cout << L[10];
    cout << L[1];

    L.remove(2);
    cout << L;

    L.remove(10);
    cout << L;

    return 0;
}
