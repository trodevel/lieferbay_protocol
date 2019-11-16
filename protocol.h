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

// $Revision: 12387 $ $Date:: 2019-11-16 #$ $Author: serge $

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

struct RideSummary
{
    GeoPosition         position;
    basic_objects::LocalTime delivery_time;
    double              max_weight;
};

struct Offer
{
    id_t            order_id;
    basic_objects::LocalTimeRange delivery_time;
    double          delivery_price;
    bool            can_accept_cancellation;
    double          cancellation_price;
};

enum class offer_state_e
{
    UNDEF                       = 0,
    PENDING                     = 1,
    ACCEPTED                    = 2,
    DECLINED                    = 3,
    CANCELLED                   = 4,
};

struct OfferWithState
{
    bool                is_open;
    Offer               offer;
    offer_state_e       state;
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
    std::vector<id_t>   pending_offer_ids;
    id_t                accepted_offer_id;
};

/**************************************************
 * REQUESTS
 **************************************************/

struct AddOfferRequest: public Request
{
    Offer           offer;
};

struct AddOfferResponse: public generic_protocol::BackwardMessage
{
    id_t            offer_id;
};

struct CancelOfferRequest: public Request
{
    id_t            offer_id;
};

struct CancelOfferResponse: public generic_protocol::BackwardMessage
{
};

struct GetOfferWithStateRequest: public Request
{
    id_t            offer_id;
};

struct GetOfferWithStateResponse: public generic_protocol::BackwardMessage
{
    OfferWithState  offer_with_state;
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

struct AcceptOfferRequest: public Request
{
    id_t            order_id;
};

struct AcceptOfferResponse: public generic_protocol::BackwardMessage
{
};

struct DeclineOfferRequest: public Request
{
    id_t            order_id;
};

struct DeclineOfferResponse: public generic_protocol::BackwardMessage
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
