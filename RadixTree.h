//
//  RadixTree.h
//  CS32Project4
//
//  Created by Yiqu on 3/8/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <map>

#include<string>
#include <iostream>
// map strings to any data type

// char 1-127

template <typename KeyType, typename ValueType>
class RadixTree {
public:
 // constructor & destructor
 RadixTree() {

 }
 ~RadixTree() {

 }


 // update the Radix Tree to associate the specified key string with a copy of the passed - in value
 // Inserting the same item twice should simply replace value
 //
 void insert(KeyType key, const ValueType& value) {
     m_map.insert({key, value});
     
 }

 //
ValueType* search(KeyType key) const {
    typename std::map<KeyType, ValueType>::const_iterator iter;
     iter = m_map.find(key);
     if (iter == m_map.end()) {
         return nullptr;
     }
     return const_cast<ValueType *>(&(iter->second));
 }
private:
 struct RadixTreeNode {
     std::string word;
     bool endOfWord;
     RadixTreeNode* edges[127];

      RadixTreeNode() {
      word = "";
      endOfWord = false;
      for (int i = 0; i < 127; i++)
          edges[i] = nullptr;
  }
 };

 RadixTreeNode* root;

 std::map<KeyType, ValueType> m_map;
};

#endif /* RadixTree_h */
