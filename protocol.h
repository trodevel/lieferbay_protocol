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

// $Revision: 12348 $ $Date:: 2019-11-12 #$ $Author: serge $

#ifndef LIB_LIEFERBAY_PROTOCOL__PROTOCOL_H
#define LIB_LIEFERBAY_PROTOCOL__PROTOCOL_H

#include <cstdint>              // uint32_t
#include <map>                  // std::map
#include <vector>               // std::vector

#include "generic_protocol/generic_protocol.h"   // generic_protocol::Request
#include "basic_objects/basic_objects.h" // basic_objects::LocalTime

namespace lieferbay_protocol {

struct Request: public generic_protocol::Request
{
    virtual ~Request() {};
};

typedef uint32_t    id_t;

/**************************************************
 * OBJECTS
 **************************************************/

struct ProductItem
{
    std::string     name;
    std::string     unit;
    double          price;
    double          weight;
};

struct ShoppingItem
{
    id_t            product_item_id;
    uint32_t        amount;
};

struct ShoppingList
{
    std::vector<ShoppingItem>   items;
};

struct GeoPosition
{
    uint32_t        plz;
    double          latitude;
    double          longitude;
};

struct Offer
{
    basic_objects::LocalTimeRange delivery_time;
    double          delivery_price;
    bool            can_return;
    double          return_price;
};

enum class ride_resolution_e
{
    UNDEF                       = 0,
    EXPIRED_OR_COMPLETED        = 1,
    CANCELLED                   = 2,
};

struct Ride
{
    bool                is_open;
    Offer         summary;
    std::vector<id_t>   pending_order_ids;
    id_t                accepted_order_id;
    ride_resolution_e   resolution;
};

enum class order_resolution_e
{
    UNDEF                       = 0,
    DELIVERED                   = 1,
    DECLINED_BY_SHOPPER         = 2,
    RIDE_CANCELLED              = 3,
    CANCELLED_BY_SHOPPER        = 4,
    CANCELLED_BY_USER           = 5,
};

enum class order_state_e
{
    UNDEF                           = 0,
    IDLE_WAITING_OFFERS             = 1,
    ACCEPTED_WAITING_SHOPPING_START = 2,
    SHOPPING_WAITING_SHOPPING_END   = 3,
    SHOPPING_ENDED_WAITING_DELIVERY = 4,
    DELIVERED_WAITING_CONFIRMATION  = 5,
    DELIVERY_CONFIRMED_WAITING_FEEDBACK  = 6,
    DONE                            = 7,
    CANCELLED_IN_SHOPPING           = 8,
    CANCELLED_IN_SHOPPING_ENDED     = 9,
};

enum class gender_e
{
    UNDEF   = 0,
    MALE    = 1,
    FEMALE  = 2,
};

struct Address
{
    uint32_t    plz;
    std::string country;
    std::string city;
    std::string street;
    std::string house_number;
    std::string extra_address_line;
};

struct Order
{
    bool                is_open;
    id_t                ride_id;
    Address             delivery_address;
    id_t                shopping_list_id;
    order_state_e       state;
    order_resolution_e  resolution;
};

/**************************************************
 * REQUESTS
 **************************************************/

struct AddRideRequest: public Request
{
    Offer     ride;
};

struct AddRideResponse: public generic_protocol::BackwardMessage
{
    id_t            ride_id;
};

struct CancelRideRequest: public Request
{
    id_t            ride_id;
};

struct CancelRideResponse: public generic_protocol::BackwardMessage
{
};

struct GetRideRequest: public Request
{
    id_t            ride_id;
};

struct GetRideResponse: public generic_protocol::BackwardMessage
{
    Ride            ride;
};

struct AddOrderRequest: public Request
{
    id_t            ride_id;
    ShoppingList    shopping_list;
    Address         delivery_address;
};

struct AddOrderResponse: public generic_protocol::BackwardMessage
{
    id_t            order_id;
};

struct CancelOrderRequest: public Request
{
    id_t            order_id;
};

struct CancelOrderResponse: public generic_protocol::BackwardMessage
{
};

struct AcceptOrderRequest: public Request
{
    id_t            order_id;
};

struct AcceptOrderResponse: public generic_protocol::BackwardMessage
{
};

struct DeclineOrderRequest: public Request
{
    id_t            order_id;
};

struct DeclineOrderResponse: public generic_protocol::BackwardMessage
{
};

struct MarkDeliveredOrderRequest: public Request
{
    id_t            order_id;
};

struct MarkDeliveredOrderResponse: public generic_protocol::BackwardMessage
{
};

struct RateBuyerRequest: public Request
{
    id_t            order_id;
    uint32_t        stars;
};

struct RateBuyerResponse: public generic_protocol::BackwardMessage
{
};

namespace web
{

/**************************************************
 * WEB OBJECTS
 **************************************************/

struct ProductItemWithId
{
    id_t            product_item_id;
    ProductItem     product_item;
};

struct ShoppingItemWithProduct
{
    ShoppingItem    shopping_item;
    ProductItem     product_item;
};

struct ShoppingListWithProduct
{
    std::vector<ShoppingItemWithProduct>   items;
};

struct ShoppingListWithTotals
{
    ShoppingListWithProduct    shopping_list;
    double          price;
    double          weight;
};

struct OfferWithBuyer
{
    id_t            ride_id;
    Offer     ride;
    std::string     buyer_name;
};

struct RideWithId
{
    id_t            ride_id;
    Ride            ride;
};

struct ShoppingRequestInfo
{
    id_t            order_id;
    double          sum;
    double          earning;
    double          weight;
    Address         address;
};

struct AcceptedOrderUser
{
    id_t            order_id;
    basic_objects::LocalTime delivery_time;
    Order           order;
    double          sum;
    std::string     buyer_name;
};

struct AcceptedOrderBuyer
{
    id_t            order_id;
    basic_objects::LocalTime delivery_time;
    Order           order;
    double          sum;
    double          earning;
    double          weight;
};

struct DashScreenUser
{
    basic_objects::LocalTime        current_time;

    std::vector<OfferWithBuyer> rides;
    std::vector<AcceptedOrderUser>      orders;
};

struct DashScreenBuyer
{
    basic_objects::LocalTime        current_time;

    std::vector<RideWithId>             rides;
    std::vector<AcceptedOrderBuyer>   orders;
};

/**************************************************
 * WEB REQUESTS
 **************************************************/

struct GetProductItemListRequest: public Request
{
};

struct GetProductItemListResponse: public generic_protocol::BackwardMessage
{
    std::vector<ProductItemWithId>  product_items;
};

struct GetShoppingRequestInfoRequest: public Request
{
    id_t            ride_id;
};

struct GetShoppingRequestInfoResponse: public generic_protocol::BackwardMessage
{
    std::vector<ShoppingRequestInfo>    requests;
};

struct GetShoppingListWithTotalsRequest: public Request
{
    id_t            shopping_list_id;
};

struct GetShoppingListWithTotalsResponse: public generic_protocol::BackwardMessage
{
    ShoppingListWithTotals  shopping_list;
};

struct GetDashScreenUserRequest: public Request
{
    id_t            user_id;
    GeoPosition     position;
};

struct GetDashScreenUserResponse: public generic_protocol::BackwardMessage
{
    DashScreenUser  dash_screen;
};

struct GetDashScreenBuyerRequest: public Request
{
    id_t            user_id;
    GeoPosition     position;
};

struct GetDashScreenBuyerResponse: public generic_protocol::BackwardMessage
{
    DashScreenBuyer   dash_screen;
};

} // namespace web

} // namespace lieferbay_protocol

#endif // LIB_LIEFERBAY_PROTOCOL__PROTOCOL_H
