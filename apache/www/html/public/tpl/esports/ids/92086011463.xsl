<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:fb="http://www.facebook.com/2008/fbml"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	>

    <xsl:output method="html"
		doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
		doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
		indent="yes" />			

	<!-- TEMPLATE COPY ALL ELEMENTS WITHOUT TEMPLATE -->
	<xsl:template match="node()">
		<xsl:element name="{local-name()}">
			<xsl:apply-templates select="@*|node()|text()" />
		</xsl:element>
	</xsl:template>

	<xsl:template match="@*|text()" priority="3">
		<xsl:copy-of select="." />
	</xsl:template>

	<!-- TEMPLATE html -->
	<xsl:template match="html">
		<html xml:lang="{//html/page/@lang}"
			lang="{//html/page/@lang}">
			<xsl:apply-templates />	
		</html>
	</xsl:template>
	
		<!-- TEMPLATE ajax -->
	<xsl:template match="ajax">
           <xsl:apply-templates select="search" />
           <xsl:apply-templates select="hrecom" />
           <xsl:apply-templates select="related" />
           <xsl:apply-templates select="homebcn" />
           <xsl:if test="boolean(classall)">
	           <html><head>
	               <link rel="stylesheet" type="text/css" media="all" href="/tpl/common/css/home.css" />
			       <link rel="stylesheet" type="text/css" media="all" href="/tpl/common/css/cercador.css" />
	               </head><body id="iframe-cats">
	               <div id="marc-iframe">
	              <xsl:apply-templates select="classall" />
	              </div>
	           </body></html>
           </xsl:if>
	</xsl:template>	

	<!-- TEMPLATE head -->
	<xsl:template match="head">
		<head>		
		<!-- capçalera bcn.cat -->
		<link rel="Shortcut Icon" type="image/ico" href="http://www.bcn.cat/favicon.ico" />		
		<!-- <script type="text/javascript" charset="utf-8" src="http://www.bcn.cat/assets/core/1.0.0/javascripts/core.js"></script>
		<script type="text/javascript">		
   		bcn.load("common", "1.0.0");
   		bcn.ready();
		</script> -->
		
		<script type="text/javascript" charset="utf-8" src="http://www.bcn.cat/assets/core/2.1.0/javascripts/core.js"></script>
		<script type="text/javascript">
          bcn.statistics();
        </script>

		<link rel="stylesheet" href="http://www.bcn.cat/assets/core/2.1.0/stylesheets/core.css" type="text/css" charset="utf-8" />

		<!-- fi capçalera bcn.cat -->	
		
		<!-- Stylesheet general -->	
		<link rel="stylesheet" type="text/css" media="all" href="/tpl/common/css/home.css" />
		<link rel="stylesheet" type="text/css" media="all" href="/tpl/common/css/cercador.css" />		
		<script src="/tpl/common/js/jquery-1.5.1.min.js" type="text/javascript"></script>	
		<script src="/tpl/common/js/jquery.scrollfollow.js" type="text/javascript"></script>	
		<script src="/tpl/common/recursos/fancybox/jquery.fancybox-1.3.0.js" type="text/javascript"></script>	
		<link rel="stylesheet" type="text/css" media="all" href="/tpl/common/recursos/fancybox/jquery.fancybox-1.3.0.css" />
	    <link type="text/css" href="/tpl/common/css/datepicker.css" rel="stylesheet" />	
		<script type="text/javascript" src="/tpl/common/js/datepicker.js"></script>
	    <script type="text/javascript" src="/tpl/common/js/dol.js"></script>
	    <script type="text/javascript" src="/tpl/common/js/jquery-ready-home10.js"></script>		
		
		<xsl:comment><![CDATA[[if IE]>
			<link rel="stylesheet" href="/tpl/common/css/cercador-ie.css" type="text/css" media="screen, projection, print" />
		<![endif]]]></xsl:comment>
		
		<xsl:comment><![CDATA[[if lt IE 8]>
			<link rel="stylesheet" href="/tpl/common/css/cercador-ie7.css" type="text/css" media="screen, projection, print" />
            <link rel="stylesheet" type="text/css" href="http://www.bcn.cat/assets/core/2.1.0/stylesheets/core-ie7.css" charset="utf-8" />
		<![endif]]]></xsl:comment>
		
	    <xsl:comment><![CDATA[[if lte IE 6]>
			<link rel="stylesheet" href="/tpl/common/css/cercador-ie6.css" type="text/css" media="screen, projection, print" />
            <link rel="stylesheet" type="text/css" href="http://www.bcn.cat/assets/core/2.1.0/stylesheets/core-ie6.css" charset="utf-8" />
		<![endif]]]></xsl:comment>
	    		
					
		<!-- Fi Stylesheet general -->
		
		<!-- Per Datepicker a Home -->
	    <xsl:if test="boolean(//html/page/central/datepicker)">		
			<script type="text/javascript" src="/tpl/common/js/dt-init.js"></script>
		</xsl:if> 
        <!-- Fi DatePicker -->				 		
		<!-- per imatges a xarxes socials -->	
		<xsl:if test="boolean(//html/page/central/detall/internetref/item/irefvalue)">
			<link rel="image_src" href="{//html/page/central/detall/internetref/item/irefvalue}" />
		</xsl:if>
		<!-- Fi imatges xarxes -->
		<!-- per filtres cerca -->
		<xsl:if test="boolean(//html/page/central/bleft/leftfilter)"></xsl:if>
		<!-- end filtres -->
		<!-- Para la presentación de los controles dentro del planol ajuntament -->
		<xsl:if test="boolean(//html/page/central/detall/coordaddressx)">		
		<link href="http://w20.bcn.cat/GuiaMap/jquery.mapguia/js/mapguia/jquery.map-guia-1.0.css" media="screen" rel="stylesheet" type="text/css" />
        <!--<link href="http://w20.bcn.cat/GuiaMap/jquery.mapguia/css/guia_mapa.css" rel="stylesheet" type="text/css" />--> 
		<!--<script type="text/javascript" src="http://w20.bcn.cat/GuiaMap/jquery.mapguia/js/jquery-mapguia-bundle-min.js"></script>-->
        <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js" type="text/javascript"></script>
        <script src="/tpl/common/js/jquery.mousewheel.js" type="text/javascript"></script>        
        
        <!-- <script type="text/javascript" src="http://w20.bcn.cat/GuiaMap/jquery.mapguia/js/mapguia-min.js"></script>-->
        <script type="text/javascript" src="/tpl/common/js/planol.js"></script>		
		</xsl:if>	
		<!-- fin presentacion planol -->	
		<!-- control shareit -->
		<xsl:if test="boolean(//html/page/central/search/queryresponse/share) or boolean(//html/page/central/detall/share)">
		<script type="text/javascript">
		var addthis_config = {"data_track_clickback":true};
		var addthis_share = { templates: { twitter: '{{title}} @ {{url}}' }
		}</script>
		<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#pubid=ra-4d71141009b7bb91"></script>
		</xsl:if>
		<!-- fin control shareit -->
		<!-- traduccio -->
		<xsl:if test="boolean(//html/page/central/detall)">
		<script>
		function googleSectionalElementInit() {
		  new google.translate.SectionalElement({
		    sectionalNodeClassName: 'goog-trans-section',
		    controlNodeClassName: 'goog-trans-control',
		    pageLanguage: 'ca',
		    background: 'transparent'
		  }, 'google_sectional_element');
		}		
		</script>
		<script src="//translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&amp;ug=section&amp;hl={//html/page/@lang}"></script>
       <script>
       
   google_initialized = false;

    function google_auto_translate(){
        if(google_initialized){             
            
            $('a.goog-te-gadget-link')[0].click();    
            
        }
        else if(google.translate)
        {
            google_initialized = true;
            setTimeout(google_auto_translate, 2500);
        }
        else
            setTimeout(google_auto_translate, 750);
    }
window.onload = google_auto_translate;
       
       </script>
		</xsl:if>
		<!-- fi traduccio -->
		
		<xsl:apply-templates />
		<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-24615609-1']);
  _gaq.push(['_setDomainName', 'none']);
  _gaq.push(['_setAllowLinker', true]);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>
		</head>
	</xsl:template>

	<!-- TEMPLATE OTHERS -->
	<xsl:template match="banners|data|noresultscomments|logo|home|leftfilter|brand|text|fbutton|htmlform|resum|footer">
		<xsl:apply-templates />
	</xsl:template>

	<!-- TEMPLATE FOR NODES THAT NEED OPEN A CLOSE NODE -->
	<xsl:template match="script|textarea">
		<xsl:element name="{name()}">
			<xsl:for-each select="@*">
				<xsl:attribute name="{name()}"><xsl:value-of select="." />
				</xsl:attribute>
			</xsl:for-each>
			<xsl:apply-templates />
			<xsl:text> </xsl:text>
		</xsl:element>
	</xsl:template>

	<!-- TEMPLATE HEADERS -->

	<xsl:template match="headers">
			<xsl:apply-templates select="logo"/>
			<xsl:apply-templates select="capsalera"/>		
	</xsl:template>

	<!-- TEMPLATE BODY -->
	<xsl:template match="page">
		<body>
			<xsl:if test="boolean(@onload)">
				  <xsl:attribute name="onload">
			      <xsl:value-of select="@onload" />
			      </xsl:attribute>
			</xsl:if>
            
            <!-- Barra Corporativa -->
            <xsl:apply-templates select="headers/brand" />

            
			<!-- Main container -->
			<div id="marc-web">
				<xsl:apply-templates select="headers" />							
				<xsl:apply-templates select="central" />
				<xsl:apply-templates select="bright" />		
			</div>
			<xsl:apply-templates select="footers" />	
			<div id="spinner" class="spinner" style="display:none;">
				<img id="img-spinner" src="/tpl/common/img/spinner.gif" alt="Loading"/>
			</div>		
		</body>
	</xsl:template>
	
		<!-- TEMPLATE CENTRAL -->
	<xsl:template match="central">
	    <xsl:apply-templates select="search" />
	    <xsl:apply-templates select="detall" />
	    <xsl:apply-templates select="content" />
	    <xsl:if test="not(boolean(search)) and not(boolean(detall)) and not(boolean(content))">
		    <div id="contenidor-home">	
		    <xsl:apply-templates select="classall" />      
		    <xsl:apply-templates select="hrecom" />	 
		    <xsl:if test="boolean(banner-right) or boolean(datepicker) or boolean(bcnproposa)"> 
			    <div id="home-col-0">	    
			    <xsl:apply-templates select="datepicker" />	  
			    <xsl:apply-templates select="bcnproposa" />	 
			    </div> 
			    <div id="home-col-1">
				      <xsl:apply-templates select="cartellera" />
				      <xsl:apply-templates select="banners" />    
				      <xsl:apply-templates select="mviewedmonth" />	
				      <xsl:apply-templates select="banner-right" />    
			    </div>
		    </xsl:if>       		
		    </div>
		</xsl:if>
	</xsl:template>
	
	<xsl:template match="search">
	<div id="contenidor">	
	 <div id="contenidor-2">	
	    <xsl:apply-templates select="/html/page/msg" />	
	    <div id="ajx-search">
	        <xsl:apply-templates select="queryresponse/list/found" />
	        <xsl:apply-templates select="noresults" />
	        <xsl:apply-templates select="noresultscomments" />
			<xsl:apply-templates select="suggestions" />					
			<xsl:apply-templates select="bleft" />	    
			<div id="col-1">			
			<xsl:apply-templates select="queryresponse" />	
		    </div>
	    </div>
	    </div>
	 </div>   
	</xsl:template>
	
	<xsl:template match="noresults">
	<h1 class="notfound"><xsl:value-of select="query"/></h1>
	<xsl:for-each select="item">
	<p class="criteris"><xsl:value-of select="."/></p>
	</xsl:for-each>
	
	</xsl:template>
	
	<xsl:template match="content">
	<div id="contenidor">	
	 <div id="contenidor-2">	
	     <xsl:apply-templates select="/html/page/msg" />	
          <xsl:apply-templates  />	
	    </div>
	 </div>   
	</xsl:template>
	
	 <!-- DETALL -->

	<xsl:template match="detall">
	
	 <div id="contenidor">	
	 <div id="contenidor-2">
	    <xsl:apply-templates select="/html/page/msg" />	     	
		<div id="col-detall-0" >	
				<xsl:if test="//html/page/@lang = 'es' or //html/page/@lang = 'en'">
					<xsl:attribute name="class">goog-trans-section</xsl:attribute>
					<xsl:attribute name="lang">ca</xsl:attribute>					
				</xsl:if>	
					
		        <xsl:apply-templates select="share" />	
		        <div class="div-detall-1"><!-- prova -->	        
		        <xsl:for-each select="internetref/item">
					<img src="{irefvalue}" alt="{ireflabel}" />
				</xsl:for-each>
				
		        <h2>
		        <xsl:if test="entity_type = 'EQ'">
		        <xsl:attribute name="class">notranslate</xsl:attribute>	
		        </xsl:if>	       
				<xsl:if test="boolean(sectionname) and entity_type = 'EQ'">
				
				<xsl:value-of select="sectionname" disable-output-escaping="yes" /><xsl:text> - </xsl:text>
				</xsl:if>
				<xsl:value-of select="name"	disable-output-escaping="yes" />
				<xsl:if test="boolean(sigla) and entity_type = 'EQ'">
					(<xsl:value-of select="sigla" disable-output-escaping="yes" />)		
				</xsl:if>	
				</h2>
				
				<xsl:if test="//html/page/@lang = 'es' or //html/page/@lang = 'en'">
				<div class="goog-trans-control"></div>
				</xsl:if>			
				<xsl:if test="entity_type = 'AG'">
				<xsl:apply-templates select="likeit" />
				</xsl:if>		
			
            
                <xsl:if test="boolean(atencio_eq)">	
				 <p class="warning"><strong><xsl:value-of select="atencio_eq" disable-output-escaping="yes" /></strong></p>
				</xsl:if>
                 <xsl:if test="boolean(warning)">	
				 <p class="warning"><xsl:value-of select="warning" disable-output-escaping="yes" /></p>
				</xsl:if>
            
			   <dl>
				<xsl:if test="boolean(institutionname)">
					<dt><xsl:value-of select="institutionname/@label" /></dt><dd>
						<xsl:text> </xsl:text>
						<xsl:if test="boolean(institutionname/@href)">
						<a href="{institutionname/@href}">
						<span class="notranslate">
						<xsl:if test="boolean(sectionname)">
							<xsl:value-of select="sectionname" disable-output-escaping="yes" /><xsl:text> - </xsl:text>
						</xsl:if>					
						<xsl:value-of select="institutionname" />
						<xsl:if test="boolean(sigla)">
							(<xsl:value-of select="sigla" disable-output-escaping="yes" />)		
						</xsl:if>	
						</span>
						</a>
						</xsl:if>
						<xsl:if test="not(boolean(institutionname/@href))">
						<span class="notranslate">
						<xsl:if test="boolean(sectionname)">
							<xsl:value-of select="sectionname" disable-output-escaping="yes" /><xsl:text> - </xsl:text>
						</xsl:if>					
						<xsl:value-of select="institutionname" />
						<xsl:if test="boolean(sigla)">
							(<xsl:value-of select="sigla" disable-output-escaping="yes" />)		
						</xsl:if>	
						</span>
						</xsl:if>
					</dd>
				</xsl:if>
  			    <xsl:if test="boolean(begindate)">
         	    <dt><xsl:value-of select="begindate/@label2"/></dt><dd>&#160;<xsl:value-of select="begindate/@label"/>&#160;<xsl:value-of select="begindate"/>&#160;<xsl:value-of select="enddate/@label"/>&#160;<xsl:value-of select="enddate"/></dd>
         	    </xsl:if>
         	    <xsl:if test="boolean(date)">
         	    <dt><xsl:value-of select="date/@label"/><xsl:text> </xsl:text></dt><dd>&#160;<xsl:value-of select="date"/></dd>
         	    </xsl:if>	
         	   
         	   </dl>      	    	
         	   <dl class="adreca">
         	   <xsl:if	test="boolean(street)">	
	         	    <dt><xsl:value-of select="street/@label" />:&#160;</dt><dd><span class="notranslate"><xsl:value-of select="street" />,&#160;<xsl:value-of select="streetnum_i" /></span></dd>
	         	 </xsl:if>               
					<xsl:apply-templates select="district|barri|postalcode"/>	
                    <xsl:if test="not(city='Barcelona')"><dt><xsl:value-of select="city/@label" />:&#160;</dt><dd><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></dd></xsl:if>
					
				</dl>	
				<dl class="phones">	
					<xsl:for-each select="phones/item">
						<dt>
						<xsl:value-of select="label" />:&#160;</dt><dd><xsl:value-of select="phonenumber" />&#xa0;<xsl:value-of select="phonedesc" /></dd>
							
					</xsl:for-each>
				</dl>	
				<dl class="interestinfo">				
					
					<xsl:for-each select="interestinfo/item">					
						<dt><xsl:value-of select="label" />:<xsl:text> </xsl:text></dt>
						<xsl:choose>
							<xsl:when test="intercode='00100002' or intercode='00030002' or intercode='00030009'">								
								<dd><a href="mailto:{interinfo}"><xsl:value-of select="interinfo" /></a></dd>						
							</xsl:when>
							<xsl:when test="intercode='00100003' or intercode='00030003' or intercode='00100004' or intercode='00030012'">								
								<dd><a href="http://{interinfo}"><xsl:value-of select="interinfo" /></a></dd>						
							</xsl:when>	
							<xsl:otherwise>
								<dd><xsl:value-of select="interinfo" /></dd>
							</xsl:otherwise>
						</xsl:choose>						
					</xsl:for-each>
				  </dl>
				  
				  <xsl:if test="boolean(status)">	
				  <dl class="status">
		            <dd><xsl:value-of select="status/item/name" /></dd>
		          </dl>
		          </xsl:if>	
				  
				  <xsl:if test="boolean(accessibility)">	
				  <dl class="accessibility">
		            <!-- <dt><xsl:value-of select="accessibility/@label" />:</dt>-->
		            <dd><xsl:value-of select="accessibility" /></dd>
		          </dl>
		          </xsl:if>	
				  
				  <xsl:if test="boolean(titularitat)">	
				  <dl class="titularitat">
		            <dt><xsl:value-of select="titularitat/@label" />:</dt>
		            <dd><xsl:value-of select="titularitat" /></dd>
		          </dl>
		          </xsl:if>	          
          
		          <!-- <xsl:apply-templates select="serveis" /> -->
				
                 <xsl:if test="boolean(resum)">	
                 <div id="resum" class="notranslate">
				 <xsl:value-of select="resum" disable-output-escaping="yes" />
				 </div>
				 </xsl:if>	
				 <xsl:if test="boolean(texte)">	
				  <div id="texte" class="notranslate">
				 <xsl:value-of select="texte" disable-output-escaping="yes" />
				 </div>
				 </xsl:if>	
				 <xsl:if test="boolean(comments)">	
				 <p class="comments"><xsl:value-of select="comments" disable-output-escaping="yes" /></p>
				 </xsl:if>	
				
				
				</div>	
				
				<xsl:if test="boolean(timetable) or boolean(classification) or boolean(../ageq)">
				<div id="contenidor-pestanes">
					
					<h3 id="informacio"><a href="#div-informacio" class="">Informació</a></h3>
					<div id="div-informacio"  class="tabdetall">					
						<xsl:apply-templates select="timetable" />						
						<xsl:apply-templates select="relations" />
						<xsl:if test="boolean(classification)">
						<div>
						<p><span class="bold"><xsl:value-of select="classification/@label"/></span></p>				
						<xsl:apply-templates select="classification" />
						</div>
						</xsl:if>
		            </div>
		            
		            <xsl:if test="entity_type = 'EQ' and boolean(../ageq)">		          
				    <h3 id="esdeveniments"><a href="#div-esdeveniments">Esdeveniments</a></h3>
					<div id="div-esdeveniments" class="tabdetall">
					     <xsl:apply-templates select="../ageq" />
	                </div>	                
	                </xsl:if>
	                
	                <xsl:if test=" boolean(../aprop)">
	                <h3 id="aprop"><a href="#div-aprop">A prop d'aqui</a></h3>
	                <div id="div-aprop" class="tabdetall">
					    <h4><xsl:value-of select="../aprop/aparcs/@label" /></h4>
					    <xsl:apply-templates select="../aprop/aparcs/list/list_items/row/item" />
					    <h4><xsl:value-of select="../aprop/restaurants/@label" /></h4>
					    <xsl:apply-templates select="../aprop/restaurants/list/list_items/row/item" />
					     
	                </div>
	                </xsl:if>					
				</div>
				</xsl:if>
				<xsl:apply-templates select="../related" />
			</div>			
			<div id="col-detall-1">		
			<xsl:if test="boolean(gmapx)">
				<!-- google maps -->
				<script type="text/javascript" src="/tpl/guiabcn/jscripts/gmapv3.js"></script>
				<!-- <script src="http://maps.google.com/maps?file=api&amp;v=2&amp;key={apikey}" type="text/javascript"></script>-->
				
				
				<script type="text/javascript">			   		
				 $(document).bind('ready', function() {loadmapdetall(<xsl:value-of select="gmapx" />,<xsl:value-of select="gmapy" />,'');});				
			    </script>				 
				
				<!-- Planol -->				
			    <script language="javascript" type="text/javascript">
			    $(window).load(function () {
			        MapObject = $('.mapa_guia').map_guia({UseHistory : false, Width : 265, Height : 265, x : "<xsl:value-of select="coordaddressx" />", y : "<xsl:value-of select="coordaddressy" />", z: "5", capas : "P001K001K006K014",plot : "<xsl:value-of select="coordaddressx" />,<xsl:value-of select="coordaddressy" />" });
			    });
			    </script>	
			    <div id="mapadetall" ><div id="detallmap"></div></div>
				<div id="mapaplanol" class="mapa_guia"></div>				
				<div id="mapastreet" ><div id="streetview"></div></div>	  
				<!--  <img src="http://w20.bcn.cat/GuiaHandler/GuiaHandler.ashx/guia.cca?x={coordaddressx}&amp;y={coordaddressy}&amp;z=5&amp;c=K001K006K014&amp;w=400&amp;h=300&amp;p={coordaddressx},{coordaddressy}"/>
				-->
				<div id="changemap">
				     <a class="active" href="#mapaplanol">Plànol BCN</a> | <a href="#mapadetall">Google Maps</a> | <a href="#mapastreet">Street view</a>
	            </div>			    
			    <div class="com-anar">
			        <a href="{link/@href}"><img src="/tpl/common/img/com-anar.{//html/page/@lang}.png" /></a>
			    </div>		
			    </xsl:if>	   
			    <xsl:apply-templates select="recommend" />
			</div>
		</div>
		</div>
	</xsl:template>
	
	<xsl:template match="serveis">
	 <dl class="serveis">
		            <!-- <dt>Serveis:</dt> -->
		<xsl:for-each select="item">					
			<dd>
			<xsl:if	test="code = '002200400'">
				<xsl:attribute name="class"><xsl:text>menjador</xsl:text></xsl:attribute>					
			</xsl:if>
			<xsl:if	test="code = '002200410'">
				<xsl:attribute name="class"><xsl:text>cuina</xsl:text></xsl:attribute>					
			</xsl:if>
			<xsl:if	test="code = '002200412'">
				<xsl:attribute name="class"><xsl:text>acollida</xsl:text></xsl:attribute>					
			</xsl:if>
			<xsl:if	test="code = '002200441'">
				<xsl:attribute name="class"><xsl:text>extraescolars</xsl:text></xsl:attribute>					
			</xsl:if>
			<xsl:value-of select="label" />			
			</dd>		
		</xsl:for-each> 
		            
	 </dl>			  
	</xsl:template>	
	
	<xsl:template match="district|barri|postalcode">
	<dt><xsl:value-of select="@label" />:&#160;</dt><dd><span class="notranslate"><xsl:value-of select="." /></span></dd>
	</xsl:template>

	<!-- capsalera -->
	<xsl:template match="capsalera">
	<div id="capsalera">
		<div id="contenidor-formulari">
			<div id="formulari">
				<h1>
					<img alt="{@alt}" src="/tpl/common/img/quebusques.{//html/page/@lang}.png" />
				</h1>
				<form id="frm-cerca" enctype="multipart/form-data"	action="index.php" method="get">
					<ul>
						
						<li id="q-cercar" style="opacity: 1;">
						<input type="hidden" name="pg" value="search" />
						<xsl:if test="boolean(//html/page/central/search)">
							<input id="q" type="text" name="q" value="{//html/page/central/search/writtenquery}"  />
						</xsl:if>	
						<xsl:if test="not(boolean(//html/page/central/search))">
							<input class="default-value" id="q" type="text" name="q" value="{@default}" />
						</xsl:if>	
						</li>
						<li id="input-cercar" style="opacity: 1;">
							<input class="cerca" type="submit" 	value="{@label}" />
						</li>
						
					</ul>
				</form>			
		         <xsl:apply-templates />
			</div>  
			 <xsl:apply-templates select="../../central/classhome" />
			 <xsl:apply-templates select="../../central/classsearch" />
		</div>
	</div>	
	</xsl:template>
	
	<!-- TEMPLATE CERCA-AVANSADA -->
	<xsl:template match="cerca-avansada">

	<div id="div-cerca-av" class="js"> 
	    
	      <h2><xsl:value-of select="pestanes/@label"/></h2>
		
		  
		  
		
		
		<h3 class="active tota-guia"><a href="#tab-totalaguia" class="active"><xsl:value-of select="pestanes/totalaguia"/></a></h3>
		
		<div id="tab-totalaguia" class="tabform">	
			<form id="frm-cerca-tota" name="cerca-tota" enctype="multipart/form-data" action="index.php" method="get">
			    <input type="hidden" value="search" name="pg" />
	        <xsl:apply-templates select="utilitzant"><xsl:with-param name="form" select="'1'"/></xsl:apply-templates>
	        <xsl:apply-templates select="adresa"><xsl:with-param name="frmname" select="'cerca-tota'"/><xsl:with-param name="form" select="'1'"/></xsl:apply-templates>
	         <xsl:apply-templates select="resultats"><xsl:with-param name="form" select="'1'"/></xsl:apply-templates>
			<div class="envia-av">
					<input class="cerca" type="submit" value="{../@label}" />
				</div>
			</form>
		</div>
		
		<h3 class="agenda"><a href="#tab-agenda" class="tab-agenda"><xsl:value-of select="pestanes/agenda"/></a></h3>
		
		
		<div id="tab-agenda" class="tabform">
	     	<form id="frm-cerca-agenda" name="cerca-agenda" enctype="multipart/form-data" action="index.php" method="get">
	     	<input type="hidden" value="search" name="pg" />
	     	<input type="hidden" value="AG" name="type" />
	     	<xsl:apply-templates select="pertemesagenda"><xsl:with-param name="form" select="'2'"/></xsl:apply-templates>
	     	<xsl:apply-templates select="datapreus"/>
	     	<xsl:apply-templates select="utilitzant"><xsl:with-param name="form" select="'2'"/></xsl:apply-templates>
		    <xsl:apply-templates select="adresa"><xsl:with-param name="frmname" select="'cerca-agenda'"/><xsl:with-param name="form" select="'2'"/></xsl:apply-templates>
		    <xsl:apply-templates select="resultats"><xsl:with-param name="form" select="'2'"/></xsl:apply-templates>
			<div class="envia-av">
		       <input class="cerca" type="submit" value="{../@label}" />
			</div>
	        </form>
        </div>
        
        <h3 class="directoris"><a href="#tab-directoris"><xsl:value-of select="pestanes/directori"/></a></h3>
        
	   	<div id="tab-directoris" class="tabform">
	   	   <form id="frm-cerca-directori" name="cerca-directori" enctype="multipart/form-data" action="index.php" method="get">
	    	<input type="hidden" value="search" name="pg" />
	    	<input type="hidden" value="EQ" name="type" />
	    	<xsl:apply-templates select="pertemesdirectori"><xsl:with-param name="form" select="'3'"/></xsl:apply-templates>
	     	<xsl:apply-templates select="utilitzant"><xsl:with-param name="form" select="'3'"/></xsl:apply-templates>
		    <xsl:apply-templates select="adresa"><xsl:with-param name="frmname" select="'cerca-directori'"/><xsl:with-param name="form" select="'3'"/></xsl:apply-templates>
		    <xsl:apply-templates select="resultats"><xsl:with-param name="form" select="'3'"/></xsl:apply-templates>
		    	<div class="envia-av">
					<input class="cerca" type="submit" value="{../@label}" />
				</div>
   			</form>     
   		</div>
   	</div>
   		
   	</xsl:template>
	
	<!-- TEMPLATE utilitzant -->
	<xsl:template match="utilitzant">
	 <xsl:param name="form" />
	       <div class="section">				
					<ul>
					<li>
					<label><xsl:value-of select="@label"/></label>
					</li>
						<li>
							<input id="tot-{$form}" type="radio" value="1" name="t" checked="checked"/>
							<label for="tot-{$form}"><xsl:value-of select="tot"/></label>
						</li>
						<li>
							<input id="qualsevol-{$form}" type="radio" value="2" name="t" />
							<label for="qualsevol-{$form}"><xsl:value-of select="qualsevol"/></label>
						</li>
						<li>
							<input id="frase-{$form}" type="radio" value="3" name="t" />
							<label for="frase-{$form}"><xsl:value-of select="frase"/></label>
						</li>		
					</ul>
					<p class="input-q">						
						<input type="text" name="q"/>
					</p>				
				</div>				
	</xsl:template>
	<!-- TEMPLATE utilitzant -->
	<xsl:template match="adresa">
	<xsl:param name="form" tunnel="yes"/>
	 <div class="section" >
          <p class="barri">
            <label for="format{$form}"><xsl:value-of select="district/@label"/></label>
            <select id="format{$form}" name="districtstr">
              <option value="*" selected="selected">*<xsl:value-of select="district"/></option>              
                  <option value="Ciutat Vella">Ciutat Vella</option>
                  <option value="Eixample">Eixample</option>
                  <option value="Gràcia">Gràcia</option>
                  <option value="Horta-Guinardó">Horta-Guinardó</option> 
                  <option value="Les Corts">Les Corts</option> 
                  <option value="Nou Barris">Nou Barris</option>
                  <option value="Sant Andreu">Sant Andreu</option> 
                  <option value="Sant Martí">Sant Martí</option>
                  <option value="Sants-Montjuïc">Sants-Montjuïc</option> 
    			  <option value="Sarrià-Sant Gervasi">Sarrià-Sant Gervasi</option> 
            </select>                    
            <select id="barri{$form}" name="barristr">
              <option value="" selected="selected">Tots els barris</option>
            </select>
          </p>
          <p class="adresa">
           <label for="input-ad{$form}"><xsl:value-of select="carrer/@label"/></label><input class="default-value" id="input-ad{$form}" type="text" name="ad" value="{carrer/@default}" />    
           <input class="default-value" id="input-ini{$form}" type="text" value="{carrer/@default-ini}" name="ini"/> 
           <input class="default-value" id="input-fi{$form}" type="text" value="{carrer/@default-fi}"  name="fi"/>       
          </p>
          <script type="text/javascript">      	       
				var regionState = new DynamicOptionList();
				regionState.setFormName("<xsl:value-of select="$frmname"/>");
				regionState.addDependentFields("districtstr","barristr");
				regionState.forValue("*").addOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Ciutat Vella").addOptions("*<xsl:value-of select="carrer"/>","la Barceloneta","el Barri Gòtic","el Raval","Sant Pere, Santa Caterina i la Ribera");
				regionState.forValue("Eixample").addOptions("*<xsl:value-of select="carrer"/>","l'Antiga Esquerra de l'Eixample","la Nova Esquerra de l'Eixample","Dreta de l'Eixample","el Fort Pienc","Sagrada Família","Sant Antoni");
				regionState.forValue("Sants-Montjuïc").addOptions("*<xsl:value-of select="carrer"/>","la Bordeta","la Font de la Guatlla","Hostafrancs","la Marina de Port","la Marina del Prat Vermell","el Poble-sec","Sants","Sants - Badal","Montjuic","Zona Franca-Port");
				regionState.forValue("Les Corts").addOptions("*<xsl:value-of select="carrer"/>","Les Corts","la Maternitat i Sant Ramon","Pedralbes");
				regionState.forValue("Sarrià-Sant Gervasi").addOptions("*<xsl:value-of select="carrer"/>","el Putget i Farró","Sarrià","Sant Gervasi - la Bonanova","Sant Gervasi - Galvany","les Tres Torres","Vallvidrera, el Tibidabo i les Planes");
				regionState.forValue("Gràcia").addOptions("*<xsl:value-of select="carrer"/>","la Vila de Gràcia","Camp d'en Grassot i Gràcia Nova","la Salut","el Coll","Vallcarca i els Penitents");
				regionState.forValue("Horta-Guinardó").addOptions("*<xsl:value-of select="carrer"/>","el Baix Guinardó","el Guinardó","Can Baró","el Carmel","la Font d'en Fargues","Horta","la Clota","Montbau","Sant Genís dels Agudells","la Teixonera","la Vall d'Hebron");
				regionState.forValue("Nou Barris").addOptions("*<xsl:value-of select="carrer"/>","Can Peguera","Canyelles","Ciutat Meridiana","la Guineueta","Porta","Prosperitat","les Roquetes","Torre Baró","la Trinitat Nova","el Turó de la Peira","Vallbona","Verdum","Vilapicina i la Torre Llobeta");
				regionState.forValue("Sant Andreu").addOptions("*<xsl:value-of select="carrer"/>","Baró de Viver","Bon Pastor","el Congrés i els Indians","Navas","Sant Andreu de Palomar","la Sagrera","Trinitat Vella");
				regionState.forValue("Sant Martí").addOptions("*<xsl:value-of select="carrer"/>","el Besòs i el Maresme","el Clot","el Camp de l'Arpa del Clot","Diagonal Mar-Front Marítim del Poblenou","el Parc i la Llacuna del Poblenou","el Poblenou","Provençals del Poblenou","Sant Martí de Provençals","la Verneda i la Pau","la Vila Olímpica del Poblenou");
				regionState.forValue("*").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Ciutat Vella").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Eixample").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Sants-Montjuïc").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Les Corts").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Sarrià-Sant Gervasi").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Gràcia").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Horta-Guinardó").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Nou Barris").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Sant Andreu").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.forValue("Sant Martí").setDefaultOptions("*<xsl:value-of select="carrer"/>");
				regionState.selectFirstOption = false;
		</script>         
      </div>      
	</xsl:template>
	
   <!-- TEMPLATE resultats -->
	<xsl:template match="resultats">
	<xsl:param name="form" tunnel="yes"/>
			<div class="section">
					<p>
						<label for="num{$form}"><xsl:value-of select="@label"/></label>
						<select id="num{$form}" name="nr">
						<xsl:for-each select="item">
	                            <option value="{code}"><xsl:value-of select="name"/></option>
	                      </xsl:for-each>     
						</select>
					</p>
				</div>
	</xsl:template>
	
	   <!-- TEMPLATE pertemesagenda -->
	<xsl:template match="pertemesagenda|pertemesdirectori">
	<xsl:param name="form" tunnel="yes"/>
	<div class="section">
          <p>
            <label for="code{$form}"> <xsl:value-of select="@label"/></label>
            <select id="code{$form}" name="code0">
              <option value="" selected="selected"><xsl:value-of select="."/></option>
              <xsl:if test="local-name()='pertemesagenda'"> 
	              <xsl:for-each select="//html/page/classform/agenda/item">
	                    <option value="{code}"><xsl:value-of select="name"/></option>
	             </xsl:for-each>
             </xsl:if>
             <xsl:if test="local-name()='pertemesdirectori'"> 
	              <xsl:for-each select="//html/page/classform/directori/item">
	                    <option value="{code}"><xsl:value-of select="name"/></option>
	             </xsl:for-each>
             </xsl:if>
            </select>
          </p>
      </div>    
	</xsl:template>
	
		<!-- TEMPLATE datapreus -->
	<xsl:template match="datapreus">
	          <div id="divDateContainer">
	             <div class="datepickerBorder">
	                  <div class="datepickerContainer">
	             		<div id="divDate"></div> 
						<xsl:apply-templates select="data"/>
	             	</div>
	             </div>
             </div>
	 <div class="section" id="cerca-data-preus">
          <p>
            <label for="formDate"><xsl:value-of select="data/@label"/></label>
             <input id="formDate" value="" name="dt"/>
    
             <label for="preu"><xsl:value-of select="preu/@label"/></label>                 
             <select id="preu" name="p">
                <xsl:for-each select="preu/item">
	                    <option value="{code}"><xsl:value-of select="name"/></option>
	             </xsl:for-each>             
            </select>
          </p>
      </div>    
    </xsl:template>
	
	<!-- TEMPLATE CLASSHOME -->
	<xsl:template match="classhome">
	<div id="directori-home">	   
	   <div class="agenda">	       
	       <xsl:apply-templates select="agendahome" />
	   </div>
	  <div class="directori">
		   <xsl:apply-templates select="direchome" />
      </div>   
	</div>
	</xsl:template>
	
    <!-- TEMPLATE direchome|agendahom -->
	<xsl:template match="direchome|agendahome">		
			<h2>
				<xsl:value-of select="@label" />                      
			</h2>	
			<ul class="col1">
				<xsl:for-each select="item1[position() &#60; 6]">
				<li><a href="{@href}"><xsl:value-of select="name" /></a></li>		
				</xsl:for-each>				
			</ul>	
			<ul class="col2">
				<xsl:for-each select="item2[position() &#60; 6]">
				<li><a href="{@href}"><xsl:value-of select="name" /></a></li>		
				</xsl:for-each>				
			</ul>		
			<p class="mostra-tots"><a class="iframe" href="{more/@href}"><xsl:value-of select="more/@label" /></a></p>
	</xsl:template>
	
		<!-- TEMPLATE CLASSHOME -->
	<xsl:template match="classsearch">
	<div id="directori-home" class="search">	   
	   <div class="agenda">	       
	       <h2>
	       <a class="iframe" href="{agenda/more/@href}"><xsl:value-of select="agenda/@label" /></a>
	       
	       <!-- <span><a class="iframe" href="{agenda/more/@href}"><xsl:value-of select="agenda/more/@label" /></a></span> -->
	       </h2>
	   </div>
	  <div class="directori">
		   <h2>
		   <a class="iframe" href="{directoris/more/@href}"><xsl:value-of select="directoris/@label" /></a>
		   
		   <!-- <span><a class="iframe" href="{directoris/more/@href}"><xsl:value-of select="directoris/more/@label" /></a></span> -->
		   </h2>
      </div>   
	</div>
	</xsl:template>
	
	<xsl:template match="found">
    	<h2>				
		<xsl:value-of select="@vis" /><xsl:text> </xsl:text><span><xsl:value-of select="@from" /></span><xsl:text> </xsl:text><xsl:value-of select="@al" /><xsl:text> </xsl:text><span><xsl:value-of select="@to" /></span><xsl:text> </xsl:text><xsl:value-of select="@de" /><xsl:text> </xsl:text><span><xsl:value-of select="@total" /></span>
		<xsl:if test="not(../../../writtenquery = '')">
		<xsl:text> </xsl:text>  
		<xsl:value-of select="@results" />
        <span>“<xsl:value-of select="../../../writtenquery" />”</span>
        </xsl:if>
        <xsl:text>.</xsl:text>         
         </h2>  
					
    </xsl:template>

	<!-- TEMPLATE BLEFT -->
	<xsl:template match="bleft|central/bleft">
		<div id="col-0">
			<xsl:for-each select="*">
                <xsl:apply-templates select="current()" />
  		    </xsl:for-each>
		</div>
	</xsl:template>

	<!-- TEMPLATE BRIGHT -->
	<xsl:template match="bright">
		<div id="col-2">
			<xsl:for-each select="*">					
			     <xsl:apply-templates select="current()" />					
			</xsl:for-each>
		</div>
	</xsl:template>


	<!-- TEMPLATE SBOX -->
	<xsl:template match="sbox">
		<div
			style="margin: 0.2cm 0cm 0.2cm 0cm;border-bottom: solid 1px #e5e5e5;">
			<xsl:apply-templates />
		</div>
	</xsl:template>


	<!-- TEMPLATE MSG -->
	<xsl:template match="msg">
		<xsl:apply-templates />
	</xsl:template>

	<xsl:template match="position">
	<ul id="fil-ariadna">
		<li>
			<a href="http://www.bcn.cat">bcn.cat</a>
		</li>
		<xsl:for-each select="pos">							
		<xsl:choose>
			<xsl:when test="boolean(@href)">
			<li>
				<a class="msg_position" href="{@href}"><xsl:value-of select="." /></a>
			</li>	
			</xsl:when>
			<xsl:otherwise>
			<li class="last"><xsl:value-of select="." /></li>	
			</xsl:otherwise>
		</xsl:choose>
	</xsl:for-each>
	</ul>
	</xsl:template>
	
	<!-- TEMPLATE ALERTS-->
	<xsl:template match="alerts">
		<ul id="fil-ariadna">
			<xsl:for-each select="msg">
				<li>					
						<xsl:value-of select="." />
			    </li>
			</xsl:for-each>
		</ul>
	</xsl:template>


	<!-- TEMPLATE FOOTERS -->

	<xsl:template match="footers">
	<div id="info-ajbarna">
		<p id="copy">
			<a
				href="http://www.bcn.cat/catala/copyright/welcome2.htm">&#169;
				Ajuntament de Barcelona
			</a>
		</p>
		<address>
			<abbr title="Plaça">Pl</abbr>
			. Sant Jaume, 1 | 08002 Barcelona |
			<abbr title="Telèfon">Tel</abbr>
			. Centraleta 93 402 70 00 |
			<a
				href="http://w3.bcn.es/V61/Home/V61HomeLinkPl/0,2687,200713899_215467956_1,00.html">
				Informació
			</a>
		</address>
	</div>
	</xsl:template>

	<!-- TEMPLATE COMMENT -->
	<xsl:template match="comment">
		<table class="comment">
			<tr>
				<td class="comment">
					<xsl:apply-templates />
				</td>
			</tr>
		</table>
	</xsl:template>

	<!-- *********************************************** -->

	<!-- TEMPLATE FORMDEF -->
	<xsl:template match="formdef">
		<table class="forms_border">
			<tr>
				<td class="forms_border">
					<xsl:apply-templates select="htmlform" />
				</td>
			<!-- </tr>
			<tr> -->
				<td class="forms_border">
					<a class="boton"
						href="javascript:document.getElementById('{@name}').submit();">
						<xsl:apply-templates select="fbutton" />
					</a>
				</td>
			</tr>
		</table>
	</xsl:template>

	<!-- TEMPLATE LISTS -->

	<xsl:template match="queryresponse|related">	
		    <xsl:apply-templates select="list" />
	</xsl:template>
	
	<xsl:template match="filters">	
		<xsl:if test="boolean(item)"> 
		<div class="filtres">
		<h3><span><xsl:value-of select="@label" /></span></h3>
		   <ul>
		      <xsl:for-each select="item">
		          <li><xsl:value-of select="." /><a href="{@href}"><img src="/tpl/common/img/x-filter.gif" alt="" /></a></li>			
		   		</xsl:for-each>
		   </ul>
        </div>
   		</xsl:if>   
	</xsl:template>

	<xsl:template match="facetlist">
	    <h3 class="titol"><xsl:value-of select="@label" /></h3>
		<xsl:for-each select="*">
		<div class="caixa">
		    <xsl:if test="local-name()!='type'">
			<h4><xsl:value-of select="@name" /></h4>
			</xsl:if>
			<xsl:if test="boolean(back)">
			<ul>
			<xsl:for-each select="back">
			    <li><xsl:value-of select="@name" />
				<a style="font: normal 12px arial;" href="{@href}">
					 (x)
				</a></li>
			</xsl:for-each>
			</ul>	
			</xsl:if>
						<ul>
				<xsl:for-each select="item">
					<xsl:choose>
						<xsl:when test="boolean(@href)">
							<li>
								<a href="{@href}"><xsl:value-of select="@name" /><xsl:text> </xsl:text><xsl:if	test="normalize-space(.)!=''"><xsl:text>(</xsl:text><xsl:value-of select="."/><xsl:text>)</xsl:text></xsl:if>
								</a>
							</li>
						</xsl:when>
						<xsl:otherwise>								
							<li>
								<xsl:value-of select="@name" />
							</li>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</ul>			
	    </div>
		</xsl:for-each>
	</xsl:template>
	
	<xsl:template match="queryresponse/list">	    
		<div id="resultats">
			<div id="accions">
			 	
			  <xsl:apply-templates select="lst_info/sort" />
			  <xsl:apply-templates select="lst_info/numrows" />
			 
			 <ul >	      
              <li> <a class="addthis_button_email at300b" href="#"><img src="/tpl/common/img/icos/ico-envia.gif" alt="Envia a un amic." /></a> </li>
              <li class="print"><a href="#" onclick="window.print();return false;"><img src="/tpl/common/img/icos/ico-print.gif" alt="Imprimeix pàgina." /></a></li>
              <li><a href="?pg=rss"><img src="/tpl/common/img/icos/ico-rss.gif" alt="RSS" /></a></li>
            </ul>
            </div> 		
            <xsl:apply-templates select="../../../gmap" mode="cerca" />            
			<xsl:apply-templates select="list_items" />				
			<xsl:apply-templates select="../share" />			
		</div>		
	</xsl:template>
	
	<xsl:template match="related/list">	
	<div id="related">  
		<h3><xsl:value-of select="../@label" /></h3> 
		<div id="div-related">  
		    
		   
		   
		    
		     <div class="prev"> <a href="{lst_info/pags/prev/@href}"><img src="/tpl/common/img/prev-relacionats.png" alt="" /></a>	</div>
									
			
			                
		    <xsl:apply-templates select="list_items/row/item"/>	
		   
		    <div class="next">
		     <xsl:if test="boolean(lst_info/pags/next)">
		    <a href="{lst_info/pags/next/@href}">
									<img src="/tpl/common/img/next-relacionats.png" alt="" />
								</a>
			</xsl:if>						
			</div>
							  		
		</div>
	</div>		
	
	</xsl:template>
	
	<xsl:template match="sort">				
		<h4><xsl:value-of select="@label" /></h4>
		   <ul class="endresat">
				<xsl:for-each select="*">
					<xsl:choose>
					   <xsl:when test="not(name()=parent::sort/@selected)">
							<li><a class="sort" href="{@href}"><xsl:value-of select="." /></a></li>
					   </xsl:when>
					   <xsl:otherwise>
							<li><span class="selected"><xsl:value-of select="." /></span></li>
					   </xsl:otherwise>
				</xsl:choose>
		</xsl:for-each>
		  </ul>			
	</xsl:template>

	<xsl:template match="lst_info">
	       <xsl:if test="boolean(pags)">
	       <div class="paginador">

	       <xsl:if test="boolean(pags/prev)">
			<a class="anterior" href="{pags/prev/@href}">Anteriors</a>
		  </xsl:if>         
        <xsl:if test="boolean(pags/pag)">
        <ul>   
		<xsl:for-each select="pags/pag">
			<xsl:choose>
				<xsl:when test="boolean(@href)">
					<li><a 
						href="{@href}">
						<xsl:value-of select="." />
					</a>
					</li>
				</xsl:when>
				<xsl:otherwise>
					 <li>
						<span class="bold">
						<xsl:value-of select="." />
						</span>
					</li>
				</xsl:otherwise>
		    </xsl:choose>
		</xsl:for-each>
		</ul>
		</xsl:if>
          <xsl:if test="boolean(pags/next)">
				<a class="seguent actiu"
					href="{pags/next/@href}">
					Següents
				</a>
			</xsl:if>         
          </div>
          </xsl:if>
	</xsl:template>

	<!-- TEMPLATE SUGGETIONS -->
	<xsl:template match="suggestions">
			<h2>
			<xsl:value-of select="@name" /><xsl:text> </xsl:text>
			<span>“<a href="{@href}"><xsl:value-of select="." /></a>”</span>.
			</h2>	
	</xsl:template>

	<!-- TEMPLATE MVIEWED -->
	<xsl:template match="mviewedmonth">
		<div id="mviewed">
		<div class="contenidor-home-2">
			<!-- <div id="div-pestanes">
			    <ul>			   
			     <li id="mvistos" class="active"><a href="#div-mvistos"><xsl:value-of select="@label" /></a></li>
			     <li id="mvalorats"><a href="#div-mvalorats"><xsl:value-of select="../mvotedmonth/@label" /></a></li>			   
			   </ul>	
		   	</div> -->		  
		   	<h2 id="mvistos" class="active"><a href="#div-mvistos"><xsl:value-of select="@label" /></a></h2>		  
		   	<div id="div-mvistos" class="tabmviewed">   
            <xsl:apply-templates select="item"/>
         	</div>         
		   	<h2 id="mvalorats" class="active"><a href="#div-mvalorats"><xsl:value-of select="../mvotedmonth/@label" /></a></h2>		   		
			<div id="div-mvalorats" class="tabmviewed">
			   <xsl:apply-templates select="../mvotedmonth/item"/>
			</div>				
		
		</div>	
		</div>
	</xsl:template>
	
	<xsl:template match="recommend">
	<div id="recommend">		
			<div id="div-recommend">
			    <h3><xsl:value-of select="@label" /></h3>
			     <xsl:apply-templates>
				  	<xsl:with-param name="jerarquia" select="'titol'"/> 
			    </xsl:apply-templates>
			</div>		
	</div>
	</xsl:template>
	

	<xsl:template match="mvotedmonth/item|mviewedmonth/item|recommend/item">  	
	
	<xsl:param name="jerarquia" />	
	
		<div>	
			<xsl:if test="position() = last()">
			<xsl:attribute name="class">last</xsl:attribute>
			</xsl:if>
			<xsl:if test="not(position() = last()) and position() mod 2 = 0">
			<xsl:attribute name="class">par</xsl:attribute>
			</xsl:if>
			<xsl:if test="entity_type = 'AG'">
			<!-- <img src="/tpl/common/img/agenda-petita.png" alt=""/>-->
			
			<xsl:choose>
				<xsl:when test="$jerarquia = 'titol'">
					<h4><a href="{@href}"><xsl:value-of select="name" /></a></h4>
				</xsl:when>
				<xsl:otherwise>
					<h3><a href="{@href}"><xsl:value-of select="name" /></a></h3>
				</xsl:otherwise>
			</xsl:choose>
			
			<dl>
				<dt class="on"><xsl:value-of select="institutionname/@label"/><xsl:text> </xsl:text></dt>
				<dd><a href="{institutionname/@href}"><span class="notranslate"><xsl:value-of select="institutionname" /></span></a></dd>
			</dl>
			<p class="cat-agenda"> 
	         			<span >         		
	         			<xsl:value-of select="type" />         		
	         			</span>
	         		  </p>
			</xsl:if>
			<xsl:if test="entity_type = 'EQ'">
			<!-- <img src="/tpl/common/img/carpetes-petita.png" alt=""/> -->
			
			<xsl:choose>
				<xsl:when test="$jerarquia = 'titol'">
			
					<h4><a href="{@href}">					
						<xsl:if test="boolean(sectionname)">
							<xsl:value-of select="sectionname" /><xsl:text> - </xsl:text>
						</xsl:if>					    
						<xsl:value-of select="name" />					
					</a></h4>
			</xsl:when>
			<xsl:otherwise>
			
			      <h3><a href="{@href}">					
						<xsl:if test="boolean(sectionname)">
							<xsl:value-of select="sectionname" /><xsl:text> - </xsl:text>
						</xsl:if>					    
						<xsl:value-of select="name" />					
					</a></h3>
			
			</xsl:otherwise>
			</xsl:choose>
			
			<p><span class="notranslate"><xsl:value-of select="street" /><xsl:text> </xsl:text><xsl:value-of select="streetnum_i" /><xsl:text> </xsl:text>
			  <xsl:if test="boolean(district)">(<xsl:value-of select="district" />)</xsl:if>
			  <xsl:if test="not(boolean(district))">(<xsl:value-of select="city" />)</xsl:if>
			  </span></p>
			  <p class="cat-equip"> 
	         			<span >         		
	         			<xsl:value-of select="type" />         		
	         			</span>
	         		  </p>
			</xsl:if>					  		
		</div>				
	</xsl:template>
	
	<!-- Agenda del equipament -->
	<xsl:template match="ageq/item">  		
		<div>	
			<xsl:if test="position() = last()">
			<xsl:attribute name="class">last</xsl:attribute>
			</xsl:if>
			<xsl:if test="not(position() = last()) and position() mod 2 = 0">
			<xsl:attribute name="class">par</xsl:attribute>
			</xsl:if>		
			<p><a href="{@href}">
					<xsl:value-of select="name" />
			</a></p>	
			<xsl:if test="boolean(begindate)">
         	    <p class="data"><span class="bold"><xsl:value-of select="begindate/@label2"/><xsl:text> </xsl:text></span><xsl:value-of select="begindate/@label"/>&#160;<xsl:value-of select="begindate"/>&#160;<xsl:value-of select="enddate/@label"/>&#160;<xsl:value-of select="enddate"/></p>
         	</xsl:if>
         	<xsl:if test="boolean(date)">
         	    <p class="data"><span class="bold"><xsl:value-of select="date/@label"/><xsl:text> </xsl:text></span><xsl:value-of select="date"/></p>
         	</xsl:if>						  		
		</div>				
	</xsl:template>
	
		<!-- Agenda del equipament -->
	<xsl:template match="classification">  		
		<p>
		<xsl:for-each select="item">				
			<a href="{code/@href}"><xsl:value-of select="name" /></a>
			<xsl:if test="position() != last()">
			<xsl:text> / </xsl:text>
			</xsl:if>         		
         </xsl:for-each>						  		
		</p>				
	</xsl:template>


	<!-- TEMPLATE RELATIONS -->
	<xsl:template match="relations">
	<xsl:if test="boolean(section)">
	<div>
		<p><span class="bold"><xsl:value-of select="@labelsection" /></span></p>
			<xsl:for-each select="section">
				<p><a href="{@href}">
				    <span class="notranslate">					
					<xsl:value-of select="sectionname" />					
					</span>
					</a>
				</p>
		</xsl:for-each>
	</div>	
	</xsl:if>
	<xsl:if test="boolean(item)">
	<div>	
		<p><span class="bold"><xsl:value-of select="@label" /></span></p>
			<xsl:for-each select="item">
				<p><xsl:value-of select="direct" /><xsl:text> </xsl:text><a href="{@href}">
				<span class="notranslate">
					<xsl:if test="boolean(sectionname)">
					<xsl:value-of select="sectionname" /><xsl:text> - </xsl:text>
					</xsl:if>
				    <xsl:value-of select="institutionname" /></span>
					</a>
				<xsl:text>. </xsl:text><xsl:value-of select="comments" />	
				</p>
		</xsl:for-each>
	</div>	
	</xsl:if>
	</xsl:template>

	<!-- TEMPLATE TIMETABLE -->
	<xsl:template match="timetable">		
		 <xsl:if test="count(horari) = 1">
	    <div id="horari">
			<p><span class="bold"><xsl:value-of select="horari/@label" /></span></p>			
				<xsl:for-each select="horari">
				    <p><xsl:value-of select="periode"	disable-output-escaping="yes" /><xsl:text> </xsl:text><xsl:value-of select="dies"	disable-output-escaping="yes" /><xsl:text> </xsl:text><xsl:value-of select="hores" disable-output-escaping="yes" />
				    
				    <xsl:if test="boolean(observacions)"><xsl:text> </xsl:text><xsl:value-of select="observacions" disable-output-escaping="yes" /></xsl:if>
				    
				    </p>
				</xsl:for-each>			
			</div>
		
		 <xsl:if test="boolean(horari/preu)">
			<div id="preu">			
			<p><span class="bold"><xsl:value-of select="horari/preu/@label" /></span></p>
				<xsl:for-each select="horari/preu">				
				    <p><xsl:value-of select="."	disable-output-escaping="yes" /></p>
				</xsl:for-each>
			</div>
		</xsl:if>
		</xsl:if>
		<!-- tabla horarios -->
		<xsl:if test="count(horari) > 1">
	    <div id="horari">
			<p><span class="bold"><xsl:value-of select="horari/@label" /></span></p>			
			<table >	
				<xsl:for-each select="horari">
				<tr>
				<td style="vertical-align:top"><p><xsl:value-of select="periode"	disable-output-escaping="yes" /></p></td>
				<td style="vertical-align:top"><p><xsl:value-of select="dies"	disable-output-escaping="yes" /></p></td>
				<td style="vertical-align:top"><p><xsl:value-of select="hores" disable-output-escaping="yes" /></p></td>
				<td style="vertical-align:top"><p><xsl:value-of select="preu" disable-output-escaping="yes" /></p></td>
				<td style="vertical-align:top"><p><xsl:value-of select="observacions" disable-output-escaping="yes" /></p></td>				    
				</tr>   
				</xsl:for-each>	
			</table>			
		</div>
		</xsl:if>
	</xsl:template>


    <!-- TEMPLATE ACTIVITATS PER DATA -->
	<xsl:template match="datepicker">	
		<div id="activitats-per-data">
		<div class="contenidor-home-2">
		 <h2><xsl:value-of select="@label"/></h2>
			<xsl:apply-templates />
		</div>
		</div>
	</xsl:template>

	<!-- TEMPLATE ACTIVITATS DESTACADES -->

	<xsl:template match="hrecom">
		<div id="activitats-destacades">
		<div class="contenidor-home-2">
	        <h2><xsl:value-of select="@label"/></h2>
	        <div id="mnudest">
	        <xsl:for-each select="temas/item">
	        
	        <span class="menudest {@selected}"><a href="{@href}"><xsl:value-of select="." /></a></span>
	        </xsl:for-each>	
	        </div>
	        <xsl:apply-templates select="../gmap" mode="destacats"/>
	        <div id="col-act-dest">	
	            <div id="act-dest-1">	
				     <xsl:apply-templates select="list/list_items/row[position() &lt; 3]"  />
				</div>
				<div id="act-dest-2">		
				    <xsl:apply-templates select="list/list_items/row[position() &gt; 2 and position() &lt; 6]"  />
				</div>		
			 </div>		 
			 <xsl:apply-templates select="list/lst_info" />
		</div>
		</div>
	</xsl:template>
	
	<xsl:template match="hrecom/list/list_items/row">
		<div class="bloc">
		<div class="contenidor">
		   <div>
			<xsl:if test="boolean(item/urlvideo)">
				<iframe title="YouTube video player" width="490"
					height="300" src="{item/urlvideo}" frameborder="0"
					allowfullscreen="1">
				</iframe>
			</xsl:if>	
			<xsl:if test="not(boolean(item/urlvideo))">
				<img src="{item/imatgeCos}" alt="" />
			</xsl:if>	
			 <h3><a href="{item/@href}">
					<xsl:value-of select="item/titol" disable-output-escaping="yes" />
			 </a></h3>		
			 <xsl:value-of select="item/resum" disable-output-escaping="yes"/>			
		  </div>
		 
		  <div class="data">
		  	<dl>
		  
		  <xsl:if test="boolean(item/institutionname)">
         	    <dt><xsl:value-of select="item/institutionname/@label"/><xsl:text> </xsl:text></dt>
         	      <dd>
         	      <span class="notranslate">
         	     <xsl:choose>
                    <xsl:when test="not(boolean(item/equipment_id))">         	     
         	         <xsl:value-of select="item/institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="item/sigla" disable-output-escaping="yes"/>
         	       </xsl:when>
         	        <xsl:otherwise>
                     <a href="{item/equipment_id/@href}"><xsl:value-of select="item/institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="item/sigla" disable-output-escaping="yes"/></a>
                    </xsl:otherwise>                
         	    </xsl:choose>
         	     </span>
         	     </dd>        	    
         	    
         	</xsl:if>
         
         	<xsl:if test="boolean(item/begindate)">
         	    <dt><xsl:value-of select="item/begindate/@label2"/><xsl:text> </xsl:text></dt><dd><xsl:value-of select="item/begindate/@label"/><xsl:text> </xsl:text><xsl:value-of select="item/begindate"/><xsl:text> </xsl:text><xsl:value-of select="item/enddate/@label"/><xsl:text> </xsl:text><xsl:value-of select="item/enddate"/></dd>
         	</xsl:if>
         	<xsl:if test="boolean(item/date)">
         	    <dt><xsl:value-of select="item/date/@label"/><xsl:text> </xsl:text></dt><dd><xsl:value-of select="item/date"/></dd>
         	</xsl:if> 
           </dl>
		 
		   <xsl:if test="boolean(item/gmapx)">  
		 	 <img class="icona" alt="" src="/tpl/guiabcn/images/ag{item/pos}.png" />
		 	</xsl:if>
		 
		  </div>
		</div>
		</div>  
	</xsl:template>
	
	<!-- TEMPLATE BARCELONA PROPOSA -->
	<xsl:template match="bcnproposa">
		<div id="bcn-proposa">
			<div class="contenidor-home-2">
				<h2><xsl:value-of select="@label"/></h2>	
				<xsl:for-each select="col">
				<ul>
				<xsl:for-each select="item">				
						<li><a href="{@href}"><xsl:value-of select="." /></a></li>					
				</xsl:for-each>
				</ul>
				</xsl:for-each>
			</div>
		</div>
	</xsl:template>
	
    <!-- END TEMPLATE RECOMANATS -->
    
    	<!-- TEMPLATE BARCELONA PROPOSA -->
	<xsl:template match="banner-right">
		<div class="banner-right">
			<div class="contenidor-home-2">
			<xsl:for-each select="item">		
			   <a class="mini" href="{@href}">
			   <xsl:if test="position()=last()">
			       <xsl:attribute name="class">last</xsl:attribute>
			   </xsl:if>
			   <img src="{@src}"  alt="{@alt}" />
			   </a>
			</xsl:for-each>	
			<xsl:if test="not(boolean(item))">
			   <a class="gran" href="{@href}"><img src="{@src}" alt="{@alt}" /></a>
			</xsl:if>		
			</div>
		</div>
	</xsl:template>

	<!-- TEMPLATE CLASS ALL **** -->

	<xsl:template match="classall">
	<div id="contenidor">	
	 <div id="contenidor-2"> 
	      <h2 class="classall"><xsl:value-of select="@label" /></h2>
	     <div class="categoria-col-1">	      
          <xsl:apply-templates select="item[position() &lt; 7]" />
         </div> 
         <div class="categoria-col-2">
          <xsl:apply-templates select="item[position() &gt; 7 and position() &lt; 12]" />
           </div> 
          <div class="categoria-col-3">
          <xsl:apply-templates select="item[position() &gt; 11]" />
          </div> 
	    </div> 
	 </div>	
	</xsl:template>

	<xsl:template match="classall/item">
	    <div id="categoria">
		<a href="{@href}" target="_parent">
			<xsl:value-of select="name" />
		</a>	
		<ul>
			<xsl:for-each select="subitem">
				<li>
					<a style="margin:0cm 0cm  0cm 0cm;" href="{@href}" target="_parent">
						<xsl:value-of select="name" />
					</a>
				</li>
			</xsl:for-each>
		</ul>
		</div>
	</xsl:template>

	<!-- TEMPLATES LIKEIT -->
	<xsl:template match="likeit">
	<div id="magrada">
		<a href="{@href}"><img src="/tpl/common/img/magrada.{//html/page/@lang}.png" alt="" /></a><span><xsl:value-of select="@votes" /></span>
	</div>	
	</xsl:template>

	<!-- TEMPLATES SHARE -->

	<xsl:template match="share">
	    <div id="compartir">
			<!-- AddThis Button BEGIN -->
			<div class="addthis_toolbox addthis_default_style ">
			<a class="addthis_button_preferred_1"></a>
			<a class="addthis_button_preferred_2"></a>
			<a class="addthis_button_preferred_3"></a>
			<a class="addthis_button_preferred_4"></a>
			<a class="addthis_button_preferred_5"></a>
			<a class="addthis_button_preferred_6"></a>
			<a class="addthis_button_preferred_7"></a>
			<a class="addthis_button_preferred_8"></a>
			<a class="addthis_button_compact"></a>
			<a class="addthis_counter addthis_bubble_style"></a>
			</div>
			
			<!-- AddThis Button END -->
       
		<noscript>
			<a title="Facebook, s'obre en finestra nova"
				href="http://www.facebook.com/share.php?u={@href}&amp;t={@label}"
				target="_blank">
				<img
					src="http://www.bcn.es/cataleg/tpl/common/img/ico-facebook.gif"
					alt="Facebook, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>
			<a title="Menéame, s'obre en finestra nova"
				href="http://meneame.net/submit.php?url={@href}" target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/icomena.gif"
					alt="Menéame, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>	
			<a title="Twitter, s'obre en finestra nova"
				href="http://twitter.com/share?counturl={@href}&amp;text={@label}"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/ico-twiter.gif"
					alt="Twitter, s'obre en finestra nova" height="14" width="14" />
			</a>
		    <xsl:text> </xsl:text>
			<a title="Delicious, s'obre en finestra nova"
				href="http://del.icio.us/post?url={@href}&amp;title={@label}"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/icodelici.gif"
					alt="Delicious, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>
			<a title="Google Bookmarks, s'obre en finestra nova"
				href="http://www.google.com/bookmarks/mark?op=add&amp;bkmk={@href}&amp;title={@label}"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/ico-google.gif"
					alt="Google Bookmarks, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>
			<a title="El meu Yahoo!, s'obre en finestra nova"
				href="http://es.bookmarks.yahoo.com/toolbar/savebm?u={@href}&amp;t={@label}"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/icoyahoo.gif"
					alt="El meu Yahoo!, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>
			<a title="MSN Reporter, s'obre en finestra nova"
				href="http://reporter.es.msn.com/?fn=contribute&amp;Title={@label}&amp;URL={@href}&amp;referrer=bcn.cat"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/ico-msn.gif"
					alt="MSN Reporter, s'obre en finestra nova" />
			</a>
			<xsl:text> </xsl:text>
			<a title="La Tafanera, s'obre en finestra nova"
				href="http://latafanera.cat/submit.php?url={@href}&amp;idioma=ca_ES"
				target="_blank">
				<img src="http://www.bcn.es/cataleg/tpl/common/img/ico-tafanera.gif" alt="La Tafanera, s'obre en finestra nova" />
			</a>
		  </noscript>
		 </div>
	</xsl:template>

	<xsl:template match="numrows">		
		<select href="{@href}" name="nr"> 
		<!--  <select name="nr" ONCHANGE="javascript:window.location='{@href}' + '&amp;nr=' + this.options[this.selectedIndex].value">--> 			
		
			<xsl:apply-templates />
		</select>
	</xsl:template>
	
	
   <xsl:template match="gmap" mode="cerca">   
   <div id="mapa">
            <div id="content-mapa">
              <h3 class="mapa"><span><xsl:value-of select="@label" /></span></h3>
              <div class="bloc-mapa">
                <xsl:apply-templates />
                <!-- <ul>                 
                  <li class="agenda">Agenda</li>
                  <li class="equipaments">Equipaments</li>
                </ul>-->
              </div>
            </div>
            <script type="text/javascript">
              $(document).bind('ready', function() {loadmapSearch('<xsl:value-of select="@lat"/>','<xsl:value-of select="@lng"/>',<xsl:value-of select="@level"/>,'<xsl:value-of select="@url"/>');});
              $('#ajx-search, #activitats-destacades').bind('ajaxStop', function() {loadmapSearch('<xsl:value-of select="@lat"/>','<xsl:value-of select="@lng"/>',<xsl:value-of select="@level"/>,'<xsl:value-of select="@url"/>');});
            </script>
   </div>
		
	</xsl:template>
	
	   <xsl:template match="gmap" mode="destacats">
            <div id="mapadest">  
                <xsl:apply-templates />
            <script type="text/javascript">
              $(document).bind('ready', function() {loadmapSearch('<xsl:value-of select="@lat"/>','<xsl:value-of select="@lng"/>',<xsl:value-of select="@level"/>,'<xsl:value-of select="@url"/>');});
              $('#ajx-search, #activitats-destacades').bind('ajaxStop', function() {loadmapSearch('<xsl:value-of select="@lat"/>','<xsl:value-of select="@lng"/>',<xsl:value-of select="@level"/>,'<xsl:value-of select="@url"/>');});
            </script>
             </div>
      </xsl:template>

<xsl:template match="list_items">
          <!-- Resultats de la cerca -->
          <div id="llista-resultats"> 
               <xsl:apply-templates select="../../../filters" />          
               <xsl:apply-templates select="row" />
               <xsl:apply-templates select="../lst_info" />
          </div>  
</xsl:template>


<xsl:template match="row">
   <xsl:apply-templates select="item" />
</xsl:template>

<xsl:template  match="row/item">
         <div>
         <xsl:if test="(1 + count(parent::*/preceding-sibling::*)) mod 2 = 1">
          <xsl:attribute name="class">par</xsl:attribute>
  		 </xsl:if> 
           <h3>
         		<a href="{@href}">
         			<xsl:value-of select="sectionname"
         				disable-output-escaping="yes" />
         			<xsl:if test="sectionname!=''">
         				<xsl:text> - </xsl:text>
         			</xsl:if>
         			<xsl:value-of select="name"
         				disable-output-escaping="yes" />&#160;<xsl:value-of select="sigla"
         				disable-output-escaping="yes" />	
         		</a>
         	</h3>
            <xsl:if test="boolean(internetref) and internetref!=''">
         		<xsl:element name="img">         			
         			<xsl:attribute name="id">listfoto</xsl:attribute>
         			<xsl:attribute name="src"><xsl:value-of select="internetref" />					</xsl:attribute>
         		</xsl:element>
         	</xsl:if>
         	<div class="dades">
         	
         	<xsl:if test="tp='EQ'">
      		    	
		         	<xsl:if test="boolean(address)">
		         	    <p><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
		         	    <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
		         	    </p>
		         	    <xsl:if test="not(city='Barcelona')"><p><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></p></xsl:if>
		         	</xsl:if>       	
		         	 
		         	<xsl:if test="boolean(phonenumber)">
		         	    <p><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></p>          	    
		         	</xsl:if>	
		        <p class="cat-equip"> 
	         	<span >         		
	         			<xsl:value-of select="type" />         		
	         	</span>
	         	</p>
		      		<!-- <img class="icona-tipus" alt="" src="/tpl/common/img/carpetes-petita.png"/>-->
	      	</xsl:if>
	      	
	      	<xsl:if test="tp='AG'">
	      	  
	      	     <dl>
         	
		         	<xsl:if test="boolean(begindate)">
		         	    <dt><xsl:value-of select="begindate/@label2"/></dt><dd><xsl:text> </xsl:text><xsl:value-of select="begindate/@label"/><xsl:text> </xsl:text><xsl:value-of select="begindate"/><xsl:text> </xsl:text><xsl:value-of select="enddate/@label"/><xsl:text> </xsl:text><xsl:value-of select="enddate"/></dd>
		         	</xsl:if>
		         	<xsl:if test="boolean(date)">
		         	    <dt><xsl:value-of select="date/@label"/></dt><dd><xsl:text> </xsl:text><xsl:value-of select="date"/></dd>
		         	</xsl:if>  
		         	<xsl:if test="boolean(institutionname)">
		         	    <dt><xsl:value-of select="institutionname/@label"/><xsl:text> </xsl:text></dt>
		         	    <dd><span class="notranslate">
		         	     <xsl:choose>
		                    <xsl:when test="not(boolean(equipment_id))">         	     
		         	         <xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/>
		         	       </xsl:when>
		         	        <xsl:otherwise>
		                     <a href="{equipment_id/@href}"><xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/></a>
		                    </xsl:otherwise>                
		         	    </xsl:choose>
		         	     </span></dd>   
		         	  
		    		 </xsl:if>
		       
		         	
		            <xsl:if test="boolean(address)">
			         	    <dd><span class="notranslate"><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
			         	    <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
			        	    </span></dd>
			         	    <xsl:if test="not(city='Barcelona')"><dd><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></dd></xsl:if>
			        </xsl:if>       	
			         	 
			        <xsl:if test="boolean(phonenumber)">
			        	    <dd><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></dd>          	    
			        </xsl:if>	
			        
			          </dl>
			          <p class="cat-agenda"> 
	         			<span >         		
	         			<xsl:value-of select="type" />         		
	         			</span>
	         		  </p>
			      	 	 <!-- <img class="icona-tipus" alt="" src="/tpl/common/img/agenda-petita.png"/>-->
			 </xsl:if>                 
            
            
           </div> 	
      		
      		
      		<xsl:if test="boolean(gmapx) and gmapx!=''">
      		
      		  <xsl:if test="tp='EQ'">
      		       <img class="icona" alt="" src="/tpl/guiabcn/images/eq{../@pos}.png"/>
      		  </xsl:if>
      		    <xsl:if test="tp='AG'">
      		       <img class="icona" alt="" src="/tpl/guiabcn/images/ag{../@pos}.png"/>
      		  </xsl:if>                 
             
             </xsl:if>           
         </div>
      
</xsl:template>


<xsl:template  match="aprop/aparcs/list/list_items/row/item|aprop/restaurants/list/list_items/row/item">
      <div>
         <xsl:if test="(1 + count(parent::*/preceding-sibling::*)) mod 2 = 1">
          <xsl:attribute name="class">par</xsl:attribute>
  		 </xsl:if> 
           <h5>
         		<a href="{@href}">
         			<xsl:value-of select="sectionname"
         				disable-output-escaping="yes" />
         			<xsl:if test="sectionname!=''">
         				<xsl:text> - </xsl:text>
         			</xsl:if>
         			<xsl:value-of select="name"
         				disable-output-escaping="yes" />&#160;<xsl:value-of select="sigla"
         				disable-output-escaping="yes" />	
         		</a>
         	</h5>
            <xsl:if test="boolean(internetref) and internetref!=''">
         		<xsl:element name="img">         			
         			<xsl:attribute name="id">listfoto</xsl:attribute>
         			<xsl:attribute name="src"><xsl:value-of select="internetref" />					</xsl:attribute>
         		</xsl:element>
         	</xsl:if>
         	<div class="dades">
         	<xsl:if test="boolean(type) and type!=''">         	
	         	 
	         	<xsl:if test="tp='AG'">
	         	<p class="cat-agenda"> 
	         	<span >         		
	         			<xsl:value-of select="type" />         		
	         	</span>
	         	</p>
	         	</xsl:if> 
	         	<xsl:if test="tp='EQ'">
	         	<p class="cat-equip"> 
	         	<span >         		
	         			<xsl:value-of select="type" />         		
	         	</span>
	         	</p>
	         	</xsl:if>         	
	         	
	        </xsl:if>          	   	
         	
         	<xsl:if test="boolean(address)">
		         <p><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
		          <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
		           </p>
		         <xsl:if test="not(city='Barcelona')"><p><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></p></xsl:if>
		    </xsl:if>       	
		         	 
		         	<xsl:if test="boolean(phonenumber)">
		         	    <p><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></p>          	    
		         	</xsl:if>	
		     </div> 	
      		
      	</div>
</xsl:template>

<xsl:template match="related/list/list_items/row/item">
      <div>
         <xsl:if test="(1 + count(parent::*/preceding-sibling::*)) mod 2 = 1">
          <xsl:attribute name="class">par</xsl:attribute>
  		 </xsl:if> 
           <h4>
         		<a href="{@href}">
         			<xsl:value-of select="sectionname"
         				disable-output-escaping="yes" />
         			<xsl:if test="sectionname!=''">
         				<xsl:text> - </xsl:text>
         			</xsl:if>
         			<xsl:value-of select="name"
         				disable-output-escaping="yes" />&#160;<xsl:value-of select="sigla"
         				disable-output-escaping="yes" />	
         		</a>
         	</h4>
            <xsl:if test="boolean(internetref) and internetref!=''">
         		<xsl:element name="img">         			
         			<xsl:attribute name="id">listfoto</xsl:attribute>
         			<xsl:attribute name="src"><xsl:value-of select="internetref" />					</xsl:attribute>
         		</xsl:element>
         	</xsl:if>
         
         <xsl:if test="tp='EQ'">
      		    	
		         	<xsl:if test="boolean(address)">
		         	    <p><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
		         	    <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
		         	    </p>
		         	    <xsl:if test="not(city='Barcelona')"><p><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></p></xsl:if>
		         	</xsl:if>       	
		         	 
		         	<xsl:if test="boolean(phonenumber)">
		         	    <p><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></p>          	    
		         	</xsl:if>	
		      		  
		      		       <img class="icona-tipus" alt="" src="/tpl/common/img/carpetes-petita.png"/>
	      	</xsl:if>
	      	
	      	<xsl:if test="tp='AG'">
	      	  
	      	     <dl>
         	
		         	<xsl:if test="boolean(begindate)">
		         	    <dt><xsl:value-of select="begindate/@label2"/></dt><dd><xsl:text> </xsl:text><xsl:value-of select="begindate/@label"/><xsl:text> </xsl:text><xsl:value-of select="begindate"/><xsl:text> </xsl:text><xsl:value-of select="enddate/@label"/><xsl:text> </xsl:text><xsl:value-of select="enddate"/></dd>
		         	</xsl:if>
		         	<xsl:if test="boolean(date)">
		         	    <dt><xsl:value-of select="date/@label"/></dt><dd><xsl:text> </xsl:text><xsl:value-of select="date"/></dd>
		         	</xsl:if>  
		         	<xsl:if test="boolean(institutionname)">
		         	    <dt><xsl:value-of select="institutionname/@label"/><xsl:text> </xsl:text></dt>
		         	    <dd><span class="notranslate">
		         	     <xsl:choose>
		                    <xsl:when test="not(boolean(equipment_id))">         	     
		         	         <xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/>
		         	       </xsl:when>
		         	        <xsl:otherwise>
		                     <a href="{equipment_id/@href}"><xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/></a>
		                    </xsl:otherwise>                
		         	    </xsl:choose>
		         	     </span></dd>   
		         	  
		    		 </xsl:if>
		       
		         	
		            <xsl:if test="boolean(address)">
			         	    <dd><span class="notranslate"><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
			         	    <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
			        	    </span></dd>
			         	    <xsl:if test="not(city='Barcelona')"><dd><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></dd></xsl:if>
			        </xsl:if>       	
			         	 
			        <xsl:if test="boolean(phonenumber)">
			        	    <dd><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></dd>          	    
			        </xsl:if>	
			        
			          </dl>
			      	 	 <img class="icona-tipus" alt="" src="/tpl/common/img/agenda-petita.png"/>
			 </xsl:if>                 
            
		          		
      	</div>
</xsl:template>

	<xsl:template match="cartellera">
	<div class="cartellera">	
		<xsl:apply-templates />
	</div>	
	</xsl:template>
	
	<xsl:template match="homebcn">
	<div id="llista-agenda">
		<h2 class="titol tit_agenda"><xsl:value-of select="@label"/></h2>
		<xsl:for-each select="list/list_items/row">
		<h3>
		
			<a
				href="http://guia.bcn.cat/{item/@href}">
				<xsl:value-of select="item/titol" disable-output-escaping="yes" />
			</a>
		</h3>
		<div>
			<img height="50" width="50" alt=""
				src="{item/imatge}" />
			<xsl:value-of select="item/resum" disable-output-escaping="yes" />
		</div>
		</xsl:for-each>		
		<ul>
			<li class="altresopcions">
				<a
					href="http://guia.bcn.cat/?idma={@lang}">
					<xsl:value-of select="@label2"/>
				</a>
			</li>
			<li class="rss">
				<xsl:if test="@lang = 'ca'">
				<a title="Sumari de l'agenda en RSS 2.0"
					href="http://w3.bcn.es/AgendaRecomanadaRSS_ca">
					<span>RSS Agenda</span>
				</a>
				</xsl:if>
				<xsl:if test="@lang = 'es'">
				<a title="Sumario de la agenda en RSS 2.0"
					href="http://w3.bcn.es/AgendaRecomanadaRSS_es">
					<span>RSS Agenda</span>
				</a>
				</xsl:if>
				<xsl:if test="@lang = 'en'">
				<a title="What's on The Diary, in RSS 2.0"
					href="http://w3.bcn.es/AgendaRecomanadaRSS_en">
					<span>RSS Diary</span>
				</a>
				</xsl:if>
				
				
				
			</li>
		</ul>
	</div>
</xsl:template>




</xsl:stylesheet>
