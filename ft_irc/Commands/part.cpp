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
                        itChannels->removeUser(user.getNickName());
                        if (itChannels->userIsTheAdmin(user.getNickName()))
                            itChannels->removeAdmin(user.getNickName());
                        vector<User *> usersInChannel = itChannels->getUsers();
                        vector<User *>::iterator itUserInChannel = usersInChannel.begin();
                        for (; itUserInChannel != usersInChannel.end(); itUserInChannel++)
                            sendToClient(user, (*itUserInChannel)->socket, user.getNickName() + " left this channel! Reason: " + *(args.begin() + 2));
                        return;
                    }
                }
                sendToClient(user, clientSocket, "ERR_NOSUCHCHANNEL()"); // kanal ismi gelicek
            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}