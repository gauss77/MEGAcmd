/**
 * @file src/client/megacmdclient.h
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

#pragma once

#include "../megacmdcommonutils.h"

namespace megacmd {
    int executeClient(int argc, char* argv[], OUTSTREAMTYPE &outstream);
} // end namespace
