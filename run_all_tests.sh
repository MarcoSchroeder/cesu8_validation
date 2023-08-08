#!/bin/bash

# Navigate to the build directory
cd ./build

# List of tests to execute
tests=(
    "cesu8_validation_test_scalar"
    "cesu8_validation_test_sse"
    "cesu8_validation_test_avx"
    "cesu8_stats_test"
)

# Loop through the tests and execute them
for test in "${tests[@]}"; do
    echo "Running test: $test"
    ./"$test"
    if [ $? -eq 0 ]; then
        echo "Test $test passed"
    else
        echo "Test $test failed"
    fi
    echo ""
done

# Return to the root directory
cd ..
