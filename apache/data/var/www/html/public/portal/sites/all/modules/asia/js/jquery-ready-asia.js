// JavaScript Document

(function ($){

$(document).ready(function(){
							   
	
	$('#llistat-resultats.amb-mapa').css('width',Drupal.settings.list_amplada+'px');
	
	$('#mapadetall, #mapastreet').hide();
	
	$('#changemap, #mapaplanol').show();

    
	/* llistat */
	
	$("#accions select#nr").change(function() {    
								
		window.location=($(this).attr('href')+'&nr='+$('#accions select#nr option:selected').val());						
	});

	$("#accions dl dd a").click(function() {    
								
		window.location=($(this).attr('href'));	
		
	});

    
	/* Pestanyes detall */
	
	if($('#contenidor-pestanes').length!=0){
	
	
	if($("li#ageq").length==0 && $("li#informacio").length==0){	
		$("#contenidor-pestanes").addClass("posicio1");
		$('#contenidor-pestanes ul#menu-pestanes').addClass('aprop');
	}else if($("li#ageq").length==0){
		$("#contenidor-pestanes").addClass("posicio2");
	}



	$('#contenidor-pestanes').addClass("js");
	
		$('#contenidor-pestanes .tabdetall').hide();
	
	var urlActual=String(window.location);
	
	var divActiu=urlActual.split("#");
	
	
	if(divActiu[1]=='esdeveniment' && $('#contenidor-pestanes .tabdetall#div-ageq').length!=0){
		$('#contenidor-pestanes .tabdetall#div-ageq').show();
		$('#contenidor-pestanes #menu-pestanes li#ageq a').addClass("active");
	
	}else{
	
		$('#contenidor-pestanes .tabdetall:first ').show();
		$('#contenidor-pestanes #menu-pestanes li:first a').addClass("active");
	}
	
	
	$('#contenidor-pestanes #menu-pestanes li a').click(function(){
		$('#contenidor-pestanes ul#menu-pestanes').removeClass().addClass('notranslate');;
		$pactivada=$(this).parent('li').attr('id');	
		
		$('#contenidor-pestanes ul#menu-pestanes').addClass($pactivada);
		$('#contenidor-pestanes li a').removeClass('active');
	
		$(this).parent('li').children('a').addClass('active'); 
	
		var currentTab = $(this).attr('href'); 
	
		$('.tabdetall').hide();
	
		$(currentTab).show();
	       // pageHeight();
		return false;
	
	});

	}
	/* Mapes */
	$('#changemap a').click(function(){
	
		$('#changemap a').removeClass('active');
	
		$(this).addClass('active'); 
	
		var currentTab = $(this).attr('href'); 
	
		$('#mapaplanol, #mapadetall, #mapastreet').hide();	
	
		$(currentTab).show();
	
		if (currentTab=='#mapadetall' || currentTab=='#mapastreet') refreshMap();	
	
		return false;
	
	});

	/* mapa districtes */
	
	if($("#mapa-districtes img").attr('src') != undefined){
	
		var url= $("#mapa-districtes img").attr('src');
		pos=url.indexOf('img/');
		url=url.substring(0,pos+4);
		
		$("#mapa-districtes area").mouseover(function(e) {								   
			$(this).parent().siblings('img').attr('src', url+$(this).attr("class")+'.gif');
			$("#mapa-districtes a."+$(this).attr("class")).addClass("active");
		}).mouseout(function(){	
			$(this).parent().siblings('img').attr('src',url+'mapa.gif');
			$("#mapa-districtes a."+$(this).attr("class")).removeClass("active");
		});
		
		$("#mapa-districtes a").mouseover(function(e) {		   
			$("#mapa-districtes img").attr('src', url+$(this).attr("class")+'.gif');
		}).mouseout(function(){
			$("#mapa-districtes img").attr('src',url+'mapa.gif');
		});
	}
	
	
	
	
	// Formulari proximes activitats
	checkperiode();
		
	
	$("#field-periode input").click(function(){
		checkperiode();
	});


	/** Amplia MAPA **/
	ampliaMapa();



});
})(jQuery);

/** Ampliacio del mapa */

function ampliaMapa(){
	(function ($){
		
	$('#mapa').scrollFollow({offset: 230});
	
	
	var mapaWidth = $('#mapa').width();   
    var ResultatsWidth = $('#llistat-resultats').width();
    
	$("#map_canvas").css("width",Drupal.settings.map_amplada-2+"px");    
   
   if (mapaWidth!=ResultatsWidth) {              
        $("#content-mapa").append('<img id="amplia" src="'+Drupal.settings.carpeta+'/img/bt-amplia.gif" alt="Ampliar el mapa" />');
   } else {
        $("#content-mapa").append('<img id="amplia" src="'+Drupal.settings.carpeta+'/img/bt-redueix.gif" alt="Reduir el mapa" />');
        $('#mapa:not(.stop)').toggleClass("stop");        
   }
  	
   $("img#amplia").css("cursor","pointer");	
  	
   $("img#amplia").click(function() {		
   		
		if($('#mapa').width()<=Drupal.settings.map_amplada){    
		       
		    $('#mapa').toggleClass("stop");
			$("#mapa.stop img#amplia").attr("src",Drupal.settings.carpeta+"/img/bt-redueix.gif");			
			// scroll top del body, per posicionar. 
			$('html, body').animate({scrollTop: $("#contingut-asia").offset().top - 70}, 500, function(){
				// $("#map").attr("src", src_iframe+"&z=" + (valor_zoom+2));
			});	
			// Ampliem el mapa a z=valor_zoom+5		   	
			$("#mapa, #llistat-resultats").animate({ width: $('#contingut-asia.llistat-cerca').width()  }, 500);	
			$("#map_canvas").css("width",$('#contingut-asia.llistat-cerca').width()-2+"px");
			
			google.maps.event.trigger(map, 'resize');
			map.fitBounds(latlngbounds);
			map.setZoom(12);
			//loadmapSearch(null,null,null,null);				
			//map.size(590);	
		} else {
			 
			$(this).attr("src",Drupal.settings.carpeta+"/img/bt-amplia.gif");									
			//$("#map").attr("src", src_iframe+"&z=" + (valor_zoom-2));
			$("#mapa").animate({ width: Drupal.settings.map_amplada }, 500,function(){
            	$('#mapa').toggleClass("stop");   
				$("#mapa").css("width",(parseFloat(Drupal.settings.map_amplada))+"px");         	
				$("#map_canvas").css("width",(parseFloat(Drupal.settings.map_amplada)-2) +"px");
				google.maps.event.trigger(map, 'resize');
	    		map.fitBounds(latlngbounds);
				map.setZoom(12);
			});			
			
			$("#llistat-resultats").animate({ width: Drupal.settings.list_amplada }, 500);
		}				
	});
	})(jQuery);	
}



/** validacio de periode del calendari */

function checkperiode(){
(function ($){
	if($("input[name=periode]:checked").val()=="rang"){
		$("input.calendari").removeClass("desactivat");
		$("input.calendari").attr("disabled","");
		
	}else{
		$("input.calendari").attr("disabled","disabled");
		$("input.calendari").addClass("desactivat");
	}
 })(jQuery);	
}

/* Obtindre una variable get per url */
function GetParam(sNomParam)
       {		 
	 var sCerca = asParametres = asParam = "";
  	 sCerca = location.search.substring(1,location.search.length);
	 asParametres = sCerca.split("&");
	 for(var i=0;i<asParametres.length;i++) 
	 	{
		 asParam = asParametres[i].split("=");
		 if (asParam[0] == sNomParam)
		 	 return(asParam[1]);
		}
    return "";
}
//init de cerca avançada
function init(showSearchCalendar,canal,base_url,code0,code1,element,idioma){


(function ($){

		
		$("#especialitat:not(:has(option))").attr("disabled","disabled").animate({ opacity:.5 }, 500 );			
		if(code1==""){
		if(code0!=""){
			$("#especialitat").attr("disabled","disabled").animate({ opacity:.5 }, 700, function(){
				$(this).children("option").remove();
				});	
			$("#especialitat").load(base_url+'/'+idioma+'/especialitat/'+code0+' #especialitat-aux option', function(response, status, xhr) {
			 
				$("#especialitat:not(:has(option))").attr("disabled","disabled").animate({ opacity:.5 }, 500 );	
				$("#especialitat:has(option)").removeAttr("disabled").animate({ opacity:1 }, 500);
				
			});
		}else{
		$("#tipusact").live("change",function(){
			
			$("#especialitat").attr("disabled","disabled").animate({ opacity:.5 }, 700, function(){
				$(this).children("option").remove();
				});	

			$("#especialitat").load(base_url+'/'+idioma+'/especialitat/'+$(this).val()+' #especialitat-aux option', function(response, status, xhr) {
			 
				$("#especialitat:not(:has(option))").attr("disabled","disabled").animate({ opacity:.5 }, 500 );	
				$("#especialitat:has(option)").removeAttr("disabled").animate({ opacity:1 }, 500);
				
			});
			
		});
		}
		}
		
		if(showSearchCalendar == 1){
			var now = new Date();
			now.setDate(now.getDate()-1);
			var now2 = new Date();
			now2.setDate(now2.getDate());
			now2.setHours(0,0,0,0);
			
			

			$(element).DatePicker({
				format:"Y-m-d",
				flat:true,
				date: $(element).siblings("div").find("#inputDate").val()?$(element).siblings("div").find("#inputDate").val():new Date() ,
				current: new Date(new Date().setMonth((new Date()).getMonth())),
				calendars:1,
				mode:"range",
				lastSel:false,
				starts:1,				
				lang:document.documentElement.getAttribute('xml:lang'),
				onRender: function(date) {
						return {
						disabled: (date.valueOf() < now.valueOf()-1),
						className: date.valueOf() == now2.valueOf() ? 'datepickerSpecial' : false
					}
				},
				onChange:function(b,a){$(element).siblings("div").find("#inputDate").val(b)}
				
			});
	
					$(element).siblings("div").find("#inputDate").val($(element).DatePickerGetDate(true))
					$(element).siblings("div").find("#inputDate").val('');
					if(idioma=="ca"){					   
						$('#prev').attr('data-direction', 'Anterior');
						$('#prev').html('Anterior');
						$('#next').attr('data-direction', 'Següent');
						$('#next').html('Següent');
					}else if(idioma=="es"){
						$('#prev').attr('data-direction', 'Anterior');
						$('#prev').html('Anterior');
						$('#next').attr('data-direction', 'Siguiente');
						$('#next').html('Siguiente');
					}else{
						$('#prev').attr('data-direction', 'Previous');
						$('#prev').html('Previous');
						$('#next').attr('data-direction', 'Next');
						$('#next').html('Next');
					}
				}
				
	   
	})(jQuery);	
		
}