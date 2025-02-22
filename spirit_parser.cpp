#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <tuple>
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
    <<parsed_data.pnr.NumberOffPassengers<<"\n"
    <<parsed_data.pnr.PNR_TransDate<<"\n"
    <<parsed_data.pnr.PNR_CreationDate<<"\n" 
    <<parsed_data.booking.xmlns<<"\n"
    <<parsed_data.booking.ID<<"\n"
    <<"PASSENGERS:\n";

  std::for_each(parsed_data.passengers.begin(), parsed_data.passengers.end(), 
      [](const PassengerData& p) {
        std::cout<<p.GivenName<<"\n"<<p.Surname<<"\n"<<p.RPH<<std::endl;
        std::cout<<"SSR CODE: "<<p.ssr_data.SSRCode<<", Service quantity: "
          <<p.ssr_data.ServiceQuantity<<std::endl;
          std::cout<<"SSR STATUS: "<<p.ssr_data.Status<<", RPH: "<<p.ssr_data.RPH<<std::endl;
          std::cout<<"Flight info code: "<<p.ssr_data.fl_data.Code<<std::endl; 
        });

  std::for_each(parsed_data.flight.ssr_s.begin(), parsed_data.flight.ssr_s.end(), [](const SSRData& f) {
    std::cout<<"AIR LINE CODE: "<<f.al_code<<std::endl;
    std::cout<<"SERVICE Qty; "<<f.service_quantity<<std::endl;
    std::cout<<"STATUS: "<<f.status;
    std::cout<<"POINT: "<<f.BoardPoint<<std::endl;
    std::cout<<"OFF POINT: "<<f.OffPoint<<std::endl;
    std::cout<<"RPH: "<<f.RPH<<std::endl;
    std::cout<<"TEXT DESC: "<<f.text<<std::endl;
  });
}

