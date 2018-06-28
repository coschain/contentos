#!/bin/bash

VERSION=`cat /etc/contentosdversion`

# if the writer node dies by itself, kill runsv causing the container to exit
CONTENTOSD_PID=`pgrep -f p2p-endpoint`
if [[ ! $? -eq 0 ]]; then
  echo NOTIFYALERT! contentosdsync has quit unexpectedly, checking for coredump and then starting a new instance..
  sleep 30
  SAVED_PID=`cat /tmp/contentosdpid`
  if [[ -e /tmp/core.$SAVED_PID ]]; then
    gdb --batch --quiet -ex "thread apply all bt full" -ex "quit" /usr/local/contentosd-full/bin/contentosd /tmp/core.$SAVED_PID >> /tmp/stacktrace
    STACKTRACE=`cat /tmp/stacktrace`
    echo NOTIFYALERT! contentosdsync stacktrace from coredump:
    for ((i=0;i<${#STACKTRACE};i+=120)); do
      echo "${STACKTRACE:i:120}"
    done
    CORE_FILE_NAME=coredump-`date '+%Y%m%d-%H%M%S'`.$SAVED_PID
  fi
  RUN_SV_PID=`pgrep -f /etc/service/contentosd`
  kill -9 $RUN_SV_PID
fi

# check if we are synced, if so kill runsv causing the container to exit
# and ecs-agent will start a new container starting the process over
BLOCKCHAIN_TIME=$(
    curl --silent --max-time 20 \
        --data '{"id":39,"method":"get_dynamic_global_properties","params":[]}' \
        localhost:8090 | jq -r .result.time
)

if [[ ! -z "$BLOCKCHAIN_TIME" ]]; then
  BLOCKCHAIN_SECS=`date -d $BLOCKCHAIN_TIME +%s`
  CURRENT_SECS=`date +%s`

  # if we're within 10 seconds of current time, call it synced and begin the upload
  BLOCK_AGE=$((${CURRENT_SECS} - ${BLOCKCHAIN_SECS}))
  if [[ ${BLOCK_AGE} -le 10 ]]; then
    CONTENTOSD_PID=`pgrep -f p2p-endpoint`
    kill -SIGINT $CONTENTOSD_PID
    echo contentosdsync: waiting for contentosd to exit cleanly
    while [ -e /proc/$CONTENTOSD_PID ]; do sleep 0.1; done
    echo contentosdsync: starting a new blockchainstate upload operation
    cd ${COMPRESSPATH:-$HOME}
    echo contentosdsync: compressing blockchainstate...
    if [[ "$USE_RAMDISK" ]]; then
      tar vcf blockchain.tar.bz2 --use-compress-prog=pbzip2 -C $HOME blockchain -C /mnt/ramdisk blockchain
    else
      tar cf blockchain.tar.bz2 --use-compress-prog=pbzip2 -C $HOME blockchain
    fi
    if [[ ! $? -eq 0 ]]; then
      echo NOTIFYALERT! contentosdsync was unable to compress shared memory file, check the logs.
      exit 1
    fi
    if [[ "$IS_BROADCAST_NODE" ]]; then
      FILE_NAME=broadcast-$VERSION-`date '+%Y%m%d-%H%M%S'`.tar.bz2
    elif [[ "$IS_AH_NODE" ]]; then
      FILE_NAME=ahnode-$VERSION-`date '+%Y%m%d-%H%M%S'`.tar.bz2
    else
      FILE_NAME=blockchain-$VERSION-`date '+%Y%m%d-%H%M%S'`.tar.bz2
    fi

    # kill the container starting the process over again
    echo contentosdsync: stopping the container after a sync operation
    RUN_SV_PID=`pgrep -f /etc/service/contentosd`
    kill -9 $RUN_SV_PID
  fi
fi

# check on this every 60 seconds
sleep 60
