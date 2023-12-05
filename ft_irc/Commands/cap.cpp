#include "../commands.hpp"

void Commands::Cap(User &user, int clientSocket)
{
    sendToClient(user, clientSocket, " CAP * LS :multi-refix sasl");
}
