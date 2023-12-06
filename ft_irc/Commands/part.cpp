#include "../commands.hpp"

void Commands::Part(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() == 3)
        {
            vector<string>::iterator itArgs = args.begin() + 1;
            if (itArgs != args.end())
            {
                for (vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
                {
                    if (itChannels->getName() == (*itArgs) && itChannels->userOnTheChannel(user.getNickName()))
                    {
                        itChannels->sendMessageToChannel(user, "PART " + itChannels->getName() + " :" + args[2], "");
                        itChannels->removeUser(user.getNickName());
                        if (itChannels->userIsTheAdmin(user.getNickName()))
                            itChannels->removeAdmin(user.getNickName());
                        isThereUserInChannel(channels, (*itChannels));
                        return ;
                    }
                }
                sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(args[1]));
            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}