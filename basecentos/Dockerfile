FROM centos:6.6
MAINTAINER Jose Fuentes <jfuentes@wtelecom.es>

ADD puppet /tmp/puppet-docker
ADD puppet.conf /etc/puppet/puppet.conf
RUN yum -y update && yum -y install ruby
RUN rpm -ivh http://yum.puppetlabs.com/puppetlabs-release-el-6.noarch.rpm && yum install -y puppet

CMD /usr/bin/ruby /usr/bin/puppet agent --no-daemonize --debug
