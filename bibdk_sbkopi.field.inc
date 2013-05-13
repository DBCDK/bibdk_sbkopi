<?php

/**
 * Implements hook_field_formatter_info().
 */
function bibdk_sbkopi_field_formatter_info() {
  return array(
    'bibdk_sbkopi_link_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_sbkopi_link',
      ),     
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function bibdk_sbkopi_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  
  // sb copy service is for type 'Tidsskriftsartikel' only
  $type = $entity->getSubType();
  if ($type != 'Tidsskriftsartikel') {
    return;
  }

  foreach ($items as $delta => $item) {
    $element[$delta]['#markup'] = '<div class="bibdk-sb_kopi-replaceme" pid="'.$entity->id.'"></div>';
  }
  $element['#attached'] = array(
      'js' => array(drupal_get_path('module', 'bibdk_sbkopi') . '/js/ajaxGetCopyOptions.js'),
    );
  return $element;
}

