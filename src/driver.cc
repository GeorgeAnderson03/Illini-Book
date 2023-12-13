#include <iostream>
#include <vector>

#include "illini_book.hpp"

int main() {
  IlliniBook test(
      "/home/vagrant/src/mp-illini-book-GeorgeAnderson2021/example/persons.csv",
      "example/relations.csv");
  // test.GetPeople();
  // test.GetRelationships();
  //  test.AreRelated(1, 6, "128");
  //    test.AreRelated(1, 2);
  //    std::cout << test.AreRelated(1, 3) << std::endl;
  //    test.GetSteps(9, 1);
  std::vector<std::string> vect = {"124", "128", "173"};
  std::cout << test.CountGroups(vect) << std::endl;
  return 0;
}
