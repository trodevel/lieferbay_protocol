<?php

/*

Response Parser.

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

namespace lieferbay_protocol;

require_once __DIR__.'/../php_snippets/convert_csv_to_array.php';   // convert_csv_to_array()
require_once __DIR__.'/../php_snippets/nonascii_hex_codec.php';     // \utils\nonascii_hex_codec\decode()
require_once __DIR__.'/../generic_protocol/response_parser.php';    // generic_protocol\create_parse_error()
require_once __DIR__.'/../basic_objects/parser.php';                // \basic_objects\parse_TimePoint24
require_once __DIR__.'/../basic_parser/parser.php';                 // \basic_parser\parse_VectorInt
require_once 'protocol.php';

function parse_ProductItem( & $csv_arr, & $offset )
{
    // Milch;Packung;1.09;1

    $res = new ProductItem;

    $res->name      = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $res->unit      = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $res->price     = \basic_parser\parse_float( $csv_arr, $offset );
    $res->weight    = \basic_parser\parse_float( $csv_arr, $offset );

    return $res;
}

function parse_ShoppingItem( & $csv_arr, & $offset )
{
    // 121212;3;

    $product_item_id   = \basic_parser\parse_int( $csv_arr, $offset );
    $amount            = \basic_parser\parse_int( $csv_arr, $offset );

    $res = new ShoppingItem( $product_item_id, $amount );

    return $res;
}

function parse_GeoPosition( & $csv_arr, & $offset )
{
    // 50667;0;0;

    $plz        = \basic_parser\parse_int( $csv_arr, $offset );
    $latitude   = \basic_parser\parse_float( $csv_arr, $offset );
    $longitude  = \basic_parser\parse_float( $csv_arr, $offset );

    $res = new GeoPosition( $plz, $latitude, $longitude );

    return $res;
}

function parse_Offer( & $csv_arr, & $offset )
{
    // 50668;0;0;20190522173000;3.5

    $position       = parse_GeoPosition( $csv_arr, $offset );
    $delivery_time  = \basic_objects\parse_LocalTime( $csv_arr, $offset );
    $max_weigth     = \basic_parser\parse_float( $csv_arr, $offset );

    $res = new Offer( $position, $delivery_time, $max_weigth );

    return $res;
}

function parse_Ride( & $csv_arr, & $offset )
{
    // 1;50668;0;0;20190522180000;2.5;3;565656;737373;878787;121212;0;

    $res = new Ride;

    $res->is_open           = \basic_parser\parse_int( $csv_arr, $offset );
    $res->summary           = parse_Offer( $csv_arr, $offset );
    $res->pending_order_ids = \basic_parser\parse_VectorInt( $csv_arr, $offset );
    $res->accepted_order_id = \basic_parser\parse_int( $csv_arr, $offset );
    $res->resolution        = \basic_parser\parse_int( $csv_arr, $offset );

    return $res;
}

function parse_Address( & $csv_arr, & $offset )
{
    // 50668;Germany;Cologne;Breslau Platz;1;;

    $plz            = \basic_parser\parse_int( $csv_arr, $offset );
    $country        = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $city           = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $street         = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $house_number   = \basic_parser\parse_enc_string( $csv_arr, $offset );
    $extra_address_line = \basic_parser\parse_enc_string( $csv_arr, $offset );

    $res = new Address( $plz, $country, $city, $street, $house_number, $extra_address_line );

    return $res;
}

function parse_Order( & $csv_arr, & $offset )
{
    // 1;565656;50668;Germany;Cologne;Breslau Platz;1;;141414;2;0;

    $res = new Order;

    $res->is_open           = \basic_parser\parse_int( $csv_arr, $offset );
    $res->ride_id           = \basic_parser\parse_int( $csv_arr, $offset );
    $res->delivery_address  = parse_Address( $csv_arr, $offset );
    $res->shopping_list_id  = \basic_parser\parse_int( $csv_arr, $offset );
    $res->state             = \basic_parser\parse_int( $csv_arr, $offset );
    $res->resolution        = \basic_parser\parse_int( $csv_arr, $offset );

    return $res;
}

function parse_AddRideResponse( & $csv_arr )
{
    // AddRideResponse;123;

    $offset = 1;

    $res = new AddRideResponse;

    $res->ride_id       = \basic_parser\parse_int( $csv_arr, $offset );

    return $res;
}

function parse_CancelRideResponse( & $csv_arr )
{
    // CancelRideResponse;

    $res = new CancelRideResponse;

    return $res;
}

function parse_GetRideResponse( & $csv_arr )
{
    // GetRideResponse;50668;0;0;20190522180000;2;

    $offset = 1;

    $res = new GetRideResponse;

    $res->ride  = parse_Ride( $csv_arr, $offset );

    return $res;
}

function parse_AddOrderResponse( & $csv_arr )
{
    // AddOrderResponse;123;

    $offset = 1;

    $res = new AddOrderResponse;

    $res->order_id      = \basic_parser\parse_int( $csv_arr, $offset );

    return $res;
}

function parse_CancelOrderResponse( & $csv_arr )
{
    // CancelOrderResponse;

    $res = new CancelOrderResponse;

    return $res;
}

function parse_AcceptOrderResponse( & $csv_arr )
{
    // AcceptOrderResponse;

    $res = new AcceptOrderResponse;

    return $res;
}

function parse_DeclineOrderResponse( & $csv_arr )
{
    // DeclineOrderResponse;

    $res = new DeclineOrderResponse;

    return $res;
}

function parse_MarkDeliveredOrderResponse( & $csv_arr )
{
    // MarkDeliveredOrderResponse;

    $res = new MarkDeliveredOrderResponse;

    return $res;
}

function parse_RateBuyerResponse( & $csv_arr )
{
    // RateBuyerResponse;

    $res = new RateBuyerResponse;

    return $res;
}

class ResponseParser extends \generic_protocol\ResponseParser
{

protected static function parse_csv_array( $csv_arr )
{
    if( sizeof( $csv_arr ) < 1 )
        return self::create_parse_error();

    $type = $csv_arr[0][0];

    $func_map = array(
        'AddRideResponse'               => 'parse_AddRideResponse',
        'CancelRideResponse'            => 'parse_CancelRideResponse',
        'GetRideResponse'               => 'parse_GetRideResponse',
        'AddOrderResponse'              => 'parse_AddOrderResponse',
        'CancelOrderResponse'           => 'parse_CancelOrderResponse',
        'AcceptOrderResponse'           => 'parse_AcceptOrderResponse',
        'DeclineOrderResponse'          => 'parse_DeclineOrderResponse',
        'MarkDeliveredOrderResponse'    => 'parse_MarkDeliveredOrderResponse',
        'RateBuyerResponse'           => 'parse_RateBuyerResponse',
        );

    if( array_key_exists( $type, $func_map ) )
    {
        $func = '\\lieferbay_protocol\\' . $func_map[ $type ];
        return $func( $csv_arr[0] );
    }

    return \generic_protocol\ResponseParser::parse_csv_array( $csv_arr );
}

}

?>
