#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

class Encryption
{
private:
	std::string m_key;
	std::string m_message;
	std::vector<std::string> m_encryptionData;
	std::string m_encryptedMessage;
public:
	Encryption() = default;
	Encryption(std::string key, std::string message);
	void PrintEncryptionData();
	std::vector<std::string> GetEncryptionData() const noexcept;
	std::string GetKey() const noexcept;
	std::string getMessage() const noexcept;
	std::string GetEncryptedMessage() const noexcept;
	void EncryptMessage();
};

