#include <vector>
#include "Com.h"

#define TIMEOUT 100
#define BUFFER_SIZE 256

class BluetoothCom : public Com
{
private:
	
	unsigned m_baudRate;
	unsigned m_byteSize;
	unsigned m_stopBits;
	unsigned m_parity;
	unsigned m_tick;

	DCB m_dcb;

public:

	BluetoothCom
	(
		unsigned BaudRate = CBR_9600, 
		unsigned ByteSize = 8, 
		unsigned StopBits = ONESTOPBIT, 
		unsigned Parity = NOPARITY, 
		Settings settings = (Com::READ | Com::WRITE | Com::EXISTING)
	);

	virtual bool Send(uint8_t* data, unsigned by_size, unsigned* bytes_sent = 0) override;
	virtual Packet Receive(unsigned* bytes_received = 0) override;
	virtual bool Init(Settings settings) override;

	inline bool GetTick() const { return m_tick; };
	inline bool SetTick(unsigned tick) { m_tick = tick; };

};
