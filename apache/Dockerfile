FROM centos:6.6
MAINTAINER “Xavier Xicota” <xavixicota@gmail.com>
ENV container docker

#install Apache
RUN yum -y install httpd
RUN chkconfig --levels 235 httpd on

#Install PHP

RUN yum -y install php

#Install PHP MySQL Support

RUN yum -y install php-mysql

#Install Commmon Modules 

RUN yum -y install php-gd php-imap php-ldap php-odbc php-pear php-xml php-xmlrpc php-mbstring php-mcrypt php-mssql php-snmp php-soap php-tidy curl curl-devel

#Install APC
RUN yum -y install php-pecl-apc

#Restart HTTP 
RUN /etc/init.d/httpd restart

#Install JDK 1.6

RUN yum install java-1.6.0-openjdk

RUN yum install java-1.6.0-openjdk-devel

# How to install PHP memcached on CentOS 6.5
 
# Install dependencies
RUN yum install cyrus-sasl-devel zlib-devel gcc-c++
 
# Get the latest libmemcached
RUN wget https://launchpad.net/libmemcached/1.0/1.0.16/+download/libmemcached-1.0.16.tar.gz
RUN tar -xvf libmemcached-1.0.16.tar.gz
RUN cd libmemcached-1.0.16
 
# Compile and install liblmemcached with sasl disabled
RUN ./configure --disable-memcached-sasl
RUN make
RUN make install
 
# After memcached's dependencies has been satisfied, install it with pecl
RUN pecl install memcached
 
# Enable it for PHP
RUN echo "extension=memcached.so" > /etc/php.d/memcached.ini

#install FTP
RUN yum install vsftpd
RUN yum install ftp

RUN service vsftpd restart
RUN chkconfig vsftpd on



#MISS FTP CONFIG HERE

#Install SSH

RUN yum install openssh-server

RUN chkconfig sshd on
RUN service sshd restart

#MOVE CUSTOM FILES TO CONTAINER

ADD ./www/ /var/www/
ADD ./Apache2/ /etc/Apache2/


EXPOSE 80 88 21 22

CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]

