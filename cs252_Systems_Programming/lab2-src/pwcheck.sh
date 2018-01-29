#!/bin/bash

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo


#Read in and set to a var
filecontents=$(cat $1)
strlength=${#filecontents}
#Test length
if [[ $strlength -lt 6 ||  $strlength -gt 32 ]]
then
  echo Error: Password length invalid.
  exit
fi
points=$strlength

#Adding symbol points
symbol=$(echo $filecontents | grep  [#$+%@] | wc -l)
let points=points+symbol*5

#Adding num char points
number=$(echo $filecontents | grep  [0-9] | wc -l)
let points=points+number*5

#Adding alpha char points
alpha=$(echo $filecontents | grep [a-zA-Z] | wc -l)
let points=points+alpha*5

#3-repeat number
repNum=$(echo $filecontents | grep '[0-9][0-9][0-9]' | wc -l)
let points=points-repNum*3

#3-repeat lowercase
repLow=$(echo $filecontents | grep '[a-z][a-z][a-z]' | wc -l)
let points=points-repLow*3

#3-repeat uppercase
repUp=$(echo $filecontents | grep '[A-Z][A-Z][A-Z]' | wc -l)
let points=points-repUp*3

#repeat alphanumeric
repAlphaNum=$(echo $filecontents | grep '\([[:alpha:]]\) *\1' | wc -l)
let points=points-repAlphaNum*10

echo Password Score: $points


