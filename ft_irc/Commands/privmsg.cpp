#include "../commands.hpp"

void Commands::Privmsg(User &user, vector<Channel> &channels, map<int, User> &users, int clientSocket)
{
    if (user._isAuth)
    {
        vector<string>::iterator itArgs = args.begin() + 1;
        if (args.size() >= 3)
        {
            if (itArgs != args.end() && (*itArgs)[0] == '#')
            {
                string message = "PRIVMSG " + *(args.begin() + 1) + " :" + *(args.begin() + 2);
                for (vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
                {
                    if (itChannels->getName() == *itArgs && itChannels->userOnTheChannel(user.getNickName()))
                    {
                        itChannels->sendMessageToChannel(user, message, user.getNickName());
                        return;
                    }
                    else if (itChannels->getName() == *itArgs && !itChannels->userOnTheChannel(user.getNickName()))
                    {
                        sendToClient(user, clientSocket, ERR_CANNOTSENDTOCHAN(itChannels->getName()));
                        return;
                    }
                }
                sendToClient(user, clientSocket, "ERR_NOSUCHCHANNEL()");
            }
            else
            {
                for (map<int, User>::iterator itUsers = users.begin(); itUsers != users.end(); itUsers++)
                {
                    if (itUsers->second.getNickName() == *itArgs)
                    {
                        sendToClient(user, itUsers->second.socket, "PRIVMSG " + itUsers->second.getNickName() + " :" + *(args.begin() + 2));
                        return;
                    }
                }
                sendToClient(user, clientSocket, ERR_NOSUCHNICK(user.getNickName()));
            }
        }
        else
            sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}
