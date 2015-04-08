class apache {
  $phpmodules = [ "php", "php-mysql", "php-gd", "php-imap", "php-ldap", "php-odbc", "php-pear", "php-xml", "php-xmlrpc", "php-mbstring", "php-mcrypt", "php-mssql", "php-snmp", "php-soap", "php-tidy", "curl", "curl-devel", "php-pecl-apc"]
  $javapackages = [ "java-1.6.0-openjdk", "java-1.6.0-openjdk-devel" ]
  $dependencies = [ "cyrus-sasl-devel", "zlib-devel", "gcc-c++" ]
  $libmemcaches = [ "memcached.x86_64", "php-pecl-memcached.x86_64" ]
  $otherpackages = [ "wget", "tar", "vsftpd", "ftp", "openssh-server" ]

  package { $phpmodules: ensure => "installed" }
  package { $javapackages: ensure => "installed" }
  package { $dependencies: ensure => "installed" }
  package { $libmemcaches: ensure => "installed" }
  package { $otherpackages: ensure => "installed" }

  # Get libmemcached
  file {"/tmp/libmemcached-1.0.16.tar.gz":
    owner   => "root",
    group   => "root",
    mode    => 0775,
    ensure  => present,
    content => download_content('https://launchpad.net/libmemcached/1.0/1.0.16/+download/libmemcached-1.0.16.tar.gz'),
    notify  => Exec["unpackLibMemcached"]
  }

  # Unpack libmemcached
  exec {"unpackLibMemcached":
    command     => "tar -xvf /tmp/libmemcached-1.0.16.tar.gz && chown -R root:root /tmp/libmemcached-1.0.16",
    cwd         => "/tmp",
    refreshonly => true,
    notify      => Exec["installLibMemcached"]
  }

  # Instal libmemcached
  exec { "installLibMemcached":
    cwd             => "/tmp/libmemcached-1.0.16",
    command     => "/tmp/libmemcached-1.0.16/configure --disable-memcached-sasl && make && make install",
    logoutput   => true,
    refreshonly => true,
    notify      => Exec["installMemcached"]
    }

  # Install memcached with pecl
  exec { "installMemcached":
      cwd             => "/tmp/libmemcached-1.0.16",
      command     => "pecl install memcached",
      logoutput   => true,
      refreshonly => true,
      notify      => Exec["enableMemcachedForPHP"]
      }

  # Enable memcached for PHP
  exec { "enableMemcachedForPHP":
      command     => "echo 'extension=memcached.so' > /etc/php.d/memcached.ini",
      logoutput   => true,
      refreshonly => true
      }

  # Apache and common modules from pupept core
  include apache
  include apache::mod::php
  include apache::mod::cgi
  include apache::mod::userdir
  include apache::mod::disk_cache
  include apache::mod::proxy_http

  # ASIA virtualhost
  apache::vhost { 'asia.es':
    port    => 80,
    docroot => '/var/www/asia',
  }

}

# Reference: https://github.com/puppetlabs/puppetlabs-apache
