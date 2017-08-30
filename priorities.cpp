//QUESTION 1

#include "priorities.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <map>


//QUESTION 1

Heap::Heap(const vector<string> & dataToAdd) {
    
    for(unsigned int i = 0; i < dataToAdd.size(); i++){
        
        //Node n = {i, dataToAdd.at(i)}; //Create node to push
        
        this->push(dataToAdd.at(i), i);
        //content.push_back(n); //Push node directly into vector<Node>
        
    }
    
}

Heap::Heap(const Heap& h) { //COPY CONSTRUCTOR

    
    //Loop for deep-copy
    //Iterate through h, create new node, then push node into this->vector(Node)
    for(unsigned int i = 0; i < h.content.size(); i++){ //Safer version
        Node n = {h.content.at(i).priority, h.content.at(i).data};
        this->content.push_back(n);
    }
    
    
}

//Question 2

size_t Heap::lengthOfContent(unsigned long index) const {
    
    size_t length = content.at(index).data.length(); //Store length for node @ index
    
    //Recursive left and right trees
    if((2*index+1) < content.size()){
        length += lengthOfContent(2*index+1);
        
        if((2*index+2) < content.size()){
            length += lengthOfContent(2*index+2);
        }
        
    }
    
    return length;
    
}


ostream &operator<<(ostream & out, const Heap& h) { //PrettyPrint()
    string str="";
    unsigned long numSpace=0;
    int element2Do=1;
    int elementDone=0;
    for(int index=0;index<h.content.size();index++){
        //print left child node space
        if(2*index+1<h.content.size()){
            numSpace=h.lengthOfContent(2*index+1);
            for(int sp=0;sp<numSpace;sp++){
                str+=" ";
            }
        }
        //print data of node
        str+=h.content.at(index).data;
        
        //print right child node space
        if(2*index+2<h.content.size()){
            numSpace=h.lengthOfContent(2*index+2);
            for(int sp=0;sp<numSpace;sp++){
                str+=" ";
            }
        }
        elementDone++;
        //print next line or right child
        if(element2Do==elementDone){
            element2Do*=2;
            elementDone=0;
            str+="\n";
        }else{
            int kid=index;
            while(kid%2==0){
                kid=(kid-1)/2;//go to parent
            }
            unsigned long parent=(kid-1)/2;
            numSpace=h.content.at(parent).data.length();
            for(int sp=0;sp<numSpace;sp++){
                str+=" ";
            }
            
        }
        
    }
    
    out<<str;
    return out;
}

//QUESTION 3

vector<string> Heap::printLinear() const{
    
    vector<string> v; //Create new vector of strings
    
    for(int i = 0; i < content.size(); i++){ //loop through to create new strings
        
        string item = "(" + content.at(i).data + ", " + to_string(content.at(i).priority) + ")";
        v.push_back(item); //push string into vector<string>
    }

    return v;

}



//QUESTION 4

unsigned int Heap::operator[](string s) const{
    
    //If string matches node data, then return priority. Cycle through elements of CONTENT.
    for(int i = 0; i < content.size(); i++){
        if (content.at(i).data == s){ //match check
            return content.at(i).priority; //return priority
        }
        
    }
    
    return 0; //return 0 if nothing found
}


//QUESTION 5

unsigned long getParentIndex(unsigned long i){ //getParentIndex CUSTOM HELPER FUNCTION
    unsigned long parentIndex;
    parentIndex = ((i - 1)/2);
    return parentIndex;
}

void Heap::heapifyUp(unsigned long index) { //HeapifyUp ALGORITHM
    
    unsigned long parentIndex;
    
    if (index != 0) {
        parentIndex = getParentIndex(index);
        if (content.at(parentIndex).priority > content.at(index).priority) {
            swap(content.at(parentIndex), content.at(index)); //use swap function given
            heapifyUp(parentIndex);
        }
    }
    
    
}


void Heap::push(string data, unsigned int priority) { //INSERT METHOD
    
    Node n = {priority, data}; //Make new node, n.
    content.push_back(n); //push n into the heap's content vector
    unsigned long nindex = content.size()-1; //get index of new pushed node, n
    
    heapifyUp(nindex);
    
    
}


Heap& Heap::operator+=(const Heap& h) {
    
    int duplicate = 0; //duplicate flag
    
    for(unsigned int i = 0; i < h.content.size(); i++){ //loop for every element in input heap, h
        
        for(unsigned int k = 0; k < this->content.size(); k++){ //inner loop to check duplicature
            if(h.content.at(i).data == this->content.at(k).data){
                duplicate = 1;
                break;
            }
            duplicate = 0;
        }
        
        if(duplicate == 0){//duplicate check
            push(h.content.at(i).data, h.content.at(i).priority);
        }
    }
    
    return *this;

}



// QUESTION 6

void Heap::heapifyDown(unsigned long index) { //HeapifyDown ALGORITHM
    
    unsigned long leftChildIndex, rightChildIndex, minIndex;
    
    leftChildIndex = (2*index)+1;
    rightChildIndex = (2*index)+2;
    
    if (rightChildIndex >= content.size()) { //break if out of bounds
        if (leftChildIndex >= content.size())
            return;
        else
            minIndex = leftChildIndex;
    } else {
        if (content.at(leftChildIndex).priority <= content.at(rightChildIndex).priority)
            minIndex = leftChildIndex;
        else
            minIndex = rightChildIndex;
    }
    if (content.at(index).priority > content.at(minIndex).priority) {
        swap(content.at(index), content.at(minIndex));
        heapifyDown(minIndex);
    }

}


string Heap::pop() {
    
    string top;
    
    if (empty()){ // used content.size() == 0 before / Now using professor's empty() method.
        return string("Heap is empty\n");
    }
    else {
        top = content.at(0).data; //store data of to-be-popped node
        swap(content.at(0), content.at(content.size() - 1));
        if (content.size() > 0){
            content.pop_back(); //reduction step (eliminate last node)
            heapifyDown(0);
        }
        
    }
    
    return top; //might have to be the old?
    
}


// QUESTION 7

Heap::Heap(istream &in) {
    
    typedef map<string, unsigned int> StrIntMap; //Shortcut for map type
    StrIntMap words; //create map
    
    string s; //count frequency
    while (in >> s){
        ++words[s];
    }
    
    unsigned int max = 1; //set max
    
    for(StrIntMap::iterator i = words.begin(); i != words.end(); ++i){ //iterate through map
        
        for(StrIntMap::iterator p = words.begin(); p != words.end(); ++p){ //loop to find max
            if(p->second > max){
                max = p->second; //set running max
            }
        }
        
        this->push(i->first, (max - i->second)); //push into the heap; i->second is # of times.
        //therefore, max subtracted by i->second equals the priority.

    }
    
    
}

