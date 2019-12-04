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

// $Revision: 12419 $ $Date:: 2019-12-04 #$ $Author: serge $

namespace lieferbay_protocol;

require_once __DIR__.'/../basic_objects/basic_objects.php';         // \basic_objects\TimeWindow, \basic_objects\Weekdays
require_once __DIR__.'/../generic_protocol/generic_protocol.php';

class Request extends \generic_protocol\Request
{
    function __construct( $session_id )
    {
        parent::__construct( $session_id );
    }
}

/**************************************************
 * OBJECTS
 **************************************************/

class ProductItem
{
    public          $name;      // string
    public          $unit;      // string
    public          $price;     // double
    public          $weight;	// double
}

class ShoppingItem
{
    public          $product_item_id;  // id_t
    public          $amount;           // int

    function __construct( $product_item_id, $amount )
    {
        $this->product_item_id  = $product_item_id;
        $this->amount           = $amount;
    }

    public function to_generic_request()
    {
        $res = $this->product_item_id . "," . $this->amount;

        return $res;
    }
}

class ShoppingList
{
    public          $items; // array<ShoppingItem>

    function __construct( $items )
    {
        $this->items    = $items;
    }

    public function to_generic_request()
    {
        $size   = sizeof( $this->items );

        $body = '';
        for( $i = 0; $i < $size; $i++ )
        {
            $body = $body . $this->items[$i]->to_generic_request() . ",";
        }

        $res = array(
            "SHOPPING_LIST"    => $body );

        return \generic_protocol\assemble_request( $res );
    }
}

class GeoPosition
{
    public          $plz;       // int
    public          $latitude;  // double
    public          $longitude; // double

    function __construct( $plz, $latitude, $longitude )
    {
        $this->plz                  = $plz;
        $this->latitude             = $latitude;
        $this->longitude            = $longitude;
    }

    public static function withPlz( $plz )
    {
        $instance = new self( $plz, 0, 0 );

        return $instance;
    }

    public static function withPos( $latitude, $longitude )
    {
        $instance = new self( 0, $latitude, $longitude);

        return $instance;
    }

    public function to_generic_request()
    {
        $res = array(
            "PLZ"           => $this->plz,
            "LATITUDE"      => $this->latitude,
            "LONGITUDE"     => $this->longitude
            );

        return \generic_protocol\assemble_request( $res );
    }
}

class Ride
{
    public      $position;      // GeoPosition
    public      $delivery_time; // basic_objects::LocalTime
    public      $max_weight;    // double
    public      $delivery_price;    // double
    public      $can_accept_cancellation;        // bool
    public      $cancellation_price;      // double

    function __construct( $position, $delivery_time, $max_weight, $delivery_price, $can_accept_cancellation, $cancellation_price )
    {
        $this->position         = $position;
        $this->delivery_time    = $delivery_time;
        $this->max_weight       = $max_weight;
        $this->delivery_price   = $delivery_price;
        $this->can_accept_cancellation       = $can_accept_cancellation;
        $this->cancellation_price     = $cancellation_price;
    }

    public function to_generic_request()
    {
        $res = array(
            "MAX_WEIGHT"    => $this->max_weight
            "DELIVERY_PRICE"    => $this->delivery_price,
            "CAN_RETURN"        => $this->can_accept_cancellation,
            "RETURN_PRICE"      => $this->cancellation_price
            );

        return \generic_protocol\assemble_request( $res ) .
            $this->position->to_generic_request() .
            $this->delivery_time->to_generic_request( "DELIVERY_TIME" );
    }
}

const ride_resolution_e_UNDEF                   = 0;
const ride_resolution_e_EXPIRED_OR_COMPLETED    = 1;
const ride_resolution_e_CANCELLED               = 2;

class RideWithState
{
    public  $is_open;           // bool
    public  $summary;           // Ride
    public  $pending_order_ids; // array<id_t>
    public  $accepted_order_id; // id_t
    public  $resolution;        // ride_resolution_e
};

const order_resolution_e_UNDEF                  = 0;
const order_resolution_e_DELIVERED              = 1;
const order_resolution_e_DECLINED_BY_BUYER    = 2;
const order_resolution_e_RIDE_CANCELLED         = 3;
const order_resolution_e_SHOPPING_FAILED   = 4;
const order_resolution_e_CANCELLED_BY_USER      = 5;


const order_state_e_UNDEF                           = 0;
const order_state_e_IDLE_WAITING_ACCEPTANCE         = 1;
const order_state_e_ACCEPTED_WAITING_SHOPPING_START = 2;
const order_state_e_SHOPPING_WAITING_SHOPPING_END   = 3;
const order_state_e_SHOPPING_ENDED_WAITING_DELIVERY = 4;
const order_state_e_DELIVERED_WAITING_CONFIRMATION  = 5;
const order_state_e_DELIVERY_CONFIRMED_WAITING_CHECK  = 6;
const order_state_e_CHECKED_WAITING_FEEDBACK        = 7;
const order_state_e_DONE                            = 8;
const order_state_e_CANCELLED_IN_SHOPPING           = 9;
const order_state_e_CANCELLED_IN_SHOPPING_ENDED     = 10;

const gender_e_UNDEF   = 0;
const gender_e_MALE    = 1;
const gender_e_FEMALE  = 2;

class Address
{
    public      $plz;       // int
    public      $country;   // string
    public      $city;      // string
    public      $street;    // string
    public      $house_number;  // string
    public      $extra_address_line;    // string

    function __construct( $plz, $country, $city, $street, $house_number, $extra_address_line )
    {
        $this->plz      = $plz;
        $this->country  = $country;
        $this->city     = $city;
        $this->street   = $street;
        $this->house_number = $house_number;
        $this->extra_address_line   = $extra_address_line;
    }

    public function to_generic_request()
    {
        $res = array(
            "PLZ"       => $this->plz,
            "COUNTRY:X" => str2hex( $this->country ),
            "CITY:X"    => str2hex( $this->city ),
            "STREET:X"  => str2hex( $this->street ),
            "HOUSE_NUMBER:X" => str2hex( $this->house_number ),
            "EAL:X"     => str2hex( $this->extra_address_line )
        );

        return \generic_protocol\assemble_request( $res );
    }

}

class Order
{
    public  $ride_id;           // id_t
    public  $delivery_address;  // Address
    public  $shopping_list_id;  // id_t
}

class OrderWithState
{
    public  $is_open;           // bool
    public  $order;             // Order
    public  $state;             // order_state_e
    public  $resolution;        // order_resolution_e
}

/**************************************************
 * REQUESTS
 **************************************************/

class AddRideRequest extends Request
{
    public $ride;   // Ride

    function __construct( $session_id, $ride )
    {
        parent::__construct( $session_id );

        $this->ride             = $ride;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "AddRideRequest"
            );

        return \generic_protocol\assemble_request( $res ) .
            $this->ride->to_generic_request() .
            parent::to_generic_request();
    }
}

class AddRideResponse extends \generic_protocol\BackwardMessage
{
    public        $ride_id;     // id_t
}

class CancelRideRequest extends Request
{
    public $ride_id;   // id_t

    function __construct( $session_id, $ride_id )
    {
        parent::__construct( $session_id );

        $this->ride_id          = $ride_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "CancelRideRequest",
            "RIDE_ID"   => $this->ride_id
            );

        return \generic_protocol\assemble_request( $res ) .
            parent::to_generic_request();
    }
}

class CancelRideResponse extends \generic_protocol\BackwardMessage
{
}

class GetRideWithStateRequest extends Request
{
    public $ride_id;   // id_t

    function __construct( $session_id, $ride_id )
    {
        parent::__construct( $session_id );

        $this->ride_id          = $ride_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "GetRideWithStateRequest",
            "RIDE_ID"   => $this->ride_id
            );

        return \generic_protocol\assemble_request( $res ) .
            parent::to_generic_request();
    }
}

class GetRideWithStateResponse extends \generic_protocol\BackwardMessage
{
    public $ride;   // RideWithState
}

class AddOrderRequest extends Request
{
    public $ride_id;        // id_t
    public $shopping_list;  // ShoppingList
    public $delivery_address;   // Address

    function __construct( $session_id, $ride_id, $shopping_list, $delivery_address )
    {
        parent::__construct( $session_id );

        $this->ride_id          = $ride_id;
        $this->shopping_list    = $shopping_list;
        $this->delivery_address = $delivery_address;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "AddOrderRequest",
            "RIDE_ID"   => $this->ride_id
            );

        return \generic_protocol\assemble_request( $res ) .
            $this->shopping_list->to_generic_request() .
            $this->delivery_address->to_generic_request() .
            parent::to_generic_request();
    }
}

class AddOrderResponse extends \generic_protocol\BackwardMessage
{
    public $order_id;   // id_t
}

class CancelOrderRequest extends Request
{
    public $order_id;   // id_t

    function __construct( $session_id, $order_id )
    {
        parent::__construct( $session_id );

        $this->order_id     = $order_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "CancelOrderRequest",
            "ORDER_ID"  => $this->order_id
            );

        return \generic_protocol\assemble_request( $res ) .
            parent::to_generic_request();
    }
}

class CancelOrderResponse extends \generic_protocol\BackwardMessage
{
}

class AcceptOrderRequest extends Request
{
    public $order_id;   // id_t

    function __construct( $session_id, $order_id )
    {
        parent::__construct( $session_id );

        $this->order_id     = $order_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "AcceptOrderRequest",
            "ORDER_ID"  => $this->order_id
        );

        return \generic_protocol\assemble_request( $res ) .
        parent::to_generic_request();
    }
}

class AcceptOrderResponse extends \generic_protocol\BackwardMessage
{
}

class DeclineOrderRequest extends Request
{
    public $order_id;   // id_t

    function __construct( $session_id, $order_id )
    {
        parent::__construct( $session_id );

        $this->order_id     = $order_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "DeclineOrderRequest",
            "ORDER_ID"  => $this->order_id
        );

        return \generic_protocol\assemble_request( $res ) .
        parent::to_generic_request();
    }
}

class DeclineOrderResponse extends \generic_protocol\BackwardMessage
{
}

class NotifyDeliveredRequest extends Request
{
    public $order_id;   // id_t

    function __construct( $session_id, $order_id )
    {
        parent::__construct( $session_id );

        $this->order_id     = $order_id;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "NotifyDeliveredRequest",
            "ORDER_ID"  => $this->order_id
        );

        return \generic_protocol\assemble_request( $res ) .
        parent::to_generic_request();
    }
}

class NotifyDeliveredResponse extends \generic_protocol\BackwardMessage
{
}

class RateBuyerRequest extends Request
{
    public $order_id;   // id_t
    public $stars;      // int

    function __construct( $session_id, $order_id, $stars )
    {
        parent::__construct( $session_id );

        $this->order_id     = $order_id;
        $this->stars        = $stars;
    }

    public function to_generic_request()
    {
        $res = array(
            "CMD"       => "RateBuyerRequest",
            "ORDER_ID"  => $this->order_id,
            "STARS"     => $this->stars,
        );

        return \generic_protocol\assemble_request( $res ) .
        parent::to_generic_request();
    }
}

class RateBuyerResponse extends \generic_protocol\BackwardMessage
{
}

?>
