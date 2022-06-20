//
//  MemberDatabase.cpp
//  CS32Project4
//
//  Created by Yiqu on 3/8/22.
//

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "RadixTree.h"
#include "MemberDatabase.h"
#include "math.h"

//The member database constructor.
MemberDatabase:: MemberDatabase()
{}

//A destructor for MemberDatabase
MemberDatabase:: ~MemberDatabase()
{}

std::vector<std::string> MemberDatabase::split(std::string &str, const std::string &pattern){
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

//Loads the member database from the data file.
bool MemberDatabase::LoadDatabase(std::string filename){
    std::ifstream inFile;
    inFile.open(filename);
    
    if (!inFile) {
        std::cerr << "Unable to open " << filename << std::endl;
        return false;   // call system to stop
    }
    
    //Read data from file
    std:: string Line;
    std::vector<std::string> tempData;
    while (getline(inFile, Line) ) {
        std::string line = Line;
        std::string name, email, attvalnum, attval;
        int NumAV;
        if (line.find(" ")) {
            name = line;
            getline(inFile, Line);
            email = Line;
            PersonProfile* newPerson = new PersonProfile(name, email);
            getline(inFile, Line);
            attvalnum = Line;
            NumAV = StringToInt(attvalnum);
            for (int i = 0; i < NumAV; i++) {
                getline(inFile, Line);
                std::vector<std::string> res = split(Line, ",");
                AttValPair* newAttValPair = new AttValPair(res[0], res[1]);
                newPerson->AddAttValPair(*(newAttValPair));
            }
            getline(inFile, Line);
            Database.insert(newPerson->GetEmail(), *(newPerson));
            v_db.push_back(newPerson);
        }
        }
    
    inFile.close();
    return true;
}

int MemberDatabase::StringToInt(std::string str){
    int res = 0;
    for (int i = 0; str.length() > 0; i++) {
        res += pow(10, i) * (str[str.length()-1] - '0');
        str = str.substr(0, str.length()-1);
    }
    
    return res;
}

//Identify all members that have the specified input attribute-value pair and return a vector
//containing their email addresses.
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::vector<std::string> res;
    for (int i = 0; i < v_db.size(); i++) {
        AttValPair attval;
        for (int j = 0; j < v_db[i]->GetNumAttValPairs(); j++) {
            v_db[i]->GetAttVal(j, attval);
            if (attval == input) {
                res.push_back(v_db[i]->GetEmail());
                continue;
            }
        }
    }
    return res;
}

//This method must determine if a member exists in the database with that email address
//and if so, a pointer to that member’s PersonProfile that is held in your MemberDatabase object;
//if there is no such member, this method returns nullptr
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    PersonProfile* m_pf = Database.search(email);
    if (m_pf != nullptr) {
        return m_pf;
    }
    return nullptr;
}
