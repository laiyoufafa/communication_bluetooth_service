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

import ConfigData from '../../../Utils/ConfigData';
import router from '@system.router';
import { TestData } from '../../../MainAbility/model/testData'
import { PageTitle } from '../../../Component/pageTitle';
import { TestImageDisplay } from '../../../Component/testImageDisplay';
import { AutoContentTable } from '../../../Component/autoContentTable';
import {
  GattServerManagerAutoTestCase ,
  initGattServerManagerAutoData
} from '../../../MainAbility/model/autoTestDataModelsManager';
import * as GattServerManagerInterface from '../../../MainAbility/model/gattServerManagerInterface';
import prompt from '@system.prompt';

/**
 *  GattServerAutoTest Manager Page Of Bluetooth test
 */

@Entry
@Component
struct GattServerAutoTestManager {
  @State message: string = 'GattServerAutoTestManager';
  //  @State textMessage: string = 'null';
  @State testMessage: string = "";
  @State changeIndex: number = - 1
  private testItem: TestData = router.getParams().testId;
  @StorageLink( "gattServerAutoTestMessage" ) gattServerAutoTestMessage: string = ""

  aboutToAppear() {
    AppStorage.SetOrCreate( 'txtScanFilterDeviceId' , "6c:96:d7:3d:87:6f" );
    AppStorage.SetOrCreate( 'txtScanFilterName' , "dudu-tiger" );
    AppStorage.SetOrCreate( 'txtScanFilterServiceUuid' , "0000180A-0000-1000-8000-00805f9b34fb" );
    AppStorage.SetOrCreate( 'txtScanOptions_interval' , "0" );
    AppStorage.SetOrCreate( 'txtScanOptionsDutyMode' , '0' );
    AppStorage.SetOrCreate( 'txtScanOptionsMatchMode' , '0' );
    AppStorage.SetOrCreate( 'cbxBleScanFilter' , true );
    AppStorage.SetOrCreate( 'cbxBleScanOptions' , true );

    AppStorage.SetOrCreate( 'curServiceUUID' , '00001877-0000-1000-8000-00805F9B34FB' );
    AppStorage.SetOrCreate( 'curCharacteristicUUID' , '00002BE0-0000-1000-8000-00805F9B34FB' );
    AppStorage.SetOrCreate( 'curDescriptorUUID' , '00002902-0000-1000-8000-00805F9B34FB' );
    AppStorage.SetOrCreate( 'curDescriptorValue' , 'Descriptor' );
    AppStorage.SetOrCreate( 'curCharacteristicValue' , 'DaYuBlue' );
    AppStorage.SetOrCreate( 'isPrimary' , true );
    AppStorage.SetOrCreate( 'advSettings_interval' , "1600" );
    AppStorage.SetOrCreate( 'advSettings_txPower' , "-7" );
    AppStorage.SetOrCreate( 'advSettings_connectable' , true );
    AppStorage.SetOrCreate( 'advDataServiceUuids_serviceUuid' , "000054F6-0000-1000-8000-00805f9b34fb" );
    AppStorage.SetOrCreate( 'advDataManufactureData_manufactureId' , "7456" );
    AppStorage.SetOrCreate( 'advDataManufactureData_manufactureValue' , "CHN" );
    AppStorage.SetOrCreate( 'advDataServiceData_serviceUuid' , "000054F6-0000-1000-8000-00805f9b34fb" );
    AppStorage.SetOrCreate( 'advDataServiceData_serviceValue' , "AdvValue" );
    AppStorage.SetOrCreate( 'advResponseServiceUuids_serviceUuid' , "000054F6-0000-1000-8000-00805f9b34fb" );
    AppStorage.SetOrCreate( 'advResponseManufactureData_manufactureId' , "6547" );
    AppStorage.SetOrCreate( 'advResponseManufactureData_manufactureValue' , "CHN" );
    AppStorage.SetOrCreate( 'advResponseServiceData_serviceUuid' , "000054F6-0000-1000-8000-00805f9b34fb" );
    AppStorage.SetOrCreate( 'advResponseServiceData_serviceValue' , "AdvValue" );
    AppStorage.SetOrCreate( 'cbxAdvSettings' , true );
    AppStorage.SetOrCreate( 'cbxInterval' , true );
    AppStorage.SetOrCreate( 'cbxTxPower' , true );
    AppStorage.SetOrCreate( 'cbxAdvResponse' , true );
  }

  build() {
    Column() {
      Stack( { alignContent : Alignment.TopStart } ) {
        TestImageDisplay( { testItem : this.testItem } )
        PageTitle( { testItem : this.testItem } )
      }

      Stack().height( "1vp" ).backgroundColor( "#000000" );
      Column() {
        Scroll() {
          Column() {
            Text( "API验证:" )
              .fontSize( "17vp" )
              .margin( { top : "10vp" , bottom : "10vp" , left : "15vp" } )
              .textAlign( TextAlign.Start )
              .width( "100%" )
            AutoContentTable( {
              testItem : this.testItem ,
              autoItems : initGattServerManagerAutoData() ,
              testMessage : this.testMessage ,
              changeIndex : this.changeIndex
            } )
          }
          .width( "100%" )
          .height( 280 )
        }
        .scrollBarWidth( 10 )
        .scrollBar( BarState.Auto )

        Stack().height( "1vp" ).backgroundColor( "#000000" );

        Scroll() {
          Column() {
            Text( "Debug日志:" )
              .fontSize( "17vp" )
              .margin( { top : "8vp" , bottom : "8vp" , left : "15vp" } )
              .textAlign( TextAlign.Start )
              .width( "100%" )
            List() {
              ListItem() {
                Text( "log:" + "\n" + this.gattServerAutoTestMessage )
                  .fontSize( "17vp" )
                  .margin( { top : "5vp" , left : "30vp" , right : "10vp" } )
                  .textAlign( TextAlign.Start )
                  .width( "90%" )
              }
            }
            .height( "80%" )
            .width( "90%" )
            .backgroundColor( $r( "sys.color.ohos_id_color_foreground_contrary" ) )
          }
          .width( "100%" )
          .height( 260 )
        }
        .scrollBarWidth( 10 )
        .scrollBar( BarState.Auto )
      }
      .height( 500 )
      .width( "100%" )
      .backgroundColor( $r( "sys.color.ohos_id_color_sub_background" ) )


      Stack().height( "1vp" ).backgroundColor( "#000000" );
      Column() {
        Button( { type : ButtonType.Normal , stateEffect : true } ) {
          Row() {
            Text( '自动测试' ).fontSize( "24vp" ).fontColor( 0xffffff ).margin( { left : 5 , right : 5 } )
          }.alignItems( VerticalAlign.Center )
        }
        .borderRadius( 8 )
        .backgroundColor( $r( "app.color.blue" ) )
        .width( 180 )
        .height( 50 )
        .margin( { top : "15vp" } )
        .onClick( async( event: ClickEvent ) => {
          let self = this
          let gattServerAutoTestMessage = ""

          //拼装数组
          var gattServerAutoArray = [ { name : "testSetLocalNameManager" , para : [ "DaYuBlue" ] },
                                      { name : "testSetBluetoothScanModeManager" , para : [ 4, 0 ] } ]
          let Interface = GattServerManagerAutoTestCase.map( i => {
            let para = gattServerAutoArray.some( itm => itm.name === i.api.name ) ? gattServerAutoArray.find( itm => itm.name === i.api.name ).para : []
            return { name : i.api.name , para }
          } )

          //循环调用
          async function forLoop() {
            for ( let m = 0 ; m < Interface.length ; m ++ ) {
              gattServerAutoTestMessage += GattServerManagerAutoTestCase[m]["api"]( ... Interface[m].para ) + "\n"
              self.changeIndex = m
              await sleep( 1 )
              AppStorage.SetOrCreate( "gattServerAutoTestMessage" , gattServerAutoTestMessage )
            }
          }

          forLoop()

          let msg = ""
          msg = "测试"
          console.log( msg )
          prompt.showToast( { message : msg } )
        } )
      }
      .backgroundColor( $r( "sys.color.ohos_id_color_sub_background" ) )
      .width( ConfigData.WH_100_100 )
      .height( ConfigData.WH_100_100 );
    }
  }
}

function sleep( time ) {
  return new Promise(( resolve , reject ) => {
    setTimeout( () => {
      resolve()
    } , time * 1000 )
  })
}