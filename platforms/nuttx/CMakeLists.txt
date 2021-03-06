############################################################################
#
#   Copyright (c) 2017 PX4 Development Team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name PX4 nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

include(cygwin_cygpath)

set(NUTTX_DIR ${PX4_BINARY_DIR}/NuttX/nuttx)
set(NUTTX_APPS_DIR ${PX4_BINARY_DIR}/NuttX/apps)

add_executable(px4 ${PX4_SOURCE_DIR}/platforms/common/empty.c)
set(FW_NAME ${PX4_BOARD_VENDOR}_${PX4_BOARD_MODEL}_${PX4_BOARD_LABEL}.elf)
set_target_properties(px4 PROPERTIES OUTPUT_NAME ${FW_NAME})
add_dependencies(px4 git_nuttx nuttx_build)

get_property(module_libraries GLOBAL PROPERTY PX4_MODULE_LIBRARIES)

# build NuttX
add_subdirectory(NuttX ${PX4_BINARY_DIR}/NuttX)

set(nuttx_libs)
list(APPEND nuttx_libs
	nuttx_apps
	nuttx_arch
	nuttx_binfmt
	nuttx_c
	nuttx_configs
	nuttx_xx
	nuttx_drivers
	nuttx_fs
	nuttx_mm
	nuttx_sched
	)

if (CONFIG_NET)
	list(APPEND nuttx_libs nuttx_net)
	target_link_libraries(nuttx_fs INTERFACE nuttx_net)
endif()

file(RELATIVE_PATH PX4_BINARY_DIR_REL ${CMAKE_CURRENT_BINARY_DIR} ${PX4_BINARY_DIR})

# only in the cygwin environment: convert absolute linker script path to mixed windows (C:/...)
# because even relative linker script paths are different for linux, mac and windows
CYGPATH(PX4_BINARY_DIR PX4_BINARY_DIR_CYG)

if(POLICY CMP0079)
	cmake_policy(SET CMP0079 NEW)
endif()

target_link_libraries(nuttx_arch
	INTERFACE
		drivers_board
		drivers_boards_common
		drivers_boards_common_arch
		arch_hrt
)

target_link_libraries(nuttx_c INTERFACE nuttx_drivers)
target_link_libraries(nuttx_xx INTERFACE nuttx_c)

target_link_libraries(px4 PRIVATE

	-nostartfiles
	-nodefaultlibs
	-nostdlib
	-nostdinc++

	-fno-exceptions
	-fno-rtti

	-Wl,--script=${PX4_BINARY_DIR_CYG}/NuttX/nuttx-config/scripts/script.ld
	-Wl,-Map=${PX4_CONFIG}.map
	-Wl,--warn-common
	-Wl,--gc-sections

	-Wl,--start-group
		drivers_boards_common_arch
		${nuttx_libs}
	-Wl,--end-group

	m
	gcc
	)

target_link_libraries(px4 PRIVATE ${module_libraries})

if (config_romfs_root)
	add_subdirectory(${PX4_SOURCE_DIR}/ROMFS ${PX4_BINARY_DIR}/ROMFS)
	target_link_libraries(px4 PRIVATE romfs)
endif()

add_custom_command(OUTPUT ${PX4_BINARY_DIR_REL}/${PX4_BOARD}.bin
	COMMAND ${CMAKE_OBJCOPY} -O binary ${PX4_BINARY_DIR_REL}/${FW_NAME} ${PX4_BINARY_DIR_REL}/${PX4_BOARD}.bin
	DEPENDS px4
	)

# create .px4 with parameter and airframe metadata
if (TARGET parameters_xml AND TARGET airframes_xml)

	string(REPLACE ".elf" ".px4" fw_package ${PX4_BINARY_DIR}/${FW_NAME})

	add_custom_command(
		OUTPUT ${fw_package}
		COMMAND
			${PYTHON_EXECUTABLE} ${PX4_SOURCE_DIR}/Tools/px_mkfw.py
				--prototype ${PX4_SOURCE_DIR}/boards/${PX4_BOARD_VENDOR}/${PX4_BOARD_MODEL}/firmware.prototype
				--git_identity ${PX4_SOURCE_DIR}
				--parameter_xml ${PX4_BINARY_DIR}/parameters.xml
				--airframe_xml ${PX4_BINARY_DIR}/airframes.xml
				--image ${PX4_BINARY_DIR}/${PX4_BOARD}.bin > ${fw_package}
		DEPENDS
			${PX4_BINARY_DIR}/${PX4_BOARD}.bin
			airframes_xml
			parameters_xml
		COMMENT "Creating ${fw_package}"
		WORKING_DIRECTORY ${PX4_BINARY_DIR}
		)

	add_custom_target(px4_package ALL DEPENDS ${fw_package})

	# upload helper
	# create upload target helper if NuttX USB CDCACM is present
	if (CONFIG_CDCACM)
		include(upload)
	endif()

endif()

# print weak symbols
add_custom_target(weak_symbols
	COMMAND ${CMAKE_NM} $<TARGET_FILE:px4> | ${GREP} " w " | cat
	DEPENDS px4
	VERBATIM
	USES_TERMINAL
	)


# debugger helpers
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Debug/gdbinit.in ${PX4_BINARY_DIR}/.gdbinit)

add_custom_target(debug
	COMMAND ${GDB} -iex 'set auto-load safe-path ${PX4_BINARY_DIR}' $<TARGET_FILE:px4>
	DEPENDS px4 ${PX4_BINARY_DIR}/.gdbinit
	WORKING_DIRECTORY ${PX4_BINARY_DIR}
	USES_TERMINAL
	)

include(blackmagic)
include(jlink)
include(profile)
include(stack_check)
