#include "heaps.h"
#include <queue>

using namespace std;

Heap *heapFromArray(string *input, int length) {

	//Create Heap-POINTER array (dynamically)
	Heap** nodeAddressArray = new Heap*[length]; 

    //Assign addresses to pointers in the array
    for(int i = 0; i < length; i++){

    	Heap* node = new Heap;
    	nodeAddressArray[i] = node;

    } 

    //Set children-relations via array (i.e., set Heap*->right / Heap*->left addresses)
    for(int i = 0; i < length; i++){

    	//Set 'name' data
    	nodeAddressArray[i]->name = input[i]; 

    	//Array index/memory address in/out of bounds validation 
    	if( ((2*i)+1) <= length){ //Array index validation - left right children
    		nodeAddressArray[i]->left = nodeAddressArray[(2*i)+1]; //set left child
    	}
    	if( ((2*i)+2) < length){ //Array index validation - right children
    		nodeAddressArray[i]->right = nodeAddressArray[(2*i)+2]; //set right child
    	}
 
    }

    return nodeAddressArray[0]; //Return pointer to root of heap
}

int sizeOf(Heap* p) { //numElements helper function
//Take in a heap pointer, and then recursion for count
    
    if(p != nullptr){
        return(sizeOf(p->right) + 1 + sizeOf(p->left)); //Recursion algorithm # of nodes
    }
    
    return 0;
}

int numElements(Heap h) {

  Heap* rootptr = &h; //Take address of heap, assign to pointer, then pass to helper fn
  return sizeOf(rootptr);
}

size_t ctlength(Heap* p) { //Content length helper function
    
    if(p != nullptr){
        return(ctlength(p->right) + p->name.size() + ctlength(p->left)); //recursion, tally size() of name data 
    }
    
    return 0;
}

size_t lengthOfContent(Heap h) {

    Heap* ctptr = &h; //Take address of heap and assign to pointer, pass ptr to helper fn
    return ctlength(ctptr);

}


/* might want to do this for Q5
Heap **returnAllHeaps(Heap h) {
    //your code here
}*/

string *printLinear(Heap h) {
    
    int n = numElements(h); //Get size of heap
    int i = 0; //Counter
    string* stringArray = new string[n]; //Create string array
    
    Heap* root = &h; //Get address of heap, then assign to pointer
    if(root == nullptr) return nullptr; 
    
    queue<Heap*> Q; //Create new queue data structure, Q, to keep track of level order traversal
    Q.push(root); 
    while(!Q.empty()){
        Heap* current = Q.front();
        if (i < n){
            stringArray[i] = current->name; //Assign string to array
            i++; //Increase counter to iterate through array
        }
        //cout << current->data<<" "; (PRINTS DIRECTLY for DEBUGGING)
        if(current->left != nullptr) Q.push(current->left);
        if(current->right != nullptr) Q.push(current->right);
        Q.pop();
    }
    return stringArray; //Return the array of strings

}


string printPretty(Heap h) { 

    string* uglyStringArray = printLinear(h);    
    string prettyString; //String to be returned    
    string spaces; //String of empty spaces
    int length = numElements(h);
    
    for(int k = 0; k < length; k++){
        
    	if( ((2*k)+1) <= length){ // Left validation 
     		for(int k = 0; k < uglyStringArray[(2*k)+1].size(); k++){ //Left spaces
            	spaces.append(" ");
        	}
    	}

        prettyString.append(spaces);
        spaces = "";
        prettyString.append(uglyStringArray[k]);

        if( ((2*k)+2) < length){ /////
	        for(int k = 0; k < uglyStringArray[(2*k)+2].size(); k++){ //Right spaces
	            spaces.append(" ");
	        }
    	}
        
        prettyString.append(spaces); //Append spaces to retunred string (prettyString)
        spaces = ""; //Reset var spaces to have no spaces
        
        if(k == 0 || k == 2 || k == 6 || k == 13 || k == 30){ 
            prettyString.append("\n");
            
        }
        
    }
    
    return prettyString;

}
