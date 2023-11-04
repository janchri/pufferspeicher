var sensors_id = ['289CDB22602206A3','2842605C602206F6','28F713436022069B','281D649A602206D3','288FCA0F602206FD','2869D16A6022067B','2861516D60220697','28E8A6686022069D','28D9F3696022068F','286BA98C60220606'];
var sensors_tmp = [95, 90, 60, 55, 50, 40, 35, 30, 27, 22];

var loc = window.location;
//const webSocketUrl = "ws://"+loc.host+"/ws";
const webSocketUrl = "ws://192.168.178.51/ws";
const ws = new WebSocket(webSocketUrl);
ws.onopen = function (openEvent) {
    ws.send("Hello Server!");
}
ws.onmessage = function (messageEvent) {
    console.log("...refresh...");
    try{
        var sensors = JSON.parse(messageEvent.data);
        for (let i in sensors.sensor) {
            sensors_tmp[sensors_id.indexOf(sensors.sensor[i].sensor_id)] = sensors.sensor[i].sensor_tmp;
        }
        updateView();
    } catch(e) {
        console.log(messageEvent.data);
    }
    
};
ws.onclose = function (closeEvent) {
    console.log("WebSocket wurde geschlossen");
};

function updateView(){
    for (let i in sensors_tmp){
        document.getElementById(sensors_id[i]).getElementsByClassName('value')[0].innerHTML = sensors_tmp[i];
    }
    document.getElementById("rectangle").style.background = getLinearGradient(sensors_tmp);
}

function getLinearGradient(temps) {
    var perc = [20, 30, 40, 50, 55, 70, 75, 80, 85, 95];
    var str = 'linear-gradient(to bottom';
    for(let i in temps){
        str += ',hsl(' +[getHue(temps[i]), '100%', '50%'] + ')'+perc[i]+'%';
    }
    str += ')';
    //console.log(str);
    return str;
    //return 'linear-gradient(to top,'+'hsl(' +[getHue(temps[0]), '100%', '50%'] + ')'+' 0%,'+'hsl(' +[getHue(temps[9]), '100%', '50%'] + ')'+' 100%)';
}

function getHue(currTemp) {
  // https://stackoverflow.com/questions/49482002/javascript-map-a-temperature-to-a-particular-hsl-hue-value
  // following hsl wheel counterclockwise from 0
  // to go clockwise, make maxHsl and minHsl negative 
  var maxHsl = 400; // maxHsl maps to max temp (here: 20deg past 360)
  var minHsl = 250; //  minhsl maps to min temp counter clockwise
  var rngHsl = maxHsl - minHsl; // = 210

  var maxTemp = 95;
  var minTemp = 20;
  var rngTemp = maxTemp - minTemp; // 125
  var degCnt = maxTemp - currTemp; // 0
  var hslsDeg = rngHsl / rngTemp;  //210 / 125 = 1.68 Hsl-degs to Temp-degs
  var returnHue = (360 - ((degCnt * hslsDeg) - (maxHsl - 360))); 
  return returnHue;  
}
