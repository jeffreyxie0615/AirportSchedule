#include "../include/Plane.h"
#include <fstream>
#include <iostream>
using namespace std;


Plane::Plane(std::string makeCopy,std::string modelCopy,std::string numTailCopy,int numSeatsCopy,int rangeCopy,int minCrewCopy, vector<vector<string>> scheduleCopy)
{
    make = makeCopy;
    model = modelCopy;
    numTail = numTailCopy;
    numSeats = numSeatsCopy;
    range = rangeCopy;
    minCrew = minCrewCopy;
    schedule = scheduleCopy;
}
string Plane::getMake()
{
    return make;
}
string Plane::getModel()
{
    return model;
}
string Plane::getTail()
{
    return numTail;
}
int Plane::getSeatNum()
{
    return numSeats;
}
int Plane::getRange()
{
    return range;
}
int Plane::getMinCrew()
{
    return minCrew;
}
vector<vector<string>>& Plane::getSchedule()
{
    return schedule;
}
void Plane::setMake(string makeCopy)
{
    make = makeCopy;
}
void Plane::setModel(string modelCopy)
{
    model = modelCopy;
}
void Plane::setTail(string numTailCopy)
{
    numTail = numTailCopy;
}
void Plane::setSeatNum(int numSeatCopy)
{
    numSeats = numSeatCopy;
}
void Plane::setRange(int rangeCopy)
{
    range = rangeCopy;
}
void Plane::setMinCrew(int minCrewCopy)
{
    minCrew = minCrewCopy;
}
void Plane::setSchedule(vector<vector<string>> schedule)
{
    this->schedule = schedule;
}
void Plane::add(vector<Plane*>& planes, std::string make,std::string model, std::string numTail,
                int numSeats, int range, int minCrew, vector<vector<string>> schedule)
{
    Plane* temp = new Plane(make, model, numTail, numSeats, range, minCrew, schedule);
    planes.push_back(temp);
}
void Plane::edit(vector<Plane*> planes, string numTail, string model, string make, int numSeats, int range, int minCrew)
{
    Plane* editPlane = find(planes, numTail);
    if (make != ""){
        editPlane->make = make;
    }
    if(model != ""){
        editPlane->model = model;
    }
    if(numTail != ""){
        editPlane->numTail = numTail;
    }
    if (numSeats != -1){
        editPlane->numSeats = numSeats;
    }
    if (range != -1){
        editPlane->range = range;
    }
    if (minCrew != -1){
        editPlane->minCrew = minCrew;
    }
    planes[findPosition(planes, numTail)] = editPlane;


}
void Plane::deletePlane(vector<Plane*>& planes, std::string numTail)
{
    int pos = findPosition(planes, numTail);
    planes.erase(planes.begin() + pos);
}
Plane* Plane::find(vector<Plane*>& planes, std::string numTailCopy)
{
    for (auto itr = planes.begin(); itr != planes.end(); itr++){
        if ((*itr)->numTail == numTailCopy){
            return *itr;
        }
    }
    return NULL;
}
// Returns the position of a plane
int Plane::findPosition(vector<Plane*> planes, std::string numTailCopy)
{
    for (unsigned int i = 0; i < planes.size(); i++)
    {
        if (planes[i]->getTail() == numTailCopy)
        {
            return i;
        }
    }
    return -1;
}
// Prints the data for all the planes
int Plane::printAll(std::vector<Plane*>& planes)
{
    for (unsigned int i = 0;i < planes.size(); i++){
        cout<<"------------------------------"<<endl;
        cout<<"The Tail Number of the Plane is: "<<planes[i]->getTail()<<endl;
        cout<<"The Make of the Plane is: "<<planes[i]->getMake()<<endl;
        cout<<"The Model of the Plane is: "<<planes[i]->getModel()<<endl;
        cout<<"The Number of Seats on the Plane is: "<<planes[i]->getSeatNum()<<endl;
        cout<<"The Range of the Plane is: "<<planes[i]->getRange()<<endl;
        cout<<"The Minimum Crew Number of the Plane is: "<<planes[i]->getMinCrew()<<endl;
    }
    cout<<"------------------------------"<<endl;
}
// Prints the data for a specific plane
void Plane::printSpec(vector<Plane*>& planes, string numTail)
{
    Plane* temp = Plane::find(planes, numTail);
    cout<<"------------------------------"<<endl;
    cout<<"The Tail Number of the Plane is: "<<temp->getTail()<<endl;
    cout<<"The Make of the Plane is: "<<temp->getMake()<<endl;
    cout<<"The Model of the Plane is: "<<temp->getModel()<<endl;
    cout<<"The Number of Seats on the Plane is: "<<temp->getSeatNum()<<endl;
    cout<<"The Range of the Plane is: "<<temp->getRange()<<endl;
    cout<<"The Minimum Crew Number of the Plane is: "<<temp->getMinCrew()<<endl;
    cout<<"------------------------------"<<endl;
}
long long int Plane::convertTime(string time)
{
    long long int res = 0;
    string year = time.substr(0, 4);
    string month = time.substr(8, 2);
    string day = time.substr(5, 2);
    string hour = time.substr(11, 2);
    string minute = time.substr(14, 2);
    res += (stoi(year)*31556952);
    res += (stoi(month)*2592000);
    res += (stoi(day) * 86400);
    res += (stoi(hour) * 3600);
    res += (stoi(minute) * 60);
    return res;
}
void Plane::display()
{
    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"The Tail Number Of The Plane Is: ";
    cout<<numTail<<endl;
    cout<<"The Make Of The Plane Is: ";
    cout<<make<<endl;
    cout<<"The Model Of The Plane Is: ";
    cout<<model<<endl;
    cout<<"The Number Of Seats On The Plane Is: ";
    cout<<numSeats<<endl;
    cout<<"The Range Of The Plane Is: ";
    cout<<range<<endl;
    cout<<"The Minimum Number Of Cabin Crew For The Plane Is: ";
    cout<<minCrew<<endl;
    cout<<"The Plane Has Assignments From: "<<endl;
    for (int i = 0; i < schedule.size(); i++)
    {
        cout<<"{";
        cout<<schedule[i][0];
        cout<<", ";
        cout<<schedule[i][1];
        cout<<"}"<<endl;
    }
}
Plane::~Plane()
{
    //dtor
}
