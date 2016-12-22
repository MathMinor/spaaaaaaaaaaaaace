<?php
$output = shell_exec('sudo python /home/pi/light.py');
echo "$output" . " lux";
?>


