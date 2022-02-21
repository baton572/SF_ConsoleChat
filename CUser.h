#pragma once

#include <list>
#include <vector>
#include <string>

struct ChatMessages
{
	ChatMessages(std::string _from, std::string* _message)
		: from(_from)
	{
		messages.push_back(_message);
	}

	std::string from;
	std::vector< std::string* > messages;
};

class CUser
{
public:
	CUser() = delete;

	CUser(const std::string& _login, const std::string& _password);

	CUser(const CUser&) = delete;

	CUser& operator=(const CUser&) = delete;

	~CUser();

	friend const bool operator== (const CUser& _P1, const CUser& _P2);
	friend const bool operator!= (const CUser& _P1, const CUser& _P2);

	CUser& operator<< (ChatMessages&);
	//CUser& operator<< (std::string& from, std::vector < std::string* > _messages);

	virtual const std::string& GetLogin();
	virtual const std::string& GetPass();
	virtual const std::string* GetNextSender();
	virtual const std::string* GetNextMessage();

private:
	const std::string m_login;
	const std::string m_pass;
	//
	std::list< ChatMessages > m_messages;
};
