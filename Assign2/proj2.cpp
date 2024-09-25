#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <locale>
#include <cctype>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

/*
Name: Sri Satya Sai Immani
CaseID: sxi219@case.edu
Filename: proj2.cpp
Date Created: 24th September, 2024
Description: This file takes in a txt file as input using -f flag and checks if each line of that file is a valid IPv4 address or not. There are 2 modes of output. "summary mode" activated by -s flag and "list mode" activated by -l flag. You are supposed to use one of the two output mode flags at once and not both. You are supposed to provide a input file using -f without which the code will not execute.
*/
#define HTTP_LENGTH 7
#define ERROR 1
#define BUFLEN 1024
#define MIN_REQUIRED_ARGC 3
#define PROTOCOL "tcp"
#define HOST_POS 1
#define PORT_POS 2

int mode = -1;
std::string output_file;
std::string url;
std::vector<std::string> error_messages;

void usage(std::vector<std::string> messages)
{ // This function determines how to run the program when there is an error.
    for (auto message : messages)
    {
        std::cerr << message << std::endl;
    }
    std::cerr << "Usage Example: ./proj2 [-i] [-q] [-a] -u URL -w filename" << std::endl;
    std::cerr << "-i option will be used to print debugging information about the given command line parameters to standard output." << std::endl;
    std::cerr << "-q indicates your program must print the HTTP request sent by your web client to the web server to standard output" << std::endl;
    std::cerr << "-a indicates your program must print the HTTP response header received from the web server to standard output" << std::endl;
    std::cerr << "-u option is used to supply the web server and page the client will access." << std::endl;
    std::cerr << "-w command line argument is used to tell the client where to save the contents of the downloaded URL" << std::endl;
}

void isValidURL(std::string url)
{ // this method checks if the given url is a valid url or not
    if (url.substr(0, HTTP_LENGTH) != "http://")
    { // starts with https://
        error_messages.push_back("Invalid URL. URL should start with http://");
    }
}

void argHandler(int argc, char *argv[])
{ // This function handles the command line arguements and throws out error messages if there are any errors.
    if (argc < MIN_REQUIRED_ARGC)
    {
        error_messages.push_back("Not enough arguments provided");
    }
    for (int i = 1; i < argc; i++)
    {
        std::string m = std::string(argv[i]);
        if (m == "-i" || m == "-q" || m == "-a")
        {
            if (mode != -1)
            {
                error_messages.push_back("Only one of the -option flags (-i, -q, -a) can be used");
            }
        }
        if (m == "-i")
        {
            mode = 1;
        }
        else if (m == "-q")
        {
            mode = 2;
        }
        else if (m == "-a")
        {
            mode = 3;
        }
        else if (m == "-u")
        {
            if (i + 1 < argc && std::string(argv[i + 1])[0] != '-')
            {
                url = std::string(argv[i + 1]);
                std::locale loc;
                std::transform(url.begin(), url.end(), url.begin(), [](unsigned char c)
                               { return std::tolower(c); });
                isValidURL(url);
                i++;
            }
            else
            {
                error_messages.push_back("No URL provided after -u flag");
            }
        }
        else if (m == "-w")
        {
            if (i + 1 < argc && std::string(argv[i + 1])[0] != '-')
            {
                output_file = std::string(argv[i + 1]);
                i++;
            }
            else
            {
                error_messages.push_back("No filename provided after -w flag");
            }
        }
        else
        {
            error_messages.push_back("Invalid argument " + m);
        }
    }
}


std::string extractHostName(std::string url)
{ // this method extracts host name from the url
    size_t host_size = url.substr(HTTP_LENGTH, url.length() - HTTP_LENGTH).find('/');
    return url.substr(HTTP_LENGTH, host_size);
}

void errExit(const char *format, const char *arg) {
    std::cerr << format << arg << std::endl;
    exit(ERROR);
}

int main(int argc, char *argv[])
{   
    argHandler(argc, argv);

    if (error_messages.size() > 0){
        usage(error_messages);
        exit(ERROR);
    }

    // Extracting Host Name and Web File from URL
    std::string host_name = extractHostName(url);
    std::string url_file = url.substr(HTTP_LENGTH + host_name.length());


    if (mode == 1)
    { // INFO Mode
        std::cout << "INFO: host: " << host_name << std::endl;
        std::cout << "INFO: web_file: " << (url_file.empty() ? "/" : url_file) << std::endl;
        std::cout << "INFO: output_file: " << output_file << std::endl;
    }

    struct sockaddr_in sin;
    struct hostent *hinfo;
    struct protoent *protoinfo;
    char buffer[BUFLEN];
    int sd, ret;

    // lookup the hostname 
    hinfo = gethostbyname(argv[HOST_POS]);
    if (hinfo == nullptr) {
        errExit("cannot find name: %s", argv[HOST_POS]);
    }

    //set endpoint information
    memset(&sin, 0x0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[PORT_POS]));
    memcpy(&sin.sin_addr, hinfo->h_addr, hinfo->h_length);
}
