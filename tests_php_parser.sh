#!/bin/bash

cd tests
for s in test_*.php; do php $s > a_$s.html; firefox a_$s.html; done;
cd ..
