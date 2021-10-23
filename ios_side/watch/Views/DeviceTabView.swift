//
//  DeviceView.swift
//  watch
//
//  Created by Alex Scutaru on 10/21/21.
//

import SwiftUI

struct DeviceTabView: View {
    @StateObject private var deviceVM = DeviceVM()
    //@State private var isLoading: Bool = false

    var body: some View {
        VStack(alignment: .center, spacing: 20) {
            Image("watch_illustration")
                .resizable()
                .aspectRatio(contentMode: .fit)
                .padding(.top)
                .frame(width: 200)

            if (deviceVM.isDeviceConnected()) {
                DeviceInfoView(deviceVM: deviceVM)
                Spacer()
                Button(action: {
                    deviceVM.disconnect()
                }) {
                    Text("Disconnect").padding(5).foregroundColor(/*@START_MENU_TOKEN@*/.green/*@END_MENU_TOKEN@*/)
                }
                .padding(.bottom)
            } else {
                if (deviceVM.isDeviceConnecting()) {
                    ProgressView("Pairing...")
                } else {
                    Button(action: {
                        deviceVM.connect()
                    }) {
                        Text("Pair with device").padding(5).foregroundColor(/*@START_MENU_TOKEN@*/.green/*@END_MENU_TOKEN@*/)
                    }
                }
                Spacer();
            }
        }
    }
}

struct DeviceView_Previews: PreviewProvider {
    static var previews: some View {
        DeviceTabView()
    }
}
