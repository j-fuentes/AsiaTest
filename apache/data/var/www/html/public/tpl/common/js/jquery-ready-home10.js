var idioma = $("html").attr("lang");

function SetMapaAmplia(){

/*******************************************/
/* Scroll + Amplia mapa                     */
/*******************************************/
   
   /** GENERACIO VARIABLES MAPA **/  
     
   var mapaWidth = $('#mapa').width();   
   var ResultatsWidth = $('#llista-resultats').width();
        
   if (mapaWidth!=ResultatsWidth) {              
        $("#content-mapa").append('<img id="amplia" src="/tpl/common/img/bt-amplia.gif" alt="Ampliar el mapa" />');
   } else {
        $("#content-mapa").append('<img id="amplia" src="/tpl/common/img/bt-redueix.gif" alt="Reduir el mapa" />');
        $('#mapa:not(.stop)').toggleClass("stop");        
   }
  	
   $("img#amplia").css("cursor","pointer");	
  	
   $("img#amplia").click(function() {		
		if($('#mapa').width()!=$('#llista-resultats').width()){            
		    $('#mapa').toggleClass("stop");
			$("#mapa.stop img#amplia").attr("src","/tpl/common/img/bt-redueix.gif");			
			// scroll top del body, per posicionar. 
			$('html, body').animate({scrollTop: $("#capsalera").height()+45}, 500, function(){
				 //$("#map").attr("src", src_iframe+"&z=" + (valor_zoom+2));
			});	
			// Ampliem el mapa a z=valor_zoom+5		   	
			$("#mapa, #llista-resultats").animate({ width: 685 }, 500);	
			$("#map").width(685);
			loadmapSearch(null,null,null,null);				
		} else {		    
			$(this).attr("src","/tpl/common/img/bt-amplia.gif");						
			$('#mapa').toggleClass("stop");			
			//$("#map").attr("src", src_iframe+"&z=" + (valor_zoom-2));			
			$("#mapa").animate({ width: 269 }, 1000);			
			$("#llista-resultats").animate({ width: 388 }, 1000);
			$("#map").width(269);					
			loadmapSearch(null,null,null,null);				
		}				
	});
			
 $("#mapa.stop img#amplia").live("mouseover", function(){
			$(this).attr("src","/tpl/common/img/bt-redueixover.gif");	
	}).live("mouseout",function(){
		$(this).attr("src","/tpl/common/img/bt-redueix.gif");
	});
	
$("#mapa:not(.stop) img#amplia").live("mouseover", function(){
			$(this).attr("src","/tpl/common/img/bt-ampliaover.gif");	
	}).live("mouseout",function(){
		$(this).attr("src","/tpl/common/img/bt-amplia.gif");
	});
	
/***** END MAPA amplia*******/

}

function getScriptGMapMarkers(responseText){    
    if (responseText != undefined && responseText.indexOf('<script id="markers" type="text/javascript">') != -1){
		var txt = responseText.substring(responseText.search('<script id="markers" type="text/javascript">'));		
		return txt.substring(0,txt.search('</script>')+9).replace(" </script>", "</script>");
	} else {
		return '';
	}
}

function addClickHandlers() {

  
   $('#mapa').scrollFollow();
   //home
   $('#activitats-destacades .paginador a, #mnudest a', this).click(function() {  
     //$('#activitats-destacades').load(this.href+'&ajax=1 #activitats-destacades > *',addClickHandlers); 
        var mapaWidth = $('#mapa').width();
        var ResultatsWidth = $('#llista-resultats').width();
     
       $('#activitats-destacades').load(encodeURI(this.href)+'&ajax=1 #activitats-destacades > *',function(response,p2,p3){
   		
		    $('#mapa').width(mapaWidth);
   		   	$('#map').width(mapaWidth);
   		   	$('#llista-resultats').width(ResultatsWidth);
   		    //console.log(getScriptGMapMarkers(response));
   		    $('#activitats-destacades').append(getScriptGMapMarkers(response));
   		    //alert(getScriptGMapMarkers(response));
   		    //igualarCaixes();
			 		  
   		});
		
   		if (typeof(window.history.pushState) == 'function') {
	    		window.history.pushState(null, this.href, this.href);
			} 
   		  
      return false;
   }); 
  
   //search
   $('#col-0 a,#col-1 .paginador a,#col-1 .sort,#col-1 .filtres a', this).click(function() {  
        var mapaWidth = $('#mapa').width();
        var ResultatsWidth = $('#llista-resultats').width();
   		//$('#ajx-search').load(this.href+'&ajax=1 #ajx-search > *',addClickHandlers);   	    
   		$('#ajx-search').load(encodeURI(this.href)+'&ajax=1 #ajx-search > *',function(response,p2,p3){   		     
   		   	$('#mapa').width(mapaWidth);
   		   	$('#map').width(mapaWidth);
   		   	$('#llista-resultats').width(ResultatsWidth); 	    
   		    $('#ajx-search').append($(getScriptGMapMarkers(response)));   		  
   		}); 
   	   if (typeof(window.history.pushState) == 'function') {
	    		window.history.pushState(null, this.href, this.href);
			} 
		 
       return false;
   });   
   $('#accions select', this).change(function() {    
     //$('#ajx-search').load($(this).attr('href')+'&nr='+this.value+'&ajax=1 #ajx-search > *',addClickHandlers);
        var mapaWidth = $('#mapa').width();
        var ResultatsWidth = $('#llista-resultats').width();
     	$('#ajx-search').load(encodeURI($(this).attr('href'))+'&nr='+this.value+'&ajax=1 #ajx-search > *',function(response,p2,p3){
     	    $('#mapa').width(mapaWidth);
   		   	$('#map').width(mapaWidth);
   		   	$('#llista-resultats').width(ResultatsWidth);
   		    $('#ajx-search').append($(getScriptGMapMarkers(response)));   		  
   		});  
   });    
   SetMapaAmplia();
   
   // detall
    $('#related .next a, #related .prev a', this).click(function() {     
       $('#related').load(encodeURI(this.href)+'&ajax=related #related > *',function(response,p2,p3){
   		    $('#related').append($(getScriptGMapMarkers(response)));   		  
   		});     
      return false;
   });    
   
}


$(document).ready(addClickHandlers);

$(document).ready(function(){
igualarCaixes();

// visualizamos div no accessibles
//$("#div-cerca-av").hide();
//$('#cerca-avansada').show();
//fin visualizamos div no accessibles
// valores por defecto

/*	if ($('#q').attr("value")!=""){
				 	$('.input-q input').attr('value', $('#q').attr("value"));
				}
*/

$('.default-value').each(function() {
    var default_value = this.value;    
    $(this).css('color', '#828181'); // this could be in the style sheet instead
    $(this).focus(function() {
        if(this.value == default_value) {
            this.value = '';            
            $(this).css('color', '#000');
			
        }
		$('#div-cerca-av .input-q input').attr("value", $(this).attr("value"));
    });    
    $(this).blur(function() {
        if(this.value == '') {
            $(this).css('color', '#828181');         
            this.value = default_value;
        }
    });
    
    $(this).parents('form').submit(function() {
  $(this).find('.default-value').each(function() {
    var input = $(this);
    if (input.val() == default_value) {
      input.val('');
    }
  })
});
//fin valores por defecto    
    
});

initDynamicOptionLists(); //init barri listbox
/*******************************************/
/* accions formulari cerca                 */
/*******************************************/

$("#cerca-avansada").css("cursor","pointer");

// Posar enllaç cerca avançada
var btLiteral="";
switch(idioma){
	case 'es':
	btLiteral="Búsqueda avanzada";
	break;
	case 'en':
	btLiteral="Advanced search";
	break;
	default:
	btLiteral="Cerca avançada";
	break;
}

$("form#frm-cerca ul").append('<li id="cerca-avansada">'+btLiteral+'</li>')



		$("#cerca-avansada").click(function(){
											
				/* agafer informacio del input central */
				
			
				$("#directori-home").slideToggle("slow");							
 		  		$("#div-cerca-av").slideToggle("slow",function(){	
				
				 //try{$("#mapa").scrollFollow();}catch(e){}										  
			     /* desactivar / activar formularios*/	
				
				$("#div-cerca-av:hidden").each(function(){
						//$("#frm-cerca input,#frm-cerca select").attr("disabled","");
						$("#frm-cerca input,#frm-cerca select").removeAttr("disabled" );
						$("#frm-cerca input.cerca").removeClass("inactiu");
						$("#frm-cerca li:not('#cerca-avansada')").animate({ opacity:1 }, 500 );	
						$("#frm-cerca li#cerca-avansada").removeClass("desplegat");
				});	
							
				$("#div-cerca-av:visible").each(function(){
					$("#frm-cerca input,#frm-cerca select").attr("disabled","disabled");
					$("#frm-cerca input.cerca").addClass("inactiu");					
					$("#frm-cerca li:not('#cerca-avansada')").animate({ opacity: 0.20 }, 500 ); 
					$("#frm-cerca li#cerca-avansada").addClass("desplegat");
					
				});
	       });
		});

// FI Formulari cerca		    
/*******************************************/
/* Tabs del formulari                      */
/*******************************************/
//$('#div-cerca-av div').hide();

$('.tabform, .tabmviewed, .tabdetall').hide();
$('#tab-totalaguia, #div-mvistos, #div-informacio, #div-pestanes').show();
//$('#div-pestanes ul li:first').addClass('active');
$('#mapadetall, #mapastreet').hide();
$('#changemap, #mapaplanol').show();

$('#changemap a').click(function(){
	$('#changemap a').removeClass('active');
	$(this).addClass('active'); 
	var currentTab = $(this).attr('href'); 
	$('#mapaplanol, #mapadetall, #mapastreet').hide();	
	$(currentTab).show();
	if (currentTab=='#mapadetall' || currentTab=='#mapastreet' ) refreshMap();	
	return false;
});


/* Pestanyes cerca avançada */
//$('#div-cerca-av').addClass("js");
$('#div-cerca-av h3:first a').addClass("active");
$('#div-cerca-av h3 a').click(function(){
	$('#div-cerca-av h3 a').removeClass('active');
	$(this).parent('h3').children('a').addClass('active'); 
	var currentTab = $(this).attr('href'); 
	$('.tabform').hide();
	$(currentTab).show();
	return false;
});

$('#mviewed h2').css('position','absolute');
$('#mviewed h2').css('top','0px');
$('#mvalorats').css('margin-left','121px');
$('#mvalorats').removeClass('active');

$('#mviewed h2 a').click(function(){
	$('#mviewed h2').removeClass('active');
	$(this).parent().addClass('active'); 
	var currentTab = $(this).attr('href'); 
	$('.tabmviewed').hide();
	$(currentTab).show();
	return false;
});

/* Pestanyes detall */

if($("h3#esdeveniments").length==0){
	$("h3#aprop").addClass("posicio");
}

$('#contenidor-pestanes').addClass("js");
$('#contenidor-pestanes h3:first a').addClass("active");
$('#contenidor-pestanes h3 a').click(function(){
	$('#contenidor-pestanes h3 a').removeClass('active');
	$(this).parent('h3').children('a').addClass('active'); 
	var currentTab = $(this).attr('href'); 
	$('.tabdetall').hide();
	$(currentTab).show();
	return false;
});


// FI TABS
/* Fancy box per iframe
*******************************************/

$("div.directori a.iframe").attr('href',$("div.directori a.iframe").attr('href')+'&ajax=1');
$("div.agenda a.iframe").attr('href',$("div.agenda a.iframe").attr('href')+'&ajax=1');

$("div.directori a.iframe, div.agenda a.iframe").fancybox({
'padding': 31,
'transitionIn' : 'elastic',
'transitionOut' : 'elastic',
'speedIn' : 800,
'speedOut' : 200,
'width' : 866,
'height' : 476,
'overlayColor' : '#000',
'overlayOpacity': .85,
'scrolling' : 'yes',
'href' : this.href,
'titleShow' : true,
'onStart' : function(){$("object").css("visibility","hidden");},
'onClosed' : function(){$("object").css("visibility","visible");}
}); 

/*
 * Ajax loading image
 *****************************************/

$("#spinner").bind("ajaxSend", function() {
	$(this).show();
}).bind("ajaxStop", function() {  
    $(document).ready(addClickHandlers);   
	$(this).hide();		
	if ($("#col-detall-0").length == 0){
		if ($("#contenidor-home").length > 0){		    		
		$('html,body').animate({ scrollTop: $("#contenidor-home").offset().top }, { duration: 'slow', easing: 'swing',complete: function(){igualarCaixes();}});
        		
		}
		if ($("#contenidor-2").length > 0){
		$('html,body').animate({ scrollTop: $("#contenidor-2").offset().top }, { duration: 'slow', easing: 'swing'});
		}
	}
	//$("html.body").animate($("#contenidor-home-2").offset().top, 500);
}).bind("ajaxError", function() {
	$(this).hide();
}).bind('ajaxComplete', function (event, request, settings) {
    _gaq.push(['_trackPageview', settings.url]);
});





/*
End Ajax loading image
*****************************************/
/* Binding AddThis to ajaxstop*/
$("#ajx-search").ajaxStop(function(){
      $.getScript('http://s7.addthis.com/js/250/addthis_widget.js#pubid=ra-4d71141009b7bb91&domready=1', function() {
            addthis.init();
            addthis.toolbox(".addthis_toolbox");
        });    
       });	

       
/****/
// DatePicker del formulari
$('#divDate').DatePicker({
	format: 'Y-m-d',
	flat: true,
	date: $('#formDate').val()? $('#formDate').val(): new Date(),
	current: new Date(new Date().setMonth((new Date()).getMonth() + 1)),
	calendars: 2,
	mode: 'range',
	lastSel: false,
	starts: 1,
	lang : document.documentElement.lang,
	onBeforeShow: function(){
		$('#formDate').DatePickerSetDate($('#formDate').val(), true);		
	},
	onChange: function(formated, dates){
		$('#formDate').val(formated);
	}
});
$('#divDateContainer').hide();

$('#formDate').focus(function() {   
    var div = $('#divDateContainer').slideDown("slow");
    $(document).bind('focusin #divDateContainer click #divDateContainer',function(e) {
        if ($(e.target).closest('#divDateContainer, #formDate').length) return;
        $(document).unbind('#divDateContainer');
        //div.fadeOut('medium');
        div.slideUp("slow"); 
    });
});

$('#divDateContainer a.select').click(function(){
	$('#divDateContainer').slideUp("slow");
	return false;
});
/*******************************************/
});
/*******************************************/
/* Igualar caixes de la home               */
/*******************************************/
function igualarCaixes(){
//alert("igualar");

var total1=$('#act-dest-1').innerHeight();
var total2=$('#act-dest-2').innerHeight();

$('#act-dest-1').children(".bloc").children('.contenidor').each(function () {	
		if (total1 > $(this).height()){
			resultat= total1-$(this).innerHeight()-20;		
            $(this).children("div:not('.data')").height( $(this).children("div:not('.data')").innerHeight()+resultat);
      	}
})
$('#act-dest-2').children(".bloc").children('.contenidor').each(function () {
			if (total2 > $(this).height()){
				resultat= total2-$(this).innerHeight()-20;
            	$(this).children("div:not('.data')").height( $(this).children("div:not('.data')").innerHeight()+resultat);
			}
})
	//$('#act-dest-1').children(".bloc").children('.contenidor').height($('#act-dest-2').height()-23);
	//$('#act-dest-2').children(".bloc").children('.contenidor').height($('#act-dest-2').height());
}

