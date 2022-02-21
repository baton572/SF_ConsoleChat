#pragma once

#include <iostream>
#include <list>
#include <map>
#include "CUser.h"

#define SLOTSMAX 80
#define SLOTSIZE 10

class CChat1
{
public:
	CChat1() = delete;

	CChat1(
		void (*DisplayFunc)(const std::string& _s),
		void (*InputString)(const std::string& _s, std::string& _t1));

	CChat1(const CChat1& _chat) = delete;

	CChat1& operator=(const CChat1& _chat) = delete;

	virtual ~CChat1();

	virtual void CommandHandler(const std::string&);

	virtual void DisplayStatus();

	virtual void DisplayMessage(const std::string&);

	virtual void Users();

	std::list< CUser* >::iterator FindUser(const std::string& _s);

	virtual bool AddUser();

	virtual bool DelUser();

	virtual bool Enter();

	virtual void DisplayMessages();

	virtual bool Exit();

	virtual bool Send();

private:
	void (*m_OutputString)(const std::string& _s);
	void (*m_InputString)(const std::string& _s, std::string& _t1);
	//
	CUser* m_pCurrentUser;
	//
	std::list< CUser* > m_users;
};
