var loc = window.location;
//const webSocketUrl = "ws://"+loc.host+"/ws";
const webSocketUrl = "ws://192.168.178.51/ws";
const ws = new WebSocket(webSocketUrl);
ws.onopen = function (openEvent) {
    ws.send("Hello Server!");
}
ws.onmessage = function (messageEvent) {
    console.log("...refresh...");
    var sensors = JSON.parse(messageEvent.data);
    for (let i in sensors.sensor) {
        document.getElementById(sensors.sensor[i].sensor_id).innerHTML = sensors.sensor[i].sensor_tmp;
    }
    colorWarmWaterBoiler([sensors.sensor[0].sensor_tmp,
            sensors.sensor[1].sensor_tmp,
            sensors.sensor[2].sensor_tmp,
            sensors.sensor[3].sensor_tmp,
            sensors.sensor[4].sensor_tmp,
            sensors.sensor[5].sensor_tmp,
            sensors.sensor[6].sensor_tmp,
            sensors.sensor[7].sensor_tmp,
            sensors.sensor[8].sensor_tmp,
            sensors.sensor[9].sensor_tmp]);
};
ws.onclose = function (closeEvent) {
    console.log("WebSocket wurde geschlossen");
};

function colorWarmWaterBoiler(temps){
    document.getElementById("rectangle").style.background = getLinearGradient(temps);
}

function getLinearGradient(temps) {
    var perc = [20, 30, 40, 50, 55, 70, 75, 80, 85, 95];
    var str = 'linear-gradient(to top';
    for(let i in temps){
        str += ',hsl(' +[getHue(temps[i]), '100%', '50%'] + ')'+perc[i]+'%';
    }
    str += ')';
    console.log(str);
    return str;
    //return 'linear-gradient(to top,'+'hsl(' +[getHue(temps[0]), '100%', '50%'] + ')'+' 0%,'+'hsl(' +[getHue(temps[9]), '100%', '50%'] + ')'+' 100%)';
}

function getHue(currTemp) {
  // https://stackoverflow.com/questions/49482002/javascript-map-a-temperature-to-a-particular-hsl-hue-value
  // following hsl wheel counterclockwise from 0
  // to go clockwise, make maxHsl and minHsl negative 
  var maxHsl = 400; // maxHsl maps to max temp (here: 20deg past 360)
  var minHsl = 220; //  minhsl maps to min temp counter clockwise
  var rngHsl = maxHsl - minHsl; // = 210

  var maxTemp = 95;
  var minTemp = 20;
  var rngTemp = maxTemp - minTemp; // 125
  var degCnt = maxTemp - currTemp; // 0
  var hslsDeg = rngHsl / rngTemp;  //210 / 125 = 1.68 Hsl-degs to Temp-degs
  var returnHue = (360 - ((degCnt * hslsDeg) - (maxHsl - 360))); 
  return returnHue;  
}
