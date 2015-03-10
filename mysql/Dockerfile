FROM ubuntu:12.04
MAINTAINER Gonzalo Cabezas
RUN apt-get -y update
#RUN apt-get -y install rubygems
#RUN echo "gem: --no-ri --no-rdoc" > ~/.gemrc
#RUN gem install puppet librarian-puppet
#Install mySQL
RUN apt-get -y install mysql-server
RUN apt-get -y install mysql-client
RUN apt-get -y install libmysql-java
#Install Java 1.6
RUN apt-get -y install openjdk-6-jre
#Install FTP
RUN apt-get -y install vsftpd
#Install Munin
RUN apt-get -y install munin
#Install SSH
RUN apt-get -y install openssh-client

VOLUME /var/lib/mysql
EXPOSE 3306
