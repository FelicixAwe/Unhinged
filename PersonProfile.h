//
//  PersonProfile.h
//  CS32Project4
//
//  Created by Yiqu on 3/6/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include "RadixTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

class PersonProfile {
public:
    //constructs a PersonProfile object, specifying the member’s name and email address
    PersonProfile(const std::string name, const std::string email);
    
    //PerosonProfile constructor.
    ~PersonProfile();
    
    //Returns member's name.
    std::string GetName() const;
    
    //Returns the member’s email address.
    std::string GetEmail() const;
    
    //Add a new attribute-value pair to the member’s profile
    void AddAttValPair(const AttValPair& attval);
    
    //Returns the total number of distinct attribute-value pairs associated with this
    //member.
    int GetNumAttValPairs() const;
    
    //This method gets the attribute-value pair.
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    std::string m_name = "";
    std::string m_email;
    int NumAttValPairs;
    std::vector<AttValPair*> m_Pair;
    RadixTree<std::string, std::set<std::string>> m_AttPair;
//    RadixTree<std::string, std::set<std::string>> m_AttPair;
    //RadixTree<std::string, std::list<std::string>> m_AttPair;
    //RadixTree<std::string, std::string []> m_AttPair;
    //std::vector<AttValPair*> m_AttPair;
    //Helper function to check if the attval is already existed.
    bool searchAtt(const AttValPair& attval);
};


#endif /* PersonProfile_h */
