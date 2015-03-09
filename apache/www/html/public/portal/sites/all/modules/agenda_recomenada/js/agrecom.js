(function ($){// JavaScript Document

  $(document).ready(function(e) {
		
	var lang = $("html").attr("lang");
	var loading = "loading...";
	switch(lang){
		case "ca":
		   loading = "carregant..."; 
		break;
		case "es":
		   loading = "cargando..."; 
		break; 
	
	}
	

	$("#llistat-categories li:first").find("a").addClass("active");

 
	/*************************/ 
	/** Age recomenada Home **/ 
	/*************************/
	
	 
	$("#llistat-categories").find("a").click(function(e){
		e.preventDefault();
		$("#llistat-categories").find("a").removeClass("active");
		
		$(this).parent("li").addClass("loading");
		$(this).addClass("active");
		
		
		$('#agenda-recomenada').append($("<div class='content-ajax'>").load(encodeURI(this.href)+'&response_type=embed #agenda-recomenada > *',function(){
			
			$("#agenda-recomenada .content-ajax:last").siblings().remove();
			
			$(".content-ajax:last .item").css('visibility', 'hidden');

			var count = $(".content-ajax:last .item").length;
			
			if(count < 6){
				$("#mes-activitats").fadeOut("slow");
			}else{
				$("#mes-activitats").fadeIn("slow");
			}
			
			agrecom_positionFadeItems();
			
			$("html, body").animate({ scrollTop: $('#llistat-categories').offset().top-110 }, 1000);	
			
			 agrecom_compartir();
			 agrecom_loadContent();
			 $("#llistat-categories").find("li").removeClass("loading");
			
		}));
	});
     
	  
	 
	$(".block-agenda-recomenada #mes-activitats").find("a").click(function(e){
		e.preventDefault();
		
		var text = $(this).text();
		$(this).addClass("loading").text(loading);
		
		var numItems = $("#agenda-recomenada").find(".item").length;
		
		var href= $("#llistat-categories").find("a.active").attr("href");		
				
		$('#agenda-recomenada').append($("<div class='content-ajax'>").load(encodeURI(href)+'&response_type=embed&nr=6&from='+numItems+' #agenda-recomenada > *',function(){
			
			var count = $(".content-ajax:last .item").length;
			
			$(".content-ajax:last .item").css('visibility', 'hidden');
			
			if(count < 6){
				$("#mes-activitats").fadeOut("slow");
			}else{
				$("#mes-activitats").fadeIn("slow");
			}
			
			agrecom_positionFadeItems();
		    
		
			$("html, body").animate({ scrollTop: $('.content-ajax:last').offset().top-75 }, 1000);	
			
			 agrecom_compartir();
			 agrecom_loadContent();
			 $("#mes-activitats a").removeClass("loading").html(text);
		}));
	
	}); 
	
	
	/** Paginador Especials **/
	
	$("#page.especial #mes-activitats").find("a").click(function(e){
		e.preventDefault();
		
		var text = $(this).text();
		$(this).addClass("loading").text(loading);
		
		var numItems = $("#agenda-recomenada").find(".item").length;
		
		var href= window.location;
				
		$('#agenda-recomenada').append($("<div class='content-ajax'>").load(encodeURI(href)+'&nr=6&from='+numItems+' #agenda-recomenada > *',function(){
			
			var count = $(".content-ajax:last .item").length;
			
			$(".content-ajax:last .item").css('visibility', 'hidden');
			
			if(count < 6){
				$("#mes-activitats").fadeOut("slow");
			}else{
				$("#mes-activitats").fadeIn("slow");
			}
			
			agrecom_positionFadeItems();
		    
		$("html, body").animate({ scrollTop: $('.content-ajax:last').offset().top-75 }, 1000);	
			
			 agrecom_compartir();
			 agrecom_loadContent();
			 $("#mes-activitats a").removeClass("loading").html(text);
		}));
	
	}); 
	
	
  /*******************************/ 
  /** Comportamen share buttons **/ 
  /*******************************/

  agrecom_compartir();
  
  
  /*******************************/ 
  /** Comportamen event load **/ 
  /*******************************/
  
  agrecom_loadContent();	

  //end Ready
  
  
  /****************************************/ 
  /** Comportament pestanyes esdeveniments **/
  /** 	Home **/ 
  /*******************************/
  
  	$('.boxgrid.caption').hover(function(){
			 var heightBoxTop = $('.boxgrid').height()/3;
		 
			$(".cover", this).stop().animate({top:heightBoxTop},{queue:false,duration:380});
			$(".backcover", this).stop().animate({top:'0px'},{queue:false,duration:380});
	}, function() {
		
		    var heightBox = $('.boxgrid').height();
			  var heightBoxBt = $('.boxgrid').height()/1.275;
			
			$(".cover", this).stop().animate({top:heightBoxBt},{queue:false,duration:380});
			$(".backcover", this).stop().animate({top:heightBox},{queue:false,duration:380});
	});
	
	$(".boxgrid").click(function(){
		
		if($('body').hasClass('front')){
			
			var boto=$(this).children('.cover').children('h3').text()+' | Equipament destacat';
			var url=$(this).children('.backcover').children('a').attr('href');
			var target = "home";				
		
		callAnalytics_heatmap(boto , url, target);
		}
		
		
		window.location=$(this).find("a").attr("href");
		return false;
	});
	
	
  
 });
 
function agrecom_loadContent(){

	$(".no-touch #agenda-recomenada h3,.no-touch #llistat-resultats h3").click(function(e){
		 if(e.which < 2)	$(this).parent("div").parent("div").addClass("selected");
		
	});

} 

 
function agrecom_positionFadeItems(){
	var v = $(".content-ajax:last .item").css('visibility', 'hidden'), cur = 0;
	for(var j, x, i = v.length; i; j = parseInt(Math.random() * i), x = v[--i], v[i] = v[j], v[j] = x);
		function fadeInNextLI() {
		  v.eq(cur++).css('visibility','visible').hide().fadeIn(600);
		  if(cur != v.length) setTimeout(fadeInNextLI, 150);
		}
	fadeInNextLI();

} 
 
function agrecom_compartir(){

  var wd = "193px";
  
  $(".compartir").mouseenter(function() {
	  
	 if(window.innerWidth < 767){  wd = "111px"; }else{  wd = "193px";}	
		
	 $(this).stop(true,true).animate({width: wd}, 'normal');

   }).mouseleave(function() {

  	 $(this).stop(true,true).animate({width: "37px"}, 'normal');
   });
}


 
})(jQuery);


