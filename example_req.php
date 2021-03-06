<?php

// $Revision: 12394 $ $Date:: 2019-11-18 #$ $Author: serge $

require_once 'lieferbay_protocol_web.php';

echo "OK\n";

$session_id = "afafaf";

{
    $ride_summary = new \lieferbay_protocol\Ride( \lieferbay_protocol\GeoPosition::withPlz( 50668 ), new \basic_objects\LocalTime( 2019, 05, 22, 17, 30, 0 ), 2.5 );

    $req = new \lieferbay_protocol\AddRideRequest( $session_id, $ride_summary );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id    = 101;

    $req = new \lieferbay_protocol\CancelRideRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id    = 101;

    $req = new \lieferbay_protocol\GetRideWithStateRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;

    $items = array();

    array_push( $items, new \lieferbay_protocol\ShoppingItem( 1212, 1 ) );
    array_push( $items, new \lieferbay_protocol\ShoppingItem( 2323, 2 ) );
    array_push( $items, new \lieferbay_protocol\ShoppingItem( 3434, 7 ) );

    $shopping_list  = new \lieferbay_protocol\ShoppingList( $items );

    $delivery_address = new \lieferbay_protocol\Address( 50668, "Germany", "Köln", "Eigelstein", "10", "" );

    $req = new \lieferbay_protocol\AddOrderRequest( $session_id, $ride_id, $shopping_list, $delivery_address );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;

    $req = new \lieferbay_protocol\CancelOrderRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;

    $req = new \lieferbay_protocol\AcceptOrderRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;

    $req = new \lieferbay_protocol\DeclineOrderRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;

    $req = new \lieferbay_protocol\NotifyDeliveredRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id        = 101;
    $stars          = 4;

    $req = new \lieferbay_protocol\RateBuyerRequest( $session_id, $ride_id, $stars );

    echo "req = " . $req->to_generic_request() . "\n";
}

/**************************************************
 * WEB REQUESTS
 **************************************************/

{
    $req = new \lieferbay_protocol\web\GetProductItemListRequest( $session_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $ride_id    = 101;

    $req = new \lieferbay_protocol\web\GetShoppingRequestInfoRequest( $session_id, $ride_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $shopping_list_id   = 232323;

    $req = new \lieferbay_protocol\web\GetShoppingListWithTotalsRequest( $session_id, $shopping_list_id );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $user_id    = 115;

    $req = new \lieferbay_protocol\web\GetDashScreenUserRequest( $session_id, $user_id, \lieferbay_protocol\GeoPosition::withPlz( 50668 ) );

    echo "req = " . $req->to_generic_request() . "\n";
}

{
    $user_id    = 115;

    $req = new \lieferbay_protocol\web\GetDashScreenBuyerRequest( $session_id, $user_id, \lieferbay_protocol\GeoPosition::withPlz( 50668 ) );

    echo "req = " . $req->to_generic_request() . "\n";
}

?>
