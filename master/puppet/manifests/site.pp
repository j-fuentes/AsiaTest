node default { }

# hostname = mysql
node /^mysql.*$/ {
  include mysql_asia
}

# hostname = apache
node /^apache.*$/ {
  include apache_asia
}

# hostname = solr
node /^solr.*$/ {
  include solr_asia
}
