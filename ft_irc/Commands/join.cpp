#include "../commands.hpp"

void Commands::sendUsersInfo(Channel &channel, User &user)
{
    string names;
    vector<User *> usersInChannel = channel.getUsers();
    for (vector<User *>::iterator itUserInChannel = usersInChannel.begin(); itUserInChannel != usersInChannel.end(); itUserInChannel++)
    {
        if (channel.userIsTheAdmin((*itUserInChannel)->getNickName()))
        names += "@";
        names += (*itUserInChannel)->getNickName().empty() ? (*itUserInChannel)->getUserName() : (*itUserInChannel)->getNickName();
        if (itUserInChannel != usersInChannel.end() - 1)
        names += " ";
    }
    channel.sendMessageToChannel(user, RPL_NAMREPLY(user.getNickName(), channel.getName(), names));
    channel.sendMessageToChannel(user, RPL_ENDOFNAMES(user.getNickName(), channel.getName()));
}


void Commands::Join(User &user, vector<Channel> &channels, int clientSocket)
{
    if (user._isAuth)
    {
        vector<string>::iterator itArgs = args.begin() + 1;
        if(args.size() == 2)
        {
            if (itArgs != args.end() && (*itArgs)[0] == '#')
            {
                for (vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
                {
                    if (itChannels->getName() == *itArgs && !itChannels->userOnTheChannel(user.getNickName()))
                    {   

                        User *userPtr = &user;
                        itChannels->addUser(userPtr);
                        sendToClient(user, clientSocket, " JOIN You are now in channel " + *itArgs);
                        sendToClient(user, clientSocket, RPL_TOPIC(user.getNickName(), itChannels->getName(), itChannels->getTopic()));
                        sendUsersInfo((*itChannels), user);
                        return;
                    }
                    else if (itChannels->getName() == *itArgs && itChannels->userOnTheChannel(user.getNickName()))
                    {
                        sendToClient(user, clientSocket, ERR_USERONCHANNEL(user.getNickName(), itChannels->getName())); //
                        return;
                    }
                }
                User *userPtr = &user;
                Channel newChannel = Channel((*itArgs), userPtr);
                channels.push_back(newChannel);
                sendToClient(user, clientSocket, " JOIN You are now in channel " + *itArgs);
                sendToClient(user, clientSocket, RPL_NOTOPIC(user.getNickName(), (*itArgs)));
                sendUsersInfo(newChannel, user);
                //getUsersInfo(channels.back());//
                //sendToClient(user, clientSocket, RPL_ENDOFNAMES(user.getNickName(), (*itArgs)));//

            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}