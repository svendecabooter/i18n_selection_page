<p>Hello,</p>
<p>You are coming from <?php print $data['from_link']; ?></p>
<p>You should go to:</p>
<ul>
  <?php foreach ($data['links'] as $links): ?>
  <li class="first"><?php print $links;?></li>
  <?php endforeach ?>
</ul>
