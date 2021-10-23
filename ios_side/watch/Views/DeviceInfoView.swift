//
//  DeviceInfoView.swift
//  watch
//
//  Created by Alex Scutaru on 10/22/21.
//

import SwiftUI

struct DetailEntryView: View {
    var name: String
    var value: String
    var rowWidth: CGFloat

    var body: some View {
        HStack(spacing: 0) {
            Text(name + ":").frame(width: 0.3 * rowWidth, alignment: .trailing)
            Spacer().frame(width: 0.05 * rowWidth)
            Text(value).frame(width: 0.65 * rowWidth, alignment: .leading)
        }
        .padding(.vertical, 3.0)
    }
}

struct DeviceInfoView: View {
    @ObservedObject var deviceVM: DeviceVM

    var body: some View {
        GeometryReader { metrics in
            VStack(spacing: 0) {
                DetailEntryView(name: "Name", value: deviceVM.deviceInfo.name, rowWidth: metrics.size.width)
                DetailEntryView(name: "Battery", value: String(deviceVM.deviceInfo.batteryLevel), rowWidth: metrics.size.width)
                DetailEntryView(name: "BT Mac", value: deviceVM.deviceInfo.btMac, rowWidth: metrics.size.width)
                DetailEntryView(name: "Wifi status", value: String(deviceVM.deviceInfo.wifiStatus), rowWidth: metrics.size.width)
                DetailEntryView(name: "Wifi SSID", value: deviceVM.deviceInfo.wifiSSID, rowWidth: metrics.size.width)
                HStack(spacing: 10) {
                    Button(action: {
                        deviceVM.setMotorState(state: true)
                    }) {
                        Text("Motor on").padding(5).foregroundColor(/*@START_MENU_TOKEN@*/.green/*@END_MENU_TOKEN@*/)
                    }

                    Button(action: {
                        deviceVM.setMotorState(state: false)
                    }) {
                        Text("Motor off").padding(5).foregroundColor(/*@START_MENU_TOKEN@*/.green/*@END_MENU_TOKEN@*/)
                    }
                }
                .padding(.top)
                Divider()
            }
        }
    }
}

struct DeviceInfoView_Previews: PreviewProvider {
    static var previews: some View {
        DeviceInfoView(deviceVM: DeviceVM())
    }
}
