//
// Created by tomer on 20/01/2020.
//

#ifndef EVENDEREH2_MYCLIENTHANDLER_H
#define EVENDEREH2_MYCLIENTHANDLER_H

#include <string.h>
#include <string>
#include "Solver.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include "Matrix.h"
#include "Cell.h"
#include "State.h"
#include "CachManager.h"

using namespace std;

class MyClientHandler : public ClientHandler {
public:
    MyClientHandler(CachManager<string, string> *cm1, Solver<vector<string>, string> *OA) {
        this->cm = cm1;
        this->solver = OA;
    };

    MyClientHandler(MyClientHandler const & a){
        this->solver=a.solver->clone();
        this->cm = a.cm;
    }
MyClientHandler* clone() override {
        return new MyClientHandler(*this);
    }

    void handleClient(int output, int input) {

        char buffer[1024] = {0};
        vector<string> v;
        string check ;
        // read the matrix from the client
        while (check.find("end") == string::npos) {
            int valread = read(input, buffer, 1024);
            check = buffer ;
            if ((check.find("end") == string::npos)) {
                v.push_back(buffer);
            }
            memset(buffer, 0, 1024);
        }
        string problem ="";
        for (int j = 0 ; j < v.size() ;j++){
            problem +=v[j] ;
        }

        string stringProbleForCach = problem ;
        std::string::iterator end_pos = std::remove(stringProbleForCach.begin(), stringProbleForCach.end(), ' ');
        stringProbleForCach.erase(end_pos, stringProbleForCach.end());
        //limit the name of the file we make to save the problem and solution to 255
        char probleForCach [255] ;
        for (int i = 0 ; i < 255 ; i++){
            probleForCach[i] = stringProbleForCach[i] ;
        }
        string solution ;
        //check if we already run this matrix
        if (this->cm->get(probleForCach)== "empty"){
            solution = this->solver->solve(v) ;
            this->cm->insert(probleForCach,solution) ;
        }
        else{
            solution = this->cm->get(probleForCach);
        }
        int valsent = send(input, solution.c_str(), solution.size(), 0);
    };

private:
    Solver<vector<string>, string> *solver;
    CachManager<string, string> *cm;
};

#endif //EVENDEREH2_MYCLIENTHANDLER_H