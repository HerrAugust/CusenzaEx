<?php
	$link = mysql_connect('localhost', 'root', 'MySQL', '80');
	if (!$link) {
		die('Could not connect: ' . mysql_error());
	}
	echo 'Connected successfully';
?> 