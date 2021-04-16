#! /bin/bash

UPLOAD_DIR="../RobotRMM"

TARGET_HOST="pi@raspberry-sena"
TARGET_DIR="~/."

rsync -avz -e ssh --delete $UPLOAD_DIR $TARGET_HOST:$TARGET_DIR --exclude="*.o" --exclude="*.a" --exclude="*.out" --exclude=".git/"

sh backup.sh
