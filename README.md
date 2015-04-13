# Puppetized AsiaTest

## 1 Description

This fork substitutes specific docker images for each service with generic docker base images equipped with puppet agent.

A puppet master can be deployed in another container and it will command the setup of the service nodes using the recipes stored in puppet scripts.

## 2 Status

- Puppet master container: __Running__
- Generic puppet agents containers: __Running and being commanded by master__
- Apache container: __Up and running.__
- Mysql container: __Up and running.__
- Solr container: __ON GOING.__

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


## 4 Notes

- '/master/puppet/modules/mysql_asia/files/database.sql' must exists but it is not uploaded because it is too heavy.
