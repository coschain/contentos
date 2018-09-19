#!/bin/sh

basepath=$(cd `dirname $0`; pwd)
srcroot=$basepath/../../
vsconfig_proj=$srcroot/.vscode/
vsconfig_src=$basepath/vscode_build_json/



if [ x$1 == x"up" ]; then
	cp -f $vsconfig_proj/c_cpp_properties.json $vsconfig_src
	cp -f $vsconfig_proj/launch.json $vsconfig_src
	cp -f $vsconfig_proj/settings.json $vsconfig_src
	cp -f $vsconfig_proj/tasks.json $vsconfig_src
else
	cp -f $vsconfig_src/c_cpp_properties.json $vsconfig_proj
	cp -f $vsconfig_src/launch.json $vsconfig_proj
	cp -f $vsconfig_src/settings.json $vsconfig_proj
	cp -f $vsconfig_src/tasks.json $vsconfig_proj
fi

