#ifndef _PNR_PARSER_HPP__
#define _PNR_PARSER_HPP__

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <vector>
#include "parser_adapt.hpp"
#include "DataTypes.hpp"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

template<typename Iterator>
class PNRParser : public qi::grammar<Iterator, PNRWrapper(), ascii::space_type> {

    qi::rule<Iterator, std::string(), ascii::space_type> TEXT;
    qi::rule<Iterator, std::string(), ascii::space_type> Q_TEXT;
    qi::rule<Iterator, PNRWrapper(), ascii::space_type> T_XML;
    qi::rule<Iterator, PNRData(), ascii::space_type> T_PNR;
    qi::rule<Iterator, BookingData(), ascii::space_type> T_BOOKING;
    qi::rule<Iterator, PassengerData(), ascii::space_type> T_PASSENGER;
    qi::rule<Iterator, DOC_SSRData(), ascii::space_type> T_DOC_SSR;
    qi::rule<Iterator, FlightInfoData(), ascii::space_type> T_FLINFO;
    qi::rule<Iterator, DOCSData(), ascii::space_type> T_DOCS;
    qi::rule<Iterator, std::vector<PassengerData>(), ascii::space_type> T_PASSENGERS;
    qi::rule<Iterator, FlightData(), ascii::space_type> T_FLIGHT; 
    qi::rule<Iterator, std::vector<SSRData>(), ascii::space_type> T_SSR_S;
    qi::rule<Iterator, SSRData(), ascii::space_type> T_SSR;

  private:

    void create_pnr_rule() {
      T_PNR %= qi::lit("<PNR") >>
        qi::lit("xmlns:xsd=") >> Q_TEXT >>
        qi::lit("xmlns:xsi=") >> Q_TEXT >>
        qi::lit("NumberOfPassengers=") >> Q_TEXT >>
        qi::lit("PNR_TransDate=") >> Q_TEXT >>
        qi::lit("PNR_CreationDate=") >> Q_TEXT >>
        qi::lit(">") >>
      T_BOOKING [phoenix::bind(&PNRData::booking, qi::_val) = qi::_1] >>
      T_PASSENGERS [phoenix::bind(&PNRData::passengers, qi::_val) = qi::_1] >>
      T_FLIGHT [phoenix::bind(&PNRData::flight, qi::_val) = qi::_1] >>
      qi::lit("</PNR>");
    }

    void create_booking_rule() {
      T_BOOKING %= qi::lit("<BookingRefID") >>
        qi::lit("xmlns=") >> Q_TEXT >>
        qi::lit("ID=") >> Q_TEXT >>
        qi::lit(">") >>
        qi::lit("<CompanyName") >> 
        qi::lit("Code=") >> Q_TEXT >>
        qi::lit("/>") >> 
        qi::lit("</BookingRefID>");
    }

    void create_passenger_rule() {
      T_PASSENGERS %= *T_PASSENGER;

      T_PASSENGER %= qi::lit("<Passenger") >>
        qi::lit("xmlns=") >> Q_TEXT >>
        qi::lit("RPH=") >> Q_TEXT >>
        qi::lit("SurnameRefNumber=") >> Q_TEXT >>
        qi::lit("AccompaniedByInfantInd=") >> Q_TEXT >>
        qi::lit(">") >>
        qi::lit("<GivenName>") >> TEXT >> qi::lit("</GivenName>") >>
        qi::lit("<Surname>") >> TEXT >> qi::lit("</Surname>") >>
        T_DOC_SSR [phoenix::bind(&PassengerData::ssr_data, qi::_val) = qi::_1] >> 
        qi::lit("</Passenger>");
    }

    void create_doc_ssr_data() {
      T_DOC_SSR %= qi::lit("<DOC_SSR") >>
        qi::lit("SSRCode=") >> Q_TEXT  >>
        qi::lit("ServiceQuantity=") >> Q_TEXT >>
        qi::lit("Status=") >> Q_TEXT >>
        qi::lit("RPH=") >> Q_TEXT >> 
        qi::lit(">") >> 
        T_FLINFO [phoenix::bind(&DOC_SSRData::fl_data, qi::_val) = qi::_1] >> 
        T_DOCS [phoenix::bind(&DOC_SSRData::docs_data, qi::_val) = qi::_1] >> 
        qi::lit("</DOC_SSR>");
    }

    void create_flight_info_data() {
      T_FLINFO %= qi::lit("<FlightInfo") >>
        qi::lit("Code=") >> Q_TEXT >> 
        qi::lit("/>");
    }
    void create_docs_data() {
      T_DOCS %= qi::lit("<DOCS") >>
        -(qi::lit("Gender=") >> Q_TEXT) >>
        qi::lit("Surname=") >> Q_TEXT >>
        qi::lit("FirstGivenName=") >> Q_TEXT >>
        qi::lit("/>");
    }

    void create_flight_ssr_rule() {
      T_SSR_S %= *T_SSR;

      T_SSR %= qi::lit("<SSR") >>
        qi::lit("SSRCode=") >> Q_TEXT >>
        qi::lit("ServiceQuantity=") >> Q_TEXT >>
        qi::lit("Status=") >> Q_TEXT >> 
        -(qi::lit("BoardPoint=") >> Q_TEXT) >>
        -(qi::lit("OffPoint=") >> Q_TEXT) >>
        qi::lit("RPH=") >> Q_TEXT >> qi::lit(">") >> 
        qi::lit("<Airline") >> qi::lit("Code=") >> Q_TEXT >> qi::lit("/>") >> 
        -(qi::lit("<Text>" ) >> TEXT >> qi::lit("</Text>")) >>
        -(qi::lit("<Text/>")) >> qi::lit("</SSR>");

    }

    void create_flight_rule() {
      T_FLIGHT %= qi::lit("<Flight") >>
        qi::lit("xmlns=") >> Q_TEXT >>
        qi::lit("DepartureDateTime=") >> Q_TEXT >>
        qi::lit("ArrivalDateTime=") >> Q_TEXT >>
        qi::lit("NumberInParty=") >> Q_TEXT >>
        qi::lit("Status=") >> Q_TEXT >>
        qi::lit("FlightNumber=") >> Q_TEXT >> qi::lit(">") >>
        
        qi::lit("<DepartureAirport") >> qi::lit("LocationCode=") >> Q_TEXT >> qi::lit("/>") >>
        qi::lit("<ArrivalAirport") >> qi::lit("LocationCode=") >> Q_TEXT >> qi::lit("/>") >>
        qi::lit("<MarketingAirline") >> qi::lit("Code=") >> Q_TEXT >> qi::lit("/>") >>
        T_SSR_S [phoenix::bind(&FlightData::ssr_s, qi::_val) = qi::_1] >>
        qi::lit("<BookingRefID") >> qi::lit("ID=") >> Q_TEXT >> qi::lit(">") >>
        qi::lit("<CompanyName") >> qi::lit("Code=") >> Q_TEXT >> qi::lit("/>") >> 
        qi::lit("</BookingRefID>") >> qi::lit("</Flight>");
    }

    void create_xmldata_rule() {
      T_XML = qi::lit("<DaneXML>") >> 
        T_PNR [phoenix::bind(&PNRWrapper::pnr, qi::_val) = qi::_1] >>
        qi::lit("</DaneXML>");
    }

    void create_terminals_rules() {
      TEXT = qi::lexeme[+(qi::char_ - '<')];
      Q_TEXT %= qi::lexeme['"' >> +(qi::char_ - '"') >> '"'];
    }

  public:
    PNRParser() : PNRParser::base_type(T_XML) {

        this->create_terminals_rules();
        this->create_flight_ssr_rule();
        this->create_flight_rule();
        this->create_passenger_rule();
        this->create_booking_rule();
        this->create_pnr_rule();
        this->create_xmldata_rule();
        this->create_doc_ssr_data();
        this->create_flight_info_data();
        this->create_docs_data();
    }
};

#endif // _PNR_PARSER_HPP__
