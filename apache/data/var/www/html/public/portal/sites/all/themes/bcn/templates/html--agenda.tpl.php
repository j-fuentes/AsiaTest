<!DOCTYPE html>
<html<?php $rdf_namespaces; ?>>
<head>
  <?php print $head; 
  $base_url = $GLOBALS['base_url'];
  ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no" />
  <link rel="Shortcut Icon" type="image/ico" href="http://www.bcn.cat/favicon.ico" />

</head>
<body class="<?php print $classes; ?>" <?php print $attributes; ?>>
<?php if(module_exists("bcn_brand")) print bcn_brand_get_html(); ?>

  <div id="skip">
    <a href="#main-menu"><?php print t('Jump to Navigation'); ?></a>
  </div>
  
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>