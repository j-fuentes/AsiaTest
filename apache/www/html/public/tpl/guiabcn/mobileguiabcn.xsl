<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:output method="xml"
		doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
		doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
		indent="yes" />

	<!-- Aqui ponemos el contenido del template -->
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

	<!-- TEMPLATE head -->
	<xsl:template match="head">
		<head>
		    <link type="text/css" rel="stylesheet" charset="utf-8" href="http://www.bcn.cat/assets/common/1.0.0/stylesheets/common.css" />
			<link type="text/css" rel="StyleSheet" href="{//html/page/@path}/tpl/guiabcn/style/stylemobile.css" />
			<meta name="HandheldFriendly" content="True" />
			<meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;" />
				
			<xsl:apply-templates />
			<!--  <link rel="shortcut icon" href="{//html/page/@path}/tpl/propiweb/images/logo.ico" /> -->
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
	<xsl:template match="data|noresultscomments|logo|home|leftfilter|brand|text|fbutton|htmlform|resum|footer">
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
		<xsl:apply-templates select="brand" />
		<xsl:if	test="not(boolean(../central/detall))">	
		<xsl:apply-templates select="capsalera" />	
		</xsl:if>	
	</xsl:template>

	<!-- TEMPLATE BODY -->
	<xsl:template match="page">
		<body>
			<xsl:if test="boolean(@onload)">
				<xsl:attribute name="onload">
      <xsl:value-of select="@onload" />
      </xsl:attribute>
			</xsl:if>
			<div class="pagina">
				<xsl:apply-templates select="headers" />
				<xsl:apply-templates select="central" />				
			</div>
			<xsl:apply-templates select="footers" />
		</body>
	</xsl:template>
	
		<!-- TEMPLATE CENTRAL -->
	<xsl:template match="central">		
			<xsl:apply-templates select="search" />
			<xsl:apply-templates select="detall" />
			<xsl:apply-templates select="content" />
			<xsl:if	test="not(boolean(search)) and not(boolean(detall)) and not(boolean(content))">
				<div id="contenidor-home">
					<xsl:apply-templates select="classall" />
					<xsl:apply-templates select="hrecom" />
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

	<xsl:template match="found">
		<h2>
			<xsl:value-of select="@vis" />
			<xsl:text> </xsl:text>
			<span>
				<xsl:value-of select="@from" />
			</span>
			<xsl:text> </xsl:text>
			<xsl:value-of select="@al" />
			<xsl:text> </xsl:text>
			<span>
				<xsl:value-of select="@to" />
			</span>
			<xsl:text> </xsl:text>
			<xsl:value-of select="@de" />
			<xsl:text> </xsl:text>
			<span>
				<xsl:value-of select="@total" />
			</span>
			<xsl:if test="not(../../../writtenquery = '')">
				<xsl:text> </xsl:text>
				<xsl:value-of select="@results" /><xsl:text> </xsl:text>
				<span>“<xsl:value-of select="../../../writtenquery" />”</span>
			</xsl:if>			
		</h2>
	</xsl:template>
	
	<!-- TEMPLATE NORESULTS -->
	<xsl:template match="noresults">
		<h1 class="notfound">
			<xsl:value-of select="query" />
		</h1>
		<xsl:for-each select="item">
			<p class="criteris">
				<xsl:value-of select="." />
			</p>
		</xsl:for-each>
	</xsl:template>
	
		<!-- TEMPLATE SUGGETIONS -->
	<xsl:template match="suggestions">
			<h2>
			<xsl:value-of select="@name" /><xsl:text> </xsl:text>
			<span>“<a href="{@href}"><xsl:value-of select="." /></a>”</span>.
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

	<!-- TEMPLATE CAPSALERA -->

	<xsl:template match="capsalera">
	
	
	<script>
	function checkloctation(){
if (document.getElementById('pt').value!='') {
	document.getElementById('btubicacio').style.display ='none';
	document.getElementById('ubicacio').innerHTML ='Cercant prop de la meva ubicació';
}
}
function getLocation()  {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(showPosition);
    }
  
  }
function showPosition(position)  {
  document.getElementById('pt').value = position.coords.latitude + "," + position.coords.longitude; 
  document.getElementById('btubicacio').style.display ='none';
  document.getElementById('ubicacio').innerHTML ='Cercant prop de la meva ubicació';  
  }
  window.onload = checkloctation;
</script>
	<div id="formulari">
	    <h1>
	         <xsl:value-of select="@alt" />				
		</h1>
		<form id="frm-cerca" enctype="multipart/form-data"	action="index.php" method="get">
					<ul>
						<li id="pg-cercar" style="opacity: 1;">
							<input type="hidden" name="pg" value="search" />
						</li>
						<li id="q-cercar" style="opacity: 1;">
						<xsl:if test="boolean(//html/page/central/search)">
							<input id="q" type="text" name="q" value="{//html/page/central/search/writtenquery}"  />
						</xsl:if>	
						<xsl:if test="not(boolean(//html/page/central/search))">
							<input class="default-value" id="q" type="text" name="q" value="" />
						</xsl:if>
						<input id="pt" type="hidden" name="pt" value="{//html/page/central/search/pt}" />	
						<input class="cerca" type="submit" 	value="{@label}" /> 
						</li>
						<!-- 
						<li id="input-cercar" style="opacity: 1;">
							<input class="cerca" type="submit" 	value="{@label}" />
						</li>-->						
					</ul>
		</form>	
		<button id="btubicacio" class="cerca" onclick="getLocation()">Detectar la meva ubicació</button><h2 id="ubicacio"></h2>
			
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


	<!-- TEMPLATE FOOTERS -->

	<xsl:template match="footers">
		<div id="info-ajbarna">
			<p id="copy">
				<a
					href="http://www.bcn.cat/catala/copyright/welcome2.htm">
					&#169; Ajuntament de Barcelona
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


	<!-- TEMPLATE queryresponse -->

	<xsl:template match="queryresponse">
	       <xsl:apply-templates select="list" />
	</xsl:template>
	
	<xsl:template match="queryresponse/list">	    
		<div id="resultats">
			<div id="accions">
			 <p>		
			  <xsl:apply-templates select="lst_info/sort" />
			  <!-- <xsl:apply-templates select="lst_info/numrows" />-->
			 </p>
			 <ul >	      
              <li><a class="addthis_button_email at300b" href="#"></a></li>
            </ul>
            </div> 		
            <!-- <xsl:apply-templates select="../../../gmap" mode="cerca" />-->  
       	          
			<xsl:apply-templates select="list_items" />	
			
			<xsl:apply-templates select="../share" />			
		</div>		
	</xsl:template>
	
		<!-- LIST ITEMS -->
<xsl:template match="list_items">
          <!-- Resultats de la cerca -->
          <div id="llista-resultats"> 
               <xsl:apply-templates select="../../../filters" />          
               <xsl:apply-templates select="row" />
               <xsl:apply-templates select="../lst_info" />
          </div>  
</xsl:template>

	<xsl:template match="facetlist">
		<xsl:for-each select="*">
			<div class="blocd">			
		    <h2 class="trigger"><a  href="javascript:void(0);"> <xsl:value-of select="@name" /></a></h2>
			<div class="toggle_container">												
						<ul>					
							<xsl:for-each select="item">
								<xsl:choose>
									<xsl:when test="boolean(@href)">																											
										<li>	<a href="{@href}">
												<xsl:value-of
													select="@name" />
												(
												<xsl:value-of
													select="." />
												)
											</a>
										</li>
									</xsl:when>
									<xsl:otherwise>								
									<!--  <xsl:if test="position()=2"><img src="/tpl/guiabcn/images/ftv2lastnode.gif" /></xsl:if>	
									<xsl:if test="position()=3"><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2lastnode.gif" /></xsl:if>	
									<xsl:if test="position()=4"><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2lastnode.gif" /></xsl:if>
									<xsl:if test="position()=5"><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2blank.gif" /><img src="/tpl/guiabcn/images/ftv2lastnode.gif" /></xsl:if>-->																
									<li><xsl:value-of select="@name" /></li>														
								    </xsl:otherwise>
				                  </xsl:choose>
							</xsl:for-each>
						</ul>	
				</div>						
		    </div>
		</xsl:for-each>

	</xsl:template>



	
	<xsl:template match="lst_info">
	       <div class="paginador">
	       <!--  
	       	<xsl:value-of select="label" />&#160;
							<xsl:value-of select="current" />
							&#160;
							<xsl:value-of select="total" />
	       -->
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
	</xsl:template>
	
	<xsl:template match="cols/*">
		<td class="col">
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	
	<xsl:template match="sort">				
		<xsl:value-of select="@label" />
				<xsl:for-each select="*">
					<xsl:choose>
							<xsl:when
								test="not(name()=parent::sort/@selected)">
								<a class="sort" href="{@href}">
									<xsl:value-of select="." />
								</a>
							</xsl:when>
							<xsl:otherwise>
								<span class="selected"><xsl:value-of select="." /></span>
							</xsl:otherwise>
						</xsl:choose>
		</xsl:for-each>			
	</xsl:template>
	

<xsl:template match="row">
   <xsl:apply-templates select="item" />
</xsl:template>

	<!-- TEMPLATE ITEM-->

<xsl:template  match="row/item">
         <div class="impar">
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
         			<xsl:attribute name="src"><xsl:value-of
         					select="internetref" />					</xsl:attribute>
         		</xsl:element>
         	</xsl:if>
         	<!--  
         	<p class="categoria"><span >         		
         			<xsl:value-of select="type" />         		
         	</span></p>-->
         	<xsl:if test="boolean(begindate)">
         	    <p><span class="bold"><xsl:value-of select="begindate/@label2"/></span><xsl:text> </xsl:text><xsl:value-of select="begindate/@label"/><xsl:text> </xsl:text><xsl:value-of select="begindate"/><xsl:text> </xsl:text><xsl:value-of select="enddate/@label"/><xsl:text> </xsl:text><xsl:value-of select="enddate"/></p>
         	</xsl:if>
         	<xsl:if test="boolean(date)">
         	    <p><span class="bold"><xsl:value-of select="date/@label"/></span><xsl:text> </xsl:text><xsl:value-of select="date"/></p>
         	</xsl:if>  
         	<xsl:if test="boolean(institutionname)">
         	    <p class="on"><span class="bold"><xsl:value-of select="institutionname/@label"/><xsl:text> </xsl:text></span>
         	    <span class="notranslate">
         	     <xsl:choose>
                    <xsl:when test="not(boolean(equipment_id))">         	     
         	         <xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/>
         	       </xsl:when>
         	        <xsl:otherwise>
                     <a href="{equipment_id/@href}"><xsl:value-of select="institutionname" disable-output-escaping="yes"/><xsl:text> </xsl:text><xsl:value-of select="sigla" disable-output-escaping="yes"/></a>
                    </xsl:otherwise>                
         	    </xsl:choose>
         	     </span>   
         	    </p>
         	</xsl:if>
         	<xsl:if test="boolean(address)">
         	    <p><span class="notranslate"><xsl:value-of select="address" disable-output-escaping="yes"/><xsl:text> </xsl:text>
         	    <xsl:if test="boolean(district)">(<xsl:value-of select="district" disable-output-escaping="yes"/>)</xsl:if>
         	    </span></p>
         	    <xsl:if test="not(city='Barcelona')"><p><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></p></xsl:if>
         	</xsl:if>       	
         	 
         	<xsl:if test="boolean(phonenumber)">
         	    <p><!-- <xsl:value-of select="phonenumber/@label"/>--><xsl:value-of select="phonenumber" disable-output-escaping="yes"/></p>          	    
         	</xsl:if>	
         	<!--  
     		  <xsl:if test="tp='EQ'">
     		       <img class="icona-tipus" alt="" src="/tpl/common/img/carpetes-petita.png"/>
     		  </xsl:if>
     		    <xsl:if test="tp='AG'">
     		       <img class="icona-tipus" alt="" src="/tpl/common/img/agenda-petita.png"/>
     		  </xsl:if>                 
             -->   	
      		    
         </div>
      
</xsl:template>

	<xsl:template match="filters">	
		<xsl:if test="boolean(item)"> 
		<div class="filtres">
		<h3><span><xsl:value-of select="@label" /></span></h3>
		   <ul>
		      <xsl:for-each select="item">
		          <li><xsl:value-of select="." /><a href="{@href}"><img src="/tpl/common/img/x-filter.gif"/></a></li>			
		   		</xsl:for-each>
		   </ul>
        </div>
   		</xsl:if>   
	</xsl:template>


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
				
		        <h1>
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
				</h1>
				<xsl:if test="//html/page/@lang = 'es' or //html/page/@lang = 'en'">
				<div class="goog-trans-control"></div>
				</xsl:if>			
				<xsl:if test="entity_type = 'AG'">
				<xsl:apply-templates select="likeit" />
				</xsl:if>
				<xsl:if test="boolean(resum)">	
                 <div id="resum" class="notranslate">
				 <xsl:value-of select="resum" disable-output-escaping="yes" />
				 </div>
				 </xsl:if>	
				<xsl:if test="boolean(begindate)">
         	    <p class="data"><span class="bold"><xsl:value-of select="begindate/@label2"/></span>&#160;<xsl:value-of select="begindate/@label"/>&#160;<xsl:value-of select="begindate"/>&#160;<xsl:value-of select="enddate/@label"/>&#160;<xsl:value-of select="enddate"/>
         	    <xsl:apply-templates select="status" />	
         	    </p>
         	    </xsl:if>
         	    <xsl:if test="boolean(date)">
         	    <p class="data"><span class="bold"><xsl:value-of select="date/@label"/><xsl:text> </xsl:text></span>&#160;<xsl:value-of select="date"/>
         	    <xsl:apply-templates select="status" />	
         	    </p>
         	    </xsl:if>			
				<xsl:if test="boolean(institutionname)">
					<p class="on">
						<span class="bold"><xsl:value-of select="institutionname/@label" /></span>
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
					</p>
				</xsl:if>
         	    <!-- <xsl:if test="entity_type = 'EQ'">	-->
         	    <xsl:if test="boolean(street)">
         	    	<p class="adreca">
         	    		<span class="bold"><xsl:value-of select="street/@label" />:<xsl:text> </xsl:text></span>
         	    		<span class="notranslate">
         	    			<xsl:value-of select="street" />
         	    			,<xsl:text> </xsl:text>
         	    			<xsl:value-of select="streetnum_i" />
         	    		</span>
         	    		<xsl:text> </xsl:text>
         	    		(<a href="{link/@href}">Google Maps</a>)
         	    	</p>
         	    </xsl:if>
         	    <xsl:apply-templates select="district|barri|postalcode"/>	
                    <xsl:if test="not(city='Barcelona')"><p><span class="bold"><xsl:value-of select="city/@label" />:&#160;</span><span class="notranslate"><xsl:value-of select="city" disable-output-escaping="yes"/></span></p></xsl:if>
					<xsl:for-each select="phones/item">
						<p>
						<xsl:if test="position() = 1"><xsl:attribute name="class">phones</xsl:attribute></xsl:if>
						<span class="bold"><xsl:value-of select="label" />:&#160;</span><xsl:value-of select="phonenumber" />&#xa0;<xsl:value-of select="phonedesc" />
						</p>		
					</xsl:for-each>
				<xsl:if test="entity_type = 'EQ'">	
					<xsl:for-each select="interestinfo/item">
					<p>
					<xsl:if test="position() = 1"><xsl:attribute name="class">interestinfo</xsl:attribute></xsl:if>
						<span class="bold"><xsl:value-of select="label" />:&#160;</span>
						<xsl:if	test="intercode='00100002' or intercode='00030002'">
							<a href="mailto:{interinfo}"><xsl:value-of select="interinfo" /></a>					
						</xsl:if>
						<xsl:if
							test="intercode='00100003' or intercode='00030003' or intercode='00100004'">
							<a href="http://{interinfo}"><xsl:value-of select="interinfo" /></a>				
						</xsl:if>
					</p>	
					</xsl:for-each>
				</xsl:if>
				</div>				
				
				<xsl:if test="boolean(timetable) or boolean(classification) or boolean(../ageq)">
				<div id="contenidor-pestanes">
				   	<div id="div-informacio"  class="tabdetall">					
						<xsl:apply-templates select="timetable" />						
						<xsl:apply-templates select="relations" />

		            </div>	    				
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
				 <xsl:if test="boolean(warning)">	
				 <p class="warning"><xsl:value-of select="warning" disable-output-escaping="yes" /></p>
				</xsl:if>
				
			
			</div>			
			<div id="col-detall-1">		
			<xsl:if test="boolean(gmapx)">
				<!-- google maps -->
				<script type="text/javascript" src="/tpl/guiabcn/jscripts/gmap.js"></script>
				<script src="http://maps.google.com/maps?file=api&amp;v=2&amp;key={apikey}" type="text/javascript"></script>
							
<script>
if (window.addEventListener){
window.addEventListener('load',function() {loadmapdetall(<xsl:value-of select="gmapx" />,<xsl:value-of select="gmapy" />,'');}, false);
 } else {
window.attachEvent('onload',function(){loadmapdetall(<xsl:value-of select="gmapx" />,<xsl:value-of select="gmapy" />,'')}); 
}
</script>	
			    <div id="detallmap" style="width: 300px; height: 300px"></div>					    
			  
			    </xsl:if>	   
			  
			  						<xsl:if test="boolean(classification)">
						<div>
						<p><span class="bold"><xsl:value-of select="classification/@label"/></span></p>				
						<xsl:apply-templates select="classification" />
						</div>
						</xsl:if>
			</div>
		</div>
		</div>
	</xsl:template>
	
	<xsl:template match="district|barri|postalcode">
	<p><span class="bold"><xsl:value-of select="@label" />:<xsl:text> </xsl:text></span><span class="notranslate"><xsl:value-of select="." /></span></p>
	</xsl:template>
	
	<!-- Classificacion -->
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
	
	<!-- TEMPLATE TIMETABLE -->
	<xsl:template match="timetable">
	    <xsl:if test="boolean(horari)">
			<div id="horari">
			<p><span class="bold"><xsl:value-of select="horari/@label" /></span></p>			
				<xsl:for-each select="horari">
				    <p><xsl:value-of select="periode"	disable-output-escaping="yes" /><xsl:text> </xsl:text><xsl:value-of select="dies"	disable-output-escaping="yes" /><xsl:text> </xsl:text><xsl:value-of select="hores" disable-output-escaping="yes" /></p>
				</xsl:for-each>
			<xsl:if test="boolean(observacions)"><p><xsl:value-of select="observacions" disable-output-escaping="yes" /></p></xsl:if>
			
			</div>
		</xsl:if>
		 <xsl:if test="boolean(preu)">
			<div id="preu">			
			<p><span class="bold"><xsl:value-of select="preu/@label" /></span></p>
				<xsl:for-each select="preu">				
				    <p><xsl:value-of select="."	disable-output-escaping="yes" /></p>
				</xsl:for-each>
			</div>
		</xsl:if>
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
				</p>
		</xsl:for-each>
	</div>	
	</xsl:if>
	</xsl:template>

	<!-- TEMPLATE RECOMANATS -->
	<xsl:template match="hrecom">
		<div id="activitats-destacades">
		<div id="contenidor-home-2">
	        <h2><xsl:value-of select="@label"/></h2>	
	        <!-- <xsl:apply-templates select="../gmap" mode="destacats"/> -->
	        <xsl:apply-templates select="list/lst_info" />
	        <div id="col-act-dest">		          	
				 <xsl:apply-templates select="list/list_items/row"/>			   
   		     </div>		 
			 <xsl:apply-templates select="list/lst_info" />
		</div>
		</div>
	</xsl:template>
	
	<xsl:template match="hrecom/list/list_items/row">
		
		<div class="contenidor">
		   <div>
			<xsl:if test="boolean(item/urlvideo)">
				<iframe title="YouTube video player" width="490"
					height="300" src="{item/urlvideo}" frameborder="0"
					allowfullscreen="1">
				</iframe>
			</xsl:if>	
			<xsl:if test="not(boolean(item/urlvideo))">
				<img src="{item/imatgeCos}" />
			</xsl:if>	
			 <h3><a href="{item/@href}">
					<xsl:value-of select="item/titol" disable-output-escaping="yes" />
			 </a></h3>		
			 			
		  </div>
		  <div class="data">		  
		  <xsl:if test="boolean(item/institutionname)">
         	    <p class="on"><span class="bold"><xsl:value-of select="item/institutionname/@label"/><xsl:text> </xsl:text></span>
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
         	    </p>
         	</xsl:if>
         
         	<xsl:if test="boolean(item/begindate)">
         	    <p class="data"><span class="bold"><xsl:value-of select="item/begindate/@label2"/></span><xsl:text> </xsl:text><xsl:value-of select="item/begindate/@label"/><xsl:text> </xsl:text><xsl:value-of select="item/begindate"/><xsl:text> </xsl:text><xsl:value-of select="item/enddate/@label"/><xsl:text> </xsl:text><xsl:value-of select="item/enddate"/></p>
         	</xsl:if>
         	<xsl:if test="boolean(item/date)">
         	    <p class="data"><span class="bold"><xsl:value-of select="item/date/@label"/></span><xsl:text> </xsl:text><xsl:value-of select="item/date"/></p>
         	</xsl:if> 
         	<!--  
         	<xsl:if test="boolean(item/equipment_id/@href)">  
		 	 <img class="icona" alt="" src="/tpl/guiabcn/images/ag{item/pos}.png"/>
		 	</xsl:if>-->
		  </div>
		  <div>
		<xsl:value-of select="item/resum" disable-output-escaping="yes"/>
		</div>
		</div> 
		 
		
	</xsl:template>

	
	
    <!-- END TEMPLATE RECOMANATS -->
<xsl:template match="status">
	<span class="status"><xsl:value-of select="."/></span>
</xsl:template>	
</xsl:stylesheet>
