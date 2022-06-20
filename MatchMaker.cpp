//
//  MatchMaker.cpp
//  CS32Project4
//
//  Created by Yiqu on 3/14/22.
//

#include "MatchMaker.h"
#include<algorithm>
#include <unordered_set>
#include <set>
#include <string>

//Constructs a MatchMaker object with the indicated parameters
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){
    m_mdb = mdb;
    m_at = at;
}

//Returning a vector of EmailCount objects (a struct we provide in provided.h),
//each holding the email address of a matching member that has at least the threshold number of compatible attribute-value pairs
//along with the number of such compatible pairs.
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    PersonProfile const * member = m_mdb.GetMemberByEmail(email);
    std::set<std::string> comp_attval;
    std::vector<EmailCount> results;
    std::set<AttValPair*> member_avp;
    std::set<std::string>cpt_member;
    std::vector<MatchMember> match_member;
//    if (member == nullptr) {
//        std::cerr << "No matching member, quit matching!\n";
//        return results;
//    }
    for (int i = 0; i < member->GetNumAttValPairs(); i++) {
        AttValPair * new_av = new AttValPair();
                if(member->GetAttVal(i, *(new_av)) == true){
                    std::vector<AttValPair> cpt_avp = m_at.FindCompatibleAttValPairs(*new_av);
                    for (int i = 0; i < cpt_avp.size(); i++) {
                        comp_attval.insert(cpt_avp[i].attribute+","+cpt_avp[i].value);
                    }
                }
    }
    if (comp_attval.size() != 0) {
        for (std::set<std::string>::iterator iter = comp_attval.begin();iter != comp_attval.end() ; iter++) {
            int pos = iter->find(",");
            AttValPair * new_avp = new AttValPair(iter->substr(0,pos), iter->substr(pos+1, iter->length()));
            std::vector<std::string> temp = m_mdb.FindMatchingMembers(*new_avp);
            cpt_member.insert(temp.begin(),temp.end());
        }
    }
    //std:: cout << cpt_member.size() << std::endl;
    //std:: cout << "here\n";
    if (cpt_member.size() != 0) {
        for (std::set<std::string>:: iterator iter = cpt_member.begin(); iter != cpt_member.end(); iter++) {
            int countAvp = 0;
            for (int i = 0; i < m_mdb.GetMemberByEmail(*iter)->GetNumAttValPairs(); i++) {
                AttValPair avp;
                m_mdb.GetMemberByEmail(*iter)->GetAttVal(i, avp);
                std::string str = avp.attribute + "," + avp.value;
                if(comp_attval.find(str) != comp_attval.end())
                    countAvp++;
            }
            if (countAvp >= threshold) {
                MatchMember * mat_mem = new MatchMember(*(iter), countAvp);
                match_member.push_back(*mat_mem);
            }
        }
    }
    
    //std::cout << "here!\n";
    //sort match members
    if (match_member.size() != 0) {
        sortMatchMember(match_member);
        for (int i = 0; i < match_member.size(); i++) {
            EmailCount *obj = new EmailCount(match_member[i].email,match_member[i].numMatch);
            results.push_back(*obj);
        }
    }
    return results;
}
