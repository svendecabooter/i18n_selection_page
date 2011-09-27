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
<div class="i18n_selection_page_body">
  <div class="i18n_selection_page_body_inner">
    <p>Hello,</p>

    <p>You are coming from <?php print $from_link_html; ?></p>

    <p>You should go to:</p>
    <?php print $to_links_html; ?>
  </div>
</div>