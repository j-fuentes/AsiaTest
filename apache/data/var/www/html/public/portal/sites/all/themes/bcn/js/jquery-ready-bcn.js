(function ($){// JavaScript Document

$(document).ready(function(e) {
    
 /* $(".tb-megamenu-main-menu .tb-megamenu-item.level-1:not(.home)").children("a").wrap("<span class='wrap-menu' />");		*/
  $(".tb-megamenu-nav.level-0").addClass("total-"+$(".tb-megamenu-main-menu .tb-megamenu-item.level-1").length);


  //cercador

  $("#block-search-form").each(function(index, element) {
	$(".tb-megamenu-nav").addClass("amb-cercador").append('<li id="bcn-search" class="tb-megamenu-item level-1"><a class="" href="#block-search-form">Search</a></li>');
  });
  
  $("body").on("click",  "#bcn-search", function(e){
	  e.preventDefault();
	 
	  $("#bcn-search").toggleClass("bcn-close");
	  $("#block-search-form").slideToggle("fast");
  });


 
  
  // menu
  $(".tb-megamenu-item.level-1:last").addClass("last");
  $("li.level-1:not(:has(li.level-2))").addClass("not-down");
  
  $(window).scroll(function () {

	 var nav = $("#zone-menu-wrapper");
	 if ($(this).scrollTop() > 146) {
		 nav.addClass("fixed-menu");
		 $("#zone-header-wrapper h1").addClass("fixed");
		} else {
		nav.removeClass("fixed-menu");
		 $("#zone-header-wrapper h1").removeClass("fixed");
	 }  
  });
  
 /* 
  $(".tb-megamenu-item").on({ 'touchstart' : function(){ $(this).addClass("taped")} });
  $(".tb-megamenu-item").on({ 'touchend' : function(){ $(this).removeClass("taped")} });
  */

});

})(jQuery);