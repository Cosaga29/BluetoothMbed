#include "BluetoothCom.h"

BluetoothCom::BluetoothCom(unsigned BaudRate, unsigned ByteSize, unsigned StopBits, unsigned Parity, Settings settings)
	: m_baudRate(BaudRate), m_byteSize(ByteSize), m_stopBits(StopBits), m_parity(Parity), m_tick(50)
{
	if (!Init(settings))
	{
		std::cout << "Error setting up port." << std::endl;
	}

}


bool BluetoothCom::Send(uint8_t* data, unsigned message_size, unsigned* bytes_sent)
{

	DWORD l_bytesSent = 0;
	unsigned attempts = 0;

	while (attempts < TIMEOUT && (DWORD)message_size != l_bytesSent)
	{
		//attempt to send
		WriteFile(hPort, (data + l_bytesSent), (message_size - l_bytesSent), &l_bytesSent, 0);

	}

	if (attempts == TIMEOUT)
	{
		return false;
	}

	return true;

}

Packet BluetoothCom::Receive(unsigned* bytes_received)
{
	uint8_t* receiveBuffer = (uint8_t*)malloc(BUFFER_SIZE);
	if (!receiveBuffer)
	{
		return { 0, 0 };
	}
	memset(receiveBuffer, 0, BUFFER_SIZE);

	DWORD l_bytesReceived;

	while (ReadFile(hPort, receiveBuffer, BUFFER_SIZE, &l_bytesReceived, 0));

	return { receiveBuffer, l_bytesReceived };
}


bool BluetoothCom::Init(Settings settings)
{
	if ((settings & Com::READ) && (settings & Com::WRITE) && (settings & Com::EXISTING))
	{
		hPort = CreateFile(
			"COM3",
			GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
		);
	}

	if (hPort == nullptr)
	{
		return false;
	}

	m_dcb = { 0 };
	
	GetCommState(hPort, &m_dcb);

	m_dcb.BaudRate = m_baudRate;
	m_dcb.ByteSize = m_byteSize;
	m_dcb.StopBits = m_stopBits;
	m_dcb.Parity = m_parity;

	SetCommState(hPort, &m_dcb);

	return true;

}