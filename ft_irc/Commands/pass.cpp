#include "../commands.hpp"

void Commands::Pass(User& user, int clientSocket, string svPasswd) {
    if(args.size() == 2)
    {
        if(user._isAuth) 
            sendToClient(user, clientSocket, ERR_ALREADYREGISTRED());
        else if (user._isRegister) {
            (void)user;
            string message;
            vector<string>::iterator it = args.begin() + 1;
            if(!(*it).empty() && *it == svPasswd) {
                sendToClient(user, clientSocket, RPL_WELCOME(user.getNickName(), user.getUserName(), user.getHostName()));
                user._isAuth = true;
            }
            else if (*it != svPasswd)
                sendToClient(user, clientSocket, ERR_PASSWDMISMATCH());
        }
    }
    else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0])); // 0'ı duzelt
}