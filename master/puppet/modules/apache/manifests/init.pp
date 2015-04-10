class apache {


  $phpmodules = [ "php", "php-mysql", "php-gd", "php-imap", "php-ldap", "php-odbc", "php-pear", "php-xml", "php-xmlrpc", "php-mbstring", "php-mcrypt", "php-mssql", "php-snmp", "php-soap", "php-tidy", "curl", "php-pecl-apc"]
  $javapackages = [ "java-1.6.0-openjdk", "java-1.6.0-openjdk-devel" ]
  $dependencies = [ "cyrus-sasl-devel", "zlib-devel", "gcc-c++" ]
  $libmemcaches = [ "memcached.x86_64" ]
  $otherpackages = [ "wget", "tar", "vsftpd", "ftp", "openssh-server" ]

  package { $otherpackages: ensure => "installed", require => Exec["update-yum"] }


  # yum update
  exec { "update-yum": path => ['/usr/bin', '/usr/sbin', '/bin'], command => "yum update -y", }

  # install curl-devel. This bypass yum list checking that returns !0 and makes puppet stop the installation of this package.
  exec { "install-curl-devel": path => ['/usr/bin', '/usr/sbin', '/bin'], command => "yum install -y curl-devel", require => Exec["update-yum"], unless => "yum list installed libcurl-devel",}

  # install php-pecl-memcached.x86_64. This bypass yum list checking that returns !0 and makes puppet stop the installation of this package.
  exec { "install-php-pecl-memcached.x86_64": path => ['/usr/bin', '/usr/sbin', '/bin'], command => "yum install -y php-pecl-memcached.x86_64", require => [ Exec["epelrepo"], Exec["update-yum"] ], unless => "yum list installed php-pecl-memcached.x86_64", }

  # add EPEL and REMI repo (needed to install some modules)
  exec { "epelrepo":
        path => ['/usr/bin', '/usr/sbin', '/bin'], cwd => "/tmp",
        command => "wget http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm && wget http://rpms.famillecollet.com/enterprise/remi-release-6.rpm && rpm -Uvh remi-release-6*.rpm epel-release-6*.rpm && yum update -y",
        unless => "ls /tmp/remi-release-6*.rpm",
      }

  # install apache
  package { 'httpd': ensure => "installed", require => Exec["update-yum"],}
  # install php modules
  package { $phpmodules: ensure => "installed", require => [ Exec["epelrepo"], Exec["update-yum"] ], }

  # install java
  package { $javapackages: ensure => "installed", require => Exec["update-yum"], }

  # install libmemcached stuff
  package { $dependencies: ensure => "installed", require => Exec["update-yum"], }
  package { $libmemcaches: ensure => "installed", require => Exec["update-yum"], }

   # Unpack libmemcached
   exec {"unpackLibMemcached":
     path => ['/usr/bin', '/usr/sbin', '/bin'],
     command     => "wget https://launchpad.net/libmemcached/1.0/1.0.16/+download/libmemcached-1.0.16.tar.gz && tar -xvf /tmp/libmemcached-1.0.16.tar.gz && chown -R root:root /tmp/libmemcached-1.0.16",
     cwd         => "/tmp",
     refreshonly => true,
     notify      => Exec["installLibMemcached"]
   }

   # Instal libmemcached
   exec { "installLibMemcached":
     cwd             => "/tmp/libmemcached-1.0.16",
     path => ['/usr/bin', '/usr/sbin', '/bin'],
     command     => "/tmp/libmemcached-1.0.16/configure --disable-memcached-sasl && make && make install",
     logoutput   => true,
     refreshonly => true,
     notify      => Exec["installMemcached"],
     }

   # Install memcached with pecl
   exec { "installMemcached":
       cwd             => "/tmp/libmemcached-1.0.16",
       path => ['/usr/bin', '/usr/sbin', '/bin'],
       command     => "pecl install memcached",
       logoutput   => true,
       refreshonly => true,
       notify      => Exec["enableMemcachedForPHP"]
      }

   # Enable memcached for PHP
   exec { "enableMemcachedForPHP":
       path => ['/usr/bin', '/usr/sbin', '/bin'],
       command     => "echo 'extension=memcached.so' > /etc/php.d/memcached.ini",
       logoutput   => true,
       refreshonly => true
       }

  # Apache configuration
  file {'/etc/httpd/conf/httpd.conf':
    ensure => file,
    source => "puppet:///modules/apache/etc/httpd/conf/httpd.conf",
    require => Package['httpd'],
  }

  file {'/etc/httpd/conf/magic':
    ensure => file,
    source => 'puppet:///modules/apache/etc/httpd/conf/magic',
    require => Package['httpd'],
  }

  file {'/etc/httpd/conf.d/munin.conf':
    ensure => file,
    source => 'puppet:///modules/apache/etc/httpd/conf.d/munin.conf',
    require => Package['httpd'],
  }

  file {'/etc/httpd/conf.d/php.conf':
    ensure => file,
    source => 'puppet:///modules/apache/etc/httpd/conf.d/php.conf',
    require => Package['httpd'],
  }

  file {'/etc/httpd/conf.d/welcome.conf':
    ensure => file,
    source => 'puppet:///modules/apache/etc/httpd/conf.d/welcome.conf',
    require => Package['httpd'],
  }

  file {'/etc/munin/':
    ensure => directory,
  }

  file {'/etc/munin/munin.conf':
    ensure => file,
    source => 'puppet:///modules/apache/etc/munin/munin.conf',
    require => File["/etc/munin"],
  }

  # Services
  service { 'httpd':
    ensure => running,
    enable => true,
  }

  service { 'sshd':
    ensure => running,
    enable => true,
  }

  service { 'vsftpd':
    ensure => running,
    enable => true,
  }

}
