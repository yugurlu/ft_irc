#include "../commands.hpp"

string Commands::getNickNames(vector<User *> users)
{
    vector<User *>::iterator itUsers = users.begin();
    string nickNames;
    for (; itUsers != users.end(); itUsers++)
    {
        nickNames += (*itUsers)->getNickName() + " ";
    }
    return nickNames;
}

void Commands::getUsersInfo(Channel &channel)
{
    vector<User *> usersInChannel = channel.getUsers();
    vector<User *>::iterator itUsers = usersInChannel.begin();
    string nickNames = getNickNames(usersInChannel);
    for(; itUsers != usersInChannel.end(); itUsers++)
    {
        sendToClient(*(*itUsers), (*itUsers)->socket, RPL_NAMREPLY((*itUsers)->getNickName(), channel.getName(), nickNames));
    }
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
                        vector<User*> users = (*itChannels).getUsers();
                        vector<User*>::iterator itUser = users.begin();
                        for(; itUser != users.end(); itUser++)
                            getUsersInfo(*itChannels);
                        User *userPtr = &user;
                        itChannels->addUser(userPtr);
                        sendToClient(user, clientSocket, " JOIN You are now in channel " + *itArgs);
                        sendToClient(user, clientSocket, RPL_TOPIC(user.getNickName(), itChannels->getName(), itChannels->getTopic()));
                        getUsersInfo(*itChannels);
                        sendToClient(user, clientSocket, RPL_ENDOFNAMES(itChannels->getName(), itChannels->getName()));
                        return;
                    }
                    else if (itChannels->getName() == *itArgs && itChannels->userOnTheChannel(user.getNickName()))
                    {
                        sendToClient(user, clientSocket, ERR_USERONCHANNEL(user.getNickName(), itChannels->getName())); //
                        return;
                    }
                }
                User *userPtr = &user;
                channels.push_back(Channel((*itArgs), userPtr));
                sendToClient(user, clientSocket, " JOIN You are now in channel " + *itArgs);
                sendToClient(user, clientSocket, RPL_TOPIC(user.getNickName(), (*itArgs), ""));//
                getUsersInfo(channels.back());//
                sendToClient(user, clientSocket, RPL_ENDOFNAMES(user.getNickName(), (*itArgs)));//

            }
        }
        else sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS(args[0]));
    }
}