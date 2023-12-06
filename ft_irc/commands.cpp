#include "commands.hpp"

void Commands::handleCommand(map<int, User> &user, vector<Channel> &channels, int clientSocket, string msg, string password)
{
    vector<string> space_buffer;
    std::istringstream  ss(msg);
    string token;

    while (std::getline(ss, token))
    {
        token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
        space_buffer.push_back(token);
        string str;
        vector<string>::iterator it = space_buffer.begin();
        if ((*it).find(':') != std::string::npos)
        {
            int where = (*it).find(':');
            string leftPart = (*it).substr(0, where);
            string rightPart = (*it).substr(where + 1);
            std::istringstream  iss(leftPart);
            while (iss >> token)
            {
                args.push_back(token);
            }
            args.push_back(rightPart);
        }
        else 
        {
            std::istringstream  iss(*it);
            while (iss >> token)
            {
                args.push_back(token);
            }
        }
        findCommand(user, channels, clientSocket, password);
        args.clear();
        space_buffer.clear();
    }
}


void Commands::findCommand(map<int, User> &users, vector<Channel> &channels, int clientSocket, string password) 
{
    if (*args.begin() == "NICK")
        this->Nick(users, clientSocket);
    else if (*args.begin() == "PASS")
        this->Pass(users[clientSocket], clientSocket, password);
    else if(*args.begin() == "CAP")
        this->Cap(users[clientSocket], clientSocket);
    else if (*args.begin() == "USER")
        this->Usèr(users[clientSocket], clientSocket);
    else if (*args.begin() == "PING")  
        this->Ping(users[clientSocket], clientSocket);
    else if (*args.begin() == "JOIN")
        this->Join(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "KICK")
        this->Kick(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "PART")
        this->Part(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "PRIVMSG")
        this->Privmsg(users[clientSocket], channels, users, clientSocket);
    else if (*args.begin() == "TOPIC")
        this->Topic(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "MODE")
        this->Mode(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "QUIT")
        this->Quit(users[clientSocket], channels, clientSocket);
    else if (*args.begin() == "NOTICE")
        this->Notice(users[clientSocket], channels, users);
    else if (*args.begin() == "WHO")
        this->Who(users, channels, users[clientSocket], clientSocket);
    else
        this->UnknowCmd(users[clientSocket], clientSocket);
}

void    Commands::UnknowCmd(User &user, int clientSocket)
{
    sendToClient(user, clientSocket, ERR_UNKNOWNCOMMAND(this->args[0]));
}

Channel*    Commands::findChannel(vector<Channel> &channels)
{
    vector<string>::iterator itArg = args.begin() + 1; 
    for (vector<Channel>::iterator itChannel = channels.begin(); itChannel != channels.end(); itChannel++)
    {
        if (*itArg == (*itChannel).getName())
            return &(*itChannel);
    }
    return NULL;
}

User* Commands::findUser(map<int, User> &users)
{
    vector<string>::iterator itArg = args.begin() + 1; 
    for (map<int, User>::iterator itUser = users.begin(); itUser != users.end(); itUser++)
    {
        if (*itArg == (*itUser).second.getNickName())
            return &((*itUser).second);
    }
    return NULL;
}

void Commands::isThereUserInChannel(vector<Channel> &channels, Channel &checkChannel)
{
    if(checkChannel.getUsers().size() == 0)
    {
        for (vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
        {
            if ((*itChannels).getName() == checkChannel.getName())
            {
                channels.erase(itChannels);
                break;
            }
        }
    }
}