/**
 * javascript to get sb_kopi options
 * script attached in bibdk_sbkopi.field.inc::bibdk_sbkopi_field_formatter_view
 **/
(function ($) {
    Drupal.addCopyLink = function (result) {
        alert(result.pid);
       // $('.bibdk-sb_kopi-replaceme[pid=' + result.pid + ']').text(result.result);
    },
    
    Drupal.bibdkKopiOptions =  function(element) {
        var pid = $(element).attr('pid');
        // Call ajax 
        var request = $.ajax({
            url:Drupal.settings.basePath + 'sbkopi/ajax',
            type:'POST',
            data:{
                pid:pid
            },
            dataType:'json',
            success:Drupal.addCopyLink
        }); 
    }
    
    /** Get copy options via ajax */
    Drupal.behaviors.sbKopi = {
        attach:function (context) {
            $('.bibdk-sb_kopi-replaceme', context).each(function (i, element) {
                Drupal.bibdkKopiOptions(element);
            });
        },
        detach:function (context) {}
    };

})(jQuery);

