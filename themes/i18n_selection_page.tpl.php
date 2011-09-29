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
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <?php print $head ?>
    <title><?php print $title ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class='i18n_selection_page'>
        <?php print $content; ?>
  </body>
</html>


