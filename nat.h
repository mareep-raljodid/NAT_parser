#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <iterator>


#define MAXCHAR 400

/*template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}*/

using namespace std;
using std::ostream;

class NAT 
{

public:
    vector <string> all_ip;
    vector <string> all_ipTo;
    vector <string> all_port;
    vector <string> all_portTo;
    vector <string> hard_wiredFrom;
    vector <string> hard_wiredTo;
    vector <string> elems;

    string source;
   
    NAT(){
       all_ip = {};
       all_ipTo = {};
       all_port = {};
       all_portTo = {};
       hard_wiredFrom = {};
       hard_wiredTo = {};
       elems = {};
   }

    void get_source(){
        cout << "Please enter the path to the NAT text";
        cout << " file with filename and extension: ";
        cin >> source;
    }

    void table_fetch(){
 
        string line;
        char buffer[MAXCHAR];
        int i =0;
        ifstream natfl(source);
        if (natfl.is_open()) {
            while (! natfl.eof() ) {
                getline (natfl,line);
                strcpy(buffer, line.c_str());
                elems.push_back(buffer);
                i++;
            }
            natfl.close();
        }
        else cout << "Unable to open the NAT file, please try again.";
        elems.pop_back();
    }



    
    void parse(){

        char delim [MAXCHAR];
        char buff [MAXCHAR];
        size_t sept;
        
        for (unsigned i =0; i < elems.size(); i++){
           
            sept = elems[i].find(',');
            strncpy(delim, elems[i].c_str(), sept);
            if (delim[0] == '*'){
                  delim[sept] = '\0';
                  strcpy(buff, delim + 2);
                  all_ip.push_back(buff);
                  strcpy(delim, elems[i].c_str() + sept + 1);
                  all_ipTo.push_back(delim);
              }
              else if (delim[sept - 1] == '*'){
                  delim[sept - 2] = '\0';
                  all_port.push_back(delim);
                  strcpy(delim, elems[i].c_str() + sept + 1);
                  all_portTo.push_back(delim);
              }
              else {
                  delim[sept] = '\0';
                  hard_wiredFrom.push_back(delim);
                  strcpy(delim,elems[i].c_str() + sept + 1);
                  hard_wiredTo.push_back(delim);
              }
        }

    }

    void init(){

        get_source();
        table_fetch();
        parse();
    }

}nat;

