#!/bin/bash

make tests

for test in tests/bin/*
do
	if [ -x "${test}" ]
	then
		./${test}
	fi
done
