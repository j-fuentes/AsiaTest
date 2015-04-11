class mysql_asia {

  class { 'mysql::server':
    root_password => 'password'
  }

  mysql::db{ 'guiabcn':
    user     => 'imisql',
    password => 'TF3461fy1',
    host     => 'localhost',
    sql      => '/home/mysql/databases.sql'
    grant    => ['SELECT', 'UPDATE', 'INSERT'],
    ensure  => present,
    charset => 'utf8',
    require => Class['mysql::server']
  }

  class {'mysql::bindings' :
    php_enable => true
  }

}
