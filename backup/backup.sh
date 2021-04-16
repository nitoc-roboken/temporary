#! /bin/bash

#　バックアップする対象のディレクトリ
TARGET_DIR="../RobotRMM"

# バックアップ先の親ディレクトリ
BASEDIR="backups"
mkdir -p $BASEDIR

# 直近のバックアップのディレクトリ名
LATESTBKUP=$(ls $BASEDIR | grep backup- | tail -n 1)
CREATEBACKUP="backups/backup-$(date +%Y%m%d-%H%M%S)"

# 差分バックアップ作成
rsync -avh --link-dest="../$LATESTBKUP" $TARGET_DIR $CREATEBACKUP --exclude=".git/" --exclude="*.o" --exclude="*.a" --exclude="*.out"

#　リードオンリー化
chmod -R -w $CREATEBACKUP