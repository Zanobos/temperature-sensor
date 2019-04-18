program_path=$1

if [ $# -ne 1 ]; then echo "Usage: $0 program_path"; exit 4; fi;
EXIT_FAILURE=1
#First Test -> no argument
./$program_path > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;
#Second Test -> only operation mode
./$program_path 1 > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;
#Third Test -> operation mode and alert_mode ON, but no temperatures
./$program_path 1 1 > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;
#Fourth Test -> operation mode and alert_mode ON, but only 1 temperature passed
./$program_path 1 1 160 > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;
#Fifth Test -> operation mode and alert_mode ON, but temperature t_high out of range
./$program_path 1 1 160 30 > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;
#Sixt Test -> operation mode and alert_mode ON, but temperature t_low out of range
./$program_path 1 1 100 -130 > nul
if [ $? -eq $EXIT_FAILURE ]; then echo "TEST PASSED"; else echo "TEST FAILED"; fi;