#ifndef FLIGHT_H
#define FLIGHT_H
#include <vector>
#include <string>
#include "Plane.h"
#include "Crew.h"
using namespace std;
class Flight
{
    public:
        Flight();
        Flight(string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
               string endTime, string startAirport, string endAirport, string status,
               int numPassenger, int numPilots, int numCabinCrew);
        virtual ~Flight();

        string getNumTail();
        string getPilots();
        string getCabinCrew();
        string getStartTime();
        string getEndTime();
        string getStartAirport();
        string getEndAirport();
        string getStatus();
        int getNumPassengers();
        int getNumPilots();
        int getNumCabinCrew();

        void setNumTail(string numTail);
        void setPilots(vector<string> pilots);
        void setCabinCrew(vector<string> cabinCrew);
        void setStartTime(string startTime);
        void setEndTime(string endTime);
        void setStartAirport(string startAirport);
        void setEndAirport(string endAirport);
        void setStatus(string status);
        void setNumPassengers(int numPassenger);
        void setNumPilots(int numPilot);
        void setNumCabinCrew(int numCabinCrew);

        static Flight* findFlight(vector<Flight*>& flights, string numTail, string startAirport, string endAirport);
        static int findPosition(vector<Flight*>& flights, string numTail, string startAirport, string endAirport);
        static void add(vector<Flight*>& flights, vector<Crew*>& crews, vector<Plane*>& planes, string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
                        string endTime, string startAirport, string endAirport, string status, int numPassenger, int numPilots, int numCabinCrew);
        static void edit(vector<Flight*>& flights, vector<Crew*>& crews, vector<Plane*>& planes, string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
                        string endTime, string startAirport, string endAirport, string status, int numPassenger, int numPilots, int numCabinCrew);
        static void deleteFlight(vector<Flight*>& flights, string numTail, string startTime, string endTime);
        static bool overEight(string startTime, string endTime);
        static bool isAvailablePlane(vector<Plane*>& planes, string numTail, string startTime, string endTime);
        static bool timeCheck(string startTime, string endTime);
        static bool validTime(string time);
        static bool pilotCheck(int numPilots, bool overEight);
        static bool cabinCheck(int numCabinCrew, bool overEight);
        static bool checkPreconditions(vector<Crew*>& crews, vector<Plane*>& planes, vector<string>& pilots, vector<string>& cabinCrew, string numTail, string startTime, string endTime, int numPassenger, int numPilots, int numCabinCrew);
    protected:

    private:
        string numTail;
        vector<string> pilots;
        vector<string> cabinCrew;
        string startTime;
        string endTime;
        string startAirport;
        string endAirport;
        string status;
        int numPassenger;
        int numPilots;
        int numCabinCrew;
};

#endif // FLIGHT_H
