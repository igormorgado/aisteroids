#!/bin/bash

for test in tests/bin/*
do
	[ -x "${test}" ] && ./${test}
done
