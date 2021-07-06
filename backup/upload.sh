#! /bin/bash

UPLOAD_DIR="/Users/sena2/git/RobotRMM"

TARGET_HOST="pi@192.168.12.133"
TARGET_DIR="~/."

rsync -avz -e ssh --delete $UPLOAD_DIR $TARGET_HOST:$TARGET_DIR --exclude="*.o" --exclude="*.a" --exclude="*.out" --exclude=".git/"

sh backup.sh
