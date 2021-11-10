import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';


declare var client;
declare var mqttSend;
declare var delay;
let that;
@Component({
  selector: 'app-tab1',
  templateUrl: 'tab1.page.html',
  styleUrls: ['tab1.page.scss']
})

export class Tab1Page implements OnInit {

  temperture;
  humidity;
  ShowTemp;
  ShowHum;
  ca = false;

  /** 
  temperture: any;
  humidity: any;
  ShowTemp: any;
  ShowHum: any;
  ca: any = false;
  */

  constructor(
    
  ) {
    that = this;
    
  }

  async ShowTemperture() {
    this.ShowTemp = this.temperture;
    let de = await delay(3000);
    this.ShowTemp = null;
  }   

  async ShowHumidity() {
    this.ShowHum = this.humidity;
    let de = await delay(3000);
    this.ShowHum = null;
  }

  /*
  async LED_ON() {
    if(this.ca == false){
      this.ca = true;
      mqttSend("@msg/led", "LEDON");
      //let de = await delay(3000);
    }
    else {
      this.ca = false;
      mqttSend("@msg/led", "LEDOFF");
    }
   console.log(this.ca); 
  }
*/

  async ngOnInit() {
    client.onMessageArrived = function (message) {
          var split_msg = message.payloadString.split("/");
          if (typeof (split_msg[0]) != 'undefined' && split_msg[0] == "") {
              that.humidity = split_msg[1];
              that.temperture = split_msg[2];
      } 
    }
  }
}
