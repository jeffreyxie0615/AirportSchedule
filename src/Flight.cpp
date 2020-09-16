#include "../include/Flight.h"
#include "../include/Plane.h"
#include "../include/Crew.h"

#include <iostream>
Flight::Flight(string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
               string endTime, string startAirport, string endAirport, string status,
               int numPassenger, int numPilots, int numCabinCrew)
{
    //ctor
    this->numTail = numTail;
    this->pilots = pilots;
    this->cabinCrew = cabinCrew;
    this->startTime = startTime;
    this->endTime = endTime;
    this->startAirport = startAirport;
    this->endAirport = endAirport;
    this->status = status;
    this->numPassenger = numPassenger;
    this->numPilots = numPilots;
    this->numCabinCrew = numCabinCrew;
}

Flight::~Flight()
{
    //dtor
}
string Flight::getNumTail()
{
    return numTail;
}
string Flight::getPilots()
{
    string result = "";
    for (unsigned int i = 0; i < pilots.size(); i++)
    {
        result += (pilots[i] + "|");
    }
    result.pop_back();
    return result;
}
string Flight::getCabinCrew()
{
    string result = "";
    for (unsigned int i = 0; i < cabinCrew.size(); i++)
    {
        result += (cabinCrew[i] + "|");
    }
    result.pop_back();
    return result;
}
string Flight::getStartTime()
{
    return startTime;
}
string Flight::getEndTime()
{
    return endAirport;
}
string Flight::getStartAirport()
{
    return startAirport;
}
string Flight::getEndAirport()
{
    return endAirport;
}
string Flight::getStatus()
{
    return status;
}
int Flight::getNumPassengers()
{
    return numPassenger;
}
int Flight::getNumPilots()
{
    return numPilots;
}
int Flight::getNumCabinCrew()
{
    return numCabinCrew;
}
void Flight::setNumTail(string numTail)
{
    this->numTail = numTail;
}
void Flight::setPilots(vector<string> pilots)
{
    this->pilots = pilots;
}
void Flight::setCabinCrew(vector<string> cabinCrew)
{
    this->cabinCrew = cabinCrew;
}
void Flight::setStartTime(string startTime)
{
    this->startTime = startTime;
}
void Flight::setEndTime(string endTime)
{
    this->endTime = endTime;
}
void Flight::setStartAirport(string startAirport)
{
    this->startAirport = startAirport;
}
void Flight::setEndAirport(string endAirport)
{
    this->endAirport = endAirport;
}
void Flight::setStatus(string status)
{
    this->status = status;
}
void Flight::setNumPassengers(int numPassenger)
{
    this->numPassenger = numPassenger;
}
void Flight::setNumPilots(int numPilots)
{
    this->numPilots = numPilots;
}
void Flight::setNumCabinCrew(int numCabinCrew)
{
    this->numCabinCrew = numCabinCrew;
}

// Checks if numPassenger is valid, if numPilots and numCabinCrew are both available and enough, if the plane is available, and if the times are
// realistic

void Flight::add(vector<Flight*>& flights, vector<Crew*>& crews, vector<Plane*>& planes, string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
                 string endTime, string startAirport, string endAirport, string status, int numPassenger, int numPilots, int numCabinCrew)
{

    if (checkPreconditions(crews, planes, pilots, cabinCrew, numTail, startTime, endTime, numPassenger, numPilots, numCabinCrew))
    {
        Flight* addFlight = new Flight(numTail, pilots, cabinCrew, startTime, endTime, startAirport, endAirport, status, numPassenger, numPilots, numCabinCrew);
        flights.push_back(addFlight);
    }
}
void Flight::edit(vector<Flight*>& flights, vector<Crew*>& crews, vector<Plane*>& planes, string numTail, vector<string> pilots, vector<string> cabinCrew, string startTime,
                  string endTime, string startAirport, string endAirport, string status, int numPassenger, int numPilots, int numCabinCrew)
{
    if (!checkPreconditions(crews, planes, pilots, cabinCrew, numTail, startTime, endTime, numPassenger, numPilots, numCabinCrew))
    {
        cout<<"Cannot Edit Flight"<<endl;
        return;
    }
    Flight* editFlight = findFlight(flights, numTail, startAirport, endAirport);
    if (numTail != "")
    {
        editFlight->setNumTail(numTail);
    }
    if (startTime != "")
    {
        editFlight->setStartTime(startTime);
    }
    if (endTime != "")
    {
        editFlight->setEndTime(endTime);
    }
    if (startAirport != "")
    {
        editFlight->setStartAirport(startAirport);
    }
    if (endAirport != "")
    {
        editFlight->setEndAirport(endAirport);
    }
    if (status != "")
    {
        editFlight->setStatus(status);
    }
    if (numPassenger != -1)
    {
        editFlight->setNumPassengers(numPassenger);
    }
    if (numPilots != -1)
    {
        editFlight->setNumPilots(numPilots);
    }
    if (numCabinCrew != -1)
    {
        editFlight->setNumCabinCrew(numCabinCrew);
    }
    flights[findPosition(flights, editFlight->getNumTail(), editFlight->getStartTime(), editFlight->getEndTime())] = editFlight;
}
void Flight::deleteFlight(vector<Flight*>& flights, string numTail, string startTime, string endTime)
{
    int index = findPosition(flights, numTail, startTime, endTime);
    if (index == -1)
    {
        cout<<"Could Not Find Plane Of That Description"<<endl;
        return;
    }
    flights.erase(flights.begin() + index);
    cout<<"Flight Successfully Deleted"<<endl;
}
Flight* Flight::findFlight(vector<Flight*>& flights, string numTail, string startAirport, string endAirport)
{
    for (auto itr = flights.begin(); itr != flights.end(); itr++)
    {
        if (((*itr)->getNumTail() == numTail)  && ((*itr)->getStartAirport() == startAirport) && ((*itr)->getEndAirport() == endAirport))
        {
            return *itr;
        }
    }
    return NULL;
}
int Flight::findPosition(vector<Flight*>& flights, string numTail, string startTime, string endTime)
{
    for (unsigned int i = 0; i < flights.size(); i++)
    {
        if (flights[i]->getNumTail() == numTail && flights[i]->getStartTime() == startTime && flights[i]->getEndTime() == endTime)
        {
            return i;
        }
    }
    return -1;
}

bool Plane::isAvailablePlane(vector<Plane*>& planes, string numTail, string startTime, string endTime)
{
    Plane* tempPlane = Plane::find(planes, numTail);
    vector<vector<string>> schedule = tempPlane->getSchedule();
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < schedule.size(); i++)
    {
        long long int schedStart = Plane::convertTime(schedule[i][0]);

        long long int schedEnd = Plane::convertTime(schedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
bool Plane::availablePlanePointer(string startTime, string endTime)
{
    vector<vector<string>> schedule = this->getSchedule();
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < schedule.size(); i++)
    {
        long long int schedStart = Plane::convertTime(schedule[i][0]);
        long long int schedEnd = Plane::convertTime(schedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
bool Crew::isAvailableCrew(vector<Crew*>& crews, string id, string startTime, string endTime, int index)
{
    Crew* tempCrew = Crew::findCrew(crews, id);
    vector<vector<string>> schedule = tempCrew->getSchedule();
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < schedule.size(); i++)
    {
        if (index == i)
        {
            continue;
        }
        long long int schedStart = Plane::convertTime(schedule[i][0]);
        long long int schedEnd = Plane::convertTime(schedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
bool Crew::availableCrewPointer(string startTime, string endTime)
{
    vector<vector<string>> schedule = this->getSchedule();
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < schedule.size(); i++)
    {
        long long int schedStart = Plane::convertTime(schedule[i][0]);
        long long int schedEnd = Plane::convertTime(schedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
//Returns true if we can add the schedule to the current crew
bool Crew::ableToAddSchedule(vector<vector<string>>& currentSchedule, string startTime, string endTime)
{
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < currentSchedule.size(); i++)
    {
        long long int schedStart = Plane::convertTime(currentSchedule[i][0]);
        long long int schedEnd = Plane::convertTime(currentSchedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
bool Plane::ableToAddSchedule(vector<vector<string>>& currentSchedule, string startTime, string endTime)
{
    long long int startInt = Plane::convertTime(startTime);
    long long int endInt = Plane::convertTime(endTime);
    for (unsigned int i = 0; i < currentSchedule.size(); i++)
    {
        long long int schedStart = Plane::convertTime(currentSchedule[i][0]);
        long long int schedEnd = Plane::convertTime(currentSchedule[i][1]);
        if ((startInt >= schedStart && startInt <= schedEnd) || (endInt >= schedStart && endInt <= schedEnd) || (startInt < schedStart && endInt > schedEnd))
        {
            return false;
        }
    }
    return true;
}
// Returns if there are enough seats on the plane
bool Plane::isAvailableSeats(vector<Plane*>& planes, string numTail, int numPassenger)
{
    Plane* tempPlane = Plane::find(planes, numTail);
    if (numPassenger <= tempPlane->getSeatNum())
    {
        return true;
    }
    return false;
}
bool Flight::overEight(string startTime, string endTime)
{
    return Plane::convertTime(endTime) - Plane::convertTime(startTime) >= 28800 ? true : false;
}
bool Flight::validTime(string time)
{
    int year = stoi(time.substr(0, 4));
    int month = stoi(time.substr(8, 2));
    int day = stoi(time.substr(5, 2));
    int hour = stoi(time.substr(11, 2));
    int minute = stoi(time.substr(14, 2));
    vector<int> months {31,28,31,30,31,30,31,31,30,31,30,31};
    // Check Leap Year
    if (year % 4 == 0 && year % 100 != 0)
    {
        months[1] = 29;
    }
    if (month > 12)
    {
        cout<<"The Submission Contains An Invalid Month"<<endl;
        return false;
    }
    if (day > months[month - 1])
    {
        cout<<"There Was An Error In Your Submission. The Input Date Does Not Exist In The Specified Month."<<endl;
        return false;
    }
    if (hour >= 24)
    {
        cout<<"The Submission Contains An Invalid Hour Value"<<endl;
        return false;
    }
    if (minute >= 60)
    {
        cout<<"The Submission Contains An Invalid Minute Value"<<endl;
        return false;
    }
    return true;
}
// Check If The End Time Is Greater Than The Start Time
bool Flight::timeCheck(string startTime, string endTime)
{
    return Plane::convertTime(endTime) - Plane::convertTime(startTime) > 0 ? true : false;
}
bool Flight::pilotCheck(int numPilots, bool overEight)
{
    int minPilots = 4;
    if (overEight)
    {
        minPilots *= 2;
    }
    return numPilots >= minPilots ? true : false;
}
bool Flight::cabinCheck(int numCabinCrew, bool overEight)
{
    int minCabinCrew = overEight ? 4 : 2;
    return numCabinCrew >= minCabinCrew;
}

bool Flight::checkPreconditions(vector<Crew*>& crews, vector<Plane*>& planes, vector<string>& pilots, vector<string>& cabinCrew, string numTail, string startTime, string endTime, int numPassenger, int numPilots, int numCabinCrew)
{
    if (!timeCheck(startTime, endTime))
    {
        cout<<"The Specified Start And End Times Are Not Realistic"<<endl;
        return false;
    }
    bool crewCount = true;
    bool pilotBool1 = true;
    bool crewBool1 = true;
    if (overEight(startTime, endTime))
    {
        crewCount = pilotCheck(numPilots, true) && cabinCheck(numCabinCrew, true);
    }else
    {
        crewCount = pilotCheck(numPilots, false) && cabinCheck(numCabinCrew, false);
    }
    if (!crewCount)
    {
        cout<<"There Are Not Enough Crew Members Scheduled For This Flight"<<endl;
        return false;
    }
    for (unsigned int i = 0; i < pilots.size(); i++)
    {
        if (!Crew::isAvailableCrew(crews, pilots[i], startTime, endTime, -1))
        {
            pilotBool1 = false;
            cout<<"One Of The Selected Pilots Is Not Available In This Time Frame"<<endl;
            return false;
        }
    }
    for (unsigned int i = 0; i < cabinCrew.size(); i++)
    {
        if (!Crew::isAvailableCrew(crews, cabinCrew[i], startTime, endTime, -1))
        {
            crewBool1 = false;
            cout<<"One Of The Selected Cabin Crew Members Is Not Available In This Time Frame"<<endl;
            return false;
        }
    }
    if (Plane::isAvailablePlane(planes, numTail, startTime, endTime) && Plane::isAvailableSeats(planes, numTail, numPassenger) && crewCount && pilotBool1 && crewBool1)
    {
        cout<<"Passed All Tests"<<endl;
        return true;
    }
    cout<<"Flight Did Not Pass All Preconditions"<<endl;
    return false;
}
