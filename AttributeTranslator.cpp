//
//  AttricuteTranslator.cpp
//  CS32Project4
//
//  Created by Yiqu on 3/7/22.
//

#include "AttributeTranslator.h"

//This is the AttributeTranslator constructor.
//It must take no arguments.
AttributeTranslator:: AttributeTranslator()
{}

//A destructor for AttributeTranslator
AttributeTranslator:: ~AttributeTranslator()
{}

//Loads the attribute-value translation data from the data file
bool AttributeTranslator::Load(std::string filename){
    std::ifstream inFile;
    inFile.open(filename);
    
    if (!inFile) {
        std::cerr << "Unable to open " << filename << std::endl;
        return false;   // call system to stop
    }
    
    //Read data from file
    std:: string Line;
    //int count = 0;
    
    while (getline(inFile, Line)) {
//        std::cout << count++ << std::endl;
        std::string line = Line;
        //std::cout << line << std::endl;
        std::vector<std::string> res = split(line, ",");
        if (res.size() != 4) {
            std::cerr << "Attribute Pair error!\n";
        }
        AttValPair *source_attval = new AttValPair(res[0], res[1]);
        AttValPair *target_attval = new AttValPair(res[2], res[3]);
        if (AttValTranslate.search(res[0]+","+res[1]) != nullptr) {
            AttValTranslate.search(res[0]+","+res[1])->push_back(*target_attval);
        }else{
            std::list<AttValPair> val;
            val.push_back(*(target_attval));
            AttValTranslate.insert(res[0]+","+res[1], val);
        }
    }
    inFile.close();
    return true;
}

std::vector<std::string> AttributeTranslator::split(std::string &str, const std::string &pattern){
    std::vector<std::string> res;
    if (str == "") {
        return res;
    }
    
    size_t pos = str.find(pattern);
    while(pos != str.npos)
        {
            std::string temp = str.substr(0, pos);
            res.push_back(temp);
            //去掉已分割的字符串,在剩下的字符串中进行分割
            str = str.substr(pos+1, str.size());
            pos = str.find(pattern);
        }
    //temp = str;
    res.push_back(str);
    return res;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    std::vector<AttValPair> res;
    //AttValPair * avp = AttValTranslate.search(s_avp);
    if (AttValTranslate.search(source.attribute+","+source.value)->size() != 0) {
        //AttValPair *s_avp = *(AttValTranslate.search(s_avp)));
        std::list<AttValPair> * ptr = AttValTranslate.search(source.attribute+","+source.value);
        for (std::list<AttValPair>::iterator iter = ptr->begin(); iter != ptr->end(); iter++) {
            res.push_back(*(iter));
        }
    }
    return res;
}
