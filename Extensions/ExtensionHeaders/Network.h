/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Standard Triangle Engine X Networking API.


SPECIFICATION:

 * set "TEX_EXPOSE_NETWORK" define to expose native if you are into that.

 * Full cross-compatibility.

 * Zero cost abstraction.

 * Full functionality of base APIS (winsock & linux berkeley sockets)

 * No loss of fidelity.

 * Not having to deal with a shit-ton of deprecated shit.

 * Utils can be imported. Network::Utils



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#define TEX_NETWORK_API

#ifdef TEX_EXPOSE_NETWORK

#ifdef _WIN32
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

typedef struct NetworkUtils
{
    WSADATA wsa;
}NetworkUtils;

#else

//linux verion of this

#endif

#endif

typedef enum NetworkProtocol{
    Protocol_HOPOPTS = 0,          /* IPv6 Hop-by-Hop options*/
    Protocol_ICMP = 1,
    Protocol_IGMP = 2,
    Protocol_GGP = 3,
    Protocol_IPV4 = 4,
    Protocol_ST = 5,
    Protocol_TCP = 6,
    Protocol_CBT = 7,
    Protocol_EGP = 8,
    Protocol_IGP = 9,
    Protocol_PUP = 12,
    Protocol_UDP = 17,
    Protocol_IDP = 22,
    Protocol_RDP = 27,
    Protocol_IPV6 = 41,         /* IPv6 header*/
    Protocol_ROUTING = 43,         /* IPv6 Routing header*/
    Protocol_FRAGMENT = 44,         /* IPv6 fragmentation header*/
    Protocol_ESP = 50,         /* encapsulating security payload*/
    Protocol_AH = 51,         /* authentication header*/
    Protocol_ICMPV6 = 58,         /* ICMPv6*/
    Protocol_NONE = 59,         /* IPv6 no next header*/
    Protocol_DSTOPTS = 60,         /* IPv6 Destination options */
    Protocol_ND = 77,
    Protocol_ICLFXBM = 78,
    Protocol_PIM = 103,
    Protocol_PGM = 113,
    Protocol_L2TP = 115,
    Protocol_SCTP = 132,
    Protocol_RAW = 255,
    Protocol_MAX = 256,
}NetworkProtocol;

typedef enum SocketTypes{
    Socket_Stream = 1,           /* stream socket */
    Socket_DataGram = 2,           /* datagram socket */
    Socket_RAW = 3,           /* raw-protocol interface */
    Socket_RDM = 4,           /* reliably-delivered message */
    Socket_SeqPacket = 5,           /* sequenced packet stream */
}SocketType;

typedef enum SendFlagBits{
    SendFlag_NormalBit = 0,
    SendFlag_OutOfBandBit = 0x1,
    SendFlag_DontRouteBit = 0x4
}SendFlagBits;

typedef enum RecieveFlagBits{
    RecieveFlag_NormalBit = 0,
    RecieveFlag_OutOfBandBit = 0x1,
    RecieveFlag_PeekBit = 0x2,
    RecieveFlag_WaitAllBit = 0x8
}RecieveFlagBits;

typedef uint64_t Socket;

typedef void AddressInfo; //pointer to native ADDERINFO //dont malloc

struct NetworkResStruct{
    void* pUtils;

    void* pInitialise_Network;
    void* pDestroy_Network;

    void* pGet_AddressInfos;
    void* pGet_AddressInfosSize;
    void* pDestroy_AddressInfos;

    void* pConnect;
    void* pDisconnect;

    void* pSend;
    void* pReceive;

    void* pGet_BacklogMax;
    void* pListen;
    void* pAccept_Connection;
}NetworkRes;

void Network_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize)
{
    memset(&NetworkRes, NULL, sizeof(NetworkRes));

    ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"Network::Utils"), &NetworkRes.pUtils);

    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Get_AddressInfos"), &NetworkRes.pGet_AddressInfos);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Get_AddressInfosSize"), &NetworkRes.pGet_AddressInfosSize);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Destroy_AddressInfos"), &NetworkRes.pDestroy_AddressInfos);

    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Connect"), &NetworkRes.pConnect);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Disconnect"), &NetworkRes.pDisconnect);

    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Send"), &NetworkRes.pSend);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Receive"), &NetworkRes.pReceive);

    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Get_BacklogMax"), &NetworkRes.pGet_BacklogMax);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Listen"), &NetworkRes.pListen);
    FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Network::Accept_Connection"), &NetworkRes.pAccept_Connection);


}

TEXRESULT Network_Get_AddressInfos(const UTF8* DNS, const UTF8* Service, AddressInfo** pResponse, NetworkProtocol Protocol, SocketType Type)
{
    TEXRESULT(*function)(const UTF8 * DNS, const UTF8 * Service, AddressInfo** pResponse, NetworkProtocol Protocol, SocketType Type) =
        (TEXRESULT(*)(const UTF8 * DNS, const UTF8 * Service, AddressInfo** pResponse, NetworkProtocol Protocol, SocketType Type))NetworkRes.pGet_AddressInfos;

    return function(DNS, Service, pResponse, Protocol, Type);
}

uint64_t Network_Get_AddressInfosSize(AddressInfo* addressinfos)
{
    uint64_t(*function)(AddressInfo * addressinfos) =
        (uint64_t(*)(AddressInfo * addressinfos))NetworkRes.pGet_AddressInfosSize;

    return function(addressinfos);
}

void Network_Destroy_AddressInfos(AddressInfo* addressinfos)
{
    void(*function)(AddressInfo * addressinfos) =
        (void(*)(AddressInfo * addressinfos))NetworkRes.pDestroy_AddressInfos;

    function(addressinfos);
}

TEXRESULT Network_Connect(Socket* pSocket, AddressInfo** addressinfo)
{
    TEXRESULT(*function)(Socket * pSocket, AddressInfo * *addressinfo) =
        (TEXRESULT(*)(Socket * pSocket, AddressInfo * *addressinfo))NetworkRes.pConnect;

    return function(pSocket, addressinfo);
}

TEXRESULT Network_Disconnect(Socket* pSocket)
{
    TEXRESULT(*function)(Socket * pSocket) =
        (TEXRESULT(*)(Socket * pSocket))NetworkRes.pDisconnect;

    return function(pSocket);
}

TEXRESULT Network_Send(Socket* pSocket, char* data, uint32_t size, SendFlagBits flagbits)
{
    TEXRESULT(*function)(Socket * pSocket, char* data, uint32_t size, SendFlagBits flagbits) =
        (TEXRESULT(*)(Socket * pSocket, char* data, uint32_t size, SendFlagBits flagbits))NetworkRes.pSend;

    return function(pSocket, data, size, flagbits);
}

TEXRESULT Network_Receive(Socket* pSocket, char* data, uint32_t size, RecieveFlagBits flagbits)
{
    TEXRESULT(*function)(Socket * pSocket, char* data, uint32_t size, RecieveFlagBits flagbits) =
        (TEXRESULT(*)(Socket * pSocket, char* data, uint32_t size, RecieveFlagBits flagbits))NetworkRes.pReceive;

    return function(pSocket, data, size, flagbits);
}

uint64_t Network_Get_BacklogMax()
{
    uint64_t(*function)() =
        (uint64_t(*)())NetworkRes.pGet_BacklogMax;

    return function();
}

TEXRESULT Network_Listen(Socket* pSocket, uint64_t backlog)
{
    TEXRESULT(*function)(Socket * pSocket, uint64_t backlog) =
        (TEXRESULT(*)(Socket * pSocket, uint64_t backlog))NetworkRes.pListen;

    return function(pSocket, backlog);
}

TEXRESULT Network_Accept_Connection(Socket* pSocket)
{
    TEXRESULT(*function)(Socket * pSocket) =
        (TEXRESULT(*)(Socket * pSocket))NetworkRes.pAccept_Connection;

    return function(pSocket);
}


