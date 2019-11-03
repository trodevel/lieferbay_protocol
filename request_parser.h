/*

Request Parser.

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

// $Revision: 12315 $ $Date:: 2019-10-31 #$ $Author: serge $

#include "generic_request/request.h"        // generic_request::Request
#include "basic_parser/malformed_request.h" // MalformedRequest
#include "enums.h"                          // request_type_e
#include "protocol.h"             // Request...

namespace lieferbay_protocol {

class RequestParser
{
public:
    typedef basic_parser::MalformedRequest      MalformedRequest;
    typedef generic_protocol::ForwardMessage    ForwardMessage;

public:

    static generic_protocol::ForwardMessage*    to_forward_message( const generic_request::Request & r );

    static void                         to_Id( id_t * res, const std::string & key, const generic_request::Request & r );
    static void                         to_order_state( order_state_e * res, const std::string & key, const generic_request::Request & r );
    static void                         to_order_resolution( order_resolution_e * res, const std::string & key, const generic_request::Request & r );
    static void                         to_ProductItem( ProductItem * res, const generic_request::Request & r );
    static void                         to_ShoppingItem( ShoppingItem * res, const generic_request::Request & r );
    static void                         to_ShoppingList( ShoppingList * res, const generic_request::Request & r );
    static void                         to_GeoPosition( GeoPosition * res, const generic_request::Request & r );
    static void                         to_Ride( RideSummary * res, const generic_request::Request & r );
    static void                         to_Address( Address * res, const generic_request::Request & r );
    //static void                         to_Order( Order * res, const generic_request::Request & r );

private:

    static request_type_e   detect_request_type( const generic_request::Request & r );

    static ForwardMessage *             to_AddRideRequest( const generic_request::Request & r );
    static ForwardMessage *             to_CancelRideRequest( const generic_request::Request & r );
    static ForwardMessage *             to_GetRideRequest( const generic_request::Request & r );
    static ForwardMessage *             to_AddOrderRequest( const generic_request::Request & r );
    static ForwardMessage *             to_CancelOrderRequest( const generic_request::Request & r );
    static ForwardMessage *             to_AcceptOrderRequest( const generic_request::Request & r );
    static ForwardMessage *             to_DeclineOrderRequest( const generic_request::Request & r );
    static ForwardMessage *             to_MarkDeliveredOrderRequest( const generic_request::Request & r );
    static ForwardMessage *             to_RateBuyerRequest( const generic_request::Request & r );
};

namespace web
{
class RequestParser
{
public:
    typedef basic_parser::MalformedRequest      MalformedRequest;
    typedef generic_protocol::ForwardMessage    ForwardMessage;

public:

    static generic_protocol::ForwardMessage*    to_forward_message( const generic_request::Request & r );

private:

    static request_type_e   detect_request_type( const generic_request::Request & r );

    static ForwardMessage *             to_GetProductItemListRequest( const generic_request::Request & r );
    static ForwardMessage *             to_GetShoppingRequestInfoRequest( const generic_request::Request & r );
    static ForwardMessage *             to_GetShoppingListWithTotalsRequest( const generic_request::Request & r );
    static ForwardMessage *             to_GetDashScreenUserRequest( const generic_request::Request & r );
    static ForwardMessage *             to_GetDashScreenBuyerRequest( const generic_request::Request & r );
};
}

} // namespace lieferbay_protocol

