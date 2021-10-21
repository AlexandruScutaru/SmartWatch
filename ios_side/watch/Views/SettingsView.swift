//
//  SettingsView.swift
//  watch
//
//  Created by Alex Scutaru on 10/21/21.
//

import SwiftUI

struct SettingsView: View {
    var body: some View {
        VStack(alignment: .center, spacing: 10) {
            Toggle(isOn: /*@PLACEHOLDER=Is On@*/.constant(true)) {
                Text("Some setting")
            }
            Toggle(isOn: /*@PLACEHOLDER=Is On@*/.constant(true)) {
                Text("Some other setting")
            }
            Text("Intensity").multilineTextAlignment(.leading)
            Slider(value: .constant(10))
            DatePicker(selection: .constant(Date())/*@END_MENU_TOKEN@*/, label: { /*@START_MENU_TOKEN@*/Text("Date") })
        }
    }
}

struct SettingsView_Previews: PreviewProvider {
    static var previews: some View {
        SettingsView()
    }
}
