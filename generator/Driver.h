/******************************************************************************
 * Copyright (c) 2016 Leandro T. C. Melo (ltcmelo@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 *****************************************************************************/

#ifndef PSYCHE_DRIVER_H__
#define PSYCHE_DRIVER_H__

#include "Config.h"
#include "CPlusPlusForwardDeclarations.h"
#include <cstddef>
#include <memory>
#include <string>
#include <tuple>

namespace cxxopts {
class Options;
}

namespace psyche {

class Factory;

/*!
 * \brief The ExecFlags struct
 */
struct PSYCHEC_API ExecutionFlags
{
    ExecutionFlags() : all_(0) {}

    struct Detail
    {
        uint32_t displayCstr : 1;  //!< Display generated constraints.
        uint32_t displayStats : 1;  //!< Ambiguity- and constraints-related stats.
        uint32_t dumpAst : 1;  //!< Both original and fixed one.
        uint32_t testOnly : 1;  //!< Test-only run.
        uint32_t disambOnly : 1;  //!< Disambiguatio-only run.
        uint32_t nonHeuristic : 1;  //!< Disable heuristics on unresolved ambiguities.

        //! Whether to write the generate constraints back.
        uint32_t writeConstraints_   : 1;
        //! Whether to handle GNU's error function as a printf variety.
        uint32_t handleGNUerrorFunc_ : 1;
    };
    union
    {
        Detail flag_;
        uint32_t all_;
    };
};


//! Return codes.
const size_t kOK = 0;
const size_t kParsingFailed = 1;
const size_t kSyntaxErrors = 2;
const size_t kInvalidAST = 3;
const size_t kProgramAmbiguous = 4;

/*!
 * \brief process
 * \param unitName
 * \param source
 * \param control
 * \param flags
 * \param factory
 * \return
 */
std::tuple<size_t,
           std::unique_ptr<CPlusPlus::TranslationUnit>,
           std::string>
process(const std::string& unitName,
        const std::string& source,
        CPlusPlus::Control& control,
        ExecutionFlags& flags,
        Factory* factory);

} // namespace psyche

#endif