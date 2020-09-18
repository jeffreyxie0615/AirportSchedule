#include "../include/Crew.h"
#include <iostream>
#include <unistd.h>
using namespace std;
Crew::Crew(string name, string id, string type, vector<vector<string>> schedule)
{
    //ctor
        this->name = name;
        this->id = id;
        this->type = type;
        this->schedule = schedule;
}

Crew::~Crew()
{
    //dtor
}
string Crew::getName()
{
    return name;
}
string Crew::getID()
{
    return id;
}
string Crew::getType()
{
    return type;
}
vector<vector<string>>& Crew::getSchedule()
{
    return schedule;
}
vector<string>& Crew::getPlaneSchedule()
{
    return planeSchedule;
}
void Crew::setName(string name)
{
    this->name = name;
}
void Crew::setID(string id)
{
    this->id = id;
}
void Crew::setType(string type)
{
    this->type = type;
}
void Crew::setSchedule(vector<vector<string>> schedule)
{
    this->schedule = schedule;
}
void Crew::setPlaneSchedule(vector<string> planeSchedule)
{
    this->planeSchedule = planeSchedule;
}
bool Crew::isPilot()
{
    return type.compare("Pilot") == 0 ? true : false;
}
void Crew::add(vector<Crew*>& crews, string name, string id, string type, vector<vector<string>> schedule)
{
    Crew* tempCrew = new Crew(name, id, type, schedule);
    crews.push_back(tempCrew);
}
void Crew::edit(vector<Crew*>& crews, string name, string id, string type, vector<vector<string>> schedule)
{
    Crew* editCrew = findCrew(crews, id);
    if (name != "")
    {
        editCrew->setName(name);
    }
    if (id != "")
    {
        editCrew->setID(id);
    }
    if (type != "")
    {
        editCrew->setType(type);
    }

    editCrew->setSchedule(schedule);

    crews[Crew::findCrewPosition(crews, id)] = editCrew;
}
void Crew::deleteCrew(vector<Crew*>& crews, string id)
{
    int pos = findCrewPosition(crews, id);
    crews.erase(crews.begin() + pos);
}
Crew* Crew::findCrew(vector<Crew*>& crews, string OGid)
{
    for (auto itr = crews.begin(); itr != crews.end(); itr++)
    {
        if ((*itr)->id == OGid)
        {
            return *itr;
        }
    }
    return NULL;
}
int Crew::findCrewPosition(vector<Crew*>& crews, string OGid)
{
    for (unsigned int i = 0; i < crews.size(); i++)
    {
        if (crews[i]->id == OGid)
        {
            return i;
        }
    }
    return -1;
}

void Crew::displayCrew(string filler)
{
    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"The Name Of The " + filler + " Is: ";
    cout<<name<<endl;
    cout<<"The ID Of The " + filler + " Is: ";
    cout<<id<<endl;
    cout<<"The " + filler + " Has Assignments From: "<<endl;
    for (int i = 0; i < schedule.size(); i++)
    {
        cout<<"{";
        cout<<schedule[i][0];
        cout<<", ";
        cout<<schedule[i][1];
        cout<<"}"<<endl;
    }
}
void Crew::displayAll()
{

    sleep(0);
    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"The Name Of The Crew Member Is: ";
    cout<<name<<endl;
    cout<<"The ID Of The Crew Member Is: ";
    cout<<id<<endl;
    cout<<"The Crew Member Has Assignments From: "<<endl;
    for (int i = 0; i < schedule.size(); i++)
    {
        cout<<"{";
        cout<<schedule[i][0];
        cout<<", ";
        cout<<schedule[i][1];
        cout<<"}"<<endl;
    }

}
