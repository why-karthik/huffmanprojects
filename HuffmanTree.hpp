//Student 1: Sri Sai Koushik Yaganti, U65258662
//Student 2: Karthik Yechuri, U51358914

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<stack>
#include <map>

using namespace std;


class HuffmanTree {
private: 
    HuffmanNode* root;
public:
  void equals(HuffmanNode *some){root = some;}
  string compress(const std::string inputStr);
  string serializeTree() const;
  string decompress(const std::string inputCode, const std::string serializedTree);
  void encode(HuffmanNode* root, string str, map<char, string> &huffmanCode);
  string postorder(HuffmanNode* root) const;
  HuffmanNode *decode(const string s) const;
};



#endif