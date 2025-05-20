#include "client_protocol.h"
#include "defs.h"




ClientProtocol::ClientProtocol(const char* servname, const char* port) :
    skt(Socket(servname, port)) {
    wasClosed = false;
}



ServerMessage ClientProtocol::recv_message() {
    ServerMessageType t = ServerMessageType::InvalidServerMessage;
    ClientMessageData d = std::monostate{}; 
    recvall(skt, &t, 1);
    switch (t)
    {
    case ServerMessageType::LobbySnapshot :   
        /* code */
        break;
    case ServerMessageType::RoomSnapshot :
        /* code */
        break;
    case ServerMessageType::GameSnapshot :
        /* code */
        break;
         
    default:
        break;
    }
    return ServerMessage{t, d};
}





void ClientProtocol::send_message(ClientMessage msg) {
    sendall(skt, &msg.type, 1);
    switch (msg.type)
    {
    case ClientMessageType::CreateGame :
        {
            CreateGame c = std::get<CreateGame>(msg.data);
            sendString(skt, c.gameName);
            sendShort(skt, &c.mapId);
        }
        break;

    case ClientMessageType::ConnectGame :
        {
            ConnectGame c = std::get<ConnectGame>(msg.data);
            sendShort(skt, &c.gameId);
        }
        break;

    default:
        break;
    }   
}


void ClientProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}












