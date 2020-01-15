#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h> 


#include "nat.h"
#include "flow.h"

#define MAXCHAR 400

using namespace std;

vector <string> gen;

int findelem(string key, vector <string> v){

    vector<string>::iterator itr = find(v.begin(), v.end(), key);

	if (itr != v.cend()) {
		return distance(v.begin(), itr);
    }
	else {
		return -1;
    }
}

void init(){
    cout << "Starting the program.." << endl;
    cout << "Engineer: Rajdeep Bandopadhyay" << endl << endl;
    cout << "A program that takes in the path of two files \n";
    cout << "which are a NAT file and a Flow file respectively \n";
    cout << "and generates a text file containing matches for the \n";
    cout << "IP addresses in the Flow file based on the NAT file. \n";
            
    cout << "Files: nat.cpp, flow.cpp, main.cpp" << endl;
    cout << "\n\n" << endl;
             
    nat.init();
    flow.init();
}


void match(){

    char delim1[MAXCHAR];
    char delim2[MAXCHAR];
    char buffer[MAXCHAR];
    int x1, x2, x3;

    cout << "The output has been written to output.txt file" << endl;

    FILE *file;
    file = freopen("output.txt","w",stdout);

    for(unsigned i = 0; i < flow.ip.size(); i++){
        strcpy(delim1, flow.ip[i].c_str());
        strcpy(delim2, flow.port[i].c_str());
        
        x1 = findelem(delim2, nat.all_ip);

        if(x1 > -1){
            sprintf (buffer, "%s -> %s",flow.elemsF[i].c_str(), nat.all_ipTo[x1].c_str());
            cout << buffer << endl;
        }

        x2 = findelem(delim1, nat.all_port);
        if(x2 > -1){ 
            sprintf (buffer, "%s -> %s",flow.elemsF[i].c_str(), nat.all_portTo[x2].c_str());
            cout << buffer << endl;
        }

        x3 = findelem(flow.elemsF[i], nat.hard_wiredFrom);
        if(x3 > -1){
            sprintf (buffer, "%s -> %s",flow.elemsF[i].c_str(), nat.hard_wiredTo[x3].c_str());
            cout << buffer << endl;
        }

        else if ((x1 == -1) && (x2 == -1) && (x3 == -1)){
            sprintf(buffer, "No NAT match for %s", flow.elemsF[i].c_str());
            cout << buffer <<endl;
        }
    }
    fclose (file);
   
}

int main(){
    
    init();
    match();
    
}
