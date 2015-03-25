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
#Install wget
RUN apt-get -y install wget
#Install SOLR
#RUN apt-get -y install solr-tomcat
ENV SOLR_VERSION 4.10.2
RUN mkdir -p /opt
RUN wget -nv http://www.mirrorservice.org/sites/ftp.apache.org/lucene/solr/$SOLR_VERSION/solr-$SOLR_VERSION.tgz -O /opt/solr-$SOLR_VERSION.tgz
RUN tar -C /opt --extract --file /opt/solr-$SOLR_VERSION.tgz
RUN mv /opt/solr-$SOLR_VERSION/example /opt/solr
RUN rm -rf /opt/solr-$SOLR_VERSION.tgz /opt/solr-$SOLR_VERSION
WORKDIR /opt/solr
#Install Munin
RUN apt-get -y install munin
#Install SSH
RUN apt-get -y install openssh-client
ADD ./data /opt/solr
CMD ["java", "-jar", "start.jar"]
