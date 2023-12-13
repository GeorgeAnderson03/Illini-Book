#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "utilities.hpp"

// Your code here!
// IlliniBook::~IlliniBook() {}

void IlliniBook::GetRelationships() {
  std::map<int, std::vector<std::pair<int, std::string>>>::iterator itr;
  for (itr = relations_.begin(); itr != relations_.end(); itr++) {
    // std::cout << "Node:" << itr->first << " ";
    for (unsigned int i = 0; i < itr->second.size(); i++) {
      /* //std::cout << "(" << itr->second.at(i).first << "|"
                << itr->second.at(i).second << ") "; */
    }
    // std::cout << std::endl;
  }
}

void IlliniBook::ReadPersonsFile(const std::string& people_fpath) {
  int person = 0;
  std::string string;
  std::ifstream ifs{people_fpath};
  std::set<int> set;
  while (ifs.good()) {
    ifs >> string;
    person = stoi(string);
    set.insert(person);
    relations_.insert(
        std::make_pair(person, std::vector<std::pair<int, std::string>>()));
  }
  persons_ = set;
}
void IlliniBook::ReadRelationsFile(const std::string& relations_fpath) {
  int person1 = -1;
  int person2 = -1;
  std::pair<int, std::string> relations;
  std::ifstream ifs{relations_fpath};
  while (ifs.good()) {
    std::string line;
    ifs >> line;
    std::vector<std::string> person_relations = utilities::Split(line, ',');
    person1 = stoi(person_relations.at(0));
    person2 = stoi(person_relations.at(1));
    if (relations_.contains(
            person1)) {  // adds new pair to already exisiting node
      relations = std::pair<int, std::string>(person2, person_relations.at(2));
      relations_.at(person1).push_back(relations);
    } else {  // create new node AND and new pair to a new node
      std::vector<std::pair<int, std::string>> tempvector;
      tempvector.push_back(
          std::pair<int, std::string>(person2, person_relations.at(2)));
      relations_.insert(
          std::pair<int, std::vector<std::pair<int, std::string>>>(person1,
                                                                   tempvector));
    }
    if (relations_.contains(
            person2)) {  // adds new pair to already exisiting node
      relations = std::pair<int, std::string>(person1, person_relations.at(2));
      relations_.at(person2).push_back(relations);
    } else {  // create new node AND and new pair to a new node
      std::vector<std::pair<int, std::string>> tempvector;
      tempvector.push_back(
          std::pair<int, std::string>(person1, person_relations.at(2)));
      relations_.insert(
          std::pair<int, std::vector<std::pair<int, std::string>>>(person2,
                                                                   tempvector));
    }
  }
}
// distance = pair<int, current + 1>
std::map<int, int> IlliniBook::Helper(
    int uin1, std::vector<std::string> relationshiptype) const {
  int start = uin1;
  std::queue<int> queue;
  std::map<int, int> map;  // first int other node second distance
  queue.push(start);
  map[start] = 0;
  std::string blank;
  std::set<int> set;
  while (!(queue.empty())) {
    int current = queue.front();
    queue.pop();
    std::vector<std::pair<int, std::string>>::const_iterator itr;
    for (itr = relations_.at(current).begin();
         itr != relations_.at(current).end();
         itr++) {
      if (map.contains(itr->first)) {
      } else {
        if (relationshiptype.at(0) == blank) {
          map.insert(std::pair<int, int>(itr->first, (map[current] + 1)));
          queue.push(itr->first);
        } else {
          for (unsigned int i = 0; i < relationshiptype.size(); i++) {
            if (itr->second == relationshiptype.at(i)) {
              map.insert(std::pair<int, int>(itr->first, (map[current] + 1)));
              queue.push(itr->first);
              /* std::cout << "ADD all neighbors NODE: " << itr->first
                        << " DISTANCE: " << map[current] + 1 << std::endl; */
            }
          }
        }
      }
    }
  }
  return map;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {  // DONE
  bool temp = AreRelated(uin_1, uin_2, "");
  // std::cout << temp << std::endl;
  return temp;
}
IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {  // DONE
  ReadPersonsFile(people_fpath);
  ReadRelationsFile(relations_fpath);
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {  // DONE
  std::map<int, int> map = Helper(uin_1, {relationship});
  // std::cout << map.contains(uin_2) << std::endl;
  return map.contains(uin_2);
}

int IlliniBook::GetRelated(
    int uin_1, int uin_2) const {  // queue questions, breadth depth advice,
                                   // similiar to get CountGroups?
  return GetRelated(uin_1, uin_2, "");
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::map<int, int> map = Helper(uin_1, {relationship});
  if (map.contains(uin_2)) {
    // std::cout << "path found distance is " << map.at(uin_2) << std::endl;
    return map.at(uin_2);
  }
  // std::cout << "-1 didnt find a path" << std::endl;
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {  // breadth depth
  std::map<int, int> map = Helper(uin, {""});
  std::vector<int> vect;
  std::map<int, int>::const_iterator itr;
  for (itr = map.begin(); itr != map.end(); itr++) {
    if (map.at(itr->first) == n) {
      // std::cout << itr->first << std::endl;
      vect.push_back(itr->first);
    }
  }
  return vect;
}

size_t IlliniBook::CountGroups()
    const {  // tweaking of current printable relation list. use queue for
             // counting set for counted combo?

  return CountGroups("");
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::vector<std::string> vect;
  vect.push_back(relationship);
  return CountGroups(vect);
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::set<int> visited;
  std::map<int, int> map;
  size_t num = 0;

  std::map<int, std::vector<std::pair<int, std::string>>>::const_iterator itr;
  for (itr = relations_.begin(); itr != relations_.end(); itr++) {
    if (visited.contains(itr->first)) {
    } else {
      map = Helper(itr->first, relationships);
      std::map<int, int>::iterator mapitr;
      for (mapitr = map.begin(); mapitr != map.end(); mapitr++) {
        visited.insert(mapitr->first);
      }
      num++;
    }
  }
  return num;
}
