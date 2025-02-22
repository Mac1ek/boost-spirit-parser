//
// Created by maciek on 2/20/25.
//

#ifndef PARSER_ADAPT_STRUCT_H
#define PARSER_ADAPT_STRUCT_H

#include <boost/fusion/include/adapt_struct.hpp>
#include "DataTypes.hpp"

BOOST_FUSION_ADAPT_STRUCT(
    PNRData,
    (std::string, xsd)
    (std::string, xsi)
    (std::string, NumberOffPassengers)
    (std::string, PNR_TransDate)
    (std::string, PNR_CreationDate)
)

BOOST_FUSION_ADAPT_STRUCT(
    BookingData,
    (std::string, xmlns)
    (std::string, ID)
    (std::string, Code)
)

BOOST_FUSION_ADAPT_STRUCT(
    PassengerData,
    (std::string, xmlns)
    (std::string, RPH)
    (std::string, SurnameRefNumber)
    (std::string, AccompByInf)
    (std::string, GivenName)
    (std::string, Surname)
    (DOC_SSRData, ssr_data)
)

BOOST_FUSION_ADAPT_STRUCT(
    DOC_SSRData,
    (std::string, SSRCode)
    (std::string, ServiceQuantity)
    (std::string, Status)
    (std::string, RPH)
    (FlightInfoData, fl_data)
    (DOCSData, docs_data)
)

BOOST_FUSION_ADAPT_STRUCT(
    FlightInfoData,
    (std::string, Code)
)

BOOST_FUSION_ADAPT_STRUCT(
  DOCSData,
  (std::string, Gender)
  (std::string, Surname)
  (std::string, FirstGivenName)
)

BOOST_FUSION_ADAPT_STRUCT(
    PNRWrapper,
    (PNRData, pnr)
    (BookingData, booking)
    (std::vector<PassengerData>, passengers)
    (FlightData, flight)
)

BOOST_FUSION_ADAPT_STRUCT(
    SSRData,
    (std::string, ssr_code)
    (std::string, service_quantity)
    (std::string, status)
    (std::string, BoardPoint)
    (std::string, OffPoint)
    (std::string, RPH)
    (std::string, al_code)
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    FlightData,
    (std::string, xmlns)
    (std::string, DepartureDateTime)
    (std::string, ArrivalDateTime)
    (std::string, NumberInParty)
    (std::string, Status)
    (std::string, FlightNumber)
    (std::string, dep_airport)
    (std::string, ariv_airport)
    (std::string, marketing_al)
    (std::vector<SSRData>, ssr_s)
    (std::string, BookingRefID)
    (std::string, CompanyCode)
)

#endif //PARSER_ADAPT_STRUCT_H
