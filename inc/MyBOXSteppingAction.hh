
#ifndef MYBOXSTEPPINGACTION_HH
#define MYBOXSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

// forward declarations
class MyBOXDetectorConstruction;
class MyBOXEventAction;
class G4VPhysicalVolume;


class MyBOXSteppingAction : public G4UserSteppingAction {

  // Method declaration:
  public:
    
    // CTR: 
    //  - detector construction object is used to find out the target volume
    //  - event action is used to fill per-event cumulative values 
	MyBOXSteppingAction(MyBOXDetectorConstruction* det, MyBOXEventAction* evtAction);
    virtual ~MyBOXSteppingAction();

    // Virtual method called by the kernel after each step
    virtual void UserSteppingAction(const G4Step* step);

    

  // Data member declarations:
  private:

    MyBOXDetectorConstruction*    fMyBOXDetector;

    MyBOXEventAction*             fMyBOXEventAction;
};

#endif
