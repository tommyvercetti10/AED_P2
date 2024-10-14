//
// Created by miguel-duarte on 20-12-2023.
//

#include "Menu.h"
#include <limits>

Menu::Menu(Management& m_) : m(m_) {}

void Menu::run() {
    const char* boldOn = "\033[1m";
    const char* boldOff = "\033[0m";
    string uc, button, exit;
    start:
    cout << boldOn << "============╬ MENU ╬============" << boldOff << '\n';
    cout << boldOn << "1." << boldOff << " Traveling\n";
    cout << boldOn << "2." << boldOff << " Information\n";
    cout << boldOn << "3." << boldOff << " Exit\n";
    cout << "Choose an option: ";
    int option, option11, option12, option21, option22, option23, option24, option25, maxStops;
    string x;
    list<Airline> airlines;
    do {
        cin >> option;
        switch (option) {
            case 1: {
                flighOpt:
                flightOptions();
                cout << boldOn << "=====================================\n" << boldOff;
                cout << boldOn << "1." << boldOff << " Check another travel\n";
                cout << boldOn << "2." << boldOff << " Go back to Menu\n";
                cout << boldOn << "3." << boldOff << " Exit\n";
                cout << "Choose an option: ";
                cin >> option11;
                if (option11 == 1) goto flighOpt;
                else if (option11 == 2) goto start;
                else if (option11 == 3) option = 3;
                break;
            }
            case 2: {
                information:
                cout << "\n--------- Information ---------\n";
                cout << boldOn << "1." << boldOff << " -- Flight Network\n";
                cout << boldOn << "2." << boldOff << " -- Airport\n";
                cout << boldOn << "3." << boldOff << " -- Country\n";
                cout << boldOn << "4." << boldOff << " -- City\n";
                cout << boldOn << "5." << boldOff << " -- Airline\n";
                cout << boldOn << "6." << boldOff << " Go Back\n";
                cout << "Choose an option: ";
                cin >> option21;

                if (option21 == 1) {
                    flightNet:
                    cout << "\n-------- Flight Network --------\n";
                    cout << boldOn << "1." << boldOff << " Overall number of airports\n";
                    cout << boldOn << "2." << boldOff << " Number of airlines\n";
                    cout << boldOn << "3." << boldOff << " Number of flights\n";
                    cout << boldOn << "4." << boldOff << " Top Airports with the highest number of flights\n";
                    cout << boldOn << "5." << boldOff << " Maximum trip(s) (with the highest number of stops)\n";
                    cout << boldOn << "6." << boldOff << " Essential Airports\n";
                    cout << boldOn << "7." << boldOff << " Go Back\n";
                    cout << "Choose an option: ";
                    cin >> option22;
                    if (option22 == 1) {
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Airports ========" << boldOff << '\n';
                        cout << "The flight network has " << m.getRf().getairports().size() << " airports.\n";
                        cout << boldOn << "====================================\n" << boldOff;
                        cout << boldOn << "1." << boldOff << " Go Back\n";
                        cout << boldOn << "2." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto flightNet;
                        else if (option11 == 2) option = 3;
                    }
                    else if (option22 == 2) {
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Airlines ========" << boldOff << '\n';
                        cout << "The flight network has " << m.getRf().getairlines().size() << " airlines.\n";
                        cout << boldOn << "====================================\n" << boldOff;
                        cout << boldOn << "1." << boldOff << " Go Back\n";
                        cout << boldOn << "2." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto flightNet;
                        else if (option11 == 2) option = 3;
                    }
                    else if (option22 == 3) {
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << "The flight network has " << m.getRf().getflights().size() << " flights.\n";
                        cout << boldOn << "====================================\n" << boldOff;
                        cout << boldOn << "1." << boldOff << " Go Back\n";
                        cout << boldOn << "2." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto flightNet;
                        else if (option11 == 2) option = 3;
                    }
                    else if (option22 == 4) {
                        topAir:
                        int top;
                        vector<pair<Vertex*, int>> numberFlights;   //[]
                        cout << "Choose the number of airports you wish to obtain: ";
                        cin >> top;
                        for (pair<const basic_string<char>, Vertex *> vertex : m.getRf().getgraph().getVertexSet()) {
                            numberFlights.emplace_back(vertex.second, vertex.second->getAdj().size() + vertex.second->getArrival());
                        }
                        sort(numberFlights.begin(), numberFlights.end(), m.comparePair);
                        cout << "Loading...\n";
                        cout << boldOn << "\n======== Top Airports ========" << boldOff << '\n';
                        cout<<"Top "<<top<<" airports in the global network with the most flights:"<<endl;
                        for (int i=0;i<top & i < numberFlights.size(); i++){
                            cout<< boldOn << i+1<<" - " << boldOff
                            << "["<<numberFlights.at(i).first->getInfo().getcode() << ", "
                            << numberFlights.at(i).first->getInfo().getname() << ", " <<
                            numberFlights.at(i).first->getInfo().getcity() << "] with "
                            << numberFlights.at(i).second << " flights" <<'\n';
                        }
                        cout << boldOn << "================================\n" << boldOff;
                        cout << boldOn << "1." << boldOff << " Check other Top\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto topAir;
                        else if (option11 == 2) goto flightNet;
                        else if (option11 == 3) option = 3;
                    }
                    else if (option22 == 5) {
                        cout << "Loading...\n";
                        set<pair<Airport, Airport>> airports = m.maxStops();
                        cout << boldOn << "======== Maximum Trips ========" << boldOff << '\n';
                        for (pair<Airport, Airport> a : airports) {
                            cout << a.first.getcode() + " - " + a.first.getcity()
                                 << boldOn << " --> " << "Stops: " << boldOff << m.getMaxDistance()
                                 << boldOn << " --> " << boldOff
                                 << a.second.getcode() + " - " + a.second.getcity();
                            cout << '\n';
                        }
                        cout << boldOn << "===============================\n" << boldOff;
                        cout << boldOn << "1." << boldOff << " Go Back\n";
                        cout << boldOn << "2." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto flightNet;
                        else if (option11 == 2) option = 3;
                    }
                    else if (option22 == 6) {
                        cout << "Loading...\n";
                        cout << boldOn << "====== Essential Airports ======" << boldOff << '\n';
                        m.essentialAirports();
                        cout << boldOn << "================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Go Back\n";
                        cout << boldOn << "2." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto flightNet;
                        else if (option11 == 2) option = 3;
                    }
                    else if (option22 == 7) goto information;
                }
                if (option21 == 2) {
                    airInfo:
                    string airport;
                    cout << "\n-------- Airport Informations --------\n";
                    cout << boldOn << "1." << boldOff << " Number of flights \n";
                    cout << boldOn << "2." << boldOff << " Number of airlines \n";
                    cout << boldOn << "3." << boldOff << " Number of destinations\n";
                    cout << boldOn << "4." << boldOff << " Number of reachable destinations within X lay-overs\n";
                    cout << boldOn << "5." << boldOff << " Reachable countries\n";
                    cout << boldOn << "6." << boldOff << " Go Back\n";
                    cout << "Choose an option: ";
                    cin >> option23;
                    set<string> airlines;
                    if (option23 == 1) {
                        airFlights:
                        int count = 0;
                        cout << "Enter the desired airport code: ";
                        cin >> airport;
                        cout << "Loading...\n";
                        for (Flight flight: m.getRf().getflights()) {
                            if (flight.getsource() == airport) count++;
                        }
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << "The Airport has " << count << " outbound flights of a total of "
                        << m.flightsForAirport(airport) << " flights.";
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airport\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto airFlights;
                        else if (option11 == 2) goto airInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 2) {
                        airNum:
                        cout << "Enter the desired airport code: ";
                        cin >> airport;
                        for (Flight flight: m.getRf().getflights()) {
                            if (flight.getsource() == airport) airlines.insert(flight.getairline());
                        }
                        cout << boldOn << "======== Number of Airlines ========" << boldOff << '\n';
                        cout << "There are " << airlines.size() << " airlines leaving this airport.";
                        cout << boldOn << "\n====================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airport\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto airNum;
                        else if (option11 == 2) goto airInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 3) {
                        airDes:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the desired airport (code): ";
                        getline(std::cin, airport);
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Destinations ========" << boldOff << '\n';
                        vector<int> dests = m.destinationsForAirport(airport);
                        cout << "The " + airport + " airport has " << dests[0] << " available airports, "
                        << dests[1] << " available cities and " << dests[2] << " available countries." << '\n';
                        cout << boldOn << "========================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airport\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto airDes;
                        else if (option11 == 2) goto airInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 4) {
                        desNum:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the desired airport (code): ";
                        getline(std::cin, airport);
                        cout << "And the number of lay-overs (stops): ";
                        int stops;
                        cin >> stops;
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Destinations ========" << boldOff << '\n';
                        vector<int> dests = m.destinationsForAirportLayOvers(airport, stops);
                        cout << "The " + airport + " airport has " << dests[0] << " available airports, "
                             << dests[1] << " available cities and " << dests[2] << " available countries, on trips with "
                             << stops << " lay-overs." << '\n';
                        cout << boldOn << "========================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airport\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto desNum;
                        else if (option11 == 2) goto airInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 5) {
                        reachCountry:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the desired airport (code or name): ";
                        getline(std::cin, airport);
                        cout << "Loading...\n";
                        vector <Airport> airports = m.getRf().getAirports(airport);
                        cout << boldOn << "======== Reachable Countries ========" << boldOff << '\n';
                        if (airports.empty()) cout << "Couldn't find an airport/city with that name.\n";
                        else {
                            set<string> countries = m.countriesForAirCity(airports);
                            cout << "The " + airports[0].getcode() + " - " + airports[0].getname() + " airport can reach " << countries.size() << " countries." << '\n';
                            cout << boldOn << "Countries:" << boldOff;
                            int i = 0;
                            for (string c : countries)
                            {
                                if (i % 6 == 0) cout << '\n';
                                cout << " - " << c;
                                i++;
                            }
                        }
                        cout << boldOn << "\n=====================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airport\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto reachCountry;
                        else if (option11 == 2) goto airInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 6) {
                        goto information;
                    }
                }
                if(option21 == 3) {
                    countryInfo:
                    string country;
                    cout << "\n-------- Country Informations --------\n";
                    cout << boldOn << "1." << boldOff << " Number of airports\n";
                    cout << boldOn << "2." << boldOff << " Number of flights leaving the country\n";
                    cout << boldOn << "3." << boldOff << " Number of flights arriving in the country\n";
                    cout << boldOn << "4." << boldOff << " Go Back\n";
                    cout << "Choose an option: ";
                    cin >> option23;
                    set<string> countries;
                    if (option23 == 1) {
                        countryAir:
                        cout << "Enter the name of the desired country: ";
                        cin >> country;
                        cout << "Loading...\n";
                        for(pair<const basic_string<char>, Airport> airport : m.getRf().getairports()) {
                            if (airport.second.getcountry() == country) {
                                countries.insert(airport.second.getname());
                            }
                        }
                        cout << boldOn << "======== Number of Airports ========" << boldOff << '\n';
                        cout << country << " has " << countries.size() <<  " airports.";
                        cout << boldOn << "\n====================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other country\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto countryAir;
                        else if (option11 == 2) goto countryInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 2) {
                        countryFlightsLeave:
                        cout << "Enter the name of the desired country: ";
                        cin >> country;
                        int count = 0;
                        for (pair<string, Vertex*> vertexSet : m.getRf().getgraph().getVertexSet()) {
                            if (vertexSet.second->getInfo().getcountry() == country) count= count + vertexSet.second->getAdj().size();
                        }
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << country << " has " << count << " flights leaving.";
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other country\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto countryFlightsLeave;
                        else if (option11 == 2) goto countryInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 3) {
                        countryFlightsArrive:
                        cout << "Enter the name of the desired country: ";
                        cin >> country;
                        int count = 0;
                        for (pair<string, Vertex*> vertexSet : m.getRf().getgraph().getVertexSet()) {
                            if (vertexSet.second->getInfo().getcountry() == country) count= count + vertexSet.second->getArrival();
                        }
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << country << " has " << count << " flights arriving.";
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other country\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto countryFlightsArrive;
                        else if (option11 == 2) goto countryInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option23 == 4) {
                        goto information;
                    }
                }
                if (option21 == 4) {
                    cityInfo:
                    cout << "\n--------- City Information ---------\n";
                    cout << boldOn << "1." << boldOff << " Number of flights\n";
                    cout << boldOn << "2." << boldOff << " Reachable countries\n";
                    cout << boldOn << "3." << boldOff << " Go Back\n";
                    cout << "Choose an option: ";
                    cin >> option24;
                    string cityName;
                    if (option24 == 1) {
                        cityFlightNum:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the name of the city: ";
                        getline(std::cin, cityName);
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << cityName << " has " << m.flightsForCityAirline(cityName) <<  " flights.";
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other city\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto cityFlightNum;
                        else if (option11 == 2) goto cityInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option24 == 2) {
                        reachCountriesCity:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the name of the city: ";
                        getline(std::cin, cityName);
                        cout << "Loading...\n";
                        vector <Airport> airports = m.getRf().getAirports(cityName);
                        cout << boldOn << "======== Reachable Countries ========" << boldOff << '\n';
                        if (airports.empty()) cout << "Couldn't find an city with that name.\n";
                        else {
                            set<string> countries = m.countriesForAirCity(airports);
                            cout << cityName << " can reach " << countries.size() << " countries." << '\n';
                            cout << boldOn << "Countries:" << boldOff;
                            int i = 0;
                            for (string c : countries)
                            {
                                if (i % 6 == 0) cout << '\n';
                                cout << " - " << c;
                                i++;
                            }
                        }
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other city\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto reachCountriesCity;
                        else if (option11 == 2) goto cityInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option24 == 3) {
                        goto information;
                    }
                }
                if (option21 == 5) {
                    airlineInfo:
                    cout << "\n--------- Airline Information ---------\n";
                    cout << boldOn << "1." << boldOff << " Number of flights\n";
                    cout << boldOn << "2." << boldOff << " Country of an airline\n";
                    cout << boldOn << "3." << boldOff << " Airports covered by an airline\n";
                    cout << boldOn << "4." << boldOff << " Go Back\n";
                    cout << "Choose an option: ";
                    cin >> option25;
                    string airline;
                    if (option25 == 1) {
                        airNumFlights:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the code of the airline: ";
                        getline(std::cin, airline);
                        cout << "Loading...\n";
                        cout << boldOn << "======== Number of Flights ========" << boldOff << '\n';
                        cout << airline << " has " << m.flightsForCityAirline(airline) <<  " flights.";
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airline\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto airNumFlights;
                        else if (option11 == 2) goto airlineInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option25 == 2) {
                        countryAirline:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the code of the airline: ";
                        getline(std::cin, airline);
                        cout << "Loading...\n";
                        cout << boldOn << "======== Country of Airline ========" << boldOff;
                        for (pair<const basic_string<char>, Airline> airline2 : m.getRf().getairlines()) {
                            if (airline2.second.getcode() == airline) {
                                cout << "\n" << airline2.second.getname() << " is based in "
                                     << airline2.second.getcountry() << ".";
                            }
                        }
                        cout << boldOn << "\n====================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airline\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto countryAirline;
                        else if (option11 == 2) goto airlineInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option25 == 3) {
                        airportLines:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the code of the airline: ";
                        getline(std::cin, airline);
                        cout << "Loading...\n";
                        cout << boldOn << "======== Covered Airports ========\n" << boldOff;
                        set<string> airports;
                        for (Flight flight : m.getRf().getflights()) {
                            if (flight.getairline() == airline) {
                                airports.insert(flight.getsource());
                                airports.insert(flight.gettarget());
                            }
                        }
                        cout << airline <<" covers " << airports.size() << " airports.";
                        cout << boldOn << "\nAirports:" << boldOff;
                        int i = 0;
                        for (string c : airports)
                        {
                            if (i % 15 == 0) cout << '\n';
                            cout << " " << c;
                            i++;
                        }
                        cout << boldOn << "\n===================================" << boldOff << '\n';
                        cout << boldOn << "1." << boldOff << " Check other airline\n";
                        cout << boldOn << "2." << boldOff << " Go Back\n";
                        cout << boldOn << "3." << boldOff << " Exit\n";
                        cout << "Choose an option: ";
                        cin >> option11;
                        if (option11 == 1) goto airportLines;
                        else if (option11 == 2) goto airlineInfo;
                        else if (option11 == 3) option = 3;
                    }
                    if (option25 == 4) {
                        goto information;
                    }
                    if (option25 == 2) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the code of the airline: ";
                        getline(std::cin, airline);
                        cout << "Loading...\n";
                        for (pair<const basic_string<char>, Airline> airline2 : m.getRf().getairlines()) {
                            if (airline2.second.getcode() == airline) {
                                cout << "\n" << airline2.second.getname() << " is based in "
                                     << airline2.second.getcountry();
                            }
                        }
                    }
                    if (option25 == 3) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter the code of the airline: ";
                        getline(std::cin, airline);
                        cout << "Loading...\n";
                        set<string> airports;
                        for (Flight flight : m.getRf().getflights()) {
                            if (flight.getairline() == airline) {
                                airports.insert(flight.getsource());
                                airports.insert(flight.gettarget());
                            }
                        }
                        cout << airline <<" covers " << airports.size() << " airports";
                    }
                }
                if (option21 == 6) {
                    goto start;
                }
                break;
            }
            default:
                cout << "Invalid Option. Try Again.\n";
        }
    } while (option != 3);
}

void Menu::flightOptions() {
    const char* boldOn = "\033[1m";
    const char* boldOff = "\033[0m";
    int count = 0, maxStops, filterOpt;
    string codeDeparture, codeArrival, filter, test, airlineCodes;
    list<Airline> airlines;
    vector<vector<Airport>> flights;
    Graph graph = m.getRf().getgraph();
    char testf = 'E';
    cout << "\n--------- Travel Setup ---------\n";
    cout << boldOn << "Info: " << boldOff;
    cout << "Write the name or code of the airport, the name of a city or the coordinates.\n";
    while (count != 3) {
        getline(cin, test);
        if (count == 0) {
            cout << boldOn << "Departure from: " << boldOff;
        }
        if (count == 1) {
            codeDeparture = test;
            cout << boldOn << "Arrival to: " << boldOff;
        }
        if (count == 2) {
            codeArrival = test;
        }
        count++;
    }
    if (isdigit(codeDeparture[0])) {
        vector<double> coord = convertCoordinates(codeDeparture);
        Vertex* vertexDeparture = m.nearestAirport(coord[0], coord[1]);
        codeDeparture = vertexDeparture->getInfo().getcode();
    }
    if (isdigit(codeArrival[0])) {
        vector<double> coord = convertCoordinates(codeArrival);
        Vertex* vertexDeparture = m.nearestAirport(coord[0], coord[1]);
        codeArrival = vertexDeparture->getInfo().getcode();
    }
    cout << "Do you want to use any filter(Y/N)?: ";
    cin >> filter;
    if (filter == "Y") {
        cout << boldOn << "1." << boldOff << " Filter one or more airlines\n";
        cout << boldOn << "2." << boldOff << " Minimize airlines\n";
        cout << boldOn << "3." << boldOff << " Maximize airlines\n";
        cout << "Choose an option: ";
        cin >> filterOpt;
        if (filterOpt == 1) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Write the airline(s) code separated by a space: ";
            getline(std::cin, airlineCodes);
            graph = m.airline_preferences(convertAirlines(airlineCodes));
        }
        else {cout << "Loading...\n";}
    }
    flights = m.bestFlights(codeDeparture,codeArrival, graph);
    cout << boldOn << "======== Best Flight Options ========" << boldOff << '\n';
    for (vector<Airport> airs : flights) {
        maxStops = airs.size();
        if (filter == "Y")
        {
            if (filterOpt == 2 || filterOpt == 3)
                airlines = m.fullTripAirlines(airs, filterOpt == 2);
        }
        for (int b = 0; b < airs.size(); b++) {
            if (b != airs.size() - 1) {
                if (filter == "Y" && (filterOpt == 2 || filterOpt == 3))
                    cout << airs[b].getcode() + " - " + airs[b].getcity()
                         << boldOn << " --> " + m.minMaxAirline(airs[b], airs[b + 1], airlines).getcode()
                         << " --> " << boldOff;
                else {
                    cout << airs[b].getcode() + " - " + airs[b].getcity()
                         << boldOn << " -->";
                    for (Airline airline : m.tripAirlines(airs[b], airs[b + 1], graph)) {
                        cout << " " + airline.getcode();
                    }
                    cout << " --> " << boldOff;
                }
            }
            else cout << airs[b].getcode() + " - " + airs[b].getcity() + '\n';
        }
    }
    if (flights.size() > 0) cout << "Stops: " << maxStops - 2 << '\n';
    else cout << "There are not any available flight within your filters.\n";
}

vector<double> Menu::convertCoordinates(string coordinates) {
    vector<double> c;
    stringstream coord(coordinates);
    string str;
    while (getline(coord, str, ' ')) c.push_back(stod(str));
    return c;
}

vector<string> Menu::convertAirlines(std::string airlines) {
    vector<string> a;
    stringstream air(airlines);
    string str;
    while (getline(air, str, ' ')) {
        a.push_back(str);
    }
    return a;
}
