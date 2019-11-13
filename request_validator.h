/*

Request Validator.

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

#include "protocol.h"    // Request...

namespace lieferbay_protocol {

class RequestValidator
{
public:
    static bool validate( const id_t & r, const std::string & key );
    static bool validate( const order_state_e & r );
    static bool validate( const ProductItem & r );
    static bool validate( const ShoppingItem & r );
    static bool validate( const ShoppingList & r );
    static bool validate( const GeoPosition & r );
    static bool validate( const Offer & r );
    static bool validate( const Address & r );
    static bool validate( const AddOfferWithStateRequest & r );
    static bool validate( const CancelOfferWithStateRequest & r );
    static bool validate( const GetOfferWithStateRequest & r );
    static bool validate( const AddOrderRequest & r );
    static bool validate( const CancelOrderRequest & r );
    static bool validate( const AcceptOrderRequest & r );
    static bool validate( const DeclineOrderRequest & r );
    static bool validate( const MarkDeliveredOrderRequest & r );
    static bool validate( const RateBuyerRequest & r );
};

namespace web {

class RequestValidator
{
public:
    static bool validate( const GetProductItemListRequest & r );
    static bool validate( const GetShoppingRequestInfoRequest & r );
    static bool validate( const GetShoppingListWithTotalsRequest & r );
    static bool validate( const GetDashScreenUserRequest & r );
    static bool validate( const GetDashScreenBuyerRequest & r );
};

} // namespace web

} // namespace lieferbay_protocol

