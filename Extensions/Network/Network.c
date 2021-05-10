#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//Main
#include "Extension.h"
#define TEX_EXPOSE_NETWORK
#include "Network.h"

volatile struct
{
	uint64_t test;
}Config;

volatile NetworkUtils Utils;


TEXRESULT Get_AddressInfos(const UTF8* DNS, const UTF8* Service, AddressInfo** pResponse, NetworkProtocol Protocol, SocketType Type)
{
#ifndef NDEBUG
	if (DNS == NULL)
	{
		Engine_Ref_ArgsError("Get_AddressInfos()", "DNS == NULLPTR");
		return Invalid_Parameter | Failure;
	}
	if (DNS == NULL)
	{
		Engine_Ref_ArgsError("Get_AddressInfos()", "DNS == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif

	ADDRINFOW Hints;
	memset((void*)&Hints, 0, sizeof(Hints));
	Hints.ai_family = AF_UNSPEC;
	switch (Type)
	{
	case Socket_Stream:
		Hints.ai_socktype = SOCK_STREAM;
		break;
	case Socket_DataGram:
		Hints.ai_socktype = SOCK_DGRAM;
		break;
	case Socket_RAW:
		Hints.ai_socktype = SOCK_RAW;
		break;
	case Socket_RDM:
		Hints.ai_socktype = SOCK_RDM;
		break;
	case Socket_SeqPacket:
		Hints.ai_socktype = SOCK_SEQPACKET;
		break;
	}
	/*
	switch (Protocol)
	{
	case Stream:
		Hints.ai_protocol = IPPRTO
		break;
	}
	*/
	Hints.ai_protocol = (int)Protocol;

	LPWSTR dns = NULL;
	LPWSTR srv = NULL;

	uint32_t dnss = MultiByteToWideChar(CP_UTF8, 0, (char*)DNS, -1, dns, 0); //windows why dont you change to UTF-32 it pains me.
	uint32_t srvs = MultiByteToWideChar(CP_UTF8, 0, (char*)Service, -1, srv, 0);

	dns = calloc(dnss, sizeof(WCHAR));
	srv = calloc(srvs, sizeof(WCHAR));

	MultiByteToWideChar(CP_UTF8, 0, (char*)DNS, -1, dns, dnss); //windows why dont you change to UTF-32 it pains me.
	MultiByteToWideChar(CP_UTF8, 0, (char*)Service, -1, srv, srvs);

	if (GetAddrInfoW(dns, srv, &Hints, (ADDRINFOW**)pResponse) != NULL)
	{
		Engine_Ref_FunctionError("Get_AddressInfos()", WSAGetLastError(), 0);
		return Failure;
	}

	free(dns);
	free(srv);
	return Success;
}


uint64_t Get_AddressInfosSize(AddressInfo* addressinfos)
{
	uint64_t it = 0;
	while (((ADDRINFOW*)addressinfos)->ai_next != NULL)
	{
		it++;
	}
	return it;
}

void Destroy_AddressInfos(AddressInfo* addressinfos)
{
	free(addressinfos);
}




TEXRESULT Connect(Socket* pSocket, AddressInfo** addressinfo)
{
	SOCKADDR_STORAGE_LH* storage = (SOCKADDR_STORAGE_LH*)((ADDRINFOW*)*addressinfo)->ai_addr;

	*pSocket = socket(((ADDRINFOW*)*addressinfo)->ai_family, ((ADDRINFOW*)*addressinfo)->ai_socktype, ((ADDRINFOW*)*addressinfo)->ai_protocol);

	if (connect(*pSocket, (SOCKADDR*)storage, sizeof(SOCKADDR_STORAGE_LH)) == SOCKET_ERROR)
	{
		closesocket(*pSocket);
		Engine_Ref_FunctionError("Connect()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}

TEXRESULT Disconnect(Socket* pSocket)
{
	closesocket(*pSocket);

	return Success;
}

TEXRESULT Send(Socket* pSocket, char* data, uint32_t size, SendFlagBits flagbits)
{
	if (send(*pSocket, data, size, (int)flagbits) == SOCKET_ERROR)
	{
		Engine_Ref_FunctionError("Send()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}

TEXRESULT Receive(Socket* pSocket, char* data, uint32_t size, RecieveFlagBits flagbits)
{
	if (recv(*pSocket, data, size, (int)flagbits) == SOCKET_ERROR)
	{
		Engine_Ref_FunctionError("Receive()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}

uint64_t Get_BacklogMax()
{
	return SOMAXCONN;
}


TEXRESULT Listen(Socket* pSocket, uint64_t backlog)
{
	if (listen(*pSocket, backlog) == SOCKET_ERROR)
	{
		Engine_Ref_FunctionError("Listen()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}

TEXRESULT Accept_Connection(Socket* pSocket)
{
	if (accept(*pSocket, 0, 0) == SOCKET_ERROR)
	{
		Engine_Ref_FunctionError("Accept_Connection()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}

TEXRESULT Poll_Events()
{


	return Success;
}




TEXRESULT Initialise_Network()
{
	memset((void*)&Utils, 0, sizeof(Utils));
	memset((void*)&Config, 0, sizeof(Config));

	if (WSAStartup(MAKEWORD(2, 2), &Utils.wsa) != 0)
	{
		Engine_Ref_FunctionError("Initialise_Network()", WSAGetLastError(), 0);
		return Failure;
	}
	return Success;
}


void Destroy_Network()
{
	WSACleanup();
	memset((void*)&Utils, 0, sizeof(Utils));
	memset((void*)&Config, 0, sizeof(Config));
}



//entry point to the extension
//this functions purpose is to register everything with the application. One time only.
__declspec(dllexport) void Initialise_Resources(ExtensionCreateInfo* ReturnInfo)
{

#ifdef NDEBUG
	ReturnInfo->BinType = Release;
#else
	ReturnInfo->BinType = Debug;
#endif

	MakeVersion(ReturnInfo->ExtensionVersion, 1, 0, 0);
	MakeVersion(ReturnInfo->MinRequiredVersion, 1, 0, 0);
	MakeVersion(ReturnInfo->MaxRequiredVersion, UINT32_MAX, UINT32_MAX, UINT32_MAX);


	Engine_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Network::Utils"), &NetworkRes.pUtils, &Utils);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Initialise_Network"), &NetworkRes.pInitialise_Network, &Initialise_Network, Construct, Single_Thread, 0.1f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Destroy_Network"), &NetworkRes.pDestroy_Network, &Destroy_Network, Destruct, Single_Thread, 100.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Get_AddressInfos"), &NetworkRes.pGet_AddressInfos, &Get_AddressInfos, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Get_AddressInfosSize"), &NetworkRes.pGet_AddressInfosSize, &Get_AddressInfosSize, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Destroy_AddressInfos"), &NetworkRes.pDestroy_AddressInfos, &Destroy_AddressInfos, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Connect"), &NetworkRes.pConnect, &Connect, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Disconnect"), &NetworkRes.pDisconnect, &Disconnect, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Send"), &NetworkRes.pSend, &Send, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Receive"), &NetworkRes.pReceive, &Receive, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Get_BacklogMax"), &NetworkRes.pGet_BacklogMax, &Get_BacklogMax, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Listen"), &NetworkRes.pListen, &Listen, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Network::Accept_Connection"), &NetworkRes.pAccept_Connection, &Accept_Connection, (CallFlagBits)NULL, (FunctionThreadingMode)NULL, 0.0f, NULL, NULL);

}




