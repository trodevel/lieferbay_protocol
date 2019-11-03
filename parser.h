/*

Parser.

Copyright (C) 2019 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 12314 $ $Date:: 2019-10-31 #$ $Author: serge $

#ifndef LIB_LIEFERBAY_PROTOCOL_PARSER_H
#define LIB_LIEFERBAY_PROTOCOL_PARSER_H

#include "enums.h"                  // request_type_e
#include "protocol.h"     // AddRideRequest

namespace lieferbay_protocol {

class Parser
{
public:
    static request_type_e   to_request_type( const std::string & s );
};

namespace web {
class Parser
{
public:
    static request_type_e   to_request_type( const std::string & s );
};

} // namespace web

} // namespace lieferbay_protocol

#endif // LIB_LIEFERBAY_PROTOCOL_PARSER_H
