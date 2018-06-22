#!/bin/bash

echo /tmp/core | tee /proc/sys/kernel/core_pattern
ulimit -c unlimited

# if we're not using PaaS mode then start contentosd traditionally with sv to control it
if [[ ! "$USE_PAAS" ]]; then
  mkdir -p /etc/service/contentosd
  cp /usr/local/bin/contentos-sv-run.sh /etc/service/contentosd/run
  chmod +x /etc/service/contentosd/run
  runsv /etc/service/contentosd
else
  /usr/local/bin/startpaascontentosd.sh
fi
