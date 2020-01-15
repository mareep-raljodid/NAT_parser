#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>


#define MAXCHAR 400

using namespace std;
using std::ostream;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "{";
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << "\n ";
    }
    out << "}";
    return out;
}

class Flow 
{

public:
    vector <string> ip;
    vector <string> port;
    vector <string> elemsF;

    string sourceF;
   
    Flow(){
       ip = {};
       port = {};
       elemsF = {};
   }

    void get_source(){
        cout << "Please enter the path to the FLOW text";
        cout << " file with filename and extension: ";
        cin >> sourceF;
    }

    void table_fetch(){
 
        string line;
        char buffer[MAXCHAR];
        int i =0;
        ifstream myfile(sourceF);
        if (myfile.is_open()) {
            while (! myfile.eof() ) {
                getline (myfile,line);
                strcpy(buffer, line.c_str());
                elemsF.push_back(buffer);
                i++;
            }
            myfile.close();
        }
        else cout << "Unable to open the FLOW file, please try again.";
        elemsF.pop_back();
    }



    
    void parse(){

        char delim [MAXCHAR];
        size_t sept;
        
        for (unsigned i =0; i < elemsF.size(); i++){
           
            sept = elemsF[i].find(':');
            strncpy(delim, elemsF[i].c_str(), sept);
                delim[sept] = '\0';
                ip.push_back(delim);
                strcpy(delim, elemsF[i].c_str() + sept + 1);
                port.push_back(delim);
        }
    }

    void init(){

        get_source();
        table_fetch();
        parse();
    }

}flow;

