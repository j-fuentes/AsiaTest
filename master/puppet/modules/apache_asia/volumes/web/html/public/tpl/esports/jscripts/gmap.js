var bIsClick;
var detallmap;
var detallpoint;

document.write([
  '<script src="http://maps.google.com/maps?file=api&amp;v=2&amp;key=', {
    'guia.bcn.es': 'ABQIAAAAXqhLkdc0bUs8sBT4Gb3cYBSxD6gEzfNsGVscRFqIL_1TCtr0VRRLw0JKCIJ_eybSDP3672YGOb4C8A',
    'guia.bcn.cat': 'ABQIAAAAXqhLkdc0bUs8sBT4Gb3cYBQWlx7lH2eBUn6Cgi7EZeCphnESbBTMlS2nY8tbd2xhrypZwHnKPLCGRg'
  }[window.location.host],
  '" type="text/javascript"><\/script>'
].join(''));



/**
 *
 */
function loadmap(Lat, Lng, Level, Url) {
	  bIsClick = false;
      if (GBrowserIsCompatible()) {
           
        var map = new GMap2(document.getElementById('map'));
                
        //map.disableDragging();
        map.addControl(new GLargeMapControl());
       
        map.addControl(new GMapTypeControl());
		 
		
		GEvent.addListener(map, 'moveend', function() {	
		  if (!bIsClick) getImmoPoints(map, Url);
		  bIsClick = false;		 
		}); 
		
		map.setCenter(new GLatLng(Lat,Lng), Level);  
          		
      }
}
/**
 *
 */
function loadmapSearch(Lat, Lng, Level, Url) {
	  bIsClick = false;

      if (GBrowserIsCompatible()) {
           
        var map = new GMap2(document.getElementById('map'));
                
        //map.disableDragging();
        //map.addControl(new GLargeMapControl()); 
        map.addControl(new GSmallMapControl()); 
        map.addControl(new GMapTypeControl());
	
		//map.setCenter(new GLatLng(Lat,Lng), Level);  
		
		addPoints(map);            		
      }
}
/**
 *
 */
function AddMarker(map, xpoint, ypoint, details, icon, markerBounds){
	var point = new GLatLng(xpoint, ypoint);
    var marker = new GMarker(point, icon);
    map.addOverlay(marker);
    markerBounds.extend(point);
    if (details!=null){
    GEvent.addListener(marker, "click", function() {
        bIsClick = true;
        marker.openInfoWindowHtml(details);
    });
    }
}
/**
 *
 */
function AddMarkerLink(map, xpoint, ypoint, href, icon){
	var point = new GLatLng(xpoint, ypoint);
    var marker = new GMarker(point, icon);
    marker.url = href;
    map.addOverlay(marker);    
    GEvent.addListener(marker, "click", function() {
        bIsClick = true;
        window.location.href = marker.url;
    });    
}
/**
 *
 */
function AddMarkerById(mapid, xpoint, ypoint, details, icon){
    var map = new GMap2(document.getElementById(mapid));
	var point = new GLatLng(xpoint, ypoint);
    var marker = new GMarker(point, icon);
    map.addOverlay(marker);
    GEvent.addListener(marker, "click", function() {
        bIsClick = true;
        marker.openInfoWindowHtml(details);
    });
}
/**
* Creates a marker whose info window displays the letter corresponding
* to the given index.
*/
function createMarker(point,index, info) {
	var marker = new GMarker(point); return marker;
}
/**
* Load detall Map
*/
function loadmapdetall(gmapx, gmapy, strElement) {
	if (GBrowserIsCompatible()) {
		detallmap = new GMap2(document.getElementById('detallmap'));

		//detallmap.disableDragging();
	
		detallmap.addControl(new GLargeMapControl());
		detallmap.addControl(new GMapTypeControl());
		
		
		var blueIcon = new GIcon(G_DEFAULT_ICON);    	
		blueIcon.iconSize = new GSize(30, 31);
        blueIcon.shadowSize = new GSize(42,30);	
        blueIcon.image = '/tpl/guiabcn/images/eq.png'
        blueIcon.shadow = '/tpl/guiabcn/images/sombra-map.png';
		
		// Setting markers 
		detallpoint = new GLatLng(gmapx,gmapy);
			
		//map.addOverlay(createMarker(point, 1,'Latitude, Longitude<br />' + point.toUrlValue(6)));
		detallmap.addOverlay(new GMarker(detallpoint,blueIcon));
		
		detallmap.setCenter(detallpoint, 14);
		
	
		//document.getElementById('detallmap').style.display="block";
		//document.getElementById('mapaplanol').style.display="none";
	}
	var fenwayPark = new GLatLng(gmapx,gmapy);
	panoramaOptions = { latlng:fenwayPark };
	var myPano = new GStreetviewPanorama(document.getElementById("streetview"),panoramaOptions);
}
/**
* Refresh and center.
**/
function refreshMap(){
   detallmap.checkResize();
   detallmap.setCenter(detallpoint, 14);
}



