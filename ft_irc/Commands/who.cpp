#include "commands.hpp"

void Commands::who(Channel &channel)
{
    vector<User *> usersInChannel = channel.getUsers();
    vector<User *>::iterator itUsers = usersInChannel.begin();
    for (; itUsers != usersInChannel.end(); itUsers++)
    {
        string userInfo = (*itUsers)->getClientName() + " " + channel.getName() + " " + (*itUsers)->getUserName() + " " + (*itUsers)->getHostName() + " " + "localhost" + " " + (*itUsers)->getNickName() + " " + "*" + " 0 " + (*itUsers)->getRealName();
        sendToClient(*(*itUsers), (*itUsers)->socket, " " + userInfo);
    }
    
}