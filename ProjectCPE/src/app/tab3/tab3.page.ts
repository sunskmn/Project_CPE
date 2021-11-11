import { DatePipe } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { NavController } from '@ionic/angular';

declare var mqttSend;
@Component({
  selector: 'app-tab3',
  templateUrl: 'tab3.page.html',
  styleUrls: ['tab3.page.scss'],
})
export class Tab3Page implements OnInit {
  datePipe: DatePipe;

  SetDayStart: any;
  SetDayEnd: any;
  SetTimeStart: any;
  SetTimeEnd: any;
  panelShow: boolean;

  show: boolean;

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

  private tutorialHidden: boolean = true;

  abrirTutorial() {
    if (this.tutorialHidden === true) {
      this.tutorialHidden = false;
      document.getElementById('tutorial').hidden = false;
    } else if (this.tutorialHidden === false) {
      this.tutorialHidden = true;
      document.getElementById('tutorial').hidden = true;
    }
  }
  zeroPad(nr, base = 10) {
    var len = String(base).length - String(nr).length + 1;
    return len > 0 ? new Array(len).join('3') + nr : nr;
  }

  SetDateAndTime(DayS, DayE, TimeS, TimeE) {
    let DS = new Date(DayS);
    let DE = new Date(DayE);
    let TS = new Date(TimeS);
    let TE = new Date(TimeE);
    this.SetDayStart = `${this.zeroPad(DS.getDate())}:${this.zeroPad(
      DS.getMonth()
    )}:${this.zeroPad(DS.getFullYear())}`;
    this.SetDayEnd = `${this.zeroPad(DE.getDate())}:${this.zeroPad(
      DE.getMonth()
    )}:${this.zeroPad(DE.getFullYear())}`;
    this.SetTimeStart = `${this.zeroPad(TS.getHours())}/${this.zeroPad(
      TS.getMinutes()
    )}/${this.zeroPad(TS.getSeconds())}`;
    this.SetTimeEnd = `${this.zeroPad(TE.getHours())}/${this.zeroPad(
      TE.getMinutes()
    )}/${this.zeroPad(TE.getSeconds())}`;

    mqttSend('@msg/SetDayStart', this.SetDayStart);
    mqttSend('@msg/SetDayEnd', this.SetDayEnd);
    mqttSend('@msg/SetTimeStart', this.SetTimeStart);
    mqttSend('@msg/SetTimeEnd', this.SetTimeEnd);

    console.log('SetDayStart : ' + this.SetDayStart);
    console.log('SetDayEnd : ' + this.SetDayEnd);
    console.log('SetTimeStart : ' + this.SetTimeStart);
    console.log('SetTimeEnd : ' + this.SetTimeEnd);
  }
  submit() {
    console.log(this.DateStart);
    console.log(this.DateFinish);
    console.log(this.TimeStart);
    console.log(this.TimeFinish);
  }
  TimeFinish(TimeFinish: any) {
    throw new Error('Method not implemented.');
  }
  DateStart(DateStart: any) {
    throw new Error('Method not implemented.');
  }
  DateFinish(DateFinish: any) {
    throw new Error('Method not implemented.');
  }
  TimeStart(TimeStart: any) {
    throw new Error('Method not implemented.');
  }

  ngOnInit() {}
}
