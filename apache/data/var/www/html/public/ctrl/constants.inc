<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
* Constants Initialization.
*@package Init_Public
**/
ini_set('error_reporting', 0);
@ini_set('display_errors','Off');
/**
*Language Cookie Name
**/
define("_CkLANG","mxidioma1");
/**
*Cookie state Name
**/
define("_CkSTATE","state1");
/**
*xml file of the layout page and navigation rules
**/
define("_NAVFILE","nav2");
define("_NAVMOBILE","navmobile");
/**
*xml file of the layout page and navigation rules for printing
**/
define("_NAVPRT","navprt");
/**
*Content folder - xml files in
**/
define("_DirHTMLS","content/");
/**
*Dir de javascripts y vbscripts
**/
define("_DirSCRIPTS","jscripts/");
/**
*Dir php blocks
**/
define("_DirBLOCKS","blocs/");
/**
*Template directory and main xsl file of the template page
**/
define("_TPLDIR","tpl/");
define("_THEME_DIR","guiabcn/");
define("_CANALS","escoles,dsvprod,esports");
/**
*Directorio donde están los ficheros de idiomas
**/
define("_DirLANGS",_TPLDIR._THEME_DIR."langs/");
define("_XMLOUTPUT2FILE",false);
define("_DEFAULT_LANG",'ca');
define("_PERMALINKS",true);
define("_CRYPT_LINKS",0);

//*********************************************************************************
require_once("ctrl/load.inc");
//*********************************************************************************
/************ SOLR *************************/

/* Whether or not to run in secure mode */
define('SOLR_SECURE', false);

/* HTTP Port to connection */
define('SOLR_SERVER_PORT', ((SOLR_SECURE) ? 8443 : 8080));

/* HTTP Basic Authentication Username */
define('SOLR_SERVER_USERNAME', 'admin');

/* HTTP Basic Authentication password */
define('SOLR_SERVER_PASSWORD', 'changeit');

/* HTTP connection timeout */
/* This is maximum time in seconds allowed for the http data transfer operation. Default value is 30 seconds */
define('SOLR_SERVER_TIMEOUT', 10);

/* File name to a PEM-formatted private key + private certificate (concatenated in that order) */
define('SOLR_SSL_CERT', 'certs/combo.pem');

/* File name to a PEM-formatted private certificate only */
define('SOLR_SSL_CERT_ONLY', 'certs/solr.crt');

/* File name to a PEM-formatted private key */
define('SOLR_SSL_KEY', 'certs/solr.key');

/* Password for PEM-formatted private key file */
define('SOLR_SSL_KEYPASSWORD', 'StrongAndSecurePassword');

/* Name of file holding one or more CA certificates to verify peer with*/
define('SOLR_SSL_CAINFO', 'certs/cacert.crt');

/* Name of directory holding multiple CA certificates to verify peer with */
define('SOLR_SSL_CAPATH', 'certs/');

/* GOOGLE MAPS */

//define('_GMAP_KEY',constant('_GMAP_KEY_'.strtoupper($_SERVER["SERVER_NAME"])));
define('_GMAP_LAT', 41.38713);
define('_GMAP_LNG', 2.170159);
define('_GMAP_LEVEL', 13);

/* Images Aj. Server */
define('_URL_SERVER_IMG', 'http://w10.bcn.cat/APPS/asiw/ObtenerImagen?vId=2&eId=');

/* IP excluded for counters */
define('_IP_EXCLUDED', '212.15.224.70');

?>