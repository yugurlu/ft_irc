#include "../commands.hpp"

void Commands::Usèr(User& user, int clientSocket) 
{
    if(args.size() != 5) 
    {
        sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
        return ;
    }
    if(user._isRegister) 
    {
        sendToClient(user, clientSocket, ERR_ALREADYREGISTRED());
        return ;
    }
    this->args.erase(this->args.begin());
    if(args[0].size() && args[1][0] == '0' && args[1][1] == '\0' && args[3].size()) 
    {
        user.setUserName(args[0]);
        user.setRealName(args[3]);
        user._isUser = true;
        if (user._isNicked) 
        {
            user._isRegister = true;
            string newClientName = user.getNickName() + "!" + user.getUserName() + "@" + user.getHostName();
            user.setClientName(newClientName);
        }
        else
        {
            string newClientName =  "!" + user.getUserName() + "@" + user.getHostName();
            user.setClientName(newClientName);
        }
    }
    else sendToClient(user, clientSocket, "User using: USER <username> 0 * <realname>");
}
