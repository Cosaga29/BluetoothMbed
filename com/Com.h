#pragma once

#include <iostream>
#include <ctype.h>
#include <Windows.h>

#define BIT(x) (1 << x)

typedef DWORD Settings;

struct Packet
{
	uint8_t* receiveBuffer;
	unsigned int bytes_read;
};

class Com
{

public:

	enum EnumSettings
	{
		READ = BIT(0),
		WRITE = BIT(1),
		EXISTING = BIT(2)
	};

protected:

	HANDLE hPort;

public:

	virtual bool Send(uint8_t* data, unsigned by_size, unsigned* bytes_sent = 0) = 0;
	virtual bool TimedSend(float ms_delay, uint8_t* data, unsigned by_size = 1, unsigned* bytes_sent = 0) = 0;
	virtual Packet Receive(unsigned* bytes_received = 0) = 0;
	virtual bool Init(const std::string& comPortName, Settings settings) = 0;

};