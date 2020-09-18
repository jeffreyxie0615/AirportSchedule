#ifndef PLANE_H
#define PLANE_H
#include <string>
#include <vector>

using namespace std;

class Plane
{
    public:
        Plane();
        Plane(std::string make,std::string model,std::string numTail,int numSeats,int range,int minCrew,
              vector<vector<string>> scheduleCopy);
        virtual ~Plane();

        string getMake();
        string getModel();
        string getTail();
        int getSeatNum();
        int getRange();
        int getMinCrew();
        vector<vector<string>>& getSchedule();

        void setMake(string makeCopy);
        void setModel(string ModelCopy);
        void setTail(string numTailCopy);
        void setSeatNum(int numSeatCopy);
        void setRange(int rangeCopy);
        void setMinCrew(int minCrewCopy);
        void setSchedule(vector<vector<string>> schedule);

        bool availablePlanePointer(string startTime, string endTime);
        void display();
        static void add(vector<Plane*>& planes, std::string make,std::string model, std::string numTail,
                        int numSeats, int range, int minCrew, vector<vector<string>> schedule);
        static void edit(vector<Plane*> planes, string make, string model, string numTail,
                         int numSeats, int range, int minCrew);
        static void deletePlane(vector<Plane*>& planes, std::string numTail);
        static Plane* find(std::vector<Plane*>& planes, std::string numTail);
        static int findPosition(std::vector<Plane*> planes, std::string numTail);
        static int printAll(std::vector<Plane*>& planes);
        static void printSpec(std::vector<Plane*>& planes, std::string numTail);
        static long long int convertTime(string time);
        static bool isAvailablePlane(std::vector<Plane*>& planes, std::string numTail, std::string startTime, std::string endTime, int index);
        static bool isAvailableSeats(std::vector<Plane*>& planes, std::string numTail, int numPassenger);
        static bool ableToAddSchedule(vector<vector<string>>& currentSchedule, string startTime, string endTime);

    protected:

    private:
        std::string make;
        std::string model;
        std::string numTail;
        int numSeats;
        int range;
        int minCrew;
        vector<vector<string>> schedule;



};

#endif // PLANE_H
