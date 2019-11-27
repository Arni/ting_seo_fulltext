<?php
/**
 * @file
 * Renders a parsed data-well fulltext XML document as content.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ting fulltext object'),
  'description' => t('Fulltext display of ting object docdook relation in a object view.'),
  'single' => TRUE,
  'content_types' => array('fulltext'),
  'render callback' => 'ting_seo_fulltext_type_render',
  'category' => t('Ting'),
);

/**
 * Render callback function.
 */
function ting_seo_fulltext_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $object = menu_get_object('ting_object', 2);

  $rel_id = NULL;
  foreach ($object->reply->getRelations() as $rel) {
    if (isset($rel->getObject()->reply) && in_array('docbook', $rel->getObject()->getTingObject()->getFormatsAvailable())) {
      //file_put_contents("/var/www/drupal7vm/drupal/debug/full6.txt", print_r($rel->uri, TRUE), FILE_APPEND);
      $rel_id = $rel->uri;
    }
  }
  if (isset($rel_id)) {
    drupal_add_js(drupal_get_path('module', 'ting_seo_fulltext') . '/js/ting-seo-fulltext.js');
    drupal_add_js(array('tingSeoFulltext' => array('url' => '/ting/fulltext/ajax/' . $rel_id)), 'setting');
    $block->content = '<div id="ting-seo-fulltext"></div>';
  }

  return $block;
}

/**
 * Plugin settings form.
 */
function ting_fulltext_seo_content_type_edit_form($form, &$form_state) {
  return $form;
}
