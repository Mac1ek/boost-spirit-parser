#ifndef _PNR_DATA_TYPES_HPP__
#define _PNR_DATA_TYPES_HPP__

#include <string>
#include <vector>

struct PNRData {
    std::string xsd;
    std::string xsi;
    std::string NumberOffPassengers;
    std::string PNR_TransDate;
    std::string PNR_CreationDate;
};

struct BookingData {
  std::string xmlns;
  std::string ID;
  std::string Code;
};

struct FlightInfoData {
  std::string Code;
};

struct DOCSData {
  std::string Gender;
  std::string Surname;
  std::string FirstGivenName;
};

struct DOC_SSRData {
  std::string SSRCode;
  std::string ServiceQuantity;
  std::string Status;
  std::string RPH;
  FlightInfoData fl_data;
  DOCSData docs_data;
};

struct PassengerData { 
  std::string xmlns;
  std::string RPH;
  std::string SurnameRefNumber;
  std::string AccompByInf;
  std::string GivenName;
  std::string Surname;
  DOC_SSRData ssr_data;
};

struct SSRData {
    std::string ssr_code;
    std::string service_quantity;
    std::string status;
    std::string BoardPoint;
    std::string OffPoint;
    std::string RPH;
    std::string al_code;
    std::string text;
};

struct FlightData {
  std::string xmlns;
  std::string DepartureDateTime;
  std::string ArrivalDateTime;
  std::string NumberInParty;
  std::string Status;
  std::string FlightNumber;
  std::string dep_airport;
  std::string ariv_airport;
  std::string marketing_al;
  std::vector<SSRData> ssr_s;
  std::string BookingRefID;
  std::string CompanyCode;
};

struct PNRWrapper {
  PNRData pnr;
  BookingData booking;
  std::vector<PassengerData> passengers;
  FlightData flight;
};

#endif

