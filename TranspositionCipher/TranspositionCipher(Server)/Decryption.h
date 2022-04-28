#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
class Decryption
{
private:
	std::string m_key;
	std::string m_decryptedMessage;
	std::vector<std::string> m_decryptionData;
	std::string m_encryptedMessage;
public:
	Decryption() = default;
	Decryption(std::string key, std::string encryptedMessage);
	void PrintDecryptionData();
	void DecryptMessage();
};

