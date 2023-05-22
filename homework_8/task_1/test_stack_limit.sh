#!/usr/bin/env bats
# @file      test_task_1.sh
# @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
#
# Copyright (c) 2020 Ignacio Vizzo, all rights reserved

stack_limit() {
  output=$(bin/stack_limit 2>&1)
  errno=$?
  echo "$output" | tail -n 4
  return $errno
}

@test "[task_1] Test Stack Limit" {
  echo "merda"
  run stack_limit
  # Capture segmentation fault
  [ "$status" -eq 139 ]

  # Check for the correct output
  [ "${lines[0]}" = "7800[KiB] Allocated in the stack" ]
  [ "${lines[1]}" = "7900[KiB] Allocated in the stack" ]
  [ "${lines[2]}" = "8000[KiB] Allocated in the stack" ]
  [ "${lines[3]}" = "8100[KiB] Allocated in the stack" ]
}
