/*
 * datasheet.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: rosaycy
 */

#include "datasheet.hpp"

std::string getDataRef(int index){
	std::string res = "";
	switch (index){
	case AIRCRAFT_MODEL: return("sim/aircraft/view/acf_ICAO");
	case AIRCRAFT_INFO_TAIL_NUMBER : return("sim/aircraft/view/acf_tailnum");
	case AIRCRAFT_AIRSPEED_INDICATED: return("sim/flightmodel/position/indicated_airspeed");
	case AIRCRAFT_AIRSPEED_MACH : return("sim/flightmodel/misc/machno");
	case AIRCRAFT_AIRSPEED_ACCELERATION: return("sim/cockpit2/gauges/indicators/airspeed_acceleration_kts_sec_pilot");
	case AIRCRAFT_AIRSPEED_LIMITS_VYSE: return("sim/aircraft/overflow/acf_Vyse");
	case AIRCRAFT_AIRSPEED_LIMITS_VMCA : return("sim/aircraft/overflow/acf_Vmca");
	case AIRCRAFT_AIRSPEED_LIMITS_VS : return("sim/aircraft/view/acf_Vs");
	case AIRCRAFT_AIRSPEED_LIMITS_VS0: return("sim/aircraft/view/acf_Vso");
	case AIRCRAFT_AIRSPEED_LIMITS_VNO: return("sim/aircraft/view/acf_Vno");
	case AIRCRAFT_AIRSPEED_LIMITS_VNE: return("sim/aircraft/view/acf_Vne");
	case AIRCRAFT_AIRSPEED_LIMITS_VFE: return("sim/aircraft/view/acf_Vfe");
	case AIRCRAFT_AIRSPEED_LIMITS_VLE: return("sim/aircraft/overflow/acf_Vle");
	case AIRCRAFT_VERTICAL_VELOCITY : return("sim/flightmodel/position/vh_ind_fpm");
	case AIRCRAFT_AIRSPEED_TRUE: return("sim/flightmodel/position/true_airspeed");

	case AIRCRAFT_HEADING_MAG: return("sim/flightmodel/position/magpsi");
	case AIRCRAFT_HEADING_TRUE:return("sim/flightmodel/position/psi");
	case AIRCRAFT_GROUND_TRACK: return ("sim/flightmodel/position/hpath");
	case AIRCRAFT_GROUND_SPEED : return("sim/flightmodel/position/groundspeed");

	case AIRCRAFT_POSITION_LATITUDE : return("sim/flightmodel/position/latitude");
	case AIRCRAFT_POSITION_LONGITUDE : return("sim/flightmodel/position/longitude");
	case AIRCRAFT_ALTITUDE_RADIO1 : return ("sim/cockpit2/gauges/indicators/radio_altimeter_height_ft_pilot");
	case AIRCRAFT_RADALT_DECISION_HEIGHT : return ("sim/cockpit/misc/radio_altimeter_minimum");

	case AIRCRAFT_ATTITUTE_ROLL : return("sim/flightmodel/position/phi");
	case AIRCRAFT_ATTITUTE_PITCH : return("sim/flightmodel/position/theta");
	case AIRCRAFT_ATTITUDE_YAW : return( "sim/flightmodel/position/R");
	case AIRCRAFT_ATTITUTE_AHRS_FAILURE :return ("sim/operation/failures/rel_g_arthorz");
	case AIRCRAFT_ANGLE_OF_ATTACK : return("sim/flightmodel2/misc/AoA_angle_degrees");
	case AIRCRAFT_ATTITUTE_VFPA : return ("sim/flightmodel/position/vpath");
	case AIRCRAFT_ATTITUTE_HFPA :return ("sim/flightmodel/position/hpath");

	case AIRCRAFT_FORCES_G_VERTICAL : return ("sim/flightmodel/forces/g_nrml");
	case AIRCRAFT_FORCES_G_LONGITUDINAL : return ("sim/flightmodel/forces/g_axil");
	case AIRCRAFT_FORCES_G_LATERAL : return ("sim/flightmodel/forces/g_side");

	case AIRCRAFT_FD_PITCH : return("sim/cockpit2/autopilot/flight_director_pitch_deg");
	case AIRCRAFT_FD_ROLL : return("sim/cockpit2/autopilot/flight_director_roll_deg");
	case AIRCRAFT_AUTOPILOT_MODE : return("sim/cockpit/autopilot/autopilot_mode");
	case AIRCRAFT_AUTOPILOT_SELECTED_AIRSPEED : return("sim/cockpit2/autopilot/airspeed_dial_kts_mach");
	case AIRCRAFT_AUTOPILOT_SELECTED_VS: return("sim/cockpit/autopilot/vertical_velocity");
	case AIRCRAFT_AUTOPILOT_SELECTED_HEADING_TRUE: return("sim/cockpit/autopilot/heading");
	case AIRCRAFT_AUTOPILOT_SELECTED_HEADING_MAG_1: return("sim/cockpit/autopilot/heading_mag");
	case AIRCRAFT_AUTOPILOT_SELECTED_HEADING_MAG_2: return("sim/cockpit/autopilot/heading_mag_2");
	case AIRCRAFT_AUTOPILOT_SELECTED_ALTITUDE: return("sim/cockpit/autopilot/altitude");
	case AIRCRAFT_ALTITUDE_BARO: return("sim/flightmodel/misc/h_ind");
	case AIRCRAFT_AUTOPILOT_GS_STATUS : return("sim/cockpit2/autopilot/glideslope_status");
	case AIRCRAFT_AUTOPILOT_APP_STATUS : return("sim/cockpit2/autopilot/approach_status");
	case AIRCRAFT_AUTOPILOT_ALT_STATUS : return("sim/cockpit2/autopilot/altitude_hold_status");
	case AIRCRAFT_AUTOPILOT_SPEED_STATUS : return("sim/cockpit2/autopilot/speed_status");
	case AIRCRAFT_AUTOPILOT_SOURCE : return("sim/cockpit/radios/ap_src");
	case AIRCRAFT_AUTOPILOT_STATUS : return("sim/cockpit/autopilot/autopilot_state");
	case AIRCRAFT_AUTOTHROTTLE_ON : return("sim/cockpit2/autopilot/autothrottle_on");
	case AIRCRAFT_AUTOPILOT_ON : return("sim/cockpit2/autopilot/autopilot_on");
	case AIRCRAFT_AUTOPILOT_HDG_MODE : return("sim/cockpit2/autopilot/heading_mode");
	case AIRCRAFT_AUTOPILOT_ALT_MODE : return("sim/cockpit2/autopilot/altitude_mode");
	case AIRCRAFT_AUTOPILOT_APPROACH_STATUS : return ("sim/cockpit2/autopilot/approach_status");

	case AIRCRAFT_NAV1_GS_FLAGGED :	return("sim/cockpit2/radios/indicators/nav1_flag_glideslope");
	case AIRCRAFT_NAV2_GS_FLAGGED :	return("sim/cockpit2/radios/indicators/nav2_flag_glideslope");
	case AIRCRAFT_NAV1_LOC_FLAGGED :	return("sim/cockpit2/radios/indicators/nav1_display_horizontal");
	case AIRCRAFT_NAV2_LOC_FLAGGED :	return("sim/cockpit2/radios/indicators/nav2_display_horizontal");
	case AIRCRAFT_NAV1_TO_FROM : return("sim/cockpit/radios/nav1_fromto");
	case AIRCRAFT_COM1_FREQ : return ("sim/cockpit2/radios/actuators/com1_frequency_hz");
	case AIRCRAFT_COM2_FREQ : return ("sim/cockpit2/radios/actuators/com2_frequency_hz");
	case AIRCRAFT_NAV1_FREQ : return ("sim/cockpit2/radios/actuators/nav1_frequency_hz");
	case AIRCRAFT_NAV1_OBS : return("sim/cockpit/radios/nav1_obs_degm");
	case AIRCRAFT_NAV1_DME : return ("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");
	case AIRCRAFT_NAV1_IDENT : return ("sim/cockpit2/radios/indicators/nav1_nav_id");
	case AIRCRAFT_NAV1_VDEV : return("sim/cockpit/radios/nav1_vdef_dot");
	case AIRCRAFT_NAV1_HDEV : return("sim/cockpit/radios/nav1_hdef_dot");
	case AIRCRAFT_NAV2_FREQ : return ("sim/cockpit2/radios/actuators/nav2_frequency_hz");
	case AIRCRAFT_NAV2_OBS : return("sim/cockpit/radios/nav2_obs_degm");
	case AIRCRAFT_NAV2_DME : return ("sim/cockpit2/radios/indicators/nav2_dme_distance_nm");
	case AIRCRAFT_NAV2_IDENT : return ("sim/cockpit2/radios/indicators/nav2_nav_id");
	case AIRCRAFT_BARO_SETTING_1: return ("sim/cockpit/misc/barometer_setting");
	case AIRCRAFT_BARO_SETTING_2: return ("sim/cockpit/misc/barometer_setting2");
	case AIRCRAFT_ADF1_FREQ : return ("sim/cockpit2/radios/actuators/adf1_frequency_hz");
	case AIRCRAFT_ADF2_FREQ : return ("sim/cockpit2/radios/actuators/adf2_frequency_hz");
	case AIRCRAFT_AVIONICS_ON : return ("sim/cockpit2/switches/avionics_power_on");
	case AIRCRAFT_XPDR_CODE : return ("sim/cockpit2/radios/actuators/transponder_code");
	case AIRCRAFT_NAV1_BEARING : return ("sim/cockpit/radios/nav1_dir_degt");
	case AIRCRAFT_NAV2_BEARING : return ("sim/cockpit/radios/nav2_dir_degt");
	case AIRCRAFT_ADF1_BEARING : return ("sim/cockpit/radios/adf1_dir_degt");
	case AIRCRAFT_ADF2_BEARING : return ("sim/cockpit/radios/adf2_dir_degt");
	case AIRCRAFT_MARKERS_OM : return ("sim/cockpit/misc/over_outer_marker");
	case AIRCRAFT_MARKERS_MM : return ("sim/cockpit/misc/over_middle_marker");
	case AIRCRAFT_MARKERS_IM : return ("sim/cockpit/misc/over_inner_marker");

	case AIRCRAFT_FLAPS_POSITION : return("sim/flightmodel2/controls/flap_handle_deploy_ratio");
	case AIRCRAFT_FLAPS1_POSITION : return("sim/flightmodel2/controls/flap1_deploy_ratio");
	case AIRCRAFT_FLAPS2_POSITION : return("sim/flightmodel2/controls/flap2_deploy_ratio");
	case AIRCRAFT_SLATS1_POSITION : return("sim/flightmodel2/controls/slat1_deploy_ratio");
	case AIRCRAFT_SLATS2_POSITION : return("sim/flightmodel2/controls/slat2_deploy_ratio");
	case AIRCRAFT_LANDING_GEAR_DOWN : return ("sim/flightmodel2/gear/deploy_ratio");
	case AIRCRAFT_ON_GROUND : return ("sim/flightmodel/failures/onground_any");

	case AICRAFT_EFIS_ND1_RANGE : return ("sim/cockpit2/EFIS/map_range");
	case AICRAFT_EFIS_ND1_MODE : return ("sim/cockpit2/EFIS/map_mode");
	case AICRAFT_EFIS_ND1_WEATHER : return ("sim/cockpit2/EFIS/EFIS_weather_on");
	case AICRAFT_EFIS_ND1_TCAS : return ("sim/cockpit2/EFIS/EFIS_tcas_on");
	case AICRAFT_EFIS_ND1_NDB : return ("sim/cockpit2/EFIS/EFIS_ndb_on");
	case AICRAFT_EFIS_ND1_VOR : return ("sim/cockpit2/EFIS/EFIS_vor_on");
	case AICRAFT_EFIS_ND1_WPT : return ("sim/cockpit2/EFIS/EFIS_fix_on");
	case AICRAFT_EFIS_ND1_AIRPORTS : return ("sim/cockpit2/EFIS/EFIS_airport_on");
	case AIRCRAFT_EFIS_ND1_TERRAIN  : return("");
	case AIRCRAFT_EFIS_NAV_SOURCE_PFD1 : return("sim/cockpit2/radios/actuators/HSI_source_select_pilot");
	case AIRCRAFT_EFIS_NAV_SOURCE_PFD2 : return("sim/cockpit2/radios/actuators/HSI_source_select_copilot");
	case AIRCRAFT_FUEL_QTY : return("sim/cockpit2/fuel/fuel_quantity");
	case AIRCRAFT_FUEL_QTY_GL : return("sim/cockpit2/fuel/fuel_quantity"); //must be transformed in XplaneData.java from kg to gallons
	case ENGINE_RPM : return("sim/flightmodel2/engines/engine_rotation_speed_rad_sec");
	case ENGINE_MIXTURE : return("sim/flightmodel/engine/ENGN_mixt");
	case ENGINE_FUEL_FLOW_GL_MN : return("sim/flightmodel/engine/ENGN_FF_");//must be transformed in XplaneData.java from kg/s to gl/min
	case ENGINE_OIL_TEMP : return("sim/flightmodel/engine/ENGN_oil_temp_c");
	case ENGINE_OIL_PRESSURE : return("sim/flightmodel/engine/ENGN_oil_press_psi");
	case ENGINE_EGT : return ("sim/cockpit2/engine/indicators/EGT_deg_C");
	case ENGINE_CHT : return("sim/cockpit2/engine/indicators/CHT_deg_C");
	case ENGINE_N1 : return("sim/cockpit2/engine/indicators/N1_percent");
	case ENGINE_N2 : return("sim/cockpit2/engine/indicators/N2_percent");
	case ENGINE_EPR : return("sim/cockpit2/engine/indicators/EPR_ratio");
	case ENGINE_TORQUE : return("sim/cockpit2/engine/indicators/torque_n_mtr");
	case ENGINE_ITT : return("sim/cockpit2/engine/indicators/ITT_deg_C");

	case ENGINE_MAN_PRESS_HG : return ("sim/cockpit2/engine/indicators/MPR_in_hg");
	case AIRCRAFT_SYSTEMS_APU_ON : return("sim/cockpit/electrical/generator_apu_on");
	case AIRCRAFT_SYSTEMS_APU_SWITCH : return("sim/cockpit/engine/APU_switch");
	case AIRCRAF_SYSTEMS_APU_RUNNING : return("sim/cockpit/engine/APU_running");
	case AIRCRAF_SYSTEMS_APU_N1  : return("sim/cockpit/engine/APU_N1");

	case FMS1_ENTRIES_NUMBER : return ("avandro/fms1/nb_entries");
	case FMS2_ENTRIES_NUMBER : return ("avandro/fms2/nb_entries");
	case FMS1_SELECTED_ENTRY : return ("avandro/fms1/selected_entry");
	case FMS2_SELECTED_ENTRY : return ("avandro/fms2/selected_entry");
	case FMS_ACTIVE : return ("avandro/fms/active");
	case FMS1_ENTRIES_DATA : return ("avandro/fms1/data");
	case FMS2_ENTRIES_DATA : return ("avandro/fms2/data");

	case AIRCRAFT_CONTROLS_YOKE_PITCH : return ("sim/joystick/FC_ptch");
	case AIRCRAFT_CONTROLS_YOKE_ROLL : return ("sim/joystick/FC_roll");

	case AIRCRAFT_CONF_ENGINE_NB  : return ("sim/aircraft/engine/acf_num_engines");
	case AIRCRAFT_CONF_BATTERY_NB : return ("sim/aircraft/electrical/num_batteries");
	case AIRCRAFT_CONF_GENERATOR_NB : return ("sim/aircraft/electrical/num_generators");
	case AIRCRAFT_CONF_INVERER_NB : return ("sim/aircraft/electrical/num_inverters");
	case AIRCRAFT_CONF_RETRACT_LANDING_GEAR : return ("sim/aircraft/gear/acf_gear_retract");
	case ALERT_MASTER_CAUTION : return ("sim/cockpit2/annunciators/master_caution");
	case ALERT_MASTER_WARNING : return ("sim/cockpit2/annunciators/master_warning");
	case ALERT_AP_DISC : return ("sim/cockpit2/annunciators/autopilot_disconnect");
	case ALERT_VACUM_LOW : return ("sim/cockpit2/annunciators/low_vacuum");
	case ALERT_ELEC_VOLTAGE_LOW : return ("sim/cockpit2/annunciators/low_voltage");
	case ALERT_FUEL_QTY : return ("sim/cockpit2/annunciators/fuel_quantity");
	case ALERT_HYDR_PRESS : return ("sim/cockpit2/annunciators/hydraulic_pressure");
	case ALERT_CONTROLS_SPEEDBRK : return ("sim/cockpit2/annunciators/speedbrake");
	case ALERT_ALERT_SURV_GPWS : return ("sim/cockpit2/annunciators/GPWS");
	case ALERT_ALERT_ICE : return ("sim/cockpit2/annunciators/ice");
	case ALERT_PITOT_HEAT : return ("sim/cockpit2/annunciators/pitot_heat");
	case ALERT_CONTROLS_SLATS : return ("sim/cockpit2/annunciators/slats");
	case ALERT_FUEL_PRESS_LOW : return ("sim/cockpit2/annunciators/fuel_pressure_low");
	case ALERT_ENGINE_OIL_PRESS_LOW : return ("sim/cockpit2/annunciators/oil_pressure_low");
	case ALERT_ENGINE_OIL_TEMP_HIGH : return ("sim/cockpit2/annunciators/oil_temperature_high");
	case ALERT_ENGINE_GENERATOR : return ("sim/cockpit2/annunciators/generator_off");
	case ALERT_ENGINE_FIRE : return ("sim/cockpit2/annunciators/engine_fires");
	case ALERT_ENGINE_REVERSER_ON : return ("sim/cockpit2/annunciators/reverser_on");
	case ALERT_ENGINE_INVERTER_OFF : return ("sim/cockpit2/annunciators/inverter_off");
	case ALERT_ENGINE_N1_LOW : return ("sim/cockpit2/annunciators/N1_low");
	case ALERT_ENGINE_N1_HIGH : return ("sim/cockpit2/annunciators/N1_high");
	case ALERT_BLEED_ICE_VANE_EXTD : return ("sim/cockpit2/annunciators/ice_vane_extend");
	case ALERT_BLEED_ICE_VANE_FAIL : return ("sim/cockpit2/annunciators/ice_vane_fail");
	case ALERT_BLEED_AIR_OFF : return ("sim/cockpit2/annunciators/bleed_air_off");
	case ALERT_BLEED_AIR_FAIL : return ("sim/cockpit2/annunciators/bleed_air_fail");
	case ALERT_PROP_FEATHER_ARM : return ("sim/cockpit2/annunciators/auto_feather_arm");
	case ALERT_FUEL_TRANSFER : return ("sim/cockpit2/annunciators/fuel_transfer");
	case ALERT_ELEC_VOLTAGE_HIGH : return ("sim/cockpit2/annunciators/hvac");
	case ALERT_ELEC_BATT_HI : return ("sim/cockpit2/annunciators/battery_charge_hi");
	case ALERT_CABIN_ALT_LOW : return ("sim/cockpit2/annunciators/cabin_altitude_12500");
	case ALERT_AP_TRIM_FAIL : return ("sim/cockpit2/annunciators/autopilot_trim_fail");
	case ALERT_FUEL_XFEED_ON : return ("sim/cockpit2/annunciators/crossfeed_on");
	case ALERT_CABIN_DOOR_OPEN : return ("sim/cockpit2/annunciators/cabin_door_open");
	case ALERT_ELEC_GPU_ON : return ("sim/cockpit2/annunciators/external_power_on");
	case ALERT_CABIN_OXY_ON : return ("sim/cockpit2/annunciators/passenger_oxy_on");
	case ALERT_FUEL_PRESS : return ("sim/cockpit2/annunciators/fuel_pressure");
	case ALERT_ENGINE_OIL_PRESS : return ("sim/cockpit2/annunciators/oil_pressure");
	case ALERT_ENGINE_OIL_TEMP : return ("sim/cockpit2/annunciators/oil_temperature");
	case ALERT_ELEC_GENERATOR : return ("sim/cockpit2/annunciators/generator");
	case ALERT_ENGINE_REVERSE : return ("sim/cockpit2/annunciators/reverser_deployed");
	case ALERT_ENGINE_INVERTER : return ("sim/cockpit2/annunciators/inverter");
	case ALERT_CONTROLS_STALL : return ("sim/cockpit2/annunciators/stall_warning");
	case ALERT_CONTROLS_GEAR : return ("sim/cockpit2/annunciators/gear_warning");

	}
	return res;
}

XPLMDataTypeID getDataType(int index){
	switch (index){
	case FMS1_ENTRIES_NUMBER:
	case FMS2_ENTRIES_NUMBER:
	case FMS1_SELECTED_ENTRY:
	case FMS2_SELECTED_ENTRY:
	case FMS_ACTIVE:
	return xplmType_Int;
	default:
		XPLMDataRef dataRef = XPLMFindDataRef(getDataRef(index).c_str());
		return XPLMGetDataRefTypes(dataRef);

	}
}




