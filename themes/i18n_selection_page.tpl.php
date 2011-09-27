<?php
/**
 * @file
 * The template file of the module
 *
 * Variables used:
 *  - $data: array of links in each language enabled.
 *
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <?php print $head ?>
    <title><?php print $title ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
    <!--[if lt IE 7]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
  </head>
  <body class='i18n_selection_page'>
        <?php print $content; ?>
  <?php print $closure ?>
  </body>
</html>


