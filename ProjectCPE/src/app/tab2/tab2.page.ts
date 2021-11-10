import { Component, OnInit } from '@angular/core';

declare var client;
declare var mqttSend;
declare var delay;
let that;
@Component({
  selector: 'app-tab2',
  templateUrl: 'tab2.page.html',
  styleUrls: ['tab2.page.scss'],
})
export class Tab2Page implements OnInit {
  temperture: any;
  humidity: any;

  SetTemperture;
  SetHumidity;

  constructor() {
    that = this;
  }

  sendData(Tem, Hum) {
    let dataSystem = Tem + "/" + Hum + "/" + "10;11;2021" + "/" + "09:30:00" + "/" + "21:00:00";
    mqttSend("@msg/DataSys", dataSystem);
    console.log(dataSystem);
  }

  ngOnInit() {
    client.onMessageArrived = function (message) {
      if (message.destinationName == "@msg/Tem") {
        console.log("Kuy Tem");
      }
      if (message.destinationName == "@msg/Hum") {
        console.log("Kuy Hum");
      }
      var split_msg = message.payloadString.split('/');
      if (typeof split_msg[0] != 'undefined' && split_msg[0] == '') {
        that.humidity = split_msg[1];
        that.temperture = split_msg[2];
      }
    };
  }
}
