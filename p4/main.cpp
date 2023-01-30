#include <iostream>
#include <vector>
#include "doprava.hpp"
#include <string>
#include <iomanip>

using namespace std;
    DepartDB ddb;

void print_timetable(Network net, string stopName){
  int nHours;
  int nMinutes;
  int nSeconds;
  vector<int> linesOnStop;

  for (auto i = 0; i < net.nlines(); i++) {
    for (auto l = 0; l < net(i).stops.size(); l++) {
      if(net(i).stops.at(l) == stopName) linesOnStop.push_back(i);
    }
  }

vector<StDepart> departsFromStop = ddb.getStDeparts(stopName);
  string lastStop;
  string firstStop;
  for (auto i = 0; i < linesOnStop.size(); i++) {
    /* code */
  lastStop = net(linesOnStop.at(i)).stops.back();
  firstStop = net(linesOnStop.at(i)).stops.at(0);
  //std::cout << "test: " << departsFromStop.size() << '\n';



  std::cout << "+------------------------------------------------------------------------------+" << '\n';
  std::cout << "| " << stopName << string(69-stopName.length(), ' ') << "Line: " << linesOnStop.at(i)  << " |" << '\n';
  std::cout << "+--------------------------------------++--------------------------------------+" << '\n';
  std::cout << "| To: " << lastStop << string(33-lastStop.length(), ' ') << "|| To: " << firstStop << string(33-firstStop.length(), ' ') << "|"<<'\n';
  std::cout << "+--------------------------------------++--------------------------------------+" << '\n';
  for (auto l = 00; l < 24; l++) {
  nHours = 0;
  nMinutes = 0;
  nSeconds = 0;
  int tempIdx = 0;
  std::cout << "| ";
  if(l < 10) std::cout << "0";
  std::cout << l << " | ";
  for (auto k = 0; k < departsFromStop.size(); k++) {
    if(departsFromStop[k].ln == linesOnStop.at(i)){
      departsFromStop[k].ti.gett(nHours, nMinutes, nSeconds);
      if(departsFromStop[k].dir == Lndir::fwd && nHours == l){
      if(nMinutes < 10) std::cout << "0";
      std::cout << nMinutes << " ";
      tempIdx++;
    }
  }
}

    std::cout << string(32-3*tempIdx, ' ') << "|| ";
    tempIdx = 0;
    if(l < 10) std::cout << "0";
    std::cout << l << " | ";
    for (auto k = 0; k < departsFromStop.size(); k++) {
      if(departsFromStop[k].ln == linesOnStop.at(i)){
        departsFromStop[k].ti.gett(nHours, nMinutes, nSeconds);
        if(departsFromStop[k].dir == Lndir::bwd && nHours == l){
          if(nMinutes < 10) std::cout << "0";
        std::cout << nMinutes << " ";
        tempIdx++;
      }
    }
  }
  cout <<  string(32-3*tempIdx, ' ') << "|" << '\n';
  }
  std::cout << "+--------------------------------------++--------------------------------------+" << '\n';

  }



}



int main(int argc, char** argv) {

    // Load files:
    DriverList dl;
    dl.loadFromFile("driver_list.txt");

    Network net;
    net.loadFromFile("network.txt");


    ddb.loadFromFile("departures.txt");

    // variables for argument decoding
    string flag_in;
    list<string> stop_in;

    if (argc > 1)
        flag_in = string(argv[1]);
    else
    {
        cerr << "Missing argument. Terminating." << endl;
        return 1;
    }

    if ((!flag_in.compare("--schedule")))
    {
            if (argc > 2)
            for(int i = 2; i<argc; i++)
            {
                string temp = argv[i];
                replace(temp.begin(), temp.end(), '_', ' ');
                stop_in.push_back(temp);
            }
        else
        {
            cerr << "Missing stop name. Terminating." << endl;
            return 2;
        }

        /* here should start the code for printing timetables*/
        /* stop_in contains names of stops, for which the timetable is to be printed. */

        // This is an example, how it can be done using lambda-function

        for_each(stop_in.begin(), stop_in.end(), [&] (string stop_name) {print_timetable(net,stop_name);} );
        // This is an example, how it can be done using for-loop
        //for( auto iter = stop_in.begin(); iter != stop_in.end(); iter++) print_timetable(net,*iter);

        /* here should end the code for printing timetables*/
    }
    else if ((!flag_in.compare("--line-routing")))
    {

        /* here should start the code for printing line routes without stats*/



        /* here should end the code for printing line routes without stats*/
    }
    else if ((!flag_in.compare("--driver-delays")))
    {

        /* here should start the code for delay statistics for drivers */




        /* here should end the code for delay statistics for drivers */
    }
    else if ((!flag_in.compare("--driver-duty")))
    {

        /* here should start the code for duty statistics for drivers */



        /* here should end the code for duty statistics for drivers */
    }
    else if ((!flag_in.compare("--line-stats")))
    {

        /* here should end the code for printing line delay statistics*/



        /* here should end the code for printing line delay statistics*/
    }
    else
    {
        cout << "Flag not recognized, terminating." << endl;
    }

    return 0;
}
