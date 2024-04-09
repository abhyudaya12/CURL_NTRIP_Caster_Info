#include <iostream>
#include <fstream>
#include "curl\curl.h"
#include "NTRIP_caster_data.h"


// Callback function to write received data to a file
size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int get_caster_xml(){

// URL of the NTRIP caster data stream
    const char* caster_url = "http://igs-ip.net:2101/";

    // Initialize cURL session
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if(curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, caster_url);

        // Set username and password for authentication
        curl_easy_setopt(curl, CURLOPT_USERPWD, "MP16804:746zew");

        // Set write callback function
        FILE *file = fopen("rtk_data.xml", "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "Failed to retrieve RTK data. Error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "RTK data received and saved." << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
        fclose(file);
    } else {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return 0;
    }

    return 1;


}


//int main() {
//    // URL of the NTRIP caster data stream
//    const char* caster_url = "http://igs-ip.net:2101/";
//
//    // Initialize cURL session
//    CURL *curl;
//    CURLcode res;
//    curl = curl_easy_init();
//
//    if(curl) {
//        // Set URL
//        curl_easy_setopt(curl, CURLOPT_URL, caster_url);
//
//        // Set username and password for authentication
//        curl_easy_setopt(curl, CURLOPT_USERPWD, "MP16804:746zew");
//
//        // Set write callback function
//        FILE *file = fopen("rtk_data.xml", "wb");
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
//
//        // Perform the request
//        res = curl_easy_perform(curl);
//
//        // Check for errors
//        if(res != CURLE_OK) {
//            std::cerr << "Failed to retrieve RTK data. Error: " << curl_easy_strerror(res) << std::endl;
//        } else {
//            std::cout << "RTK data received and saved." << std::endl;
//        }
//
//        // Clean up
//        curl_easy_cleanup(curl);
//        fclose(file);
//    } else {
//        std::cerr << "Failed to initialize cURL." << std::endl;
//        return 1;
//    }
//
//    return 0;
//}
