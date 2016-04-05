<div class="slack-messages">
  <?php foreach ($messages as $delta => $message) : ?>
    <div class="slack-message" id="slack-message-<?php print $delta; ?>">
      <?php if (!empty($message['time'])) : ?>
       <span class="message-time"><?php print $message['time']; ?></span>
      <?php endif; ?>
      <?php if (!empty($message['text'])) : ?>
        <span class="message-text"><?php print $message['text']; ?></span>
      <?php endif; ?>
    </div>
  <?php endforeach; ?>
</div>