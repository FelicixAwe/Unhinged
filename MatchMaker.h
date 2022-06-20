//
//  MatchMaker.h
//  CS32Project4
//
//  Created by Yiqu on 3/8/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker {
public:
    //Constructs a MatchMaker object with the indicated parameters
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    
    //A destructor for MemberDatabase
    //~MemberDatabase();
    
    //Returning a vector of EmailCount objects (a struct we provide in provided.h),
    //each holding the email address of a matching member that has at least the threshold number of compatible attribute-value pairs
    //along with the number of such compatible pairs.
    std::vector<EmailCount> IdentifyRankedMatches(std::string email,
                                                  int threshold) const;
private:
    MemberDatabase m_mdb;
    AttributeTranslator m_at;
    struct MatchMember{
        MatchMember(std::string str, int num): email(str), numMatch(num) {}
        MatchMember(): email(""), numMatch(0) {}
        void AddNumberMatch(){ numMatch++; }
        int GetnumMatch() { return numMatch; }
        std::string GetEmail(){ return email; }
        std::string email;
        int numMatch;
    };
    int existsMember(std::vector<MatchMember> match_member, const std::string str) const {
        for (int i = 0; i < match_member.size(); i++) {
            if (str == match_member[i].GetEmail()) {
                return i;
            }
        }
        return -1;
    }
    void sortMatchMember(std::vector<MatchMember> &match_member) const {
        bool atLeastOneSwap;
            do
            {
                atLeastOneSwap = false;
                for(int j = 0;j < match_member.size()-1; j++)
                    {
                        if(match_member[j].numMatch < match_member[j+1].numMatch)
                        {
                            std::swap(match_member[j], match_member[j+1]);
                            atLeastOneSwap = true;
                        }
                    }
            }while(atLeastOneSwap == true);
    }
    std::vector<std::string> split(std::string &str, const std::string &pattern){
        std::vector<std::string> res;
        if (str == "") {
            return res;
        }
        
        size_t pos = str.find(pattern);
        while(pos != str.npos)
            {
                std::string temp = str.substr(0, pos);
                res.push_back(temp);
                str = str.substr(pos+1, str.size());
                pos = str.find(pattern);
            }
        res.push_back(str);
        return res;
    }
};

#endif /* MatchMaker_h */
