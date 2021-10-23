//
//  DeviceVM.swift
//  watch
//
//  Created by Alex Scutaru on 10/22/21.
//

import Foundation

extension String {
    var boolValue: Bool {
        return (self as NSString).boolValue
    }

    var integerValue: Int {
        return (self as NSString).integerValue
    }
}

public extension Notification.Name {
    static var deviceConnected = Notification.Name("deviceConnected")
    static var scanTimeout = Notification.Name("scanTimeout")

    static var deviceNameRead = Notification.Name("deviceNameRead")
    static var batteryLevelRead = Notification.Name("batteryLevelRead")
    static var btMacRead = Notification.Name("btMacRead")
    static var wifiStatusRead = Notification.Name("wifiStatusRead")
    static var wifiSsidRead = Notification.Name("wifiSsidRead")
}

class DeviceVM: ObservableObject {
    private var mBleManager: BleManager!

    @Published var deviceInfo: DeviceInfoModel = DeviceInfoModel()
    @Published var mDeviceConnected: Bool = false
    @Published var mDeviceConnecting: Bool = false

    init() {
        mBleManager = BleManager()
        NotificationCenter.default.addObserver(self, selector: #selector(onDeviceConnected(_:)), name: .deviceConnected, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onScanTimeout(_:)), name: .scanTimeout, object: nil)

        NotificationCenter.default.addObserver(self, selector: #selector(onDeviceNameRead(_:)), name: .deviceNameRead, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onBatteryLevelRead(_:)), name: .batteryLevelRead, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onBtMacRead(_:)), name: .btMacRead, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onWifiStatusRead(_:)), name: .wifiStatusRead, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onWifiSsidRead(_:)), name: .wifiSsidRead, object: nil)
        //mBleManager = BleManager()
    }

    func connect() {
        mDeviceConnecting = true
        mBleManager.connect(device: BleUUIDs.ServiceUUID)
    }

    func disconnect() {
        mBleManager.disconnect()
        mDeviceConnected = false
        mDeviceConnecting = false
    }

    func isDeviceConnected() -> Bool {
        return mDeviceConnected
    }

    func isDeviceConnecting() -> Bool {
        return mDeviceConnecting
    }

    func setMotorState(state: Bool) {
        if mDeviceConnected {
            let value = state ? "1" : "0"
            mBleManager.writeCharacteristic(value: value)
        }
    }

    @objc private func onDeviceConnected(_ notification: Notification) {
        self.mDeviceConnected = true
        self.mDeviceConnecting = false
        mBleManager.getAllData()
    }

    @objc private func onScanTimeout(_ notification: Notification) {
        //maybe will create some state type thingy and update the ui accordingly, not with ifs...
        mDeviceConnecting = false
    }

    //characteristics read events
    @objc private func onDeviceNameRead(_ notification: Notification) {
        print(#function)
        if let value = notification.userInfo?["value"] as? String {
            print(value)
            deviceInfo.name = value
        }
    }

    @objc private func onBatteryLevelRead(_ notification: Notification) {
        print(#function)
        if let value = notification.userInfo?["value"] as? String {
            print(value)
            deviceInfo.batteryLevel = value.integerValue
        }
    }

    @objc private func onBtMacRead(_ notification: Notification) {
        print(#function)
        if let value = notification.userInfo?["value"] as? String {
            print(value)
            deviceInfo.btMac = value
        }
    }

    @objc private func onWifiStatusRead(_ notification: Notification) {
        print(#function)
        if let value = notification.userInfo?["value"] as? String {
            print(value)
            deviceInfo.wifiStatus = value.boolValue
        }
    }

    @objc private func onWifiSsidRead(_ notification: Notification) {
        print(#function)
        if let value = notification.userInfo?["value"] as? String {
            print(value)
            deviceInfo.wifiSSID = value
        }
    }
}
