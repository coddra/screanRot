#!/bin/bash

MESSAGE_LIST="lock unlock toggle-lock reset"

while [[ "$1" != "" ]]; do
    if echo $MESSAGE_LIST | grep -w "$1" &> /dev/null; then
        echo "$1" > /tmp/screenrotator
    fi
    shift 1
done
