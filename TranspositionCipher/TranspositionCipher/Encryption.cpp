#include "Encryption.h"

Encryption::Encryption(std::string key, std::string message) : m_key{ key }, m_message{ message }
{

	while ((float)m_message.size() / m_key.size() != (int)m_message.size() / m_key.size())
	{
		m_message.append("*");
	}

	m_encryptionData.resize(m_key.size());
	for (int i = 0; i < m_key.size(); ++i)
	{
		m_encryptionData[i].push_back(m_key[i]);
	}

	int index = 0;
	for (int i = 0; i < m_message.size(); ++i)
	{
		if (index == 5)
			index = 0;
		m_encryptionData[index].push_back(m_message[i]);
		index++;
	}

	/*for (const auto& line : m_encryptionData)
	{
		std::cout << line << std::endl;
	}
	std::cout << std:: endl;*/
}

void Encryption::PrintEncryptionData()
{

	int indexMax = m_message.size() / m_encryptionData.size() + 1;
	//std::cout << indexMax << std::endl;
	for (int i = 0; i < indexMax; ++i)
	{
		for (int j = 0; j < m_key.size(); ++j)
		{
			std::cout << m_encryptionData[j][i] << " ";
		}
		std::cout << std:: endl;
	}
	std::cout << std::endl;
}

std::vector<std::string> Encryption::GetEncryptionData() const noexcept
{
	return m_encryptionData;
}

std::string Encryption::GetKey() const noexcept
{
	return m_key;
}

std::string Encryption::getMessage() const noexcept
{
	return m_message;
}

std::string Encryption::GetEncryptedMessage() const noexcept
{
	return m_encryptedMessage;
}

void Encryption::EncryptMessage()
{



	std::vector<std::string>tempEncryptionData = m_encryptionData;
	std::sort(tempEncryptionData.begin(), tempEncryptionData.end());

	for (const auto& line : tempEncryptionData)
	{
		
		m_encryptedMessage += line.substr(1, line.size());
	}
	std::cout << std::endl;

	
}
