#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "PNRParser.hpp"
#include <algorithm>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

int main(int argc, char** argv) {
  
  std::fstream file;
  file.open(argv[argc-1]);
  std::string input;
  
  if(file.is_open()) {
    std::stringstream stream;
    stream<< file.rdbuf();
    input = stream.str();
  }

  auto iter_beg = input.begin();
  auto iter_end = input.end();

  PNRParser<std::string::iterator> parser;
  PNRWrapper parsed_data;
  bool result = qi::phrase_parse(iter_beg, iter_end, parser, ascii::space, parsed_data);

  if(!result) {
    
    std::cout<<"Parse input false!\n";
    return -1;
  }

  //Print some data for check 
  std::cout<<"File parsed successfull! Data: \n"
    <<parsed_data.pnr.xsd<<"\n"
    <<parsed_data.pnr.xsi<<"\n"
    <<"Number of passengers: "<<parsed_data.pnr.NumberOffPassengers<<"\n"
    <<parsed_data.pnr.PNR_TransDate<<"\n"
    <<parsed_data.pnr.PNR_CreationDate<<"\n" 
    <<parsed_data.pnr.booking.xmlns<<"\n"
    <<"Booking ID: "<<parsed_data.pnr.booking.ID<<"\n"
    <<"------- PASSENGERS ------------------ ------------------:\n";

  std::for_each(parsed_data.pnr.passengers.begin(), parsed_data.pnr.passengers.end(),
      [](const PassengerData& p) {
        std::cout<<"------- PASSENGER DATA -------------- ------------------"<<std::endl;
        std::cout<<p.GivenName<<"\n"<<p.Surname<<"\n"<<p.RPH<<std::endl;
        std::cout<<"SSR CODE: "<<p.ssr_data.SSRCode<<", Service quantity: "
          <<p.ssr_data.ServiceQuantity<<std::endl;
          std::cout<<"SSR STATUS: "<<p.ssr_data.Status<<", RPH: "<<p.ssr_data.RPH<<std::endl;
          std::cout<<"Flight info code: "<<p.ssr_data.fl_data.Code<<std::endl;
        std::cout<<"--------- ------------ -------------- ------------------"<<std::endl;
        });

  std::cout<<"Starting point code: "<<parsed_data.pnr.flight.ariv_airport<<std::endl;
  std::cout<<"End point code: "<<parsed_data.pnr.flight.dep_airport<<std::endl;
  std::cout<<"Flight number: "<<parsed_data.pnr.flight.FlightNumber<<std::endl;
  std::cout<<"Company code: "<<parsed_data.pnr.flight.CompanyCode<<std::endl;
  std::for_each(parsed_data.pnr.flight.ssr_s.begin(), parsed_data.pnr.flight.ssr_s.end(), [](const SSRData& f) {
    std::cout<<"BEGIN SSR ------------ -------------- ------------------"<<std::endl;
    std::cout<<"AIR LINE CODE: "<<f.al_code<<std::endl;
    std::cout<<"SERVICE Qty; "<<f.service_quantity<<std::endl;
    std::cout<<"STATUS: "<<f.status<<std::endl;
    std::cout<<"BEG POINT: "<<f.BoardPoint<<std::endl;
    std::cout<<"OFF POINT: "<<f.OffPoint<<std::endl;
    std::cout<<"RPH: "<<f.RPH<<std::endl;
    std::cout<<"TEXT DESC: "<<f.text<<std::endl;
    std::cout<<"END SSR -------------- -------------- ------------------"<<std::endl;
  });
}

