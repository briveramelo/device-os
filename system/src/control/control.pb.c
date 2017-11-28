/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9 at Thu Nov 23 14:57:36 2017. */

#include "control.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t particle_ctrl_WiFiAntennaConfiguration_fields[2] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, particle_ctrl_WiFiAntennaConfiguration, antenna, antenna, 0),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_WiFiAccessPoint_fields[15] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, particle_ctrl_WiFiAccessPoint, ssid, ssid, 0),
    PB_FIELD(  2, FIXED_LENGTH_BYTES, SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, bssid, ssid, 0),
    PB_FIELD(  3, UENUM   , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, security, bssid, 0),
    PB_FIELD(  4, UENUM   , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, cipher, security, 0),
    PB_FIELD(  5, UINT32  , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, channel, cipher, 0),
    PB_FIELD(  6, INT32   , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, max_data_rate, channel, 0),
    PB_FIELD(  7, INT32   , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, rssi, max_data_rate, 0),
    PB_FIELD(  8, STRING  , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, password, rssi, 0),
    PB_FIELD(  9, UENUM   , SINGULAR, STATIC  , OTHER, particle_ctrl_WiFiAccessPoint, eap_type, password, 0),
    PB_FIELD( 10, STRING  , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, inner_identity, eap_type, 0),
    PB_FIELD( 11, STRING  , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, outer_identity, inner_identity, 0),
    PB_FIELD( 12, BYTES   , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, private_key, outer_identity, 0),
    PB_FIELD( 13, BYTES   , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, client_certificate, private_key, 0),
    PB_FIELD( 14, BYTES   , SINGULAR, CALLBACK, OTHER, particle_ctrl_WiFiAccessPoint, ca_certificate, client_certificate, 0),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_WiFiAccessPointList_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, particle_ctrl_WiFiAccessPointList, aps, aps, &particle_ctrl_WiFiAccessPoint_fields),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_IPAddress_fields[3] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, particle_ctrl_IPAddress, protocol, protocol, 0),
    PB_FIELD(  2, BYTES   , SINGULAR, CALLBACK, OTHER, particle_ctrl_IPAddress, address, protocol, 0),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_IPConfiguration_fields[7] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, particle_ctrl_IPConfiguration, type, type, 0),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, particle_ctrl_IPConfiguration, address, type, &particle_ctrl_IPAddress_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, particle_ctrl_IPConfiguration, netmask, address, &particle_ctrl_IPAddress_fields),
    PB_FIELD(  4, MESSAGE , SINGULAR, STATIC  , OTHER, particle_ctrl_IPConfiguration, gateway, netmask, &particle_ctrl_IPAddress_fields),
    PB_FIELD(  5, MESSAGE , SINGULAR, STATIC  , OTHER, particle_ctrl_IPConfiguration, dhcp_server, gateway, &particle_ctrl_IPAddress_fields),
    PB_FIELD(  6, STRING  , SINGULAR, CALLBACK, OTHER, particle_ctrl_IPConfiguration, hostname, dhcp_server, 0),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_DNSConfiguration_fields[2] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, particle_ctrl_DNSConfiguration, server, server, &particle_ctrl_IPAddress_fields),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_NetworkConfiguration_fields[7] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, particle_ctrl_NetworkConfiguration, interface, interface, 0),
    PB_FIELD(  2, BOOL    , SINGULAR, STATIC  , OTHER, particle_ctrl_NetworkConfiguration, state, interface, 0),
    PB_FIELD(  3, STRING  , SINGULAR, CALLBACK, OTHER, particle_ctrl_NetworkConfiguration, name, state, 0),
    PB_FIELD(  4, FIXED_LENGTH_BYTES, SINGULAR, STATIC  , OTHER, particle_ctrl_NetworkConfiguration, mac, name, 0),
    PB_FIELD(  5, MESSAGE , SINGULAR, STATIC  , OTHER, particle_ctrl_NetworkConfiguration, ipconfig, mac, &particle_ctrl_IPConfiguration_fields),
    PB_FIELD(  7, MESSAGE , REPEATED, CALLBACK, OTHER, particle_ctrl_NetworkConfiguration, dnsconfig, ipconfig, &particle_ctrl_DNSConfiguration_fields),
    PB_LAST_FIELD
};

const pb_field_t particle_ctrl_GetNetworkConfigurationRequest_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, particle_ctrl_GetNetworkConfigurationRequest, interface, interface, 0),
    PB_LAST_FIELD
};








/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(particle_ctrl_IPConfiguration, address) < 65536 && pb_membersize(particle_ctrl_IPConfiguration, netmask) < 65536 && pb_membersize(particle_ctrl_IPConfiguration, gateway) < 65536 && pb_membersize(particle_ctrl_IPConfiguration, dhcp_server) < 65536 && pb_membersize(particle_ctrl_DNSConfiguration, server) < 65536 && pb_membersize(particle_ctrl_NetworkConfiguration, ipconfig) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_particle_ctrl_WiFiAntennaConfiguration_particle_ctrl_WiFiAccessPoint_particle_ctrl_WiFiAccessPointList_particle_ctrl_IPAddress_particle_ctrl_IPConfiguration_particle_ctrl_DNSConfiguration_particle_ctrl_NetworkConfiguration_particle_ctrl_GetNetworkConfigurationRequest)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(particle_ctrl_IPConfiguration, address) < 256 && pb_membersize(particle_ctrl_IPConfiguration, netmask) < 256 && pb_membersize(particle_ctrl_IPConfiguration, gateway) < 256 && pb_membersize(particle_ctrl_IPConfiguration, dhcp_server) < 256 && pb_membersize(particle_ctrl_DNSConfiguration, server) < 256 && pb_membersize(particle_ctrl_NetworkConfiguration, ipconfig) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_particle_ctrl_WiFiAntennaConfiguration_particle_ctrl_WiFiAccessPoint_particle_ctrl_WiFiAccessPointList_particle_ctrl_IPAddress_particle_ctrl_IPConfiguration_particle_ctrl_DNSConfiguration_particle_ctrl_NetworkConfiguration_particle_ctrl_GetNetworkConfigurationRequest)
#endif


/* @@protoc_insertion_point(eof) */