node default { }

# hostname = mysql
#node 'mysql.*' {
#  include mysql
#}

# hostname = apache
node 'apache.home' {
  include apache
}

# hostname = solr
#node 'solr.*' {
#  include solr
#}