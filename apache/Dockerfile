FROM ubuntu:12.04
MAINTAINER Xavier Xicota
RUN apt-get -y update

# UnComment to install Puppet on Ubuntu
#RUN apt-get -y install rubygems
#RUN echo "gem: --no-ri --no-rdoc" > ~/.gemrc
#RUN gem install puppet librarian-puppet

#Install Apache
RUN apt-get -y install apache2

# APACHE CONF
#/etc/apache2/apache2.conf
#/etc/apache2/mods-enabled
#/etc/apache2/sites-enabled 
#/etc/apache2/conf.d.

#INSTALL PHP APC

RUN apt-get -y install php5 libapache2-mod-php5
RUN apt-get -y install libpcre3-dev
RUN apt-get -y install php-pear
RUN apt-get -y install php5-dev
RUN apt-get -y install make
RUN apt-get -y install apache2-prefork-dev

# ADD extension=apc.so on php.ini

#RUN sed -i ‘$a extension=apc.so’ /etc/php5/apache2/php.ini

RUN service apache2 restart

#Install Memcached

RUN apt-get install -y mysql-server php5-mysql php5 php5-memcached memcached

#Install Java 1.6
RUN apt-get -y install openjdk-6-jre

#Install FTP
RUN apt-get -y install vsftpd

#Install Munin
RUN apt-get -y install munin
#Install SSH
RUN apt-get -y install openssh-client

EXPOSE 80 88 21 22

CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]

