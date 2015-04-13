# Puppetized AsiaTest

## 1 Description

This fork substitutes specific docker images for each service with generic docker base images equipped with puppet agent.

A puppet master can be deployed in another container and it will command the setup of the service nodes using the recipes stored in puppet scripts.

## 2 Status

- Puppet master container: __Running__
- Generic puppet agents containers: __Running and being commanded by master__
- Apache container: __Up and running.__
- Mysql container: __Up and running.__
- Solr container: __Up and running.__

## 3 Deploy instructions

### 3.1 Run puppet master
- Go to the `master` directory: `cd ./master`
- Execute the launcher script. The first time, use the option `-b` to build the container: `./launchmaster.sh -b`

#### 3.1.1 Certificates signing
Puppet master denies to configure agents by default. In order to allow the master to command an agent, you have to explicit sign the agent certificate.
- Get a bash console in the agent container: `docker exec -ti <container name> bash`
- Force the agent to ask the master: `puppet agent --test`
- Get a bash console in the puppet master container: `docker exec -ti puppetmaster bash`
- List not-signed certificates: `puppet cert list`. It must return a list of agents that tries to connect with the master.
- Sign the desired agents certificates: `puppet cert sign <agent hostname.domain>`


### 3.2 Deploy the application
- In the root directory: `docker-compose up`
> You may want to change in `docker-compose.yml` the port mapping between containers and the host machine.


## 4 Additional and important notes

- `/master/puppet/modules/mysql_asia/files/database.sql` must exists but it is not uploaded because it is too heavy.
- Before deploying the _solr_ node, download `http://www.mirrorservice.org/sites/ftp.apache.org/lucene/solr/4.10.2/solr-4.10.2.tgz` and place it in `/master/puppet/modules/solr_asia/files/solr-4.10.2.tgz`. This is not included because it weights too much. Before it was downloaded in by the puppet agent itselt, but it took soo much and sometimes it failed.

## 5 Suggested improvements
- Independent container for storage volumes: deploy dedicated containers for each 'storage', i.e. a container for mysql storage, a container for the website files. This way, we could have "stateless" containers running the applications servers: httpd, mysqld, vsftpd. That application containers would mount the storage volume from the others.

- It could be better to specify the apache configuration in the puppet script instead of in the .conf files.

- It could be interesting to configure the servers bind addresses to the address that is in the docker internal network

- In order to speed up the deploy, we could create docker images of the container when puppet finalized the configuration. New instances could be launched from this images.
