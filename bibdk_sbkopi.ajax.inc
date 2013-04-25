<?php

function bibdk_sbkopi_ajax_get_options() {
  
  // get pid from request
 // var_dump($_REQUEST);
  $result = bibdk_sbkopi_ajax_openorder_request($_REQUEST['pid']);
 // var_dump($result);
 // die();
  
  $data['result'] = $result;
  $data['pid'] = $_REQUEST['pid'];
  /*  if (!isset($result)){
    $data['error'] = t('no_recommendations');
    }
    else {
    $data['list'] = bibdk_adhl_get_list($result);
    } */
  drupal_json_output($data);
  // @TODO do a request to openorder
}

function bibdk_sbkopi_ajax_openorder_request($pid) {
  
  $xml = bibdk_openorder_do_checkArticleDeliveryRequest($pid);
  echo $xml;
  
  return bibdk_sbkopi_ajax_parse_response($json);
  
  }

function bibdk_sbkopi_ajax_parse_response($xml) {
  // @TODO implement
  var_dump($xml);
  return $xml;
} 

