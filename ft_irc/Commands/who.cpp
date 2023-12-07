#include "../commands.hpp"

void Commands::Who(map<int, User> &users, vector<Channel> &channels, User &user, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() < 1)
        {
            sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
            return;
        }
        if (args[1][0] == '#')
        {
            Channel *channel = findChannel(channels);
            if(!channel)
            {
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));
                return;
            }
            vector<User *> usersInChannel = channel->getUsers();
            for(vector<User *>::iterator itUsers = usersInChannel.begin(); itUsers != usersInChannel.end(); itUsers++)
                sendToClient(user, clientSocket, RPL_WHOREPLY((*itUsers)->getNickName(), channel->getName(), (*itUsers)->getUserName(), (*itUsers)->getHostName(), "localhost", (*itUsers)->getNickName(), "*", "0 ", (*itUsers)->getRealName()));
            sendToClient(user, clientSocket, RPL_ENDOFWHO(user.getNickName(), channel->getName()));
            return;
        }
    
        User *userPtr = findUser(users);
        if(userPtr)
            sendToClient(user, clientSocket, RPL_WHOREPLY(userPtr->getNickName(),"*", userPtr->getUserName(), userPtr->getHostName(), "localhost", userPtr->getNickName(), "*", "0 ", (*userPtr).getRealName()));
    }
}