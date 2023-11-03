#include "server.hpp"

void SendToClient(int clientSocket, const std::string& message) {
    string sending = message + "\r\n";
    send(clientSocket, sending.c_str(), sending.size(), 0);
}

string Server::cmd(std::string& wholeMsg) {
    return (wholeMsg.substr(0, wholeMsg.find(' ')));
}

void Server::FindCmd(string msg, int clientSocket) {
    string parsedCmd = cmd(msg);

    if(parsedCmd == "WHO\n") {
       commands.whoCmd(this->user, clientSocket);
    }
    if(parsedCmd == "NICK") {
        this->user.setNickName(msg.substr(5, msg.find(' ') + 1));
        string message = "Nick changed! Updated nick : " + user.getNickName() + "\n";
        SendToClient(clientSocket, message);
    }
}
