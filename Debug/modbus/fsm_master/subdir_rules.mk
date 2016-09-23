################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
modbus/fsm_master/fsm_master.obj: ../modbus/fsm_master/fsm_master.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Engenharia/6 periodo/Microcontrolador/MBUS_mestre/modbus/fsm_master" --include_path="D:/Engenharia/6 periodo/Microcontrolador/MBUS_mestre/modbus/rtu" --include_path="D:/Engenharia/6 periodo/Microcontrolador/MBUS_mestre/modbus/port" --include_path="D:/Engenharia/6 periodo/Microcontrolador/MBUS_mestre/modbus/port" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="modbus/fsm_master/fsm_master.pp" --obj_directory="modbus/fsm_master" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


