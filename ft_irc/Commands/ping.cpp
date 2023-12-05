#include "../commands.hpp"

void    Commands::Ping(User &user, int clientSocket) {
    vector<string>::iterator it = args.begin() + 1;
    if ((*it).empty())
        sendToClient(user, clientSocket, ERR_NEEDMOREPARAMS());
    else
        sendToClient(user, clientSocket, " PONG " + (*it));
}