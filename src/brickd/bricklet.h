/*
 * brickd
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * bricklet.h: SPI Tinkerforge Protocol (SPITFP) implementation for direct
 *             communication between brickd and Bricklets with co-processor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BRICKD_BRICKLET_H
#define BRICKD_BRICKLET_H

#include <stdbool.h>
#include <stdint.h>

#include <daemonlib/threads.h>
#include <daemonlib/queue.h>

#include "stack.h"

typedef struct {
    char spi_device[64]; // e.g. "/dev/spidev0.0";
} BrickletConfig;

typedef struct {
    Stack base;

	Queue request_queue;
	Mutex request_queue_mutex;

	Queue response_queue;
	Mutex response_queue_mutex;

	int notification_event;
	int spi_fd;
	bool spi_thread_running;
	Thread spi_thread;

	BrickletConfig config;
} Bricklet;

Bricklet* bricklet_init(BrickletConfig *config);
void bricklet_exit(Bricklet *bricklet);

#endif // BRICKD_BRICKLET_H