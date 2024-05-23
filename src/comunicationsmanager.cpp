/**
 * @file src/comunicationsmanager.cpp
 * @brief MEGAcmd: Communications manager non supporting non-interactive mode
 *
 * (c) 2013 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGAcmd.
 *
 * MEGAcmd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#include "comunicationsmanager.h"

using namespace mega;

namespace megacmd {
OUTSTREAMTYPE &operator<<(OUTSTREAMTYPE &os, const CmdPetition& p)
{
    return os << p.line;
}

#ifdef _WIN32
std::ostream &operator<<(std::ostream &os, const CmdPetition& p)
{
    return os << p.line;
}
#endif

ComunicationsManager::ComunicationsManager()
{
}

bool ComunicationsManager::receivedPetition()
{
    return false;
}

void ComunicationsManager::registerStateListener(CmdPetition *inf)
{
    std::lock_guard<std::recursive_mutex> g(mStateListenersMutex);
    stateListenersPetitions.push_back(inf);
    if (stateListenersPetitions.size() >MAXCMDSTATELISTENERS && stateListenersPetitions.size()%10 == 0)
    {
        LOG_debug << " Number of register listeners has grown too much: " << stateListenersPetitions.size() << ". Sending an ACK to discard disconnected ones.";
        string sack="ack";
        informStateListeners(sack);
    }
    return;
}

int ComunicationsManager::waitForPetition()
{
    return 0;
}


void ComunicationsManager::stopWaiting()
{
}

int ComunicationsManager::get_next_comm_id()
{
    return 0;
}

bool ComunicationsManager::informStateListeners(string &s)
{
    s+=(char)0x1F;
    std::lock_guard<std::recursive_mutex> g(mStateListenersMutex);

    for (std::vector< CmdPetition * >::iterator it = stateListenersPetitions.begin(); it != stateListenersPetitions.end();)
    {
        if (informStateListener((CmdPetition *)*it, s) <0)
        {
            delete *it;
            it = stateListenersPetitions.erase(it);
        }
        else
        {
             ++it;
        }
    }

    if (!stateListenersPetitions.size())
    {
        return false;
    }
    return true;
}

void ComunicationsManager::informStateListenerByClientId(string &s, int clientID)
{
    s+=(char)0x1F;

    std::lock_guard<std::recursive_mutex> g(mStateListenersMutex);
    for (std::vector< CmdPetition * >::iterator it = stateListenersPetitions.begin(); it != stateListenersPetitions.end();)
    {
        if ((clientID == ((CmdPetition *)*it)->clientID ) && informStateListener((CmdPetition *)*it, s) <0)
        {
            delete *it;
            it = stateListenersPetitions.erase(it);
        }
        else
        {
             ++it;
        }
    }
}
int ComunicationsManager::informStateListener(CmdPetition *inf, string &s)
{
    return 0;
}

void ComunicationsManager::returnAndClosePetition(CmdPetition *inf, OUTSTRINGSTREAM *s, int outCode)
{
    delete inf;
    return;
}

void ComunicationsManager::sendPartialOutput(CmdPetition *inf, OUTSTRING *s)
{
    return;
}

void ComunicationsManager::sendPartialOutput(CmdPetition *inf, char *s, size_t size)
{
    return;
}



/**
 * @brief getPetition
 * @return pointer to new CmdPetition. Petition returned must be properly deleted (this can be calling returnAndClosePetition)
 */
CmdPetition * ComunicationsManager::getPetition()
{
    CmdPetition *inf = new CmdPetition();
    return inf;
}

int ComunicationsManager::getConfirmation(CmdPetition *inf, string message)
{
    return MCMDCONFIRM_NO;
}

std::string ComunicationsManager::getUserResponse(CmdPetition *inf, string message)
{
    return string();
}

ComunicationsManager::~ComunicationsManager()
{
    std::lock_guard<std::recursive_mutex> g(mStateListenersMutex);
    for (std::vector< CmdPetition * >::iterator it = stateListenersPetitions.begin(); it != stateListenersPetitions.end();)
    {
        delete *it;
        it = stateListenersPetitions.erase(it);
    }
}

MegaThread *CmdPetition::getPetitionThread() const
{
    return petitionThread;
}

void CmdPetition::setPetitionThread(MegaThread *value)
{
    petitionThread = value;
}
}//end namespace
