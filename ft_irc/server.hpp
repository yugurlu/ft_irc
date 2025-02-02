#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include "user.hpp"
#include "commands.hpp"
#include "channel.hpp"
#include "numeric.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::string;

class Server {
    private:
        int _serverPort;
        int _serverSocket;
        struct sockaddr_in _serverAddr;
        struct sockaddr_in _newAddr;
        socklen_t _addrSize;
        
        std::map<int, std::string> _clientNames;
        string _password;
        std::map<int, User> Users;
        Commands commands;
        string hostName;

        vector<Channel> channels;
    public:
        Server(int port);
        void Start();
        void Cmd(std::string, int, string);
        void setPassword(string);
        string getPassword(void);
        void resetClient(int);
};

#endif
