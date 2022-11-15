//Student 1: Sri Sai Koushik Yaganti, U65258662
//Student 2: Karthik Yechuri, U51358914

#include "HuffmanTree.hpp"

using namespace std;


void HuffmanTree::encode(HuffmanNode* root, string str, map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->getCharacter()] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

string HuffmanTree::postorder(HuffmanNode* root)const
{
    string ser = "";    

    if(root->isLeaf()){
        ser += 'L';
        ser += root->getCharacter();
        return ser;
    }
    else{
        ser += postorder(root->left) + postorder(root->right) + 'B';
        return ser;
    }
}

HuffmanNode *HuffmanTree::decode(const string serial) const{
    size_t freq;
    stack<HuffmanNode*> tree;

    string::const_iterator itr = serial.begin();
    while(itr != serial.end()){
        if(*itr == 'L'){
            itr++;
            HuffmanNode *node = new HuffmanNode(*itr, 0);
            tree.push(node);
        }
        else{
            HuffmanNode *rightnode = tree.top();
            tree.pop();
            HuffmanNode *leftnode = tree.top();
            tree.pop();
            freq = rightnode->getFrequency() + leftnode->getFrequency();
            HuffmanNode *parent = new HuffmanNode('\0', freq, nullptr, leftnode, rightnode);

            tree.push(parent);
        }
        itr++;
        
    }

    return tree.top();
}


string HuffmanTree::compress(const std::string inputStr){
    // count frequency of appearance of each character
	// and store it in a map
	map<char, int> freq;
	for (unsigned int i = 0; i < inputStr.length(); i++) {
        char ch = inputStr[i];
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
    map<char, int>::iterator itr;

	for (itr = freq.begin(); itr != freq.end(); ++itr) {  
        HuffmanNode *p = new HuffmanNode(itr->first, itr->second);
		pq.insert(p);
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		HuffmanNode *left = pq.min(); 
        pq.removeMin();
		HuffmanNode *right = pq.min(); 
        pq.removeMin();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->getFrequency() + right->getFrequency();
        HuffmanNode *q = new HuffmanNode('\0', sum, nullptr, left, right);
		pq.insert(q);
	}

	// root stores pointer to root of Huffman Tree
	HuffmanNode* parent = pq.min();

    root = parent;
    
	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	map<char, string> huffmanCode;
	encode(parent, "", huffmanCode);

    map<char, string>::iterator qtr;

	// print encoded string
	string str = "";
	for (unsigned int i = 0; i < inputStr.length(); i++) {
        char ch = inputStr[i];
		str += huffmanCode[ch];
	}


    return str;
}


string HuffmanTree::serializeTree() const{
    
    return postorder(root);

}

string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    string initialstr = "";//Decoded string

    HuffmanNode *dectree  = decode(serializedTree);
    HuffmanNode *decnode = root;

    string::const_iterator itr = inputCode.begin();
    while(itr != inputCode.end()){
        if(*itr == '0'){
            decnode = decnode->left;
            if((decnode->left == nullptr)&&(decnode->right)==nullptr){
                initialstr = initialstr + decnode->getCharacter();
                decnode = dectree;
            }
        }
        else{
            decnode = decnode->right;
            if((decnode->left == nullptr)&&(decnode->right)==nullptr){
                initialstr = initialstr + decnode->getCharacter();
                decnode = dectree;
            }
        }
        itr++;
    }
    return initialstr;

}