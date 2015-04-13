class mysql_asia {

#  include mysql

  $override_options = {
    'mysqld' => {
      'bind_address' => '0.0.0.0',
    }
  }

  class { 'mysql::server':
    root_password => 'password',
    override_options => $override_options
  }

  file {'/tmp/databases.sql':
    ensure => file,
    source => 'puppet:///modules/mysql_asia/databases.sql',
  }

  mysql::db{ 'guiabcn':
    user     => 'imisql',
    password => 'TF3461fy1',
    host     => '0.0.0.0',
    sql      => '/home/mysql/databases.sql',
    grant    => ['SELECT', 'UPDATE', 'INSERT'],
    ensure  => present,
    charset => 'utf8',
    require => Class['mysql::server']
  }

  class {'mysql::bindings' :
    php_enable => true
  }

}
