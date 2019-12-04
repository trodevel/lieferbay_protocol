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
    bool            is_mandatory;
    bool            should_accept_expensive_alternative;
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

struct Ride
{
    GeoPosition     position;
    basic_objects::LocalTimeRange delivery_time;
    double          max_weight;
    double          delivery_price;
    bool            can_accept_cancellation;
    double          cancellation_price;
};

enum class ride_resolution_e
{
    UNDEF                       = 0,
    EXPIRED_OR_COMPLETED        = 1,
    CANCELLED                   = 2,
};

struct RideWithState
{
    bool                is_open;
    Ride                summary;
    std::vector<id_t>   pending_order_ids;
    std::vector<id_t>   declined_order_ids;
    id_t                accepted_order_id;
    ride_resolution_e   resolution;
};

enum class order_resolution_e
{
    UNDEF                       = 0,
    DELIVERED                   = 1,
    DELIVERED_WITH_ISSUES       = 2,
    DECLINED_BY_BUYER           = 3,
    RIDE_CANCELLED              = 4,
    SHOPPING_FAILED             = 5,
    CANCELLED_BY_USER           = 6,
};

enum class failure_reason_e
{
    UNDEF                       = 0,
    MISSING_ITEM                = 1,
    SHOP_CLOSED                 = 2,
    TIME_SHORTAGE               = 3,
    OTHER                       = 4,
};

enum class order_state_e
{
    UNDEF                           = 0,
    IDLE_WAITING_ACCEPTANCE         = 1,
    ACCEPTED_WAITING_SHOPPING_START = 2,
    SHOPPING_WAITING_SHOPPING_END   = 3,
    SHOPPING_ENDED_WAITING_DELIVERY = 4,
    DELIVERED_WAITING_CONFIRMATION  = 5,
    DELIVERY_CONFIRMED_WAITING_CHECK  = 6,
    CHECKED_WAITING_FEEDBACK        = 7,
    DONE                            = 8,
    CANCELLED_IN_SHOPPING           = 9,
    CANCELLED_IN_SHOPPING_ENDED     = 10,
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
    id_t                ride_id;
    Address             delivery_address;
    ShoppingList        shopping_list;
    basic_objects::LocalTimeRange wish_delivery_time;
    bool                is_time_fixed;
    double              wish_delivery_price;
};

struct OrderWithState
{
    bool                is_open;
    Order               order;
    order_state_e       state;
    order_resolution_e  resolution;
};

/**************************************************
 * REQUESTS
 **************************************************/

struct AddRideRequest: public Request
{
    Ride            ride;
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

struct GetRideWithStateRequest: public Request
{
    id_t            ride_id;
};

struct GetRideWithStateResponse: public generic_protocol::BackwardMessage
{
    RideWithState   ride;
};

struct AddOrderRequest: public Request
{
    Order           order;
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

struct NotifyShoppingStartedRequest: public Request
{
    id_t            order_id;
};

struct NotifyShoppingStartedResponse: public generic_protocol::BackwardMessage
{
};

struct NotifyShoppingEndedRequest: public Request
{
    id_t            order_id;
};

struct NotifyShoppingEndedResponse: public generic_protocol::BackwardMessage
{
};

struct NotifyShoppingFailedRequest: public Request
{
    id_t            order_id;
};

struct NotifyShoppingFailedResponse: public generic_protocol::BackwardMessage
{
};

struct NotifyDeliveredRequest: public Request
{
    id_t            order_id;
};

struct NotifyDeliveredResponse: public generic_protocol::BackwardMessage
{
};

struct ConfirmDeliveryRequest: public Request
{
    id_t            order_id;
};

struct ConfirmDeliveryResponse: public generic_protocol::BackwardMessage
{
};

struct ComplainRequest: public Request
{
    id_t            order_id;
};

struct ComplainResponse: public generic_protocol::BackwardMessage
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

struct RateUserRequest: public Request
{
    id_t            order_id;
    uint32_t        stars;
};

struct RateUserResponse: public generic_protocol::BackwardMessage
{
};

} // namespace lieferbay_protocol

#endif // LIB_LIEFERBAY_PROTOCOL__PROTOCOL_H
