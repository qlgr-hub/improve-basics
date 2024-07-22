#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>
#include <sstream>

using namespace std;

//using SOCKET = int;

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>

#define UsingWinsock 1

using ssize_t = SSIZE_T;

#else // !_MSC_VER

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define UsingWinsock 0

#endif // _MSC_VER


class WinsockWrapper
{
public:
    WinsockWrapper()
    {
#if UsingWinsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            exit(1);
        }

        cout << "Winsock started!" << endl;
#endif // UsingWinsock
    }

    ~WinsockWrapper()
    {
#if UsingWinsock
        WSACleanup();

        cout << "Winsock shut down!" << endl;
#endif // UsingWinsock     
    }
};

class Socket
{
private:
#if !UsingWinsock
    using SOCKET = int;
#endif // UsingWinsock

    addrinfo* m_ServerInfo{ nullptr };
    SOCKET m_Socket{ static_cast<SOCKET>(0xFFFFFFFF) };
    sockaddr_storage m_AcceptedSocketStorage{};
    socklen_t m_AcceptedSocketSize{ sizeof(m_AcceptedSocketStorage) };

    void CreateSocket(string& webAddress, string& port, addrinfo& hints)
    {
        getaddrinfo(webAddress.empty() ? NULL : webAddress.c_str(), port.c_str(), &hints, &m_ServerInfo);

        m_Socket = socket(m_ServerInfo->ai_family, m_ServerInfo->ai_socktype, m_ServerInfo->ai_protocol);
    }

    Socket(SOCKET newSocket, sockaddr_storage&& socketStorage)
        : m_Socket{ newSocket }
        , m_AcceptedSocketStorage{ socketStorage }
    {

    }

public:
    Socket(string& port)
    {
#ifndef NDEBUG
        stringstream portStream{ port };
        int portValue{};
        portStream >> portValue;
        assert(portValue > 1024);
        // Ports under 1024 are reserved for certain applications and protocals!
#endif // !NDEBUG

        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        string address{ "" };
        CreateSocket(address, port, hints);
    }

    Socket(string& webAddress, string& port)
    {
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        CreateSocket(webAddress, port, hints);
    }

    Socket(string& webAddress, string& port, addrinfo& hints)
    {
        CreateSocket(webAddress, port, hints);
    }

    ~Socket()
    {
        Close();
    }

    bool IsValid()
    {
        return m_Socket != -1;
    }

    int Connect()
    {
        int connectionResult{ connect(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen) };

#ifndef NDEBUG
        if (connectionResult == -1) {
            cout << "Connection failed!" << endl;
        }
        else {
            cout << "Connection Succeeded" << endl;
        }
#endif // !NDEBUG

        return connectionResult;
    }

    int Bind()
    {
        int bindResult{ bind(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen) };

#ifndef NDEBUG
        if (bindResult == -1) {
            cout << "Bind failed!" << endl;
        }
        else {
            cout << "Bind Succeeded" << endl;
        }
#endif // !NDEBUG

        return bindResult;
    }

    int Listen(int queueSize)
    {
        int listenResult{ listen(m_Socket, queueSize) };

#ifndef NDEBUG
        if (listenResult == -1) {
            cout << "Listen failed!" << endl;
        }
        else {
            cout << "Listen Succeeded" << endl;
        }
#endif // !NDEBUG

        return listenResult;
    }

    Socket Accept()
    {
        SOCKET newSocket{ accept(m_Socket, reinterpret_cast<sockaddr*>(&m_AcceptedSocketStorage), &m_AcceptedSocketSize) };

#ifndef NDEBUG
        if (newSocket == -1) {
            cout << "Accept failed!" << endl;
        }
        else {
            cout << "Accept Succeeded" << endl;
        }
#endif // !NDEBUG

        m_AcceptedSocketSize = sizeof(m_AcceptedSocketStorage);
        return Socket(newSocket, move(m_AcceptedSocketStorage));
    }

    void Close()
    {
#if UsingWinsock
        closesocket(m_Socket);
#else
        close(m_Socket);
#endif // UsingWinsock

        m_Socket = -1;
        freeaddrinfo(m_ServerInfo);
    }

    ssize_t Send(stringstream data)
    {
        string packetData{ data.str() };
        ssize_t sendResult{ send(m_Socket, packetData.c_str(), packetData.length(), 0) };

#ifndef NDEBUG
        if (sendResult == -1) {
            cout << "Send failed!" << endl;
        }
        else {
            cout << "Send Succeeded" << endl;
        }
#endif // !NDEBUG

        return sendResult;
    }

    stringstream Receive()
    {
        const int size{ 1024 };
        char dataReceived[size]{};
        ssize_t receiveResult{ recv(m_Socket, dataReceived, size, 0) };

#ifndef NDEBUG
        if (receiveResult == -1) {
            cout << "Receive failed!" << endl;
        }
        else if (receiveResult == 0) {
            cout << "Receive Detected Closed Connection!" << endl;
            Close();
        }
        else {
            dataReceived[receiveResult] = '\0';
            cout << "Receive Succeeded" << endl;
        }
#endif // !NDEBUG

        stringstream data{ dataReceived };
        return move(data);
    }
};


int main()
{
    WinsockWrapper myWinsockWrapper;

    string address{ "127.0.0.1" };
    string port{ "3000" };
    Socket myConnectingSocket(address, port);
    
    int connectResult{ myConnectingSocket.Connect() };
    assert(connectResult != -1);

    string message{ "Sending Data Over a NetWork!" };
    stringstream data;
    data << message;

    myConnectingSocket.Send(move(data));

    return 0;
}