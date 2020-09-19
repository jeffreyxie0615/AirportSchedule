#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "include/Plane.h"
#include "include/Crew.h"
#include "include/Flight.h"

using namespace std;
    // read in Plane
    ostream& operator << (ostream& out, Plane* obj){
        out<<obj->getTail()<<","<<obj->getModel()<<","<<obj->getMake()<<","<<obj->getSeatNum()<<","<<obj->getRange()<<","
        <<obj->getMinCrew();
        vector<vector<string>> schedule = obj->getSchedule();
        for (unsigned int i = 0; i < schedule.size(); i++)
        {
            out<<",";
            string res = schedule[i][0]+schedule[i][1];
            out<<res;
        }
        out<<"\n";
        return out;
    }
    // read in Crew
    ostream& operator << (ostream& out, Crew* obj)
    {
        out<<obj->getName()<<","<<obj->getID()<<","<<obj->getType();
        vector<vector<string>> schedule = obj->getSchedule();
        vector<string> planeSchedule = obj->getPlaneSchedule();
        for (unsigned int i = 0; i < schedule.size(); i++)
        {
            out<<",";
            string res = schedule[i][0]+schedule[i][1];
            out<<res;
        }

        for (unsigned int i = 0; i < planeSchedule.size(); i++)
        {
            out<<","<<planeSchedule[i];
        }
        out<<"\n";
        return out;
    }
    ostream& operator << (ostream& out, Flight* obj)
    {
        out<<obj->getNumTail()<<","<<obj->getPilots()<<","<<obj->getCabinCrew()<<","<<obj->getStartTime()<<","<<obj->getEndTime()
        <<","<<obj->getStartAirport()<<","<<obj->getEndAirport()<<","<<obj->getStatus()<<","<<obj->getNumPassengers()<<","<<
        obj->getNumPilots()<<","<<obj->getNumCabinCrew()<<"\n";
        return out;
    }
// Overloaded operator to read from file
istream& operator >> (istream& in, Flight* obj)
{
    string tempString;
    in>>tempString;
    stringstream ss(tempString);
    string x;
    int i = 0;
    vector<string> pilots;
    vector<string> cabinCrew;
    while (getline(ss,x,','))
    {

        if (i == 0){
            obj->setNumTail(x);
        }else if (i == 1)
        {
            string y;
            stringstream ss(x);
            while (getline(ss,y,'|'))
            {
                pilots.push_back(y);
            }
        }else if (i == 2)
        {
            string y;
            stringstream ss(x);
            while (getline(ss,y,'|'))
            {
                cabinCrew.push_back(y);
            }
        }else if (i == 3)
        {
            obj->setStartTime(x);
        }else if (i == 4)
        {
            obj->setEndTime(x);
        }else if (i == 5)
        {
            obj->setStartAirport(x);
        }else if (i == 6)
        {
            obj->setEndAirport(x);
        }else if (i == 7)
        {
            obj->setStatus(x);
        }else if (i == 8)
        {
            obj->setNumPassengers(stoi(x));
        }else if (i == 9)
        {
            obj->setNumPilots(stoi(x));
        }else if (i == 10)
        {
            obj->setNumCabinCrew(stoi(x));
        }
        i++;
    }
    obj->setPilots(pilots);
    obj->setCabinCrew(cabinCrew);
    return in;
}
istream& operator >> (istream& in, Crew* obj)
{
    string tempString;
    in>>tempString;
    stringstream ss(tempString);
    string x;
    int i = 0;
    vector<vector<string>> filler;
    vector<string> planeSchedule;
    while (getline(ss, x, ','))
    {
        if (i == 0)
        {
            obj->setName(x);
        }else if (i == 1)
        {
            obj->setID(x);
        }else if (i == 2)
        {
            obj->setType(x);
        }else if (i == 3)
        {
            string start1 = x.substr(0,16);
            string end1 = x.substr(16,16);
            vector<string> temp = {start1,end1};
            filler.push_back(temp);
        }else if (i == 4)
        {
            planeSchedule.push_back(x);
            continue;
        }
        i++;
    }
    obj->setSchedule(filler);
    obj->setPlaneSchedule(planeSchedule);
    return in;
}
istream& operator >> (istream& in, Plane* obj){
    string tempString;
    in>>tempString;
    stringstream ss (tempString);
    string x;
    int i = 0;
    vector<vector<string>> schedule;
    while (getline(ss, x, ','))
    {

        if (i==0){
            obj->setTail(x);
        }else if(i==1)
        {
            obj->setModel(x);
        }else if(i==2)
        {
            obj->setMake(x);
        }else if(i==3)
        {
            obj->setSeatNum(stoi(x));
        }else if(i==4)
        {
            obj->setRange(stoi(x));
        }else if(i==5)
        {
            obj->setMinCrew(stoi(x));
        }else if (i==6)
        {
            string start1 =x.substr(0,16);
            string end1 = x.substr(16,16);
            vector<string> filler {start1,end1};
            schedule.push_back(filler);
            continue;
        }

        i++;
    }
    obj->setSchedule(schedule);
    return in;
    }
    string enterSchedule(bool departure)
    {
        string form = departure ? "Departure" : "Arrival";
        string temp;
        // Enter In Start Time
        while (true)
        {
            cout<<"~~Please Enter In A " + form + " Flight Time For The Flight. Enter It In The Format Of 'year-month-date-hour-minute' (xxxx/xx/xx/xx/xx): "<<endl;
            cin>>temp;
            if (temp == "Exit")
            {
                return "Failed";
            }
            if (temp == ".")
            {
                return ".";
            }
            bool valid = true;
            for (int i = 0; i < 16; i++)
            {
                if (i == 4 || i == 7 || i == 10 || i == 13)
                {
                    if (temp[i] != '/')
                    {
                        valid = false;
                        break;
                    }
                }else
                {
                    if (!isdigit(temp[i]))
                    {
                        valid = false;
                        break;
                    }
                }
            }
            if (!valid || temp.size() != 16)
            {
                cout<<"The Input Is Not Formatted Properly. Try Again!"<<endl;
                continue;
            }
            if (!Flight::validTime(temp))
            {
                cout<<"Restarting Submission..."<<endl;
                continue;
            }
            break;
        }
        return temp;
    }

string enterAllNum(int length)
{
    string temp;
    while (true)
    {
        cin>>temp;
        bool valid = true;
        if (temp == "Exit")
        {
            return "Failed";
        }
        if (temp == "Done")
        {
            return "Done";
        }
        if (temp == ".")
        {
            return ".";
        }
        for (int i = 0; i < length; i++)
        {
            if (!isdigit(temp[i]))
            {
                valid = false;
                break;
            }
        }
        if ((length != -1 && (signed)temp.size() != length) || !valid)
        {
            cout<<"~~There Was An Error In Your Entry. Try Again!"<<endl;
            continue;
        }
        break;
    }
    return temp;
}
string enterAirport()
{
    string temp;
    while (true)
    {
        cin>>temp;
        if (temp == "Exit")
        {
            cout<<"Successfully Exited Entry"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
            cout<<"~~What Do You Want To Do Next?"<<endl;
            cout<<"~~Press '1' For A List Of Commands"<<endl;
            return "Failed";
        }
        bool valid = true;
        for (unsigned int i = 0; i < temp.size(); i++)
        {
            if (!isupper(temp[i]))
            {
                valid = false;
                break;
            }
        }
        if (temp.size() != 3 || !valid)
        {
            cout<<"The Input Is Not Formatted Properly. Try Again!"<<endl;
            valid = true;
            continue;
        }
        break;
    }
    return temp;
}
string enterNoSpace()
{
    string temp;
    while (true)
    {
        std::getline(std::cin >> std::ws, temp);

        if (temp == ".")
        {
            return ".";
        }
        if (temp == "Exit")
        {
            return "Failed";
        }


        if (temp.find(' ') != string::npos)
        {
            cout<<"Do Not Add Any Spaces To Your Input. Please Try Again!"<<endl;
            continue;
        }
        break;
    }
    cout<<"here"<<endl;
    return temp;
}
void printExit()
{
    cout<<"Successfully Exited Entry"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
    cout<<"~~What Do You Want To Do Next?"<<endl;
    cout<<"~~Press '1' For A List Of Commands"<<endl;
}
int main()
{

    vector<Plane*>planes={};
    vector<Crew*>crews = {};
    vector<Flight*> flights = {};

    ifstream reader ("database.txt");

    Plane* tempPlane = new Plane("","","",0,0,0, {{}});
    Crew* tempCrew = new Crew("","","", {{}});
    Flight* tempFlight = new Flight("",{},{},"","","","","",0,0,0);
    int index = 0;
    string filler;
    vector<vector<string>> filler2DVector;
    vector<string> fillerVector;
    bool loopExit = false;
    // Reads from database
    while (index < 3)
    {

        if (index == 0)
        {

            while (reader>>tempPlane)
            {
                if ((tempPlane->getModel()).compare("~") == 0)
                {
                    index++;
                    break;
                }
                planes.push_back(tempPlane);
                tempPlane = new Plane("","","",0,0,0, {});

            }
        }else if (index == 1)
        {
            while (reader>>tempCrew)
            {
                if ((tempCrew->getName()).compare("~") == 0)
                {
                    index++;
                    break;
                }
                crews.push_back(tempCrew);
                tempCrew = new Crew("","","", filler2DVector);
            }
        }else if (index == 2)
        {

            while (reader>>tempFlight)
            {

                if ((tempFlight->getNumTail()).compare("~") == 0)
                {
                    index++;
                    break;
                }
                flights.push_back(tempFlight);
                tempFlight = new Flight("",fillerVector,fillerVector,"","","","","",0,0,0);
            }

        }
    }
    reader.close();
    cout<<"Welcome To The Airport Menu"<<endl;
    cout<<"~~Press '1' For A List Of Commands"<<endl;
    bool portOn = true;
    int choice;
    while (portOn)
    {
        cin>>choice;
        switch (choice)
        {
            case (0):
            {
                cout<<"---------------------------------------------------"<<endl;
                cout<<"Exiting The Program..."<<endl;
                portOn = false;
            }
            break;
            case (1):
            {
                cout<<"---------------------------------------------------"<<endl;
                cout<<"~~Press '0' To Exit The Program And Make All Updates Permanent"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;
                cout<<"~~Press '2' To Add A New Crew Member"<<endl;
                cout<<"~~Press '3' To Add A New Plane"<<endl;
                cout<<"~~Press '4' To Add A New Flight"<<endl;
                cout<<"~~Press '5' To Edit An Existing Crew Member"<<endl;
            }
            break;
            // Add New Crew Member
            case (2):
            {
                string name;
                string id;
                string type;
                string startTime;
                string endTime;
                string make;
                vector<string> filler (2,"");
                vector<vector<string>> schedule;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                cout<<"~~Please Enter A Name For The Crew Member: "<<endl;
                // Enter In Crew Name
                name = enterNoSpace();
                if (name == "Failed")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                cout<<"~~Please Enter A 6 Digit ID For The Crew Member: "<<endl;
                // Enter In Crew ID
                //Enter In ID Of Crew Member
                while (true)
                {
                    id = enterAllNum(6);
                    if (id == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (id == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (Crew::findCrew(crews, id) != NULL)
                    {
                        cout<<"There Already Is A Crew Member With That ID. Try Entering In A Different ID!"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                // Enter In Type Of Crew Member
                cout<<"~~Please Enter The Type Of Crew Member (Pilot Or Cabin) " + name + " Is: "<<endl;
                while (true)
                {
                    cin>>type;
                    if (type == "Exit")
                    {
                        loopExit = true;
                        break;
                    }
                    if (type != "Pilot" && type != "Cabin")
                    {
                        cout<<"There Was An Error In Your Entry"<<endl;
                        cout<<"~~Please Enter The Type Of Crew Member (Pilot Or Cabin) " + name + " Is: "<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                // Enter In Predetermined Schedule
                while (true)
                {
                    cout<<"~~Do You Want To Add A Departure And Arrival Flight Schedule For The Crew Member? ('Yes' Or 'No')"<<endl;
                    string temp;
                    cin>>temp;
                    if (temp == "Exit")
                    {
                        loopExit = true;
                        break;
                    }
                    if (temp != "Yes")
                    {
                        break;
                    }
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (!Flight::validTime(startTime))
                    {
                        continue;
                    }
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (!Flight::validTime(endTime))
                    {
                        continue;
                    }
                    if (!Flight::timeCheck(startTime,endTime))
                    {
                        cout<<"The Arrival Time Must Be Later Than The Departure Time"<<endl;
                        startTime = "";
                        endTime = "";
                        continue;
                    }

                    if (!Crew::ableToAddSchedule(schedule, startTime, endTime))
                    {
                        cout<<"The Crew Member Is Already Scheduled For An Assignment In The Given Time Interval. Try Again!"<<endl;
                        continue;
                    }
                    filler[0] = startTime;
                    filler[1] = endTime;
                    schedule.push_back(filler);
                }
                if (loopExit)
                {
                    loopExit = false;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Generating Crew Member..."<<endl;
                Crew::add(crews, name, id, type, schedule);
                cout<<"Success!"<<endl;
                cout<<"~~What Do You Want To Do Next?"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;
            }
            break;
            // Start Of Case 3
            case (3):
            {
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                string make;
                string model;
                string numTail;
                string numSeats;
                string range;
                string minCrew;
                string startTime;
                string endTime;
                bool validTail = true;

                vector<vector<string>> schedule;
                vector<string> filler (2,"");
                cout<<"~~Please Enter In A Make For The Plane: "<<endl;
                make = enterNoSpace();
                if (make == "Exit")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                cout<<"~~Please Enter In A Model For The Plane: "<<endl;
                model = enterNoSpace();
                if (model == "Failed")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                // Add Tail Number For The Plane
                while (true)
                {
                    cout<<"~~Please Enter In The 6 Character Tail Number For The Plane: (Format: X000XX) Where X Is A Letter And 0 Is A Digit"<<endl;
                    cin>>numTail;
                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        if (i == 1 || i == 2 || i == 3)
                        {
                            if (!isdigit(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }else
                        {
                            if (!isupper(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }
                    }
                    if (!validTail || numTail.size() != 6)
                    {
                        cout<<"There Was An Error With The Provided Tail Number"<<endl;
                        validTail = true;
                        continue;
                    }
                    if (Plane::find(planes, numTail) != NULL)
                    {
                        cout<<"There Already Is A Plane With That Tail Number. Try Entering In A Different ID!"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                // Enter In Number Of Seats


                cout<<"~~Please Enter In A Number Of Seats For The Airplane: "<<endl;
                numSeats = enterAllNum(-1);
                if (numSeats == "Failed")
                {
                    break;
                }

                // Enter In Range Of The Airplane
                cout<<"~~Please Enter In The Maximum Range Of The Airplane"<<endl;
                range = enterAllNum(-1);
                if (range == "Failed")
                {
                    break;
                }
                // Add The Minimum Number Of Cabin Crew For The Airplane
                cout<<"~~Please Enter In The Minimum Number Of Cabin Crew For The Airplane"<<endl;
                minCrew = enterAllNum(-1);
                if (minCrew == "Failed")
                {
                    break;
                }
                // Add Departure And Arrival Times
                while (true)
                {
                    cout<<"~~Do You Want To Add A Departure And Arrival Flight Schedule For The Plane? ('Yes' Or 'No')"<<endl;
                    string temp;
                    cin>>temp;
                    if (temp == "Exit")
                    {
                        loopExit = true;
                        break;
                    }
                    if (temp != "Yes")
                    {
                        break;
                    }
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (!Flight::timeCheck(startTime,endTime))
                    {
                        startTime = "";
                        endTime = "";
                        continue;
                    }
                    if (!Plane::ableToAddSchedule(schedule, startTime, endTime))
                    {
                        cout<<"The Plane Is Already Scheduled For An Assignment In The Given Time Interval. Try Again!"<<endl;
                        continue;
                    }
                    filler[0] = startTime;
                    filler[1] = endTime;
                    schedule.push_back(filler);
                }
                if (loopExit)
                {
                    loopExit = false;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }

                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Generating Plane..."<<endl;
                Plane::add(planes, make, model, numTail, stoi(numSeats), stoi(range), stoi(minCrew), schedule);
                cout<<"Success!"<<endl;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"~~What Do You Want To Do Next?"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;
            }
            break;
            // Finish Plane

            // Flight
            case (4):
            {
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                string numTail;
                string pilot;
                string cabin;
                string startTime;
                string endTime;
                string startAirport;
                string endAirport;
                string status;
                string numPassenger;
                string numPilots;
                string cabinCrew;
                Plane* fillerPlane;
                string confirm;
                vector<string> pilots;
                vector<string> cabins;
                int minPilot = 4;
                int minCabinCrew;
                bool quit = false;
                while (true)
                {
                    cout<<"~~Please Enter In The Tail Number Of The Plane You Wish To Schedule The Flight For (Format: X000XX) Where X Is A Letter And 0 Is A Digit: "<<endl;
                    cout<<"If You Want To See A List Of All Planes, Please Enter 'Show'. Otherwise, Just Enter In The Tail Number:"<<endl;
                    string display;
                    display = enterNoSpace();
                    if (display == "Failed")
                    {
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        loopExit = true;
                        break;

                    }
                    if (display == "Show")
                    {
                        for (Plane* displayPlane : planes)
                        {
                            displayPlane->display();
                        }
                        cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                        cout<<"~~Please Enter In The Tail Number Of The Plane You Wish To Schedule The Flight For (Format: X000XX) Where X Is A Letter And 0 Is A Digit: "<<endl;
                        cin>>numTail;
                    }else
                    {
                        numTail = display;
                    }

                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    fillerPlane = Plane::find(planes, numTail);

                    if (fillerPlane == NULL)
                    {
                        cout<<"We Could Not Locate The Plane With The Input ID. Try Again!"<<endl;
                        continue;
                    }else
                    {
                        cout<<"You Have Chosen To Schedule A Flight For Plane: " + numTail<<endl;
                        cout<<"Confirm This Selection? ('Yes' Or 'No')"<<endl;
                        cin>>confirm;
                        if (confirm != "Yes")
                        {
                            quit = true;
                        }
                    }
                    minCabinCrew = fillerPlane->getMinCrew();
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                if (quit)
                {
                    quit = false;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                // Add Departure and Arrival

                while (true)
                {
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (!Flight::timeCheck(startTime,endTime))
                    {
                        startTime = "";
                        endTime = "";
                        cout<<"The End Time Must Be Later Than The Start Time"<<endl;
                        continue;
                    }
                    if (!Plane::isAvailablePlane(planes, numTail, startTime, endTime, -1))
                    {
                        cout<<"The Plane You Selected Is Not Available In This Time. Try Again!"<<endl;
                        continue;
                    }
                    if (Flight::overEight(startTime, endTime))
                    {
                        minPilot *= 2;
                        minCabinCrew *= 2;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }

                // Enter In ID Of Pilots
                cout<<"Please Enter In The IDs Of The Pilots You Wish To Add To The Flight (xxxxxx Where x Is The Digits Of The ID)"<<endl;
                cout<<"Make Sure You Enter In The IDs One By One"<<endl;
                cout<<"This Flight Requires At Least " << minPilot  <<" Pilots. Make Sure You Enter In The Correct Amount Before Moving On."<<endl;
                cout<<"Enter In 'Done' Once You Are Finished\n"<<endl;
                cout<<"If You Want To See A List Of All Available Pilots, Please Enter 'Show':"<<endl;
                string display;
                display = enterNoSpace();
                if (display == "Failed")
                {
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;

                }
                if (display == "Show")
                {
                    for (Crew* displayCrew : crews)
                    {
                        if (displayCrew->isPilot() && displayCrew->availableCrewPointer(startTime, endTime))
                        {
                            displayCrew->displayCrew("Pilot");
                        }
                    }
                    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                    cout<<"~~Please Enter In The IDs Of The Pilots You Wish To Add To The Flight (xxxxxx Where x Is The Digits Of The ID)"<<endl;
                    cout<<"Make Sure You Enter In The IDs One By One"<<endl;
                    cout<<"This Flight Requires At Least " << minPilot  <<" Pilots. Make Sure You Enter In The Correct Amount Before Moving On."<<endl;
                }
                int counter = 0;
                while (true)
                {
                    pilot = enterAllNum(6);
                    if (pilot == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (pilot == "Done")
                    {
                        if (counter < minPilot)
                        {
                            cout<<"You Did Not Enter A Sufficient Number Of Pilots For The Flight. Try Again!"<<endl;
                            continue;
                        }else
                        {
                            break;
                        }
                    }
                    Crew* checkPilot = Crew::findCrew(crews, pilot);


                    if (!checkPilot || !checkPilot->isPilot())
                    {
                        cout<<"The ID Corresponds To A Crew Member That Either Does Not Exist Or Is Not A Pilot. Try Again!"<<endl;
                        continue;
                    }
                    if (std::find(pilots.begin(), pilots.end(), pilot) != pilots.end())
                    {
                        cout<<"This Pilot Has Already Been Assigned To This Flight. Pick Another One!"<<endl;
                        continue;
                    }
                    pilots.push_back(pilot);
                    counter++;
                    cout<<"Added Pilot!"<<endl;
                }//This Is The End Of Adding Pilot IDs
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                // Enter In ID Of Cabin Crew
                cout<<"~~Please Enter In The IDs Of The Cabin Crew You Wish To Add To The Flight (xxxxxx Where x Is The Digits Of The ID)"<<endl;
                cout<<"Make Sure You Enter In The IDs One By One"<<endl;
                cout<<"This Flight Requires At Least " << minCabinCrew << " Cabin Crew Members. Make Sure You Enter In The Correct Amount Before Moving On."<<endl;
                cout<<"Enter In 'Done' Once You Are Finished"<<endl;
                cout<<"If You Want To See A List Of All Available Cabin Crew Members, Please Enter 'Show':"<<endl;

                display = enterNoSpace();
                if (display == "Failed")
                {
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;

                }
                if (display == "Show")
                {
                    for (Crew* displayCrew : crews)
                    {
                        if (!displayCrew->isPilot() && displayCrew->availableCrewPointer(startTime, endTime))
                        {
                            displayCrew->displayCrew("Cabin Crew Member");
                        }
                    }
                }
                counter = 0;
                while (true)
                {
                    cabin = enterAllNum(6);
                    if (cabin == "Failed")
                    {
                        loopExit = true;
                        cout<<"Exited Entry Successfully"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (cabin == "Done")
                    {
                        if (counter < minCabinCrew)
                        {
                            cout<<"You Did Not Enter A Sufficient Number Of Cabin Crew. Try Again!"<<endl;
                            continue;
                        }else
                        {
                            break;
                        }
                    }

                    bool checker2 = false;

                    Crew* checkCabin = Crew::findCrew(crews, cabin);
                    if (!checkCabin || checkCabin->isPilot())
                    {
                        checker2 = true;
                    }

                    if (checker2)
                    {
                        cout<<"The ID Corresponds To A Crew Member That Either Doesn't Exist Or Is Not A Cabin Crew Member"<<endl;
                        continue;
                    }
                    if (find(cabins.begin(), cabins.end(), cabin) != cabins.end())
                    {
                        cout<<"This Cabin Crew Member Has Already Been Assigned To This Flight. Pick Another One!"<<endl;
                        continue;
                    }
                    cabins.push_back(cabin);
                    counter++;
                    cout<<"Added Cabin Crew Member!"<<endl;
                }// This Is The End Of Adding Cabin Crew
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                // Add The Starting Airport
                cout<<"~~Please Enter In A Starting Airport For The Flight (XXX) Where X Is An Uppercase Character"<<endl;
                startAirport = enterAirport();
                if (startAirport == "Failed")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                // End Of Adding startAirport

                // Add The Ending Airport
                cout<<"~~Please Enter In An Ending Airport For The Flight (XXX) Where X Is An Uppercase Character"<<endl;
                endAirport = enterAirport();
                if (endAirport == "Failed")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                // End Of Adding endAirport

                // Add The Flight Status
                cout<<"~~Please Enter In The Status Of The Flight (Active, Canceled, Complete)"<<endl;
                while (true)
                {
                    cin>>status;
                    if (status == "Exit")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    bool valid = true;
                    if (status != "Active" && status != "Complete" && status != "Canceled")
                    {
                        valid = false;
                    }
                    if (!valid)
                    {
                        cout<<"The Input Was Not A Valid Status. Try Again!"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                // Add The Number Of Passengers
                cout<<"~~Please Enter In The Number Of Passengers On The Flight"<<endl;
                while (true)
                {
                    numPassenger = enterAllNum(-1);
                    if (numPassenger == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    Plane* checker = Plane::find(planes, numTail);
                    if (checker->getSeatNum() < stoi(numPassenger))
                    {
                        cout<<"The Input Number Of Passengers Exceeds The Number Of Seats On The Plane. Try Again!"<<endl;
                        continue;
                    }
                    break;
                }// End Adding Passengers
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                //Generating Flight Object
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Generating The Flight..."<<endl;
                Flight::add(flights, crews, planes, numTail, pilots, cabins, startTime, endTime, startAirport, endAirport, status, stoi(numPassenger),
                            pilots.size(), cabins.size());
                for (unsigned int i = 0; i < pilots.size(); i++)
                {
                    Crew* updatePilot = Crew::findCrew(crews, pilots[i]);
                    updatePilot->getSchedule().push_back({startTime, endTime});
                }
                for (unsigned int i = 0; i < cabins.size(); i++)
                {
                    Crew* updateCrew = Crew::findCrew(crews, cabins[i]);
                    updateCrew->getSchedule().push_back({startTime, endTime});
                }
                cout<<"Success!"<<endl;
                cout<<"~~What Do You Want To Do Next?"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;

            } // This Is The End Of Case 4
            break;

            // Edit Crew
            case (5) :
            {
                string name;
                string id;
                string type;
                string temp;
                string startTime;
                string endTime;
                vector<vector<string>> schedule;
                bool loopExit = false;
                Crew* editorCrew;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                cout<<"Editing Crew Member...\n"<<endl;
                cout<<"Here Is A List Of All Crew Members: \n"<<endl;
                for (Crew* crew : crews)
                {
                    crew->displayAll();
                }
                cout<<"~~~~~~~~~~~~~~~~~~\n"<<endl;
                cout<<"~~Please Enter In The ID Of The Crew Member You Wish To Change The Information For: "<<endl;

                while (true)
                {
                    id = enterAllNum(6);
                    if (id == "Failed")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Edit"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (id == ".")
                    {
                        cout<<"No Edit Was Made"<<endl;
                        id = editorCrew->getID();
                        break;
                    }
                    editorCrew = Crew::findCrew(crews, id);
                    if (editorCrew == NULL)
                    {
                        cout<<"We Could Not Find A Crew Member With That ID"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    break;
                }
                cout<<"~~Confirm Selection For: " + editorCrew->getName() + "(" + id + ")? ('Yes' Or 'No')"<<endl;
                cin>>temp;
                if (temp != "Yes")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                cout<<"Here Is The Data For: " + editorCrew->getName()<<endl;
                editorCrew->displayAll();
                cout<<"\n---------------------------------------------------"<<endl;
                cout<<"For Each Edit, Type A Period '.' If You Don't Want To Make Any Changes"<<endl;
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Edit The Name:"<<endl;
                name = enterNoSpace();
                if (name == "Failed")
                {
                    cout<<"Successfully Exited Edit"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                if (name == ".")
                {
                    cout<<"No Edit Was Made\n"<<endl;
                }else
                {
                    cout<<"Changed Name To: " + name<<endl;
                    editorCrew->setName(name);
                }
                cout<<"~~Edit The ID (6 Digits):"<<endl;

                while (true)
                {
                    id = enterAllNum(6);
                    if (id == "Failed")
                    {
                        cout<<"Successfully Exited Edit"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        loopExit = true;
                        break;
                    }
                    if (id == ".")
                    {
                        cout<<"No Edit Was Made\n"<<endl;
                        id = editorCrew->getID();
                    }else if (Crew::findCrew(crews, id) != NULL)
                    {
                        cout<<"A Crew Member Already Has That ID. Try Again!"<<endl;
                        continue;
                    }else
                    {
                        cout<<"Changed ID To: " + id<<endl;
                        editorCrew->setID(id);
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                cout<<"~~Edit The Type ('Pilot' Or 'Cabin')"<<endl;
                while (true)
                {
                    type = enterNoSpace();
                    if (type == "Failed")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    if (type == ".")
                    {
                        cout<<"No Edit Was Made\n"<<endl;
                        type = editorCrew->getType();
                    }else if (type != "Pilot" && type != "Cabin")
                    {
                        cout<<"The Input Must Be Either 'Pilot' Or 'Cabin'. Try Again!"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                editorCrew->setType(type);
                // edit schedule
                schedule = editorCrew->getSchedule();
                for (unsigned int i = 0; i < schedule.size(); i++)
                {
                    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                    cout<<"The Start Time Is: " + schedule[i][0]<<endl;
                    cout<<"The End Time Is: " + schedule[i][1]<<endl;
                    while (true)
                    {
                        startTime = enterSchedule(true);
                        if (startTime == "Failed")
                        {
                            loopExit = true;
                            cout<<"Successfully Exited Entry"<<endl;
                            cout<<"---------------------------------------------------"<<endl;
                            cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                            cout<<"~~What Do You Want To Do Next?"<<endl;
                            cout<<"~~Press '1' For A List Of Commands"<<endl;
                            break;
                        }
                        if (startTime == ".")
                        {
                            cout<<"No Edit Was Made\n"<<endl;
                            startTime = schedule[i][0];
                        }
                        endTime = enterSchedule(false);
                        if (endTime == "Failed")
                        {
                            loopExit = true;
                            cout<<"Successfully Exited Entry"<<endl;
                            cout<<"---------------------------------------------------"<<endl;
                            cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                            cout<<"~~What Do You Want To Do Next?"<<endl;
                            cout<<"~~Press '1' For A List Of Commands"<<endl;
                            break;
                        }
                        if (endTime == ".")
                        {
                            cout<<"No Edit Was Made\n"<<endl;
                            endTime = schedule[i][1];
                            break;
                        }
                        if (!Flight::timeCheck(startTime,endTime))
                        {
                            startTime = "";
                            endTime = "";
                            cout<<"The End Time Must Be Later Than The Start Time. Starting Entry From The Beginning..."<<endl;
                            continue;
                        }
                        if (!Crew::isAvailableCrew(crews, id, startTime, endTime, i))
                        {
                            cout<<"The Crew Member You Selected Is Not Available In This Time. Starting Entry From The Beginning..."<<endl;
                            continue;
                        }

                        break;
                    }
                    if (loopExit)
                    {
                        loopExit = false;
                        break;
                    }
                    schedule[i][0] = startTime;
                    schedule[i][1] = endTime;
                }
                while (true)
                {
                    cout<<"~~Do You Want To Add A Departure And Arrival Flight Schedule For The Crew Member? ('Yes' Or 'No')"<<endl;
                    string temp;
                    cin>>temp;
                    if (temp == "Exit")
                    {
                        loopExit = true;
                        break;
                    }
                    if (temp != "Yes")
                    {
                        break;
                    }
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (!Flight::timeCheck(startTime,endTime))
                    {
                        cout<<"The Arrival Time Must Be Later Than The Departure Time"<<endl;
                        startTime = "";
                        endTime = "";
                        continue;
                    }

                    if (!Crew::ableToAddSchedule(schedule, startTime, endTime))
                    {
                        cout<<"The Crew Member Is Already Scheduled For An Assignment In The Given Time Interval. Try Again!"<<endl;
                        continue;
                    }
                    schedule.push_back({startTime, endTime});
                }
                if (loopExit)
                {
                    loopExit = false;
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                editorCrew->setSchedule(schedule);
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Finalizing Edits To The Cabin Crew Member..."<<endl;
                cout<<"Success!"<<endl;
                cout<<"~~What Do You Want To Do Next?"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;
                cout<<""<<endl;
            }//End Of Case 5
            break;

            case (6):
            {
                bool loopExit = false;
                string temp;
                string numTail;
                string make;
                string model;
                string numSeats;
                string range;
                string minCrew;
                string startTime;
                string endTime;
                vector<vector<string>> schedule;
                Plane* editorPlane;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                cout<<"Editing Plane...\n"<<endl;
                cout<<"Here Is A List Of All Planes: \n"<<endl;
                for (Plane* plane : planes)
                {
                    plane->display();
                }
                cout<<"~~~~~~~~~~~~~~~~~~\n"<<endl;
                while (true)
                {
                    bool validTail = true;
                    cout<<"~~Please Enter In The 6 Character Tail Number For The Plane: (Format: X000XX) Where X Is A Letter And 0 Is A Digit"<<endl;
                    cin>>numTail;
                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        if (i == 1 || i == 2 || i == 3)
                        {
                            if (!isdigit(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }else
                        {
                            if (!isupper(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }
                    }
                    if (!validTail || numTail.size() != 6)
                    {
                        cout<<"There Was An Error With The Provided Tail Number"<<endl;
                        validTail = true;
                        continue;
                    }
                    if (Plane::find(planes, numTail) == NULL)
                    {
                        cout<<"We Could Not Find A Plane With That Tail Number. Try Entering In A Different Tail Number!"<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit){
                    loopExit = false;
                    break;
                }

                cout<<"~~Confirm Selection For Plane: " + numTail + "? ('Yes' Or 'No')"<<endl;
                editorPlane = Plane::find(planes, numTail);
                cin>>temp;
                if (temp != "Yes")
                {
                    cout<<"Successfully Exited Entry"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                cout<<"Here Is The Data For: " + editorPlane->getTail()<<endl;
                editorPlane->display();
                cout<<"\n---------------------------------------------------"<<endl;
                cout<<"For Each Edit, Type A Period '.' If You Don't Want To Make Any Changes"<<endl;
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Edit The Make:"<<endl;
                make = enterNoSpace();
                if (make == "Failed")
                {
                    printExit();
                    break;
                }
                if (make == ".")
                {
                    cout<<"No Edit Was Made\n"<<endl;
                }else
                {
                    cout<<"Changed Make To: " + make<<endl;
                    editorPlane->setMake(make);
                }
                // edit model
                cout<<"~~Edit The Model:"<<endl;
                model = enterNoSpace();
                if (model == "Failed")
                {
                    printExit();
                    break;
                }
                if (model == ".")
                {
                    cout<<"No Edit Was Made\n"<<endl;
                }else
                {
                    cout<<"Changed Model To: " + model<<endl;
                    editorPlane->setModel(model);
                }
                // edit numTail
                while (true)
                {
                    bool validTail = true;
                    cout<<"~~Edit The Tail Number. Please Enter In The 6 Character Tail Number For The Plane: (Format: X000XX) Where X Is A Letter And 0 Is A Digit"<<endl;
                    cin>>numTail;
                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        cout<<"Successfully Exited Entry"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                        cout<<"~~What Do You Want To Do Next?"<<endl;
                        cout<<"~~Press '1' For A List Of Commands"<<endl;
                        break;
                    }
                    if (numTail == ".")
                    {
                        cout<<"No Edit Was Made\n"<<endl;
                        numTail = editorPlane->getTail();
                        break;
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        if (i == 1 || i == 2 || i == 3)
                        {
                            if (!isdigit(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }else
                        {
                            if (!isupper(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }
                    }
                    if (!validTail || numTail.size() != 6)
                    {
                        cout<<"There Was An Error With The Provided Tail Number"<<endl;
                        validTail = true;
                        continue;
                    }
                    if (Plane::find(planes, numTail) != NULL)
                    {
                        cout<<"There Already Is A Plane With That Tail Number. Try Entering In A Different Tail Number!"<<endl;
                        continue;
                    }
                    cout<<"Changed Tail Number To: " + numTail<<endl;
                    editorPlane->setTail(numTail);
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }

                // edit numSeat
                cout<<"~~Edit The Number Of Seats On The Plane"<<endl;
                numSeats = enterAllNum(-1);
                if (numSeats == "Failed")
                {
                    cout<<"Successfully Exited Edit"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                if (numSeats == ".")
                {
                    cout<<"No Edit Was Made\n"<<endl;
                    editorPlane->setSeatNum(editorPlane->getSeatNum());
                }else
                {
                    cout<<"Changed The Number Of Seats To: " + numSeats<<endl;
                    editorPlane->setSeatNum(stoi(numSeats));
                }

                // edit range
                cout<<"~~Edit The Range Of The Plane"<<endl;
                range = enterAllNum(-1);
                if (range == "Failed")
                {
                    cout<<"Successfully Exited Edit"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                if (range == ".")
                {
                    cout<<"No Edit Was Made\n"<<endl;
                    editorPlane->setRange(editorPlane->getRange());
                }else
                {
                    cout<<"Changed The Range To: " + range<<endl;
                    editorPlane->setRange(stoi(range));
                }

                // edit minCrew
                cout<<"~~Edit The Minimum Number Of Cabin Crew On The Plane"<<endl;
                minCrew = enterAllNum(-1);
                if (minCrew == "Failed")
                {
                    cout<<"Successfully Exited Edit"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                    cout<<"~~What Do You Want To Do Next?"<<endl;
                    cout<<"~~Press '1' For A List Of Commands"<<endl;
                    break;
                }
                if (minCrew == ".")
                {
                    cout<<"No Edit Was Made/n"<<endl;
                    editorPlane->setSeatNum(editorPlane->getMinCrew());
                }else
                {
                    cout<<"Changed The Minimum Number Of Cabin Crew To: " + minCrew<<endl;
                    editorPlane->setMinCrew(stoi(minCrew));
                }
                schedule = editorPlane->getSchedule();
                for (unsigned int i = 0; i < schedule.size(); i++)
                {
                    cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                    cout<<"The Start Time Is: " + schedule[i][0]<<endl;
                    cout<<"The End Time Is: " + schedule[i][1]<<endl;
                    while (true)
                    {
                        startTime = enterSchedule(true);
                        if (startTime == "Failed")
                        {
                            loopExit = true;
                            cout<<"Successfully Exited Entry"<<endl;
                            cout<<"---------------------------------------------------"<<endl;
                            cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                            cout<<"~~What Do You Want To Do Next?"<<endl;
                            cout<<"~~Press '1' For A List Of Commands"<<endl;
                            break;
                        }
                        if (startTime == ".")
                        {
                            cout<<"No Edit Was Made\n"<<endl;
                            startTime = schedule[i][0];
                        }
                        endTime = enterSchedule(false);

                        if (endTime == "Failed")
                        {
                            loopExit = true;
                            cout<<"Successfully Exited Entry"<<endl;
                            cout<<"---------------------------------------------------"<<endl;
                            cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                            cout<<"~~What Do You Want To Do Next?"<<endl;
                            cout<<"~~Press '1' For A List Of Commands"<<endl;
                            break;
                        }
                        if (endTime == ".")
                        {
                            cout<<"No Edit Was Made\n"<<endl;
                            endTime = schedule[i][1];
                            break;
                        }
                        if (!Flight::timeCheck(startTime,endTime))
                        {
                            startTime = "";
                            endTime = "";
                            cout<<"The End Time Must Be Later Than The Start Time. Starting Entry From The Beginning..."<<endl;
                            continue;
                        }
                        if (!Plane::isAvailablePlane(planes, numTail, startTime, endTime, i))
                        {
                            cout<<"The Plane You Selected Is Not Available In This Time. Starting Entry From The Beginning..."<<endl;
                            continue;
                        }
                        break;
                    }
                    if (loopExit)
                    {
                        break;
                    }
                    schedule[i][0] = startTime;
                    schedule[i][1] = endTime;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                while (true)
                {
                    cout<<"~~Do You Want To Add A Departure And Arrival Flight Schedule For The Plane? ('Yes' Or 'No')"<<endl;
                    string temp;
                    cin>>temp;
                    if (temp == "Exit")
                    {
                        loopExit = true;
                        break;
                    }
                    if (temp != "Yes")
                    {
                        break;
                    }
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        break;
                    }
                    if (!Flight::timeCheck(startTime,endTime))
                    {
                        startTime = "";
                        endTime = "";
                        continue;
                    }
                    if (!Plane::ableToAddSchedule(schedule, startTime, endTime))
                    {
                        cout<<"The Plane Is Already Scheduled For An Assignment In The Given Time Interval. Try Again!"<<endl;
                        continue;
                    }
                    schedule.push_back({startTime, endTime});
                }
                if (loopExit)
                {
                    loopExit = false;
                    printExit();
                    break;
                }
                editorPlane->setSchedule(schedule);
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"~~Finalizing Edits To The Plane..."<<endl;
                cout<<"Success!"<<endl;
                cout<<"~~What Do You Want To Do Next?"<<endl;
                cout<<"~~Press '1' For A List Of Commands"<<endl;
                cout<<""<<endl;
            }
            break;

            case (7):
            {
                Flight* editorFlight;
                string numTail;
                string startTime;
                string endTime;
                string temp;
                string pilotsString;
                string cabinsString;
                string pilotID;
                string cabinID;
                vector<Crew*> pilots;
                vector<Crew*> cabins;
                int minPilot = 4;
                int minCabinCrew;
                bool init = true;
                bool conflict = false;
                bool add = false;
                string x;
                string msg;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"MAKE SURE YOU SEPARATE WORDS WITH HYPHENS, NOT SPACES"<<endl;
                cout<<"Enter In 'Exit' At Any Time To Exit The Entry"<<endl;
                cout<<"Editing Flight...\n"<<endl;
                cout<<"Here Is A List Of All Flights: \n"<<endl;
                for (Flight* flight : flights)
                {
                    flight->display();
                }
                cout<<"~~~~~~~~~~~~~~~~~~\n"<<endl;
                while (true)
                {
                    bool validTail = true;
                    cout<<"~~Please Enter In The 6 Character Tail Number For The Plane: (Format: X000XX) Where X Is A Letter And 0 Is A Digit"<<endl;
                    cin>>numTail;
                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        if (i == 1 || i == 2 || i == 3)
                        {
                            if (!isdigit(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }else
                        {
                            if (!isupper(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }
                    }
                    if (!validTail || numTail.size() != 6)
                    {
                        cout<<"There Was An Error With The Provided Tail Number"<<endl;
                        validTail = true;
                        continue;
                    }
                    if (Plane::find(planes, numTail) == NULL)
                    {
                        cout<<"We Could Not Find A Plane With That Tail Number. Try Entering In A Different Tail Number!"<<endl;
                        continue;
                    }

                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    cout<<startTime<<endl;
                    editorFlight = Flight::findFlight(flights, numTail, startTime);
                    if (editorFlight == NULL)
                    {
                        cout<<"We Could Not Find A Flight With That Set Of Tail Number And Start Time. Starting Entry From The Beginning..."<<endl;
                        continue;
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                cout<<"~~Confirm Selection For Flight With Plane " + numTail + " And Start Date: " + startTime + "? ('Yes' Or 'No')"<<endl;
                cin>>temp;
                if (temp != "Yes")
                {
                    printExit();
                    break;
                }


                cout<<"Here Is The Data For: " + editorFlight->getNumTail() + " Starting At " + editorFlight->getStartAirport()<<endl;
                editorFlight->display();
                cout<<"\n---------------------------------------------------"<<endl;
                cout<<"For Each Edit, Type A Period '.' If You Don't Want To Make Any Changes"<<endl;
                cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
                // edit numTail
                while (true)
                {
                    bool validTail = true;
                    cout<<"~~Edit The Tail Number. Please Enter In The 6 Character Tail Number For The Plane: (Format: X000XX) Where X Is A Letter And 0 Is A Digit"<<endl;
                    cin>>numTail;
                    if (numTail == "Exit")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    if (numTail == ".")
                    {
                        cout<<"No Edit Was Made\n"<<endl;
                        numTail = editorFlight->getNumTail();
                        break;
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        if (i == 1 || i == 2 || i == 3)
                        {
                            if (!isdigit(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }else
                        {
                            if (!isupper(numTail[i]))
                            {
                                validTail = false;
                                break;
                            }
                        }
                    }
                    if (!validTail || numTail.size() != 6)
                    {
                        cout<<"There Was An Error With The Provided Tail Number"<<endl;
                        validTail = true;
                        continue;
                    }
                    if (Plane::find(planes, numTail) != NULL)
                    {
                        cout<<"There Already Is A Plane With That Tail Number. Try Entering In A Different Tail Number!"<<endl;
                        continue;
                    }
                    cout<<"Changed Tail Number To: " + numTail<<endl;
                    editorFlight->setNumTail(numTail);
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                while (true)
                {
                    cout<<"~~Edit The Departure Time"<<endl;
                    startTime = enterSchedule(true);
                    if (startTime == "Failed")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    if (startTime == ".")
                    {
                        startTime = editorFlight->getStartTime();
                    }
                    cout<<"~~Edit The Arrival Time"<<endl;
                    endTime = enterSchedule(false);
                    if (endTime == "Failed")
                    {
                        loopExit = true;
                        printExit();
                        break;
                    }
                    if (endTime == ".")
                    {
                        endTime = editorFlight->getEndTime();
                    }

                    if (!Flight::timeCheck(startTime, endTime))
                    {
                        cout<<"The Arrival Time Must Come After The Departure Time"<<endl;
                        continue;
                    }

                    if (!Plane::isAvailablePlane(planes, numTail, startTime, endTime, -1))
                    {
                        cout<<"The Plane Is Not Available In This Time Interval. Try Again!\n"<<endl;
                        continue;
                    }
                    pilotsString = editorFlight->getPilots();
                    cabinsString = editorFlight->getCabinCrew();
                    stringstream ss (pilotsString);
                    stringstream ss2 (cabinsString);
                    while (getline(ss,x,'|'))
                    {
                        pilots.push_back(Crew::findCrew(crews, x));
                        if (!Crew::isAvailableCrew(crews, x, startTime, endTime, -1))
                        {
                            if (init)
                            {
                                init = !init;
                                cout<<"These Pilots Have A Time Conflict With The Scheduled Flight: "<<endl;
                            }
                            msg += (x + ", ");
                            conflict = true;
                        }
                    }
                    if (msg.size() > 2)
                    {
                        msg.pop_back();
                        msg.pop_back();
                    }
                    cout<<msg + "\n"<<endl;
                    msg = "";
                    init = true;
                    while (getline(ss2,x,'|'))
                    {
                        cabins.push_back(Crew::findCrew(crews, x));
                        if (!Crew::isAvailableCrew(crews, x, startTime, endTime, -1))
                        {
                            if (init)
                            {
                                init = !init;
                                cout<<"These Cabin Crew Members Have A Time Conflict With The Scheduled Flight: "<<endl;
                            }
                            msg += (x + ", ");
                            conflict = true;
                        }
                    }
                    if (msg.size() > 2)
                    {
                        msg.pop_back();
                        msg.pop_back();
                    }
                    cout<<msg + "\n"<<endl;
                    if (conflict)
                    {
                        cout<<"WARNING!!! YOU ARE ABOUT TO CHANGE THE SCHEDULE TO A TIME IN WHICH AT LEAST 1 CREW MEMBER HAS A CONFLICT WITH\nYOU WILL HAVE THE OPTION TO ALTER THE LIST OF CREW MEMBERS FOR THE FLIGHT\nARE YOU SURE YOU WANT TO PROCEED? (Enter 'Confirm' To Proceed, 'No' To Re-Enter A Schedule, Or 'Exit' To Quit)"<<endl;
                        temp = enterNoSpace();
                        if (temp == "Failed")
                        {
                            loopExit = true;
                            printExit();
                            break;
                        }
                        if (temp == "Confirm")
                        {
                            cout<<"Set Flight To Leave At " + startTime + " And Arrive At " + endTime<<endl;
                            break;
                        }else
                        {
                            continue;
                        }
                    }
                    break;
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
                if (Flight::overEight(startTime, endTime))
                {
                    minPilot *= 2;
                    minCabinCrew *= 2;
                }


                // edit pilots
                cout<<"Do You Want To Remove Any Pilots From The Flight? ('Yes' Or 'No')"<<endl;
                cout<<"Keep In Mind The Flight Needs At Least " + to_string(minPilot) + " Pilots"<<endl;
                temp = enterNoSpace();
                if (temp == "Failed")
                {
                    printExit();
                    break;
                }
                if (temp == "Yes")
                {
                    int counter = 0;
                    while (true)
                    {
                        cout<<"Enter The ID Of Each Pilot To Delete Them From The Flight"<<endl;
                        cout<<"Enter In 'Done' When Finished"<<endl;
                        pilotID = enterAllNum(6);
                        if (pilotID == "Failed")
                        {
                            loopExit = true;
                            printExit();
                            break;
                        }
                        if (pilotID == "Done")
                        {
                            cout<<"Removed " + to_string(counter) + " Pilots From The Flight\n"<<endl;
                            break;
                        }
                        Crew* deleteCrew = Crew::findCrew(crews, pilotID);
                        if (deleteCrew == NULL)
                        {
                            cout<<"Could Not Find Crew Member With That ID. Try Again!"<<endl;
                            continue;
                        }
                        deleteCrew->deleteAssignment(startTime);
                        cout<<"Removed " + pilotID + " From The Flight\n"<<endl;
                        counter++;
                    }
                    if (loopExit)
                    {
                        loopExit = false;
                        break;
                    }
                }
                int counter = pilots.size();
                if (minPilot - counter > 0)
                {
                    cout<<"You Need To Add At Least " <<minPilot - counter<<" Pilots To The Flight For It To Be Valid"<<endl;
                    cout<<"Enter In 'Done' When Finished"<<endl;
                    add = true;
                }else
                {
                    cout<<"Do You Want To Add Pilots To The Flight? ('Yes' Or 'No')"<<endl;
                    temp = enterNoSpace();
                    if (temp == "Failed")
                    {
                        printExit();
                        break;
                    }
                    if (temp == "Yes")
                    {
                        add = true;
                    }
                }
                if (add)
                {
                    while (true)
                    {
                        cout<<"~~Please Enter In The ID Of The Pilot You Wish To Add To The Flight (xxxxxx) Where x Is A Digit"<<endl;
                        pilotID = enterAllNum(6);
                        if (pilotID == "Failed")
                        {
                            loopExit = true;
                            printExit();
                            break;
                        }
                        if (pilotID == "Done")
                        {
                            if (counter < minPilot)
                            {
                                cout<<"There Are Not Enough Pilots Scheduled For The Flight. There Needs To Be At Least " + to_string(minPilot) + "Pilots"<<endl;
                                continue;
                            }else
                            {
                                cout<<"Finished Adding Pilots To Flight"<<endl;
                                break;
                            }
                        }
                        Crew* addCrew = Crew::findCrew(crews, pilotID);
                        if (addCrew == NULL)
                        {
                            cout<<"Could Not Find A Pilot With That ID. Try Again!"<<endl;
                            continue;
                        }
                        if (find(pilots.begin(), pilots.end(), addCrew) != pilots.end())
                        {
                            cout<<"That Pilot Is Already Scheduled For This Flight. Try Again!"<<endl;
                            continue;
                        }
                        if (addCrew->isPilot() && addCrew->availableCrewPointer(startTime, endTime))
                        {
                            pilots.push_back(addCrew);
                            addCrew->addAssignment(startTime, endTime);
                            counter++;
                        }else
                        {
                            cout<<"That Crew Member Either Is Not A Pilot Or Is Not Available In This Time Slot. Try Again!"<<endl;
                            continue;
                        }
                    }
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }

                // edit cabin crew
                add = false;
                cout<<"Do You Want To Remove Any Cabin Crew Members From The Flight? ('Yes' Or 'No')"<<endl;
                cout<<"Keep In Mind The Flight Needs At Least " + to_string(minCabinCrew) + " Cabin Crew Members"<<endl;
                temp = enterNoSpace();
                if (temp == "Failed")
                {
                    printExit();
                    break;
                }
                if (temp == "Yes")
                {
                    int counter = 0;
                    while (true)
                    {
                        cout<<"Enter The ID Of Each Cabin Crew Member To Delete Them From The Flight"<<endl;
                        cout<<"Enter In 'Done' When Finished"<<endl;
                        cabinID = enterAllNum(6);
                        if (cabinID == "Failed")
                        {
                            loopExit = true;
                            printExit();
                            break;
                        }
                        if (cabinID == "Done")
                        {
                            cout<<"Removed " + to_string(counter) + " Cabin Crew Members From The Flight\n"<<endl;
                            break;
                        }
                        Crew* deleteCrew = Crew::findCrew(crews, cabinID);
                        if (deleteCrew == NULL)
                        {
                            cout<<"Could Not Find Crew Member With That ID. Try Again!"<<endl;
                            continue;
                        }
                        deleteCrew->deleteAssignment(startTime);
                        cout<<"Removed " + cabinID + " From The Flight\n"<<endl;
                        counter++;
                    }
                    if (loopExit)
                    {
                        loopExit = false;
                        break;
                    }
                }
                counter = cabins.size();
                if (minCabinCrew - counter > 0)
                {
                    cout<<"You Need To Add At Least " <<minCabinCrew - counter<<" Cabin Crew Members To The Flight For It To Be Valid"<<endl;
                    cout<<"Enter In 'Done' When Finished"<<endl;
                    add = true;
                }else
                {
                    cout<<"Do You Want To Add Cabin Crew Members To The Flight? ('Yes' Or 'No')"<<endl;
                    temp = enterNoSpace();
                    if (temp == "Failed")
                    {
                        printExit();
                        break;
                    }
                    if (temp == "Yes")
                    {
                        add = true;
                    }
                }
                if (add)
                {
                    while (true)
                    {
                        cout<<"~~Please Enter In The ID Of The Cabin Crew Member You Wish To Add To The Flight (xxxxxx) Where x Is A Digit"<<endl;
                        cabinID = enterAllNum(6);
                        if (cabinID == "Failed")
                        {
                            loopExit = true;
                            printExit();
                            break;
                        }
                        if (cabinID == "Done")
                        {
                            if (counter < minCabinCrew)
                            {
                                cout<<"There Are Not Enough Cabin Crew Members Scheduled For The Flight. There Needs To Be At Least " + to_string(minCabinCrew) + " Cabin Crew Members"<<endl;
                                continue;
                            }else
                            {
                                cout<<"Finished Adding Cabin Crew Members To Flight"<<endl;
                                break;
                            }
                        }
                        Crew* addCrew = Crew::findCrew(crews, cabinID);
                        if (addCrew == NULL)
                        {
                            cout<<"Could Not Find A Cabin Crew Member With That ID. Try Again!"<<endl;
                            continue;
                        }
                        if (find(cabins.begin(),cabins.end(), addCrew) != cabins.end())
                        {
                            cout<<"That Cabin Crew Member Is Already Scheduled For This Flight. Try Again!"<<endl;
                            continue;
                        }
                        if (!addCrew->isPilot() && addCrew->availableCrewPointer(startTime, endTime))
                        {
                            cabins.push_back(addCrew);
                            addCrew->addAssignment(startTime, endTime);
                            counter++;
                        }else
                        {
                            cout<<"That Crew Member Either Is Not A Cabin Crew Member Or Is Not Available In The Time Slot. Try Again!"<<endl;
                            continue;
                        }
                    }
                }
                if (loopExit)
                {
                    loopExit = false;
                    break;
                }
            }

            break;
        }// End Of Switch Statement

    }



    // rewrite to file
    ofstream writer("database.txt");
    // Write out planes
    for (unsigned int i = 0; i < planes.size(); i++)
    {
        writer<<planes[i];
    }
    cout<<"finished"<<endl;
    writer<<"~,~,~,0,0,0,0000/00/00/00/000000/00/00/00/00\n";

    // Write out crew members
    for (unsigned int i = 0; i < crews.size(); i++)
    {
        writer<<crews[i];
    }

    writer<<"~,~,~,0000/00/00/00/000000/00/00/00/00,~\n";

    // Write out flights
    for (unsigned int i = 0; i < flights.size(); i++)
    {
        writer<<flights[i];
    }
    writer<<"~,~,~,0000/00/00/00/000000/00/00/00/00,~,~,~,~,0,0,0";
    writer.close();
    return 0;
}

