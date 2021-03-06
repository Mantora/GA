#pragma once

#define ZMQ_PAIR 0
#define ZMQ_PUB 1
#define ZMQ_SUB 2
#define ZMQ_REQ 3
#define ZMQ_REP 4
#define ZMQ_DEALER 5
#define ZMQ_ROUTER 6
#define ZMQ_PULL 7
#define ZMQ_PUSH 8
#define ZMQ_XPUB 9
#define ZMQ_XSUB 10

class ZeroMqConnector
{
public:
	ZeroMqConnector(int zmqSocketType);
	~ZeroMqConnector(void);

	bool setup();
	bool shutdown();

	bool connect(const char* address);
	bool bind(const char* address);

	bool send(void* data, size_t len);
	bool receive(void** outBuffer, size_t* outSize);

private:
	int socketType;

	void* context;
	void* socket;
};

