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
<p>Hello,</p>
<p>You are coming from <?php print $data['from_link']; ?></p>
<p>You should go to:</p>
<?php print $data['links_html']; ?>
