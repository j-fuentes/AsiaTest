// JavaScript Document
(function($) {
    

$(document).ready(function() {

	var flag = false;
	if( $(window).width() <= 640)
	{
		flag = true;
		gomobile();
	}
	
	$(window).resize(function() {
	
	if( $(window).width() <= 640 && flag == false)
	{
		flag = true;
		gomobile();
	}
	if( $(window).width() > 640)
	{
		flag = false;
		$('#bt-menu').remove();
		$('.menu-corner').remove();
		$('#vista-llistat').remove();
		$("body.mobile .logotype").children("a").children("img").attr("src", "http://www.bcn.cat/assets/images/brand/banner/2012/logo-ajment.png").attr('width','130').attr('height','43');	
		$("body").removeClass("mobile");
	
	}
		
	});
		
});

function gomobile()
{
		$("body").addClass("mobile");
		
		$("body:not(#home).mobile h1").before("<img src='/tpl/dsvprod/img/mobile/ico-menu.png' id='bt-menu' class='mobile-show' />");
		$("body:not(#home) #navegacio-separada").prepend('<img class="menu-corner mobile-show" src="/tpl/dsvprod/img/mobile/corner_menu.png" width="7" />');
		$("body.mobile .logotype").children("a").children("img").attr("src", "/tpl/dsvprod/img/mobile/logo_m.png").removeAttr("width").removeAttr("height");
		
		$("#bt-menu").toggle(function(){
		
			$("#marc-web").animate({"left": "+=80%"}, 'normal');
			$("#navegacio-separada").animate({"left": "+=80%"}, 'normal',function(){$("body, html").toggleClass("nav-expand");});
			
			}, function() {
			$("#navegacio-separada").animate({"left": "-=80%"}, 'normal');
			$("#marc-web").animate({"left": "-=80%"}, 'normal',function(){$("body, html").toggleClass("nav-expand");});
		});
		
	
		/** Llistat **/
		 /*if($("#ajx-search h2") != undefined){
			$("#ajx-search h2").after("<span id='vista-llistat'>Vista en mapa</span>");
			
			$("#vista-llistat").toggle(function(){
				
				$("#llista-resultats div:not(.paginador)").hide();
				$("#mapa").show();
				$(this).html("Vista en llistat");
				$(this).addClass("mapa");
			
				}, function() {
				$("#llista-resultats div:not(.paginador)").show();
				$("#mapa").hide();
				$(this).html("Vista en mapa");
				$(this).removeClass("mapa");
			});
			
		}*/
}
		
})(jQuery);