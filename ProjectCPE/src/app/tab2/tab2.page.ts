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

  sendData() {
    console.log(this.SetTemperture);
    console.log(this.SetHumidity);
  }

  setTempAndHum(temp, hum) {
    mqttSend('@msg/temp', temp);
    mqttSend('@msg/hum', hum);
  }

  ngOnInit() {
    client.onMessageArrived = function (message) {
      var split_msg = message.payloadString.split('/');
      if (typeof split_msg[0] != 'undefined' && split_msg[0] == '') {
        that.humidity = split_msg[1];
        that.temperture = split_msg[2];
      }
    };
  }
}
