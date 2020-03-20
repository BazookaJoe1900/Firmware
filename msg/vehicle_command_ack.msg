uint64 timestamp		# time since system start (microseconds)

enum start VEHICLE_CMD_RESULT uint8
ACCEPTED = 0				# Command ACCEPTED and EXECUTED |
TEMPORARILY_REJECTED = 1	# Command TEMPORARY REJECTED/DENIED |
DENIED = 2					# Command PERMANENTLY DENIED |
UNSUPPORTED = 3				# Command UNKNOWN/UNSUPPORTED |
FAILED = 4					# Command executed, but failed |
IN_PROGRESS = 5				# Command being executed |
enum end

uint16 ARM_AUTH_DENIED_REASON_GENERIC = 0
uint16 ARM_AUTH_DENIED_REASON_NONE = 1
uint16 ARM_AUTH_DENIED_REASON_INVALID_WAYPOINT = 2
uint16 ARM_AUTH_DENIED_REASON_TIMEOUT = 3
uint16 ARM_AUTH_DENIED_REASON_AIRSPACE_IN_USE = 4
uint16 ARM_AUTH_DENIED_REASON_BAD_WEATHER = 5

uint8 ORB_QUEUE_LENGTH = 3

uint16 command
enum VEHICLE_CMD_RESULT result
bool from_external
uint8 result_param1
int32 result_param2
uint8 target_system
uint8 target_component
