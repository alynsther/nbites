#ifndef _Noggin_h_DEFINED
#define _Noggin_h_DEFINED

#include <Python.h>
#include <boost/shared_ptr.hpp>

#include "MotionInterface.h"
#include "Profiler.h"
#include "PyVision.h"
#include "BallEKF.h"
#include "Comm.h"
#include "GameController.h"
#include "RoboGuardian.h"
#include "Sensors.h"
#include "PyConstants.h"
#include "memory/log/LoggingBoard.h"
#include "memory/log/PyLoggingBoard.h"

#include "ParticleFilter.h"
#include "MotionSystem.h"
#include "VisionSystem.h"
#include "FieldConstants.h"

//#define LOG_LOCALIZATION

/**
 *
 * @brief Class to control the main thread function of all reasoning and
 * planning components of the robot.
 */

class Noggin
{
public:
    Noggin(boost::shared_ptr<Vision> v,
           boost::shared_ptr<Comm> c, boost::shared_ptr<RoboGuardian> rbg,
           boost::shared_ptr<Sensors> _sensors,
           boost::shared_ptr<man::memory::log::LoggingBoard> loggingBoard,
           MotionInterface * _minterface,
           man::memory::Memory::ptr Memory
           );
    virtual ~Noggin();

    // reinitialize and reload the Python interpreter
    void reload_hard ();
    // reload Brain module
    void reload_brain ();
    // reload specified modules
    void reload_modules (std::string modules);
    // run behavioral step
    void runStep();

    // current Noggin error status
    bool inErrorState() { return error_state; }

private:
    // Initialize the interpreter and C Python extensions
    void initializePython();
    // Insert the man directory in the system path
    void modifySysPath();
    // Import the util.module_helper and noggin.Brain modules
    bool import_modules();
    // Instantiate a Brain instance
    void getBrainInstance();
    // Initialize the localization system
    void initializeLocalization();
    // Run the localization update; performed at every run step
    void updateLocalization();
    //Process button  clicks that pertain to GameController manipulation
    void processGCButtonClicks();

    /**
     * Takes a boolean indicating whether or not the robot is in a 
     * fallen state, and if it is the first frame in such a state,
     * it notifies the localization motion model, to adjust
     * the belief accordingly. 
     * 
     * @param fallen Indicates whether or not the robot is in a 
     *               fallen state. Provided by RoboGuardian 
     *               (or BH walk engine FallDownState.)
     */
    void updateRobotFallenState(bool fallen)
    {
	if(!fallenState && fallen)
	{
	    std::cout << "Noggin: Entering fallen state!" << std::endl;
	    fallenState = true;
	    locMotionSystem->setFallen(true);
	}
	else if(fallenState && !fallen)
	{
	    std::cout << "Noggin: No longer in fallen state." << std::endl;
	    fallenState = false;
	}
    }

private:
    boost::shared_ptr<Vision> vision;
    boost::shared_ptr<Comm> comm;
    boost::shared_ptr<GameController> gc;
    boost::shared_ptr<Sensors> sensors;
    boost::shared_ptr<RoboGuardian> guard;
    man::memory::log::LoggingBoard::ptr loggingBoard;
    man::memory::Memory::ptr memory;


    boost::shared_ptr<ClickableButton> chestButton;
    boost::shared_ptr<ClickableButton> leftFootButton;
    boost::shared_ptr<ClickableButton> rightFootButton;

    boost::shared_ptr<MotionSystem> locMotionSystem;
    boost::shared_ptr<VisionSystem> locVisionSystem;

    bool error_state;
    PyObject *module_helper;
    PyObject *brain_module;
    PyObject *brain_instance;
    MotionInterface * motion_interface;
    bool fallenState;

    // GC stuff
    bool registeredGCReset;
    // Teammate ball stuff
    int ballFramesOff;
    // Reload specifiers
    int do_reload;
    std::vector<std::string> module_list;

// Public members
public:
    boost::shared_ptr<LocSystem> loc;
    boost::shared_ptr<BallEKF> ballEKF;

#ifdef LOG_LOCALIZATION
    void startLocLog();
    void stopLocLog();

private:
    bool loggingLoc;
#endif // LOG_LOCALIZATION
};

#endif // _Noggin_h_DEFINED
