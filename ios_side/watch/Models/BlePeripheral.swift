//
//  BlePeripheral.swift
//  watch
//
//  Created by Alex Scutaru on 10/23/21.
//

import Foundation
import CoreBluetooth

struct BlePeripheral {
    var peripheral: CBPeripheral?
    var service: CBService?
    var characteristicBattery: CBCharacteristic?
    var characteristicBtMac: CBCharacteristic?
    var characteristicWifiStatus: CBCharacteristic?
    var characteristicWifiSSID: CBCharacteristic?
    var characteristicNotification: CBCharacteristic?
}
