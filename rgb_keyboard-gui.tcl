#!/usr/bin/wish

# This is a simple frontend for rgb_keyboard, not all options from the
# cli are implemented
# GPLv3 or later

# general window setup
wm title . "rgb_keyboard GUI"

# setting variables
set keymap_file ""
set custom_file ""
set led_pattern "fixed"
set led_direction "left"
set led_color "#ffffff"
set led_multi 0
set led_brightness 9
set led_speed 0
set profile_active 1
set profile_target 1

# main frame
frame .fr
pack .fr -fill both -expand 1

# led settings
frame .fr.led -borderwidth 1 -relief groove
pack .fr.led -fill both -padx 5 -pady 5
frame .fr.led.top
frame .fr.led.bottom
pack .fr.led.top .fr.led.bottom -expand 1 -fill both

label .fr.led.top.label -text "LED settings"
tk_optionMenu .fr.led.top.pattern led_pattern fixed sine rain waterfall vortex \
swirl diagonal-wave breathing breathing-color reactive-ripple reactive-single \
reactive-horizontal horizontal-wave vertical-wave pulse hurricane ripple \
reactive-color custom off
button .fr.led.top.file -text "Open custom pattern file" -command { set custom_file [tk_getOpenFile] }
button .fr.led.top.color -text "Select color" -command { set led_color [tk_chooseColor] }
checkbutton .fr.led.top.multicolor -text "Multicolor" -variable led_multi
button .fr.led.top.apply -text "Apply" -command { applyLed }

pack .fr.led.top.label .fr.led.top.pattern .fr.led.top.file .fr.led.top.color .fr.led.top.multicolor -padx 5 -pady 5 -side left
pack .fr.led.top.apply -padx 5 -pady 5 -side right

tk_optionMenu .fr.led.bottom.direction led_direction left right
label .fr.led.bottom.label_brightness -text "Brightness"
spinbox .fr.led.bottom.brightness -from 0 -to 9 -textvariable led_brightness
label .fr.led.bottom.label_speed -text "Speed"
spinbox .fr.led.bottom.speed -from 0 -to 3 -textvariable led_speed

pack .fr.led.bottom.direction .fr.led.bottom.label_brightness .fr.led.bottom.brightness .fr.led.bottom.label_speed .fr.led.bottom.speed -padx 5 -pady 5 -side left

# keymap settings
#
# this part is disabled for now, as remapping the keys is potentially
# dangerous and requires user confirmation on the commandline
#
# frame .fr.keymap -borderwidth 1 -relief groove
# pack .fr.keymap -fill both -padx 5 -pady 5
# label .fr.keymap.label -text "Keymap settings"
# button .fr.keymap.file -text "Open Keymap file" -command { set keymap_file [tk_getOpenFile] }
# button .fr.keymap.apply -text "Apply" -command { applyKeymap }
# pack .fr.keymap.label .fr.keymap.file -padx 5 -pady 5 -side left
# pack .fr.keymap.apply -padx 5 -pady 5 -side right

# profile settings
frame .fr.profile -borderwidth 1 -relief groove
pack .fr.profile -fill both -padx 5 -pady 5
label .fr.profile.label -text "Profile settings"
label .fr.profile.label_active -text "Active profile"
spinbox .fr.profile.active -from 1 -to 3 -textvariable profile_active
label .fr.profile.label_target -text "Apply settings to profile"
spinbox .fr.profile.target -from 1 -to 3 -textvariable profile_target
button .fr.profile.apply -text "Apply" -command { applyProfile }

pack .fr.profile.label .fr.profile.label_active .fr.profile.active .fr.profile.label_target .fr.profile.target -padx 5 -pady 5 -side left
pack .fr.profile.apply -padx 5 -pady 5 -side right

# padding frame
frame .fr.pad
pack .fr.pad -expand 1 -fill both -padx 5 -pady 5

# bottom buttons
button .fr.exit -text "Exit" -command { exit }
pack .fr.exit -padx 5 -pady 5 -side right
button .fr.apply -text "Apply all" -command { applyAll }
pack .fr.apply -padx 5 -pady 5 -side right
button .fr.about -text "About" -command { tk_messageBox -message "rgb_keyboard GUI" -detail "Use cli for more options\nGPLv3 or later" -type ok }
pack .fr.about -padx 5 -pady 5 -side left

# pocedures for applying the settings
proc checkInstall {} {
	return [exec rgb_keyboard -h]
}

proc applyKeymap {} {
	
	global keymap_file
	global profile_target
	
	if { [checkInstall] == 0 } {
		return
	}
	
	if { $keymap_file != "" } {
		puts "rgb_keyboard --keymap $keymap_file --profile $profile_target"
		exec rgb_keyboard --keymap $keymap_file --profile $profile_target
	}
	
}

proc applyLed {} {
	
	global custom_file
	global led_pattern
	global led_direction
	global led_color
	global led_multi
	global led_brightness
	global led_speed
	global profile_target
	
	if { [checkInstall] == 0 } {
		return
	}
	
	# turn #rrggbb to rrggbb
	set led_color_hex [string range $led_color 1 6]
	
	if { $led_multi == 0 } {
		puts "rgb_keyboard --brightness $led_brightness --leds $led_pattern --color $led_color_hex --speed $led_speed --direction $led_direction --profile $profile_target"
		exec rgb_keyboard --brightness $led_brightness --leds $led_pattern --color $led_color_hex --speed $led_speed --direction $led_direction --profile $profile_target
	} else {
		puts "rgb_keyboard --brightness $led_brightness --leds $led_pattern --color multi --speed $led_speed --direction $led_direction --profile $profile_target"
		exec rgb_keyboard --brightness $led_brightness --leds $led_pattern --color multi --speed $led_speed --direction $led_direction --profile $profile_target
	}
	
	if { $custom_file != "" } {
		puts "rgb_keyboard --custom-pattern $custom_file --profile $profile_target"
		exec rgb_keyboard --custom-pattern $custom_file --profile $profile_target
	}
	
}

proc applyProfile {} {
	
	global profile_active
	
	if { [checkInstall] == 0 } {
		return
	}
	
	puts "rgb_keyboard --active $profile_active"
	exec rgb_keyboard --active $profile_active
	
}

proc applyAll {} {
	
	applyLed
	applyKeymap
	applyProfile
	
}
