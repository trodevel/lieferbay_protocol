<?php

/*

Lieferbay Protocol messages.

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

// $Revision: 12354 $ $Date:: 2019-11-13 #$ $Author: serge $

namespace lieferbay_protocol\web;

require_once __DIR__.'/../lieferbay_protocol/html_helper.php';

function to_html_not_impl( & $obj )
{
    return get_html_table_header_elems( array( 'not implemented yet' ) );
}

/**************************************************
 * OBJECTS
 **************************************************/

function get_header_ProductItemWithId()
{
    return get_html_table_header_elems( array( 'ID' ) ) . \lieferbay_protocol\get_header_ProductItem();
}

function to_html_ProductItemWithId_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
        $obj->product_item_id ) ) . \lieferbay_protocol\to_html_ProductItem_tabledata( $obj->product_item );
}

function to_html_GetProductItemListResponse( & $obj )
{
//     var_dump( $obj );

    $num   = sizeof( $obj->product_items );

    $res = '<h3>Product Item List (' . $num . ')</h3>';

    $body = '';
    for( $i = 0; $i < $num; $i++ )
    {
        $body = $body . get_html_table_tr( to_html_ProductItemWithId_tabledata( $obj->product_items[$i] ) );
    }

    $res = $res. get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
        get_html_table_tr( get_header_ProductItemWithId() ) . $body );

    return $res;
}

function get_header_ShoppingRequestInfo()
{
    return get_html_table_header_elems( array( 'ORDER ID', 'SUM', 'EARNING', 'WEIGHT' ) ) . \lieferbay_protocol\get_header_Address();
}

function to_html_ShoppingRequestInfo_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
            $obj->order_id,
            $obj->sum,
            $obj->earning,
            $obj->weight ) ) .
            \lieferbay_protocol\to_html_Address_tabledata( $obj->address );
}

function to_html_GetShoppingRequestInfoResponse( & $obj )
{
    $num   = sizeof( $obj->requests );

    $res = '<h3>Shopping Request Info (' . $num . ')</h3>';

    $body = '';
    for( $i = 0; $i < $num; $i++ )
    {
        $body = $body . get_html_table_tr( to_html_ShoppingRequestInfo_tabledata( $obj->requests[$i] ) );
    }

    $res = $res. get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
        get_html_table_tr( get_header_ShoppingRequestInfo() ) . $body );

    return $res;
}

function get_header_ShoppingItemWithProduct()
{
    return \lieferbay_protocol\get_header_ShoppingItem() . \lieferbay_protocol\get_header_ProductItem();
}

function to_html_ShoppingItemWithProduct_tabledata( & $obj )
{
    return \lieferbay_protocol\to_html_ShoppingItem_tabledata( $obj->shopping_item ) .
        \lieferbay_protocol\to_html_ProductItem_tabledata( $obj->product_item );
}

function to_html_ShoppingListWithProduct( & $obj )
{
    //     var_dump( $obj );

    $num   = sizeof( $obj->items );

    $res = '<h3>Shopping List (' . $num . ')</h3>';

    $body = '';
    for( $i = 0; $i < $num; $i++ )
    {
        $body = $body . get_html_table_tr( to_html_ShoppingItemWithProduct_tabledata( $obj->items[$i] ) );
    }

    $res = $res. get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
        get_html_table_tr( get_header_ShoppingItemWithProduct() ) . $body );

    return $res;
}

function to_html_ShoppingListWithTotals( & $obj )
{
    $res = to_html_ShoppingListWithProduct( $obj->shopping_list );

    $res = $res . '<h3>Price: ' . $obj->price . '</h3>';
    $res = $res . '<h3>Weight: ' . $obj->weight . '</h3>';

    return $res;
}

function to_html_GetShoppingListWithTotalsResponse( & $obj )
{
    $res = '<h3>Shopping List with Totals:</h3>';

    $res = $res . to_html_ShoppingListWithTotals( $obj->shopping_list );

    return $res;
}

function get_header_OfferWithBuyer()
{
    return get_html_table_header_elems( array( 'RIDE ID' ) ) .
        \lieferbay_protocol\get_header_Offer() .
        get_html_table_header_elems( array( 'SHOPPER NAME' ) );
}

function to_html_OfferWithBuyer_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
        $obj->ride_id ) ) .
        \lieferbay_protocol\to_html_Offer_tabledata( $obj->ride ) .
        get_html_table_data_elems( array(
            $obj->buyer_name ) );
}

function get_header_OfferWithStateWithId()
{
    return get_html_table_header_elems( array( 'RIDE ID' ) ) .
    \lieferbay_protocol\get_header_OfferWithState();
}

function to_html_OfferWithStateWithId_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
        $obj->ride_id ) ) .
        \lieferbay_protocol\to_html_OfferWithState_tabledata( $obj->ride );
}

function get_header_AcceptedOrderUser()
{
    return get_html_table_header_elems( array( 'ORDER ID', 'DELIVERY TIME' ) ) .
    \lieferbay_protocol\get_header_Order() .
    get_html_table_header_elems( array( 'SUM', 'SHOPPER NAME' ) );
}

function to_html_AcceptedOrderUser_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
        $obj->order_id,
        \basic_objects\to_string_LocalTime( $obj->delivery_time ) ) ) .
        \lieferbay_protocol\to_html_Order_tabledata( $obj->order ) .
        get_html_table_data_elems( array(
            $obj->sum,
            $obj->buyer_name ) );
}

function get_header_AcceptedOrderBuyer()
{
    return get_html_table_header_elems( array( 'ORDER ID', 'DELIVERY TIME' ) ) .
        \lieferbay_protocol\get_header_Order() .
        get_html_table_header_elems( array( 'SUM', 'EARNING', 'WEIGHT' ) );
}

function to_html_AcceptedOrderBuyer_tabledata( & $obj )
{
    return get_html_table_data_elems( array(
        $obj->order_id,
        \basic_objects\to_string_LocalTime( $obj->delivery_time ) ) ) .
        \lieferbay_protocol\to_html_Order_tabledata( $obj->order ) .
        get_html_table_data_elems( array(
            $obj->sum,
            $obj->earning,
            $obj->weight
            ) );
}

function to_html_DashScreenUser( & $obj )
{
    $res = '<h3>Dash Screen User ( current time ' . \basic_objects\to_string_LocalTime( $obj->current_time ) . ' )</h3>';

    {
        $num   = sizeof( $obj->rides );

        $res = $res . '<h2>Offered OfferWithStates ( ' . $num . ' )</h2>';

        $body = '';
        for( $i = 0; $i < $num; $i++ )
        {
            $body = $body . get_html_table_tr( to_html_OfferWithBuyer_tabledata( $obj->rides[$i] ) );
        }

        $res = $res . get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
                get_html_table_tr( get_header_OfferWithBuyer() ) . $body );
    }

    {
        $num   = sizeof( $obj->orders );

        $res = $res . '<h2>My orders ( ' . $num . ' )</h2>';

        $body = '';
        for( $i = 0; $i < $num; $i++ )
        {
            $body = $body . get_html_table_tr( to_html_AcceptedOrderUser_tabledata( $obj->orders[$i] ) );
        }

        $res = $res . get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
            get_html_table_tr( get_header_AcceptedOrderUser() ) . $body );
    }

    return $res;
}

function to_html_GetDashScreenUserResponse( & $obj )
{
    $res = to_html_DashScreenUser( $obj->dash_screen );

    return $res;
}

function to_html_DashScreenBuyer( & $obj )
{
    $res = '<h3>Dash Screen Buyer ( current time ' . \basic_objects\to_string_LocalTime( $obj->current_time ) . ' )</h3>';

    {
        $num   = sizeof( $obj->rides );

        $res = $res . '<h2>My Offered OfferWithStates and Shopping Requests ( ' . $num . ' )</h2>';

        $body = '';
        for( $i = 0; $i < $num; $i++ )
        {
            $body = $body . get_html_table_tr( to_html_OfferWithStateWithId_tabledata( $obj->rides[$i] ) );
        }

        $res = $res . get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
            get_html_table_tr( get_header_OfferWithStateWithId() ) . $body );
    }

    {
        $num   = sizeof( $obj->orders );

        $res = $res . '<h2>My accepted orders ( ' . $num . ' )</h2>';

        $body = '';
        for( $i = 0; $i < $num; $i++ )
        {
            $body = $body . get_html_table_tr( to_html_AcceptedOrderBuyer_tabledata( $obj->orders[$i] ) );
        }

        $res = $res . get_html_table( NULL, NULL, NULL, 'border="1" cellspacing="1" cellpadding="3"',
            get_html_table_tr( get_header_AcceptedOrderBuyer() ) . $body );
    }

    return $res;
}

function to_html_GetDashScreenBuyerResponse( & $obj )
{
    $res = to_html_DashScreenBuyer( $obj->dash_screen );

    return $res;
}

// *********************************************************

function to_html( $obj )
{
    $handler_map = array(
        'lieferbay_protocol\web\GetProductItemListRequest'      => 'to_html_not_impl',
        'lieferbay_protocol\web\GetProductItemListResponse'     => 'to_html_GetProductItemListResponse',
        'lieferbay_protocol\web\GetShoppingRequestInfoRequest'        => 'to_html_not_impl',
        'lieferbay_protocol\web\GetShoppingRequestInfoResponse'       => 'to_html_GetShoppingRequestInfoResponse',
        'lieferbay_protocol\web\GetShoppingListWithTotalsRequest'   => 'to_html_not_impl',
        'lieferbay_protocol\web\GetShoppingListWithTotalsResponse'  => 'to_html_GetShoppingListWithTotalsResponse',
        'lieferbay_protocol\web\GetDashScreenUserRequest'       => 'to_html_not_impl',
        'lieferbay_protocol\web\GetDashScreenUserResponse'      => 'to_html_GetDashScreenUserResponse',
        'lieferbay_protocol\web\GetDashScreenBuyerRequest'    => 'to_html_not_impl',
        'lieferbay_protocol\web\GetDashScreenBuyerResponse'   => 'to_html_GetDashScreenBuyerResponse'
    );

    $type = get_class ( $obj );

    if( array_key_exists( $type, $handler_map ) )
    {
        $func = '\\lieferbay_protocol\\web\\' . $handler_map[ $type ];
        return $func( $obj );
    }

    return \lieferbay_protocol\to_html( $obj );
}

?>
