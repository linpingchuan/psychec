/******************************************************************************
 Copyright (c) 2017 Leandro T. C. Melo (ltcmelo@gmail.com)

 This library is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation; either version 2.1 of the License, or (at your option)
 any later version.

 This library is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 for more details.

 You should have received a copy of the GNU Lesser General Public License along
 with this library; if not, write to the Free Software Foundation, Inc., 51
 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *****************************************************************************/

#ifndef PSYCHE_STD_LIB_INDEX_H__
#define PSYCHE_STD_LIB_INDEX_H__

#include "Config.h"
#include "CPlusPlusForwardDeclarations.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace psyche {

class PSYCHEC_API StdLibIndex final
{
public:
    // TODO: Sync with language options
    enum class StdLibVersion {
        C89,
        C99,
        C11
    };

    StdLibIndex(StdLibVersion std);

    std::vector<std::string> inspect(const CPlusPlus::Control&) const;

private:
    enum class SymbolKind : char
    {
        Type,
        Value
    };
    using StdSymbol = std::pair<const char*, SymbolKind>;
    using Index = std::unordered_map<const char*, std::vector<StdSymbol>>;

    StdLibVersion std_;
    static const Index c89idx_;
    static const Index c99idx_;
    static const Index c11idx_;
};

} // namespace psyche

#endif