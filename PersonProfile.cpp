//
//  PersonProfile.cpp
//  CS32Project4
//
//  Created by Yiqu on 3/6/22.
//

#include <stdio.h>
#include <cassert>
#include "PersonProfile.h"

//constructs a PersonProfile object, specifying the member’s name and email address
PersonProfile::PersonProfile(const std::string name,
                             const std::string email){
    m_name = name;
    //m_email = new EmailCount(email, int count = 1);
    m_email = email;
    NumAttValPairs = 0;
}

//PerosonProfile constructor.
PersonProfile::~PersonProfile(){
//    std::vector<AttValPair*>::iterator iter = m_AttPair.begin();
//    while (iter != m_AttPair.end()) {
//        delete *iter;
//        *iter = nullptr;
//        iter = m_AttPair.erase(iter);
//    }
}

//Returns member's name.
std::string PersonProfile:: GetName() const{
    return m_name;
}

//Returns the member’s email address.
std::string PersonProfile:: GetEmail() const{
    return m_email;
}

//Add a new attribute-value pair to the member’s profile
void PersonProfile::AddAttValPair(const AttValPair& attval){
    AttValPair* new_AttPair = new AttValPair();
    *(new_AttPair) = attval;
    m_Pair.push_back(new_AttPair);
    NumAttValPairs++;
    if (searchAtt(attval) == true) {
       m_AttPair.search(attval.attribute)->insert(attval.value);
        return;
    }
    std::set<std::string> val;
    val.insert(new_AttPair->value);
    m_AttPair.insert(new_AttPair->attribute, val);
}

bool PersonProfile::searchAtt(const AttValPair& attval){
    if (m_AttPair.search(attval.attribute) != nullptr) {
        return true;
    }
    return false;
}

//Returns the total number of distinct attribute-value pairs associated with this
//member.
int PersonProfile::GetNumAttValPairs() const{
    return NumAttValPairs;
}

//This method gets the attribute-value pair.
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if (attribute_num >= GetNumAttValPairs() && m_Pair[attribute_num] != nullptr) {
        return false;
    }
    else{
        attval = *(m_Pair[attribute_num]);
        return true;
    }
}


