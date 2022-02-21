#include "CUser.h"

CUser::CUser(const std::string& _login, const std::string& _password)
	: m_login(_login)
	, m_pass(_password)
{
}

CUser::~CUser()
{
	for (auto from : m_messages)
	{
		for (auto m : from.messages)
			delete m;
	}
}

const bool operator==(const CUser& _P1, const CUser& _P2)
{
	return _P1.m_login == _P2.m_login;
}

const bool operator!=(const CUser& _P1, const CUser& _P2)
{
	return _P1.m_login != _P2.m_login;
}

CUser& CUser::operator<<(ChatMessages& _messages)
{
	ChatMessages* pFrom = nullptr;
	//
	for (auto u : m_messages)
	{
		if (u.from == _messages.from)
		{
			pFrom = &u;
			break;
		}
	}
	//
	if (pFrom)
	{
		for (auto m : _messages.messages)
			pFrom->messages.push_back(m);
	}
	else
	{
		m_messages.push_back(_messages);
	}
	//
	return *this;
}

//CUser& CUser::operator<<(std::string& from, std::vector < std::string* > _messages)
//{
//	ChatMessages* pFrom = nullptr;
//	//
//	for (auto u : m_messages)
//	{
//		if (u.from == _messages.from)
//		{
//			pFrom = &u;
//			break;
//		}
//	}
//	//
//	if (pFrom)
//	{
//		for (auto m : _messages.messages)
//			pFrom->messages.push_back(m);
//	}
//	else
//	{
//		m_messages.push_back(_messages);
//	}
//	//
//	return *this;
//}

const std::string& CUser::GetLogin()
{
	return m_login;
}

const std::string& CUser::GetPass()
{
	return m_pass;
}
