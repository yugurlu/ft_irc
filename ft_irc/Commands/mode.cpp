#include "../commands.hpp"

void Commands::Mode(User& user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() < 2)
        {
            sendToClient(user, clientSocket, RPL_CHANNELMODEIS(user.getNickName(), "+nt"));
            return;
        }
        Channel *channel = findChannel(channels);
        if(!channel->userIsTheAdmin(user.getNickName()))
        {
            sendToClient(user, clientSocket, ERR_CHANOPRIVSNEEDED(channel->getName()));
            return;
        }
        vector<string>::iterator itArgs = args.begin() + 2;
        if (itArgs != args.end() && *itArgs == "+o")
        {
            itArgs++;
            if (itArgs != args.end())
            {
                if (channel->userOnTheChannel(*itArgs))
                {
                    channel->addAdmin(*itArgs);
                    sendToClient(user, clientSocket, "MODE " + channel->getName() + " +o " + *itArgs);
                    return;
                }
                else
                {
                    sendToClient(user, clientSocket, ERR_NOSUCHNICK(*itArgs));
                    return;
                }
            }
            else
            {
                sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
                return;
            }
        }
        else if (itArgs != args.end() && *itArgs == "-o")
        {
            itArgs++;
            if (itArgs != args.end())
            {
                if (channel->userOnTheChannel(*itArgs))
                {
                    channel->removeAdmin(*itArgs);
                    sendToClient(user, clientSocket, "MODE " + channel->getName() + " -o " + *itArgs);
                    return;
                }
                else
                {
                    sendToClient(user, clientSocket, ERR_NOSUCHNICK(*itArgs));
                    return;
                }
            }
            else
            {
                sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
                return;
            }
        }
    }
}