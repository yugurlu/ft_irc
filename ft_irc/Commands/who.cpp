#include "../commands.hpp"

void Commands::who(vector<Channel> &channels, User &user, int clientSocket)
{
    if (user._isAuth)
    {
        if (args.size() == 2)
        {
            Channel *channel = findChannel(channels);
            if (channel)
            {
                vector<User *> users = channel->getUsers();
                vector<User *>::iterator itUsers = users.begin();
                for (; itUsers != users.end(); itUsers++)
                {
                    sendToClient(user, (*itUsers)->socket, RPL_WHOREPLY(user.getNickName(), channel->getName(), (*itUsers)->getUserName(), (*itUsers)->getHostName(), "localhost", (*itUsers)->getNickName(), "*", " 0", (*itUsers)->getRealName()));
                }
                sendToClient(user, clientSocket, RPL_ENDOFWHO(channel->getName(), channel->getName()));
            }
            else
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));
        }
        else
            sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}