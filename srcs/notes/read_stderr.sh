#!/bin/bash
echo "Type something for stderr:" >&2
read line <&2
echo "You typed (from stderr): $line"

