#include "../commands.hpp"

void Commands::Topic(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if (args.size() < 2)
        {
            sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
            return;
        }
        Channel *channel = findChannel(channels);
        if (channel)
        {   
            if (!channel->userOnTheChannel(user.getNickName()))
            {
                sendToClient(user, clientSocket, ERR_NOTONCHANNEL(channel->getName()));
                return;
            }
            vector<string>::iterator itArgs = args.begin() + 2;
            if (itArgs != args.end())
            {
                if (channel->userIsTheAdmin(user.getNickName()))
                {
                    channel->setTopic(*itArgs);
                    sendToClient(user, clientSocket, RPL_TOPIC(user.getNickName(), channel->getName(), channel->getTopic()));
                }
                else
                    sendToClient(user, clientSocket, ERR_CHANOPRIVSNEEDED(channel->getName()));
            }
            else
                sendToClient(user, clientSocket, RPL_TOPIC(user.getNickName(), channel->getName(), channel->getTopic()));
            }
            else 
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(args[1]));
    }
}