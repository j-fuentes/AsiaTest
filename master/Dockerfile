FROM centos:6.6
MAINTAINER Jose Fuentes <jfuentes@wtelecom.es>

ADD puppet.conf /etc/puppet/puppet.conf
RUN yum -y update && yum -y install ruby wget tar
RUN rpm -ivh http://yum.puppetlabs.com/puppetlabs-release-el-6.noarch.rpm && yum install -y puppet-server
CMD /usr/bin/ruby /usr/bin/puppet master --no-daemonize --debug
