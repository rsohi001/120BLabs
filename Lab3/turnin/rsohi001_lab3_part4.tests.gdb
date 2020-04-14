# Test file for "Lab3"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x0F => PORTB: 0x00, PORTC: 0xF0 "
# Set inputs
setPINA 0x0F
# Continue for several ticks
continue 2
# Set expect values
expectPORTB 0x00
expectPORTC 0xF0
# Check pass/fail
checkResult

# Add tests below
test "PINA: 0xFA => PORTB:0x0F PORTC: 0xA0"
setPINA 0xFA
continue 2
expectPORTB 0x0F
expectPORTC 0xA0
checkResult

test "PINA: 0xBB => PORTB:0x0B PORTC: 0xB0"
setPINA 0xBB
continue 2
expectPORTB 0x0B
expectPORTC 0xB0
checkResult

test "PINA: 0x14 => PORTB:0x01 PORTC: 0x40"
setPINA 0x14
continue 2
expectPORTB 0x01
expectPORTC 0x40
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n