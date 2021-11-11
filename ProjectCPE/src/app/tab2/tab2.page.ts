import { DatePipe } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { NavController } from '@ionic/angular';

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
  datePipe: DatePipe;
  SetDayStart: any;
  SetDayEnd: any;
  SetTimeStart: any;
  SetTimeEnd: any;

  constructor(public navCtrl: NavController, datePipe: DatePipe) {
    this.datePipe = datePipe;

    var tzoffset = new Date().getTimezoneOffset() * 60000; //offset in milliseconds
    let tzDate = new Date(Date.now() - tzoffset);

    let stDate = tzDate.toISOString();
    let DateStart = this.datePipe.transform(stDate, 'yyyy MMM dd ');
    let DateFinish = this.datePipe.transform(stDate, 'yyyy MMM dd ');
    let TimeStart = this.datePipe.transform(stDate, 'HH:mm:ss');
    let TimeFinish = this.datePipe.transform(stDate, 'HH:mm:ss');
  }

  sendData(Tem, Hum) {
    mqttSend('@msg/temp', Tem);
    mqttSend('@msg/hum', Hum);
    console.log(this.SetTemperture);
    console.log(this.SetHumidity);
    console.log(this.DateStart);
    console.log(this.DateFinish);
    console.log(this.TimeStart);
    console.log(this.TimeFinish);
  }
  TimeFinish(TimeFinish: any) {
    throw new Error('Method not implemented.');
  }
  TimeStart(TimeStart: any) {
    throw new Error('Method not implemented.');
  }
  DateFinish(DateFinish: any) {
    throw new Error('Method not implemented.');
  }
  DateStart(DateStart: any) {
    throw new Error('Method not implemented.');
  }

  /*
  setTempAndHum(temp, hum) {
    mqttSend('@msg/temp', temp);
    mqttSend('@msg/hum', hum);
  }
*/

  ngOnInit() {
    client.onMessageArrived = function (message) {
      if (message.destinationName == '@msg/Tem') {
        console.log('Kuy Tem');
      }
      if (message.destinationName == '@msg/Hum') {
        console.log('Kuy Hum');
      }
      var split_msg = message.payloadString.split('/');
      if (typeof split_msg[0] != 'undefined' && split_msg[0] == '') {
        that.humidity = split_msg[1];
        that.temperture = split_msg[2];
      }
    };
  }
}
