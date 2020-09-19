#ifndef CREW_H
#define CREW_H
#include <string>
#include <vector>

using namespace std;
class Crew
{
    public:
        Crew();
        Crew(string name, string id, string type, vector<vector<string>> schedule);
        virtual ~Crew();

        string getName();
        string getID();
        string getType();
        vector<vector<string>>& getSchedule();
        vector<string>& getPlaneSchedule();

        void setName(string name);
        void setID(string id);
        void setType(string type);
        void setSchedule(vector<vector<string>> schedule);
        void setPlaneSchedule(vector<string> planeSchedule);
        void deleteAssignment(string startTime);
        void addAssignment(string startTIme, string endTime);
        bool isPilot();
        void displayCrew(string filler);
        void displayAll();
        bool availableCrewPointer(string startTime, string endTime);
        static bool isAvailableCrew(vector<Crew*>& crews, string id, string startTime, string endTime, int index);
        static bool ableToAddSchedule(vector<vector<string>>& currentSchedule, string startTime, string endTime);
        static void add(vector<Crew*>& crews, string name, string id, string type, vector<vector<string>> schedule);
        static void edit(vector<Crew*>& crews, string name, string id, string type, vector<vector<string>> schedule);
        static void deleteCrew(vector<Crew*>& crews, string id);
        static Crew* findCrew(vector<Crew*>& crews, string OGid);
        static int findCrewPosition(vector<Crew*>& crews, string id);
        static void printAll();
        static void printSpec();

    protected:

    private:
        string name;
        string id;
        string type;
        vector<vector<string>> schedule;
        vector<string> planeSchedule;
};

#endif // CREW_H
