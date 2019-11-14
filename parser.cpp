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

// $Revision: 12371 $ $Date:: 2019-11-14 #$ $Author: serge $

#include "parser.h"                 // self

#include <stdexcept>                // std::invalid_argument

namespace lieferbay_protocol {

#define TUPLE_VAL_STR(_x_)  _x_,#_x_
#define TUPLE_STR_VAL(_x_)  #_x_,_x_
#define TUPLE_VAL_STR_PREF(_x_,_p_)  _x_,_p_+std::string(#_x_)

template< typename _M, typename _U, typename _V >
void insert_inverse_pair( _M & map, _U first, _V second )
{
    map.insert( typename _M::value_type( second, first ) );
}

template< typename _U, typename _V >
std::pair<_V,_U> make_inverse_pair( _U first, _V second )
{
    return std::make_pair( second, first );
}

request_type_e Parser::to_request_type( const std::string & s )
{
    typedef std::string KeyType;
    typedef request_type_e Type;

    typedef std::map< KeyType, Type > Map;
    static const Map m =
    {
        make_inverse_pair( Type:: TUPLE_VAL_STR( AddOfferRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( CancelOfferRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( GetOfferWithStateRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( AddOrderRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( CancelOrderRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( AcceptOfferRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( DeclineOfferRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( NotifyDeliveredRequest ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR( RateBuyerRequest ) ),
    };

    auto it = m.find( s );

    if( it == m.end() )
        return request_type_e::UNDEF;

    return it->second;
}

namespace web {

request_type_e Parser::to_request_type( const std::string & s )
{
    typedef std::string KeyType;
    typedef request_type_e Type;

    typedef std::map< KeyType, Type > Map;
    static const Map m =
    {
        make_inverse_pair( Type:: TUPLE_VAL_STR_PREF( GetProductItemListRequest, "web/" ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR_PREF( GetShoppingRequestInfoRequest, "web/" ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR_PREF( GetShoppingListWithTotalsRequest, "web/" ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR_PREF( GetDashScreenUserRequest, "web/" ) ),
        make_inverse_pair( Type:: TUPLE_VAL_STR_PREF( GetDashScreenBuyerRequest, "web/" ) ),
    };

    auto it = m.find( s );

    if( it == m.end() )
        return request_type_e::UNDEF;

    return it->second;
}

} // namespace web

} // namespace lieferbay_protocol
