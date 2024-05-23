/**
 * @file src/comunicationsmanagerportnamedPipes.h
 * @brief MegaCMD: Communications manager using Network NamedPipes
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
#ifndef COMUNICATIONSMANAGERNAMEDPIPES_H
#define COMUNICATIONSMANAGERNAMEDPIPES_H

#include "comunicationsmanager.h"

#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>


#define MEGACMDINITIALPORTNUMBER 12300

namespace megacmd {
class CmdPetitionNamedPipes: public CmdPetition
{
public:
    HANDLE outNamedPipe;
    CmdPetitionNamedPipes(){
    }
    virtual ~CmdPetitionNamedPipes()
    {
        if (outNamedPipe != INVALID_HANDLE_VALUE)
        {
            CloseHandle(outNamedPipe);
        }
    }
    std::string getPetitionDetails() const override
    {
        std::ostringstream details;
        details << "namedPipe output: " << outNamedPipe;
        return details.str();
    }
};

OUTSTREAMTYPE &operator<<(OUTSTREAMTYPE &os, CmdPetitionNamedPipes &p);

class ComunicationsManagerNamedPipes : public ComunicationsManager
{
private:
    bool petitionready;

    // namedPipes and asociated variables
    HANDLE pipeGeneral;

    static bool ended;

    char buffer[1024];

    // to get next namedPipe id
    int count;
    std::mutex *mtx;
    std::mutex *informerMutex;

    /**
     * @brief create_new_namedPipe
     * The caller is responsible for deleting the newly created namedPipe
     * @return
     */
    HANDLE create_new_namedPipe(int *pipeId);

public:
    ComunicationsManagerNamedPipes();

    int initialize();

    bool receivedPetition();

    int waitForPetition();

    virtual void stopWaiting();

    int get_next_comm_id();

    void registerStateListener(CmdPetition *inf);

    /**
     * @brief returnAndClosePetition
     * I will clean struct and close the namedPipe within
     */
    void returnAndClosePetition(CmdPetition *inf, OUTSTRINGSTREAM *s, int);

    void sendPartialOutput(CmdPetition *inf, OUTSTRING *s);

    void sendPartialOutput(CmdPetition *inf, char *s, size_t size);


    int informStateListener(CmdPetition *inf, std::string &s);

    /**
     * @brief getPetition
     * @return pointer to new CmdPetitionPosix. Petition returned must be properly deleted (this can be calling returnAndClosePetition)
     */
    CmdPetition *getPetition();

    virtual int getConfirmation(CmdPetition *inf, std::string message);
    virtual std::string getUserResponse(CmdPetition *inf, std::string message);

    ~ComunicationsManagerNamedPipes();
    HANDLE doCreatePipe(std::wstring nameOfPipe);

};

}//end namespace
#endif // COMUNICATIONSMANAGERPOSIX_H
