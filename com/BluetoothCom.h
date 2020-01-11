#pragma once

#include <vector>
#include <chrono>

#include "Com.h"

#define TIMEOUT 100
#define BUFFER_SIZE 256
#define DELAY_FACTOR 100000

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds mcs;
typedef std::chrono::nanoseconds ncs;
typedef std::chrono::duration<double> duration;

class BluetoothCom : public Com
{
private:
	
	std::string m_comPortName;
	unsigned m_baudRate;
	unsigned m_byteSize;
	unsigned m_stopBits;
	unsigned m_parity;
	unsigned m_tick;

	DCB m_dcb;

public:

	BluetoothCom
	(
		const std::string& comPortName = "COM4",
		unsigned BaudRate = CBR_9600, 
		unsigned ByteSize = 8, 
		unsigned StopBits = ONESTOPBIT, 
		unsigned Parity = NOPARITY, 
		Settings settings = (Com::READ | Com::WRITE | Com::EXISTING)
	);

	virtual bool Send(uint8_t* data, unsigned by_size, unsigned* bytes_sent = 0) override;
	virtual bool TimedSend(float ms_delay, uint8_t* data, unsigned by_size, unsigned* bytes_sent = 0) override;
	virtual Packet Receive(unsigned* bytes_received = 0) override;
	virtual bool Init(const std::string& comPortName, Settings settings) override;

	inline bool GetTick() const { return m_tick; };
	inline bool SetTick(unsigned tick) { m_tick = tick; };

};
