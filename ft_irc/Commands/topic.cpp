#include "../commands.hpp"

void Commands::Topic(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {  
        if(args.size() == 3)
        {
            Channel *channel = findChannel(channels);
            if (channel)
            {
                if(channel->userIsTheAdmin(user.getNickName()))
                {
                    vector<string>::iterator topic = args.begin() + 2;
                    channel->setTopic(*topic);
                    vector<User*> vecUser = channel->getUsers();
                    vector<User*>::iterator it = vecUser.begin();
                    for(; it != vecUser.end(); it++)
                        sendToClient(user, (*it)->socket, RPL_TOPIC(user.getNickName(), channel->getName(), *topic)); //*
                }
            }
            else sendToClient(user, clientSocket, ERR_NOSUCHCHANNEL(channel->getName()));

        }
        else sendToClient(user, clientSocket,ERR_NEEDMOREPARAMS(args[0])); //
    }
}