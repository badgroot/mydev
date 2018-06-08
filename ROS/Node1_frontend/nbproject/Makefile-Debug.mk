#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/JsonReadWrite.o \
	${OBJECTDIR}/gui.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/modbus.o \
	${OBJECTDIR}/ros_talker.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lmodbus -lroscpp -lrosconsole -lrostime
CXXFLAGS=-lmodbus -lroscpp -lrosconsole -lrostime

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/opt/ros/kinetic/lib `pkg-config --libs gtkmm-3.0` -lroscpp  -lrosconsole -lrostime -ljsoncpp -lroscpp_serialization -lpthread  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk node1_frontend

node1_frontend: ${OBJECTFILES}
	g++ -o node1_frontend ${OBJECTFILES} ${LDLIBSOPTIONS} -I /opt/ros/kinetic/include

${OBJECTDIR}/JsonReadWrite.o: JsonReadWrite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/ros/kinetic/include `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/JsonReadWrite.o JsonReadWrite.cpp

${OBJECTDIR}/gui.o: gui.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/ros/kinetic/include `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui.o gui.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/ros/kinetic/include `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/modbus.o: modbus.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/ros/kinetic/include `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/modbus.o modbus.cpp

${OBJECTDIR}/ros_talker.o: ros_talker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/ros/kinetic/include `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ros_talker.o ros_talker.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} node1_frontend

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
