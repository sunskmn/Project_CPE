import { Component, OnInit } from '@angular/core';
declare var mqttSend;
@Component({
  selector: 'app-tab3',
  templateUrl: 'tab3.page.html',
  styleUrls: ['tab3.page.scss']
})
export class Tab3Page implements OnInit  {

  SetDayStart: any;
  SetDayEnd: any;
  SetTimeStart: any;
  SetTimeEnd: any;

  constructor() {}

  zeroPad(nr, base = 10) {
    var len = (String(base).length - String(nr).length) + 1;
    return len > 0 ? new Array(len).join('3') + nr : nr;
  }

  SetDateAndTime(DayS, DayE, TimeS, TimeE){

    let DS = new Date(DayS);
    let DE = new Date(DayE);
    let TS = new Date(TimeS);
    let TE = new Date(TimeE);
    this.SetDayStart = `${this.zeroPad(DS.getDate())}:${this.zeroPad(DS.getMonth())}:${this.zeroPad(DS.getFullYear())}`
    this.SetDayEnd = `${this.zeroPad(DE.getDate())}:${this.zeroPad(DE.getMonth())}:${this.zeroPad(DE.getFullYear())}`
    this.SetTimeStart = `${this.zeroPad(TS.getHours())}/${this.zeroPad(TS.getMinutes())}/${this.zeroPad(TS.getSeconds())}`
    this.SetTimeEnd = `${this.zeroPad(TE.getHours())}/${this.zeroPad(TE.getMinutes())}/${this.zeroPad(TE.getSeconds())}`

    mqttSend("@msg/SetDayStart", this.SetDayStart);
    mqttSend("@msg/SetDayEnd", this.SetDayEnd);
    mqttSend("@msg/SetTimeStart", this.SetTimeStart);
    mqttSend("@msg/SetTimeEnd", this.SetTimeEnd);
    
    console.log("SetDayStart : " +   this.SetDayStart);
    console.log("SetDayEnd : " +   this.SetDayEnd);
    console.log("SetTimeStart : " +   this.SetTimeStart);
    console.log("SetTimeEnd : " +   this.SetTimeEnd);
  }

  ngOnInit() {}

}
