#include "socket.h"

Socket::Socket() {

}
Socket ::~Socket() {

}

int Socket::init_and_connect() {
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }
    else {
        std::cout << "WSAStartup Successful.\n";
    }
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 2;
    }
    else {
        std::cout << "Socket Successful.\n";
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    InetPton(AF_INET, L"192.168.1.5", &address.sin_addr.s_addr);

    // Kết nối với máy chủ
    iResult = connect(connectSocket, (sockaddr*)&address, sizeof(address));
    if (iResult == SOCKET_ERROR) {
        std::cout << "connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 3;
    }
    else {
        std::cout << "Successful connected.\n";
    }
}
void Socket::break_up() {
    closesocket(connectSocket);
    WSACleanup();
}
int Socket::send_Event(int type, int x, int y) {
    char message[12] = { '\0' };

    // Convert int to char
    int networkEvent = htonl(type);
    memcpy(message + 0 * sizeof(int), &networkEvent, sizeof(int));
    networkEvent = htonl(x);
    memcpy(message + 1 * sizeof(int), &networkEvent, sizeof(int));
    networkEvent = htonl(y);
    memcpy(message + 2 * sizeof(int), &networkEvent, sizeof(int));
    for (int i = 0; i < 3; i++) {
        int networkInteger;
        memcpy(&networkInteger, message + i * sizeof(int), sizeof(int));
        data[i] = ntohl(networkInteger); // Chuyển đổi dữ liệu từ dạng mạng sang dạng máy tính (Little Endian)
    }
    int bytesSent = send(connectSocket, message, 12, 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 0;
    }
    return 1;
}