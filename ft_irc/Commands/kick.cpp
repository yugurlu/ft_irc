#include "../commands.hpp"

void Commands::Kick(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() == 3 || args.size() == 4)
        {
            string kickNickName = args[2];
            string reason = "";
            if (args.size() == 4)
                reason = args[3];
            Channel *channel = findChannel(channels);
            if(!channel)
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));
            else if (channel->userIsTheAdmin(user.getNickName()))
            {
                User *kickUser = channel->getUser(kickNickName); 
                channel->sendMessageToChannel(user, "KICK " + channel->getName() + " " + kickUser->getNickName() + " :" + reason, "");
                channel->removeUser(kickNickName);
                isThereUserInChannel(channels, *channel);
            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
   }
}