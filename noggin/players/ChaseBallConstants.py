
# Transition Constants

# Frame thresholds
FRAMES_ON_THRESH = 2
FRAMES_OFF_THRESH = 12
GIVE_UP_THRESH = 200
SUPER_SAFE_KICKS = False

# Turning
# Value to stop spinning to ball and approach
BALL_BEARING_THRESH = 10
# Value to start spinning to ball
BALL_BEARING_OFF_THRESH = 17

BALL_SPIN_POSITION_THRESH = 10
USE_LOC_CHASE = False

# close approach/turn thresholds
BALL_CLOSE_DIST_THRESH = 42
BALL_CLOSE_TURN_BEARING_THRESH = 15
BALL_CLOSE_APPROACH_BEARING_THRESH = 5

BALL_POS_KICK_DIST_THRESH = 17.5
BALL_POS_KICK_BEARING_THRESH = 30
BALL_TURN_KICK_BEARING_THRESH = 40

BALL_KICK_DIST_THRESH = 18
BALL_KICK_BEARING_THRESH_LOWER = 12
BALL_KICK_BEARING_THRESH_UPPER = 38

FIND_BALL_SPIN_SPEED = 25.0
BALL_SPIN_SPEED = 15.0
BALL_SPIN_GAIN = 0.4
MIN_BALL_SPIN_MAGNITUDE = 2
Y_SPIN_SPEED = 0.8
X_SPEED_TO_BALL = 0
Y_SLOW_SPEED = 3

CLOSE_TURN_GAIN = 2.3
CLOSE_TURN_Y_GAIN = .6

APPROACH_X_GAIN = 0.22
APPROACH_Y_GAIN = 3.0

APPROACH_CLOSE_X_GAIN = 2.5
APPROACH_CLOSE_Y_GAIN = 0.2

POS_KICK_X_GAIN = 0.8
POS_KICK_Y_GAIN = 0.8
POS_KICK_TARGET_Y_GAIN = -3.0
POS_KICK_TARGET_X_GAIN = 0.5

# positionForKick() values
BALL_KICK_LEFT_Y_L = 14
BALL_KICK_LEFT_Y_R = 6
BALL_KICK_LEFT_X_CLOSE = 10
BALL_KICK_LEFT_X_FAR = 15

# Values to clip are approaching speed to
MAX_X_SPEED = 7.5
MIN_X_SPEED = -7.5

# Values for controlling the strafing
MAX_Y_SPEED = 3.0
MIN_Y_SPEED = -MAX_Y_SPEED
CHASE_Y_EPSILON = 0.75

# Keep track of what gait we're using
FAST_GAIT = "fastGait"
NORMAL_GAIT = "normalGait"
