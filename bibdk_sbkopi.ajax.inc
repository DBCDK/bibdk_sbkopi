<?php

function bibdk_sbkopi_ajax_get_options() {
  $result = bibdk_sbkopi_ajax_openorder_request($_REQUEST['pid']);
  $data['pid'] = $_REQUEST['pid'];
  $data['link'] = $result;

  drupal_json_output($data);
}

function bibdk_sbkopi_ajax_openorder_request($pid) {
  $xml = bibdk_openorder_do_checkArticleDeliveryRequest($pid);
  return bibdk_sbkopi_ajax_parse_response($xml, $pid);
}

function bibdk_sbkopi_ajax_parse_response($xml, $pid) {
  $xpath = _bibdk_sbkopi_set_xpath($xml);
  if ($xpath === FALSE) {
    return 'error';
  }

  //var_dump($xml);
  // get articleDeliveryPossible
  $query = '//ns:articleDeliveryPossible';
  $nodelist = $xpath->query($query);
  $possible = $nodelist->item(0)->nodeValue;

// get articleDirect
  $query = '//ns:articleDirect';
  $nodelist = $xpath->query($query);
  $deliver = $nodelist->item(0)->nodeValue;

  // var_dump($deliver);
  // var_dump($possible);

  if ($possible) {
    $result = _bibdk_sbkopi_make_link($deliver, $pid);
  }
  else {
    return 'error';
  }
  return $result;
}

function _bibdk_sbkopi_make_link($method, $pid) {
  // two methods postal (print), electronic (e-copy) 
  switch ($method) {
    case 'postal' :
      $label = t('order_printed_copy');
      return _bibdk_sb_kopi_get_link($pid, $label, 'PAY');
    case 'electronic' :
      $label = t('order_electronic_copy');
      return _bibdk_sb_kopi_get_link($pid, $label, 'FREE');
    default :
      return 'error';
  }
}

function _bibdk_sb_kopi_get_link($pid, $label, $type) {
  return '<a href="' . base_path() . 'reservation?ids=' . $pid . '&bestil_kopi='.$type.'" class="bibdk-popup-link" rel="reservation">' . $label . '</a>';
}

function _bibdk_sbkopi_set_xpath($xml) {
  $dom = new DomDocument();
  if (!@$dom->loadXML($xml)) {
    return FALSE;
  }
  $xpath = new DomXPATH($dom);
  $xpath->registerNamespace('ns', 'http://oss.dbc.dk/ns/openorder');
  return $xpath;
}

