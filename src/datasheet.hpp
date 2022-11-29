/*
 * defines.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rosaycy
 */

#ifndef SRC_DATASHEET_HPP_
#define SRC_DATASHEET_HPP_
#include <string>
#include "XPLMDataAccess.h"
enum DataSheets{
	PLUGIN_TIMER = -1,
	/** this is used to detect a false datasheet reference*/
	NOT_A_REFERENCE  = 0,
	/**TEXT: aircraft type name eg: B58, B737-800...*/
	AIRCRAFT_MODEL  = 1,
	/**TEXT: return the aircraft tail number*/
	AIRCRAFT_INFO_TAIL_NUMBER = 2,

	/**FLOAT: indicated airspeed in knots. does not account for the sensor*/
	AIRCRAFT_AIRSPEED_INDICATED = 101,
	/**FLOAT: indicated airspeed in mach. does not account for the sensor*/
	AIRCRAFT_AIRSPEED_MACH = 102,
	/**FLOAT: selected airspeed on the autopilot  = may be mach or knots depending on the autopilot mode selection */
	AIRCRAFT_AUTOPILOT_SELECTED_AIRSPEED = 103,
	/**FLOAT: airspeed trend in knots per seconds */
	AIRCRAFT_AIRSPEED_ACCELERATION = 104,
	/**FLOAT: VSPEED: Speed that will allow for the best rate of climb with OEI one Engine Inop */
	AIRCRAFT_AIRSPEED_LIMITS_VYSE = 105,
	/**FLOAT: Minimum control speed in the air  = or airborne.
	 * The minimum speed at which steady straight flight can be maintained when an engine fails or is inoperative
	 * and with the corresponding opposite engine set to provide maximum thrust*/
	AIRCRAFT_AIRSPEED_LIMITS_VMCA = 106,
	/**FLOAT: Stall speed or minimum steady flight speed for which the aircraft is still controllable*/
	AIRCRAFT_AIRSPEED_LIMITS_VS = 107,
	/**FLOAT: Stall speed or minimum flight speed in landing configuration.*/
	AIRCRAFT_AIRSPEED_LIMITS_VS0 = 108,
	/**FLOAT: Maximum structural cruising speed or maximum speed for normal operations.*/
	AIRCRAFT_AIRSPEED_LIMITS_VNO = 109,
	/**FLOAT: Never exceed speed*/
	AIRCRAFT_AIRSPEED_LIMITS_VNE = 110,
	/**FLOAT: Maximum flap extended speed*/
	AIRCRAFT_AIRSPEED_LIMITS_VFE = 111,
	/**FLOAT: Maximum landing gear extended speed.*/
	AIRCRAFT_AIRSPEED_LIMITS_VLE = 112,
	/**FLOAT: aircraft vertical velocity in feet/min*/
	AIRCRAFT_VERTICAL_VELOCITY = 113,
	/**FLOAT: aircraft true speed in knots*/
	AIRCRAFT_AIRSPEED_TRUE = 114,

	/**FLOAT: aircraft heading magnetic*/
	AIRCRAFT_HEADING_MAG = 200,
	/**FLOAT: aircraft heading true north*/
	AIRCRAFT_HEADING_TRUE = 201,
	/**FLOAT: aircraft track on ground*/
	AIRCRAFT_GROUND_TRACK = 202,
	/**FLOAT: aircraft ground speed in knots*/
	AIRCRAFT_GROUND_SPEED = 203,

	/**FLOAT: aircraft baromtric altitude in feet*/
	AIRCRAFT_ALTITUDE_BARO = 300,
	/**FLOAT: return the aircraft position  = lat*/
	AIRCRAFT_POSITION_LATITUDE = 301,
	/**FLOAT: return the aircraft position  = lon*/
	AIRCRAFT_POSITION_LONGITUDE = 302,
	/**FLOAT: returns the radio altimeter 1 altitude in feet*/
	AIRCRAFT_ALTITUDE_RADIO1 = 303,
	/**FLOAT; returns the decision altitude*/
	AIRCRAFT_RADALT_DECISION_HEIGHT = 304,


	/**FLOAT: aircraft roll angle in degrees  = positive right*/
	AIRCRAFT_ATTITUTE_ROLL = 400,
	/**FLOAT: aircraft pitch angle in degrees  = positive up*/
	AIRCRAFT_ATTITUTE_PITCH = 401,
	/**FLOAT: aircraft yaw angle in degrees  = positive right*/
	AIRCRAFT_ATTITUDE_YAW = 402,
	/**FLOAT: aircraft angle of attack  = positive up*/
	AIRCRAFT_ANGLE_OF_ATTACK = 403,
	/**FLOAT: aircraft vertical flight path angle (positive up)*/
	AIRCRAFT_ATTITUTE_VFPA = 404,
	/**FLOAT: aircraft horizontal flight path angle (positive right)*/
	AIRCRAFT_ATTITUTE_HFPA = 405,

	/**BOOLEAN : aircraft AHRS validity */
	AIRCRAFT_ATTITUTE_AHRS_FAILURE = 410,

	/**FLOAT: total g-force on the aircraft (vertical)*/
	AIRCRAFT_FORCES_G_VERTICAL = 420,
	/**FLOAT: total g-force on the aircraft (along the plane)*/
	AIRCRAFT_FORCES_G_LONGITUDINAL = 421,
	/**FLOAT: total g-force on the aircraft (lateral)*/
	AIRCRAFT_FORCES_G_LATERAL = 422,

	/**FLOAT: flight director pitch angle in degrees  = positive up*/
	AIRCRAFT_FD_PITCH = 500,
	/**FLOAT: flight director roll angle in degrees  = positive right*/
	AIRCRAFT_FD_ROLL = 501,

	/**FLOAT: aircraft vertical velocity in feet/min*/
	AIRCRAFT_AUTOPILOT_STATUS = 600,
	/**BOOL: return 0 if nothing is engaged 1 if FD only and 2 if FD+AP*/
	AIRCRAFT_AUTOPILOT_MODE = 601,
	/**INTEGER: return 1 of the autothrottle is on, O if not*/
	AIRCRAFT_AUTOTHROTTLE_ON = 602,
	/**BOOL: return 1 of the autopilot is on, O if not*/
	AIRCRAFT_AUTOPILOT_ON = 603,
	/**INTEGER: returns 0 if source is AP1 or 1 for AP2*/
	AIRCRAFT_AUTOPILOT_SOURCE = 604,
	/**FLOAT: returns the selected true heading */
	AIRCRAFT_AUTOPILOT_SELECTED_HEADING_TRUE = 605,
	/**FLOAT: returns the selected magnetic heading left*/
	AIRCRAFT_AUTOPILOT_SELECTED_HEADING_MAG_1 = 606,
	/**FLOAT: returns the selected magnetic heading right*/
	AIRCRAFT_AUTOPILOT_SELECTED_HEADING_MAG_2 = 607,
	/**FLOAT: returns the selected altitude */
	AIRCRAFT_AUTOPILOT_SELECTED_ALTITUDE = 608,
	/**INTEGER: return 0 if off, 1 if armed, 2 if captured*/
	AIRCRAFT_AUTOPILOT_GS_STATUS = 609,
	/**INTEGER: return 0 if off, 1 if armed, 2 if captured*/
	AIRCRAFT_AUTOPILOT_APP_STATUS = 610,
	/**INTEGER: return 0 if off, 1 if armed, 2 if captured*/
	AIRCRAFT_AUTOPILOT_SPEED_STATUS = 611,
	/**INTEGER: return 0 if off, 1 if armed, 2 if captured*/
	AIRCRAFT_AUTOPILOT_ALT_STATUS = 612,
	/**FLOAT: autopilot selected V/S in feet/min*/
	AIRCRAFT_AUTOPILOT_SELECTED_VS = 613,
	/**BOOL: autopilot heading mode 1: engaged, 0 : not engaged */
	AIRCRAFT_AUTOPILOT_HDG_MODE = 614,
	/**BOOL: autopilot altitude mode 1: engaged, 0 : not engaged */
	AIRCRAFT_AUTOPILOT_ALT_MODE = 615,
    /**INTEGER  Autopilot approach status.  0=off,1=armed,2=captured*/
    AIRCRAFT_AUTOPILOT_APPROACH_STATUS = 616,

	/**FLOAT: vertical deviation of the nav 1  = in dots*/
	AIRCRAFT_NAV1_VDEV = 700,
	/**FLOAT: horizontal deviation of the nav 1  = in dots*/
	AIRCRAFT_NAV1_HDEV = 701,
	/**FLOAT: vertical deviation of the nav 2  = in dots*/
	AIRCRAFT_NAV2_VDEV = 702,
	/**FLOAT: horizontal deviation of the nav 2  = in dots*/
	AIRCRAFT_NAV2_HDEV = 703,
	/**BOOL: return 1 if the glide slope for nav 1 is flagged*/
	AIRCRAFT_NAV1_GS_FLAGGED = 704,
	/**BOOL: return 1 if the glide slope for nav 2 is flagged*/
	AIRCRAFT_NAV2_GS_FLAGGED = 705,
	/**BOOL: return 1 if the locator for nav 1 is flagged*/
	AIRCRAFT_NAV1_LOC_FLAGGED = 706,
	/**BOOL: return 1 if the locator for nav 1 is flagged*/
	AIRCRAFT_NAV2_LOC_FLAGGED = 708,
	/**INTEGER: return the OBS TO/FROM indicator from nav 1. 0 if TO, 1 if FROM*/
	AIRCRAFT_NAV1_TO_FROM = 709,
	/**FLOAT: frequency set on VHF 1 in Hz  = eg 121900 is provided for 121.90 MHz*/
	AIRCRAFT_COM1_FREQ = 710,
	/**FLOAT: frequency set on VHF 2 in Hz  = eg 121900 is provided for 121.90 MHz*/
	AIRCRAFT_COM2_FREQ = 711,
	/**TEXT: return the ground station ident  = 3 alphanum selected on NAV 1*/
	AIRCRAFT_NAV1_IDENT = 712,
	/**FLOAT: frequency set on NAV 1 in Hz  = eg 109800 is provided for 109.80 Mhz*/
	AIRCRAFT_NAV1_FREQ = 713,
	/**FLOAT: the OBS set on NAV 1 in degrees  = positive right*/
	AIRCRAFT_NAV1_OBS = 714,
	/**FLOAT: the DME distance for NAV 1 in NM*/
	AIRCRAFT_NAV1_DME = 715,
	/**TEXT: return the ground station ident  = 3 alphanum selected on NAV 2*/
	AIRCRAFT_NAV2_IDENT = 716,
	/**FLOAT: frequency set on NAV 2 in Hz  = eg 109800 is provided for 109.80 Mhz*/
	AIRCRAFT_NAV2_FREQ = 717,
	/**FLOAT: the OBS set on NAV 2 in degrees  = positive right*/
	AIRCRAFT_NAV2_OBS = 718,
	/**FLOAT: the DME distance for NAV 2 in NM*/
	AIRCRAFT_NAV2_DME = 719,
	/**FLOAT: aircraft baro setting 1  = left can be Hpa or iHg*/
	AIRCRAFT_BARO_SETTING_1 = 720,
	/**FLOAT: aircraft baro setting 2  = right can be Hpa or iHg*/
	AIRCRAFT_BARO_SETTING_2 = 721,
	/**FLOAT: frequency set on ADF 1 in Hz  = eg 345000 is provided for 345 Mhz*/
	AIRCRAFT_ADF1_FREQ = 722,
	/**FLOAT: frequency set on ADF 2 in Hz  = eg 345000 is provided for 345 Mhz*/
	AIRCRAFT_ADF2_FREQ = 723,
	/**INTEGER: ATC XPRD code*/
	AIRCRAFT_XPDR_CODE = 724,
    /**FLOAT: the bearing to the VOR 1*/
    AIRCRAFT_NAV1_BEARING =725,
    /**FLOAT: the bearing to the VOR 2*/
    AIRCRAFT_NAV2_BEARING =726,
    /**FLOAT: the bearing to the ADF 1*/
    AIRCRAFT_ADF1_BEARING = 727,
    /**FLOAT: the bearing to the ADF 2*/
    AIRCRAFT_ADF2_BEARING = 728,
	/**BOOLEAN true if over outer marker*/
	AIRCRAFT_MARKERS_OM = 729,
	/**BOOLEAN true if over middle marker*/
	AIRCRAFT_MARKERS_MM = 730,
	/**BOOLEAN true if over inner marker*/
	AIRCRAFT_MARKERS_IM = 731,

	/**FLOAT:Actual flap position in % of full extension
	 * for example if 50% of 35 Deg full flaps, means 12.5 Deg*/
	AIRCRAFT_FLAPS_POSITION = 800,
	/**FLOAT:Actual flap set 1 position in % of full extension*/
	AIRCRAFT_FLAPS1_POSITION = 801,
	/**FLOAT:Actual flap set 2 position in % of full extension*/
	AIRCRAFT_FLAPS2_POSITION = 802,
	/**FLOAT:Actual slats set 1 position in % of full extension*/
	AIRCRAFT_SLATS1_POSITION = 803,
	/**FLOAT:Actual slap set 2 position in % of full extension*/
	AIRCRAFT_SLATS2_POSITION = 804,
	/**INTEGER: landing gear status 1: if Lg is down, 0 if not*/
	AIRCRAFT_LANDING_GEAR_DOWN = 810,
	/**BOOL: 1 if the A/C is on ground, 0 if airborne */
	AIRCRAFT_ON_GROUND = 811,
	/**BOOL: 1 if avionics is on*/
	AIRCRAFT_AVIONICS_ON = 820,


	/**INTEGER: the mode selected for the ND 1  = approach, vor, map, nav, plan*/
	AICRAFT_EFIS_ND1_MODE = 900,
	/**INTEGER: range selector value for ND 1  = 1 to 6 : index of the range selector*/
	AICRAFT_EFIS_ND1_RANGE = 901,
	/**BOOL: is weather displayed on ND 1*/
	AICRAFT_EFIS_ND1_WEATHER = 902,
	/**BOOL: is TCAS displayed on ND 1*/
	AICRAFT_EFIS_ND1_TCAS = 903,
	/**BOOL: are NDB displayed on ND 1*/
	AICRAFT_EFIS_ND1_NDB = 904,
	/**BOOL: are VORs displayed on ND 1*/
	AICRAFT_EFIS_ND1_VOR = 905,
	/**BOOL: are waypoints displayed on ND 1*/
	AICRAFT_EFIS_ND1_WPT = 906,
	/**BOOL: are airports displayed on ND 1*/
	AICRAFT_EFIS_ND1_AIRPORTS = 907,
	/**BOOL: is terrain displayed on ND 1*/
	AIRCRAFT_EFIS_ND1_TERRAIN = 908,
	/** INTEGER: Nav source for pilot */
	AIRCRAFT_EFIS_NAV_SOURCE_PFD1 = 950,
	/** INTEGER: Nav source for co-pilot */
	AIRCRAFT_EFIS_NAV_SOURCE_PFD2 = 951,

	/**FLOAT[9] provides the fuel quantity of the different tanks in kg*/
	AIRCRAFT_FUEL_QTY = 1001,
	/**FLOAT[9] provides the fuel quantity of the different tanks in gallons*/
	AIRCRAFT_FUEL_QTY_GL = 1002,

	/**FLOAT[8] provides the RPM per engine*/
	ENGINE_RPM = 2000,
	/**FLOAT[8] provides the mixture per engine*/
	ENGINE_MIXTURE = 2001,
	/**FLOAT[8] provides the fuel flow per engine in Gallons/min*/
	ENGINE_FUEL_FLOW_GL_MN = 2002,
	/**FLOAT[8] provides the oil temperature per engine in degrees Celcius*/
	ENGINE_OIL_TEMP =2003,
	/**FLOAT[8] provides the oil pressure per engine in PSI*/
	ENGINE_OIL_PRESSURE = 2004,
	/**FLOAT[8] provides the Exhaust Gas Temperature in �C*/
	ENGINE_EGT = 2005,
	/**FLOAT[8] provides the manual pressure in  Hg*/
	ENGINE_MAN_PRESS_HG = 2006,
	/**FLOAT[8]	n	Engine CHT (Cylindar temp) in degrees C*/
	ENGINE_CHT = 2007,
	/**FLOAT[8]	engines	N1 %.*/
	ENGINE_N1 = 2100,
	/**float[8] N2, %.*/
	ENGINE_N2 = 2101,
	/** FLOAT[8] Exhaust Pressure ratio*/
	ENGINE_EPR = 2102,
	/**FLOAT [8] engine torque in Newton/meter*/
	ENGINE_TORQUE = 2103,
	/**FLOAT[8] Internal turbine Temp in deg C*/
	ENGINE_ITT = 2104,

	/**-======SYSTEMS=======-*/
	/** BOOL: true if the APU generator is on */
	AIRCRAFT_SYSTEMS_APU_ON = 3001,
	/** INTEGER: APU switch status (0 : off, 1: on, 2 : start*/
	AIRCRAFT_SYSTEMS_APU_SWITCH = 3002,
	/**BOOL: true if APU is running*/
	AIRCRAF_SYSTEMS_APU_RUNNING = 3003,
	/**FLOAT: N1 of the APU turbine*/
	AIRCRAF_SYSTEMS_APU_N1 = 3004,

	/**Aircraft configuration*/
	/**INTEGER number of engines*/
	AIRCRAFT_CONF_ENGINE_NB = 5000,
	/**INTEGER number of batteries*/
	AIRCRAFT_CONF_BATTERY_NB = 5001,
	/**INTEGER number of electrical generator*/
	AIRCRAFT_CONF_GENERATOR_NB = 5002,
	/**INTEGER number of inverters*/
	AIRCRAFT_CONF_INVERER_NB =5003,
	/**BOOL: true if the aicraft has retractable landing gear*/
	AIRCRAFT_CONF_RETRACT_LANDING_GEAR = 5100,

	/** FMS functions */
	/**INTEGER: number of entries in FMS 1*/
	FMS1_ENTRIES_NUMBER = 8001,
	/**INTEGER: number of entries in FMS 2*/
	FMS2_ENTRIES_NUMBER = 8002,
	/**INTEGER: CURRENT SELECTION IF MFS 1*/
	FMS1_SELECTED_ENTRY = 8003,
	/**INTEGER: CURRENT SELECTION IF MFS 2*/
	FMS2_SELECTED_ENTRY = 8004,
	/**INTEGER active FMS*/
	FMS_ACTIVE = 8005,
	/**FMSstructure[256] FMS entries in FMS1*/
	FMS1_ENTRIES_DATA = 8016,
	/**FMSstructure[256] FMS entries in FMS2*/
	FMS2_ENTRIES_DATA = 8017,

	/**FLOAT pitch value of the yoke*/
	AIRCRAFT_CONTROLS_YOKE_PITCH = 9001,
	/**FLOAT roll value of the yoke*/
	AIRCRAFT_CONTROLS_YOKE_ROLL = 9002,

	/**Alerts */
	ALERT_MASTER_CAUTION = 10000,
	ALERT_MASTER_WARNING = 10001,
	ALERT_AP_DISC = 10100,
	ALERT_AP_TRIM_FAIL = 10101,
	ALERT_ELEC_VOLTAGE_LOW = 10200,
	ALERT_ELEC_VOLTAGE_HIGH = 10201,
	ALERT_ELEC_BATT_HI = 10202,
	ALERT_ELEC_GENERATOR = 10203,
	ALERT_ELEC_GPU_ON = 10204,
	ALERT_VACUM_LOW = 10210,
	ALERT_FUEL_QTY = 10301,
	ALERT_FUEL_PRESS_LOW = 10302,
	ALERT_FUEL_TRANSFER = 10303,
	ALERT_FUEL_XFEED_ON = 10304,
	ALERT_FUEL_PRESS = 10305,
	ALERT_HYDR_PRESS = 10400,
	ALERT_ALERT_SURV_GPWS = 10500,
	ALERT_ALERT_ICE = 10600,
	ALERT_PITOT_HEAT = 10601,
	ALERT_BLEED_ICE_VANE_EXTD = 10700,
	ALERT_BLEED_ICE_VANE_FAIL = 10701,
	ALERT_BLEED_AIR_OFF = 10702,
	ALERT_BLEED_AIR_FAIL = 10703,
	ALERT_PROP_FEATHER_ARM = 10800,
	ALERT_CABIN_ALT_LOW = 10900,
	ALERT_CABIN_OXY_ON = 10901,
	ALERT_CABIN_DOOR_OPEN = 10902,
	ALERT_ENGINE_OIL_PRESS_LOW = 11000,
	ALERT_ENGINE_OIL_TEMP_HIGH = 11001,
	ALERT_ENGINE_GENERATOR = 11002,
	ALERT_ENGINE_FIRE = 11003,
	ALERT_ENGINE_INVERTER = 11004,
	ALERT_ENGINE_REVERSER_ON = 11005,
	ALERT_ENGINE_INVERTER_OFF = 11006,
	ALERT_ENGINE_OIL_PRESS = 11007,
	ALERT_ENGINE_OIL_TEMP = 11008,
	ALERT_ENGINE_N1_LOW = 11009,
	ALERT_ENGINE_N1_HIGH = 11010,
	ALERT_ENGINE_REVERSE = 11011,
	ALERT_CONTROLS_SPEEDBRK = 12000,
	ALERT_CONTROLS_SLATS = 12001,
	ALERT_CONTROLS_STALL = 12002,
	ALERT_CONTROLS_GEAR = 12003


};

std::string getDataRef(int index);
XPLMDataTypeID getDataType(int index);
#endif /* SRC_DATASHEET_HPP_ */
