<?php
shell_exec('sudo python /home/pi/camera.py');
$dir          = '/home/pi/CSPictures';
$file_display = array(
    'jpg',
    'jpeg',
    'png',
    'gif'
);

if (file_exists($dir) == false) {
    echo 'Directory \''. $dir. '\' not found!';
} else {
    $dir_contents = scandir($dir);

    foreach ($dir_contents as $file) {
        $file_type = strtolower(end(explode('.', $file)));

        if ($file !== '.' && $file !== '..' && in_array($file_type, $file_display) == true) {
            echo '<img src="file://'. $dir. '/'. $file. '" alt="'. $file. '" />';
        }
    }
}
?>
