FROM centos:6.6
MAINTAINER Gonzalo Cabezas
RUN yum -y update
#RUN apt-get -y install rubygems
#RUN echo "gem: --no-ri --no-rdoc" > ~/.gemrc
#RUN gem install puppet librarian-puppet
#Install mySQL
RUN rpm -Uvh http://dev.mysql.com/get/mysql-community-release-el6-5.noarch.rpm
RUN yum -y install mysql-community-server
#RUN /etc/init.d/mysqld start
RUN chkconfig mysqld on
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
RUN mkdir /home/mysql
#VOLUME /home/AsiaTest/mysql:/home/datatest
ADD databases.sql /home/mysql/
ADD cargardb.sh /home/mysql/
RUN chmod -R 777 /home/mysql/cargardb.sh
EXPOSE 3306
CMD ["/usr/bin/mysqld_safe"]
