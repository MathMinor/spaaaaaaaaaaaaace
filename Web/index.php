<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
<script>

function light_run () {
      $.ajax({
        url:"light_data.php", //the page containing php script
        type: "POST", //request type
        success:function(result){
         result;
         $('#light').html(result);
       }
     });
 }

function camera_run () {
      $.ajax({
        url:"camera_data.php", //the page containing php script
        type: "POST", //request type
        success:function(result){
	result;
	$('#camera').html(result);
       }
     });
 }

function tempHum_run () {
      $.ajax({
        url:"tempHum_data.php", //the page containing php script
        type: "POST", //request type
        success:function(result){
         result;
	$('#temphum').html(result);
       }
     });
 }

function accel_run () {
      $.ajax({
        url:"accel_data.php", //the page containing php script
        type: "POST", //request type
        success:function(result){
         result;
	$('#accel').html(result);
       }
     });
 }


</script>

<style> <?php include 'spaaace.css'; ?> </style>

<center>
<font size="10">***********</font><font size="12">SP</font><font size="14">AAA</font><font size="12">CE</font><font size="10">************</font>
<br>
<button type="button" class="column-left" onclick="light_run()">Get Light</button>
<button type="button" class="column-center" onclick="tempHum_run()">Get Temperature/Humidity</button>
<button type="button" class="column-right" onclick="accel_run()">Get Accelerometer</button>
<br>

<span id="light" class="column-left"> Light </span>
<span id="temphum" class="column-center"> Temp/Hum </span>
<span id="accel" class="column-right"> Accel </span>
<br>
<br>
<br> <button type="button" onclick="camera_run()">Get Picture</button>
<br> <div id="camera"> 
<iframe src="index_image.html" width="75%" name="iframe_image"> </iframe>
 </div>
</center>
