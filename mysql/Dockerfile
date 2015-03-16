FROM centos:6.6
MAINTAINER Gonzalo Cabezas
RUN yum -y update
#RUN apt-get -y install rubygems
#RUN echo "gem: --no-ri --no-rdoc" > ~/.gemrc
#RUN gem install puppet librarian-puppet
#Install mySQL
RUN yum -y install mysql55w mysql55w-server
RUN service mysqld start
#Install Java 1.6
RUN yum -y install java-1.6.0-openjdk
RUN yum -y install java-1.6.0-openjdk-devel
#Install FTP
RUN yum -y install vsftpd
RUN yum -y install ftp
RUN service vsftpd restart
RUN chkconfig vsftpd on
#Install Munin
#RUN apt-get -y install munin
#Install SSH
RUN yum -y install openssh-server
RUN chkconfig sshd on
RUN service sshd restart

VOLUME /var/lib/mysql
EXPOSE 3306
