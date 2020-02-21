/* SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2017-2019 WireGuard LLC. All Rights Reserved.
 */

package device

/* Reduce memory consumption for Android */

const (
	QueueOutboundSize          = 1024
	QueueInboundSize           = 1024
	QueueHandshakeSize         = 1024
	MaxSegmentSize             = 1700
	PreallocatedBuffersPerPool = 1024
)
