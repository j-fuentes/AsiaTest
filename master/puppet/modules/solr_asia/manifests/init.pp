class solr_asia {
  $mysqlpackages = [ "mysql-server", "mysql-client", "libmysql-java" ]
  $javapackages = [ "openjdk-6-jre" ]
  $utils = [ "wget", "tar" ]

  exec { "update-apt": path => ['/usr/bin', '/usr/sbin', '/bin'], command => "apt-get update -y", refreshonly => true }

  # Utils installation
  package { $utils: ensure => "installed", require => Exec["update-apt"], }

  # Java installation
  package { $javapackages: ensure => "installed", require => Exec["update-apt"], }

  # Mysql packages
  package { $mysqlpackages: ensure => "installed", require => Exec["update-apt"], }

  # Solr installation
  file {'/tmp/solr-4.10.2.tgz':
    source => 'puppet:///modules/solr_asia/solr-4.10.2.tgz',
  }

  exec {"getSolr":
    path => ['/usr/bin', '/usr/sbin', '/bin'],
    command     => "tar xvzf ./solr-4.10.2.tgz && mv ./solr-4.10.2/example/* /opt/solr && rm -rf ./solr-4.10.2.tgz ./solr-4.10.2 ",
    cwd         => "/tmp",
    unless      => "ls /opt/solr/start.jar"
  }

  # Run Solr
  exec {"runSolr":
    path => ['/usr/bin', '/usr/sbin', '/bin'],
    command     => "java -jar start.jar &",
    cwd         => "/opt/solr",
    require => Exec["getSolr"],
  }

}
