/**
 * @file src/client/megacmd_client_main.cpp
 * @brief MEGAcmd: Interactive CLI and service application
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

#include "megacmdclient.h"

int main(int argc, char* argv[])
{
    return megacmd::executeClient(argc, argv, COUT);
}
