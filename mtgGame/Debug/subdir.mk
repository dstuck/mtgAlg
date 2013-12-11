################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BasicGame.cpp \
../Battlefield.cpp \
../Card.cpp \
../Card_Creature.cpp \
../Card_Land.cpp \
../Controller.cpp \
../Exile.cpp \
../Graveyard.cpp \
../Hand.cpp \
../HumanController.cpp \
../Library.cpp \
../Location.cpp \
../MatClass.cpp \
../MetaHandler.cpp \
../Planeswalker.cpp \
../Playable.cpp \
../Player.cpp \
../SBA_Destroyed.cpp \
../SBA_Milled.cpp \
../SBA_NoLife.cpp \
../StateBasedAction.cpp \
../StateBasedActionQueue.cpp \
../TestController.cpp \
../TestControllerv2.cpp 

C_UPPER_SRCS += \
../Random.C \
../main.C 

OBJS += \
./BasicGame.o \
./Battlefield.o \
./Card.o \
./Card_Creature.o \
./Card_Land.o \
./Controller.o \
./Exile.o \
./Graveyard.o \
./Hand.o \
./HumanController.o \
./Library.o \
./Location.o \
./MatClass.o \
./MetaHandler.o \
./Planeswalker.o \
./Playable.o \
./Player.o \
./Random.o \
./SBA_Destroyed.o \
./SBA_Milled.o \
./SBA_NoLife.o \
./StateBasedAction.o \
./StateBasedActionQueue.o \
./TestController.o \
./TestControllerv2.o \
./main.o 

CPP_DEPS += \
./BasicGame.d \
./Battlefield.d \
./Card.d \
./Card_Creature.d \
./Card_Land.d \
./Controller.d \
./Exile.d \
./Graveyard.d \
./Hand.d \
./HumanController.d \
./Library.d \
./Location.d \
./MatClass.d \
./MetaHandler.d \
./Planeswalker.d \
./Playable.d \
./Player.d \
./SBA_Destroyed.d \
./SBA_Milled.d \
./SBA_NoLife.d \
./StateBasedAction.d \
./StateBasedActionQueue.d \
./TestController.d \
./TestControllerv2.d 

C_UPPER_DEPS += \
./Random.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/dstuck/projects/mtgAlg/mtgGame/headers" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards/creatures" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards/land" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.C
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/dstuck/projects/mtgAlg/mtgGame/headers" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards/creatures" -I"/Users/dstuck/projects/mtgAlg/mtgGame/cards/land" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


