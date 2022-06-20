//
//  MemberDatabase.h
//  CS32Project4
//
//  Created by Yiqu on 3/8/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

class MemberDatabase {
public:
    //The member database constructor.
    MemberDatabase();
    
    //A destructor for MemberDatabase
    ~MemberDatabase();
    
    //Loads the member database from the data file.
    bool LoadDatabase(std::string filename);
    
    //Identify all members that have the specified input attribute-value pair and return a vector
    //containing their email addresses.
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    
    //This method must determine if a member exists in the database with that email address
    //and if so, a pointer to that member’s PersonProfile that is held in your MemberDatabase object;
    //if there is no such member, this method returns nullptr
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
private:
    std::vector<std::string> split(std::string &str, const std::string &pattern);
//    void ReadData(std::vector<std::string> tempData, int count);
    int StringToInt(std::string str);
    //RadixTree<std::string, PersonProfile> Database;
    RadixTree<std::string, PersonProfile> Database;
    std::vector<PersonProfile*> v_db;
};

#endif /* MemberDatabase_h */
