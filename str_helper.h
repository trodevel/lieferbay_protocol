/*

String Helper. Provides to_string() function.

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

#include <string>
#include <sstream>

#include "enums.h"                  // request_type_e
#include "protocol.h"     // order_state_e

namespace lieferbay_protocol {

class StrHelper
{
public:
    static const std::string & to_string( const request_type_e l );
    static const std::string & to_string( const order_state_e l );
    static const std::string & to_string( const order_resolution_e l );
    static std::ostream & write( std::ostream & os, const GeoPosition & l );
    static std::ostream & write( std::ostream & os, const Offer & l );
    static std::ostream & write( std::ostream & os, const AddOfferWithStateRequest & l );
    static std::ostream & write( std::ostream & os, const CancelOfferWithStateRequest & l );
    static std::ostream & write( std::ostream & os, const GetOfferWithStateRequest & l );
    static std::ostream & write( std::ostream & os, const AddOrderRequest & l );
    static std::ostream & write( std::ostream & os, const CancelOrderRequest & l );
    static std::ostream & write( std::ostream & os, const AcceptOrderRequest & l );
    static std::ostream & write( std::ostream & os, const DeclineOrderRequest & l );
    static std::ostream & write( std::ostream & os, const MarkDeliveredOrderRequest & l );
    static std::ostream & write( std::ostream & os, const RateBuyerRequest & l );

    template<class T>
    static std::string to_string( const T & l )
    {
        std::ostringstream os;

        write( os, l );

        return os.str();
    }
};

} // namespace lieferbay_protocol

namespace lieferbay_protocol {

namespace web {

class StrHelper
{
public:
    static const std::string & to_string( const request_type_e l );
    static std::ostream & write( std::ostream & os, const GetProductItemListRequest & l );
    static std::ostream & write( std::ostream & os, const GetShoppingRequestInfoRequest & l );
    static std::ostream & write( std::ostream & os, const GetDashScreenUserRequest & l );
    static std::ostream & write( std::ostream & os, const GetDashScreenBuyerRequest & l );

    template<class T>
    static std::string to_string( const T & l )
    {
        std::ostringstream os;

        write( os, l );

        return os.str();
    }
};

} // namespace web

} // namespace lieferbay_protocol
