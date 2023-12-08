#include "../commands.hpp"

void Commands::Pass(User& user, int clientSocket, string svPasswd) {
    if(args.size() == 2)
    {
        if(user._isRegister)
        {
            sendToClient(user, clientSocket, ERR_ALREADYREGISTRED());
            return ;
        }
        string message;
        vector<string>::iterator it = args.begin() + 1;
        if(!(*it).empty() && *it == svPasswd)
            user._isRegister = true;
        else if (*it != svPasswd)
            sendToClient(user, clientSocket, ERR_PASSWDMISMATCH());
    }
    else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
}