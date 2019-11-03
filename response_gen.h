/*

Protocol response generator.

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

// $Revision: 12315 $ $Date:: 2019-10-31 #$ $Author: serge $

#ifndef LIB_LIEFERBAY_PROTOCOL_RESPONSE_GEN_H
#define LIB_LIEFERBAY_PROTOCOL_RESPONSE_GEN_H

#include "protocol.h"        // AddOrderResponse

namespace lieferbay_protocol {

inline AddRideResponse * create_AddRideResponse(
        id_t                            ride_id )
{
    auto * res = new AddRideResponse;

    res->ride_id    = ride_id;

    return res;
}

inline CancelRideResponse * create_CancelRideResponse()
{
    auto * res = new CancelRideResponse;

    return res;
}

inline GeoPosition * init_GeoPosition(
        GeoPosition     * res,
        uint32_t        plz,
        double          latitude,
        double          longitude )
{
    res->plz            = plz;
    res->latitude       = latitude;
    res->longitude      = longitude;

    return res;
}

inline RideSummary * init_RideSummary(
        RideSummary           * res,
        const GeoPosition               & position,
        const basic_objects::LocalTime  & delivery_time,
        double                          max_weight )
{
    res->position       = position;
    res->delivery_time  = delivery_time;
    res->max_weight     = max_weight;

    return res;
}

inline Ride * init_Ride(
        Ride           * res,
        bool                            is_open,
        const RideSummary               & summary,
        const std::vector<id_t>         & pending_order_ids,
        id_t                            accepted_order_id,
        ride_resolution_e               resolution )
{
    res->is_open            = is_open;
    res->summary            = summary;
    res->pending_order_ids  = pending_order_ids;
    res->accepted_order_id  = accepted_order_id;
    res->resolution         = resolution;

    return res;
}

inline GetRideResponse * create_GetRideResponse(
        const Ride  & ride )
{
    auto * res = new GetRideResponse;

    res->ride   = ride;

    return res;
}

inline AddOrderResponse * create_AddOrderResponse( id_t order_id )
{
    auto * res = new AddOrderResponse;

    res->order_id   = order_id;

    return res;
}

inline CancelOrderResponse * create_CancelOrderResponse()
{
    auto * res = new CancelOrderResponse;

    return res;
}

inline AcceptOrderResponse * create_AcceptOrderResponse()
{
    auto * res = new AcceptOrderResponse;

    return res;
}

inline DeclineOrderResponse * create_DeclineOrderResponse()
{
    auto * res = new DeclineOrderResponse;

    return res;
}

inline MarkDeliveredOrderResponse * create_MarkDeliveredOrderResponse()
{
    auto * res = new MarkDeliveredOrderResponse;

    return res;
}

inline RateBuyerResponse * create_RateBuyerResponse()
{
    auto * res = new RateBuyerResponse;

    return res;
}

} // namespace lieferbay_protocol

namespace lieferbay_protocol {

namespace web {

inline GetProductItemListResponse * create_GetProductItemListResponse(
        const std::vector<ProductItemWithId>  & product_items )
{
    auto * res = new GetProductItemListResponse;

    res->product_items  = product_items;

    return res;
}

inline GetShoppingRequestInfoResponse * create_GetShoppingRequestInfoResponse(
        const std::vector<ShoppingRequestInfo>    & rides )
{
    auto * res = new GetShoppingRequestInfoResponse;

    res->requests  = rides;

    return res;
}

inline GetShoppingListWithTotalsResponse * create_GetShoppingListWithTotalsResponse(
        const ShoppingListWithTotals    & shopping_list )
{
    auto * res = new GetShoppingListWithTotalsResponse;

    res->shopping_list  = shopping_list;

    return res;
}

inline GetDashScreenUserResponse * create_GetDashScreenUserResponse(
        const DashScreenUser & dash_screen )
{
    auto * res = new GetDashScreenUserResponse;

    res->dash_screen    = dash_screen;

    return res;
}

inline GetDashScreenBuyerResponse * create_GetDashScreenBuyerResponse(
        const DashScreenBuyer & dash_screen )
{
    auto * res = new GetDashScreenBuyerResponse;

    res->dash_screen    = dash_screen;

    return res;
}

inline DashScreenUser * init_DashScreenUser(
        DashScreenUser  * res,
        const basic_objects::LocalTime              & current_time,
        const std::vector<RideSummaryWithBuyer>   & rides,
        const std::vector<AcceptedOrderUser>        & orders )
{
    res->current_time   = current_time;
    res->rides          = rides;
    res->orders         = orders;

    return res;
}

inline DashScreenBuyer * init_DashScreenBuyer(
        DashScreenBuyer  * res,
        const basic_objects::LocalTime          & current_time,
        const std::vector<RideWithId>           & rides,
        const std::vector<AcceptedOrderBuyer> & orders )
{
    res->current_time   = current_time;
    res->rides          = rides;
    res->orders         = orders;

    return res;
}


inline ShoppingRequestInfo * init_ShoppingRequestInfo(
        ShoppingRequestInfo * res,
        id_t                order_id,
        double              sum,
        double              earning,
        double              weight,
        Address             address )
{
    res->order_id   = order_id;
    res->sum        = sum;
    res->earning    = earning;
    res->weight     = weight;
    res->address    = address;

    return res;
}

} // namespace web

} // namespace lieferbay_protocol

#endif // LIB_LIEFERBAY_PROTOCOL_RESPONSE_GEN_H
