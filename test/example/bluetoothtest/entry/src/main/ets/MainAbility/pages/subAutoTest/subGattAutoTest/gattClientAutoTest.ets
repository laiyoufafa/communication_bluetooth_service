/**
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// @ts-nocheck
import ConfigData from '../../../../Utils/ConfigData';
import router from '@system.router';
import { TestData } from '../../../model/testData'
import { PageTitle } from '../../../../Component/pageTitle';
import { TestImageDisplay } from '../../../../Component/testImageDisplay';
import { AutoContentTable } from '../../../../Component/autoContentTable';
import { GattClientAutoTestCase , initGattClientAutoData } from '../../../model/autoTestDataModels';
import * as GattClientInterface from '../../../model/gattClientInterface';
import prompt from '@system.prompt';

/**
 *  GattClientAutoTest Page Of Bluetooth test
 */
@Entry
@Component
struct GattClientAutoTest {
  @State message: string = 'GattClientAutoTest';
//  @State textMessage: string = 'null';
  @State testMessage: string = "";
  @State changeIndex:number = -1
  private testItem: TestData = router.getParams().testId;
  @StorageLink ("gattClientAutoTestMessage") gattClientAutoTestMessage:string =""
  aboutToAppear(){
    AppStorage.SetOrCreate('peripheralDeviceId', '00:1A:7D:DA:71:15');
    AppStorage.SetOrCreate('serviceUUID', '00001801-0000-1000-8000-00805f9b34fb');
    AppStorage.SetOrCreate('characteristicUUID', '00002b29-0000-1000-8000-00805f9b34fb');
    AppStorage.SetOrCreate('characteristicValue', '00002b29-0000-1000-8000-00805f9b34fb');
    AppStorage.SetOrCreate('descriptorUUID', '00002902-0000-1000-8000-00805f9b34fb');
    AppStorage.SetOrCreate('descriptorValue', '00002902-0000-1000-8000-00805f9b34fb');
  }
  build() {
    Column() {
      Stack({ alignContent: Alignment.TopStart }) {
        TestImageDisplay({ testItem: this.testItem })
        PageTitle({ testItem: this.testItem })
      }
      Stack().height("1vp").backgroundColor("#000000");
      Column() {
        Scroll() {
          Column() {
            Text("API验证:")
              .fontSize("17vp")
              .margin({ top: "10vp", bottom:"10vp",left: "15vp"})
              .textAlign(TextAlign.Start)
              .width("100%")
            AutoContentTable({
              testItem: this.testItem,
              autoItems: initGattClientAutoData(),
              testMessage: this.testMessage,
              changeIndex:this.changeIndex
            })
          }
          .width("100%")
          .height(260)
        }
        .scrollBarWidth(10)
        .scrollBar(BarState.Auto)

        Stack().height("1vp").backgroundColor("#000000");

        Scroll() {
          Column() {
            Text("Debug日志:")
              .fontSize("17vp")
              .margin({ top: "8vp", bottom: "8vp", left: "15vp"})
              .textAlign(TextAlign.Start)
              .width("100%")
            List(){
              ListItem(){
                Text("log:" + "\n"  + this.gattClientAutoTestMessage)
                  .fontSize("17vp")
                  .margin({ top: "5vp", left: "30vp", right: "10vp" })
                  .textAlign(TextAlign.Start)
                  .width("90%")
              }
            }
            .height("80%")
            .width("90%")
            .backgroundColor($r("sys.color.ohos_id_color_foreground_contrary"))
          }
          .width("100%")
          .height(280)
        }
        .scrollBarWidth(10)
        .scrollBar(BarState.Auto)
      }
      .height(500)
      .width("100%")
      .backgroundColor($r("sys.color.ohos_id_color_sub_background"))


      Stack().height("1vp").backgroundColor("#000000");
      Column() {
        Button({ type: ButtonType.Normal, stateEffect: true }) {
          Row() {
            Text('自动测试').fontSize("24vp").fontColor(0xffffff).margin({ left: 5, right: 5 })
          }.alignItems(VerticalAlign.Center)
        }
        .borderRadius(8)
        .backgroundColor($r("app.color.blue"))
        .width(180)
        .height(50)
        .margin({ top: "15vp"})
        .onClick(async(event: ClickEvent) => {
          let self = this
          let gattClientAutoTestMessage =""

          //拼装数组
          var gattClientAutoArray=[{name:"testSetLocalName",para:["DaYuBlue"]},
                 {name:"testSetBluetoothScanMode",para:[4,0]}]
          let Interface = GattClientAutoTestCase.map(i=>{
            let para = gattClientAutoArray.some(itm=>itm.name===i.api.name)?gattClientAutoArray.find(itm=>itm.name===i.api.name).para:[]
            return {name:i.api.name,para}
          })

          //循环调用
          async function forLoop() {
            for (let m=0 ; m<Interface.length ; m++){
              gattClientAutoTestMessage += GattClientAutoTestCase[m]["api"](...Interface[m].para) + "\n"
              self.changeIndex=m
              await sleep(1)
              AppStorage.SetOrCreate("gattClientAutoTestMessage", gattClientAutoTestMessage)
            }
          }
          forLoop()

          let msg = ""
          msg = "测试"
          console.log(msg)
          prompt.showToast({ message: msg })
        })
      }
      .backgroundColor($r("sys.color.ohos_id_color_sub_background"))
      .width(ConfigData.WH_100_100)
      .height(ConfigData.WH_100_100);
    }
  }
}

function sleep(time) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve()
    }, time * 1000)
  })
}