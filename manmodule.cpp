/**
 * \mainpage
 * \section Author
 * @author NorthernBites
 *
 * \section Copyright
 * Version : $Id$
 *
 * \section Description
 *
 * This file was generated by Aldebaran Robotics ModuleGenerator
 */

#ifndef _WIN32
#include <signal.h>
#endif

#include "altypes.h"
#include "alxplatform.h"
#include "manmodule.h"
#include "alptr.h"
#include "albroker.h"
#include "almodule.h"
#include "albrokermanager.h"
#include "alerror.h"

//NBites includes
#include "alproxy.h"

using namespace std;
using namespace AL;

//<EXE_INCLUDE> don't remove this comment
#include "Man.h" //EDIT -JS



//</EXE_INCLUDE> don't remove this comment

//<ODECLAREINSTANCE> don't remove this comment

//</ODECLAREINSTANCE> don't remove this comment
static boost::shared_ptr<Man> man;

#ifndef MAN_IS_REMOTE

#ifdef _WIN32
#define ALCALL __declspec(dllexport)
#else
#define ALCALL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

ALCALL int _createModule( ALPtr<ALBroker> pBroker )
{
#ifdef REDIRECT_C_STDERR
  // Redirect stderr to stdout
  FILE *_syderr = stderr;
  stderr = stdout;
#endif

  // init broker with the main broker inctance
  // from the parent executable
  ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
  ALBrokerManager::getInstance()->addBroker(pBroker);

  // create modules instance
  //<OGETINSTANCE> don't remove this comment

  //</OGETINSTANCE> don't remove this comment

  //NBites code
  man  = boost::shared_ptr<Man>(new Man(pBroker,"Man"));
  man->manStart();

  return 0;
}

ALCALL int _closeModule(  )
{
  // Delete module instance
  //<OKILLINSTANCE> don't remove this comment
  //ALPtr<ALProxy>
  // man  = pBroker->getProxy("Man");
    man->manStop();
  //</OKILLINSTANCE> don't remove this comment

  return 0;
}

# ifdef __cplusplus
}
# endif

#else
void _terminationHandler( int signum )
{
  //ALPtr<ALProxy> man  = pBroker->getProxy("Man");

  if (signum == SIGINT) {
    // no direct exit, main thread will exit when finished
    cerr << "Exiting Man via thread stop." << endl;
    man->manStop();
  }
  else {
    cerr << "Emergency stop -- exiting immediately" << endl;
    // fault, exit immediately
    ::exit(1);
  }
  ALBrokerManager::getInstance()->killAllBroker();
  ALBrokerManager::kill();
  exit(0);
}


int usage( char* progName )
{
  std::cout << progName <<", a remote module of naoqi !" << std::endl

            << "USAGE :" << std::endl
            << "-b\t<ip> : binding ip of the server. Default is 127.0.0.1" << std::endl
            << "-p\t<port> : binding port of the server. Default is 9559" << std::endl
            << "-pip\t<ip> : ip of the parent broker. Default is 127.0.0.1" << std::endl
            << "-pport\t<ip> : port of the parent broker. Default is 9559" << std::endl
            << "-h\t: Display this help\n" << std::endl;
  return 0;
}

int main( int argc, char *argv[] )
{
#ifdef REDIRECT_C_STDERR
  // Redirect stderr to stdout
  FILE *_syderr = stderr;
  stderr = stdout;
#endif

  std::cout << "..::: starting MANMODULE revision " << MANMODULE_VERSION_REVISION << " :::.." << std::endl;
  std::cout << "Copyright (c) 2007, Aldebaran-robotics" << std::endl << std::endl;

  int  i = 1;
  std::string brokerName = "manmodule";
  std::string brokerIP = "0.0.0.0";
  int brokerPort = 0 ;
  // Default parent broker IP
  std::string parentBrokerIP = "127.0.0.1";
  // Default parent broker port
  int parentBrokerPort = kBrokerPort;

  // checking options
  while( i < argc ) {
    if ( argv[i][0] != '-' ) return usage( argv[0] );
    else if ( std::string( argv[i] ) == "-b" )        brokerIP          = std::string( argv[++i] );
    else if ( std::string( argv[i] ) == "-p" )        brokerPort        = atoi( argv[++i] );
    else if ( std::string( argv[i] ) == "-pip" )      parentBrokerIP    = std::string( argv[++i] );
    else if ( std::string( argv[i] ) == "-pport" )    parentBrokerPort  = atoi( argv[++i] );
    else if ( std::string( argv[i] ) == "-h" )        return usage( argv[0] );
    i++;
  }

  // If server port is not set
  if ( !brokerPort )
    brokerPort = FindFreePort( brokerIP );

  std::cout << "Try to connect to parent Broker at ip :" << parentBrokerIP
            << " and port : " << parentBrokerPort << std::endl;
  std::cout << "Start the server bind on this ip :  " << brokerIP
            << " and port : " << brokerPort << std::endl;

  // Starting Broker
 ALPtr<ALBroker> pBroker = ALBroker::createBroker(brokerName, brokerIP, brokerPort, parentBrokerIP,  parentBrokerPort);
 pBroker->setBrokerManagerInstance(ALBrokerManager::getInstance());


  //<OGETINSTANCE> don't remove this comment
 //ALPtr<Man> manptr = ALModule::createModule<Man>(pBroker,"Man" );
 man = boost::shared_ptr<Man>(new Man(pBroker,"Man"));
  //</OGETINSTANCE> don't remove this comment

#ifndef _WIN32
  struct sigaction new_action;
  /* Set up the structure to specify the new action. */
  new_action.sa_handler = _terminationHandler;
  sigemptyset( &new_action.sa_mask );
  new_action.sa_flags = 0;

  sigaction( SIGINT, &new_action, NULL );
#endif


  man->manStart();
  cout << "Main method finished starting man" <<endl;
  //manptr->manAwaitOn();
  //manptr->manAwaitOff();

  //   Not sure what the purpose of this modulegenerator code is: //EDIT -JS
  pBroker.reset(); // because of while( 1 ), broker counted by brokermanager
  while( 1 )
  {
    SleepMs( 100 );
  }

  cout << "Main method finished" <<endl;


#ifdef _WIN32
  _terminationHandler( 0 );
#endif

  exit( 0 );
}
#endif
