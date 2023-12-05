#include "../commands.hpp"

void Commands::Kick(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() == 4)
        {
            string kickNickName = args[2];
            string reason = args[3];
            Channel *channel = findChannel(channels);
            if(!channel)
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));
            else if (channel->userIsTheAdmin(user.getNickName()))
            {
                User *kickUser = channel->getUser(kickNickName); 
                sendToClient(user, kickUser->socket, " KICK You're kicked for Reason: " + reason);
                channel->removeUser(kickNickName);
            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
   }
}