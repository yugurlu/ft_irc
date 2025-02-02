#ifndef COMMANDS_HPP
# define COMMANDS_HPP

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
#include <sstream>
#include <algorithm>
#include "user.hpp"
#include "channel.hpp"
#include "numeric.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::map;

class Commands {
    private:

    public:
        string parsedCmd;
        vector<string> args;

        void Cap(User&,int);
        void Usèr(User&, int);
        void Ping(User&, int);
        void UnknowCmd(User&, int);
        void Pass(User&, int, string);
        void Nick(map<int, User> &, int);
        void Join(User&, vector<Channel> &, int);
        void Part(User&, vector<Channel> &, int);
        void Kick(User&, vector<Channel> &, int);
        void Mode(User&, vector<Channel> &, int);
        void Quit(User&, vector<Channel> &, int);
        void Topic(User&, vector<Channel> &, int);
        void Notice(User&, vector<Channel> &, map<int, User> &);
        void Privmsg(User&, vector<Channel> &, map<int, User> &, int);
        void Who(map<int, User> &, vector<Channel> &, User &, int);

        void sendUsersInfo(Channel &, User &, int);
        Channel* findChannel(vector<Channel> &);
        User* findUser(map<int, User> &);
        void findCommand(map<int, User> &, vector<Channel> &, int, string);
        void handleCommand(map<int, User> &, vector<Channel> &, int, string, string);
        string getPrefix(User &);
        void isThereUserInChannel(vector<Channel> &, Channel&);


};

#endif
