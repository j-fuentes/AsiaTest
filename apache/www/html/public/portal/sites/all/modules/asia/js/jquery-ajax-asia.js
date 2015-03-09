// JavaScript Document
(function ($){

	$(document).ready(function(){							   
		initAjax();					   
		
		var positionLoaderW=$(window).width()/2+90;
		$("#content").append("<img src='"+Drupal.settings.carpeta+"/img/ajax-loader.gif' id='loader' style='display:none;left:"+positionLoaderW+"px' />");	
		
	});
	
	//Inicialització Ajax
function initAjax() {
	$(".paginador a, #llistat-filtres a, #accions a, #llistat-resultats .filtres a").bind("click", eventsHandler);
	$("#nr").bind("change",eventsHandler);


}

function eventsHandler(e) {
	
	    e.preventDefault();
        var urlAction = $(this).attr("href");
		
			$("#wrapper-results").css("opacity", ".4");
			 
			 var positionLoaderW=$(window).width()/2+90;
			$("img#loader").css("display","block");
			
			$("#wrapper-results").load(urlAction+"&nr="+$("#nr").val() +" #results-asia", function(response) {
				
				
				/** Carrega del mapa **/
				
				
				$('#results-asia').append($(getScriptGMapMarkers(response)));
				$('#llistat-resultats.amb-mapa').css('width',Drupal.settings.list_amplada+'px');
				
				ampliaMapa();
				
				$("#filtres-generics h3").click(function(){
					$("#llistat-filtres").slideToggle("slow", function(){
								//	$("#columna-0,#wrapper-bottom,#contingut" ).height($("#contingut .content-nadal").height()+110);
					});
					$(this).toggleClass("on");
					
								
				});
				$(".paginador a, #llistat-filtres a, #accions a, #llistat-resultats .filtres a").bind("click", eventsHandler);
	
				$("#nr").bind("change",eventsHandler);
				
				//pageHeight();
						
			   $('html, body').animate({scrollTop: $("#results-asia").offset().top - 75}, 1000, function(){
						 $("#wrapper-results").css("opacity", "1");
						  $("img#loader").css("display","none");
				});	
		});	

}

function getScriptGMapMarkers(responseText){
    
    if (responseText != undefined && responseText.indexOf('<script id="markers" type="text/javascript">') != -1){
		var txt = responseText.substring(responseText.search('<script id="markers" type="text/javascript">'));
		
		return txt.substring(0,txt.search('</script>')+9)
		
	} else {
		return '';
	}
}	
	
})(jQuery);						   