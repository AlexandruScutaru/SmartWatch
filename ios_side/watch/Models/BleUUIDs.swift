//
//  BleUUIDs.swift
//  watch
//
//  Created by Alex Scutaru on 10/23/21.
//

import Foundation
import CoreBluetooth

struct BleUUIDs{
    static let ServiceUUID = CBUUID(string: "00000001-0000-1000-8000-00805f9b34fb")
    static let BatteryCharacteristicUUID = CBUUID(string: "00000002-0000-1000-8000-00805f9b34fb")
    static let BtMacCharacteristicUUID = CBUUID(string: "00000003-0000-1000-8000-00805f9b34fb")
    static let WifiStatusCharacteristicUUID = CBUUID(string: "00000004-0000-1000-8000-00805f9b34fb")
    static let WifiSsidCharacteristicUUID = CBUUID(string: "00000005-0000-1000-8000-00805f9b34fb")
    static let NotificationCharacteristicUUID = CBUUID(string: "00000006-0000-1000-8000-00805f9b34fb")

    static let MaxCharacters = 20
}
