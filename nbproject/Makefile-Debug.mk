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
	${OBJECTDIR}/ALGP.o \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Encryption.o \
	${OBJECTDIR}/Game/Area.o \
	${OBJECTDIR}/Game/Entitys/Entity.o \
	${OBJECTDIR}/Game/Entitys/Movable_entity.o \
	${OBJECTDIR}/Network/Connection.o \
	${OBJECTDIR}/Network/General.o \
	${OBJECTDIR}/Network/TCP_Connection.o \
	${OBJECTDIR}/Output.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/Tools.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lpthread -lgpgme -lsodium
CXXFLAGS=-lpthread -lgpgme -lsodium

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libALGP.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libALGP.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libALGP.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/ALGP.o: ALGP.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ALGP.o ALGP.cpp

${OBJECTDIR}/Client.o: Client.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Encryption.o: Encryption.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Encryption.o Encryption.cpp

${OBJECTDIR}/Game/Area.o: Game/Area.cpp
	${MKDIR} -p ${OBJECTDIR}/Game
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game/Area.o Game/Area.cpp

${OBJECTDIR}/Game/Entitys/Entity.o: Game/Entitys/Entity.cpp
	${MKDIR} -p ${OBJECTDIR}/Game/Entitys
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game/Entitys/Entity.o Game/Entitys/Entity.cpp

${OBJECTDIR}/Game/Entitys/Movable_entity.o: Game/Entitys/Movable_entity.cpp
	${MKDIR} -p ${OBJECTDIR}/Game/Entitys
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game/Entitys/Movable_entity.o Game/Entitys/Movable_entity.cpp

${OBJECTDIR}/Network/Connection.o: Network/Connection.cpp
	${MKDIR} -p ${OBJECTDIR}/Network
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Network/Connection.o Network/Connection.cpp

${OBJECTDIR}/Network/General.o: Network/General.cpp
	${MKDIR} -p ${OBJECTDIR}/Network
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Network/General.o Network/General.cpp

${OBJECTDIR}/Network/TCP_Connection.o: Network/TCP_Connection.cpp
	${MKDIR} -p ${OBJECTDIR}/Network
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Network/TCP_Connection.o Network/TCP_Connection.cpp

${OBJECTDIR}/Output.o: Output.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Output.o Output.cpp

${OBJECTDIR}/Server.o: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/Tools.o: Tools.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tools.o Tools.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
