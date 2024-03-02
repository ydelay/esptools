#ifndef ESPCONFIGPAGEHTML_H
#define ESPCONFIGPAGEHTML_H
#include <Arduino.h>
#include <string>



// TAG de la page è remplacer
// <!--%DEVICENAME%-->

const char header_html[] PROGMEM = R"=====(
<!DOCTYPE html>
    <html lang="fr">
    
    <head>
        <!-- <meta http-equiv="refresh" content="60" charset="UTF-8"> -->
        <META HTTP-EQUIV="Pragma" CONTENT="no-cache">
        <META HTTP-EQUIV="Expires" CONTENT="-1">
        <meta name="viewport" content="width=device-width, initial-scale=1.0" charset="utf-8">
<!--        <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"> -->
        <link rel="stylesheet" href="/w3.css"> 
        <title>Device <!--%DEVICENAME%--></title>
    </head>
    
    <body onload="_onloadBody()">
        <!-- Fenêtre popup -->
    <div id="popup" class="w3-modal">
        <div class="w3-modal-content w3-card-4">
            <header class="w3-container w3-blue"> 
                <span onclick="document.getElementById('popup').style.display='none'" 
                class="w3-button w3-display-topright">&times;</span>
                <h2>Confirmation</h2>
            </header>
            <div class="w3-container">
                <p>Le formulaire a été soumis avec succès.</p>
                <p><button class="w3-button w3-block w3-blue w3-section w3-padding w3-round w3-hover-light-blue" onclick="document.getElementById('popup').style.display='none'">OK</button></p>
            </div>
        </div>
    </div>
    
        <div class="w3-container w3-blue">
            <h1 class="w3-center "><!--%DEVICENAME%--></h1>
        </div>
        <div>
            <p></p>
    
        </div>
        <div class="w3-row w3-center">
            <a href="/device" class="w3-button w3-third tablink <!--%DEVICECOLOR%--> w3-hover-blue w3-padding"><b>Device</b></a>
            <a href="/mqtt" class="w3-button w3-third tablink <!--%MQTTCOLOR%--> w3-hover-blue w3-padding"><b>MQTT</b></a>
            <a href="/wifi" class="w3-button w3-third tablink <!--%WIFICOLOR%--> w3-hover-blue w3-padding"><b>WiFi</b></a>
        </div>
        <p></p>
)=====";

const char footer_html[] PROGMEM = R"=====(
</body>

</html>

)=====";


// TAG de la page è remplacer
// <!--%COLORINFO%-->   : w3-blue si actif w3-light-blue si inactif
// <!--%COLORDETAIL%--> : w3-blue si actif w3-light-blue si inactif
// <!--%COLORCONFIG%--> : w3-blue si actif w3-light-blue si inactif

const char header_device_html[] PROGMEM = R"=====(

       <!-- Début zone header_device -->
        <div id="WiFI" class=" topic" style="display:block">
            <div class="w3-col">
                <a href="/device/info" class=" w3-button <!--%COLORINFO%--> w3-third w3-hover-blue"><b>Info</b></a>
                <a href="/device/detail" class="w3-button <!--%COLORDETAIL%--> w3-third w3-hover-blue"><b>Detail</b></a>
                <a href="/device/config" class="w3-button <!--%COLORCONFIG%--> w3-third w3-hover-blue"><b>Config</b></a>
            </div>
        </div>
        <p></p>
)=====";


// TAG de la page è remplacer
// 
// <!--%DEVICENAME%-->        : Config.getDeviceName()
// <!--%DEVICEID%-->          : ESP.getChipId()
// <!--%DEVICELOCATION-->     : Config.getDeviceLocation()
// <!--%DEVICEDESCRIPTION%--> : Config.getDeviceDescription()
// <!--%DEVICEVCC%-->         : ESP.getVcc()
// <!--%DEVICELASTRESET%-->   : ESP.getResetReason()
// <!--%WEBUSER%-->           : Config.getWebUser()
// <!--%WEBPASSWORD%-->       : Config.getWebPassword()
// <!--%WEBPORT%-->           : Config.getWebPort()
// <!--%WEBSTATUS%-->         : Webserver.status()
// <!--%COREVERSION%-->       : ESP.getCoreVersion()
// <!--%SDKVERSION%-->        : ESP.getSdkVersion()    
// <!--%FLASHSTATUS%-->       : ESP.checkFlashCRC()
// <!--%OTAACTIVATED%-->      : Config.getOtaActivated()
// <!--%OTAPASSWORD%-->       : Config.getOtaPassword()
// <!--%OTAPORT%-->           : Config.getOtaPort()

const char device_info_html[] PROGMEM = R"=====(
            <!-- Début zone device_info -->


            <p></p>

            <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                    <p></p>
                    <legend><b>Device</b></legend>
                    <p></p>

                <div class="w3-container w3-cell w3-mobile">
                    <p><b>Device Name :</b> <!--%DEVICENAME%--></p>
                    <p><b>Device ID :</b> <!--%DEVICEID%--></p>
                    <p><b>Device Location :</b> <!--%DEVICELOCATION%--></p>
                    <p><b>Device Description :</b> <!--%DEVICEDESCRIPTION%--></p>
                    <p><b>VCC :</b> <!--%DEVICEVCC%--></p>
                    <p><b>Last reset reason :</b> <!--%DEVICELASTRESET%--></p>
                </div>
            </fieldset>
            <!------------------------------------------------------------------------------------------------------------------------------------->          
            <p></p>
            <!------------------------------------------------------------------------------------------------------------------------------------->          
            <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                <p></p>
                <legend><b> Web server </b></legend>
                <p></p>
                <div class="w3-container w3-cell w3-mobile">
                    <p><b>User :</b> <!--%WEBUSER%--></p>
                    <p><b>Password :</b> <!--%WEBPASSWORD%--></p>
                    <p><b>Port :</b> <!--%WEBPORT%--></p>
                    <p><b>Status :</b> <!--%WEBSTATUS%--></p>
                </div>
            </fieldset>
            <p></p>

            <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                <p></p>
                <legend><b>SDK</b></legend>
                <p></p>
                <div class="w3-container w3-cell w3-mobile">
                    <p><b>Core version :</b> <!--%COREVERSION%--></p>
                    <p><b>SDK version :</b> <!--%SDKVERSION%--></p>
                    <p><b>Flash status :</b> <!--%FLASHSTATUS%--></p>
            </fieldset>
            <p></p>
            <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                <p></p>
                <legend><b>OTA</b></legend>
                <p></p>
                <div class="w3-container w3-cell w3-mobile">
                    <p><b>OTA activated :</b> <!--%OTAACTIVATED%--></p>
                    <p><b>OTA password :</b> <!--%OTAPASSWORD%--></p>
                </div>
            </fieldset>			   
)=====";


// TAG de la page è remplacer
// 
// <!--%FREEHEAP%-->           : ESP.getFreeHeap()
// <!--%HEAPFRAGMENTATION%-->  : ESP.getHeapFragmentation()
// <!--%HEAPMAXFREEBLOCK%-->   : ESP.getMaxFreeBlockSize() 
// <!--%FLASHCHIPID%-->        : ESP.getFlashChipId()
// <!--%FLASHCHIPSIZE%-->      : ESP.getFlashChipSize()
// <!--%FLASHREALSIZE%-->      : ESP.getFlashChipRealSize()
// <!--%FLASHCIPSPEED%-->      : ESP.getFlashChipSpeed()
// <!--%SKETCHSIZE%-->         : ESP.getSketchSize()
// <!--%SKETCHFREESPACE%-->    : ESP.getFreeSketchSpace()
// <!--%SKETCHMD5%-->          : ESP.getSketchMD5()


const char device_detail_html[] PROGMEM = R"=====(

    <p></p>
    <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <legend><b>Memory</b></legend>
        <div class="w3-container w3-mobile">
          <p>Free Heap : <!--%FREEHEAP%--></p>
          <p>Heap Fragmentation : <!--%HEAPFRAGMENTATION%--></p>
          <p>Max Frees Heap Block : <!--%HEAPMAXFREEBLOCK%--></p>
        </div> 
    </fieldset>
    <p></p>
    <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <legend><b>Flash</b></legend>
        <div class="w3-container w3-mobile">
          <p>Chip ID : <!--%FLASHCHIPID%--></p>
          <p>Chip size : <!--%FLASHCHIPSIZE%--></p>
          <p>Real size : <!--%FLASHREALSIZE%--></p>
          <p>Chip speed : <!--%FLASHCIPSPEED%--></p>
        </div> 
    </fieldset>
    <p></p>
    <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <legend><b>Sketch</b></legend>
        <div class="w3-container w3-mobile">
          <p>Size : <!--%SKETCHSIZE%--></p>
          <p>Free space : <!--%SKETCHFREESPACE%--></p>
          <p>MD5 : <!--%SKETCHMD5%--></p>
        </div> 
    </fieldset>

)=====";

// TAG de la page è remplacer
// 
// <!--%DEVICENAME%-->         : Config.getDeviceName()
// <!--%DEVICELOCATION%-->     : Config.getDeviceLocation()
// <!--%DEVICEDESCRIPTION%-->  : Config.getDeviceDescription()
// <!--%WEBUSER%-->            : Config.getWebUser()
// <!--%WEBPASSWORD%-->        : Config.getWebPassword()
// <!--%WEBPORT%-->            : Config.getWebPort()
// <!--%OTAPASSWORD%-->        : Config.getOtaPassword()
// <!--%OTASTATUS%-->          : Config.getOtaActivated() ? "checked" : ""

const char device_config_html[] PROGMEM = R"=====(

            <!-- Début zone device_config -->
            <div>
                <!------------------------------------------------------------------------------------------------------------------------------------->
                <p></p>
            
                <form id="DeviceForm" action="/device/submit" method="post">
                
                  <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                    <p></p>
                    <legend><b>Device</b></legend>
                    <p></p>
            
                    <div class="w3-row">
                      <div class="w3-third">
                        <label for="devicename">Name :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="devicename" name="devicename" value="<!--%DEVICENAME%-->"><br>
                      </div>
                      <div class="w3-third">
                        <label for="devicelocation">Location :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="devicelocation" name="devicelocation" value="<!--%DEVICELOCATION%-->"><br>
                      </div>
                      <div class="w3-third">
                        <label for="devicedescription">Description :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="devicedescription" name="devicedescription" value="<!--%DEVICEDESCRIPTION%-->"><br>
                      </div>
                    </div>
                  </fieldset>
                <!------------------------------------------------------------------------------------------------------------------------------------->          
                  <p></p>
                <!------------------------------------------------------------------------------------------------------------------------------------->          
                <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                    <p></p>
                    <legend><b> Web server </b></legend>
                    <p></p>
            
                    <div class="w3-row">
                      <div class="w3-third">
                        <label for="webuser">User :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="webuser" name="webuser" value="<!--%WEBUSER%-->"><br>
                      </div>
                      <div class="w3-third">
                        <div class="w3-col" style="width:90%">
                          <label for="webpassword">Password:</label><br>
                          <input class="w3-input w3-border w3-round w3-border-blue" type="password" id="webpassword" name="webpassword" value="<!--%WEBPASSWORD%-->"><br>
                        </div>
                        <div class="w3-col" style="width:10%">
                          <label for="WEBmasquer"></label><br>
                          <button class="w3-button w3-circle w3-blue" type="button" id="WEBmasquer" onclick="toggleWebpasswordVisibility()">+</button>
                        </div>
                      </div>
                      <div class="w3-third">
                        <label for="webport">Port :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="webport" name="webport" value="<!--%WEBPORT%-->"><br>
                      </div>
                    </div>
                  </fieldset>
                <!------------------------------------------------------------------------------------------------------------------------------------->
                <p></p>
                <!------------------------------------------------------------------------------------------------------------------------------------->          
                <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                    <p></p>
                    <legend><b> OTA </b></legend>
                    <p></p>
            
                    <div class="w3-row">
                      <div class="w3-half">
                        <div class="w3-col" style="width:90%">
                          <label for="otapassword">Password:</label><br>
                          <input class="w3-input w3-border w3-round w3-border-blue" type="password" id="otapassword" name="otapassword" value="<!--%OTAPASSWORD%-->"><br>
                        </div>
                        <div class="w3-col" style="width:10%">
                          <label for="OTAmasquer"></label><br>
                          <button class="w3-button w3-circle w3-blue" type="button" id="OTAmasquer" onclick="toggleOTApasswordVisibility()">+</button>
                        </div>
                      </div>
                      <div class="w3-half">
                        <label for="otaport">Port :</label><br>
                        <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="otaport" name="otaport" value="<!--%OTAPORT%-->"><br>
                      </div>
                    </div>
                    <div class="w3-row">
                      <div class="w3-half">
                        <input type="checkbox" id="otaenable" name="otaenable" <!--%OTASTATUS%--> >
                        <label for="otaenable"> Activer le mode OTA</label><br>
                      </div>
                    </div>
                  </fieldset>
                <!------------------------------------------------------------------------------------------------------------------------------------->
            
            
                  <p></p>
                  <div class="w3-row">
                  <div class="w3-third w3-container"></div>
                  <div class="w3-third w3-container ">
                  <input class="w3-col w3-button w3-blue" type="submit" value="Submit">
                  </div>
                  </div>
                </form>
              </div>
            
                <!------------------------------------------------------------------------------------------------------------------------------------->
            
              <script>
            
                function toggleWebpasswordVisibility() {
                  var web_passwordInput = document.getElementById("webpassword");
                  if (web_passwordInput.type === "password") {
                    web_passwordInput.type = "text";
                  } else {
                    web_passwordInput.type = "password";
                  }
                }
                
                function toggleOTApasswordVisibility() {
                  var OTA_passwordInput = document.getElementById("otapassword");
                  if (OTA_passwordInput.type === "password") {
                    OTA_passwordInput.type = "text";
                  } else {
                    OTA_passwordInput.type = "password";
                  }
                }
            
              document.getElementById('DeviceForm').addEventListener('submit', function(event) {
                event.preventDefault();
                var formData = new FormData(this);
                fetch(this.action, {
                    method: this.method,
                    body: formData
                })
                .then(function(response) {
                    if (response.ok) {
                        openPopup();
                    } else {
                        alert('Erreur lors de l\'envoi du formulaire');
                    }
                })
                .catch(function(error) {
                    alert('Erreur lors de l\'envoi du formulaire : ' + error.message);
                });
            });
            
            function openPopup() {
                document.getElementById('popup').style.display = 'block';
            }
            
            function closePopup() {
                document.getElementById('popup').style.display = 'none';
            }
              </script>
)=====";

const char header_mqtt_html[] PROGMEM = R"=====(
    <!-- Début zone header_mqtt -->
    <div id="WiFI" class=" topic" style="display:block">
      <div class="w3-col">
        <a href="/mqtt/info" class=" w3-button <!--%COLORINFO%--> w3-half w3-hover-blue"><b>Info</b></a>
        <a href="/mqtt/config" class="w3-button <!--%COLORCONFIG%--> w3-half w3-hover-blue"><b>Config</b></a>
      </div>
      <p></p>
    <!-- Fin zone header_mqtt -->
)=====";

  // TAG de la page è remplacer
  // <!-- Début zone MQTT_Info -->
  // <!--%MQTTSERVERADDRESS%-->
  // <!--%MQTTSERVERPORT%-->
  // <!--%MQTTUSER%-->
  // <!--%MQTTPASSWORD%-->

const char mqtt_info_html[] PROGMEM = R"=====(
      <p></p>
      <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <legend><b>MQTT</b></legend>
        <div class="w3-container w3-mobile">
          <p>Server address : <!--%MQTTSERVERADDRESS%--></p>
          <p>Server port : <!--%MQTTSERVERPORT%--></p>
          <p>User : <!--%MQTTUSER%--></p>
          <p>Password : <!--%MQTTPASSWORD%--></p>
        </div>
      </fieldset>
      <!-- Fin zone MQTT_Info -->
)=====";

  // TAG de la page è remplacer  
  // <!--%MQTTSERVERADDRESS%-->
  // <!--%MQTTSERVERPORT%-->
  // <!--%MQTTUSER%-->
  // <!--%MQTTPASSWORD%-->

const char mqtt_config_html[] PROGMEM = R"=====(
   <!-- Début zone mqtt_config -->
            <div>
              <!------------------------------------------------------------------------------------------------------------------------------------->
              <p></p>
          
              <form id="MQTTForm" action="/mqtt/submit" method="post">
              
                <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
                  <p></p>
                  <legend><b>MQTT</b></legend>
                  <p></p>
          
                  <div class="w3-row">
                      <label for="mqttserverip">Server address :</label><br>
                      <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="mqttserverip" name="mqttserverip" value="<!--%MQTTSERVERADDRESS%-->"><br>
                  <div class="w3-row">
                      <label for="mqttport">Server port :</label><br>
                      <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="mqttport" name="mqttport" value="<!--%MQTTSERVERPORT%-->"><br>
                    </div>
                    <div class="w3-row">
                      <label for="mqttuser">User :</label><br>
                      <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="mqttuser" name="mqttuser" value="<!--%MQTTUSER%-->"><br>
                    </div>
                  </div>
                  <div class="w3-row">
                    <div class="w3-col" style="width:85%">
                      <label for="mqttpassword">Password :</label><br>
                      <input class="w3-input w3-border w3-round w3-border-blue" type="password" id="mqttpassword" name="mqttpassword" value="<!--%MQTTPASSWORD%-->"><br>
                    </div>
                    <div class="w3-col" style="width:5%">
                      <p></p>
                    </div>
                    <div class="w3-col" style="width:10%">
                      <label for="MQTTmasquer"></label><br>
                      <button class="w3-button w3-circle w3-blue" type="button" id="MQTTmasquer" onclick="togglemqttpasswordVisibility()">+</button>
                    </div>
                  </div>

                </fieldset>
          
          
                <p></p>
                <div class="w3-row">
                <div class="w3-third w3-container"></div>
                <div class="w3-third w3-container ">
                <input class="w3-col w3-button w3-blue" type="submit" value="Submit">
                </div>
                </div>
              </form>
            </div>
          
              <!------------------------------------------------------------------------------------------------------------------------------------->
          
            <script>
          
              function togglemqttpasswordVisibility() {
                var web_passwordInput = document.getElementById("mqttpassword");
                if (web_passwordInput.type === "password") {
                  web_passwordInput.type = "text";
                } else {
                  web_passwordInput.type = "password";
                }
              }
              
          
            document.getElementById('MQTTForm').addEventListener('submit', function(event) {
              event.preventDefault();
              var formData = new FormData(this);
              fetch(this.action, {
                  method: this.method,
                  body: formData
              })
              .then(function(response) {
                  if (response.ok) {
                      openPopup();
                  } else {
                      alert('Erreur lors de l\'envoi du formulaire');
                  }
              })
              .catch(function(error) {
                  alert('Erreur lors de l\'envoi du formulaire : ' + error.message);
              });
          });
          
          function openPopup() {
              document.getElementById('popup').style.display = 'block';
          }
          
          function closePopup() {
              document.getElementById('popup').style.display = 'none';
          }
            </script>
)=====";

// TAG de la page è remplacer
// <!--%COLORINFO%--> : w3-blue si actif w3-light-blue si inactif
// <!--%COLORSCAN%--> : w3-blue si actif w3-light-blue si inactif
// <!--%COLORCONFIG%--> : w3-blue si actif w3-light-blue si inactif

const char header_wifi_html[] PROGMEM = R"=====(
       <!-- Début zone header_WiFi -->
        <div id="WiFI" class=" topic" style="display:block">
            <div class="w3-col">
                <a href="/wifi/info" class=" w3-button <!--%COLORINFO%--> w3-third w3-hover-blue"><b>Info</b></a>
                <a href="/wifi/scan" class="w3-button <!--%COLORSCAN%--> w3-third w3-hover-blue"><b>Scan</b></a>
                <a href="/wifi/config" class="w3-button <!--%COLORCONFIG%--> w3-third w3-hover-blue"><b>Config</b></a>
            </div>
        </div>
)=====";



// TAG de la page è remplacer
// <!--%SSID%--> : SSID du röseau
// <!--%RSSI%-->
// <!--%ACCESSPOINT%-->
// <!--%CANAL%-->
// <!--%IP%-->
// <!--%SUBNET%-->
// <!--%GATEWAY%-->
// <!--%DNS%-->
//

const char wifi_info_html[] PROGMEM = R"=====(
    <!-- Début zone WiFi Info -->
    <div class="w3-container">
        <p></p>
        <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
            <legend>
                <h3>Info WiFi</h3>
            </legend>
            <div class="w3-row">
                <div class="w3-col l1 s5">SSID</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%SSID%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">RSSI</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%RSSI%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">Access point</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%ACCESSPOINT%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">Canal</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%CANAL%--></div>
            </div>
        </fieldset>
        <p></p>
        <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
            <legend>
                <h3>Configuration IP</h3>
            </legend>
            <div class="w3-row">
                <div class="w3-col l1 s5">IP</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%IP%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">Subnet</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%SUBNET%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">Gateway</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%GATEWAY%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s5">DNS</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%DNS%--></div>
            </div>
        </fieldset>
    </div>
    <!-- Fin zone WiFi Info -->
      )=====";

// TAG de la page è remplacer
// <!--%NETLINE%-->

const char wifi_scan_html[] PROGMEM = R"=====(
    <!-- Début de la section WiFi Scan -->
    <div class="w3-container">
        <h3>WiFi disponible</h3>
        <p></p>
        <!--%NETLINE%-->
    </div>
    <!-- Fin de la section WiFi Scan -->
)=====";


// TAG de la page è remplacer
// <!--%SSID%--> 
// <!--%RSSI%-->
// <!--%ENCRYPT%-->
// <!--%BSSID%-->
// <!--%CHANNEL%-->
// <!--%HIDDEN%-->

const char wifi_scanrow_html[] PROGMEM = R"=====(
        <!-- Début de la section Scan rows -->
        <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
            <legend>
                <h5> <!--%SSID%--> </h5>
            </legend>
            <div class="w3-row">
                <div class="w3-col l1 s4">RSSI</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s6"><!--%RSSI%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s4">S&eacute;curit&eacute;</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s7"><!--%ENCRYPT%--></div>
            </div>

            <div class="w3-row">
                <div class="w3-col l1 s4">Access point</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s7"><!--%BSSID%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s4">Cach&eacute;</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s7"><!--%HIDDEN%--></div>
            </div>
            <div class="w3-row">
                <div class="w3-col l1 s4">Canal</div>
                <div class="w3-col l1 s1"> : </div>
                <div class="w3-col l9 s7"><!--%CHANNEL%--></div>
            </div>
        </fieldset>
        <p></p>
        <!-- Fin de la section Scan rows -->
)=====";


// TAG de la page è remplacer
// <!--%STASSID%--> 
// <!--%STASSIDPW%-->
// <!--%STASTATUS%-->   valeur checked ou vide
// <!--%STADHCP%-->     valeur checked ou vide
// <!--%STAIP%-->
// <!--%STASUBNET%-->
// <!--%STAGATEWAY%-->
// <!--%STADNS%-->
// <!--%APSSID%-->
// <!--%APSSIDPW%-->
// <!--%APSTATUS%-->   valeur checked ou vide
// <!--%APCDEFAUT%-->  valeur checked ou vide
// <!--%APIP%-->
// <!--%APSUBNET%-->
// <!--%APGATEWAY%-->
// <!--%APDNS%-->


const char wifi_config_html[] PROGMEM = R"=====(
<!-- Début zone WiFi Config -->

<div>
    <!------------------------------------------------------------------------------------------------------------------------------------->
    <p></p>

    <form id="WiFiForm" action="/wifi/submit" method="post">
    <!------------------------------------------------------------------------------------------------------------------------------------->

      <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <p></p>
        <legend><b>Mode client</b></legend>
        <p></p>

        <div class="w3-row">
          <div class="w3-half">
            <label for="STAssid">SSID:</label><br>
            <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="STAssid" name="STAssid" value="<!--%STASSID%-->"><br>
          </div>
          <div class="w3-half">
            <div class="w3-col" style="width:90%">
              <label for="STApassword">Password:</label><br>
              <input class="w3-input w3-border w3-round w3-border-blue" type="password" id="STApassword" name="STApassword" value="<!--%STASSIDPW%-->"><br>
            </div>
            <div class="w3-col" style="width:10%">
              <label for="masquer"></label><br>
              <button class="w3-button w3-circle w3-blue" type="button" id="STAmasquer" onclick="toggleSTAPasswordVisibility()">+</button>
            </div>
         </div> 
        </div>

    <!------------------------------------------------------------------------------------------------------------------------------------->

        <div class="w3-row">
          <div class="w3-half">
            <input type="checkbox" id="stamode" name="stamode" <!--%STASTATUS%-->>
            <label for="stamode"> Activer le mode client</label><br>
          </div>
          <div class="w3-half">
            <input type="checkbox" id="STAtoggleIP"  name="stadhcp" onclick="_STAtoggleIP()" <!--%STADHCP%-->>
            <label for="STAtoggleIP"> Utiliser DHCP</label><br>
            <p></p>
          </div>
      </div>

    <!----------------------------------------------onclick="_STAtoggleIP()"--------------------------------------------------------------------------------------->

      <div id="STAipForm" style="display:none">
            <p><b>Adresse statique</b></p>
            <div class="w3-row-padding">
              <div class="w3-half">
                <label for="STAadress">Adresse:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="STAadress" name="STAadress" value="<!--%STAIP%-->"><br>
              </div>
              <div class="w3-half">
                <label for="STAsubnet">Subnet:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="STAsubnet" name="STAsubnet" value="<!--%STASUBNET%-->"><br>
              </div>
              <div class="w3-half">
                <label for="STAgateway">Gateway:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="STAgateway" name="STAgateway" value="<!--%STAGATEWAY%-->"><br>
              </div>
              <div class="w3-half">
                <label for="STAdns">DNS:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="STAdns" name="STAdns" value="<!--%STADNS%-->"><br>
              </div>
            </div>
          </div>

      </fieldset>

    <!------------------------------------------------------------------------------------------------------------------------------------->
      <p></p>
      <fieldset class="w3-bottombar w3-topbar w3-round w3-border-blue">
        <p></p>
        <legend><b>Mode acces point</b></legend>
        <p></p>

        <div class="w3-row">
          <div class="w3-half">
            <label for="APssid">SSID:</label><br>
            <input class="w3-input w3-border w3-round w3-border-blue" type="text" id="APssid" name="APssid" value="<!--%APSSID%-->"><br>
          </div>
          <div class="w3-half">
            <div class="w3-col" style="width:90%">
              <label for="APpassword">Password:</label><br>
              <input class="w3-input w3-border w3-round w3-border-blue" type="password" id="APpassword" name="APpassword" value="<!--%APSSIDPW%-->"><br>
            </div>
            <div class="w3-col" style="width:10%">
              <label for="APmasquer"></label><br>
              <button class="w3-button w3-circle w3-blue" type="button" id="APmasquer" onclick="toggleAPPasswordVisibility()">+</button>
            </div>
          </div>
        </div>

    <!------------------------------------------------------------------------------------------------------------------------------------->

        <div class="w3-row">
          <div class="w3-half">
            <input type="checkbox" id="apmode" name="apmode" <!--%APSTATUS%--> >
            <label for="apmode"> Activer le mode access point</label><br>
          </div>
          <div class="w3-half">
            <input type="checkbox" id="APtoggleIP" name="IPdefault" onclick="_APtoggleIP()" <!--%APCDEFAUT%--> >
            <label for="APtoggleIP"> Utiliser la configuration par d&eacute;faut</label><br>
            <p></p>
          </div>
        </div>

    <!------------------------------------------------------------------------------------------------------------------------------------->

        <div id="APipForm" style="display:none">
            <p><b>Configuration personalis&eacute;e</b></p>
            <div class="w3-row">
              <div class="w3-half">
                <label for="APadress">Adresse:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="APadress" name="APadress" value="<!--%APIP%-->"><br>
              </div>
              <div class="w3-half">
                <label for="APsubnet">Subnet:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="APsubnet" name="APsubnet" value="<!--%APSUBNET%-->"><br>
              </div>
              <div class="w3-half">
                <label for="APgateway">Gateway:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="APgateway" name="APgateway" value="<!--%APGATEWAY%-->"><br>
              </div>
              <div class="w3-half">
                <label for="APdns">DNS:</label><br>
                <input class="w3-input w3-border w3-border-blue" type="text" id="APdns" name="APdns" value="<!--%APDNS%-->"><br>
              </div>
            </div>
          </div>
      </fieldset>
    <!------------------------------------------------------------------------------------------------------------------------------------->


      <p></p>
      <div class="w3-row">
      <div class="w3-third w3-container"></div>
      <div class="w3-third w3-container ">
      <input class="w3-col w3-button w3-blue" type="submit" value="Submit">
      </div>
      </div>
    </form>
  </div>

    <!------------------------------------------------------------------------------------------------------------------------------------->

  <script>

    function _onloadBody() {
      var sta_checkBox = document.getElementById('STAtoggleIP');
      var sta_ipForm = document.getElementById('STAipForm');
      sta_ipForm.style.display = sta_checkBox.checked ? 'none' : 'block';
      sta_checkBox.addEventListener('change', function () {
          sta_ipForm.style.display = this.checked ? 'none' : 'block';
      });
      var ap_checkBox = document.getElementById('APtoggleIP');
      var ap_ipForm = document.getElementById('APipForm');
      ap_ipForm.style.display = ap_checkBox.checked ? 'none' : 'block';
      ap_checkBox.addEventListener('change', function () {
          ap_ipForm.style.display = this.checked ? 'none' : 'block';
      });
    };


    function _STAtoggleIP() {
      var sta_checkBox = document.getElementById("STAtoggleIP");
      var sta_ipForm = document.getElementById("STAipForm");
      if (sta_checkBox.checked === true) {
        sta_ipForm.style.display = "none";
      } else {
        sta_ipForm.style.display = "block";
      }
    }

    function _APtoggleIP() {
      var ap_checkBox = document.getElementById("APtoggleIP");
      var ap_ipForm = document.getElementById("APipForm");
      if (ap_checkBox.checked === true) {
        ap_ipForm.style.display = "none";
      } else {
        ap_ipForm.style.display = "block";
      }
    }

    function toggleSTAPasswordVisibility() {
      var sta_passwordInput = document.getElementById("STApassword");
      if (sta_passwordInput.type === "password") {
        sta_passwordInput.type = "text";
      } else {
        sta_passwordInput.type = "password";
      }
    }
    function toggleAPPasswordVisibility() {
      var ap_passwordInput = document.getElementById("APpassword");
      if (ap_passwordInput.type === "password") {
        ap_passwordInput.type = "text";
      } else {
        ap_passwordInput.type = "password";
      }
    }

  document.getElementById('WiFiForm').addEventListener('submit', function(event) {
    event.preventDefault();
    var formData = new FormData(this);
    fetch(this.action, {
        method: this.method,
        body: formData
    })
    .then(function(response) {
        if (response.ok) {
            openPopup();
        } else {
            alert('Erreur lors de l\'envoi du formulaire');
        }
    })
    .catch(function(error) {
        alert('Erreur lors de l\'envoi du formulaire : ' + error.message);
    });
});

function openPopup() {
    document.getElementById('popup').style.display = 'block';
}

function closePopup() {
    document.getElementById('popup').style.display = 'none';
}
  </script>


)=====";

const char w3css[] PROGMEM = R"=====(
html{box-sizing:border-box}*,:after,:before{box-sizing:inherit}html{-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}header,section{display:block}[hidden]{display:none}a{background-color:transparent}a:active,a:hover{outline-width:0}b{font-weight:bolder}button,input{font:inherit;margin:0}button,input{overflow:visible}button{text-transform:none}[type=button],[type=reset],[type=submit],button{-webkit-appearance:button}[type=button]::-moz-focus-inner,[type=reset]::-moz-focus-inner,[type=submit]::-moz-focus-inner,button::-moz-focus-inner{border-style:none;padding:0}[type=button]:-moz-focusring,[type=reset]:-moz-focusring,[type=submit]:-moz-focusring,button:-moz-focusring{outline:1px dotted ButtonText}fieldset{border:1px solid silver;margin:0 2px;padding:.35em .625em .75em}legend{color:inherit;display:table;max-width:100%;padding:0;white-space:normal}[type=checkbox],[type=radio]{padding:0}[type=number]::-webkit-inner-spin-button,[type=number]::-webkit-outer-spin-button{height:auto}[type=search]{-webkit-appearance:textfield;outline-offset:-2px}[type=search]::-webkit-search-decoration{-webkit-appearance:none}::-webkit-file-upload-button{-webkit-appearance:button;font:inherit}body,html{font-family:Verdana,sans-serif;font-size:15px;line-height:1.5}html{overflow-x:hidden}h1{font-size:36px}h2{font-size:30px}h3{font-size:24px}h4{font-size:20px}h5{font-size:18px}h6{font-size:16px}h1,h2,h3,h4,h5,h6{font-family:"Segoe UI",Arial,sans-serif;font-weight:400;margin:10px 0}a{color:inherit}.w3-table,.w3-table-all{border-collapse:collapse;border-spacing:0;width:100%;display:table}.w3-table-all{border:1px solid #ccc}.w3-table-all tr{border-bottom:1px solid #ddd}.w3-table-all tr:nth-child(odd){background-color:#fff}.w3-table-all tr:nth-child(even){background-color:#f1f1f1}.w3-table th,.w3-table-all th{padding:8px 8px;display:table-cell;text-align:left;vertical-align:top}.w3-table th:first-child,.w3-table-all th:first-child{padding-left:16px}.w3-button{border:none;display:inline-block;padding:8px 16px;vertical-align:middle;overflow:hidden;text-decoration:none;color:inherit;background-color:inherit;text-align:center;cursor:pointer;white-space:nowrap}.w3-button{-webkit-touch-callout:none;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}.w3-button:disabled{cursor:not-allowed;opacity:.3}:disabled *{pointer-events:none}.w3-display-container{position:relative}.w3-input{padding:8px;display:block;border:none;border-bottom:1px solid #ccc;width:100%}.w3-modal{z-index:3;display:none;padding-top:100px;position:fixed;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:#000;background-color:rgba(0,0,0,.4)}.w3-modal-content{margin:auto;background-color:#fff;position:relative;padding:0;outline:0;width:600px}.w3-block{display:block;width:100%}.w3-container:after,.w3-container:before,.w3-row-padding:after,.w3-row-padding:before,.w3-row:after,.w3-row:before{content:"";display:table;clear:both}.w3-col,.w3-half,.w3-third{float:left;width:100%}.w3-col.s1{width:8.33333%}.w3-col.s2{width:16.66666%}.w3-col.s3{width:24.99999%}.w3-col.s4{width:33.33333%}.w3-col.s5{width:41.66666%}.w3-col.s6{width:49.99999%}.w3-col.s7{width:58.33333%}.w3-col.s8{width:66.66666%}.w3-col.s9{width:74.99999%}.w3-col.s10{width:83.33333%}.w3-col.s11{width:91.66666%}.w3-col.s12{width:99.99999%}@media (min-width:601px){.w3-third{width:33.33333%}.w3-half{width:49.99999%}}@media (min-width:993px){.w3-col.l1{width:8.33333%}.w3-col.l2{width:16.66666%}.w3-col.l3{width:24.99999%}.w3-col.l4{width:33.33333%}.w3-col.l5{width:41.66666%}.w3-col.l6{width:49.99999%}.w3-col.l7{width:58.33333%}.w3-col.l8{width:66.66666%}.w3-col.l9{width:74.99999%}.w3-col.l10{width:83.33333%}.w3-col.l11{width:91.66666%}.w3-col.l12{width:99.99999%}}.w3-content{margin-left:auto;margin-right:auto}.w3-content{max-width:980px}@media (max-width:600px){.w3-modal-content{margin:0 10px;width:auto!important}.w3-modal{padding-top:30px}}@media (max-width:768px){.w3-modal-content{width:500px}.w3-modal{padding-top:50px}}@media (min-width:993px){.w3-modal-content{width:900px}}.w3-display-topright{position:absolute;right:0;top:0}.w3-display-container:hover .w3-display-hover{display:block}.w3-display-container:hover span.w3-display-hover{display:inline-block}.w3-display-hover{display:none}.w3-circle{border-radius:50%}.w3-round{border-radius:4px}.w3-row-padding,.w3-row-padding>.w3-col,.w3-row-padding>.w3-half,.w3-row-padding>.w3-third{padding:0 8px}.w3-container{padding:.01em 16px}.w3-card,.w3-card-2{box-shadow:0 2px 5px 0 rgba(0,0,0,.16),0 2px 10px 0 rgba(0,0,0,.12)}.w3-card-4{box-shadow:0 4px 10px 0 rgba(0,0,0,.2),0 4px 20px 0 rgba(0,0,0,.19)}@keyframes w3-spin{0%{transform:rotate(0)}100%{transform:rotate(359deg)}}@keyframes fading{0%{opacity:0}50%{opacity:1}100%{opacity:0}}@keyframes opac{from{opacity:0}to{opacity:1}}@keyframes animatetop{from{top:-300px;opacity:0}to{top:0;opacity:1}}@keyframes animateleft{from{left:-300px;opacity:0}to{left:0;opacity:1}}@keyframes animateright{from{right:-300px;opacity:0}to{right:0;opacity:1}}@keyframes animatebottom{from{bottom:-300px;opacity:0}to{bottom:0;opacity:1}}@keyframes animatezoom{from{transform:scale(0)}to{transform:scale(1)}}.w3-center{text-align:center!important}.w3-border-0{border:0!important}.w3-border{border:1px solid #ccc!important}.w3-topbar{border-top:6px solid #ccc!important}.w3-bottombar{border-bottom:6px solid #ccc!important}.w3-section{margin-top:16px!important;margin-bottom:16px!important}.w3-padding{padding:8px 16px!important}.w3-padding-16{padding-top:16px!important;padding-bottom:16px!important}.w3-padding-24{padding-top:24px!important;padding-bottom:24px!important}.w3-padding-32{padding-top:32px!important;padding-bottom:32px!important}.w3-padding-48{padding-top:48px!important;padding-bottom:48px!important}.w3-padding-64{padding-top:64px!important;padding-bottom:64px!important}.w3-button:hover{color:#000!important;background-color:#ccc!important}.w3-hover-none:hover{background-color:transparent!important}.w3-hover-none:hover{box-shadow:none!important}.w3-blue,.w3-hover-blue:hover{color:#fff!important;background-color:#2196f3!important}.w3-hover-light-blue:hover,.w3-light-blue{color:#000!important;background-color:#87ceeb!important}.w3-hover-red:hover,.w3-red{color:#fff!important;background-color:#f44336!important}.w3-hover-text-blue:hover,.w3-text-blue{color:#2196f3!important}.w3-hover-text-light-blue:hover,.w3-text-light-blue{color:#87ceeb!important}.w3-hover-text-red:hover,.w3-text-red{color:#f44336!important}.w3-border-blue,.w3-hover-border-blue:hover{border-color:#2196f3!important}.w3-border-light-blue,.w3-hover-border-light-blue:hover{border-color:#87ceeb!important}.w3-border-red,.w3-hover-border-red:hover{border-color:#f44336!important}
)=====";
#endif //ESPCONFIGPAGEHTML_H