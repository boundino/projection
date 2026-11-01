#!/bin/bash 

make raa_fitndraw.exe || exit 1

./raa_fitndraw.exe datas/vns/OOD0_withflow_alldatasets_cent0to10.root datas/templates.root raa_cent0to10
