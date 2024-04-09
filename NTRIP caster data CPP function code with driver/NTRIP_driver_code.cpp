#include <iostream>
#include <fstream>
#include "NTRIP_caster_data.h"

int main(){

int response;

response = get_caster_xml();

if(response == 1){
    std::cout << "XML data downloaded!!";
}
else{
    std::cout << "Failed! Try again";
}

}
