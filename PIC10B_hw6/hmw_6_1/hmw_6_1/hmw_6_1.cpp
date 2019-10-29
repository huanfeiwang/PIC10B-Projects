//
//  hmw_6_1.cpp
//
//  Created by Rui Yan on 2019/3/7.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;

class ListInt;
class Iterator;

class Node
{
public:
    /*
     Constructs a node with a given data value.
     @param s the data to store in this node
     */
    Node(int s);

    /* Destructor */
    ~Node() {}
private:
    int data;
    Node* previous;
    Node* next;
    friend class ListInt;
    friend class Iterator;
};

class ListInt
{

public:
    /**
     Constructs an empty list.
     */
    ListInt();

    /* Destructor. Deletes Nodes that are dynamically allocated */
    ~ListInt();

    /**
     Appends an element to the list.
     @param data the value to append
     */
    void push_back(int data);

    /**
     Swaps the nodes to which the iterators it1 and it2 point to.
     */
    void swap_nodes(Iterator it1, Iterator it2);

    /**
     Sorts the elements of the ListInt using selection sort algorithm.
     */
    void selection_sort();

    /**
     Inserts an element into the list.
     @param iter the position before which to insert
     @param s the value to append
     */
    void insert(Iterator iter, int s);
    /**
     Removes an element from the list.
     @param iter the position to remove
     @return an iterator pointing to the element after the
     erased element
     */
    Iterator erase(Iterator iter);
    /**
     Gets the beginning position of the list.
     @return an iterator pointing to the beginning of the list
     */
    Iterator begin();
    /**
     Gets the past-the-end position of the list.
     @return an iterator pointing past the end of the list
     */
    Iterator end();

    bool empty();

private:
    Node* first;
    Node* last;
    friend class Iterator;
};

class Iterator
{
public:
    /**
     Constructs an iterator that does not point into any list.
     */
    Iterator();

    /* Copy constructor */
    Iterator(const Iterator & pos);
    /**
     Looks up the value at a position.
     @return the value of the node to which the iterator points
     */
    int get() const;
    /**
     Advances the iterator to the next node.
     */
    void next();
    /**
     Moves the iterator to the previous node.
     */
    void previous();
    /**
     Compares two iterators.
     @param b the iterator to compare with this iterator
     @return true if this iterator and b are equal
     */
    bool equals(Iterator b) const;

    /* Overloaded Operators */
    bool operator==(const Iterator& b) const;
    bool operator!=(const Iterator& b) const;
    Iterator operator++(int unused); //postfix
    Iterator& operator++(); //prefix
    Iterator operator--(int unused); //postfix
    Iterator& operator--(); //prefix
    int operator*() const;

private:
    Node* position;
    ListInt* container;
    friend class ListInt;
};

Node::Node(int s)
{
    data = s;
    previous = NULL;
    next = NULL;
}

ListInt::ListInt()
{
    first = NULL;
    last = NULL;
}

ListInt::~ListInt()
{

    if (!empty()) // if the list is nonempty
    {

        Node* node = this->first;

        while (node->next != NULL)
        {
            node = node->next; // jump to the next one

            delete node->previous; // deleting the memory for previous
        }

        if (node->next == NULL) // reaching the last node
        {
            delete node;
        }
    }

}

bool ListInt::empty()
{
    return (last == NULL);
}

void ListInt::push_back(int data)
{
    Node* new_node = new Node(data);
    if (last == NULL) // List is empty
    {
        first = new_node;
        last = new_node;
    }
    else
    {
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
}



// TODO: ListInt selection_sort

/** member function selection_sort that sorts the elements
of the ListInt using selection sort algorithm */
/** gets the position of the smallest element in linked list*/
Iterator min_position(Iterator from, Iterator to)
{
    Iterator min_pos = from;
    Iterator pos = from;
    ++pos;
    for(Iterator it = pos; it != to; it++){
        if(*it < *min_pos) min_pos = it;
    }
    return min_pos;
}

void ListInt::selection_sort()
{
    Iterator pos1;
    Iterator pos2;
    pos1.position = this->first;
    pos1.container = this;
    pos2.position = this->last;
    pos2.container = this;

    for(; pos1 != pos2; pos1++){
        // Find the position of the minimum
        Iterator min_pos = min_position(pos1, pos2);
        if(min_pos != pos1){
            swap_nodes(min_pos, pos1);
        }
    }
}

void ListInt::insert(Iterator iter, int s)
{
    if (iter.position == NULL)
    {
        push_back(s);
        return;
    }

    Node* after = iter.position;
    Node* before = after->previous;
    Node* new_node = new Node(s);
    new_node->previous = before;
    new_node->next = after;
    after->previous = new_node;
    if (before == NULL) // Insert at beginning
        first = new_node;
    else
        before->next = new_node;
}

Iterator ListInt::erase(Iterator iter)
{
    assert(iter.position != NULL);
    Node* remove = iter.position;
    Node* before = remove->previous;
    Node* after = remove->next;
    if (remove == first)
        first = after;
    else
        before->next = after;
    if (remove == last)
        last = before;
    else
        after->previous = before;
    delete remove;
    Iterator r;
    r.position = after;
    r.container = this;
    return r;
}

Iterator ListInt::begin()
{
    Iterator iter;
    iter.position = first;
    iter.container = this;
    return iter;
}

Iterator ListInt::end()
{
    Iterator iter;
    iter.position = NULL;
    iter.container = this;
    return iter;
}


Iterator::Iterator()
{
    position = NULL;
    container = NULL;
}

Iterator::Iterator(const Iterator & pos)
{
    (*this) = pos;
}

int Iterator::get() const
{
    assert(position != NULL);
    return position->data;
}

void Iterator::next()
{
    assert(position != NULL);
    position = position->next;
}

void Iterator::previous()
{
    assert(position != container->first);
    if (position == NULL)
        position = container->last;
    else
        position = position->previous;
}

bool Iterator::equals(Iterator b) const
{
    return position == b.position;
}

bool Iterator::operator==(const Iterator& b) const
{
    return position == b.position;
}

bool Iterator::operator!=(const Iterator& b) const
{
    return position != b.position;
}

Iterator & Iterator::operator++() // prefix
{
    assert(position != NULL);
    position = position->next;
    return *this;
}

Iterator Iterator::operator++(int unused) // postfix
{
    assert(position != NULL);

    Iterator clone(*this);

    position = position->next;

    return clone;
}


Iterator & Iterator::operator--() //prefix
{

    assert(position != container->first);
    if (position == NULL)
        position = container->last;
    else
        position = position->previous;

    return *this;
}

Iterator Iterator::operator--(int unused)
{

    assert(position != container->first);

    Iterator clone(*this);

    if (position == NULL)
        position = container->last;
    else
        position = position->previous;

    return clone;
}


int Iterator::operator*() const
{
    assert(position != NULL);
    return position->data;
}

// TODO: ListInt swap_nodes
/** member function swap_nodes that swaps the nodes
    to which the iterator it1 and it2 point to */
void ListInt::swap_nodes(Iterator it1, Iterator it2)
{
    Node* pos1 = it1.position;
    Node* pos2 = it2.position;
    Node* prev1 = it1.position->previous;
    Node* next1 = it1.position->next;
    Node* prev2 = it2.position->previous;
    Node* next2 = it2.position->next;

    if(pos1->next == pos2){
        pos1->next = next2;
        pos2->previous = prev1;
    }

    if(prev1!=NULL)
        prev1->next = pos2;
    
    if(next1!=NULL)
        next1->previous = pos2;
    
    if(prev2!=NULL)
        prev2->next = pos1;
    
    if(next2!=NULL)
        next2->previous = pos1;

    pos1->previous = prev2;
    pos1->next = next2;
    pos2->previous = prev1;
    pos2->next = next1;



    // if (it1.position == it2.position)
    //    return;
    // if (it1.position->next == it2.position) { // right next to each other
    //     it1.position->next = it2.position->next;
    //     it2.position->previous = it1.position->previous;

    //     if (it1.position->next != NULL)
    //         it1.position->next->previous = it1.position;

    //     if (it2.position->next != NULL)
    //         it2.position->previous->next = it2.position;

    //     it2.position->next = it1.position;
    //     it1.position->previous = it2.position;

    // } else {
    //     Node* p = it2.position->previous;
    //     Node* n = it2.position->next;

    //     it2.position->previous = it1.position->previous;
    //     it2.position->next = it1.position->next;

    //     it1.position->previous = p;
    //     it1.position->next = n;

    //     if (it2.position->next != NULL)
    //         it2.position->next->previous = it2.position;
    //     if (it2.position->previous != NULL)
    //         it2.position->previous->next = it2.position;

    //     if (it1.position->next != NULL)
    //         it1.position->next->previous = it1.position;
    //     if (it1.position->previous != NULL)
    //         it1.position->previous->next = it1.position;
    // }
}

// TODO:
/** reads the list of integers from the file data1.txt into a ListInt and then
 sort the elements of the list using the member function selection sort(). */

int main() {

    ListInt l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    Iterator it1;
    Iterator it2;

    it1=l.begin();
    it2=l.begin();
    
    it1++;
    it2++;
    it2++;
    it2++;

    cout << endl;

    cout << *it1 << " " << *it2 << endl;

    cout << "before: " << endl;
    
    for(Iterator p=l.begin(); p!=l.end(); p++)
    { cout << *p << " ";}

    l.swap_nodes(it1, it2);

    cout << "\nafter swapping: " << endl;
    for(Iterator p=l.begin(); p!=l.end(); p++)
    { cout << *p << " ";}

    cout << endl;

    // ifstream infile("data1.txt");
    // string line;
    // ListInt num;

    // merge sort
    // binary sort

    // while(getline(infile, line)){
    //     int n;
    //     istringstream(line) >> n;
    //     num.push_back(n);
    // }

    // // print ListInt before sorting
    // cout << "Iterating through the list in data1.txt: \n" << endl;
    // for(Iterator it = num.begin(); !it.equals(num.end()); ) {
    //     cout << *it;
    //     ++ it;
    //     if(it.equals(num.end())) {
    //         cout << "\n" << endl;
    //         break;
    //     }
    //     else cout << "->";
    // }

    // // sort ListInt using selection sorting
    // num.selection_sort();

    // // print ListInt after sorting
    // cout << "Sorted list:" << endl;
    // for(Iterator it = num.begin(); !it.equals(num.end()); ) {
    //     cout << *it;
    //     ++ it;
    //     if(it.equals(num.end())) {
    //         cout << "\n" << endl;
    //         break;
    //     }
    //     else cout << "->";
    // }
    // system("pause");
    return 0;
}
