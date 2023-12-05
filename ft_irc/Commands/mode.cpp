#include "../commands.hpp"

void Commands::Mode(User& user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        if(args.size() == 3)
        {
            string operation = args[2];
            Channel *channel = findChannel(channels);
            if (channel )
            {
                if(channel->userIsTheAdmin(user.getNickName()) && operation.size() == 2 && operation.find('o'))
                {
                    User *modifyUser = channel->getUser(args[3]);
                    if (operation[0] == '+')
                    {
                        channel->addAdmin(args[3]);
                        sendToClient(user, modifyUser->socket, " MODE You have been promoted admin!"); //
                        sendToClient(user, clientSocket, " MODE You promoted admin!"); //
                    }
                    else if (operation[0] == '-')
                    {
                        channel->removeAdmin(args[3]);
                        sendToClient(user, modifyUser->socket, " MODE You reduced it"); //
                        sendToClient(user, clientSocket, " MODE You were reduced!"); //
                    }
                }
            }
            else sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}