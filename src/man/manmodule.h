/**
 * @author NorthernBites
 *
 * Version : $
 *
 * This file was generated by Aldebaran Robotics ModuleGenerator
 */

#ifndef MANMODULE_H
#define MANMODULE_H

// ..::: Headers ::
#include <fstream>
#include <sstream>

#include "alcommon/albroker.h"
#include "alcommon/albrokermanager.h"
#include "alcommon/almodule.h"
#include "alcommon/alproxy.h"
#include "alcore/alerror.h"
#include "alcore/alptr.h"
#include "alcore/altypes.h"
#include "alproxies/alsentinelproxy.h"
#include "altools/alxplatform.h"

#include "manconfig.h"

// ..::: Version Information ::
/** Major release version */
#define MANMODULE_VERSION_MAJOR    "0"

/** Minor release version */
#define MANMODULE_VERSION_MINOR    "1"

/** Revision release version */
#define MANMODULE_VERSION_REVISION MANMODULE_REVISION

/** Full string version: (ex. 0.1-r2) */
#define MANMODULE_VERSION MANMODULE_VERSION_MAJOR"."MANMODULE_VERSION_MINOR"-r"MANMODULE_VERSION_REVISION

/** Internal version name */
#define MANMODULE_VERSION_CODENAME "internal"

/** Release date */
//#define MANMODULE_VERSION_DATE     "20071113"

#define ALVALUE_STRING( val ) ((val.getType() == ALValue::TypeString) ? std::string(val) : std::string("") )
#define ALVALUE_DOUBLE( val ) ((val.getType() == ALValue::TypeDouble || val.getType() == ALValue::TypeInt) ? double(val) : 0.0 )
#define ALVALUE_INT( val ) ((val.getType() == ALValue::TypeInt || val.getType() == ALValue::TypeDouble) ? int(val) : 0)

#endif // MANMODULE_H
