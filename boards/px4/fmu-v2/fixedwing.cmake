
px4_add_board(
	PLATFORM nuttx
	VENDOR px4
	MODEL fmu-v2
	LABEL fixedwing
	TOOLCHAIN arm-none-eabi
	ARCHITECTURE cortex-m4
	ROMFSROOT px4fmu_common
	IO px4_io-v2_default
	#TESTING
	#UAVCAN_INTERFACES 2

	SERIAL_PORTS
		GPS1:/dev/ttyS3
		TEL1:/dev/ttyS1
		TEL2:/dev/ttyS2
		TEL4:/dev/ttyS6

	DRIVERS
		adc
		#barometer # all available barometer drivers
		barometer/ms5611
		batt_smbus
		camera_capture
		camera_trigger
		differential_pressure # all available differential pressure drivers
		distance_sensor # all available distance sensor drivers
		gps
		imu/l3gd20
		imu/lsm303d
		imu/mpu6000
		#imu/mpu9250
		lights/rgbled
		#magnetometer # all available magnetometer drivers
		magnetometer/hmc5883
		px4fmu
		px4io
		#telemetry # all available telemetry drivers
		telemetry/iridiumsbd
		tone_alarm
		#uavcan

	MODULES
		camera_feedback
		commander
		dataman
		ekf2
		events
		fw_att_control
		fw_pos_control_l1
		land_detector
		load_mon
		logger
		mavlink
		navigator
		sensors
		vmount
		airspeed_selector

	SYSTEMCMDS
		bl_update
		#config
		#dumpfile
		#esc_calib
		hardfault_log
		i2cdetect
		#led_control
		mixer
		#motor_ramp
		#motor_test
		mtd
		#nshterm
		param
		perf
		pwm
		reboot
		#sd_bench
		top
		#topic_listener
		tune_control
		usb_connected
		ver
	)
