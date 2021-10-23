//
//  BleManager.swift
//  watch
//
//  Created by Alex Scutaru on 10/23/21.
//

import Foundation
import CoreBluetooth

class BleManager: NSObject {
    private var centralManager: CBCentralManager!
    private var mBlePeripheral = BlePeripheral()
    private var mRssi = NSNumber()

    override init() {
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }

    func writeCharacteristic(value: String) {
        let valueString = (value as NSString).data(using: String.Encoding.utf8.rawValue)
        if let blePeripheral = mBlePeripheral.peripheral {
            if let characteristic = mBlePeripheral.characteristicNotification {
                  blePeripheral.writeValue(valueString!, for: characteristic, type: CBCharacteristicWriteType.withResponse)
            }
        }
    }

    func getAllData() {
        mBlePeripheral.peripheral!.readValue(for: mBlePeripheral.characteristicBattery!)
        mBlePeripheral.peripheral!.readValue(for: mBlePeripheral.characteristicBtMac!)
        mBlePeripheral.peripheral!.readValue(for: mBlePeripheral.characteristicWifiStatus!)
        mBlePeripheral.peripheral!.readValue(for: mBlePeripheral.characteristicWifiSSID!)
    }

    func connect(device: CBUUID) {
        print(#function)
        scan()
    }

    func disconnect() {
        centralManager!.cancelPeripheralConnection(mBlePeripheral.peripheral!)
    }

    func onConnected() -> Void {
        NotificationCenter.default.post(name: .deviceConnected, object: nil)
    }

    func connectToDevice() -> Void {
        centralManager?.connect(mBlePeripheral.peripheral!, options: nil)
    }

    func disconnectFromDevice() -> Void {
        if mBlePeripheral.peripheral != nil {
            centralManager?.cancelPeripheralConnection(mBlePeripheral.peripheral!)
        }
    }

    func scan() {
        print(#function)
        centralManager?.scanForPeripherals(withServices: [BleUUIDs.ServiceUUID])

        Timer.scheduledTimer(withTimeInterval: 5, repeats: false) {_ in
            print("scan timeout")
            self.centralManager?.stopScan()
            NotificationCenter.default.post(name: .scanTimeout, object: nil)
        }
    }
}

extension BleManager: CBCentralManagerDelegate {
    //check
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
            case .poweredOff:
                print("Powered Off")
            case .poweredOn:
                print("Powered On")
            case .unsupported:
                print("Unsupported")
            case .unauthorized:
                print("Unauthorized")
            case .unknown:
                print("Unknown")
            case .resetting:
                print("Resetting")
            @unknown default:
                print("Error")
        }
    }

    //discover
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        print(#function)
        mBlePeripheral.peripheral = peripheral
        mRssi = RSSI
        mBlePeripheral.peripheral!.delegate = self
        print("Peripheral Discovered: \(mBlePeripheral.peripheral!)")

        let valueDict: [String: String] = ["value": mBlePeripheral.peripheral!.name!]
        NotificationCenter.default.post(name: .deviceNameRead, object: nil, userInfo: valueDict)

        connectToDevice()
    }

    //connect
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        self.centralManager?.stopScan()
        mBlePeripheral.peripheral!.discoverServices([BleUUIDs.ServiceUUID])
    }
}

extension BleManager: CBPeripheralDelegate {
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else {
            return
        }

        for service in services {
            peripheral.discoverCharacteristics(nil, for: service)
        }
        mBlePeripheral.service = services[0]
    }

    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else {
            return
        }

        print("Found \(characteristics.count) characteristics.")

        for characteristic in characteristics {
            if characteristic.uuid.isEqual(BleUUIDs.BatteryCharacteristicUUID) {
                mBlePeripheral.characteristicBattery = characteristic
                peripheral.setNotifyValue(true, for: mBlePeripheral.characteristicBattery!)
                peripheral.readValue(for: mBlePeripheral.characteristicBattery!)
                print("Battery Characteristic: \(mBlePeripheral.characteristicBattery!.uuid)")
            } else if characteristic.uuid.isEqual(BleUUIDs.BtMacCharacteristicUUID) {
                mBlePeripheral.characteristicBtMac = characteristic
                peripheral.setNotifyValue(true, for: mBlePeripheral.characteristicBtMac!)
                peripheral.readValue(for: mBlePeripheral.characteristicBtMac!)
                print("BT MAC Characteristic: \(mBlePeripheral.characteristicBtMac!.uuid)")
            } else if characteristic.uuid.isEqual(BleUUIDs.WifiStatusCharacteristicUUID) {
                mBlePeripheral.characteristicWifiStatus = characteristic
                peripheral.setNotifyValue(true, for: mBlePeripheral.characteristicWifiStatus!)
                peripheral.readValue(for: mBlePeripheral.characteristicWifiStatus!)
                print("WIFI Status Characteristic: \(mBlePeripheral.characteristicWifiStatus!.uuid)")
            } else if characteristic.uuid.isEqual(BleUUIDs.WifiSsidCharacteristicUUID) {
                mBlePeripheral.characteristicWifiSSID = characteristic
                peripheral.setNotifyValue(true, for: mBlePeripheral.characteristicWifiSSID!)
                peripheral.readValue(for: mBlePeripheral.characteristicWifiSSID!)
                print("WIFI SSID Characteristic: \(mBlePeripheral.characteristicWifiSSID!.uuid)")
            } else if characteristic.uuid.isEqual(BleUUIDs.NotificationCharacteristicUUID) {
                mBlePeripheral.characteristicNotification = characteristic
                print("Notification Characteristic: \(mBlePeripheral.characteristicNotification!.uuid)")
            }
        }
        onConnected()
    }

    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        guard
            let characteristicValue = characteristic.value,
            let characteristicASCIIValue = NSString(data: characteristicValue, encoding: String.Encoding.utf8.rawValue)
        else {
            return
        }
        let characteristicValueDict: [String: String] = ["value": characteristicASCIIValue as String]

        if characteristic == mBlePeripheral.characteristicBattery {
            NotificationCenter.default.post(name: .batteryLevelRead, object: nil, userInfo: characteristicValueDict)
        } else if characteristic == mBlePeripheral.characteristicBtMac {
            NotificationCenter.default.post(name: .btMacRead, object: nil, userInfo: characteristicValueDict)
        } else if characteristic == mBlePeripheral.characteristicWifiStatus {
            NotificationCenter.default.post(name: .wifiStatusRead, object: nil, userInfo: characteristicValueDict)
        } else if characteristic == mBlePeripheral.characteristicWifiSSID {
            NotificationCenter.default.post(name: .wifiSsidRead, object: nil, userInfo: characteristicValueDict)
        }

        print("Value Recieved: \((characteristicASCIIValue as String))")
    }

    func peripheral(_ peripheral: CBPeripheral, didReadRSSI RSSI: NSNumber, error: Error?) {
        peripheral.readRSSI()
    }

    func peripheral(_ peripheral: CBPeripheral, didWriteValueFor characteristic: CBCharacteristic, error: Error?) {
        guard error == nil else {
            print("Error discovering services: error")
            return
        }
        print(#function)
        print("Message sent")
    }

    func peripheral(_ peripheral: CBPeripheral, didUpdateNotificationStateFor characteristic: CBCharacteristic, error: Error?) {
        print(#function)
        if (error != nil) {
            print("Error changing notification state:\(String(describing: error?.localizedDescription))")
        } else {
            print("Characteristic's value subscribed")
        }

        if (characteristic.isNotifying) {
            print ("Subscribed. Notification has begun for: \(characteristic.uuid)")
        }
    }
}
