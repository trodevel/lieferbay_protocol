<?php

/*

Response Parser. Web.

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

// $Revision: 12347 $ $Date:: 2019-11-12 #$ $Author: serge $

namespace lieferbay_protocol\web;

require_once __DIR__.'/../lieferbay_protocol/response_parser.php';

function parse_ProductItemWithId( & $csv_arr, & $offset )
{
    // 121212;Milch;Packung;1.09;1

    $res = new ProductItemWithId;

    $res->product_item_id   = \basic_parser\parse_int( $csv_arr, $offset );
    $res->product_item      = \lieferbay_protocol\parse_ProductItem( $csv_arr, $offset );

    return $res;
}

function parse_ShoppingItemWithProduct( & $csv_arr, & $offset )
{
    // 121212;2;Milch;Packung;1.09;1

    $res = new ShoppingItemWithProduct;

    $res->shopping_item     = \lieferbay_protocol\parse_ShoppingItem( $csv_arr, $offset );
    $res->product_item      = \lieferbay_protocol\parse_ProductItem( $csv_arr, $offset );

    return $res;
}

function parse_ShoppingListWithProduct( & $csv_arr, & $offset )
{
    // 1;121212;2;Milch;Packung;1.09;1

    $res = new ShoppingListWithProduct;

    $size    = \basic_parser\parse_int( $csv_arr, $offset );

    //echo "size = $size\n";

    $res->items = array();

    for( $i = 0; $i < $size; $i++ )
    {
        array_push( $res->items, parse_ShoppingItemWithProduct( $csv_arr, $offset ) );
    }

    return $res;
}

function parse_ShoppingListWithTotals( & $csv_arr, & $offset )
{
    // 1;121212;2;Milch;Packung;1.09;2;2.18;2;

    $res = new ShoppingListWithTotals;

    $res->shopping_list = parse_ShoppingListWithProduct( $csv_arr, $offset );
    $res->price         = \basic_parser\parse_float( $csv_arr, $offset );
    $res->weight        = \basic_parser\parse_float( $csv_arr, $offset );

    return $res;
}

function parse_OfferWithBuyer( & $csv_arr, & $offset )
{
    // 232323;50668;0;0;20190522173000;3.5;Johann=20Meyer;

    $res = new OfferWithBuyer;

    $res->ride_id       = \basic_parser\parse_int( $csv_arr, $offset );
    $res->ride          = \lieferbay_protocol\parse_Offer( $csv_arr, $offset );
    $res->buyer_name  = \basic_parser\parse_enc_string( $csv_arr, $offset );

    return $res;
}

function parse_RideWithId( & $csv_arr, & $offset )
{
    // 232323;50668;0;0;20190522173000;3.5;1;

    $res = new RideWithId;

    $res->ride_id       = \basic_parser\parse_int( $csv_arr, $offset );
    $res->ride          = \lieferbay_protocol\parse_Ride( $csv_arr, $offset );

    return $res;
}

function parse_ShoppingRequestInfo( & $csv_arr, & $offset )
{
    // 232323;2.18;.3;1.25;20190522173000;...

    $res = new ShoppingRequestInfo;

    $res->order_id      = \basic_parser\parse_int( $csv_arr, $offset );
    $res->sum           = \basic_parser\parse_float( $csv_arr, $offset );
    $res->earning       = \basic_parser\parse_float( $csv_arr, $offset );
    $res->weight        = \basic_parser\parse_float( $csv_arr, $offset );
    $res->address       = \lieferbay_protocol\parse_Address( $csv_arr, $offset );

    return $res;
}

function parse_AcceptedOrderUser( & $csv_arr, & $offset )
{
    // 232323;20190327202000;1;565656;50668;Germany;Cologne;Breslau Platz;1;;141414;4;17.25;Johann=20Meyer;

    $res = new AcceptedOrderUser;

    $res->order_id      = \basic_parser\parse_int( $csv_arr, $offset );
    $res->delivery_time = \basic_objects\parse_LocalTime( $csv_arr, $offset );
    $res->order         = \lieferbay_protocol\parse_Order( $csv_arr, $offset );
    $res->sum           = \basic_parser\parse_float( $csv_arr, $offset );
    $res->buyer_name  = \basic_parser\parse_enc_string( $csv_arr, $offset );

    return $res;
}

function parse_AcceptedOrderBuyer( & $csv_arr, & $offset )
{
    // 232323;20190327202000;1;565656;50668;Germany;Cologne;Breslau Platz;1;;141414;4;17.25;3.27;1.5;

    $res = new AcceptedOrderBuyer;

    $res->order_id      = \basic_parser\parse_int( $csv_arr, $offset );
    $res->delivery_time = \basic_objects\parse_LocalTime( $csv_arr, $offset );
    $res->order         = \lieferbay_protocol\parse_Order( $csv_arr, $offset );
    $res->sum           = \basic_parser\parse_float( $csv_arr, $offset );
    $res->earning       = \basic_parser\parse_float( $csv_arr, $offset );
    $res->weight        = \basic_parser\parse_float( $csv_arr, $offset );

    return $res;
}

function parse_DashScreenUser( & $csv_arr, & $offset )
{
    // 20190327202000;...

    $res = new DashScreenUser;

    $res->current_time  = \basic_objects\parse_LocalTime( $csv_arr, $offset );

    {
        $size    = \basic_parser\parse_int( $csv_arr, $offset );

        //echo "size = $size\n";

        $res->rides = array();

        for( $i = 0; $i < $size; $i++ )
        {
            array_push( $res->rides, parse_OfferWithBuyer( $csv_arr, $offset ) );
        }
    }

    {
        $size    = \basic_parser\parse_int( $csv_arr, $offset );

        //echo "size = $size\n";

        $res->orders = array();

        for( $i = 0; $i < $size; $i++ )
        {
            array_push( $res->orders, parse_AcceptedOrderUser( $csv_arr, $offset ) );
        }
    }

    return $res;
}

function parse_DashScreenBuyer( & $csv_arr, & $offset )
{
    // 20190327202000;...

    $res = new DashScreenBuyer;

    $res->current_time  = \basic_objects\parse_LocalTime( $csv_arr, $offset );

    {
        $size    = \basic_parser\parse_int( $csv_arr, $offset );

        //echo "size = $size\n";

        $res->rides = array();

        for( $i = 0; $i < $size; $i++ )
        {
            array_push( $res->rides, parse_RideWithId( $csv_arr, $offset ) );
        }
    }

    {
        $size    = \basic_parser\parse_int( $csv_arr, $offset );

        //echo "size = $size\n";

        $res->orders = array();

        for( $i = 0; $i < $size; $i++ )
        {
            array_push( $res->orders, parse_AcceptedOrderBuyer( $csv_arr, $offset ) );
        }
    }

    return $res;
}

function parse_GetProductItemListResponse( & $csv_arr )
{
    // web/GetProductItemListResponse;5;...

    $res = new GetProductItemListResponse;

    $offset = 1;

    $size    = \basic_parser\parse_int( $csv_arr, $offset );

    //echo "size = $size\n";

    $res->product_items = array();

    for( $i = 0; $i < $size; $i++ )
    {
        array_push( $res->product_items, parse_ProductItemWithId( $csv_arr, $offset ) );
    }

    return $res;
}

function parse_GetShoppingRequestInfoResponse( & $csv_arr )
{
    // web/GetShoppingRequestInfoResponse;5;...

    $res = new GetShoppingRequestInfoResponse;

    $offset = 1;

    $size    = \basic_parser\parse_int( $csv_arr, $offset );

    //echo "size = $size\n";

    $res->requests = array();

    for( $i = 0; $i < $size; $i++ )
    {
        array_push( $res->requests, parse_ShoppingRequestInfo( $csv_arr, $offset ) );
    }

    return $res;
}

function parse_GetShoppingListWithTotalsResponse( & $csv_arr )
{
    // web/GetShoppingListWithTotalsResponse;...

    $res = new GetShoppingListWithTotalsResponse;

    $offset = 1;

    $res->shopping_list = parse_ShoppingListWithTotals( $csv_arr, $offset );

    return $res;
}

function parse_GetDashScreenUserResponse( & $csv_arr )
{
    // web/GetDashScreenUserResponse;...

    $res = new GetDashScreenUserResponse;

    $offset = 1;

    $res->dash_screen   = parse_DashScreenUser( $csv_arr, $offset );

    return $res;
}

function parse_GetDashScreenBuyerResponse( & $csv_arr )
{
    // web/GetDashScreenBuyerResponse;...

    $res = new GetDashScreenBuyerResponse;

    $offset = 1;

    $res->dash_screen   = parse_DashScreenBuyer( $csv_arr, $offset );

    return $res;
}

class ResponseParser extends \lieferbay_protocol\ResponseParser
{

protected static function parse_csv_array( $csv_arr )
{
    if( sizeof( $csv_arr ) < 1 )
        return self::create_parse_error();

    $type = $csv_arr[0][0];

    $func_map = array(
        'web/GetProductItemListResponse'    => 'parse_GetProductItemListResponse',
        'web/GetShoppingRequestInfoResponse'      => 'parse_GetShoppingRequestInfoResponse',
        'web/GetShoppingListWithTotalsResponse'     => 'parse_GetShoppingListWithTotalsResponse',
        'web/GetDashScreenUserResponse'     => 'parse_GetDashScreenUserResponse',
        'web/GetDashScreenBuyerResponse'  => 'parse_GetDashScreenBuyerResponse',
        );

    if( array_key_exists( $type, $func_map ) )
    {
        $func = '\\lieferbay_protocol\\web\\' . $func_map[ $type ];
        return $func( $csv_arr[0] );
    }

    return \lieferbay_protocol\ResponseParser::parse_csv_array( $csv_arr );
}

}

?>
