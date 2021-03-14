#!/bin/bash

for i in {1..100}; do
	./bin/gas-simulation &
	PID=$!
	echo $PID

	sleep 1

	kill -TERM $PID
done
