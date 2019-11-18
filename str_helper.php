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

// $Revision: 12394 $ $Date:: 2019-11-18 #$ $Author: serge $

namespace lieferbay_protocol;

require_once 'protocol.php';

function to_string_GeoPosition( & $obj )
{
    $res = $obj->plz . " ( " . $obj->latitude . ", " . $obj->longitude . " )";

    return $res;
}

function to_string_ride_resolution_e( $val )
{
    $map = array(
        ride_resolution_e_UNDEF                     => 'UNDEF',
        ride_resolution_e_EXPIRED_OR_COMPLETED      => 'EXPIRED_OR_COMPLETED',
        ride_resolution_e_CANCELLED                 => 'CANCELLED',
    );

    if( array_key_exists( $val, $map ) )
    {
        return $map[ $val ];
    }

    return "?";
}

function to_string_order_state_e( $val )
{
    $map = array(
        order_state_e_UNDEF                         => 'UNDEF',
        order_state_e_IDLE_WAITING_ACCEPTANCE       => 'IDLE_WAITING_ACCEPTANCE',
        order_state_e_ACCEPTED_WAITING_SHOPPING_START       => 'ACCEPTED_WAITING_SHOPPING_START',
        order_state_e_SHOPPING_WAITING_SHOPPING_END         => 'SHOPPING_WAITING_SHOPPING_END',
        order_state_e_SHOPPING_ENDED_WAITING_DELIVERY       => 'SHOPPING_ENDED_WAITING_DELIVERY',
        order_state_e_DELIVERED_WAITING_CONFIRMATION        => 'DELIVERED_WAITING_CONFIRMATION',
        order_state_e_DELIVERY_CONFIRMED_WAITING_FEEDBACK   => 'DELIVERY_CONFIRMED_WAITING_FEEDBACK',
        order_state_e_DONE                          => 'DONE',
        order_state_e_CANCELLED_IN_SHOPPING         => 'CANCELLED_IN_SHOPPING',
        order_state_e_CANCELLED_IN_SHOPPING_ENDED   => 'CANCELLED_IN_SHOPPING_ENDED',
    );

    if( array_key_exists( $val, $map ) )
    {
        return $map[ $val ];
    }

    return "?";
}

function to_string_order_resolution_e( $val )
{
    $map = array(
        order_resolution_e_UNDEF                    => 'UNDEF',
        order_resolution_e_DELIVERED                => 'DELIVERED',
        order_resolution_e_DECLINED_BY_SHOPPER      => 'DECLINED_BY_SHOPPER',
        order_resolution_e_RIDE_CANCELLED           => 'RIDE_CANCELLED',
        order_resolution_e_CANCELLED_BY_SHOPPER     => 'CANCELLED_BY_SHOPPER',
        order_resolution_e_CANCELLED_BY_USER        => 'CANCELLED_BY_USER',
    );

    if( array_key_exists( $val, $map ) )
    {
        return $map[ $val ];
    }

    return "?";
}

?>
