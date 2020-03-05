//
// Created by tomer on 16/01/2020.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <functional>
#include <map>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>
#include <iterator>

#ifndef EVENDEREH2_CACHMANGER_H
#define EVENDEREH2_CACHMANGER_H

using namespace std;
template<class Problem,class Solution>
class CachManager {
private:
    unsigned int size;
    unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>> map;
    list<Problem> data;
public:
    CachManager(int size1) {
        this->size = size1;
    }


    void insert(Problem, Solution);

    Solution get(Problem key);

    //void foreach(function<void(Solution &)> function);

    void use(typename unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>>::iterator &iterator) {
        data.erase(iterator->second.second);
        data.push_front(iterator->first);
        iterator->second.second = data.begin();
    }
};

template<class Problem,class Solution>
void CachManager<Problem,Solution>::insert(Problem key, Solution obj) {
    auto item = map.find(key);
    //check if the key exists
    if (item != map.end()) {
        use(item);
        map[key] = {obj, data.begin()};
        return;
    } else {
        if (map.size() == size) {
            map.erase(data.back());
            data.pop_back();
        }
        // insert new pair to the map
        data.push_front(key);
        map.insert({key, {obj, data.begin()}});
    }
    // write to the file
    string file = key ;
    ofstream myFile;
    myFile.open(file);
    myFile << obj ;
    myFile.close();
}
/*
template<class Problem,class Solution>
void CachManager<Problem,Solution>::foreach(function<void(Solution &)> function) {
    for (Problem key: data) {
        function(map[key].first);
    }
}*/

template<class Problem,class Solution>
Solution CachManager<Problem,Solution>::get(Problem key) {
    auto item = map.find(key);
    if (item == map.end()) {
        // check if in the list
        ifstream in_file;
        string file_name = key;
        //open the file
        in_file.open(file_name);
        if (!in_file) {
            // if not in list and file
            return "empty";
        }
        // getting the object from the file
        Solution solution;
        getline(in_file,solution);
        in_file.close();
        return solution;
    }
    use(item);
    return item->second.first;
}


#endif //EVENDEREH2_CACHMANGER.H