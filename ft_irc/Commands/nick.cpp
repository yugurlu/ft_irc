#include "../commands.hpp"

void Commands::Nick(map<int, User> &users, int clientSocket) { 
    map<int, User>::iterator itUser = users.begin();
    vector<string>::iterator itArgs = args.begin() + 1;
    
    if(args.size() == 2)
    {
        while (itUser != users.end())
        {
            if (itUser->second.getNickName() == *itArgs) {
                sendToClient(users[clientSocket], clientSocket, ERR_NICKNAMEINUSE(*itArgs));
                return;
            }
            itUser++;
        }
        if(users[clientSocket]._isNicked)
        {
            users[clientSocket].setNickName(*itArgs);
            return ;
        }
        else 
        {
            users[clientSocket].setNickName(*itArgs);
            string message = " NICK " + users[clientSocket].getNickName() + " ; Requesting the new nick " + users[clientSocket].getNickName();
            sendToClient(users[clientSocket], clientSocket, message);
            if (users[clientSocket]._isUser) 
            {
                users[clientSocket]._isRegister = true;
                string newClientName = users[clientSocket].getNickName() + "!" + users[clientSocket].getUserName() + "@" + users[clientSocket].getHostName();
                users[clientSocket].setClientName(newClientName);
            }
            else if(users[clientSocket]._isNicked)
            {
                string newClientName = users[clientSocket].getNickName() + "!" + "@" + users[clientSocket].getHostName();
                users[clientSocket].setClientName(newClientName);
            }
        }
        users[clientSocket]._isNicked = true;
    }
    else sendToClient(users[clientSocket], clientSocket, ERR_NONICKNAMEGIVEN());
}