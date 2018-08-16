#!/bin/bash

VERSION=`cat /etc/contentosdversion`

if [[ "$IS_BROADCAST_NODE" ]]; then
  CONTENTOSD="/usr/local/contentosd-default/bin/contentosd"
elif [[ "$IS_AH_NODE" ]]; then
  CONTENTOSD="/usr/local/contentosd-default/bin/contentosd"
else
  CONTENTOSD="/usr/local/contentosd-full/bin/contentosd"
fi

chown -R contentosd:contentosd $HOME

# clean out data dir since it may be semi-persistent block storage on the ec2 with stale data
rm -rf $HOME/*

# seed nodes come from doc/seednodes.txt which is
# installed by docker into /etc/contentosd/seednodes.txt
SEED_NODES="$(cat /etc/contentosd/seednodes.txt | awk -F' ' '{print $1}')"

ARGS=""

# if user did not pass in any desired
# seed nodes, use the ones above:
if [[ -z "$CONTENTOSD_SEED_NODES" ]]; then
    for NODE in $SEED_NODES ; do
        ARGS+=" --seed-node=$NODE"
    done
fi

# if user did pass in desired seed nodes, use
# the ones the user specified:
if [[ ! -z "$CONTENTOSD_SEED_NODES" ]]; then
    for NODE in $CONTENTOSD_SEED_NODES ; do
        ARGS+=" --seed-node=$NODE"
    done
fi

NOW=`date +%s`
CONTENTOSD_FEED_START_TIME=`expr $NOW - 1209600`

if [[ ! "$IS_BROADCAST_NODE" ]]; then
  ARGS+=" --follow-start-feeds=$CONTENTOSD_FEED_START_TIME"
  ARGS+=" --disable-get-block"
fi

# overwrite local config with image one
if [[ "$IS_BROADCAST_NODE" ]]; then
  cp /etc/contentosd/config-for-broadcaster.ini $HOME/config.ini
elif [[ "$IS_AH_NODE" ]]; then
  cp /etc/contentosd/config-for-ahnode.ini $HOME/config.ini
else
  cp /etc/contentosd/fullnode.config.ini $HOME/config.ini
fi

chown contentosd:contentosd $HOME/config.ini

cd $HOME

mv /etc/nginx/nginx.conf /etc/nginx/nginx.original.conf
cp /etc/nginx/contentosd.nginx.conf /etc/nginx/nginx.conf

# let's get going
cp /etc/nginx/healthcheck.conf.template /etc/nginx/healthcheck.conf
echo server 127.0.0.1:8091\; >> /etc/nginx/healthcheck.conf
echo } >> /etc/nginx/healthcheck.conf
rm /etc/nginx/sites-enabled/default
cp /etc/nginx/healthcheck.conf /etc/nginx/sites-enabled/default
/etc/init.d/fcgiwrap restart
service nginx restart
exec chpst -ucontentosd \
    $CONTENTOSD \
        --rpc-endpoint=0.0.0.0:8091 \
        --p2p-endpoint=0.0.0.0:2001 \
        --data-dir=$HOME \
        $ARGS \
        $CONTENTOSD_EXTRA_OPTS \
        2>&1&
SAVED_PID=`pgrep -f p2p-endpoint`
echo $SAVED_PID >> /tmp/contentosdpid