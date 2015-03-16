<div id="page" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <!-- ______________________ HEADER _______________________ -->

  <header id="header">
     <div id="zone-header-wrapper" class="zone-wrapper">
        <div id="region-header" class="grid">

           <h1 id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">Equipaments <?php if ($site_slogan): ?>
              <span class="site-slogan"><?php print $site_slogan; ?></span>
            <?php endif; ?>
           </a></h1>
        
            
    
            <?php if ($page['header']): ?>
                  <?php print render($page['header']); ?>
            <?php endif; ?>

		</div>	
     </div>
  </header> 
  
<!-- /header -->

<!-- ______________________ Menu Region ___________________ -->

 <?php if ($page['menu']): ?>
 <div id="zone-menu-wrapper">
     <div id="region-menu" class="grid">
       <nav id="navigation">
         <?php print render($page['menu']); ?>
       </nav>
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /menu -->



<!-- ______________________ Zone Promotional ___________________ -->

 <?php if ($page['promotional']): ?>
 <div id="zone-promotional-wrapper" class="zone-wrapper">
     <div id="region-promotional" class="grid">
         <?php print render($page['promotional']); ?>
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /promotional -->


<!-- ________________________ Zone Row 1 _______________________ -->

 <?php if ($page['r1_b1'] || $page['r1_b2']  || $page['r1_full'] ): ?>
 <div id="zone-row-1-wrapper" class="zone-wrapper">
     <div id="zone-row-1-content" class="grid">
		 <?php if ($page['r1_b1']): ?>
            <div id="region-r1-b1" class="b1 grid-50">
             <?php print render($page['r1_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r1_b2']): ?>
            <div id="region-r1-b2" class="b2 grid-50">
             <?php print render($page['r1_b2']); ?>
            </div>
         <?php endif; ?>
         
          <?php if ($page['r1_full']): ?>
            <div id="region-r1-full" class="grid-full">
             <?php print render($page['r1_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 1 -->


<!-- ________________________ Zone Row 2 _______________________ -->

 <?php if ($page['r2_b1'] || $page['r2_b2']  || $page['r2_full'] ): ?>
 <div id="zone-row-2-wrapper" class="zone-wrapper">
     <div id="zone-row-2-content" class="grid">
		 
		 <?php if ($page['r2_b1']): ?>
            <div id="region-r2-b1" class="b1 grid-50">
             <?php print render($page['r2_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r2_b2']): ?>
            <div id="region-r2-b2" class="b2 grid-50">
             <?php print render($page['r2_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r2_full']): ?>
            <div id="region-r2-full" class="grid-full">
             <?php print render($page['r2_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 2 -->
 
 
<!-- ________________________ Zone Main Content _______________________ -->
 
 <?php if ($page['content']): ?>


 <div id="zone-row-content-wrapper" class="zone-wrapper">
    <div id="zone-content" class="grid">
 
        <?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>

            <?php print $breadcrumb; ?>

            <?php if ($title): ?>
              <h2 class="title"><?php print $title; ?></h2>
            <?php endif; ?>

            <?php print render($title_suffix); ?>
            <?php print $messages; ?>
            <?php print render($page['help']); ?>

            <?php if ($tabs): ?>
              <div class="tabs"><?php print render($tabs); ?></div>
            <?php endif; ?>

            <?php if ($action_links): ?>
              <ul class="action-links"><?php print render($action_links); ?></ul>
            <?php endif; ?>

        <?php endif; ?>
		<div id="main">
			<?php print render($page['content']) ?>
        </div>

  </div>
</div> 
  
<?php endif; ?>
 
<!-- /Zone Main Content -->
 
 
<!-- ________________________ Zone Row 3 _______________________ -->

 <?php if ($page['r3_b1'] || $page['r3_b2']  || $page['r3_full'] ): ?>
 <div id="zone-row-3-wrapper" class="zone-wrapper">
     <div id="zone-row-3-content" class="grid">
		 
		 <?php if ($page['r3_b1']): ?>
            <div id="region-r3-b1" class="b1 grid-50">
             <?php print render($page['r3_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r3_b2']): ?>
            <div id="region-r3-b2" class="b2 grid-50">
             <?php print render($page['r3_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r3_full']): ?>
            <div id="region-r3-full" class="grid-full">
             <?php print render($page['r3_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 3 -->

<!-- ________________________ Zone Row 4 _______________________ -->

 <?php if ($page['r4_b1'] || $page['r4_b2']  || $page['r4_full'] ): ?>
 <div id="zone-row-4-wrapper" class="zone-wrapper">
     <div id="zone-row-4-content" class="grid">
		 
		 <?php if ($page['r4_b1']): ?>
            <div id="region-r4-b1" class="b1 grid-50">
             <?php print render($page['r4_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r4_b2']): ?>
            <div id="region-r4-b2" class="b2 grid-50">
             <?php print render($page['r4_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r4_full']): ?>
            <div id="region-r4-full" class="grid-full">
             <?php print render($page['r4_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 4 -->

<!-- ________________________ Zone Row 5 _______________________ -->

 <?php if ($page['r5_b1'] || $page['r5_b2']  || $page['r5_full'] ): ?>
 <div id="zone-row-5-wrapper" class="zone-wrapper">
     <div id="zone-row-5-content" class="grid">
		 
		 <?php if ($page['r5_b1']): ?>
            <div id="region-r5-b1" class="b1 grid-50">
             <?php print render($page['r5_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r5_b2']): ?>
            <div id="region-r5-b2" class="b2 grid-50">
             <?php print render($page['r5_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r5_full']): ?>
            <div id="region-r5-full" class="grid-full">
             <?php print render($page['r5_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 5 -->

<!-- ________________________ Zone Row 6 _______________________ -->

 <?php if ($page['r6_b1'] || $page['r6_b2']  || $page['r6_full'] ): ?>
 <div id="zone-row-6-wrapper" class="zone-wrapper">
     <div id="zone-row-6-content" class="grid">
		 
		 <?php if ($page['r6_b1']): ?>
            <div id="region-r6-b1" class="b1 grid-50">
             <?php print render($page['r6_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r6_b2']): ?>
            <div id="region-r6-b2" class="b2 grid-50">
             <?php print render($page['r6_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r6_full']): ?>
            <div id="region-r6-full" class="grid-full">
             <?php print render($page['r6_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 6 -->
 
 
<!-- ________________________ Zone Row 7 _______________________ -->

 <?php if ($page['r7_b1'] || $page['r7_b2']  || $page['r7_full'] ): ?>
 <div id="zone-row-7-wrapper" class="zone-wrapper">
     <div id="zone-row-7-content" class="grid">
		 
		 <?php if ($page['r7_b1']): ?>
            <div id="region-r7-b1" class="b1 grid-50">
             <?php print render($page['r7_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r7_b2']): ?>
            <div id="region-r7-b2" class="b2 grid-50">
             <?php print render($page['r7_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r7_full']): ?>
            <div id="region-r7-full" class="grid-full">
             <?php print render($page['r7_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 7 --> 

<!-- ________________________ Zone Row 8 _______________________ -->

 <?php if ($page['r8_b1'] || $page['r8_b2']  || $page['r8_full'] ): ?>
 <div id="zone-row-8-wrapper" class="zone-wrapper">
     <div id="zone-row-8-content" class="grid">
		 
		 <?php if ($page['r8_b1']): ?>
            <div id="region-r8-b1" class="b1 grid-50">
             <?php print render($page['r8_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r8_b2']): ?>
            <div id="region-r8-b2" class="b2 grid-50">
             <?php print render($page['r8_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r8_full']): ?>
            <div id="region-r8-full" class="grid-full">
             <?php print render($page['r8_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 8 --> 

<!-- ________________________ Zone Row 9 _______________________ -->

 <?php if ($page['r9_b1'] || $page['r9_b2']  || $page['r9_full'] ): ?>
 <div id="zone-row-9-wrapper" class="zone-wrapper">
     <div id="zone-row-9-content" class="grid">
		 
		 <?php if ($page['r9_b1']): ?>
            <div id="region-r9-b1" class="b1 grid-50">
             <?php print render($page['r9_b1']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r9_b2']): ?>
            <div id="region-r9-b2" class="b2 grid-50">
             <?php print render($page['r9_b2']); ?>
            </div>
         <?php endif; ?>
         
         <?php if ($page['r9_full']): ?>
            <div id="region-r9-full" class="grid-full">
             <?php print render($page['r9_full']); ?>
            </div>
         <?php endif; ?>
         
     </div> 
 </div>
 <?php endif; ?>
 
<!-- /Zone Row 9 --> 
 
<!-- ______________________ FOOTER _______________________ -->

  <?php if ($page['footer']): ?>
    <footer id="footer">
      <div id="zone-footer-wrapper" class="zone-wrapper">
        <div id="region-footer" class="grid">
		  <?php print render($page['footer']); ?>
        </div>
      </div>
    </footer> 
  <?php endif; ?>
  
  <!-- /footer -->

</div> <!-- /page -->
