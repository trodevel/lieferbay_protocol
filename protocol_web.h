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

// $Revision: 12391 $ $Date:: 2019-11-18 #$ $Author: serge $

#ifndef LIB_LIEFERBAY_PROTOCOL__PROTOCOL_WEB_H
#define LIB_LIEFERBAY_PROTOCOL__PROTOCOL_WEB_H

#include "protocol.h"           // ShoppingItem

namespace lieferbay_protocol {

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

struct RideWithBuyer
{
    id_t            ride_id;
    Ride            ride;
    std::string     buyer_name;
};

struct RideWithStateWithId
{
    id_t            ride_id;
    RideWithState   ride;
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

    std::vector<RideWithBuyer>      rides;
    std::vector<AcceptedOrderUser>  orders;
};

struct DashScreenBuyer
{
    basic_objects::LocalTime        current_time;

    std::vector<RideWithStateWithId>             rides;
    std::vector<AcceptedOrderBuyer> orders;
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

#endif // LIB_LIEFERBAY_PROTOCOL__PROTOCOL_WEB_H
