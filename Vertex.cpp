//
// Created by Ruipeng Han on 11/30/20.
//

#include "Vertex.h"
#include <vector>
#include <sstream>

Vertex::Vertex(bool invalid) {
    invalid_vertex_ = true;
}

Vertex::Vertex(string info) {
    vector<string> result;
    stringstream s_stream(info); //create string stream from the string

    //vector<string> parsed_row;
    string line;
    while (std::getline(s_stream, line)) {        // read full line
        const char *mystart=line.c_str();    // prepare to parse the line - start is position of begin of field
        bool instring{false};
        for (const char* p=mystart; *p; p++) {  // iterate through the string
            if (*p=='"')                        // toggle flag if we're btw double quote
                instring = !instring;
            else if (*p==',' && !instring) {    // if comma OUTSIDE double quote
                result.push_back(string(mystart,p-mystart));  // keep the field
                mystart=p+1;                    // and start parsing next one
            }
        }
        result.push_back(string(mystart));   // last field delimited by end of line instead of comma
    }

    airport_id_ = result[0];
    name_ = result[1];
    city_ = result[2];
    country_ = result[3];
    latitude_ = stod(result[6]);
    longitude_  = stod(result[7]);
    altitude_ = stod(result[8]);
}

// 还原row
void Vertex::print() {
    if (!invalid_vertex_)
        std::cout << "airport id: " << airport_id_ << " name: " << name_ << " city: " << city_ << " country: " << country_
             << " latitude: " << latitude_ << " longitude: " << longitude_ << " altitude: " << altitude_ << std:: endl;
    else
        std::cout<< "Invalid vertex." << std::endl;

}
