var bIsClick;
var detallmap;
var detallpoint;
var panorama;
var panOptions;

document.write([
  '<script src="http://maps.google.com/maps/api/js?sensor=true" type="text/javascript"><\/script>'
].join(''));
/**
 *
 */
function loadmapSearch(Lat, Lng, Level, Url) {	  
	  bIsClick = false;
	  var myOptions = {
			  zoom: 12,
			  center: new google.maps.LatLng(41.398479, 2.184804),
			  mapTypeId: google.maps.MapTypeId.ROADMAP,
			  zoomControl: true,
			  zoomControlOptions: {style: google.maps.ZoomControlStyle.SMALL}
			}	  
	  var map = new google.maps.Map(document.getElementById("map"),myOptions);
	  addPoints(map);
}
/**
 *
 */
function AddMarker(map, xpoint, ypoint, html, houseMarker, houseMarkerShadow, latlngbounds){
    var infowindow = new google.maps.InfoWindow({ content: html });	
    var LatLng = new google.maps.LatLng(xpoint, ypoint)
    var marker = new google.maps.Marker({ position: LatLng, map: map, icon: houseMarker, shadow: houseMarkerShadow });   
	google.maps.event.addListener(marker, 'click', function() { 
		infowindow.open(map,marker);
	});
	latlngbounds.extend(LatLng);
}
/**
 * 
 * @param gmapx
 * @param gmapy
 * @param strElement
 */
function loadmapdetall(gmapx, gmapy, strElement) {
	 detallpoint = new google.maps.LatLng(gmapx, gmapy);
	 var myOptions = {
			  zoom: 5,
			  center: detallpoint,
			  mapTypeId: google.maps.MapTypeId.ROADMAP,
			  zoomControl: true,
			  zoomControlOptions: {style: google.maps.ZoomControlStyle.SMALL},
			  streetViewControl: true
			}	  
	detallmap = new google.maps.Map(document.getElementById("mapadetall"),myOptions);	
	var markerSize = new google.maps.Size(30,31);
	var houseMarker = new google.maps.MarkerImage("/tpl/guiabcn/images/eq.png",markerSize);
	var markerShadowSize = new google.maps.Size(42,30);
	var markerShadowPoint = new google.maps.Point(0,0);
	var markerShadowAnchor = new google.maps.Point(14,28);
	var houseMarkerShadow = new google.maps.MarkerImage("/tpl/guiabcn/images/sombra-map.png",markerShadowSize,markerShadowPoint,markerShadowAnchor);
	var marker = new google.maps.Marker({ position: detallmap.getCenter(), map: detallmap, icon: houseMarker, shadow: houseMarkerShadow });  
	//streeview
	
	panOptions = {
	            position: detallpoint,
	            addressControl: false,	            
	            navigationControlOptions: {
	                position: google.maps.ControlPosition.TOP_RIGHT,
	                style: google.maps.NavigationControlStyle.SMALL
	            },
	            linksControl: false,
	            pov: {
	               heading: 34,
	               pitch: 0,
	               zoom: 1
	            }
	         };
	 
	panorama = new google.maps.StreetViewPanorama(document.getElementById("streetview"), panOptions);
	panorama.setVisible(true);
	//detallmap.setStreetView(panorama);
	
}
/**
* Refresh and center.
**/
function refreshMap(){
	google.maps.event.trigger(panorama, 'resize'); 
	google.maps.event.trigger(detallmap, 'resize'); 	
	detallmap.setZoom(14);
	detallmap.setCenter(detallpoint);
}