//
//  AttricuteTranslator.hpp
//  CS32Project4
//
//  Created by Yiqu on 3/7/22.
//

#ifndef AttricuteTranslator_hpp
#define AttricuteTranslator_hpp

#include <stdio.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <list>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator{
public:
    //This is the AttributeTranslator constructor.
    //It must take no arguments.
    AttributeTranslator();
    
    //A destructor for AttributeTranslator
    ~AttributeTranslator();
    
    //Loads the attribute-value translation data from the data file
    bool Load(std::string filename);
    
    //Identify all compatible attribute-value pairs and return
    //a vector containing them. I
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    std::vector<std::string> split(std::string &str, const std::string &pattern);
    //RadixTree<std::string, std::vector<AttValPair>> AttValTranslate;
    RadixTree<std::string, std::list<AttValPair>> AttValTranslate;
};

#endif /* AttricuteTranslator_hpp */
