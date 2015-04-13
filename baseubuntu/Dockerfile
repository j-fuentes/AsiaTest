FROM ubuntu:12.04
MAINTAINER Jose Fuentes <jfuentes@wtelecom.es>

RUN apt-get -y update && apt-get -y install ruby
RUN apt-get install -y puppet

ADD puppet /tmp/puppet-docker
ADD puppet.conf /etc/puppet/puppet.conf

CMD /usr/bin/ruby /usr/bin/puppet agent --no-daemonize --debug
