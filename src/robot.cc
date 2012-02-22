#include <iostream>
using namespace std;


class Robot {
	//Need datum for (0,0) - center of robot compared to center of start position?
	float rotation = 0; // in radians
	float xlocation = 0;
	float ylocation = 0;
	bool knownposition = true; //set to false if we only know location via dead-reckoning
  public:
    void setpower(newpower){currentpower=newpower;}
} Bot;
