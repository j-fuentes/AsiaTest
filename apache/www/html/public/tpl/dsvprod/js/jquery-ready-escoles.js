// JavaScript Document
(function ($){
	$(document).ready(function(){

	
	
	

		$("body").addClass("js");
		$("h2.tit_webs_destacades").hide();

	// Pestanyes, galeria alcalde i webs destacades
	// ---------------------------------------------------------------------------------------------------------------------
	
	 	webs_destacades();
		anim_intro();

	// Marcar menú interiors
	// ---------------------------------------------------------------------------------------------------------------------

	$("body#interior").find(".menu").children("li.first").addClass("active-trail");
	
	 $(".menu li").click(function() {
		window.location= $(this).find("a").attr("href");
		return false;
 	});

	
	/* butlleti */
	
	$("#bulleti").submit(function(){
		
		if(validarEmail($("#bulleti-email").val())){
			
		 	return true;
		}else{
			$("#bulleti-email").css("border","1px solid #C60C30");
			return false;
		};
		
	});

		/* mapa districtes */

		if($("#mapa-districtes img").attr('src') != undefined){

			var url= $("#mapa-districtes img").attr('src');
			pos=url.indexOf('img/mapa/');
			url=url.substring(0,pos+9);
			
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
		
		if($(".accordion") != undefined){
			var allPanels = $('.accordion > dd').hide();
			
			$('.accordion > dt > span').click(function() {
			
			if($(this).hasClass('active'))
			{
				$('.accordion > dt > span').removeClass('active');
				allPanels.slideUp('slow');
			}
			else
			{
				$('.accordion > dt > span').removeClass('active');
				$(this).addClass('active');
				allPanels.slideUp('slow');
				$(this).parent().next().slideDown('slow');
			}
			return false;
			});
		}
		
		if($('#label-bulleti-nom')!= undefined){
			$('#bulleti-nom').focus(function() {
				$('#label-bulleti-nom').css({'display':'none'})
			});
			$('#bulleti-nom').blur(function() {
				if ($(this).attr("value")==""){
					$('#label-bulleti-nom').css({'display':'block'})
				}else
				{
					$('#label-bulleti-nom').css({'display':'none'})
				}
			});
		}
		if($('#label-bulleti-email')!= undefined){
			$('#bulleti-email').focus(function() {
				$('#label-bulleti-email').css({'display':'none'})
			});
			$('#bulleti-email').blur(function() {
				if ($(this).attr("value")==""){
					$('#label-bulleti-email').css({'display':'block'})
				}else
				{
					$('#label-bulleti-email').css({'display':'none'})
				}
			});
		}
		
	});
})(jQuery);

(function($) {
    
		  $(document).ready(function() {
		
		$('#banner-suscription').toggle(function(event) {
			event.preventDefault();
			$('html, body').animate({
				scrollTop: $("#form-suscription").offset().top
			}, 2000);
		   $('#form-suscription').animate({ 
			 'height':'133px'
		   }, 500,'easeInOutExpo',function(){
			   $('#form-suscription form').fadeIn(10);
			   });
		   },
		   function(event) {
			event.preventDefault();
			$('#form-suscription form').fadeOut('fast');
		   $('#form-suscription').animate({ 
			  'height':'0px'
		   }, 500,'easeInOutExpo');			
		});
		
	});
	$.extend($.easing,
	{
		def: 'easeOutQuad',
	   
		easeInOutExpo: function (x, t, b, c, d) {
        if (t==0) return b;
        if (t==d) return b+c;
        if ((t/=d/2) < 1) return c/2 * Math.pow(2, 10 * (t - 1)) + b;
        return c/2 * (-Math.pow(2, -10 * --t) + 2) + b;
    }
});
		
})(jQuery);

function anim_intro(){
	
	var delay_interframe = 800;
	var delay_intraframe = 1900;
	var time_animate     = 1300;
	 
	if($('#frame_1_nen').attr('src') != undefined){
		
		$('#tots').hide();
		$('#fondo_2').hide();
		$('#fondo_3').hide();
		
		$('#frame_1_nen').animate({
		bottom: '-100px'
		}, time_animate, function() {
			$('#frame_1_text').fadeIn(delay_interframe,function(){
			$('#frame_1_nen').delay(delay_intraframe).fadeOut('fast');
			$('#frame_1_text').delay(delay_intraframe).fadeOut('fast',function(){
				$('#fondo_1').fadeOut('slow');
				$('#fondo_2').fadeIn('fast');
				$('#frame_2_nen').animate({
					
					bottom: '-100px'
					}, time_animate, function() {
						$('#frame_2_text').fadeIn(delay_interframe,function(){
						$('#frame_2_nen').delay(delay_intraframe).fadeOut('fast');
						$('#frame_2_text').delay(delay_intraframe).fadeOut('fast',function(){
							$('#fondo_2').fadeOut('slow');
							$('#fondo_3').fadeIn('fast');
							$('#frame_3_nen').animate({
								
								bottom: '-100px'
								}, time_animate, function() {
									$('#frame_3_text').fadeIn(delay_interframe,function(){
										$('#frame_3_nen').delay(delay_intraframe).fadeOut('fast');
										$('#frame_3_text').delay(delay_intraframe).fadeOut('fast',function(){
											$('#tots').fadeIn(delay_interframe);
											});
									});
								});
							});
						});
					});
				});
			});
		});
	}
}

// script de navegacio webs destacades
// ---------------------------------------------------------------------------------------------------------------------
function webs_destacades(){

    /*$("#webs-destacadas ul").addClass("js");*/
	$("#webs-destacadas").append('<img id="esq" src="/tpl/escoles/img/fletxa-video-esq-blau.gif" alt="Anterior"  /><img id="dret" src="/tpl/escoles/img/fletxa-video-dret-blau.gif" alt="Següent"  /> ');
	
	//$("img#dret, img#esq").animate({opacity:.5});
	
	$("img#esq").css("display","none");
	
	 var cont = 0;
	 var total = $("#webs-destacadas ul li").length / 6;
	 
	 if( (Math.round(total) - total) >= 0) {total=Math.round(total)}
	 else{total=Math.round(total)+1};
		 
	$("img#esq").mouseover(function() {
		$(this).css("cursor","pointer");
		$(this).attr("src","/tpl/escoles/img/fletxa-video-esq-blau-sin.gif");
	
	}).mouseout(function() {
		
		$(this).attr("src","/tpl/escoles/img/fletxa-video-esq-blau.gif");
	});
	
	
	$("img#dret").mouseover(function() {
		$(this).css("cursor","pointer");
		$(this).attr("src","/tpl/escoles/img/fletxa-video-dret-blau-sin.gif");
		
	}).mouseout(function() {
		
		$(this).attr("src","/tpl/escoles/img/fletxa-video-dret-blau.gif");
	});
	
	
	$("img#dret").click(function() {
		
		if(cont	== 0){$("img#esq:hidden").fadeIn('slow');}				 
		
		if(cont < total-1){						 
		   
		   $("#webs-destacadas ul").animate({"left": "-=864px"}, 'normal');
		   
		   cont++;
		   if(cont == total-1){$("img#dret").fadeOut('slow');}
		}
	});
	
	$("img#esq").click(function() {
		
		
		if(cont	< total){$("img#dret").fadeIn('slow');}
	
		if(cont < total && cont != 0){	
	
		   $("#webs-destacadas ul").animate({"left": "+=864"}, 'normal');
		  cont--;
		}
		if(cont == 0){$("img#esq").fadeOut('slow');}
	});


	}

function validarEmail(valor) {
 var filter = /[\w-\.]{3,}@([\w-]{2,}\.)*([\w-]{2,}\.)[\w-]{2,4}/;
        // utilizamos test para comprobar si el parametro valor cumple la regla
        if(filter.test(valor))
            return true;
        else
            return false;
}