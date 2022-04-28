#include "Decryption.h"

Decryption::Decryption(std::string key, std::string encryptedMessage) : m_key{ key }, m_encryptedMessage{ encryptedMessage }
{
	int index = m_encryptedMessage.size() / m_key.size();
	std::cout << index << std::endl;
	m_decryptionData.resize(m_key.size());
	for (int i = 0; i < m_key.size(); ++i)
	{
		m_decryptionData[i].push_back(m_key[i]);
	}

	std::sort(m_decryptionData.begin(), m_decryptionData.end());
	int j = 0;
	for (int i = 0; i < m_key.size(); ++i)
	{
		int tempIndex = 0;
		for (; j < encryptedMessage.size() && tempIndex < index; ++j, ++tempIndex)
		{
			m_decryptionData[i] += encryptedMessage[j];
		}
	}
	std::cout << std::endl;

}

void Decryption::PrintDecryptionData()
{
	std::cout << m_encryptedMessage << std::endl;
	int indexMax = m_encryptedMessage.size() / m_key.size() + 1;
	//std::cout << indexMax << std::endl;
	for (int i = 0; i < indexMax; ++i)
	{
		for (int j = 0; j < m_key.size(); ++j)
		{
			std::cout << m_decryptionData[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Decryption::DecryptMessage()
{
	std::unordered_map<char, int> tempMap;
	for (int i = 0; i < m_key.size(); ++i)
	{
		tempMap.insert(std::pair<char, int>(m_key[i], i));
	}

	std::vector < std::string> tempDecryptionData;
	tempDecryptionData.resize(m_key.size());




}
