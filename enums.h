/*

Core enums.

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

#ifndef LIEFERBAY_PROTOCOL_ENUMS_H
#define LIEFERBAY_PROTOCOL_ENUMS_H

namespace lieferbay_protocol {

enum class request_type_e
{
    UNDEF,
    AddOfferWithStateRequest,
    CancelOfferWithStateRequest,
    GetOfferWithStateRequest,
    AddOrderRequest,
    CancelOrderRequest,
    AcceptOrderRequest,
    DeclineOrderRequest,
    MarkDeliveredOrderRequest,
    RateBuyerRequest,
};

namespace web {

enum class request_type_e
{
    UNDEF,
    GetProductItemListRequest,
    GetShoppingRequestInfoRequest,
    GetShoppingListWithTotalsRequest,
    GetDashScreenUserRequest,
    GetDashScreenBuyerRequest
};

} // namespace web

} // namespace lieferbay_protocol

#endif // LIEFERBAY_PROTOCOL_ENUMS_H
