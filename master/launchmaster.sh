#!/bin/bash

if [ $1 = "-b" ]
  then
  docker build -t jfuentes/puppetmaster .
fi
docker run -ti -v $(pwd)/puppet/modules:/etc/puppet/modules -v $(pwd)/puppet/manifests:/etc/puppet/manifests --name puppetmaster --hostname master jfuentes/puppetmaster  /usr/bin/ruby /usr/bin/puppet master --no-daemonize --debug
