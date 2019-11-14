/*

Request Validator.

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


#include "request_validator.h"      // self

#include "request_parser.h"         // MalformedRequest

#include "generic_protocol/request_validator.h"     // generic_protocol::RequestValidator::validate
#include "basic_objects/validator.h"                // basic_objects::Validator::validate

namespace lieferbay_protocol {

bool RequestValidator::validate( const id_t & r, const std::string & key)
{
    if( r == 0 )
        throw RequestParser::MalformedRequest( key + " is 0" );

    return true;
}

bool RequestValidator::validate( const order_state_e & r )
{
    return true;
}

bool RequestValidator::validate( const ProductItem & r )
{
    THROW_IF_STRING_EMPTY( r.name, "NAME");
    THROW_IF_STRING_EMPTY( r.unit, "UNIT");
    THROW_IF_FLOAT_NEG_ZERO( r.price, "PRICE");
    THROW_IF_FLOAT_NEG_ZERO( r.weight, "WEIGHT");

    return true;
}

bool RequestValidator::validate( const ShoppingItem & r )
{
    validate( r.product_item_id, "PRODUCT_ITEM_ID" );
    THROW_IF_INT_NEG_ZERO( r.amount, "AMOUNT");

    return true;
}

bool RequestValidator::validate( const ShoppingList & r )
{
    THROW_IF_ARRAY_EMPTY( r.items, "SHOPPING_LIST");

    for( auto & e: r.items )
    {
        validate( e );
    }

    return true;
}

bool RequestValidator::validate( const GeoPosition & r )
{
    THROW_IF_INT_NEG_ZERO( r.plz, "PLZ");

    if( r.latitude != 0.0 )
        throw RequestParser::MalformedRequest( "non-zero latitude is not supported yet" );

    if( r.longitude != 0.0 )
        throw RequestParser::MalformedRequest( "non-zero longitude is not supported yet" );

    return true;
}

bool RequestValidator::validate( const Offer & r )
{
    validate( r.position );
    basic_objects::Validator::validate( r.delivery_time );
    THROW_IF_FLOAT_NEG_ZERO( r.max_weight, "MAX_WEIGHT");

    return true;
}

bool RequestValidator::validate( const Address & r )
{
    THROW_IF_INT_NEG_ZERO( r.plz,           "PLZ" );
    THROW_IF_STRING_EMPTY( r.country,       "COUNTRY" );
    THROW_IF_STRING_EMPTY( r.city,          "CITY" );
    THROW_IF_STRING_EMPTY( r.street,        "STREET" );
    THROW_IF_STRING_EMPTY( r.house_number,  "HOUSE_NUMBER" );

    return true;
}

bool RequestValidator::validate( const AddOfferRequest & r )
{
    validate( r.offer_with_state );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const CancelOfferRequest & r )
{
    validate( r.offer_id, "RIDE_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const GetOfferWithStateRequest & r )
{
    validate( r.offer_id, "RIDE_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const AddOrderRequest & r )
{
    validate( r.offer_id, "RIDE_ID" );
    validate( r.shopping_list );
    validate( r.delivery_address );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const CancelOrderRequest & r )
{
    validate( r.order_id, "ORDER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const AcceptOfferRequest & r )
{
    validate( r.order_id, "ORDER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const DeclineOfferRequest & r )
{
    validate( r.order_id, "ORDER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const NotifyDeliveredRequest & r )
{
    validate( r.order_id, "ORDER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const RateBuyerRequest & r )
{
    validate( r.order_id, "ORDER_ID" );
    THROW_IF_INT_NOT_IN_RANGE( r.stars, "STARS", 0, 5 );

    return generic_protocol::RequestValidator::validate( r );
}

namespace web {

bool RequestValidator::validate( const GetProductItemListRequest & r )
{
    return true;
}

bool RequestValidator::validate( const GetShoppingRequestInfoRequest & r )
{
    ::lieferbay_protocol::RequestValidator::validate( r.offer_id, "RIDE_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const GetShoppingListWithTotalsRequest & r )
{
    ::lieferbay_protocol::RequestValidator::validate( r.shopping_list_id, "SHOPPING_LIST_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const GetDashScreenUserRequest & r )
{
    ::lieferbay_protocol::RequestValidator::validate( r.user_id, "USER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

bool RequestValidator::validate( const GetDashScreenBuyerRequest & r )
{
    ::lieferbay_protocol::RequestValidator::validate( r.user_id, "USER_ID" );

    return generic_protocol::RequestValidator::validate( r );
}

} // namespace web


} // namespace lieferbay_protocol
