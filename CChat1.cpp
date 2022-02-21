#include "CChat1.h"

CChat1::CChat1(
    void (*OutputString)(const std::string& _s),
    void (*InputString)(const std::string& _s, std::string& _t1))
    //
    : m_pCurrentUser(nullptr)
    , m_OutputString(OutputString)
    , m_InputString(InputString)
{
}

CChat1::~CChat1()
{
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        delete* it;
    }
}

void CChat1::DisplayMessage(const std::string& _s)
{
    m_OutputString(_s);
}

void CChat1::CommandHandler(const std::string& _s)
{
    std::string s = "\r\n";
    //
    if (_s == "?")
    {
        s += "Commands:\r\n";
        s += "users, adduser, deluser, enter, exit, send [login / all]\r\n";
        //
        DisplayMessage(s);
    }
    else
    {
        if (_s == "status")
        {
            DisplayStatus();
        }
        else if (_s == "users")
        {
            Users();
        }
        else if (_s == "adduser")
        {
            AddUser();
        }
        else if (_s == "deluser")
        {
            DelUser();
        }
        else if (_s == "enter")
        {
            Enter();
        }
        else if (_s == "exit")
        {
            Exit();
        }
        else if (_s == "send")
        {
            Send();
        }
        else
        {
            DisplayMessage("\r\nUnknown command!\r\n");
        }
    }
}

void CChat1::DisplayStatus()
{
    std::string s = "\r\nChat 1.0\r\n";
    s += "Users   : ";
    s += std::to_string(m_users.size()) + "\r\n";
    s += "Messages: ";
    //
    //for ()

    //s += std::to_string(m_slotsEmpty) + "\r\n";
    //s += "Slot size  : ";
    //s += std::to_string(m_slotSize) + "\r\n";
    //s += "Snack types: ";
    //s += (m_types.size() > 0 ? std::to_string(m_types.size()) : "-") + "\r\n";
    //
    DisplayMessage(s);
}

void CChat1::Users()
{
    std::string s = "\r\nUsers:";
    if (m_users.size() > 0)
    {
        for (auto it = m_users.begin(); it != m_users.end(); ++it)
            s += "\r\nLogin: " + (*it)->GetLogin();
        s += "\r\n";
    }
    else
        s += " -\r\n";
    //
    DisplayMessage(s);
}

std::list< CUser* >::iterator CChat1::FindUser(const std::string& _s)
{
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it)->GetLogin() == _s)
        {
            return it;
        }
    }
    return m_users.end();
}

bool CChat1::AddUser()
{
    std::string login;
    m_InputString("\r\nLogin: ", login);
    //
    auto it = FindUser(login);
    if (it != m_users.end())
    {
        DisplayMessage("Already existed!\r\n");
        return false;
    }
    //
    std::string pass;
    m_InputString("\r\nPassword: ", pass);
    //
    DisplayMessage("");
    //
    CUser* pUser = new CUser(login, pass);
    if (pUser)
    {
        m_users.push_back(pUser);
        return true;
    }
    return false;
}

bool CChat1::DelUser()
{
    std::string s;
    m_InputString("\r\nLogin: ", s);
    //
    auto it = FindUser(s);
    if (it == m_users.end())
    {
        DisplayMessage("Login is not found!\r\n");
        return false;
    }
    std::string pass;
    m_InputString("\r\nPassword: ", pass);
    //
    DisplayMessage("");
    //
    if (pass == (*it)->GetPass())
    {
        delete* it;
        m_users.erase(it);
        //
        return true;
    }
    else
    {
        DisplayMessage("Incorrect password!\r\n");
        return false;
    }
}

bool CChat1::Enter()
{
    if (m_pCurrentUser)
    {
        DisplayMessage("Interface is in use!\r\n");
        return false;
    }
    else
    {
        std::string s;
        m_InputString("\r\nLogin: ", s);
        //
        auto it = FindUser(s);
        if (it == m_users.end())
        {
            DisplayMessage("Login is not found!\r\n");
            return false;
        }
        std::string pass;
        m_InputString("\r\nPassword: ", pass);
        //
        DisplayMessage("");
        //
        if (pass == (*it)->GetPass())
        {
            m_pCurrentUser = *it;
            return true;
        }
        else
        {
            DisplayMessage("Incorrect password!\r\n");
            return false;
        }
    }
}

void CChat1::DisplayMessages()
{
    if (m_pCurrentUser)
    {
        for (auto from : m_pCurrentUser->m_messages)
        Displa



    }
}

bool CChat1::Exit()
{
    DisplayMessage("Interface is free!\r\n");
    //
    if (m_pCurrentUser)
        return true;
    else
        return false;
}

bool CChat1::Send()
{
    if (m_pCurrentUser)
    {
        std::string address;
        std::string* message = new std::string;
        m_InputString("\r\nRecipient: ", address);
        //
        m_InputString("\r\nMessage:   ", *message);

        for (auto user : m_users)
        {
            if (user->GetLogin() == address)
            {
                auto letter = ChatMessages(address, message);
                (*user) << letter;
                //
                return true;
            }
        }
    }
    //
    return false;
}
