#!/usr/bin/env bats
# @file      test_task_2.sh
# @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
#
# Copyright (c) 2020 Ignacio Vizzo, all rights reserved

@test "[task_2] Check bin/task_2 existance" {
  run test -e bin/task_2
  (( status == 0 ))
}

@test "[task_2] Check 0  inputs" {
  run bin/task_2
  (( status == 1 ))
}


@test "[task_2] Check 1  inputs" {
  run bin/task_2
  (( status == 1 ))
}

@test "[task_2] Check 2  inputs" {
  run bin/task_2 0.txt 0.txt
  (( status == 0 ))
}

@test "[task_2] Check 2+ inputs" {
  run bin/task_2 0 0 0
  (( status == 1 ))
}

@test "[task_2] Check input arguments format" {
  run bin/task_2 err.txt err.txt
  (( status == 1 ))
}

@test "[task_2] Check supported extensions" {
  run bin/task_2 00.tRt 00.txt
  run bin/task_2 00.txt 00.Txt
  (( status == 1 ))
}

@test "[task_2] Check mean value, both .txt files" {
  output_150=$(./bin/task_2 100.txt 200.txt |tail -1)
  output_163=$(./bin/task_2 101.txt 225.txt |tail -1)

  (( status == 0 ))
  [ $output_150 -eq 150 ]
  [ $output_163 -eq 163 ]
}

@test "[task_2] Check sum value, both .png files" {
  output_300=$(./bin/task_2 100.png 200.png |tail -1)
  output_66=$(./bin/task_2 11.png 55.png |tail -1)

  (( status == 0 ))
  [ $output_300 -eq 300 ]
  [ $output_66 -eq 66 ]
}

@test "[task_2] Check modulo division [.txt|.png] files" {
  output_1=$(./bin/task_2 7.txt 3.png |tail -1)
  output_2=$(./bin/task_2 14.txt 3.png |tail -1)

  (( status == 0 ))
  [ $output_1 -eq 1 ]
  [ $output_2 -eq 2 ]
}


