/*

CSV response encoder.

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

// $Revision: 12356 $ $Date:: 2019-11-13 #$ $Author: serge $

#include "csv_response_encoder.h"       // self

#include <typeinfo>                     // typeid

#include "utils/nonascii_hex_codec.h"   // nonascii_hex_codec
#include "utils/csv_helper.h"           // CsvHelper
#include "utils/utils_assert.h"         // ASSERT

#include "generic_protocol/csv_helper.h"    // generic_protocol::CsvHelper::to_csv()
#include "basic_objects/csv_helper.h"       // basic_objects::CsvHelper::write()

#include "str_helper.h"

#define MODULENAME      "lieferbay_protocol::CsvResponseEncoder"

namespace lieferbay_protocol {

std::string CsvResponseEncoder::to_csv( const generic_protocol::BackwardMessage & r )
{
    if( typeid( r ) == typeid( CancelOfferWithStateResponse ) )
    {
        return to_csv( static_cast<const CancelOfferWithStateResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( AddOrderResponse ) )
    {
        return to_csv( static_cast<const AddOrderResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( CancelOrderResponse ) )
    {
        return to_csv( static_cast<const CancelOrderResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( AcceptOrderResponse ) )
    {
        return to_csv( static_cast<const AcceptOrderResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( DeclineOrderResponse ) )
    {
        return to_csv( static_cast<const DeclineOrderResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( MarkDeliveredOrderResponse ) )
    {
        return to_csv( static_cast<const MarkDeliveredOrderResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( RateBuyerResponse ) )
    {
        return to_csv( static_cast<const RateBuyerResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( AddOfferWithStateResponse ) )
    {
        return to_csv( static_cast<const AddOfferWithStateResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( GetOfferWithStateResponse ) )
    {
        return to_csv( static_cast<const GetOfferWithStateResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( web::GetShoppingRequestInfoResponse ) )
    {
        return to_csv( static_cast<const web::GetShoppingRequestInfoResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( web::GetShoppingListWithTotalsResponse ) )
    {
        return to_csv( static_cast<const web::GetShoppingListWithTotalsResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( web::GetProductItemListResponse ) )
    {
        return to_csv( static_cast<const web::GetProductItemListResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( web::GetDashScreenUserResponse ) )
    {
        return to_csv( static_cast<const web::GetDashScreenUserResponse&>( r ) );
    }
    else if( typeid( r ) == typeid( web::GetDashScreenBuyerResponse ) )
    {
        return to_csv( static_cast<const web::GetDashScreenBuyerResponse&>( r ) );
    }
    else
    {
        return generic_protocol::CsvHelper::to_csv( r );
    }
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const Order & r )
{
    utils::CsvHelper::write( os, static_cast<unsigned>( r.is_open ) );

    utils::CsvHelper::write( os, r.ride_id );

    write( os, r.delivery_address );

    utils::CsvHelper::write(
            os,
            r.shopping_list_id );

    write( os, r.state );
    write( os, r.resolution );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, order_state_e r )
{
    utils::CsvHelper::write( os, static_cast<unsigned>( r ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, order_resolution_e r )
{
    utils::CsvHelper::write( os, static_cast<unsigned>( r ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::ProductItemWithId & r )
{
    utils::CsvHelper::write(
            os,
            r.product_item_id );

    write( os, r.product_item );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const ProductItem & r )
{
    return utils::CsvHelper::write(
            os,
            utils::nonascii_hex_codec::encode( r.name ),
            utils::nonascii_hex_codec::encode( r.unit ),
            r.price,
            r.weight );
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::ShoppingListWithProduct & r )
{
    utils::CsvHelper::write_user_array<false>(
                os,
                r.items.begin(),
                r.items.end(),
                [](std::ostream & os, const web::ShoppingItemWithProduct & r ) { CsvResponseEncoder::write( os, r ); } );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::AcceptedOrderUser & r )
{
    utils::CsvHelper::write( os, r.order_id );

    basic_objects::CsvHelper::write( os, r.delivery_time );

    write( os, r.order );

    utils::CsvHelper::write( os,
            r.sum,
            utils::nonascii_hex_codec::encode( r.buyer_name ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::AcceptedOrderBuyer & r )
{
    utils::CsvHelper::write( os, r.order_id );

    basic_objects::CsvHelper::write( os, r.delivery_time );

    write( os, r.order );

    utils::CsvHelper::write(
            os,
            r.sum,
            r.earning,
            r.weight );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::DashScreenUser & r )
{
    basic_objects::CsvHelper::write( os, r.current_time );

    utils::CsvHelper::write_user_array<false>(
                os,
                r.rides.begin(),
                r.rides.end(),
                [](std::ostream & os, const web::OfferWithBuyer & r ) { CsvResponseEncoder::write( os, r ); } );

    utils::CsvHelper::write_user_array<false>(
                os,
                r.orders.begin(),
                r.orders.end(),
                [](std::ostream & os, const web::AcceptedOrderUser & r ) { CsvResponseEncoder::write( os, r ); } );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::DashScreenBuyer & r )
{
    basic_objects::CsvHelper::write( os, r.current_time );

    utils::CsvHelper::write_user_array<false>(
                os,
                r.rides.begin(),
                r.rides.end(),
                [](std::ostream & os, const web::OfferWithStateWithId & r ) { CsvResponseEncoder::write( os, r ); } );

    utils::CsvHelper::write_user_array<false>(
                os,
                r.orders.begin(),
                r.orders.end(),
                [](std::ostream & os, const web::AcceptedOrderBuyer & r ) { CsvResponseEncoder::write( os, r ); } );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::ShoppingRequestInfo & r )
{
    utils::CsvHelper::write(
            os,
            r.order_id,
            r.sum,
            r.earning,
            r.weight );

    write( os, r.address );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const ShoppingList & r )
{
    utils::CsvHelper::write_user_array<false>(
                os,
                r.items.begin(),
                r.items.end(),
                [](std::ostream & os, const ShoppingItem & r ) { CsvResponseEncoder::write( os, r ); } );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const GeoPosition & r )
{
    utils::CsvHelper::write( os, r.plz, r.latitude, r.longitude );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const Offer & r )
{
    write( os, r.position );
    basic_objects::CsvHelper::write( os, r.delivery_time );
    utils::CsvHelper::write( os, r.max_weight );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, offer_state_e r )
{
    utils::CsvHelper::write( os, static_cast<unsigned>( r ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const OfferWithState & r )
{
    utils::CsvHelper::write( os, static_cast<unsigned>( r.is_open ) );

    write( os, r.offer );

    utils::CsvHelper::write_array( os, r.pending_order_ids.begin(), r.pending_order_ids.end() );

    utils::CsvHelper::write( os, r.order_id );

    write( os, r.resolution );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const ShoppingItem & r )
{
    utils::CsvHelper::write(
            os,
            r.product_item_id,
            r.amount );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const Address & r )
{
    utils::CsvHelper::write(
            os,
            r.plz,
            utils::nonascii_hex_codec::encode( r.country ),
            utils::nonascii_hex_codec::encode( r.city ),
            utils::nonascii_hex_codec::encode( r.street ),
            utils::nonascii_hex_codec::encode( r.house_number ),
            utils::nonascii_hex_codec::encode( r.extra_address_line ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::OfferWithBuyer & r )
{
    utils::CsvHelper::write( os, r.ride_id );

    write( os, r.ride );

    utils::CsvHelper::write( os, utils::nonascii_hex_codec::encode( r.buyer_name ) );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::ShoppingItemWithProduct & e )
{
    write( os, e.shopping_item );
    write( os, e.product_item );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::OfferWithStateWithId & r )
{
    utils::CsvHelper::write( os, r.ride_id );

    write( os, r.ride );

    return os;
}

std::ostream & CsvResponseEncoder::write( std::ostream & os, const web::ShoppingListWithTotals & r )
{
    write( os, r.shopping_list );

    utils::CsvHelper::write(
            os,
            r.price,
            r.weight );

    return os;
}

std::string CsvResponseEncoder::to_csv( const AddOfferWithStateResponse & r )
{
    return utils::CsvHelper::to_csv( "AddOfferWithStateResponse", r.ride_id );
}

std::string CsvResponseEncoder::to_csv( const CancelOfferWithStateResponse & r )
{
    return utils::CsvHelper::to_csv( "CancelOfferWithStateResponse" );
}

std::string CsvResponseEncoder::to_csv( const GetOfferWithStateResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write( os, "GetOfferWithStateResponse" ) ;

    write( os, r.ride );

    return os.str();
}

std::string CsvResponseEncoder::to_csv( const AddOrderResponse & r )
{
    return utils::CsvHelper::to_csv( "AddOrderResponse", r.order_id );
}

std::string CsvResponseEncoder::to_csv( const CancelOrderResponse & r )
{
    return utils::CsvHelper::to_csv( "CancelOrderResponse" );
}

std::string CsvResponseEncoder::to_csv( const AcceptOrderResponse & r )
{
    return utils::CsvHelper::to_csv( "AcceptOrderResponse" );
}

std::string CsvResponseEncoder::to_csv( const DeclineOrderResponse & r )
{
    return utils::CsvHelper::to_csv( "DeclineOrderResponse" );
}

std::string CsvResponseEncoder::to_csv( const MarkDeliveredOrderResponse & r )
{
    return utils::CsvHelper::to_csv( "MarkDeliveredOrderResponse" );
}

std::string CsvResponseEncoder::to_csv( const RateBuyerResponse & r )
{
    return utils::CsvHelper::to_csv( "RateBuyerResponse" );
}

std::string CsvResponseEncoder::to_csv( const web::GetShoppingRequestInfoResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write(
            os,
            "web/GetShoppingRequestInfoResponse" ) ;

    utils::CsvHelper::write_user_array(
            os,
            r.requests.begin(),
            r.requests.end(),
            [](std::ostream & os, const web::ShoppingRequestInfo & r) { CsvResponseEncoder::write( os, r ); } );

    return os.str();
}

std::string CsvResponseEncoder::to_csv( const web::GetShoppingListWithTotalsResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write(
            os,
            "web/GetShoppingListWithTotalsResponse" ) ;

    write( os, r.shopping_list );

    return os.str();
}

std::string CsvResponseEncoder::to_csv( const web::GetProductItemListResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write(
            os,
            "web/GetProductItemListResponse" ) ;

    utils::CsvHelper::write_user_array(
            os,
            r.product_items.begin(),
            r.product_items.end(),
            [](std::ostream & os, const web::ProductItemWithId & r) { CsvResponseEncoder::write( os, r ); } );

    return os.str();
}

std::string CsvResponseEncoder::to_csv( const web::GetDashScreenUserResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write(
            os,
            "web/GetDashScreenUserResponse" ) ;

    write( os, r.dash_screen );

    return os.str();
}

std::string CsvResponseEncoder::to_csv( const web::GetDashScreenBuyerResponse & r )
{
    std::ostringstream os;

    utils::CsvHelper::write(
            os,
            "web/GetDashScreenBuyerResponse" ) ;

    write( os, r.dash_screen );

    return os.str();
}

} // namespace lieferbay_protocol
