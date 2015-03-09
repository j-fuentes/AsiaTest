
// JavaScript Document



(function ($){
//Drupal.settings.ico_markers
//Drupal.settings.base_url
//Drupal.settings.urljson
//Drupal.settings.detall
$(document).ready(function(e) {
	
    assingId();

	var activeWindow = null;

	var gmarkers = []; // Array amb tots els markers
	var listCategories = []; // Array que guarda només la categoria quan s'ha seleccionat	
	var bubleList=[]; // Array amb tots els html de cada item ordenat per la categoria i posicio (geolocalitzacio)
	var url = $("#bcn-map-actions form").attr('action');
	
	if(url==""){
		url = Drupal.settings.urljson;
	}
	
	
	
	// si la lista esta activada afegir el menu de visio
	if(Drupal.settings.activelist==1){
		$('#bcn-map-view').prepend('<div id="menu-view-map"><ul><li id="item-view-map" class="active"><a href="#map-canvasGM">'+Drupal.settings.literals[0]+'</a></li><li><a  id="item-view-list" href="#llistat-text">'+Drupal.settings.literals[1]+'</a></li></ul></div>');
		$('#llistat-text').hide();
	}
	
	// menu del mapa
	$('#menu-view-map ul li a').click( function(e){
		e.preventDefault();
		$('#menu-view-map ul li').removeClass('active');
		$(this).parent('li').addClass('active');
		var elem = $(this).attr('href');
		$(elem).show();
		$(elem).siblings('div').not('#menu-view-map').hide();
		
	});
		
	//alert(Drupal.settings.base_url+' + '+ Drupal.settings.ico_markers);
	
	
	// Quan selecciones a mostrar tots
	$("#bcn-map-actions").find("input#tots").change(function(){
		
		if($(this).is(":checked")){				
			$(this).parent('li').siblings('li').children('input').attr("checked","checked");	
			$("#bcn-map-actions ul li input").not('#tots').each(function(index, element) {
           		category=$(element).attr("data-id");
				
				
				if($.inArray( category, listCategories ) != -1 ){
					show(category);
				}else{ // si és el primer cop, guarda'ls i carregals
					var params = $(this).attr("value");
					carregaMap(url+params, category);			
				}
				
			});	
			
		}else{
			
			$(this).parent('li').siblings('li').children('input').removeAttr("checked");
			$("#bcn-map-actions ul li input").not('#tots').each(function(index, element) {
				category=$(element).attr("data-id");
				hide(category);
				removeLlistat(category);
			});		
		}
		
		
		
		
	});
	
	
	
	//Quan fas checked al menu
	
	$("#bcn-map-actions").find("input:checkbox").not('#tots').change(function(){
		
		
		//guarda categoria
		category=$(this).attr("data-id");
		
		
		if($(this).is(":checked")){			
			//si la categoria esta en el array, és a dir, que no és el primer cop que es selecciona
			//mostram els markers de la categoria de l'array gmarkers
			if($.inArray( category, listCategories ) != -1 ){
				show(category);
			}else{ // si és el primer cop, guarda'ls i carregals
				var params = $(this).attr("value");
				carregaMap(url+params, category);			    
			}		
			
		}else{
			$(this).parent('li').siblings('li').children('input#tots').removeAttr("checked");

			hide(category);
			removeLlistat(category);
			
		}		
		
	});
	
	/////////////////
	
	$(".hide").click(function(e){
		hideProva();
	})
	
	////////////////
	
	function carregaMap(url,id){   
	   bubleList[id]=[];
	   
		$.getJSON(url, function(data){
			
				
			// Si hi ha trobat alguna cosa
			if(data.page.central.search.queryresponse!=undefined){
			var literals =	data.page.central.search.queryresponse.list.list_items.cols;
			
			var list = data.page.central.search.queryresponse.list.list_items.row;
			$.each(list, function() {	
				
				elem = this["item"];
				var pos = elem["pos"];				
				//Inicialització classe que s'afegeix quan elem te imatge
				var classImg ="";
				
					var marker = new google.maps.Marker({
						position: new google.maps.LatLng(elem["gmapx"],elem["gmapy"]),
						map: mapGM,
						title: elem["name"],
						icon: Drupal.settings.ico_markers + id + ".png"
					});
			       
				   // Imatge
				   //Si no te imatge es buit
				    var timg='';
					if(elem["internetref"]=="undefined" || elem["internetref"]==null || elem["internetref"]==""){
						var timg='';												
					}else{ // Si te imatge pinta tag img.
						var timg='<img src="'+elem["internetref"]+'" alt=""/>';
						classImg=' amb-img';
					}
					
							  
					var html ="";
					
					
					switch(elem["tp"]){
						// EQUIPAMENTS
						case "EQ":
							var outEq="";
							// Adreça
							if(elem['address']!=null){
									outEq+="<p class='address'>"+elem["address"];
									if(elem['district']!=null){
										outEq+=" ("+elem["district"]+")";
									}
									outEq+="</p>";
								}
								// telefon
								if(elem['phonenumber']!=null){
									outEq+="<p>"+elem["phonenumber"]+"</p>";
								}
								// Web
								if(elem['code_url']!=null){
									 var web=elem['code_url'];
									if(web.indexOf("http") == -1){
										web='http://'+web;
									}
									outEq+="<p><a href='"+web+"'>"+elem["code_url"]+"</a></p>";
								}
								
							 
							 html = "<div class='item eq"+classImg+"'>"+timg+"<div><strong><a href='"+Drupal.settings.detall+elem["@attributes"]["href"]+"'>"+elem["name"]+"</a></strong>"+outEq+"</div></div>";
							break;
							
						// AGENDA	
						case "AG":
							if (elem['date']!=null || elem['begindate']!=null || elem['enddate']!=null || elem['institutionname']!=null){
								var outAg="<dl>";
								
								// data			
								if (elem['date']!=null){
									outAg+='<dt>'+Drupal.settings.literals[2]+':</dt><dd>'+elem['date']+'</dd>';					
														
								}else if (elem['begindate']!=null || elem['enddate']!=null){
									outAg+='<dt>'+Drupal.settings.literals[2]+':</dt><dd>';
									if(elem['begindate']!=null){
										outAg+=literals['begindate']+' '+elem['begindate'];
									}
									if(elem['enddate']!=null){
										outAg+=' '+literals['enddate']+' '+elem['enddate'];
									}
									
								}
								// on
								if(elem['institutionname']!=null){
									outAg+='<dt>'+literals['institutionname']+'</dt><dd>'+elem['institutionname']+'<dd>';
								}
								outAg+='</dl>';
								// adreça
								if(elem['address']!=null){
									outAg+='<p>'+elem["address"];
									if(elem['district']!=null){
										outAg+=' ('+elem["district"]+')';
									}
									outAg+="</p>";
								}
								// telefon
								if(elem['phonenumber']!=null){
									outAg+="<p>"+elem["phonenumber"]+"</p>";
								}
								// web
								if(elem['code_url']!=null){
									 var web=elem['code_url'];
									if(web.indexOf("http") == -1){
										web='http://'+web;
									}
									outAg+="<p><a href='"+web+"'>"+elem["code_url"]+"</a></p>";
								}
																
							}
							
						     html = "<div class='item ag"+classImg+"'>"+timg+"<div><strong><a href='"+Drupal.settings.detall+elem["@attributes"]["href"]+"'>"+elem["name"]+"</a></strong>"+outAg+"</div></div>";
					 		
						break;						
						
					}
					// afegeix la variable html d'un marker en la categoria i posicio del array si aquesta pos es repetida, si no la guarda com a nova.
					if(bubleList[id][pos]==null){
						bubleList[id][pos] = html;
					}else{
						bubleList[id][pos] += html;
					}
					
					//Definicio de bubbles dins del mapa
					var infowindow = new google.maps.InfoWindow({ content:  '<div class="bubble">'+bubleList[id][pos]+'</div>' });
					google.maps.event.addListener(marker, 'click', function() { 
						if(activeWindow != null){
							activeWindow.close(); 
						}			 			 
						infowindow.open(mapGM,marker);
						activeWindow = infowindow; 
						
						$(".item.eq:not(:last),.item.ag:not(:last)").children("div").children("p.adress").remove();						
						
					});
				 
					marker.category = id;
					
					gmarkers.push(marker);
			
				
		
			});
			// Si no hi ha resultats
			}else{
				bubleList[id] = "<p>No s'ha trobat ningun registre</p>";
			}
			listCategories.push(id);
			printLlistat(id); // funció que pinta en el llistat tots els items d'una categoria de menu
		});
	}
	
	
	$("#llistat-categories li a").click(function(e){
		e.preventDefault(); 
		href = $(this).attr("href");
		param = getParam ("c", href);
		id = $(this).attr("data-id");
		
		$("#llistat-categories li a").removeClass("active");
		$(this).addClass("active");
		
		
		
			if($.inArray( id, listCategories ) != -1 ){
				 show(id);
			}else{ // si és el primer cop, guarda'ls i carregals
				 carregaMapAgRecom(param,id);		    
			}
		
		$("#llistat-categories li a:not(.active)").each(function(index, element) { hide($(this).attr("data-id")); });
			
		
			
	});	
	
	function carregaMapAgRecom(param,id){   
	   bubleList[id]=[];
	   url = "http://guia.bcn.cat/index.php?pg=agrecom&xout=json&ajax=agrecom&nr=500&wtarget=agenda500-tots&idma=&c="+param;	
	   
	   $.getJSON(url, function(data){

			// Si hi ha trobat alguna cosa
			
			//var literals =	data.page.central.search.queryresponse.list.list_items.cols;
			
			var list = data.hrecom.list.list_items.row;
			
			var pos = 0;
			$.each(list, function() {	
				
				elem = this["item"];
				pos++;
				
				//Inicialització classe que s'afegeix quan elem te imatge
				var classImg ="";
				
					var marker = new google.maps.Marker({
						position: new google.maps.LatLng(elem["gmapx"],elem["gmapy"]),
						map: mapGM,
						title: elem["name"],
						icon: Drupal.settings.ico_markers + id + ".png"
					});
			       
				   // Imatge
				   //Si no te imatge es buit
				/*    var timg='';
					if(elem["internetref"]=="undefined" || elem["internetref"]==null || elem["internetref"]==""){
						var timg='';												
					}else{ // Si te imatge pinta tag img.
						var timg='<img src="'+elem["internetref"]+'" alt=""/>';
						classImg=' amb-img';
					}
					
							  
					var html ="";
					
					
					switch(elem["tp"]){
						// EQUIPAMENTS
						case "EQ":
							var outEq="";
							// Adreça
							if(elem['address']!=null){
									outEq+="<p class='address'>"+elem["address"];
									if(elem['district']!=null){
										outEq+=" ("+elem["district"]+")";
									}
									outEq+="</p>";
								}
								// telefon
								if(elem['phonenumber']!=null){
									outEq+="<p>"+elem["phonenumber"]+"</p>";
								}
								// Web
								if(elem['code_url']!=null){
									 var web=elem['code_url'];
									if(web.indexOf("http") == -1){
										web='http://'+web;
									}
									outEq+="<p><a href='"+web+"'>"+elem["code_url"]+"</a></p>";
								}
								
							 
							 html = "<div class='item eq"+classImg+"'>"+timg+"<div><strong><a href='"+Drupal.settings.detall+elem["@attributes"]["href"]+"'>"+elem["name"]+"</a></strong>"+outEq+"</div></div>";
							break;
							
						// AGENDA	
						case "AG":
							if (elem['date']!=null || elem['begindate']!=null || elem['enddate']!=null || elem['institutionname']!=null){
								var outAg="<dl>";
								
								// data			
								if (elem['date']!=null){
									outAg+='<dt>'+Drupal.settings.literals[2]+':</dt><dd>'+elem['date']+'</dd>';					
														
								}else if (elem['begindate']!=null || elem['enddate']!=null){
									outAg+='<dt>'+Drupal.settings.literals[2]+':</dt><dd>';
									if(elem['begindate']!=null){
										outAg+=literals['begindate']+' '+elem['begindate'];
									}
									if(elem['enddate']!=null){
										outAg+=' '+literals['enddate']+' '+elem['enddate'];
									}
									
								}
								// on
								if(elem['institutionname']!=null){
									outAg+='<dt>'+literals['institutionname']+'</dt><dd>'+elem['institutionname']+'<dd>';
								}
								outAg+='</dl>';
								// adreça
								if(elem['address']!=null){
									outAg+='<p>'+elem["address"];
									if(elem['district']!=null){
										outAg+=' ('+elem["district"]+')';
									}
									outAg+="</p>";
								}
								// telefon
								if(elem['phonenumber']!=null){
									outAg+="<p>"+elem["phonenumber"]+"</p>";
								}
								// web
								if(elem['code_url']!=null){
									 var web=elem['code_url'];
									if(web.indexOf("http") == -1){
										web='http://'+web;
									}
									outAg+="<p><a href='"+web+"'>"+elem["code_url"]+"</a></p>";
								}
																
							}
							
						     html = "<div class='item ag"+classImg+"'>"+timg+"<div><strong><a href='"+Drupal.settings.detall+elem["@attributes"]["href"]+"'>"+elem["name"]+"</a></strong>"+outAg+"</div></div>";
					 		
						break;						
						
					}
					// afegeix la variable html d'un marker en la categoria i posicio del array si aquesta pos es repetida, si no la guarda com a nova.
					if(bubleList[id][pos]==null){
						bubleList[id][pos] = html;
					}else{
						bubleList[id][pos] += html;
					}
					*/
					
					
					//Definicio de bubbles dins del mapa
					var infowindow = new google.maps.InfoWindow({ content:  '<div class="bubble"><a href="'+Drupal.settings.detall+elem["@attributes"]["href"]+'">'+elem["name"]+'</a></div>' });
					google.maps.event.addListener(marker, 'click', function() { 
						if(activeWindow != null){
							activeWindow.close(); 
						}			 			 
						infowindow.open(mapGM,marker);
						activeWindow = infowindow; 
						
						$(".item.eq:not(:last),.item.ag:not(:last)").children("div").children("p.adress").remove();						
						
					});
				 
					marker.category = id;
					
					gmarkers.push(marker);
			
				
		
			});
			// Si no hi ha resultats
			
			listCategories.push(id);
			printLlistat(id); // funció que pinta en el llistat tots els items d'una categoria de menu
		});
	}
	
	// mostra tots els items d'una categoria de menu
	function show(category) {	
		
		for(var i = 0; i < gmarkers.length; i++) {
			
			if(gmarkers[i].category == category) {
				gmarkers[i].setVisible(true);
			}
		}
		// ho pinta en la visio llistat
		printLlistat(category);
	}
	
	// pinta tot el llistat d'items d'una categoria de menu agrupan en un <div>
	function printLlistat(category){
		//alert(category);
		var totCategory="";
		$("#bcn-map-actions ul li").each(function(index, element) {
			if($(this).children("input").attr("data-id")==category){
				
				var titCategoria=$(this).children("input").siblings("label").text();
				
				//tots els items				
				for(var i = 0; i < bubleList[category].length; i++) {	
							if(bubleList[category][i]!=null){
							totCategory += bubleList[category][i];		
							}							
					
				}	
				
				$("#llistat-text").prepend('<div class="'+category+'"><h3>'+titCategoria+'</h3>'+totCategory+'</div>')
			}
			
		});
	}
	
	// Borra del llistat una categoria
	function removeLlistat(category){
		$("#llistat-text div."+category).remove();
	}
	
	// Oculta tots el punts en el mapa d'una categoria.
	function hide(category) {
		for(var i = 0; i < gmarkers.length; i++) {
			if(gmarkers[i].category == category) {
				gmarkers[i].setVisible(false);
				
			}
		}
	}
	
	// Assignacio automatica de atribut "data-id", el map-num és la nostra categoria o id, l'utilitzem també per fer les imatges (markers/map-num.png).
	function assingId() {
		$("#bcn-map-actions").find("input:checkbox").not("#tots").each(function(index, element) {
            $(this).attr("data-id","map-"+index);
        });
	}
	
	function getParam (name, href) {
			return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(href)||[,""])[1].replace(/\+/g, '%20'))||null;
		}
	
});

})(jQuery);	