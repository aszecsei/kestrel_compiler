#!/bin/bash

##### Constants

TITLE="Compiler Script"

##### Functions

function compile_assembly
{
	echo 'Compiling ' "$srcFile" ' to ' "$outFile" '...'
	as "$srcFile" -o "$outFile"
}

function link_assembly
{
	echo "Linking " "$outFile" "..."
	gcc "$outFile" -o "$execName"
}

##### Main

execName=""
srcFile=""

while [ "$1" != "" ]; do
	case $1 in
		-f | --file)	shift
				srcFile=$1
				;;
		-o | --output)	shift
				execName=$1
				;;
		* )		srcFile=$1
	esac
	shift
done

if [ "$srcFile" = "" ]; then
	echo "Error: Must supply source file"
	exit 1
fi

outFile="${srcFile%%.*}.o"
if [ "$execName" = "" ]; then
	execName="${srcFile%%.*}"
fi

compile_assembly
link_assembly
