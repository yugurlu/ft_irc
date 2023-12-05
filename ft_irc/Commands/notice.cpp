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
                return ;
        }
        else if ((args.begin() + 1)[0] == "#")
            return ;

        User *reciverUser = findUser(users);
        if (reciverUser)
            sendToClient(user, reciverUser->socket, " NOTICE " + *msg);
    }
}
