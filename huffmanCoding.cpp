#include "huffman.h"
#include <iostream>
#include <sstream>

//QUESTION 1 - 0 credit


HuffmanTree::HuffmanHeap::HuffmanHeap(istream &instr) {
    // start with an empty map
    map<string, unsigned int> associate;
    // ----
    // use a the input stream with a string to read every word one by one
    string g;
    // read every word one by one
    while(instr >> g) {
        // if the word was already seen, increment the count. Otherwise, initialized it at 1
        if (associate.find(g) != associate.end()) {
            associate[g]++;
        }else {
            associate[g] = 1;
        }
    }
    
    // insert every word in the heap
    for(auto &ada : associate) {
        auto tn = new TreeNode(ada.first);
        this->push(tn, ada.second);
    }
}


void HuffmanTree::HuffmanHeap::pop() {
    if(content.size() <= 1) return;
    auto newpriority = content[0]->priority;
    auto tn1 = *(content[0]->data);
    Heap::pop();
    newpriority += content[0]->priority;
    auto tn2 = *(content[0]->data);
    Heap::pop();
    auto tn = new TreeNode(tn1, tn2);
    Heap::push(tn, newpriority);
}



// QUESTION 2
void HuffmanTree::dfs(HuffmanCode& hc, TreeNode *tn, string &s) {

    
    //Map to keep track of visited
    
    map<TreeNode*, int> vm; //VISITED MAP
    string runningCode = s;
    
    
    vm.insert(pair<TreeNode*, int>(tn, 1)); //Mark node as visited by adding it to the visitedmap
    
    //cout << "DEBUG: (printing vm[tn]): " << vm[tn] << endl;
    
    if(tn->word != nullptr){ //Check if leaf
        hc.insert(pair<string, string>(*(tn->word),runningCode)); //Associate code
    }
    
    //-----DFS Recursion
    
    for(auto i = 0; i <= 1; ++i){
        
        
        if(tn->children[i] != nullptr){
        
            if(vm[tn->children[i]] != 1){
                runningCode = s + to_string(i); //append to string
                dfs(hc, tn->children[i], runningCode); //recursive step
                
                if(runningCode.size() > 0){ //erase last character of string
                    runningCode.resize(runningCode.size() - 1);
                }
            }
            
        }
    
    
    
    }
     
    
    
    
}

//QUESTION 3


HuffmanCode::HuffmanCode(istream &input) {
    
    string getlineStr;
    string inputWord;
    string inputHuffCode;
    string oneWord;

    while(getline(input, getlineStr)){
        
        //string into stringstream
        istringstream stream1(getlineStr);
        vector<string> vc;
        unsigned int count = 1;
        

        while(stream1 >> oneWord){
            
            //-----input validation-------
            
        //input validation (# of params)
            vc.push_back(oneWord); //add to vector
            
            if(count > 2){
                cout << "Error 0: Too many params!" << endl;
                throw 0; //exception too many params
            }
            
            count++;

            
        }
        
        //check HuffmanCoding formatting
        string checkformat = vc.at(1); //Huffman code
        for(auto j = 0; j < checkformat.length(); ++j){
            if(checkformat[j] != '0' && checkformat[j] != '1'){
                cout << "Error 0: Incorrect HuffmanCode format - something is not a 0 or a 1." << endl;
                throw 0; //exception: formatting
            }
        }
        
        //-----end input validation----
        
        this->insert(pair<string, string>(vc.at(0),vc.at(1)));

    }

}


//QUESTION 4

HuffmanTree::HuffmanTree(const HuffmanCode &hc) {
    
    //example entry: <hello, 110>
    
    HuffmanCode hcmap = hc; //Copy input map just in case
    this->root = new TreeNode; //initialize root
    
    //strategy: build entire tree first, and then go through and add shit.
    
    for(auto entry : hcmap) {
        
        resetIterator();
        
        //cout << "debug hcmap contents: " << entry.first << entry.second << endl;
        //cout << "second entry length: " << entry.second.length() << endl;
        
        for(int i = 0; i < entry.second.length(); i++){
            if(entry.second[i] == '1'){ //Huffcode bit is 1
                if(iter->children[1] == nullptr){ //if there does not exist a child
                    
                    if(i == entry.second.length() - 1){ //if exhausted code
                        if(iter->children[1] != nullptr){
                            cout << "Error 1: Is not a prefix code." << endl;
                            throw 1;
                        } else {
                            iter->children[1] = new TreeNode(entry.first);
                        }

                    } else {
                        TreeNode* node = new TreeNode(); //then create a tree node as child
                        iter->children[1] = node;
                        moveDownOnOne();
                    }
                    
                    
                } else moveDownOnOne();
                
            }
            
            if(entry.second[i] == '0'){ //Huffcode bit is 0
                if(iter->children[0] == nullptr){ //if there does not exist a child
                    
                    if(i == entry.second.length() - 1){ //if exhausted code
                        if(iter->children[0] != nullptr){
                            cout << "Error 1: Is not a prefix code." << endl;
                            throw 1;
                        } else {
                            iter->children[0] = new TreeNode(entry.first);
                        }
                    } else {
                        TreeNode* node = new TreeNode(); //then create a tree node as child
                        iter->children[0] = node;
                        moveDownOnZero();
                    }
                    
                } else moveDownOnZero();
                
            }
            
            
            if(entry.second[i] != '0' && entry.second[i] != '1'){ //Huffcode bit is INVALID (i.e., not 1 or 0)
                cout << "Error 2: A Huffman Code is invalid: contains x that is not 0 or 1" << endl;
                throw 2;
            }
            

        }
        
        //iter->children[i]= new TreeNode(entry.first);
        
        //cout << entry.first << "%%" << entry.second << endl;
        
            
    }

    
}

// QUESTION 5

void HuffmanEncoder::encode(istream &fin, ostream &fout) const {
    
    string dict;
    string ss;
    while(getline(fin, ss)){
        dict = dict + ss;
    }
    
    //cout << "DEBUG string: " << dict << endl;
    
    istringstream stream1(dict);
    
    HuffmanTree newTree(stream1); //Make Huffman tree out of input stream
    HuffmanCode hc; //Map of codes
    hc = newTree.getCode();
    string word;
    
    /* for(auto entry : hc) {
        cout << "DEBUG: " << entry.first << " " << entry.second << endl;
    } */
    
    
    istringstream stream2(dict);
    
    while(stream2 >> word){
        if(hc.count(word) != 1){
            cout << "Error 1: Word from istream not contained in dictionary.";
            throw 1;
        }
        fout << hc[word];
    }
    
}


//QUESTION 5

void HuffmanDecoder::push(istream &f) {

    string str; //Store stream
    HuffmanCode hc = this->getCode(); //Get Huffmancode Map
    getline(f, str);
    int position = 0;
    int substrlen = 1;
    int found = 0; //For error throw
    
    //Sequence Validation
    for (int i = 0; i < str.length(); i++) {
        if (!(str[i] == '0') && !(str[i] == '1')) {
            cout << "Error 0: Invalid sequence: contains an x that is neither 0 nor 1." << endl;
            throw 0; //Error: Invalid sequence
        }
    }
    
    while (position + substrlen <= str.length()) {
        string segment = str.substr(position, substrlen);
        
        map<string, string>::iterator it; //initialize map iterators (old school)
        for (it = hc.begin(); it != hc.end(); ++it) {
            if (it->second == segment) {
                savedWords.push(&(it->first)); //Found match, push the first
                position += substrlen; //Move cursor by length
                substrlen = 0;
                found++; //Up the found
                break;
            }
        }
        
        substrlen++;
    }
    
    if(found == 0){
        cout << "Error 0: Word not fully completed." << endl;
        throw 1; //Word not fully completed error.
    }
    
    
}

