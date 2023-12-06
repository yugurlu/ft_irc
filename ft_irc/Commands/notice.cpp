#include "../commands.hpp"

void Commands::Notice(User &user, vector<Channel> &channels, map<int, User> &users)
{
    if (user._isAuth)
    {
        vector<string>::iterator msg = args.begin() + 2;
        Channel *channel = findChannel(channels);
        if (channel)
        {
            if(channel->userOnTheChannel(user.getNickName()))
            {
                vector<User *> users = channel->getUsers();
                vector<User *>::iterator itUser = users.begin();
                for (; itUser != users.end(); itUser++)
                {
                    if ((*itUser)->getNickName() != user.getNickName())
                        sendToClient(user, (*itUser)->socket, " NOTICE " + user.getNickName() + ": " + *msg);
                }
                return;
            }
            else
            {
                sendToClient(user, user.socket, ERR_CANNOTSENDTOCHAN(channel->getName())); //
                return ;
            }
        }
        else if (args[1][0] == '#')
        {
            sendToClient(user, user.socket, ERR_NOSUCHCHANNEL(channel->getName())); //
            return ;
        }

        User *reciverUser = findUser(users);
        if (reciverUser)
            sendToClient(user, reciverUser->socket, " NOTICE " + *msg);
        else
          sendToClient(user, user.socket, "ERR_WASNOSUCHNICK");  
    }
}
