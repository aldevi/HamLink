#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_parser.h"

void hamlinkd_parse_config(hamlinkd_config* config) {
    char line[MAX_LINE_LENGTH];
    char* key;
    char* value;
    FILE* fp = fopen(CONFIG_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        key = strtok(line, "=");
        value = strtok(NULL, "=");

        // Don't forget to remove the newline character
        if (value != NULL && value[strlen(value) - 1] == '\n')
            value[strlen(value) - 1] = '\0';

        if (key != NULL && value != NULL) {
            if (strcmp("ax25_ip", key) == 0)
                strcpy(config->ax25_ip, value);
            else if (strcmp("ax25_netmask", key) == 0)
                strcpy(config->ax25_netmask, value);
            else if (strcmp("ax25_callsign", key) == 0)
                strcpy(config->ax25_callsign, value);
            else if (strcmp("ax25_baudrate", key) == 0)
                config->ax25_baudrate = atoi(value);
            else if (strcmp("ax25_enable_fx25", key) == 0)
                config->ax25_enable_fx25 = atoi(value);
            else if (strcmp("ax25_ptt_gpio", key) == 0)
                config->ax25_ptt_gpio = atoi(value);
            else if (strcmp("ax25_ptt_inverted", key) == 0)
                config->ax25_ptt_inverted = atoi(value);
            else if (strcmp("gateway_enable", key) == 0)
                config->gateway_enable = atoi(value);
            else if (strcmp("gateway_eth_enable", key) == 0)
                config->eth_gateway_enable = atoi(value);
            else if (strcmp("gateway_eth_ip", key) == 0)
                strcpy(config->eth_gateway_ip, value);
            else if (strcmp("gateway_eth_netmask", key) == 0)
                strcpy(config->eth_gateway_netmask, value);
            else if (strcmp("gateway_wifi_enable", key) == 0)
                config->wifi_gateway_enable = atoi(value);
            else if (strcmp("gateway_wifi_ssid", key) == 0)
                strcpy(config->wifi_gateway_ssid, value);
            else if (strcmp("gateway_wifi_psk", key) == 0)
                strcpy(config->wifi_gateway_psk, value);
            else if (strcmp("gateway_wifi_channel", value) == 0)
                config->wifi_gateway_channel = atoi(value);
            else if (strcmp("gateway_dhcp_enable", key) == 0)
                config->gateway_dhcp_enable = atoi(value);
            else if (strcmp("gateway_dhcp_start", key) == 0)
                strcpy(config->gateway_dhcp_start, value);
            else if (strcmp("gateway_dhcp_end", key) == 0)
                strcpy(config->gateway_dhcp_end, value);
            else if (strcmp("audio_device", key) == 0)
                strcpy(config->audio_device, value);
        }
    }
    fclose(fp);
}

void hamlinkd_save_config(hamlinkd_config* config) {
    FILE* fp = fopen("/home/alexis/RPI/hamlinkdconf.test", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp, "ax25_ip=%s\n", config->ax25_ip);
    fprintf(fp, "ax25_netmask=%s\n", config->ax25_netmask);
    fprintf(fp, "ax25_callsign=%s\n", config->ax25_callsign);
    fprintf(fp, "ax25_baudrate=%d\n", config->ax25_baudrate);
    fprintf(fp, "ax25_enable_fx25=%d\n", config->ax25_enable_fx25);
    fprintf(fp, "ax25_ptt_gpio=%d\n", config->ax25_ptt_gpio);
    fprintf(fp, "ax25_ptt_inverted=%d\n", config->ax25_ptt_inverted);
    fprintf(fp, "gateway_enable=%d\n", config->gateway_enable);
    fprintf(fp, "gateway_eth_enable=%d\n", config->eth_gateway_enable);
    fprintf(fp, "gateway_eth_ip=%s\n", config->eth_gateway_ip);
    fprintf(fp, "gateway_eth_netmask=%s\n", config->eth_gateway_netmask);
    fprintf(fp, "gateway_wifi_enable=%d\n", config->wifi_gateway_enable);
    fprintf(fp, "gateway_wifi_ssid=%s\n", config->wifi_gateway_ssid);
    fprintf(fp, "gateway_wifi_psk=%s\n", config->wifi_gateway_psk);
    fprintf(fp, "gateway_wifi_channel=%d\n", config->wifi_gateway_channel);
    fprintf(fp, "gateway_dhcp_enable=%d\n", config->gateway_dhcp_enable);
    fprintf(fp, "gateway_dhcp_start=%s\n", config->gateway_dhcp_start);
    fprintf(fp, "gateway_dhcp_end=%s\n", config->gateway_dhcp_end);
    fprintf(fp, "audio_device=%s\n", config->audio_device);
}

void hamlinkd_print_config(hamlinkd_config* config) {
    printf("ax25_ip: %s\n", config->ax25_ip);
    printf("ax25_netmask: %s\n", config->ax25_netmask);
    printf("ax25_callsign: %s\n", config->ax25_callsign);
    printf("ax25_baudrate: %d\n", config->ax25_baudrate);
    printf("ax25_enable_fx25: %d\n", config->ax25_enable_fx25);
    printf("ax25_ptt_gpio: %d\n", config->ax25_ptt_gpio);
    printf("ax25_ptt_inverted: %d\n", config->ax25_ptt_inverted);
    printf("gateway_enable: %d\n", config->gateway_enable);
    printf("gateway_eth_enable: %d\n", config->eth_gateway_enable);
    printf("gateway_eth_ip: %s\n", config->eth_gateway_ip);
    printf("gateway_eth_netmask: %s\n", config->eth_gateway_netmask);
    printf("gateway_wifi_enable: %d\n", config->wifi_gateway_enable);
    printf("gateway_wifi_ssid: %s\n", config->wifi_gateway_ssid);
    printf("gateway_wifi_psk: %s\n", config->wifi_gateway_psk);
    printf("gateway_wifi_channel: %d\n", config->wifi_gateway_channel);
    printf("gateway_dhcp_enable: %d\n", config->gateway_dhcp_enable);
    printf("gateway_dhcp_start: %s\n", config->gateway_dhcp_start);
    printf("gateway_dhcp_end: %s\n", config->gateway_dhcp_end);
    printf("audio_device: %s\n", config->audio_device);
}