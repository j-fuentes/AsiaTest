# Puppetized AsiaTest

## Description

This fork substitutes specific docker images for each service with generic docker base images equipped with puppet agent.

A puppet master can be deployed in another container and it will command the setup of the service nodes using the recipes stored in puppet scripts.

## Status

- Puppet master container: __Running__
- Generic puppet agents containers: __Running and being commanded by master__
- Apache container: __Running and receiving configuration from master. Puppet fails when inyecting '/etc/munin/munin.conf' into agent.__
- Mysql container: __ON GOING.__
- Solr container: __ON GOING.__
