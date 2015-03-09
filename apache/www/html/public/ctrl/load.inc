<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

//* Loads configuration file, db user/pass
if (file_exists(_TPLDIR."/config.inc"))
include(_TPLDIR."/config.inc");
else
header ("Location: error.html");
?>