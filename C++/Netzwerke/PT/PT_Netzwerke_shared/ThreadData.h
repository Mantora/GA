#pragma once

class Socket_TCP_windows;

struct ThreadData
{
	SOCKET connectedSocket;
	Socket_TCP_windows* serverInstance;
	SOCKADDR_IN clientDatas;

	ThreadData( Socket_TCP_windows* serverInstance, SOCKET connectedSocket, SOCKADDR_IN clientDatas )
	{
		connectedSocket = connectedSocket;
		serverInstance = serverInstance;
		clientDatas = clientDatas;
	};
};