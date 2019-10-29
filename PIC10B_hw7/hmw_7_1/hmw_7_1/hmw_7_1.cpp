//
//  main.cpp
//  hmw_7_1
//
//  Created by Rui Yan on 2019/3/14.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// This class implements a heap (heap-tree).

class HeapTasks
{
public:
    
    HeapTasks(); // Constructs an empty heap.
    
    void push(pair<string, int> new_element); // Adds a new element to this heap.
    
    pair<string, int> top() const; //Gets the maximum element stored in this heap.
    
    void pop(); //Removes the maximum element from this heap.
    
    int size() const; // Returns the number of elements in this heap.
    
public:
    /** Turns the tree back into a heap, provided only the root
     node violates the heap condition. */
    void fix_heap(); //Heapify is the process of converting a binary tree into a Heap data structure.
    
    /**
     Returns the index of the left child.
     @param index the index of a node in this heap
     @return the index of the left child of the given node
     */
    int get_left_child_index(int index);
    
    /**
     Returns the index of the right child.
     @param index the index of a node in this heap
     @return the index of the right child of the given node
     */
    int get_right_child_index(int index);
    
    /**
     Returns the index of the parent.
     @param index the index of a node in this heap
     @return the index of the parent of the given node
     */
    int get_parent_index(int index);
    
    /**
     Returns the value of the left child.
     @param index the index of a node in this heap
     @return the value of the left child of the given node
     */
    pair<string, int> get_left_child(int index);
    
    /**
     Returns the value of the right child.
     @param index the index of a node in this heap
     @return the value of the right child of the given node
     */
    pair<string, int> get_right_child(int index);
    
    /**
     Returns the value of the parent.
     @param index the index of a node in this heap
     @return the value of the parent of the given node
     */
    pair<string, int> get_parent(int index);
    
    vector< pair<string, int> > elements;
};

HeapTasks::HeapTasks()
{
    elements.push_back(make_pair("",0));
}

void HeapTasks::push(pair<string, int> new_element)
{
    // Add a new leaf
    elements.push_back(make_pair("",0));
    int index = elements.size() - 1;
    
    // Demote parents that are smaller than the new element
    while (index > 1 && get_parent(index).second < new_element.second)
    {
        elements[index] = get_parent(index);
        index = get_parent_index(index);
    }
    
    // Store the new element into the vacant slot
    elements[index] = new_element;
}

pair<string, int> HeapTasks::top() const
{
    return elements[1];
}

void HeapTasks::pop()
{
    // Remove last element
    int last_index = elements.size() - 1;
    pair<string, int> last = elements[last_index];
    elements.pop_back();
    
    if (last_index > 1)
    {
        elements[1] = last;
        fix_heap();
    }
}

int HeapTasks::size() const
{
    return elements.size() - 1;
}

void HeapTasks::fix_heap()
{
    pair<string, int> root = elements[1];
    
    int last_index = elements.size() - 1;
    // Promote children of removed root while they are larger than last
    
    int index = 1;
    bool more = true;
    while (more)
    {
        int child_index = get_left_child_index(index);
        if (child_index <= last_index)
        {
            // Get larger child
            
            // Get left child first
            pair<string, int> child = get_left_child(index);
            
            // Use right child instead if it is larger
            if (get_right_child_index(index) <= last_index
                && get_right_child(index).second > child.second)
            {
                child_index = get_right_child_index(index);
                child = get_right_child(index);
            }
            
            // Check if smaller child is larger than root
            if (child > root)
            {
                // Promote child
                elements[index] = child;
                index = child_index;
            }
            else
            {
                // Root is larger than both children
                more = false;
            }
        }
        else
        {
            // No children
            more = false;
        }
    }
    
    // Store root element in vacant slot
    elements[index] = root;
}

int HeapTasks::get_left_child_index(int index)
{
    return 2 * index;
}

int HeapTasks::get_right_child_index(int index)
{
    return 2 * index + 1;
}

int HeapTasks::get_parent_index(int index)
{
    return index / 2;
}

pair<string, int> HeapTasks::get_left_child(int index)
{
    return elements[2 * index];
}

pair<string, int> HeapTasks::get_right_child(int index)
{
    return elements[2 * index + 1];
}

pair<string, int> HeapTasks::get_parent(int index)
{
    return elements[index / 2];
}

int main()
{
    bool ctnue = true;
    string ctnuestr;
    HeapTasks tasks;

    
    while (ctnue) {

        // ask for filename
        string filename;
        cout << "Enter the file name containing tasks: ";
        getline(cin, filename);
        string line;
        ifstream in (filename.c_str());
    
        cout << "\nDisplaying uploaded list of tasks (before heap): " << endl;
        
        if(in.is_open()) {
            while(getline(in, line)) {
                stringstream ss(line);
                string field_val;
                string taskname;
                int priority;
                int counter = 0;
                while(getline(ss, field_val, '|')){
                    if(counter==0) taskname = field_val;
                    if(counter==1) istringstream(field_val) >> priority;
                    counter ++;
                }
                tasks.push(make_pair(taskname, priority));
                cout << line << endl;
            }
        }

        cout << "\nDisplaying uploaded list of tasks (before heap): " << endl;
        
        while (tasks.size() > 0)
        {
            pair<string, int> task = tasks.top();
            tasks.pop();
            cout << task.first << "|" << task.second << endl;
        }
        
        // ask if continue
        cout << endl;
        cout << "Continue <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(256, '\n');
        cout << endl;
        if(ctnuestr == "n") ctnue = false;
    }
    return 0;
}
