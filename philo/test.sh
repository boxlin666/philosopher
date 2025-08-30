#!/bin/bash

# A simple automated test script for the philosophers project

# --- Configuration ---
PROG_NAME="philo"
MAKE_CMD="make re"
TIMEOUT_SECONDS=5 # Default timeout for tests that should survive

# --- Colors for reporting ---
GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
RESET="\033[0m"

# --- Test counters ---
passed_tests=0
total_tests=0

# ==============================================================================
# 1. COMPILE THE PROGRAM
# ==============================================================================
echo -e "${BLUE}--- Compiling the program ---${RESET}"
$MAKE_CMD
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed. Aborting tests.${RESET}"
    exit 1
fi
echo -e "${GREEN}Compilation successful.${RESET}\n"

# ==============================================================================
# 2. HELPER FUNCTION TO RUN A SINGLE TEST
# ==============================================================================
# Usage: run_test "description" "expected_outcome" "timeout" "philo_args"
run_test() {
    local description="$1"
    local expected_outcome="$2" # Can be "DEATH", "SURVIVE", "EAT_ENOUGH", "ARG_ERROR"
    local timeout_duration="$3"
    local philo_args="$4"

    ((total_tests++))
    echo -n "Test: $description ... "

    # Create a temporary file to capture the output
    OUTPUT_FILE=$(mktemp)
    
    # Run the program with a timeout. Capture stdout & stderr.
    # The `timeout` command is crucial. It kills the process if it runs too long.
    timeout $timeout_duration ./$PROG_NAME $philo_args > "$OUTPUT_FILE" 2>&1
    local exit_code=$?

    local result="FAIL"

    # --- Validation Logic ---
    case "$expected_outcome" in
        "DEATH")
            # We expect the program to print "died"
            if grep -q "died" "$OUTPUT_FILE"; then
                result="PASS"
            fi
            ;;
        "SURVIVE")
            # We expect the program NOT to print "died".
            # It should either finish or be killed by the timeout.
            if ! grep -q "died" "$OUTPUT_FILE"; then
                result="PASS"
            fi
            ;;
        "EAT_ENOUGH")
            # We expect it to finish without deaths AND meet the meal count.
            # This is a more complex check, here's a simple version.
            if ! grep -q "died" "$OUTPUT_FILE" && [ $exit_code -ne 124 ]; then
                 # 124 is the exit code for timeout, success means it finished on its own
                result="PASS"
            fi
            ;;
        "ARG_ERROR")
            # We expect the program to exit with a non-zero status code before timeout
            if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ]; then
                result="PASS"
            fi
            ;;
    esac

    # --- Reporting ---
    if [ "$result" == "PASS" ]; then
        echo -e "${GREEN}[OK]${RESET}"
        ((passed_tests++))
    else
        echo -e "${RED}[KO]${RESET}"
        echo "    - Args: ./$PROG_NAME $philo_args"
        echo "    - Expected: $expected_outcome"
        echo "    - Output:"
        # Indent the output for readability
        sed 's/^/        /' "$OUTPUT_FILE"
    fi

    # Cleanup
    rm "$OUTPUT_FILE"
}

# ==============================================================================
# 3. DEFINE AND RUN ALL TEST CASES
# ==============================================================================
echo -e "${BLUE}--- Running Tests ---${RESET}"

# --- Argument Validation Tests ---
run_test "Invalid number of arguments" "ARG_ERROR" 1 "4 800 200"
#run_test "Invalid number of arguments" "ARG_ERROR" 1 "4 800 200 7 9"
run_test "Non-numeric argument"        "ARG_ERROR" 1 "4 800 200 abc"
#run_test "Negative number of arguments""ARG_ERROR" 1 "5 -10 200 200"
run_test "Zero philosophers"           "ARG_ERROR" 1 "0 800 200 200"
run_test "Zero time_to_eat"            "ARG_ERROR" 1 "5 800 000 200"

# --- Edge Case & Death Logic Tests ---
run_test "1 philosopher must die"      "DEATH"   3 "1 800 200 200"
run_test "Guaranteed death"            "DEATH"   2 "4 300 200 200"
run_test "Guaranteed death"            "DEATH"   2 "4 300 400 200"
run_test "Guaranteed death"            "DEATH"   2 "4 300 200 400"
run_test "Standard run should survive" "SURVIVE" $TIMEOUT_SECONDS "4 410 200 200"
run_test "Extreme survival test"       "SURVIVE" $TIMEOUT_SECONDS "3 7 2 2"

# --- Stress Tests ---
run_test "Stress test with 200 philos should survive" "SURVIVE" 10 "200 800 200 200"
run_test "Rapid test with small times should survive" "SURVIVE" 10 "4 60 5 5"
run_test "Rapid test with small times should survive" "SURVIVE" 10 "4 400 10 380"

# --- Optional Part: Meal Count Tests ---
run_test "Meal count of 0 should exit immediately" "EAT_ENOUGH" 2 "5 800 200 200 0"
run_test "Meal count of 7 should finish successfully" "EAT_ENOUGH" 10 "5 800 200 200 7"
run_test "Meal count of 50 should finish successfully" "EAT_ENOUGH" 10 "4 210 100 100 50"

# Add more of your specific test cases here...

echo ""

# ==============================================================================
# 4. FINAL SUMMARY
# ==============================================================================
echo -e "${BLUE}--- Test Summary ---${RESET}"
if [ "$passed_tests" -eq "$total_tests" ]; then
    echo -e "${GREEN}All $total_tests tests passed! Great job!${RESET}"
else
    echo -e "${RED}$passed_tests / $total_tests tests passed.${RESET}"
fi